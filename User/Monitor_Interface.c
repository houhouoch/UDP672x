#include "Monitor_Interface.h"


void IF_Monitor_Set_Vol(uint8_t monitor, float value)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_MONITOR_SET_VOL;
    msg.data.monitor_param.data_u8 = monitor;
    msg.data.monitor_param.data_float = value;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}

void UI_IF_Monitor_Set_Vol(uint8_t monitor, float value)
{
    systemInfo.monitor.vol = value;
    systemInfo.monitor.vol_monitor = monitor;
    lv_event_send_refresh(ui.Monitor_btn_LogicV_label);
    eeprom_Monitor_RequestSave(0);
}



void IF_Monitor_Set_Amp(uint8_t monitor, float value)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_MONITOR_SET_AMP;
    msg.data.monitor_param.data_u8 = monitor;
    msg.data.monitor_param.data_float = value;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}

void UI_IF_Monitor_Set_Amp(uint8_t monitor, float value)
{
    systemInfo.monitor.amp = value;
    systemInfo.monitor.amp_monitor = monitor;
    lv_event_send_refresh(ui.Monitor_btn_LogicA_label);
    eeprom_Monitor_RequestSave(0);
}



void IF_Monitor_Set_Wat(uint8_t monitor, float value)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_MONITOR_SET_WAT;
    msg.data.monitor_param.data_u8 = monitor;
    msg.data.monitor_param.data_float = value;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}

void UI_IF_Monitor_Set_Wat(uint8_t monitor, float value)
{
    systemInfo.monitor.wat = value;
    systemInfo.monitor.wat_monitor = monitor;
    lv_event_send_refresh(ui.Monitor_btn_LogicW_label);
    eeprom_Monitor_RequestSave(0);
}



void IF_Monitor_Set_Dvm(uint8_t monitor, float value)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_MONITOR_SET_DVM;
    msg.data.monitor_param.data_u8 = monitor;
    msg.data.monitor_param.data_float = value;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}

void UI_IF_Monitor_Set_Dvm(uint8_t monitor, float value)
{
    systemInfo.monitor.dvm = value;
    systemInfo.monitor.dvm_monitor = monitor;
    lv_event_send_refresh(ui.Monitor_btn_LogicDvm_label);
    eeprom_Monitor_RequestSave(0);
}





void IF_Monitor_Set_Logic(uint8_t num, uint8_t logic)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_MONITOR_SET_LOGIC;
    msg.data.monitor_param.num = num;
    msg.data.monitor_param.data_u8 = logic;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}

void UI_IF_Monitor_Set_Logic(uint8_t num, uint8_t logic)
{
    if(num > (ARRAY_COUNT(systemInfo.monitor.logic) - 1))
    {
        return ;
    }
    systemInfo.monitor.logic[num] = logic;
    lv_event_send_refresh(ui.Monitor_btn_Logic_label);
    eeprom_Monitor_RequestSave(0);
}



void IF_Monitor_Set_Sensitivity(uint8_t sensitivity)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_MONITOR_SET_SENSITIVITY;
    msg.data.monitor_param.data_u8 = sensitivity;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
void UI_IF_Monitor_Set_Sensitivity(uint8_t sensitivity)
{
    systemInfo.monitor.sensitivity = sensitivity;
    lv_event_send_refresh(ui.Monitor_btn_sensitivity_label);
    eeprom_Monitor_RequestSave(0);
}


void IF_Monitor_Set_PowerOFF(uint8_t powerOFF)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_MONITOR_SET_ACTION;
    msg.data.monitor_param.data_u8 = powerOFF;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
void UI_IF_Monitor_Set_PowerOFF(uint8_t powerOFF)
{
    systemInfo.monitor.powerOFF = powerOFF;
    lv_event_send_refresh(ui.Monitor_btn_PowerOFF_label);
    eeprom_Monitor_RequestSave(0);
}


void IF_Monitor_Set_Tips(uint8_t tips)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_MONITOR_SET_TIPS;
    msg.data.monitor_param.data_u8 = tips;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
void UI_IF_Monitor_Set_Tips(uint8_t tips)
{
    systemInfo.monitor.tips = tips;
    lv_event_send_refresh(ui.Monitor_btn_Tips_label);
    eeprom_Monitor_RequestSave(0);
}


void IF_Monitor_Set_Beep(uint8_t beep)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_MONITOR_SET_BEEP;
    msg.data.monitor_param.data_u8 = beep;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
void UI_IF_Monitor_Set_Beep(uint8_t beep)
{
    systemInfo.monitor.beep = beep;
    lv_event_send_refresh(ui.Monitor_btn_beep_label);
    eeprom_Monitor_RequestSave(0);
}


uint8_t IF_Monitor_Get_ON_OFF(void)
{
    return systemInfo.monitor.enable;
}
void IF_Monitor_Set_ON_OFF(uint8_t onoff)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_MONITOR_SET_ONOFF;
    msg.data.monitor_param.data_u8 = onoff;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
void UI_IF_Monitor_Set_ON_OFF(uint8_t onoff)
{
    systemInfo.monitor.enable = onoff;
    lv_obj_set_hidden(ui.Bar_icon_Monitor, !onoff);
    eeprom_Monitor_RequestSave(0);
}


