#ifndef POWER_CTRL_H
#define POWER_CTRL_H

#include <stdint.h>
#include <stdbool.h>
#include "tim.h"

#ifdef __cplusplus
extern "C" {
#endif

/* -------- 绑定到实际的 PWM 定时器/通道 -------- */
#ifndef POW_PWM_TIM
#define POW_PWM_TIM        htim1
#endif
#ifndef POW_PWM_CH_CUR
#define POW_PWM_CH_CUR     TIM_CHANNEL_1    /* 电流PWM */
#endif
#ifndef POW_PWM_CH_VOL
#define POW_PWM_CH_VOL     TIM_CHANNEL_2    /* 电压PWM */
#endif

/* -------- 线性映射与爬升参数 -------- */
#ifndef POW_PWM_MAX_CCR
#define POW_PWM_MAX_CCR          60000      /* 你的 ARR≈60000 */
#endif
#ifndef VOL_PWM_COUNTS_PER_V
#define VOL_PWM_COUNTS_PER_V     1000       /* 1V -> 1000 计数 */
#endif
#ifndef VOL_RAMP_STEP_COUNTS
#define VOL_RAMP_STEP_COUNTS     4000        /* 每 20ms 走 400 计数 */
#endif

#ifndef CUR_PWM_COUNTS_PER_A
#define CUR_PWM_COUNTS_PER_A     7502.92         /* 1A -> 1000 计数 */
#endif

/* 给电流单独一套（可与电压不同步速），不定义就沿用上面那组 */
#ifndef CUR_MIN_STEP_COUNTS
#define CUR_MIN_STEP_COUNTS   MIN_STEP_COUNTS
#endif
#ifndef CUR_MAX_STEP_COUNTS
#define CUR_MAX_STEP_COUNTS   MAX_STEP_COUNTS
#endif
#ifndef CUR_STEP_DIV
#define CUR_STEP_DIV          STEP_DIV
#endif


/* ===== 自适应步长参数 ===== */
/* 距离越大，step = diff / STEP_DIV 越大；再夹在 [MIN, MAX] 内 */
#define MIN_STEP_COUNTS   10      /* 离得很近也别小于这个 */
#define MAX_STEP_COUNTS   8000    /* 限一个上限，防止猛冲，按你PWM分辨率改 */
#define STEP_DIV          2      /* 越小越快：4更快、8更慢 */


/* ===== API ===== */
void power_init(void);
void power_tick_20ms(void);

void power_set_output(bool on);
bool power_get_output(void);

uint16_t power_get_pwm_vol(void);
uint16_t power_get_pwm_cur(void);

/* 线性映射：CCR = counts_per_volt * V + offset_counts;
   如果 inverted=true 则 CCR = ARR - CCR */
void power_set_linear_map(float counts_per_volt, float offset_counts, bool inverted);

void power_update_cc_cv_leds(void);
/* 从 UI 标签读取电压，更新全局记录（不直接写PWM） */
void power_apply_voltage_from_label(void);

/* 硬件抽象（如需强定义，自己在别处实现） */
void __attribute__((weak)) power_hw_out_enable(bool en);
bool __attribute__((weak)) power_hw_read_sense_fail(void);
bool __attribute__((weak)) power_hw_read_otp(void);
bool __attribute__((weak)) power_hw_read_cc_pin(void);
#ifdef __cplusplus
}
#endif
#endif /* POWER_CTRL_H */
