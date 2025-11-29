#include "ListTemp_Interface.h"

void IF_ListTemp_Set_Type(int8_t temp_type)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_LISTTEMP_SET_TYPE;
    msg.data.data_u8 = temp_type;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}

void IF_ListTemp_Set_Object(int8_t object)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_LISTTEMP_SET_OBJ;
    msg.data.data_u8 = object;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}

void IF_ListTemp_Set_MaxValue(float value)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_LISTTEMP_SET_MAX;
    msg.data.data_float = value;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}

void IF_ListTemp_Set_MinValue(float value)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_LISTTEMP_SET_MIN;
    msg.data.data_float = value;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}

void IF_ListTemp_Set_Count(int16_t count)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_LISTTEMP_SET_COUNT;
    msg.data.data_u16 = count;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}

void IF_ListTemp_Set_Start(int16_t start)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_LISTTEMP_SET_START;
    msg.data.data_u16 = start;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}

void IF_ListTemp_Set_Interval(float value)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_LISTTEMP_SET_INTERVAL;
    msg.data.data_float = value;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}

void IF_ListTemp_Set_Invert(uint8_t invert)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_LISTTEMP_SET_INVERT;
    msg.data.data_u8 = invert;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}

void IF_ListTemp_Set_Period(float period)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_LISTTEMP_SET_PLUSE_PERIOD;
    msg.data.data_float = period;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}

void IF_ListTemp_Set_Width(float width)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_LISTTEMP_SET_PLUSE_WIDTH;
    msg.data.data_float = width;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}

void IF_ListTemp_Set_Symmetry(uint8_t Symmetry)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_LISTTEMP_SET_SYMMETRY;
    msg.data.data_u8 = Symmetry;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}

void IF_ListTemp_Set_expValue(uint8_t value)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_LISTTEMP_SET_EXPRATE;
    msg.data.data_u8 = value;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}

void IF_ListTemp_Generate(void)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_LISTTEMP_GENERATE;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}


/* ---------------------------------------------------------- */


//设置List模板类型
void UI_IF_ListTemp_Set_Type(int8_t temp_type)
{
    if((TEMP_TYPE_MIN <= temp_type) && (temp_type <= TEMP_TYPE_MAX)) {
        //恢复
        static int32_t tempCount = 0;
        if(ListTempInfo.param[ListTempInfo.edit_obj].temp_type == TEMP_TYPE_Pulse) {
            ListTempInfo.totalCount = tempCount;
        }
        ListTempInfo.param[ListTempInfo.edit_obj].temp_type = temp_type;
        //保存之前的点数
        if(ListTempInfo.param[ListTempInfo.edit_obj].temp_type == TEMP_TYPE_Pulse) {
            tempCount = ListTempInfo.totalCount;
            ListTempInfo.totalCount = 2;
        }
        lv_event_send_refresh_recursive(ui.ListTempPage_btn_type_label);
    }
}
//设置List模板变量
void UI_IF_ListTemp_Set_Object(int8_t object)
{
    if((LISTTEMP_EDIT_OBJECT_MIN <= object) && (object <= LISTTEMP_EDIT_OBJECT_MAX)) {
        ListTempInfo.edit_obj = object;
        lv_event_send_refresh_recursive(ui.ListTempPage_btn_obj_label);
    }
}

//设置List模板的最大值
void UI_IF_ListTemp_Set_MaxValue(float value)
{
    float max = 0;
    if(ListTempInfo.edit_obj == LISTTEMP_EDIT_OBJECT_VOL) {
        max = VOL_MAX;
    } else
        if(ListTempInfo.edit_obj == LISTTEMP_EDIT_OBJECT_AMP) {
            max = AMP_MAX;
        }
    if(value <= max) {
        ListTempInfo.param[ListTempInfo.edit_obj].maxValue = value;
    }
    lv_event_send_refresh_recursive(ui.ListTempPage_btn_maxValue_label);
}

//设置List模板的最小值
void UI_IF_ListTemp_Set_MinValue(float value)
{
    float min = 0;
    if(ListTempInfo.edit_obj == LISTTEMP_EDIT_OBJECT_VOL) {
        min = VOL_MIN;
    } else
        if(ListTempInfo.edit_obj == LISTTEMP_EDIT_OBJECT_AMP) {
            min = AMP_MIN;
        }
    if(value >= min) {
        ListTempInfo.param[ListTempInfo.edit_obj].minValue = value;
    }
    lv_event_send_refresh_recursive(ui.ListTempPage_btn_minValue_label);
}

//设置List模板的总点数
void UI_IF_ListTemp_Set_Count(int16_t count)
{
    if((count < 0) || (count > (LISTOUT_MAX_COUNT - ListTempInfo.startpoint))) {
        return ;
    }
    int16_t min = LIST_POINT_COUNT_MIN;
    int16_t max = (LISTOUT_MAX_COUNT - ListTempInfo.startpoint);
    if(ListTempInfo.param[ListTempInfo.edit_obj].temp_type == TEMP_TYPE_Pulse) {
        max = 2;
        min = 2;
    }
    if(count < min) {
        count = min;
    } else
        if(count > max) {
            count = max;
            IF_MsgBox_Tips_Mult(&mStr_ListSet_MaxPoint);
        }
    ListTempInfo.totalCount = count;
    lv_event_send_refresh_recursive(ui.ListTempPage_btn_cout_label);
}

//设置List模板的起始点
void UI_IF_ListTemp_Set_Start(int16_t start)
{
    int16_t min = LIST_POINT_MIN;
    int16_t max = (LISTOUT_MAX_COUNT - ListTempInfo.totalCount);
    if(start < min) {
        start = min;
    } else
        if(start > max) {
            start = max;
            IF_MsgBox_Tips_Mult(&mStr_ListSet_MaxPoint);
        }
    ListTempInfo.startpoint = start;
    lv_event_send_refresh_recursive(ui.ListTempPage_btn_start_label);
}


//设置List模板的时间间隔
void UI_IF_ListTemp_Set_Interval(float value)
{
    float min = KT_MIN;
    float max = KT_MAX;
    if(value < min) {
        value = min;
    } else
        if(value > max) {
            value = max;
            IF_MsgBox_Tips_Mult(&mStr_ListSet_MaxkT);
        }
    ListTempInfo.interval = value;
    lv_event_send_refresh_recursive(ui.ListTempPage_btn_0_label);
}

//设置List模板的反相
void UI_IF_ListTemp_Set_Invert(uint8_t invert)
{
    switch(ListTempInfo.param[ListTempInfo.edit_obj].temp_type) {
        case TEMP_TYPE_Sin:
        case TEMP_TYPE_Pulse:
        case TEMP_TYPE_Ramp:
            break;
        default:
            IF_MsgBox_Tips_Mult(&mStr_ListTemp_InvalidParam);
            return;
    }
    ListTempInfo.param[ListTempInfo.edit_obj].invert = (invert != 0);
    lv_event_send_refresh_recursive(ui.ListTempPage_cont_1);
}

///
//在此添加 脉冲波形的配置
void UI_IF_ListTemp_Set_Period(float period)
{
    switch(ListTempInfo.param[ListTempInfo.edit_obj].temp_type) {
        case TEMP_TYPE_Pulse:
            break;
        default:
            IF_MsgBox_Tips_Mult(&mStr_ListTemp_InvalidParam);
            return;
    }
    float min = ListTempInfo.param[ListTempInfo.edit_obj].pluseWidth;
    float max = KT_MAX;
    if(period < min) {
        period = min;
    } else
        if(period > max) {
            period = max;
            IF_MsgBox_Tips_Mult(&mStr_ListTemp_MaxPeriod);
        }
    ListTempInfo.param[ListTempInfo.edit_obj].plusePeriod = period;
    lv_event_send_refresh_recursive(ui.ListTempPage_cont_1);
}
void UI_IF_ListTemp_Set_Width(float width)
{
    switch(ListTempInfo.param[ListTempInfo.edit_obj].temp_type) {
        case TEMP_TYPE_Pulse:
            break;
        default:
            IF_MsgBox_Tips_Mult(&mStr_ListTemp_InvalidParam);
            return;
    }
    float min = KT_MIN;
    float max = ListTempInfo.param[ListTempInfo.edit_obj].plusePeriod;
    if(width < min) {
        width = min;
    } else
        if(width > max) {
            width = max;
            IF_MsgBox_Tips_Mult(&mStr_ListTemp_MaxWidth);
        }
    ListTempInfo.param[ListTempInfo.edit_obj].pluseWidth = width;
    lv_event_send_refresh_recursive(ui.ListTempPage_cont_1);
}
///


//设置List模板的斜波对称
void UI_IF_ListTemp_Set_Symmetry(uint8_t Symmetry)
{
    switch(ListTempInfo.param[ListTempInfo.edit_obj].temp_type) {
        case TEMP_TYPE_Ramp:
            break;
        default:
            IF_MsgBox_Tips_Mult(&mStr_ListTemp_InvalidParam);
            return;
    }
    if(Symmetry < SYMMETRY_MIN) {
        Symmetry = SYMMETRY_MIN;
    } else
        if(Symmetry > SYMMETRY_MAX) {
            Symmetry = SYMMETRY_MAX;
            IF_MsgBox_Tips_Mult(&mStr_ListTemp_MaxSymmetry);
        }
    ListTempInfo.param[ListTempInfo.edit_obj].Symmetry = Symmetry;
    lv_event_send_refresh_recursive(ui.ListTempPage_cont_1);
}

//设置List模板的指数
void UI_IF_ListTemp_Set_expValue(uint8_t value)
{
    switch(ListTempInfo.param[ListTempInfo.edit_obj].temp_type) {
        case TEMP_TYPE_expUp:
        case TEMP_TYPE_expDown:
            break;
        default:
            IF_MsgBox_Tips_Mult(&mStr_ListTemp_InvalidParam);
            return;
    }
    if(value < EXP_VALUE_MIN) {
        value = EXP_VALUE_MIN;
    } else
        if(value > EXP_VALUE_MAX) {
            value = EXP_VALUE_MAX;
            IF_MsgBox_Tips_Mult(&mStr_ListTemp_MaxExp);
        }
    ListTempInfo.param[ListTempInfo.edit_obj].expValue = value;
    lv_event_send_refresh_recursive(ui.ListTempPage_cont_1);
}

void UI_IF_ListTemp_Generate(void)
{
    ListTempPage_Generate();
    IF_MsgBox_Tips_Mult(&mStr_List_Temp_Generted);
}


