#include "DelayTemp_Interface.h"




void IF_DelayTemp_Set_Type(int8_t temp_type)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_DELAYTEMP_SET_TYPE;
    msg.data.data_u8 = temp_type;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
void IF_DelayTemp_Set_Code(int8_t code)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_DELAYTEMP_SET_CODE;
    msg.data.data_u8 = code;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
void IF_DelayTemp_Set_Start(int16_t start)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_DELAYTEMP_SET_START;
    msg.data.data_u16 = start;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
void IF_DelayTemp_Set_Count(int16_t count)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_DELAYTEMP_SET_COUNT;
    msg.data.data_u16 = count;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
void IF_DelayTemp_Set_Ton(float Ton)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_DELAYTEMP_SET_TON;
    msg.data.data_float = Ton;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
void IF_DelayTemp_Set_Toff(float Toff)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_DELAYTEMP_SET_TOFF;
    msg.data.data_float = Toff;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
void IF_DelayTemp_Set_Base(float baseT)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_DELAYTEMP_SET_TBASE;
    msg.data.data_float = baseT;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
void IF_DelayTemp_Set_Step(float stepT)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_DELAYTEMP_SET_TSTEP;
    msg.data.data_float = stepT;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
void IF_DelayTemp_Generate(void)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_DELAYTEMP_GENERATE;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}




void UI_IF_DelayTemp_Set_Type(int8_t temp_type)
{
    if((temp_type >= DELAYTEMP_TYPE_MIN) && (temp_type <= DELAYTEMP_TYPE_MAX)) {
        Delay_Temp_Set_Type(temp_type);
    }
    lv_event_send_refresh_recursive(ui.DelayTempPage_cont_1);
}

void UI_IF_DelayTemp_Set_Code(int8_t code)
{
    if((code >= DELAYTEMP_CODE_MIN) && (code <= DELAYTEMP_CODE_MAX)) {
        DelayTempInfo.code = code;
    }
    lv_event_send_refresh_recursive(ui.DelayTempPage_btn_param1_label);
}

void UI_IF_DelayTemp_Set_Start(int16_t start)
{
    int16_t min = 0;
    int16_t max = (DELAYOUT_MAX_COUNT - DelayTempInfo.totalCount);
    if(start < min) {
        start = min;
    } else
        if(start > max) {
            start = max;
        }
    DelayTempInfo.startpoint = start;
    lv_event_send_refresh_recursive(ui.DelayTempPage_btn_start_label);
}

void UI_IF_DelayTemp_Set_Count(int16_t count)
{
    int16_t min = 2;
    int16_t max = (DELAYOUT_MAX_COUNT - DelayTempInfo.startpoint);
    if(count < min) {
        count = min;
    } else
        if(count > max) {
            count = max;
        }
    DelayTempInfo.totalCount = count;
    lv_event_send_refresh_recursive(ui.DelayTempPage_btn_count_label);
}

void UI_IF_DelayTemp_Set_Ton(float Ton)
{
    float min = 0.1f;
    float max = DT_MAX;
    if(Ton < min) {
        Ton = min;
    } else
        if(Ton > max) {
            Ton = max;
        }
    DelayTempInfo.fix.time_on = Ton;
    lv_event_send_refresh_recursive(ui.DelayTempPage_btn_param1_label);
}
void UI_IF_DelayTemp_Set_Toff(float Toff)
{
    float min = 0.1f;
    float max = DT_MAX;
    if(Toff < min) {
        Toff = min;
    } else
        if(Toff > max) {
            Toff = max;
        }
    DelayTempInfo.fix.time_off = Toff;
    lv_event_send_refresh_recursive(ui.DelayTempPage_btn_param2_label);
}


void UI_IF_DelayTemp_Set_Base(float baseT)
{
    float min = 0.1f;
    float max = DT_MAX;
    if(baseT < min) {
        baseT = min;
    } else
        if(baseT > max) {
            baseT = max;
        }
    DelayTempInfo.inc_dec.time_base = baseT;
    lv_event_send_refresh_recursive(ui.DelayTempPage_btn_param1_label);
}
void UI_IF_DelayTemp_Set_Step(float stepT)
{
    float min = 0.1f;
    float max = DT_MAX;
    if(stepT < min) {
        stepT = min;
    } else
        if(stepT > max) {
            stepT = max;
        }
    DelayTempInfo.inc_dec.time_step = stepT;
    lv_event_send_refresh_recursive(ui.DelayTempPage_btn_param2_label);
}

void UI_IF_DelayTemp_Generate(void)
{
    Delay_Temp_Generate();
    IF_MsgBox_Tips_Mult(&mStr_Delay_Temp_Generted);
}


