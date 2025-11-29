#include "Setting_Interface.h"

//AC电源状态
uint8_t IF_System_Get_AC_Power_Fault(void)
{
    return systemInfo.status.bits.fault_ACpowerdown;
}

void IF_System_Set_AC_Power_Fault(uint8_t status)
{
    systemInfo.status.bits.fault_ACpowerdown = status;
}


//波特率
#include "usart.h"
#include "mb_user.h"

static void UART_BaudRate_Check(void)
{
    if(huart5.Init.BaudRate != COMM_BAUDR_SET) {
        __HAL_UART_DISABLE(&huart5);
        HAL_UART_DeInit(&huart5);
        huart5.Init.BaudRate = COMM_BAUDR_SET;
        HAL_UART_Init(&huart5);
        __HAL_UART_ENABLE(&huart5);
        //开始接收
        __HAL_UART_ENABLE_IT(&huart5, UART_IT_IDLE);
    }
}


void IF_System_Set_BaudRate(uint32_t baudRate)
{
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_SET_COMM_BAUDRATE;
    msg.data.data_u32 = baudRate;
    CMD_MsgQueue_Send(&msg);
}
int32_t IF_System_Get_BaudRate(void)
{
    return COMM_BAUDR_SET;
}
void UI_IF_System_Set_BaudRate(uint32_t baudRate)
{
    if(baudRate < BAUDR_MIN) {
        IF_MsgBox_Tips_Mult(&mStr_Comm_BaudRate_Min);
        return;
    } else
        if(baudRate > BAUDR_MAX) {
            IF_MsgBox_Tips_Mult(&mStr_Comm_BaudRate_Max);
            return;
        }
    COMM_BAUDR_SET = baudRate;
    UART_BaudRate_Check();
    lv_event_send_refresh(ui.Setting_btn_Comm_BaudRate_label);
    eeprom_Option_RequestSave(0);
    MB_User_Config(COMM_BAUDR_SET, COMM_PROTOL_ADDR_SET);
}


//设置协议类型
void IF_System_Set_Potrcol(uint8_t protocol)
{
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_SET_COMM_PROTOCOL;
    msg.data.data_u8 = protocol;
    CMD_MsgQueue_Send(&msg);
}
uint8_t IF_System_Get_Potrcol(void)
{
    return COMM_PROTOL_SET;
}
void UI_IF_System_Set_Potrcol(uint8_t protocol)
{
    if(protocol > UART_PROTOL_MAX) {
        protocol = UART_PROTOL_MAX;
    }
    COMM_PROTOL_SET = protocol;
    lv_event_send_refresh(ui.Setting_btn_Comm_Protocol_label);
    eeprom_Option_RequestSave(0);
}

//设置协议地址
void IF_System_Set_Potrcol_Address(uint8_t address)
{
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_SET_COMM_PROTOCOL_ADDR;
    msg.data.data_u8 = address;
    CMD_MsgQueue_Send(&msg);
}
uint8_t IF_System_Get_Potrcol_Address(void)
{
    return COMM_PROTOL_ADDR_SET;
}
void UI_IF_System_Set_Potrcol_Address(uint8_t address)
{
    if(address < PROTOCOL_ADDR_MIN) {
        address = PROTOCOL_ADDR_MIN;
    } else
        if(address > PROTOCOL_ADDR_MAX) {
            address = PROTOCOL_ADDR_MAX;
        }
    COMM_PROTOL_ADDR_SET = address;
    lv_event_send_refresh(ui.Setting_btn_Comm_Address_label);
    eeprom_Option_RequestSave(0);
    MB_User_Config(COMM_BAUDR_SET, COMM_PROTOL_ADDR_SET);
}



//背光
void IF_System_Brightness_Set(uint8_t light)
{
    //发送信息
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_SET_BACK_LIGHT;
    msg.data.data_u8 = light;
    CMD_MsgQueue_Send(&msg);
}
uint8_t IF_System_LCD_Light_Get(void)
{
    return BACKLIGHT_SET;
}
void UI_IF_System_Brightness_Set(uint8_t light)
{
    if(light < BACK_LIGHT_MIN) {
        light = BACK_LIGHT_MIN;
    }
    else
        if(light > BACK_LIGHT_MAX) {
            light = BACK_LIGHT_MAX;
        }
    BACKLIGHT_SET = light;
    TIM16->CCR1 = light * 2;
    TIM5->CCR1 = light * 2;
    if(ui.Setting_btn_BackLight_label != NULL) {
        lv_event_send_refresh(ui.Setting_btn_BackLight_label);
        eeprom_Option_RequestSave(0);
    }
}
//语言
void IF_System_Language_Set(uint8_t language)
{
    //发送信息
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_SET_LANGUAGE;
    msg.data.data_u8 = language;
    CMD_MsgQueue_Send(&msg);
}
void UI_IF_System_Language_Set(uint8_t language)
{
    LANGUAGE_SET = language;
    eeprom_Option_RequestSave(0);
    //刷新虚拟按键
    Tree_Btnm_Refresh();
    lv_event_send_refresh(ui.Menu_cont);
    lv_event_send_refresh_recursive(ui.HomePage_cont_Set);
}


//蜂鸣器
void IF_System_Beeper_Set(uint8_t onoff)
{
    //发送信息
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_BEEP_ONOFF;
    msg.data.data_u8 = onoff;
    CMD_MsgQueue_Send(&msg);
}
uint8_t IF_System_Beeper_Get_Onoff(void)
{
    return (BEEP_SET != 0);
}
void UI_IF_System_Beeper_Set(uint8_t onoff)
{
    BEEP_SET = onoff;
    beep_Set_Enable(onoff);
    lv_event_send_refresh(ui.Setting_btn_Beep_label);
    eeprom_Option_RequestSave(0);
    extern void Status_Refresh(uint8_t type, uint8_t onoff);
    Status_Refresh(MSG_TYPE_BEEP_ONOFF, onoff);
}


//掉电检测
void IF_System_Set_PowerDown(uint8_t onoff)
{
    //发送信息
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_POWERDOWN_ONOFF;
    msg.data.data_u8 = onoff;
    CMD_MsgQueue_Send(&msg);
}
uint8_t IF_System_PowerDown_Get_Onoff(void)
{
    return (POWERDOWN_SET != 0);
}
void UI_IF_System_Set_PowerDown(uint8_t onoff)
{
    POWERDOWN_SET = onoff;
    lv_event_send_refresh(ui.Setting_btn_PowerDown_label);
    eeprom_Option_RequestSave(0);
}



//开机保持P-OUT
void IF_System_POUT_Onoff(uint8_t onoff)
{
    //发送信息
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_OUTOPTION_SET_OUTKEEPON;
    msg.data.data_u8 = onoff;
    CMD_MsgQueue_Send(&msg);
}
void UI_IF_System_POut_Onoff(uint8_t onoff)
{
    POWER_OUTKEEPON_SET = onoff;
    lv_event_send_refresh(ui.OutOptionPage_btn_P_Out_label);
    eeprom_OutSet_RequestSave(0);
}


//DVM电压表开关
void IF_System_DVM_Onoff(uint8_t onoff)
{
    //发送信息
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_OUTOPTION_SET_DVM_ONOFF;
    msg.data.data_u8 = onoff;
    CMD_MsgQueue_Send(&msg);
}
void UI_IF_System_DVM_Onoff(uint8_t onoff)
{
    DVM_ONOFF_SET = onoff;
    if(DVM_ONOFF_SET != 0) {
        lv_obj_set_height(ui.HomePage2_btn_Mode, 35);
        lv_obj_set_style_local_text_font(ui.HomePage2_btn_Mode_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_AlibabaPuHuiTi_Light_20);
        lv_obj_set_hidden(ui.HomePage_btn_DVM_label, 0);
        lv_obj_set_hidden(ui.HomePage2_label_DVM, 0);
        lv_obj_set_hidden(ui.HomePage2_label_DVM_label, 0);
    } else {
        lv_obj_set_height(ui.HomePage2_btn_Mode, 35 + 33);
        lv_obj_set_style_local_text_font(ui.HomePage2_btn_Mode_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_AlibabaPuHuiTi_Light_26);
        lv_obj_set_hidden(ui.HomePage_btn_DVM_label, 1);
        lv_obj_set_hidden(ui.HomePage2_label_DVM, 1);
        lv_obj_set_hidden(ui.HomePage2_label_DVM_label, 1);
    }
    lv_event_send_refresh(ui.OutOptionPage_btn_DVM_label);
    eeprom_OutSet_RequestSave(0);
}

/* ------------------------- DHCP ------------------------- */
//DHCP
#include "lwip.h"
void IF_System_LAN_Apply(void)
{
    //发送信息
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_SET_APPLY;
    CMD_MsgQueue_Send(&msg);
}
void UI_IF_System_LAN_Apply(uint8_t flag)
{
    DHCP_SET = DHCP_SET_TMP;
    memcpy(IP_SET, IP_SET_TMP, sizeof(IP_SET_TMP));
    memcpy(NETMASK_SET, NETMASK_SET_TMP, sizeof(NETMASK_SET_TMP));
    memcpy(GW_SET, GW_SET_TMP, sizeof(GW_SET_TMP));
    
    systemInfo.flag.bits.net_save |= 1;
    //更新UI显示
    lv_event_send_refresh_recursive(ui.Setting_cont_1);
    eeprom_Option_RequestSave(flag);
}

//DHCP
void IF_System_DHCP_Onoff(uint8_t onoff)
{
    //发送信息
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_SET_DHCP;
    msg.data.data_u8 = onoff;
    CMD_MsgQueue_Send(&msg);
}
uint8_t IF_System_Get_DHCP_Onoff(void)
{
    return DHCP_SET;
}
uint8_t IF_System_Get_DHCP_TMP_Onoff(void)
{
    return DHCP_SET_TMP;
}
void UI_IF_System_DHCP_Onoff(uint8_t onoff)
{
    DHCP_SET_TMP = onoff;
    if(onoff != 0) {
        lv_obj_set_style_local_text_opa(ui.Setting_btn_NetIP_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 100);
        lv_obj_set_style_local_text_opa(ui.Setting_btn_GateWay_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 100);
        lv_obj_set_style_local_text_opa(ui.Setting_btn_NetMask_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 100);
    } else {
        lv_obj_set_style_local_text_opa(ui.Setting_btn_NetIP_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 255);
        lv_obj_set_style_local_text_opa(ui.Setting_btn_GateWay_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 255);
        lv_obj_set_style_local_text_opa(ui.Setting_btn_NetMask_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 255);
    }
    lv_event_send_refresh_recursive(ui.Setting_cont_1);
    eeprom_Option_RequestSave(0);
}

//网络地址
void IF_System_Set_LAN_IP(uint8_t addr0, uint8_t addr1, uint8_t addr2, uint8_t addr3)
{
    //发送信息
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_SET_IP;
    msg.data.lan_param.ip[0] = addr0;
    msg.data.lan_param.ip[1] = addr1;
    msg.data.lan_param.ip[2] = addr2;
    msg.data.lan_param.ip[3] = addr3;
    CMD_MsgQueue_Send(&msg);
}
void UI_IF_System_Set_LAN_IP(uint8_t addr0, uint8_t addr1, uint8_t addr2, uint8_t addr3)
{
    IP_SET_TMP[0] = addr0;
    IP_SET_TMP[1] = addr1;
    IP_SET_TMP[2] = addr2;
    IP_SET_TMP[3] = addr3;
    lv_event_send_refresh_recursive(ui.Setting_cont_1);
    eeprom_Option_RequestSave(0);
}

//网关
void IF_System_Set_LAN_GW(uint8_t addr0, uint8_t addr1, uint8_t addr2, uint8_t addr3)
{
    //发送信息
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_SET_GW;
    msg.data.lan_param.ip[0] = addr0;
    msg.data.lan_param.ip[1] = addr1;
    msg.data.lan_param.ip[2] = addr2;
    msg.data.lan_param.ip[3] = addr3;
    CMD_MsgQueue_Send(&msg);
}
void UI_IF_System_Set_LAN_GW(uint8_t addr0, uint8_t addr1, uint8_t addr2, uint8_t addr3)
{
    GW_SET_TMP[0] = addr0;
    GW_SET_TMP[1] = addr1;
    GW_SET_TMP[2] = addr2;
    GW_SET_TMP[3] = addr3;
    lv_event_send_refresh_recursive(ui.Setting_cont_1);
    eeprom_Option_RequestSave(0);
}

//子网掩码
void IF_System_Set_LAN_NetMask(uint8_t addr0, uint8_t addr1, uint8_t addr2, uint8_t addr3)
{
    //发送信息
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_SET_NETMASK;
    msg.data.lan_param.ip[0] = addr0;
    msg.data.lan_param.ip[1] = addr1;
    msg.data.lan_param.ip[2] = addr2;
    msg.data.lan_param.ip[3] = addr3;
    CMD_MsgQueue_Send(&msg);
}
void UI_IF_System_Set_LAN_NetMask(uint8_t addr0, uint8_t addr1, uint8_t addr2, uint8_t addr3)
{
    NETMASK_SET_TMP[0] = addr0;
    NETMASK_SET_TMP[1] = addr1;
    NETMASK_SET_TMP[2] = addr2;
    NETMASK_SET_TMP[3] = addr3;
    lv_event_send_refresh_recursive(ui.Setting_cont_1);
    eeprom_Option_RequestSave(0);
}







void IF_System_Set_Remote(uint8_t remote)
{
    //发送信息
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_SYSTEM_REMOTE;
    msg.data.data_u8 = remote;
    CMD_MsgQueue_Send(&msg);
}
uint8_t IF_System_Get_Remote(void)
{
    return SCPI_REMOTE_MODE;
}
void UI_IF_System_Set_Remote(uint8_t remote)
{
    static uint8_t lockFlag = 0;
    if(remote != 0) {
        //若指令前已经锁定了,则不解锁
        if(IF_Power_Get_Lock() != 0) {
            lockFlag = 1;
        }
        UI_IF_Power_Set_Lock(1);
    } else {
        //恢复本地控制:若先前没锁定,则解锁
        if(lockFlag == 0) {
            UI_IF_Power_Set_Lock(0);
        }
        lockFlag = 0;
    }
    extern void Status_Refresh(uint8_t type, uint8_t onoff);
    Status_Refresh(MSG_TYPE_SYSTEM_REMOTE, remote);
    SCPI_REMOTE_MODE = remote;
}

#include "ff.h"
#include "listout.h"
#include "delayout.h"
#include "BatTester.h"
//USB U盘
void IF_System_USB_Disk_Connect(uint8_t connect)
{
    //发送信息
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_USB_DISK_CONNECT;
    msg.data.data_u8 = connect;
    CMD_MsgQueue_Send(&msg);
}
void UI_IF_System_USB_Disk_Connect(uint8_t connect)
{
    extern void Status_Refresh(uint8_t type, uint8_t onoff);
    Status_Refresh(MSG_TYPE_USB_DISK_CONNECT, connect);
    //    //提示框
    //    if(connect) {
    //        IF_MsgBox_Tips_Mult(&mStr_USB_Disk_Connected);
    //    } else {
    //        IF_MsgBox_Tips_Mult(&mStr_USB_Disk_Disconnected);
    //    }
    //USB Host连接上后创建文件夹
    {
        DIR tempDir = {0};
        if(f_opendir(&tempDir, LISTOUT_FILE_USB_PATH) != FR_OK) {
            f_mkdir(LISTOUT_FILE_USB_PATH);
        }
        f_closedir(&tempDir);
        if(f_opendir(&tempDir, DELAYOUT_FILE_USB_PATH) != FR_OK) {
            f_mkdir(DELAYOUT_FILE_USB_PATH);
        }
        f_closedir(&tempDir);
        if(f_opendir(&tempDir, GROUP_FILE_USB_PATH) != FR_OK) {
            f_mkdir(GROUP_FILE_USB_PATH);
        }
        f_closedir(&tempDir);
        if(f_opendir(&tempDir, BAT_TESTER_FILE_USB_PATH) != FR_OK) {
            f_mkdir(BAT_TESTER_FILE_USB_PATH);
        }
        f_closedir(&tempDir);
    }
    //若当前显示文件管理页面,则刷新页面
    if(ui.ListManagePage_cont != NULL) {
        if(lv_obj_is_visible(ui.ListManagePage_cont) != 0) {
            lv_event_send_refresh(ui.ListManagePage_cont);
        }
    }
    if(ui.DelayManagePage_cont != NULL) {
        if(lv_obj_is_visible(ui.DelayManagePage_cont) != 0) {
            lv_event_send_refresh(ui.DelayManagePage_cont);
        }
    }
    if(ui.GroupPage_cont != NULL) {
        if(lv_obj_is_visible(ui.GroupPage_cont) != 0) {
            lv_event_send_refresh(ui.GroupPage_cont);
        }
    }
    if(ui.BatTesterManager_cont != NULL) {
        if(lv_obj_is_visible(ui.BatTesterManager_cont) != 0) {
            lv_event_send_refresh(ui.BatTesterManager_cont);
        }
    }
}

//USB Device
void IF_System_USB_Device_Connect(uint8_t connect)
{
    //发送信息
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_USB_DEVICE_CONNECT;
    msg.data.data_u8 = connect;
    CMD_MsgQueue_Send(&msg);
}
void UI_IF_System_USB_Device_Connect(uint8_t connect)
{
    extern void Status_Refresh(uint8_t type, uint8_t onoff);
    Status_Refresh(MSG_TYPE_USB_DEVICE_CONNECT, connect);
}

//LAN接口
void IF_System_LAN_Connect(uint8_t connect)
{
    //发送信息
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_LAN_CONNECT;
    msg.data.data_u8 = connect;
    CMD_MsgQueue_Send(&msg);
}

void UI_IF_System_LAN_Connect(uint8_t connect)
{
    extern void Status_Refresh(uint8_t type, uint8_t onoff);
    Status_Refresh(MSG_TYPE_LAN_CONNECT, connect);
}






#include "bmpImage.h"
void IF_System_ScreenShot(void)
{
    //发送信息
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_SCREENSHOT;
    CMD_MsgQueue_Send(&msg);
}

void UI_IF_System_ScreenShot(void)
{
    static uint8_t count = 0;
    static char imgName[128] = {0};
    sprintf(imgName, "USB:ScreenShot%d.bmp", count++);
    if(0 == dump_image_to_bmp_file(imgName)) {
        IF_MsgBox_Tips_Mult(&mStr_ScreenShot_OK_Event);
    } else {
        IF_MsgBox_Tips_Mult(&mStr_ScreenShot_Failed_Event);
    }
}


//校准模式
void IF_System_Set_CalibMode(uint8_t enable)
{
    //发送信息
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_SET_CALIBMODE;
    msg.data.data_u8 = enable;
    CMD_MsgQueue_Send(&msg);
}
void UI_IF_System_Set_CalibMode(uint8_t enable)
{
    POWER_CALIB_MODE = enable;
    extern void Status_Refresh(uint8_t type, uint8_t onoff);
    Status_Refresh(MSG_TYPE_SET_CALIBMODE, enable);
    IF_MsgBox_Tips_Mult(&mStr_Calib_Enter_Tips);
}




