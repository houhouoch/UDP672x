//无List

#ifndef _BATTERY_TESTER_INTERFACE_H_
#define _BATTERY_TESTER_INTERFACE_H_

#include <stdint.h>
#include "Commd.h"
#include "main.h"
#include "SettingData.h"

#include "Task_Manager.h"
#include "BatTesterPage.h"
#include "BatTester.h"
#include "Interface.h"


void IF_BatTester_Set_Editable(uint8_t editable);
uint8_t IF_BatTester_Get_Editable(void);


void IF_BatTester_Set_On_Off(uint8_t onoff);
void IF_BatTester_Set_Start(int32_t start);
void IF_BatTester_Set_Count(int32_t count);
void IF_BatTester_Set_Cycle(int32_t cycle);
void IF_BatTester_Set_PointParam(int32_t idx, float volt, float curr, float time);


/*
 * @brief       void IF_BatTester_Set(float vol,float amp)
 * @details     BatTester设置输出
 */
void IF_BatTester_Set(float vol, float amp);
void IF_BatTester_Refresh_RemainTime(void);
/*
 * @brief       void IF_BatTester_Set_CurIdx(uint16_t value)
 * @details     BatTester显示当前位置
 */
void IF_BatTester_Set_CurIdx(uint16_t value);
/*
 * @brief       void IF_BatTester_Set_Loop(uint16_t value)
 * @details     BatTester显示已循环次数
 */
void IF_BatTester_Set_Loop(uint16_t value);
/*
 * @brief       void IF_BatTester_Set_State(uint16_t value)
 * @details     BatTester设置当前状态
 */
void IF_BatTester_Set_State(uint16_t value);


void IF_BatTester_Set_Gobal_Protect(uint8_t idx, uint8_t logic, uint8_t stop, float value);
void IF_BatTester_Set_Group_Protect(uint8_t no, uint8_t idx, uint8_t logic, uint8_t stop, float value);


void UI_IF_BatTester_Set_On_Off(uint8_t onoff);
void UI_IF_BatTester_Set_Start(int32_t start);
void UI_IF_BatTester_Set_Count(int32_t count);
void UI_IF_BatTester_Set_Cycle(int32_t cycle);
void UI_IF_BatTester_Set_PointParam(int32_t idx, float volt, float curr, float time);

void UI_IF_BatTester_Refresh_RemainTime(void);
void UI_IF_BatTester_Set_CurIdx(uint16_t value);
void UI_IF_BatTester_Set_Loop(uint16_t value);
void UI_IF_BatTester_Set_State(uint16_t value);


void UI_IF_BatTester_Set_Gobal_Protect(uint8_t idx, uint8_t logic, uint8_t stop, float value);
void UI_IF_BatTester_Set_Group_Protect(uint8_t no, uint8_t idx, uint8_t logic, uint8_t stop, float value);

void IF_BatTester_Set_TrigTime(float time);
float IF_BatTester_Get_TrigTime(void);
#endif
