#ifndef _ADC_TASK_H
#define _ADC_TASK_H



#include "cmsis_os.h"

/* === 实时全局（单写多读）=== */
extern volatile float g_adc_v_adc;   // ADC端电压（SD6500换算后的电压单位，未做整机拟合）
extern volatile float g_adc_a_adc;   // ADC端电流对应电压（同上）
extern volatile float g_adc_v_disp;  // 显示用电压（已按拟合/比例映射）
extern volatile float g_adc_a_disp;  // 显示用电流
extern volatile float g_adc_w_disp;  // 显示用功率
extern volatile TickType_t g_adc_ts_v;
extern volatile TickType_t g_adc_ts_a;

/* 拟合/比例系数设置 */
void ADC_SetScale(float vol_k, float vol_b, float amp_k, float amp_b);

/* 快照读取（一次性取全，防止你读到半更新）*/
typedef struct {
    float v_adc, a_adc;
    float v_disp, a_disp, w_disp;
    TickType_t ts_v, ts_a;
} adc_snapshot_t;


void ADC_GetSnapshot(adc_snapshot_t *out);

void SD6500_Task(void *argument);


#endif