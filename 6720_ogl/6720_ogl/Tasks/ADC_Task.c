#include "ADC_Task.h"
#include "user_TasksInit.h"
#include "stdio.h"
#include "lvgl.h"
#include "tim.h"
#include "Beep_Device.h"
#include "Button_Device.h"
#include "user_HardwareInitTask.h"
#include "Gui_Task.h"
/* Private typedef -----------------------------------------------------------*/
#include "gui_guider.h"
#include "sd6500.h"
#include "power_ctrl.h"

extern sd6500_t g_sd;
extern I2C_Dev_Def g_i2c_sd;
/* Private function prototypes -----------------------------------------------*/
void i2c_init_adc(void)
{
  HAL_GPIO_WritePin(ADC_SCL_GPIO_Port, ADC_SCL_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(ADC_SDA_GPIO_Port, ADC_SDA_Pin, GPIO_PIN_SET);   
}
/* === 配置参数 === */
#ifndef SD6500_TASK_PERIOD_MS
#define SD6500_TASK_PERIOD_MS     100   // 任务基准周期（交替两路 => 每路 ~25 Hz）
#endif
#ifndef SD6500_READY_TIMEOUT_MS
#define SD6500_READY_TIMEOUT_MS    5   // 等待ADIF超时（> 0 避免卡死）
#endif
#ifndef SD6500_TOGGLE_SETTLE_MS
#define SD6500_TOGGLE_SETTLE_MS    0   // 切换通道后的可选稳定延时（多数情况可为0）
#endif

/* === 全局实时量（单写多读，不加锁）=== */
volatile float g_adc_v_adc  = 0.0f;
volatile float g_adc_a_adc  = 0.0f;
volatile float g_adc_v_disp = 0.0f;
volatile float g_adc_a_disp = 0.0f;
volatile float g_adc_w_disp = 0.0f;
volatile TickType_t g_adc_ts_v = 0;
volatile TickType_t g_adc_ts_a = 0;

/* === 映射系数（默认值：按你给的拟合线）=== */
/* 电压(显示) = VOL_K * ADC读出值 + VOL_B ；这里“ADC读出值”就是 sd6500_get_val 返回的 fval */
static float VOL_K = 20.354f;
static float VOL_B = 0.0078f;

/* 电流通道给占位：你自己按标定填；没有就临时 1:1 */
static float AMP_K = 2.6435f;
static float AMP_B = 0.0059f;

void ADC_SetScale(float vol_k, float vol_b, float amp_k, float amp_b)
{
    VOL_K = vol_k; VOL_B = vol_b;
    AMP_K = amp_k; AMP_B = amp_b;
}

void ADC_GetSnapshot(adc_snapshot_t *out)
{
    if (!out) return;
    /* 单写多读的简单快照：先拷贝到局部再回填，避免半更新 */
    float v_adc  = g_adc_v_adc;
    float a_adc  = g_adc_a_adc;
    float v_disp = g_adc_v_disp;
    float a_disp = g_adc_a_disp;
    float w_disp = g_adc_w_disp;
    TickType_t tv = g_adc_ts_v;
    TickType_t ta = g_adc_ts_a;

    out->v_adc = v_adc; out->a_adc = a_adc;
    out->v_disp = v_disp; out->a_disp = a_disp; out->w_disp = w_disp;
    out->ts_v = tv; out->ts_a = ta;
}

/* === 最新值（单写多读，不加锁）=== */
static volatile float      s_last_vol = 0.0f, s_last_amp = 0.0f;
static volatile TickType_t s_ts_vol   = 0,    s_ts_amp   = 0;
/* 可选：暴露一个快照接口，GUI/控制随时拉 */
void SD6500_GetLatest(float *v_vol, float *v_amp,
                      TickType_t *ts_vol, TickType_t *ts_amp)
{
    if (v_vol) *v_vol = s_last_vol;
    if (v_amp) *v_amp = s_last_amp;
    if (ts_vol) *ts_vol = s_ts_vol;
    if (ts_amp) *ts_amp = s_ts_amp;
}

/* 统计错误，便于调试/看门狗策略 */
static uint32_t s_no_ready_cnt = 0;  // 连续未就绪计数
static uint32_t s_io_err_cnt   = 0;  // 读失败计数

int SD6500_BringUp(void)
{   
    g_i2c_sd.clk.initFlag = 1;
    g_i2c_sd.sda.initFlag = 1;
   return  sd6500_init(&g_sd, &g_i2c_sd);
}




#include <math.h>


void ui_update_real_labels(void)
{
    static float last_v= -999, last_a= -999, last_w= -999;
    static uint32_t last_ms = 0;
    const float DV = 0.01f;   // 10mV 变化再刷
    const float DA = 0.001f;  // 1mA  变化再刷
    const float DW = 0.01f;   // 10mW 变化再刷
    const uint32_t MAX_QUIET_MS = 200; // 至少 200ms 刷一次以防“卡住不动”

    adc_snapshot_t s; ADC_GetSnapshot(&s);
    uint32_t now = HAL_GetTick();
    bool need = false;

    if (fabsf(s.v_disp - last_v) >= DV) need = true;
    if (fabsf(s.a_disp - last_a) >= DA) need = true;
    if (fabsf(s.w_disp - last_w) >= DW) need = true;
    if (!need && (now - last_ms) >= MAX_QUIET_MS) need = true;

    if (!need) return;

    // —— 用“整数拼接”避免浮点打印乱码 & 统一宽度（前导零）——
    int vi = (int)lroundf(s.v_disp * 100.0f);
    int ai = (int)lroundf(s.a_disp * 1000.0f);
    int wi = (int)lroundf(s.w_disp * 100.0f);
    unsigned V = vi<0? -vi:vi, A = ai<0? -ai:ai, W = wi<0? -wi:wi;

//带有负数的符号
//    lv_label_set_text_fmt(guider_ui.screen_RealVal_V, "%s%02u.%02u",
//                          vi<0?"-":"", V/100, V%100);
//    lv_label_set_text_fmt(guider_ui.screen_RealVal_A, "%s%01u.%03u",
//                          ai<0?"-":"", A/1000, A%1000);
//    lv_label_set_text_fmt(guider_ui.screen_RealVal_W, "%s%02u.%02u",
//                          wi<0?"-":"", W/100, W%100);

    lv_label_set_text_fmt(guider_ui.screen_RealVal_V, "%02u.%02u",
                           V/100, V%100);
    lv_label_set_text_fmt(guider_ui.screen_RealVal_A, "%01u.%03u",
                           A/1000, A%1000);
    lv_label_set_text_fmt(guider_ui.screen_RealVal_W, "%02u.%02u",
                           W/100, W%100);





    last_v = s.v_disp; last_a = s.a_disp; last_w = s.w_disp;
    last_ms = now;
}

void SD6500_Task(void *argument)
{
    (void)argument;

    if (SD6500_BringUp() != 0) {
        // 可加重试或报错
    }

    const TickType_t T_ON  = pdMS_TO_TICKS(40);   // 开输出时 25Hz 左右
    const TickType_t T_OFF = pdMS_TO_TICKS(200);  // 关输出时 5Hz 慢速巡检
    TickType_t last_wake = xTaskGetTickCount();
    bool last_on = false;

    for (;;) {
        bool on = power_get_output();  // 别依赖 UI 变量，直接问电源模块
        if (!on) {
            // 关输出：不采样（或偶尔采一次），让出 CPU
            vTaskDelayUntil(&last_wake, T_OFF);
            last_on = false;
            continue;
        }

        // Rising edge：刚打开时可做一次复位/切通道
        if (!last_on) {
            (void)sd6500_toggle_mux(&g_sd);  // 可选
            last_on = true;
        }

        // 等就绪（最多等几 ms），避免空读 + 忙等
        if (sd6500_wait_ready_poll(&g_sd, SD6500_READY_TIMEOUT_MS) == 0) {
            uint8_t who = 0;
            float   val = 0.0f;
            if (sd6500_get_val(&g_sd, &who, &val) == 0) {
                if (who == SD6500_SEL_VOL) {
                    g_adc_v_adc  = val;
                    g_adc_v_disp = VOL_K * (val + 0.0029463f) + VOL_B; // 你的补偿保留
                    g_adc_ts_v   = xTaskGetTickCount();
                } else if (who == SD6500_SEL_AMP) {
                    g_adc_a_adc  = val;
                    g_adc_a_disp = AMP_K * (val + 0.0043f) + AMP_B;
                    g_adc_ts_a   = xTaskGetTickCount();
                    g_adc_w_disp = g_adc_v_disp * g_adc_a_disp;        // 最新功率
                }
                s_no_ready_cnt = 0;
            } else {
                s_io_err_cnt++;
            }
            (void)sd6500_toggle_mux(&g_sd);   // 交替两路
        } else {
            s_no_ready_cnt++;  // 这次没就绪，跳过
        }

        // 固定节拍（关键！否则就抖）
        vTaskDelayUntil(&last_wake, T_ON);
    }
}



