#ifndef _DELAY_TEMP_INTERFACE_H_
#define _DELAY_TEMP_INTERFACE_H_

#include <stdint.h>
#include "Commd.h"
#include "main.h"
#include "SettingData.h"

#include "Task_Manager.h"
#include "DelayTempPage.h"


void IF_DelayTemp_Set_Type(int8_t temp_type);
void IF_DelayTemp_Set_Code(int8_t code);
void IF_DelayTemp_Set_Start(int16_t start);
void IF_DelayTemp_Set_Count(int16_t count);
void IF_DelayTemp_Set_Ton(float Ton);
void IF_DelayTemp_Set_Toff(float Toff);
void IF_DelayTemp_Set_Base(float baseT);
void IF_DelayTemp_Set_Step(float stepT);
void IF_DelayTemp_Generate(void);

void UI_IF_DelayTemp_Set_Type(int8_t temp_type);
void UI_IF_DelayTemp_Set_Code(int8_t code);
void UI_IF_DelayTemp_Set_Start(int16_t start);
void UI_IF_DelayTemp_Set_Count(int16_t count);
void UI_IF_DelayTemp_Set_Ton(float Ton);
void UI_IF_DelayTemp_Set_Toff(float Toff);
void UI_IF_DelayTemp_Set_Base(float baseT);
void UI_IF_DelayTemp_Set_Step(float stepT);
void UI_IF_DelayTemp_Generate(void);

#endif
