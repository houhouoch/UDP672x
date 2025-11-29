#ifndef _BATTESTER_SCPI_H_
#define _BATTESTER_SCPI_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scpi/scpi.h"
#include "scpi-def.h"


scpi_result_t Cmd_Set_BatTester_State(scpi_t *context);
scpi_result_t Cmd_Read_BatTester_State(scpi_t *context);

scpi_result_t Cmd_Set_BatTester_Base(scpi_t *context);
scpi_result_t Cmd_Read_BatTester_Base(scpi_t *context);

scpi_result_t Cmd_Set_BatTester_PointParam(scpi_t *context);
scpi_result_t Cmd_Read_BatTester_PointParam(scpi_t *context);


scpi_result_t Cmd_Set_BatTester_Gobal_Protect(scpi_t *context);
scpi_result_t Cmd_Read_BatTester_Gobal_Protect(scpi_t *context);
scpi_result_t Cmd_Set_BatTester_Group_Protect(scpi_t *context);
scpi_result_t Cmd_Read_BatTester_Group_Protect(scpi_t *context);
scpi_result_t Cmd_Set_BatTester_TrigTime(scpi_t *context);
scpi_result_t Cmd_Read_BatTester_TrigTime(scpi_t *context);

scpi_result_t Cmd_Read_BatTester_FileName(scpi_t *context);
#endif