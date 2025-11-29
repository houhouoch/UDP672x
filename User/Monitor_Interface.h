#ifndef _MONITOR_INTERFACE_H_
#define _MONITOR_INTERFACE_H_

#include <stdint.h>
#include "Commd.h"
#include "main.h"
#include "SettingData.h"

#include "Task_Manager.h"

void IF_Monitor_Set_Vol(uint8_t monitor, float value);
void UI_IF_Monitor_Set_Vol(uint8_t monitor, float value);

void IF_Monitor_Set_Amp(uint8_t monitor, float value);
void UI_IF_Monitor_Set_Amp(uint8_t monitor, float value);

void IF_Monitor_Set_Wat(uint8_t monitor, float value);
void UI_IF_Monitor_Set_Wat(uint8_t monitor, float value);

void IF_Monitor_Set_Dvm(uint8_t monitor, float value);
void UI_IF_Monitor_Set_Dvm(uint8_t monitor, float value);

void IF_Monitor_Set_Logic(uint8_t num, uint8_t logic);
void UI_IF_Monitor_Set_Logic(uint8_t num, uint8_t logic);


void IF_Monitor_Set_Sensitivity(uint8_t sensitivity);
void UI_IF_Monitor_Set_Sensitivity(uint8_t sensitivity);

void IF_Monitor_Set_PowerOFF(uint8_t powerOFF);
void UI_IF_Monitor_Set_PowerOFF(uint8_t powerOFF);

void IF_Monitor_Set_Tips(uint8_t tips);
void UI_IF_Monitor_Set_Tips(uint8_t tips);

void IF_Monitor_Set_Beep(uint8_t beep);
void UI_IF_Monitor_Set_Beep(uint8_t beep);

uint8_t IF_Monitor_Get_ON_OFF(void);
void IF_Monitor_Set_ON_OFF(uint8_t onoff);
void UI_IF_Monitor_Set_ON_OFF(uint8_t onoff);

#endif
