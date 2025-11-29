#ifndef _TRIGGER_INTERFACE_H_
#define _TRIGGER_INTERFACE_H_

#include <stdint.h>
#include "Commd.h"
#include "main.h"

#include "Task_Manager.h"
#include "TriggerPage.h"

void UI_IF_Trigger_Set_Mode(int8_t ch, int8_t mode);
/* -------------------- 输入模式配置 -------------------- */
void UI_IF_Trigger_Set_In_Source(int8_t ch, int8_t source);
void UI_IF_Trigger_Set_In_Type(int8_t ch, int8_t type);
void UI_IF_Trigger_Set_In_Sens(int8_t ch, int8_t Sens);
void UI_IF_Trigger_Set_In_Response(int8_t ch, int8_t response);

/* -------------------- 输出模式配置 -------------------- */
void UI_IF_Trigger_Set_Out_Source(int8_t ch, int8_t source);
void UI_IF_Trigger_Set_Out_Condition(int8_t ch, int8_t condition);
void UI_IF_Trigger_Set_Out_Condition_Val(int8_t ch, float value);
void UI_IF_Trigger_Set_Out_Polarity(int8_t ch, int8_t polarity);




void IF_Trigger_Set_Mode(int8_t ch, int8_t mode);
/* -------------------- 输入模式配置 -------------------- */
void IF_Trigger_Set_In_Source(int8_t ch, int8_t source);
void IF_Trigger_Set_In_Type(int8_t ch, int8_t type);
void IF_Trigger_Set_In_Sens(int8_t ch, int8_t Sens);
void IF_Trigger_Set_In_Response(int8_t ch, int8_t response);

/* -------------------- 输出模式配置 -------------------- */
void IF_Trigger_Set_Out_Source(int8_t ch, int8_t source);
void IF_Trigger_Set_Out_Condition(int8_t ch, int8_t condition);
void IF_Trigger_Set_Out_Condition_Val(int8_t ch, float value);
void IF_Trigger_Set_Out_Polarity(int8_t ch, int8_t polarity);

#endif
