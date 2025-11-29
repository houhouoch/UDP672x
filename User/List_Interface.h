#ifndef _LIST_INTERFACE_H_
#define _LIST_INTERFACE_H_

#include <stdint.h>
#include "Commd.h"
#include "main.h"
#include "SettingData.h"

#include "Task_Manager.h"
#include "ListPage.h"
#include "ListOut.h"
#include "Interface.h"

void IF_List_Set_On_Off(uint8_t onoff);
void IF_List_Set_Start(int32_t start);
void IF_List_Set_Count(int32_t count);
void IF_List_Set_Cycle(int32_t cycle);
void IF_List_Set_lastState(int8_t laststate);
void IF_List_Set_PointParam(int32_t idx, float volt, float curr, float time);


/*
 * @brief       void IF_ListOut_Set(float vol,float amp)
 * @details     ListOut设置输出
 */
void IF_ListOut_Set(float vol, float amp);
void IF_List_Refresh_RemainTime(void);
/*
 * @brief       void IF_ListOut_Set_CurIdx(uint16_t value)
 * @details     ListOut显示当前位置
 */
void IF_ListOut_Set_CurIdx(uint16_t value);
/*
 * @brief       void IF_ListOut_Set_Loop(uint16_t value)
 * @details     ListOut显示已循环次数
 */
void IF_ListOut_Set_Loop(uint16_t value);
/*
 * @brief       void IF_ListOut_Set_State(uint16_t value)
 * @details     ListOut设置当前状态
 */
void IF_ListOut_Set_State(uint16_t value);



void UI_IF_List_Set_On_Off(uint8_t onoff);
void UI_IF_List_Set_Start(int32_t start);
void UI_IF_List_Set_Count(int32_t count);
void UI_IF_List_Set_Cycle(int32_t cycle);
void UI_IF_List_Set_lastState(int8_t laststate);
void UI_IF_List_Set_PointParam(int32_t idx, float volt, float curr, float time);

void UI_IF_List_Refresh_RemainTime(void);
void UI_IF_List_Set_CurIdx(uint16_t value);
void UI_IF_List_Set_Loop(uint16_t value);
void UI_IF_List_Set_State(uint16_t value);

#endif
