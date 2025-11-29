#include "Monitor_SCPI.h"

#include "main.h"
#include "Commd.h"

#include "Setting_Interface.h"

//蜂鸣器
scpi_result_t Cmd_Set_Beeper(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    scpi_bool_t param1 = {0};
    if(!SCPI_ParamBool(context, &param1, FALSE)) {
        SCPI_ERR_RETURN;
    }
    IF_Display_Go_to_Page(PAGE_SETTING);
    IF_System_Beeper_Set(param1);
    return SCPI_RES_OK;
}

scpi_result_t Cmd_Read_Beeper(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    const char *beeper_str = "";
    if(!SCPI_ChoiceToName(scpi_bool_def, IF_System_Beeper_Get_Onoff(), &beeper_str) != 0) {
        SCPI_ERR_RETURN;
    }
    char buffer[32] = "";
    int length = snprintf(buffer, sizeof(buffer) - 1, "%s", beeper_str);
    SCPI_ResultCharacters(context, buffer, length);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_System_Beeper(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    BEEP_WARRING();
    return SCPI_RES_OK;
}

//掉电检测
scpi_result_t Cmd_Set_PowerDown(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    scpi_bool_t param1 = {0};
    if(!SCPI_ParamBool(context, &param1, FALSE)) {
        SCPI_ERR_RETURN;
    }
    IF_Display_Go_to_Page(PAGE_SETTING);
    IF_System_Set_PowerDown(param1);
    return SCPI_RES_OK;
}

scpi_result_t Cmd_Read_PowerDown(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    const char *beeper_str = "";
    if(!SCPI_ChoiceToName(scpi_bool_def, IF_System_PowerDown_Get_Onoff(), &beeper_str) != 0) {
        SCPI_ERR_RETURN;
    }
    char buffer[32] = "";
    int length = snprintf(buffer, sizeof(buffer) - 1, "%s", beeper_str);
    SCPI_ResultCharacters(context, buffer, length);
    return SCPI_RES_OK;
}

//屏幕背光
scpi_result_t Cmd_Set_Brightness(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    scpi_number_t param_brightness = {0};
    if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &param_brightness, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(param_brightness.special != FALSE) {
        switch(param_brightness.content.tag) {
            case SCPI_NUM_MIN:
                param_brightness.content.value = BACK_LIGHT_MIN;
                break;
            case SCPI_NUM_MAX:
                param_brightness.content.value = BACK_LIGHT_MAX;
                break;
        }
    }
    IF_Display_Go_to_Page(PAGE_SETTING);
    IF_System_Brightness_Set(param_brightness.content.value);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_Brightness(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    char buffer[32] = "";
    int length = snprintf(buffer, sizeof(buffer) - 1, "%d", IF_System_LCD_Light_Get());
    SCPI_ResultCharacters(context, buffer, length);
    return SCPI_RES_OK;
}


//波特率
scpi_result_t Cmd_Set_COM_BaudRate(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    scpi_number_t param_baudRate = {0};
    if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &param_baudRate, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(param_baudRate.special != FALSE) {
        switch(param_baudRate.content.tag) {
            case SCPI_NUM_MIN:
                param_baudRate.content.value = BAUDR_MIN;
                break;
            case SCPI_NUM_MAX:
                param_baudRate.content.value = BAUDR_MAX;
                break;
        }
    }
    IF_Display_Go_to_Page(PAGE_SETTING);
    IF_System_Set_BaudRate(param_baudRate.content.value);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_COM_BaudRate(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    char buffer[32] = "";
    int length = snprintf(buffer, sizeof(buffer) - 1, "%d", IF_System_Get_BaudRate());
    SCPI_ResultCharacters(context, buffer, length);
    return SCPI_RES_OK;
}



#if 1
//通讯协议
scpi_result_t Cmd_Set_COM_Protocol(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    scpi_number_t param_protocol = {0};
    if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &param_protocol, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(param_protocol.special != FALSE) {
        switch(param_protocol.content.tag) {
            case SCPI_NUM_MIN:
                param_protocol.content.value = UART_PROTOL_MIN;
                break;
            case SCPI_NUM_MAX:
                param_protocol.content.value = UART_PROTOL_MAX;
                break;
        }
    }
    IF_Display_Go_to_Page(PAGE_SETTING);
    IF_System_Set_Potrcol(param_protocol.content.value);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_COM_Protocol(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    char buffer[32] = "";
    int length = snprintf(buffer, sizeof(buffer) - 1, "%d", IF_System_Get_Potrcol());
    SCPI_ResultCharacters(context, buffer, length);
    return SCPI_RES_OK;
}

//通讯地址
scpi_result_t Cmd_Set_COM_Protocol_Address(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    scpi_number_t param_address = {0};
    if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &param_address, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(param_address.special != FALSE) {
        switch(param_address.content.tag) {
            case SCPI_NUM_MIN:
                param_address.content.value = PROTOCOL_ADDR_MIN;
                break;
            case SCPI_NUM_MAX:
                param_address.content.value = PROTOCOL_ADDR_MAX;
                break;
        }
    }
    IF_Display_Go_to_Page(PAGE_SETTING);
    IF_System_Set_Potrcol_Address(param_address.content.value);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_COM_Protocol_Address(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    char buffer[32] = "";
    int length = snprintf(buffer, sizeof(buffer) - 1, "%d", IF_System_Get_Potrcol_Address());
    SCPI_ResultCharacters(context, buffer, length);
    return SCPI_RES_OK;
}
#endif



//保存网络设置
scpi_result_t Cmd_Set_LAN_Apply(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    IF_Display_Go_to_Page(PAGE_SETTING);
    IF_System_LAN_Apply();
    return SCPI_RES_OK;
}

//DHCP
scpi_result_t Cmd_Set_LAN_DHCP(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    scpi_bool_t param1 = {0};
    if(!SCPI_ParamBool(context, &param1, FALSE)) {
        SCPI_ERR_RETURN;
    }
    IF_Display_Go_to_Page(PAGE_SETTING);
    IF_System_DHCP_Onoff(param1);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_LAN_DHCP(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    const char *beeper_str = "";
    if(!SCPI_ChoiceToName(scpi_bool_def, IF_System_Get_DHCP_Onoff(), &beeper_str) != 0) {
        SCPI_ERR_RETURN;
    }
    char buffer[32] = "";
    int length = snprintf(buffer, sizeof(buffer) - 1, "%s", beeper_str);
    SCPI_ResultCharacters(context, buffer, length);
    return SCPI_RES_OK;
}


//IP地址
scpi_result_t Cmd_Set_LAN_IP(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    char IP_str[64] = {0};
    size_t IP_len = 0;
    if(!SCPI_ParamCopyText(context, IP_str, sizeof(IP_str) - 1, &IP_len, FALSE)) {
        SCPI_ERR_RETURN;
    }
    int ip_addr[4] = {0};
    uint8_t valibCount = sscanf(IP_str, "%d.%d.%d.%d", &ip_addr[0], &ip_addr[1], &ip_addr[2], &ip_addr[3]);
    if(valibCount == 4) {
        IF_Display_Go_to_Page(PAGE_SETTING);
        IF_System_Set_LAN_IP(ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3]);
    }
    return SCPI_RES_OK;
}

scpi_result_t Cmd_Read_LAN_IP(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    char buffer[64] = "";
    int length = snprintf(buffer, sizeof(buffer) - 1, "%d.%d.%d.%d", IP_SET[0], IP_SET[1], IP_SET[2], IP_SET[3]);
    SCPI_ResultCharacters(context, buffer, length);
    return SCPI_RES_OK;
}

//网关
scpi_result_t Cmd_Set_LAN_GateWay(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    char GW_str[64] = {0};
    size_t GW_len = 0;
    if(!SCPI_ParamCopyText(context, GW_str, sizeof(GW_str) - 1, &GW_len, FALSE)) {
        SCPI_ERR_RETURN;
    }
    int gateway_addr[4] = {0};
    uint8_t valibCount = sscanf(GW_str, "%d.%d.%d.%d", &gateway_addr[0], &gateway_addr[1], &gateway_addr[2], &gateway_addr[3]);
    if(valibCount == 4) {
        IF_Display_Go_to_Page(PAGE_SETTING);
        IF_System_Set_LAN_GW(gateway_addr[0], gateway_addr[1], gateway_addr[2], gateway_addr[3]);
    }
    return SCPI_RES_OK;
}

scpi_result_t Cmd_Read_LAN_GateWay(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    char buffer[64] = "";
    int length = snprintf(buffer, sizeof(buffer) - 1, "%d.%d.%d.%d", GW_SET[0], GW_SET[1], GW_SET[2], GW_SET[3]);
    SCPI_ResultCharacters(context, buffer, length);
    return SCPI_RES_OK;
}

//子网掩码
scpi_result_t Cmd_Set_LAN_NetMask(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    char NetMask_str[64] = {0};
    size_t NetMask_len = 0;
    if(!SCPI_ParamCopyText(context, NetMask_str, sizeof(NetMask_str) - 1, &NetMask_len, FALSE)) {
        SCPI_ERR_RETURN;
    }
    int netmask_addr[4] = {0};
    uint8_t valibCount = sscanf(NetMask_str, "%d.%d.%d.%d", &netmask_addr[0], &netmask_addr[1], &netmask_addr[2], &netmask_addr[3]);
    if(valibCount == 4) {
        IF_Display_Go_to_Page(PAGE_SETTING);
        IF_System_Set_LAN_NetMask(netmask_addr[0], netmask_addr[1], netmask_addr[2], netmask_addr[3]);
    }
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_LAN_NetMask(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    char buffer[64] = "";
    int length = snprintf(buffer, sizeof(buffer) - 1, "%d.%d.%d.%d", NETMASK_SET[0], NETMASK_SET[1], NETMASK_SET[2], NETMASK_SET[3]);
    SCPI_ResultCharacters(context, buffer, length);
    return SCPI_RES_OK;
}


//远程控制模式
scpi_result_t Cmd_Set_System_Remote_Mode(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    IF_System_Set_Remote(1);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Set_System_Local_Mode(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    IF_System_Set_Remote(0);
    return SCPI_RES_OK;
}


scpi_result_t Cmd_Set_System_Lock(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    IF_Power_Set_Lock(1);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Set_System_UnLock(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    IF_Power_Set_Lock(0);
    return SCPI_RES_OK;
}

