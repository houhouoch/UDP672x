#ifndef _TRIGGER_SCPI_H_
#define _TRIGGER_SCPI_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scpi/scpi.h"
#include "scpi-def.h"

/* -------------------- 输入模式配置 -------------------- */
scpi_result_t Cmd_Set_Trigger_In_Enable(scpi_t *context);
scpi_result_t Cmd_Read_Trigger_In_Enable(scpi_t *context);
//受控源
scpi_result_t Cmd_Set_Trigger_In_Source(scpi_t *context);
scpi_result_t Cmd_Read_Trigger_In_Source(scpi_t *context);
//输入信号类型
scpi_result_t Cmd_Set_Trigger_In_Type(scpi_t *context);
scpi_result_t Cmd_Read_Trigger_In_Type(scpi_t *context);
//灵敏度
scpi_result_t Cmd_Set_Trigger_In_Sensitivity(scpi_t *context);
scpi_result_t Cmd_Read_Trigger_In_Sensitivity(scpi_t *context);
//响应
scpi_result_t Cmd_Set_Trigger_In_Response(scpi_t *context);
scpi_result_t Cmd_Read_Trigger_In_Response(scpi_t *context);

/* -------------------- 输出模式配置 -------------------- */
scpi_result_t Cmd_Set_Trigger_Out_Enable(scpi_t *context);
scpi_result_t Cmd_Read_Trigger_Out_Enable(scpi_t *context);
//触发源
scpi_result_t Cmd_Set_Trigger_Out_Source(scpi_t *context);
scpi_result_t Cmd_Read_Trigger_Out_Source(scpi_t *context);
//触发条件
scpi_result_t Cmd_Set_Trigger_Out_Condition(scpi_t *context);
scpi_result_t Cmd_Read_Trigger_Out_Condition(scpi_t *context);
//输出极性
scpi_result_t Cmd_Set_Trigger_Out_Polarity(scpi_t *context);
scpi_result_t Cmd_Read_Trigger_Out_Polarity(scpi_t *context);
#endif
