#ifndef _LIST_TEMP_INTERFACE_H_
#define _LIST_TEMP_INTERFACE_H_

#include <stdint.h>
#include "Commd.h"
#include "main.h"
#include "SettingData.h"

#include "Task_Manager.h"
#include "ListTempPage.h"

void IF_ListTemp_Set_Type(int8_t temp_type);
void IF_ListTemp_Set_Object(int8_t object);
void IF_ListTemp_Set_MaxValue(float value);
void IF_ListTemp_Set_MinValue(float value);
void IF_ListTemp_Set_Count(int16_t count);
void IF_ListTemp_Set_Start(int16_t start);
void IF_ListTemp_Set_Interval(float value);
void IF_ListTemp_Set_Invert(uint8_t invert);
void IF_ListTemp_Set_Period(float period);
void IF_ListTemp_Set_Width(float width);
void IF_ListTemp_Set_Symmetry(uint8_t Symmetry);
void IF_ListTemp_Set_expValue(uint8_t value);
void IF_ListTemp_Generate(void);


void UI_IF_ListTemp_Set_Type(int8_t temp_type);
void UI_IF_ListTemp_Set_Object(int8_t object);
void UI_IF_ListTemp_Set_MaxValue(float value);
void UI_IF_ListTemp_Set_MinValue(float value);
void UI_IF_ListTemp_Set_Count(int16_t count);
void UI_IF_ListTemp_Set_Start(int16_t start);
void UI_IF_ListTemp_Set_Interval(float value);
void UI_IF_ListTemp_Set_Invert(uint8_t invert);
void UI_IF_ListTemp_Set_Period(float period);
void UI_IF_ListTemp_Set_Width(float width);
void UI_IF_ListTemp_Set_Symmetry(uint8_t Symmetry);
void UI_IF_ListTemp_Set_expValue(uint8_t value);
void UI_IF_ListTemp_Generate(void);

#endif
