#ifndef _LISTOUT_SCPI_H_
#define _LISTOUT_SCPI_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scpi/scpi.h"
#include "scpi-def.h"

scpi_result_t Cmd_Set_ListTemp_Type(scpi_t *context);
scpi_result_t Cmd_Read_ListTemp_Type(scpi_t *context);

scpi_result_t Cmd_Set_ListTemp_Obj(scpi_t *context);
scpi_result_t Cmd_Read_ListTemp_Obj(scpi_t *context);

scpi_result_t Cmd_Set_ListTemp_Start(scpi_t *context);
scpi_result_t Cmd_Read_ListTemp_Start(scpi_t *context);

scpi_result_t Cmd_Set_ListTemp_Count(scpi_t *context);
scpi_result_t Cmd_Read_ListTemp_Count(scpi_t *context);

scpi_result_t Cmd_Set_ListTemp_MaxValue(scpi_t *context);
scpi_result_t Cmd_Read_ListTemp_MaxValue(scpi_t *context);

scpi_result_t Cmd_Set_ListTemp_MinValue(scpi_t *context);
scpi_result_t Cmd_Read_ListTemp_MinValue(scpi_t *context);

scpi_result_t Cmd_Set_ListTemp_Interval(scpi_t *context);
scpi_result_t Cmd_Read_ListTemp_Interval(scpi_t *context);

scpi_result_t Cmd_Set_ListTemp_Invert(scpi_t *context);
scpi_result_t Cmd_Read_ListTemp_Invert(scpi_t *context);

scpi_result_t Cmd_Set_ListTemp_Period(scpi_t *context);
scpi_result_t Cmd_Read_ListTemp_Period(scpi_t *context);

scpi_result_t Cmd_Set_ListTemp_Width(scpi_t *context);
scpi_result_t Cmd_Read_ListTemp_Width(scpi_t *context);

scpi_result_t Cmd_Set_ListTemp_Symmetry(scpi_t *context);
scpi_result_t Cmd_Read_ListTemp_Symmetry(scpi_t *context);

scpi_result_t Cmd_Set_ListTemp_ExpValue(scpi_t *context);
scpi_result_t Cmd_Read_ListTemp_ExpValue(scpi_t *context);

scpi_result_t Cmd_ListTemp_Generate(scpi_t *context);


scpi_result_t Cmd_Set_List_State(scpi_t *context);
scpi_result_t Cmd_Read_List_State(scpi_t *context);

scpi_result_t Cmd_Set_List_Base(scpi_t *context);
scpi_result_t Cmd_Read_List_Base(scpi_t *context);

scpi_result_t Cmd_Set_List_PointParam(scpi_t *context);
scpi_result_t Cmd_Read_List_PointParam(scpi_t *context);

scpi_result_t Cmd_Read_List_FileName(scpi_t *context);
#endif