#include "SettingPage.h"
#include "SettingPage_item.h"
#include "SettingData.h"

#include "Beep_Device.h"
#include "Interface.h"
#include "Setting_Interface.h"

/*
 * @brief
 * @details     特殊字符定义
 */
typedef struct {
    uint8_t value;
    const MultStr_Def *multStr;
} valueString_Def;
static const char *valueStr_GetStr(uint8_t value, const valueString_Def *valueStr)
{
    for(uint8_t i = 0; valueStr[i].multStr != NULL; ++i) {
        if(valueStr[i].value == value) {
            return MultStr_GetS(valueStr[i].multStr);
        }
    }
    return "";
}



/*
 * @brief       void Brightness_handler(lv_obj_t *obj, lv_event_t event)
 * @details     屏幕背光事件处理
 */
void Brightness_handler(lv_obj_t *obj, lv_event_t event)
{
    static uint8_t editFlag = 0;
    NumberInput_Process(7, UI_IF_System_Brightness_Set);
    switch(event)
    {
        case LV_EVENT_KEY:
        {
            uint8_t light = BACKLIGHT_SET;
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                case LV_KEY_UP: {
                    if(light < BACK_LIGHT_MAX) {
                        light++;
                    }
                }
                break;
                case LV_KEY_DOWN: {
                    if(light > BACK_LIGHT_MIN) {
                        light--;
                    }
                }
                break;
                case LV_KEY_ENCODER:
                case LV_KEY_ENTER:
                    break;
                case LV_KEY_ESC:
                    editFlag = 0;
                    break;
                default:
                {} break;
            }
            UI_IF_System_Brightness_Set(light);
        }
        break;
        case LV_EVENT_CLICKED:
            editFlag = 1;
        case LV_EVENT_REFRESH: {
        } break;
    }
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_Brightness));
    static char buf[16] = {0};
    sprintf(buf, "%3d%%", BACKLIGHT_SET);
    lv_label_set_text_static(obj, buf);
    lv_obj_t *button = lv_obj_get_parent(obj);
    if(editFlag != 0) {
        lv_obj_set_state(button, LV_STATE_FOCUSED);
        lv_obj_set_state(obj, LV_STATE_FOCUSED);
        label_setSelStr(obj, buf, buf);
    } else {
        lv_obj_set_state(button, LV_STATE_DEFAULT);
        lv_obj_set_state(obj, LV_STATE_DEFAULT);
        lv_label_set_text_sel_start(obj, 0);
        lv_label_set_text_sel_end(obj, 0);
    }
}



/*
 * @brief       void Beep_handler(lv_obj_t *obj, lv_event_t event)
 * @details     蜂鸣器事件处理
 */
void Beep_handler(lv_obj_t *obj, lv_event_t event)
{
    const valueString_Def valueStr[] = {
        {0, &mStr_OFF},
        {1, &mStr_ON},
        {0},
    };
    static uint8_t editFlag = 0;
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key) {
                case LV_KEY_UP:
                case LV_KEY_DOWN:
                case LV_KEY_ENCODER:
                case LV_KEY_ENTER: {
                    uint8_t temp = BEEP_SET;
                    temp = (temp + 1) % 2;
                    UI_IF_System_Beeper_Set(temp);
                }
                break;
                case LV_KEY_ESC:
                    editFlag = 0;
                    break;
            }
        }
        break;
        case LV_EVENT_CLICKED: {
            if(editFlag == 1) {
                uint8_t temp = BEEP_SET;
                temp = (temp + 1) % 2;
                UI_IF_System_Beeper_Set(temp);
            }
            editFlag = 1;
        }
        case LV_EVENT_REFRESH:
            break;
    }
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_Beeper));
    const char *str = valueStr_GetStr(BEEP_SET, valueStr);
    lv_label_set_text_static(obj, str);
    lv_obj_t *button = lv_obj_get_parent(obj);
    if(editFlag != 0) {
        lv_obj_set_state(button, LV_STATE_FOCUSED);
        lv_obj_set_state(obj, LV_STATE_FOCUSED);
        label_setSelStr(obj, str, str);
    } else {
        lv_obj_set_state(button, LV_STATE_DEFAULT);
        lv_obj_set_state(obj, LV_STATE_DEFAULT);
        lv_label_set_text_sel_start(obj, 0);
        lv_label_set_text_sel_end(obj, 0);
    }
}


/*
 * @brief       void Power_Setting_handler(lv_obj_t *obj, lv_event_t event)
 * @details     掉电检测开关处理
 */
void Power_Setting_handler(lv_obj_t *obj, lv_event_t event)
{
    const valueString_Def valueStr[] = {
        {0, &mStr_OFF},
        {1, &mStr_ON},
        {0},
    };
    static uint8_t editFlag = 0;
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key) {
                case LV_KEY_UP:
                case LV_KEY_DOWN:
                case LV_KEY_ENCODER:
                case LV_KEY_ENTER: {
                    uint8_t temp = POWERDOWN_SET;
                    temp = (temp + 1) % 2;
                    UI_IF_System_Set_PowerDown(temp);
                }
                break;
                case LV_KEY_ESC:
                    editFlag = 0;
                    break;
            }
        }
        break;
        case LV_EVENT_CLICKED: {
            if(editFlag == 1) {
                uint8_t temp = POWERDOWN_SET;
                temp = (temp + 1) % 2;
                UI_IF_System_Set_PowerDown(temp);
            }
            editFlag = 1;
        }
        case LV_EVENT_REFRESH:
            break;
    }
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_PowerDown));
    const char *str = valueStr_GetStr(POWERDOWN_SET, valueStr);
    lv_label_set_text_static(obj, str);
    lv_obj_t *button = lv_obj_get_parent(obj);
    if(editFlag != 0) {
        lv_obj_set_state(button, LV_STATE_FOCUSED);
        lv_obj_set_state(obj, LV_STATE_FOCUSED);
        label_setSelStr(obj, str, str);
    } else {
        lv_obj_set_state(button, LV_STATE_DEFAULT);
        lv_obj_set_state(obj, LV_STATE_DEFAULT);
        lv_label_set_text_sel_start(obj, 0);
        lv_label_set_text_sel_end(obj, 0);
    }
}





static int8_t __BaudRate_GetCurIdx(uint32_t baudRate)
{
    for(uint8_t i = 0; i < ((sizeof(BaudRate_step) / sizeof(BaudRate_step[0]))); ++i)
    {
        if(baudRate == BaudRate_step[i]) {
            return i;
        }
    }
    return -1;
}

#include "usart.h"
static void __BaudRate_SetCurIdx(uint8_t idx)
{
    if(idx >= ((sizeof(BaudRate_step) / sizeof(BaudRate_step[0]))))
    {
        return;
    }
    COMM_BAUDR_SET = BaudRate_step[idx];
    UI_IF_System_Set_BaudRate(COMM_BAUDR_SET);
}

/*
 * @brief       void Comm_BaudRate_handler(lv_obj_t *obj, lv_event_t event)
 * @details     RS232波特率设置
 */
void Comm_BaudRate_handler(lv_obj_t *obj, lv_event_t event)
{
    static uint8_t editFlag = 0;
    NumberInput_Process(7, UI_IF_System_Set_BaudRate);
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key) {
                case LV_KEY_ENCODER:
                case LV_KEY_ENTER:
                case LV_KEY_UP: {
                    int8_t idx = __BaudRate_GetCurIdx(COMM_BAUDR_SET);
                    idx += 1;
                    __BaudRate_SetCurIdx(idx);
                }
                break;
                case LV_KEY_DOWN: {
                    int8_t idx = __BaudRate_GetCurIdx(COMM_BAUDR_SET);
                    idx -= 1;
                    if(idx < 0) {
                        idx = 0;
                    }
                    __BaudRate_SetCurIdx(idx);
                }
                break;
                case LV_KEY_ESC: {
                    editFlag = 0;
                }
                break;
                default:
                {} break;
            }
        }
        break;
        case LV_EVENT_CLICKED:
            editFlag = 1;
            break;
    }
    static char stringSet[16] = {0};
    sprintf(stringSet, "%d", COMM_BAUDR_SET);
    lv_label_set_text_static(obj, stringSet);
    lv_obj_t *button = lv_obj_get_parent(obj);
    if(editFlag != 0) {
        lv_obj_set_state(button, LV_STATE_FOCUSED);
        lv_obj_set_state(obj, LV_STATE_FOCUSED);
        label_setSelStr(obj, stringSet, stringSet);
    } else {
        lv_obj_set_state(button, LV_STATE_DEFAULT);
        lv_obj_set_state(obj, LV_STATE_DEFAULT);
        lv_label_set_text_sel_start(obj, 0);
        lv_label_set_text_sel_end(obj, 0);
    }
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_Comm_BaudRate));
}

/*
 * @brief       void Comm_Protocol_handler(lv_obj_t *obj, lv_event_t event)
 * @details     通讯协议
 */
void Comm_Protocol_handler(lv_obj_t *obj, lv_event_t event)
{
    const valueString_Def valueStr[] = {
        {UART_PROTOL_SCPI, &mStr_Comm_Protocol_SCPI},
        {UART_PROTOL_MULT_SCPI, &mStr_Comm_Protocol_MultSCPI},
        {UART_PROTOL_MODBUS, &mStr_Comm_Protocol_Modbus},
        {0},
    };
    static uint8_t editFlag = 0;
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key) {
                case LV_KEY_UP:
                case LV_KEY_DOWN:
                case LV_KEY_ENCODER:
                case LV_KEY_ENTER: {
                    uint8_t temp = COMM_PROTOL_SET;
                    temp = (temp + 1) % (UART_PROTOL_MAX + 1);
                    UI_IF_System_Set_Potrcol(temp);
                }
                break;
                case LV_KEY_ESC:
                    editFlag = 0;
                    break;
            }
        }
        break;
        case LV_EVENT_CLICKED: {
            if(editFlag == 1) {
                uint8_t temp = COMM_PROTOL_SET;
                temp = (temp + 1) % (UART_PROTOL_MAX + 1);
                UI_IF_System_Set_Potrcol(temp);
            }
            editFlag = 1;
        }
        case LV_EVENT_REFRESH:
            break;
    }
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_Comm_Protocol));
    const char *str = valueStr_GetStr(COMM_PROTOL_SET, valueStr);
    lv_label_set_text_static(obj, str);
    lv_obj_t *button = lv_obj_get_parent(obj);
    if(editFlag != 0) {
        lv_obj_set_state(button, LV_STATE_FOCUSED);
        lv_obj_set_state(obj, LV_STATE_FOCUSED);
        label_setSelStr(obj, str, str);
    } else {
        lv_obj_set_state(button, LV_STATE_DEFAULT);
        lv_obj_set_state(obj, LV_STATE_DEFAULT);
        lv_label_set_text_sel_start(obj, 0);
        lv_label_set_text_sel_end(obj, 0);
    }
}

/*
 * @brief       void Comm_Protocol_Address_handler(lv_obj_t *obj, lv_event_t event)
 * @details     协议地址设置
 */
void Comm_Protocol_Address_handler(lv_obj_t *obj, lv_event_t event)
{
    static uint8_t editFlag = 0;
    NumberInput_Process(7, UI_IF_System_Set_Potrcol_Address);
    switch(event)
    {
        case LV_EVENT_KEY:
        {
            uint8_t addr = COMM_PROTOL_ADDR_SET;
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                case LV_KEY_UP: {
                    if(addr < PROTOCOL_ADDR_MAX) {
                        addr++;
                    }
                }
                break;
                case LV_KEY_DOWN: {
                    if(addr > PROTOCOL_ADDR_MIN) {
                        addr--;
                    }
                }
                break;
                case LV_KEY_ENCODER:
                case LV_KEY_ENTER:
                    break;
                case LV_KEY_ESC:
                    editFlag = 0;
                    break;
                default:
                {} break;
            }
            UI_IF_System_Set_Potrcol_Address(addr);
        }
        break;
        case LV_EVENT_CLICKED:
            editFlag = 1;
        case LV_EVENT_REFRESH: {
        } break;
    }
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_Comm_Address));
    static char buf[16] = {0};
    sprintf(buf, "%d", COMM_PROTOL_ADDR_SET);
    lv_label_set_text_static(obj, buf);
    lv_obj_t *button = lv_obj_get_parent(obj);
    if(editFlag != 0) {
        lv_obj_set_state(button, LV_STATE_FOCUSED);
        lv_obj_set_state(obj, LV_STATE_FOCUSED);
        label_setSelStr(obj, buf, buf);
    } else {
        lv_obj_set_state(button, LV_STATE_DEFAULT);
        lv_obj_set_state(obj, LV_STATE_DEFAULT);
        lv_label_set_text_sel_start(obj, 0);
        lv_label_set_text_sel_end(obj, 0);
    }
}



#include "lwip.h"
#include "lwip/init.h"
#include "lwip/netif.h"




static void IP_Focus(lv_obj_t *obj, uint8_t *idx, uint8_t ip[4])
{
    char string[32] = {0};
    uint8_t stringlen = 0;
    for(uint8_t i = 0; i < 4; ++i)
    {
        char temp[8] = {0};
        uint8_t templen = 0;
        templen = sprintf(temp, "%3d", ip[i]);
        strcat(string, temp);
        if((idx != NULL) && (*idx == i)) {
            lv_label_set_text_sel_start(obj, stringlen);
            lv_label_set_text_sel_end(obj, stringlen + templen);
        }
        if(i != (4 - 1)) {
            strcat(string, ".");
            templen += 1;
        }
        stringlen += templen;
    }
    lv_label_set_text(obj, string);
    if(idx == NULL) {
        lv_label_set_text_sel_start(obj, 0);
        lv_label_set_text_sel_end(obj, 0);
    }
}

/*
 * @brief       void IP_handler(lv_obj_t *obj, lv_event_t event)
 * @details     IP地址事件处理
 */
void IP_handler(lv_obj_t *obj, lv_event_t event)
{
    static uint8_t editFlag = 0;
    static uint8_t editIdx = 0;
    uint8_t refreshFlag = 0;
    NumberInput_Process(7, IP_SET_TMP[editIdx] =);
    switch(event)
    {
        case LV_EVENT_KEY:
        {
            refreshFlag = 1;
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                case LV_KEY_UP: {
                    if(IP_SET_TMP[editIdx] < 255) {
                        IP_SET_TMP[editIdx]++;
                    } else {
                        IP_SET_TMP[editIdx] = 0;
                    }
                }
                break;
                case LV_KEY_DOWN: {
                    if(IP_SET_TMP[editIdx] > 0) {
                        IP_SET_TMP[editIdx]--;
                    } else {
                        IP_SET_TMP[editIdx] = 255;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(editIdx > 0) {
                        editIdx--;
                    } else {
                        editIdx = 3;
                    }
                }
                break;
                case LV_KEY_RIGHT:
                case LV_KEY_ENCODER:
                case LV_KEY_ENTER:
                    if(editIdx < 3) {
                        editIdx++;
                    } else {
                        editIdx = 0;
                    }
                    break;
                case LV_KEY_ESC: {
                    editFlag = 0;
                }
                break;
                default:
                {} break;
            }
        }
        break;
        case LV_EVENT_CLICKED:
            editFlag = 1;
        case LV_EVENT_REFRESH:
            refreshFlag = 1;
            break;
    }
    if(refreshFlag != 0)
    {
        BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_IP));
        lv_obj_t *button = lv_obj_get_parent(obj);
        //根据DHCP开启时,显示DHCP地址
        uint8_t *p_ip = NULL;
        if(editFlag != 0) {
            p_ip = IP_SET_TMP;
        } else {
            static uint8_t ip_now[4] = {0};
            extern struct netif gnetif;
            ip_now[0] = (gnetif.ip_addr.addr >> 0) & 0xff;
            ip_now[1] = (gnetif.ip_addr.addr >> 8) & 0xff;
            ip_now[2] = (gnetif.ip_addr.addr >> 16) & 0xff;
            ip_now[3] = (gnetif.ip_addr.addr >> 24) & 0xff;
            p_ip = ip_now;
        }
        if(editFlag != 0) {
            lv_obj_set_state(button, LV_STATE_FOCUSED);
            lv_obj_set_state(obj, LV_STATE_FOCUSED);
            IP_Focus(obj, &editIdx, p_ip);
        } else {
            lv_obj_set_state(button, LV_STATE_DEFAULT);
            lv_obj_set_state(obj, LV_STATE_DEFAULT);
            IP_Focus(obj, NULL, p_ip);
        }
    }
}

/*
 * @brief       void GateWay_handler(lv_obj_t *obj, lv_event_t event)
 * @details     网关事件处理
 */
void GateWay_handler(lv_obj_t *obj, lv_event_t event)
{
    static uint8_t editFlag = 0;
    static uint8_t editIdx = 0;
    uint8_t refreshFlag = 0;
    NumberInput_Process(7, GW_SET_TMP[editIdx] =);
    switch(event)
    {
        case LV_EVENT_KEY:
        {
            refreshFlag = 1;
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                case LV_KEY_UP: {
                    if(GW_SET_TMP[editIdx] < 255) {
                        GW_SET_TMP[editIdx]++;
                    } else {
                        GW_SET_TMP[editIdx] = 0;
                    }
                }
                break;
                case LV_KEY_DOWN: {
                    if(GW_SET_TMP[editIdx] > 0) {
                        GW_SET_TMP[editIdx]--;
                    } else {
                        GW_SET_TMP[editIdx] = 255;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(editIdx > 0) {
                        editIdx--;
                    } else {
                        editIdx = 3;
                    }
                }
                break;
                case LV_KEY_RIGHT:
                case LV_KEY_ENCODER:
                case LV_KEY_ENTER:
                    if(editIdx < 3) {
                        editIdx++;
                    } else {
                        editIdx = 0;
                    }
                    break;
                case LV_KEY_ESC: {
                    editFlag = 0;
                }
                break;
                default:
                {} break;
            }
        }
        break;
        case LV_EVENT_CLICKED:
            editFlag = 1;
        case LV_EVENT_REFRESH: {
            refreshFlag = 1;
        }
        break;
    }
    if(refreshFlag != 0)
    {
        BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_Gateway));
        lv_obj_t *button = lv_obj_get_parent(obj);
        //根据DHCP开启时,显示DHCP网关
        uint8_t *p_gateway = NULL;
        if(editFlag != 0) {
            p_gateway = GW_SET_TMP;
        } else {
            static uint8_t gateway_now[4] = {0};
            extern struct netif gnetif;
            gateway_now[0] = (gnetif.gw.addr >> 0) & 0xff;
            gateway_now[1] = (gnetif.gw.addr >> 8) & 0xff;
            gateway_now[2] = (gnetif.gw.addr >> 16) & 0xff;
            gateway_now[3] = (gnetif.gw.addr >> 24) & 0xff;
            p_gateway = gateway_now;
        }
        if(editFlag != 0) {
            lv_obj_set_state(button, LV_STATE_FOCUSED);
            lv_obj_set_state(obj, LV_STATE_FOCUSED);
            IP_Focus(obj, &editIdx, p_gateway);
        } else {
            lv_obj_set_state(button, LV_STATE_DEFAULT);
            lv_obj_set_state(obj, LV_STATE_DEFAULT);
            IP_Focus(obj, NULL, p_gateway);
        }
    }
}

/*
 * @brief       void NetMask_handler(lv_obj_t *obj, lv_event_t event)
 * @details     子网掩码事件处理
 */
void NetMask_handler(lv_obj_t *obj, lv_event_t event)
{
    static uint8_t editFlag = 0;
    static uint8_t editIdx = 0;
    uint8_t refreshFlag = 0;
    NumberInput_Process(7, NETMASK_SET_TMP[editIdx] =);
    switch(event)
    {
        case LV_EVENT_KEY:
        {
            refreshFlag = 1;
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                case LV_KEY_UP: {
                    if(NETMASK_SET_TMP[editIdx] < 255) {
                        NETMASK_SET_TMP[editIdx]++;
                    } else {
                        NETMASK_SET_TMP[editIdx] = 0;
                    }
                }
                break;
                case LV_KEY_DOWN: {
                    if(NETMASK_SET_TMP[editIdx] > 0) {
                        NETMASK_SET_TMP[editIdx]--;
                    } else {
                        NETMASK_SET_TMP[editIdx] = 255;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(editIdx > 0) {
                        editIdx--;
                    } else {
                        editIdx = 3;
                    }
                }
                break;
                case LV_KEY_RIGHT:
                case LV_KEY_ENCODER:
                case LV_KEY_ENTER:
                    if(editIdx < 3) {
                        editIdx++;
                    } else {
                        editIdx = 0;
                    }
                    break;
                case LV_KEY_ESC: {
                    editFlag = 0;
                }
                break;
                default:
                {} break;
            }
        }
        break;
        case LV_EVENT_CLICKED:
            editFlag = 1;
        case LV_EVENT_REFRESH: {
            refreshFlag = 1;
        }
        break;
    }
    if(refreshFlag != 0)
    {
        BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_NetMask));
        lv_obj_t *button = lv_obj_get_parent(obj);
        //根据DHCP开启时,显示DHCP子网掩码
        uint8_t *p_netmask = NULL;
        if(editFlag != 0) {
            p_netmask = NETMASK_SET_TMP;
        } else {
            static uint8_t netmask_now[4] = {0};
            extern struct netif gnetif;
            netmask_now[0] = (gnetif.netmask.addr >> 0) & 0xff;
            netmask_now[1] = (gnetif.netmask.addr >> 8) & 0xff;
            netmask_now[2] = (gnetif.netmask.addr >> 16) & 0xff;
            netmask_now[3] = (gnetif.netmask.addr >> 24) & 0xff;
            p_netmask = netmask_now;
        }
        if(editFlag != 0) {
            lv_obj_set_state(button, LV_STATE_FOCUSED);
            lv_obj_set_state(obj, LV_STATE_FOCUSED);
            IP_Focus(obj, &editIdx, p_netmask);
        } else {
            lv_obj_set_state(button, LV_STATE_DEFAULT);
            lv_obj_set_state(obj, LV_STATE_DEFAULT);
            IP_Focus(obj, NULL, p_netmask);
        }
    }
}


/*
 * @brief       void DHCP_handler(lv_obj_t *obj, lv_event_t event)
 * @details     DHCP事件处理
 */
void DHCP_handler(lv_obj_t *obj, lv_event_t event)
{
    const valueString_Def valueStr[] = {
        {0, &mStr_OFF},
        {1, &mStr_ON},
        {0},
    };
    static uint8_t editFlag = 0;
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key) {
                case LV_KEY_UP:
                case LV_KEY_DOWN:
                case LV_KEY_ENCODER:
                case LV_KEY_ENTER: {
                    uint8_t temp = DHCP_SET_TMP;
                    temp = (temp + 1) % 2;
                    UI_IF_System_DHCP_Onoff(temp);
                }
                break;
                case LV_KEY_ESC:
                    editFlag = 0;
                    break;
            }
        }
        break;
        case LV_EVENT_CLICKED: {
            if(editFlag == 1) {
                uint8_t temp = DHCP_SET_TMP;
                temp = (temp + 1) % 2;
                UI_IF_System_DHCP_Onoff(temp);
            }
            editFlag = 1;
        }
        case LV_EVENT_REFRESH:
            break;
    }
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_DHCP));
    const char *str = valueStr_GetStr(DHCP_SET_TMP, valueStr);
    lv_label_set_text_static(obj, str);
    lv_obj_t *button = lv_obj_get_parent(obj);
    if(editFlag != 0) {
        lv_obj_set_state(button, LV_STATE_FOCUSED);
        lv_obj_set_state(obj, LV_STATE_FOCUSED);
        label_setSelStr(obj, str, str);
    } else {
        lv_obj_set_state(button, LV_STATE_DEFAULT);
        lv_obj_set_state(obj, LV_STATE_DEFAULT);
        lv_label_set_text_sel_start(obj, 0);
        lv_label_set_text_sel_end(obj, 0);
    }
}




/*
 * @brief       void Reboot_handler(lv_obj_t *obj, lv_event_t event)
 * @details     重启
 */
void Reboot_handler(lv_obj_t *obj, lv_event_t event)
{
    switch(event)
    {
        case LV_EVENT_CLICKED: {
            __disable_irq();
            NVIC_SystemReset();
        }
        break;
    }
}