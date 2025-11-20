#include "power_ctrl.h"
#include "main.h"
#include "gui_guider.h"
#include "lvgl.h"
#include <stdlib.h>
#include <stdio.h>

/* 由 Gui_Task.c 导出的全局 UI 句柄 */
extern lv_ui guider_ui;

/* 可选：保留一个全局电压设定值给其它模块看（非必须） */
float OutSetVal_V = 0.0f;
float OutSetVal_A = 0.0f;  

/* —— 线性映射参数 —— */
static float s_counts_per_volt = VOL_PWM_COUNTS_PER_V;
static float s_offset_counts   = 0.0f;
static bool  s_inverted        = false;  /* 若硬件“反向”，设 true：CCR = ARR - 线性值 */

/* 电流映射（缺省与电压相同） */
static float s_counts_per_amp  = CUR_PWM_COUNTS_PER_A;
static float s_offset_counts_a = -75.52;
static bool  s_a_inverted      = false;

/* 可运行时修改映射（电压） */
void power_set_linear_map(float counts_per_volt, float offset_counts, bool inverted)
{
    s_counts_per_volt = counts_per_volt;
    s_offset_counts   = offset_counts;
    s_inverted        = inverted;
}


/* 可运行时修改映射（电流） */
void power_set_linear_map_cur(float counts_per_amp, float offset_counts, bool inverted)
{
    s_counts_per_amp  = counts_per_amp;
    s_offset_counts_a = offset_counts;
    s_a_inverted      = inverted;
}

/* 取定时器自动重装值（ARR） */
static inline uint32_t pwm_get_arr(void)
{
    return __HAL_TIM_GET_AUTORELOAD(&POW_PWM_TIM);
}

static inline uint16_t clamp_u16(int32_t x, uint32_t arr)
{
    if (x < 0) return 0;
    if ((uint32_t)x > arr) return (uint16_t)arr;
    return (uint16_t)x;
}

/* V → CCR 线性换算（可反向） */
static uint16_t volts_to_ccr(float v)
{
    float c = s_counts_per_volt * v + s_offset_counts;
    uint32_t arr = pwm_get_arr();
    if (s_inverted) c = (float)arr - c;
    return clamp_u16((int32_t)(c + 0.5f), arr);
}
/* A → CCR（可反向） */
static uint16_t amps_to_ccr(float a)
{
    float c = s_counts_per_amp * a + s_offset_counts_a;
    uint32_t arr = pwm_get_arr();
    if (s_a_inverted) c = (float)arr - c;
    return clamp_u16((int32_t)(c + 0.5f), arr);
}

/* ========= 从 UI 取设定 ========= */
/* 从标签取电压设定文本→float（空文本或非法返回0）*/
static float read_set_voltage_from_label(void)
{
    const char *txt = lv_label_get_text(guider_ui.screen_OutSetVal_V);
    if (!txt || !*txt) return 0.0f;
    return (float)atof(txt);
}
/* 从标签取电流设定文本→float（空文本或非法返回0）*/
static float read_set_current_from_label(void)
{
    const char *txt = lv_label_get_text(guider_ui.screen_OutSetVal_A);
    if (!txt || !*txt) return 0.0f;
    return (float)atof(txt);
}

/* 只更新全局记录，不直接写 PWM（由心跳统一动作） */
void power_apply_voltage_from_label(void)
{
    float v = read_set_voltage_from_label();
    OutSetVal_V = v;
    printf("V-SET: %.2f\r\n", v);
}
/* 同上：电流 */
void power_apply_current_from_label(void)
{
    float a = read_set_current_from_label();
    OutSetVal_A = a;
    printf("A-SET: %.3f\r\n", a);
}

/* —— 仅保留一个真正有用的输出开关 —— */
static bool s_out_on = false;

void power_init(void)
{
    HAL_TIM_PWM_Start(&POW_PWM_TIM, POW_PWM_CH_CUR);
    HAL_TIM_PWM_Start(&POW_PWM_TIM, POW_PWM_CH_VOL);
  
    __HAL_TIM_SET_COMPARE(&POW_PWM_TIM, POW_PWM_CH_CUR, 0);
    __HAL_TIM_SET_COMPARE(&POW_PWM_TIM, POW_PWM_CH_VOL, 0);

    power_set_linear_map_cur(7502.92f, -75.52f, false);
    s_out_on = false;
    power_hw_out_enable(false);  /* 默认断开 OUT_ONOFF */
}

void power_set_output(bool on)
{
    s_out_on = on;
    power_update_cc_cv_leds();   // 开就判定灯；关就熄灯
}

bool power_get_output(void)
{
    return s_out_on;
}

uint16_t power_get_pwm_vol(void)
{
    return __HAL_TIM_GET_COMPARE(&POW_PWM_TIM, POW_PWM_CH_VOL);
}

uint16_t power_get_pwm_cur(void)
{
    return __HAL_TIM_GET_COMPARE(&POW_PWM_TIM, POW_PWM_CH_CUR);
}


/* ===== 自适应步长 ===== */
static inline uint32_t calc_adaptive_step(uint32_t cur, uint32_t target)
{
    uint32_t diff = (cur > target) ? (cur - target) : (target - cur);
    uint32_t step = diff / STEP_DIV;          /* 误差越大，步子越大 */
    if (step < MIN_STEP_COUNTS) step = MIN_STEP_COUNTS;
    if (step > MAX_STEP_COUNTS) step = MAX_STEP_COUNTS;
    if (step > diff) step = diff;             /* 最后一步不越界 */
    return step;
}



/* 电流通道用独立参数 */
static inline uint32_t calc_adaptive_step_cur(uint32_t cur, uint32_t target)
{
    uint32_t diff = (cur > target) ? (cur - target) : (target - cur);
    uint32_t step = diff / CUR_STEP_DIV;
    if (step < CUR_MIN_STEP_COUNTS) step = CUR_MIN_STEP_COUNTS;
    if (step > CUR_MAX_STEP_COUNTS) step = CUR_MAX_STEP_COUNTS;
    if (step > diff) step = diff;
    return step;
}



/* ===== 20ms 心跳：按目标爬升/回落（电压 + 电流） ===== */
void power_tick_20ms(void)
{
    /* 每20ms读取一次 UI 设定 */
    float set_v = read_set_voltage_from_label();
    if (set_v < 0) set_v = 0;
    /* 你的电压标定保留： */
    set_v = (set_v + 0.041f) / 1.026f;
    if (set_v < 0) set_v = 0;

    float set_a = read_set_current_from_label();
    if (set_a < 0) set_a = 0;
    /* 如需电流标定，这里加： set_a = (set_a + Ia_offset) / Ia_gain; */

    uint32_t target_ccr_vol = volts_to_ccr(set_v);
    uint32_t target_ccr_cur = amps_to_ccr(set_a);
    uint32_t cur_vol        = __HAL_TIM_GET_COMPARE(&POW_PWM_TIM, POW_PWM_CH_VOL);
    uint32_t cur_cur        = __HAL_TIM_GET_COMPARE(&POW_PWM_TIM, POW_PWM_CH_CUR);

    if (!s_out_on) {
        /* 关机：两路都平滑回落到 0，再断开硬件输出 */
        if (cur_vol > 0) {
            uint32_t stepv = calc_adaptive_step(cur_vol, 0);
            __HAL_TIM_SET_COMPARE(&POW_PWM_TIM, POW_PWM_CH_VOL, cur_vol - stepv);
        }
        if (cur_cur > 0) {
            uint32_t stepi = calc_adaptive_step_cur(cur_cur, 0);
            __HAL_TIM_SET_COMPARE(&POW_PWM_TIM, POW_PWM_CH_CUR, cur_cur - stepi);
        }
        if ( (cur_vol == 0) && (cur_cur == 0) ) {
            power_hw_out_enable(false);
        }
        return;
    }

    if (cur_vol != target_ccr_vol) {
    __HAL_TIM_SET_COMPARE(&POW_PWM_TIM, POW_PWM_CH_VOL, target_ccr_vol);
}


    /* 开机：按目标爬/降（电压 + 电流） */
    if (cur_vol != target_ccr_vol) {
        uint32_t stepv = calc_adaptive_step(cur_vol, target_ccr_vol);
        uint32_t nextv = (cur_vol < target_ccr_vol) ? (cur_vol + stepv) : (cur_vol - stepv);
        __HAL_TIM_SET_COMPARE(&POW_PWM_TIM, POW_PWM_CH_VOL, nextv);
    }
    if (cur_cur != target_ccr_cur) {
        uint32_t stepi = calc_adaptive_step_cur(cur_cur, target_ccr_cur);
        uint32_t nexti = (cur_cur < target_ccr_cur) ? (cur_cur + stepi) : (cur_cur - stepi);
        __HAL_TIM_SET_COMPARE(&POW_PWM_TIM, POW_PWM_CH_CUR, nexti);
    }
    
// 马上就开输出  不经过
//     __HAL_TIM_SET_COMPARE(&POW_PWM_TIM, POW_PWM_CH_VOL, target_ccr_vol);
//         __HAL_TIM_SET_COMPARE(&POW_PWM_TIM, POW_PWM_CH_CUR, target_ccr_cur);
   // 只要输出开着就会根据实时状态变灯
      power_update_cc_cv_leds();
}



/* ===== CC/CV 指示封装 ===== */
typedef enum { CCCV_OFF = 0,
                CCCV_CC = 1, 
                CCCV_CV = 2
                } cccv_state_t;
static cccv_state_t s_last_cccv = (cccv_state_t)0xFF;  /* 未初始化态 */

void power_update_cc_cv_leds(void)
{
    cccv_state_t now;

    if (!s_out_on) {
        now = CCCV_OFF;  // 关输出：两灯都灭
    } else {
        /* 约定：power_hw_read_cc_pin() == true 表示 CC 模式 */
        bool cc = power_hw_read_cc_pin();
        now = cc ? CCCV_CC : CCCV_CV;
    }

    if (now == s_last_cccv) return;  // 状态没变，不重复操作/打印

    switch (now) {
    case CCCV_OFF:
        HAL_GPIO_WritePin(LED_CC_GPIO_Port, LED_CC_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_CV_GPIO_Port, LED_CV_Pin, GPIO_PIN_RESET);
        lv_obj_add_flag(guider_ui.screen_CcText, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_CvText, LV_OBJ_FLAG_HIDDEN);
        break;
    case CCCV_CC:
        HAL_GPIO_WritePin(LED_CC_GPIO_Port, LED_CC_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED_CV_GPIO_Port, LED_CV_Pin, GPIO_PIN_RESET);
        lv_obj_clear_flag(guider_ui.screen_CcText, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_CvText, LV_OBJ_FLAG_HIDDEN);
    //    printf("LED_CC_set\r\n");
        break;
    case CCCV_CV:
        HAL_GPIO_WritePin(LED_CC_GPIO_Port, LED_CC_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_CV_GPIO_Port, LED_CV_Pin, GPIO_PIN_SET);
        lv_obj_clear_flag(guider_ui.screen_CvText, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_CcText, LV_OBJ_FLAG_HIDDEN);
       // printf("LED_CV_set\r\n");
        break;
    }

    s_last_cccv = now;
}








/* ===== 硬件抽象（默认实现，可在别处强定义覆盖） ===== */
void __attribute__((weak)) power_hw_out_enable(bool en)
{
    HAL_GPIO_WritePin(OUT_ONOFF_GPIO_Port, OUT_ONOFF_Pin, en ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_ONOFF_GPIO_Port, LED_ONOFF_Pin, en ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

bool __attribute__((weak)) power_hw_read_cc_pin(void)
{
    return (HAL_GPIO_ReadPin(TEST_CC_GPIO_Port, TEST_CC_Pin) == GPIO_PIN_SET);
}
bool __attribute__((weak)) power_hw_read_sense_fail(void)
{
    return (HAL_GPIO_ReadPin(SENSE_GPIO_Port, SENSE_Pin) == GPIO_PIN_RESET);
}

bool __attribute__((weak)) power_hw_read_otp(void)
{
    return (HAL_GPIO_ReadPin(TEST_OTP_GPIO_Port, TEST_OTP_Pin) == GPIO_PIN_RESET);
}
