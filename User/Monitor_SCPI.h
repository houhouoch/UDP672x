#ifndef _MONITOR_SCPI_H_
#define _MONITOR_SCPI_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scpi/scpi.h"
#include "scpi-def.h"

scpi_result_t Cmd_Set_Monitor_State(scpi_t *context);
scpi_result_t Cmd_Read_Monitor_State(scpi_t *context);

scpi_result_t Cmd_Set_Monitor_Vol(scpi_t *context);
scpi_result_t Cmd_Read_Monitor_Vol(scpi_t *context);

scpi_result_t Cmd_Set_Monitor_Amp(scpi_t *context);
scpi_result_t Cmd_Read_Monitor_Amp(scpi_t *context);

scpi_result_t Cmd_Set_Monitor_Wat(scpi_t *context);
scpi_result_t Cmd_Read_Monitor_Wat(scpi_t *context);

scpi_result_t Cmd_Set_Monitor_Dvm(scpi_t *context);
scpi_result_t Cmd_Read_Monitor_Dvm(scpi_t *context);

scpi_result_t Cmd_Set_Monitor_Logic(scpi_t *context);
scpi_result_t Cmd_Read_Monitor_Logic(scpi_t *context);

scpi_result_t Cmd_Set_Monitor_StopWay(scpi_t *context);
scpi_result_t Cmd_Read_Monitor_StopWay(scpi_t *context);

#endif
