#include "Trigger_Interface.h"



void IF_Trigger_Set_Mode(int8_t ch, int8_t mode)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_TRIGGER_SET_MODE;
    msg.data.trigger_param.ch = ch;
    msg.data.trigger_param.data_u8 = mode;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
/* -------------------- 输入模式配置 -------------------- */
void IF_Trigger_Set_In_Source(int8_t ch, int8_t source)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_TRIGGER_SET_IN_SOURCE;
    msg.data.trigger_param.ch = ch;
    msg.data.trigger_param.data_u8 = source;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
void IF_Trigger_Set_In_Type(int8_t ch, int8_t type)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_TRIGGER_SET_IN_TYPE;
    msg.data.trigger_param.ch = ch;
    msg.data.trigger_param.data_u8 = type;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
void IF_Trigger_Set_In_Sens(int8_t ch, int8_t Sens)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_TRIGGER_SET_IN_SENS;
    msg.data.trigger_param.ch = ch;
    msg.data.trigger_param.data_u8 = Sens;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
void IF_Trigger_Set_In_Response(int8_t ch, int8_t response)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_TRIGGER_SET_IN_RESPONSE;
    msg.data.trigger_param.ch = ch;
    msg.data.trigger_param.data_u8 = response;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}

/* -------------------- 输出模式配置 -------------------- */
void IF_Trigger_Set_Out_Source(int8_t ch, int8_t source)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_TRIGGER_SET_OUT_SOURCE;
    msg.data.trigger_param.ch = ch;
    msg.data.trigger_param.data_u8 = source;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
void IF_Trigger_Set_Out_Condition(int8_t ch, int8_t condition)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_TRIGGER_SET_OUT_CONDITION;
    msg.data.trigger_param.ch = ch;
    msg.data.trigger_param.data_u8 = condition;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
void IF_Trigger_Set_Out_Condition_Val(int8_t ch, float value)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_TRIGGER_SET_OUT_CONDITION_VAL;
    msg.data.trigger_param.ch = ch;
    msg.data.trigger_param.data_float = value;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
void IF_Trigger_Set_Out_Polarity(int8_t ch, int8_t polarity)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_TRIGGER_SET_OUT_POLARITY;
    msg.data.trigger_param.ch = ch;
    msg.data.trigger_param.data_u8 = polarity;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}






void UI_IF_Trigger_Set_Mode(int8_t ch, int8_t mode)
{
    if(!(TRIGGER_CH_MIN <= ch) || !(ch <= TRIGGER_CH_MAX)) {
        return;
    }
    if(!(TRIGGER_MODE_MIN <= mode) || !(mode <= TRIGGER_MODE_MAX)) {
        return;
    }
    Trigger[ch].mode = mode;
    lv_event_send_refresh(ui.TriggerPage_img_chSel);
}
/* -------------------- 输入模式配置 -------------------- */
void UI_IF_Trigger_Set_In_Source(int8_t ch, int8_t source)
{
    if(!(TRIGGER_CH_MIN <= ch) || !(ch <= TRIGGER_CH_MAX)) {
        return;
    }
    if(!(IN_SOURCE_MIN <= source) || !(source <= IN_SOURCE_MAX)) {
        return;
    }
    if(!(Trigger[ch].mode != TRIGGER_MODE_IN)) {
        return;
    }
    Trigger[ch].inConf.inSlave = source;
    if(lv_obj_is_visible(ui.TriggerPage_cont_1) == 0) {
        return ;
    }
    lv_event_send_refresh(ui.TriggerPage_cont_1);
}
void UI_IF_Trigger_Set_In_Type(int8_t ch, int8_t type)
{
    if(!(TRIGGER_CH_MIN <= ch) || !(ch <= TRIGGER_CH_MAX)) {
        return;
    }
    if(!(IN_TYPE_MIN <= type) || !(type <= IN_TYPE_MAX)) {
        return;
    }
    if(!(Trigger[ch].mode != TRIGGER_MODE_IN)) {
        return;
    }
    Trigger[ch].inConf.inType = type;
    if(lv_obj_is_visible(ui.TriggerPage_cont_1) == 0) {
        return ;
    }
    lv_event_send_refresh(ui.TriggerPage_cont_1);
}
void UI_IF_Trigger_Set_In_Sens(int8_t ch, int8_t Sens)
{
    if(!(TRIGGER_CH_MIN <= ch) || !(ch <= TRIGGER_CH_MAX)) {
        return;
    }
    if(!(IN_SENS_MIN <= Sens) || !(Sens <= IN_SENS_MAX)) {
        return;
    }
    if(!(Trigger[ch].mode != TRIGGER_MODE_IN)) {
        return;
    }
    Trigger[ch].inConf.inSens = Sens;
    if(lv_obj_is_visible(ui.TriggerPage_cont_1) == 0) {
        return ;
    }
    lv_event_send_refresh(ui.TriggerPage_cont_1);
}
void UI_IF_Trigger_Set_In_Response(int8_t ch, int8_t response)
{
    if(!(TRIGGER_CH_MIN <= ch) || !(ch <= TRIGGER_CH_MAX)) {
        return;
    }
    if(!(IN_RESP_MIN <= response) || !(response <= IN_RESP_MAX)) {
        return;
    }
    if(!(Trigger[ch].mode != TRIGGER_MODE_IN)) {
        return;
    }
    Trigger[ch].inConf.inRespon = response;
    if(lv_obj_is_visible(ui.TriggerPage_cont_1) == 0) {
        return ;
    }
    lv_event_send_refresh(ui.TriggerPage_cont_1);
}

/* -------------------- 输出模式配置 -------------------- */
void UI_IF_Trigger_Set_Out_Source(int8_t ch, int8_t source)
{
    if(!(TRIGGER_CH_MIN <= ch) || !(ch <= TRIGGER_CH_MAX)) {
        return;
    }
    if(!(OUT_SOURCE_MIN <= source) || !(source <= OUT_SOURCE_MAX)) {
        return;
    }
    if(!(Trigger[ch].mode != TRIGGER_MODE_OUT)) {
        return;
    }
    Trigger[ch].outConf.outSource = source;
    if(lv_obj_is_visible(ui.TriggerPage_cont_1) == 0) {
        return ;
    }
    lv_event_send_refresh(ui.TriggerPage_cont_1);
}
void UI_IF_Trigger_Set_Out_Condition(int8_t ch, int8_t condition)
{
    if(!(TRIGGER_CH_MIN <= ch) || !(ch <= TRIGGER_CH_MAX)) {
        return;
    }
    if(!(CONDITION_MIN <= condition) || !(condition <= CONDITION_MAX)) {
        return;
    }
    if(!(Trigger[ch].mode != TRIGGER_MODE_OUT)) {
        return;
    }
    Trigger[ch].outConf.condition = condition;
    if(lv_obj_is_visible(ui.TriggerPage_cont_1) == 0) {
        return ;
    }
    lv_event_send_refresh(ui.TriggerPage_cont_1);
}
void UI_IF_Trigger_Set_Out_Condition_Val(int8_t ch, float value)
{
    if(!(TRIGGER_CH_MIN <= ch) || !(ch <= TRIGGER_CH_MAX)) {
        return;
    }
    if(!(Trigger[ch].mode != TRIGGER_MODE_OUT)) {
        return;
    }
    uint8_t condition = Trigger[ch].outConf.condition;
    switch(condition)
    {
        case CONDITION_OUT_OFF:
            break;
        case CONDITION_OUT_ON:
            break;
        case CONDITION_V_MORE:
        case CONDITION_V_LESS:
        case CONDITION_V_EQUAL: {
            if(!(VOL_MIN <= value) || !(value <= VOL_MAX)) {
                return;
            }
            Trigger[ch].outConf.value.vol = value;
        }
        break;
        case CONDITION_C_LESS:
        case CONDITION_C_MORE:
        case CONDITION_C_EQUAL: {
            if(!(AMP_MIN <= value) || !(value <= AMP_MAX)) {
                return;
            }
            Trigger[ch].outConf.value.amp = value;
        }
        break;
        case CONDITION_P_LESS:
        case CONDITION_P_MORE:
        case CONDITION_P_EQUAL: {
            if(!(WAT_MIN <= value) || !(value <= WAT_MAX)) {
                return;
            }
            Trigger[ch].outConf.value.wat = value;
        }
        break;
    }
    if(lv_obj_is_visible(ui.TriggerPage_cont_1) == 0) {
        return ;
    }
    lv_event_send_refresh(ui.TriggerPage_cont_1);
}
void UI_IF_Trigger_Set_Out_Polarity(int8_t ch, int8_t polarity)
{
    if(!(TRIGGER_CH_MIN <= ch) || !(ch <= TRIGGER_CH_MAX)) {
        return;
    }
    if(!(POLARITY_MIN <= polarity) || !(polarity <= POLARITY_MAX)) {
        return;
    }
    if(!(Trigger[ch].mode != TRIGGER_MODE_OUT)) {
        return;
    }
    Trigger[ch].outConf.outPolarity = polarity;
    if(lv_obj_is_visible(ui.TriggerPage_cont_1) == 0) {
        return ;
    }
    lv_event_send_refresh(ui.TriggerPage_cont_1);
}





