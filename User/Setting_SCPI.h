#ifndef _SETTING_SCPI_H_
#define _SETTING_SCPI_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scpi/scpi.h"
#include "scpi-def.h"

//提示音
scpi_result_t Cmd_Set_Beeper(scpi_t *context);
scpi_result_t Cmd_Read_Beeper(scpi_t *context);
scpi_result_t Cmd_System_Beeper(scpi_t *context);

//掉电检测
scpi_result_t Cmd_Set_PowerDown(scpi_t *context);
scpi_result_t Cmd_Read_PowerDown(scpi_t *context);

//屏幕背光
scpi_result_t Cmd_Set_Brightness(scpi_t *context);
scpi_result_t Cmd_Read_Brightness(scpi_t *context);

//RS232波特率
scpi_result_t Cmd_Set_COM_BaudRate(scpi_t *context);
scpi_result_t Cmd_Read_COM_BaudRate(scpi_t *context);
#if 1
    //通讯协议
    scpi_result_t Cmd_Set_COM_Protocol(scpi_t *context);
    scpi_result_t Cmd_Read_COM_Protocol(scpi_t *context);
    //通讯地址
    scpi_result_t Cmd_Set_COM_Protocol_Address(scpi_t *context);
    scpi_result_t Cmd_Read_COM_Protocol_Address(scpi_t *context);
#endif

//应用LAN设置
scpi_result_t Cmd_Set_LAN_Apply(scpi_t *context);
//DHCP
scpi_result_t Cmd_Set_LAN_DHCP(scpi_t *context);
scpi_result_t Cmd_Read_LAN_DHCP(scpi_t *context);
//IP地址
scpi_result_t Cmd_Set_LAN_IP(scpi_t *context);
scpi_result_t Cmd_Read_LAN_IP(scpi_t *context);
//网关
scpi_result_t Cmd_Set_LAN_GateWay(scpi_t *context);
scpi_result_t Cmd_Read_LAN_GateWay(scpi_t *context);
//子网掩码
scpi_result_t Cmd_Set_LAN_NetMask(scpi_t *context);
scpi_result_t Cmd_Read_LAN_NetMask(scpi_t *context);

//远程控制模式
scpi_result_t Cmd_Set_System_Remote_Mode(scpi_t *context);
scpi_result_t Cmd_Set_System_Local_Mode(scpi_t *context);
//上锁
scpi_result_t Cmd_Set_System_Lock(scpi_t *context);
scpi_result_t Cmd_Set_System_UnLock(scpi_t *context);
#endif
