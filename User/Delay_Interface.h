#ifndef _DELAY_INTERFACE_H_
#define _DELAY_INTERFACE_H_

#include <stdint.h>
#include "Commd.h"
#include "main.h"
#include "SettingData.h"

#include "Task_Manager.h"
#include "DelayOutPage.h"
#include "DelayOut.h"
#include "Interface.h"

void IF_Delay_Set_On_Off(uint8_t onoff);
void IF_Delay_Set_Start(int32_t start);
void IF_Delay_Set_Count(int32_t count);
void IF_Delay_Set_Cycle(int32_t cycle);
void IF_Delay_Set_Stop(int8_t stop);
void IF_Delay_Set_StopValue(float value);
void IF_Delay_Set_lastState(int8_t laststate);
void IF_Delay_Set_PointParam(int32_t idx, uint8_t onoff, float time);


void IF_Delay_Refresh_RemainTime(void);
/*
 * @brief       void IF_DelayOut_Set_CurIdx(uint16_t value)
 * @details     DelayOut显示当前位置
 */
void IF_DelayOut_Set_CurIdx(uint16_t value);
/*
 * @brief       void IF_DelayOut_Set_Loop(uint16_t value)
 * @details     DelayOut显示已循环次数
 */
void IF_DelayOut_Set_Loop(uint16_t value);
/*
 * @brief       void IF_DelayOut_Set_State(uint16_t value)
 * @details     DelayOut设置当前状态
 */
void IF_DelayOut_Set_State(uint16_t value);



void UI_IF_Delay_Set_On_Off(uint8_t onoff);
void UI_IF_Delay_Set_Start(int32_t start);
void UI_IF_Delay_Set_Count(int32_t count);
void UI_IF_Delay_Set_Cycle(int32_t cycle);
void UI_IF_Delay_Set_Stop(int8_t stop);
void UI_IF_Delay_Set_StopValue(float value);
void UI_IF_Delay_Set_lastState(int8_t laststate);
void UI_IF_Delay_Set_PointParam(int32_t idx, uint8_t onoff, float time);

void UI_IF_Delay_Refresh_RemainTime(void);
void UI_IF_Delay_Set_CurIdx(uint16_t value);
void UI_IF_Delay_Set_Loop(uint16_t value);
void UI_IF_Delay_Set_State(uint16_t value);

#endif
