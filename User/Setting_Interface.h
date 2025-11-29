#ifndef _SETTING_INTERFACE_H_
#define _SETTING_INTERFACE_H_

#include <stdint.h>
#include "Commd.h"
#include "main.h"
#include "SettingData.h"
#include "SettingPage.h"

#include "Task_Manager.h"

//获取AC电源状态
uint8_t IF_System_Get_AC_Power_Fault(void);
void IF_System_Set_AC_Power_Fault(uint8_t status);

//波特率
void IF_System_Set_BaudRate(uint32_t baudRate);
int32_t IF_System_Get_BaudRate(void);
void UI_IF_System_Set_BaudRate(uint32_t baudRate);

void IF_System_Set_Potrcol(uint8_t protocol);
uint8_t IF_System_Get_Potrcol(void);
void UI_IF_System_Set_Potrcol(uint8_t protocol);

void IF_System_Set_Potrcol_Address(uint8_t address);
uint8_t IF_System_Get_Potrcol_Address(void);
void UI_IF_System_Set_Potrcol_Address(uint8_t address);

//背光
void IF_System_Brightness_Set(uint8_t light);
uint8_t IF_System_LCD_Light_Get(void);
void UI_IF_System_Brightness_Set(uint8_t light);
//语言
void IF_System_Language_Set(uint8_t language);
void UI_IF_System_Language_Set(uint8_t language);
//蜂鸣器
void IF_System_Beeper_Set(uint8_t connevt);
uint8_t IF_System_Beeper_Get_Onoff(void);
void UI_IF_System_Beeper_Set(uint8_t connevt);

//掉电检测
void IF_System_Set_PowerDown(uint8_t onoff);
uint8_t IF_System_PowerDown_Get_Onoff(void);
void UI_IF_System_Set_PowerDown(uint8_t onoff);

//开机保持P-OUT
void IF_System_POUT_Onoff(uint8_t onoff);
void UI_IF_System_POut_Onoff(uint8_t onoff);

//DVM电压表开关
void IF_System_DVM_Onoff(uint8_t onoff);
void UI_IF_System_DVM_Onoff(uint8_t onoff);

/* ------------------------- DHCP ------------------------- */
//应用LAN设置
void IF_System_LAN_Apply(void);
void UI_IF_System_LAN_Apply(uint8_t flag);

//DHCP
void IF_System_DHCP_Onoff(uint8_t onoff);
uint8_t IF_System_Get_DHCP_Onoff(void);
uint8_t IF_System_Get_DHCP_TMP_Onoff(void);
void UI_IF_System_DHCP_Onoff(uint8_t onoff);

//网络地址
void IF_System_Set_LAN_IP(uint8_t addr0, uint8_t addr1, uint8_t addr2, uint8_t addr3);
void UI_IF_System_Set_LAN_IP(uint8_t addr0, uint8_t addr1, uint8_t addr2, uint8_t addr3);
//网关
void IF_System_Set_LAN_GW(uint8_t addr0, uint8_t addr1, uint8_t addr2, uint8_t addr3);
void UI_IF_System_Set_LAN_GW(uint8_t addr0, uint8_t addr1, uint8_t addr2, uint8_t addr3);
//子网掩码
void IF_System_Set_LAN_NetMask(uint8_t addr0, uint8_t addr1, uint8_t addr2, uint8_t addr3);
void UI_IF_System_Set_LAN_NetMask(uint8_t addr0, uint8_t addr1, uint8_t addr2, uint8_t addr3);

//远程控制
void IF_System_Set_Remote(uint8_t connect);
uint8_t IF_System_Get_Remote(void);
void UI_IF_System_Set_Remote(uint8_t connect);
//USB U盘
void IF_System_USB_Disk_Connect(uint8_t connect);
void UI_IF_System_USB_Disk_Connect(uint8_t connect);
//USB Device
void IF_System_USB_Device_Connect(uint8_t connect);
void UI_IF_System_USB_Device_Connect(uint8_t connect);
//LAN
void IF_System_LAN_Connect(uint8_t connevt);
void UI_IF_System_LAN_Connect(uint8_t connevt);
//截图
void IF_System_ScreenShot(void);
void UI_IF_System_ScreenShot(void);

//校准模式
void IF_System_Set_CalibMode(uint8_t enable);
void UI_IF_System_Set_CalibMode(uint8_t enable);


#endif
