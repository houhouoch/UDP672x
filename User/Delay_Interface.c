#include "Delay_Interface.h"


//设置List开关
void IF_Delay_Set_On_Off(uint8_t onoff)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_DELAYPAGE_SET_ONOFF;
    msg.data.data_u8 = onoff;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
//设置起始点
void IF_Delay_Set_Start(int32_t start)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_DELAYPAGE_SET_START;
    msg.data.data_u16 = start;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
//设置总点数
void IF_Delay_Set_Count(int32_t count)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_DELAYPAGE_SET_COUNT;
    msg.data.data_u16 = count;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
//设置循环次数
void IF_Delay_Set_Cycle(int32_t cycle)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_DELAYPAGE_SET_CYCLE;
    msg.data.data_u16 = cycle;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}

void IF_Delay_Set_Stop(int8_t stop)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_DELAYPAGE_SET_STOP;
    msg.data.data_u8 = stop;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}

void IF_Delay_Set_StopValue(float value)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_DELAYPAGE_SET_STOPVAL;
    msg.data.data_float = value;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}

//设置结束状态:Hold/Off
void IF_Delay_Set_lastState(int8_t laststate)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_DELAYPAGE_SET_ENDSTATE;
    msg.data.data_u8 = laststate;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}


void IF_Delay_Set_PointParam(int32_t idx, uint8_t onoff, float time)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_DELAYPAGE_SET_PARAM;
    msg.data.delay_param.idx = idx;
    msg.data.delay_param.onoff = onoff;
    msg.data.delay_param.time = time;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}


/* ----------------------- Delay --------------------- */

void IF_Delay_Refresh_RemainTime(void)
{
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_DELAYOUT_REMAINTIME;
    CMD_MsgQueue_Send(&msg);
}

/*
 * @brief       void IF_DelayOut_Set_CurIdx(uint16_t value)
 * @details     DelayOut显示当前位置
 */
void IF_DelayOut_Set_CurIdx(uint16_t value)
{
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_DELAYOUT_SET_CURIDX;
    msg.data.data_u16 = value;
    CMD_MsgQueue_Send(&msg);
}

/*
 * @brief       void IF_DelayOut_Set_Loop(uint16_t value)
 * @details     DelayOut显示已循环次数
 */
void IF_DelayOut_Set_Loop(uint16_t value)
{
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_DELAYOUT_SET_LOOP;
    msg.data.data_u16 = value;
    CMD_MsgQueue_Send(&msg);
}

/*
 * @brief       void IF_DelayOut_Set_State(uint16_t value)
 * @details     DelayOut设置当前状态
 */
void IF_DelayOut_Set_State(uint16_t value)
{
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_DELAYOUT_SET_STATE;
    msg.data.data_u16 = value;
    CMD_MsgQueue_Send(&msg);
}


/* ---------------------------------------------------------- */


void UI_IF_Delay_Set_On_Off(uint8_t onoff)
{
    //设置
    if(onoff != 0) {
        IF_DelayOut_Set_State(DELAY_STATE_RUNNING);
    } else {
        IF_DelayOut_Set_State(DELAY_STATE_STOP);
    }
}


void UI_IF_Delay_Set_Start(int32_t start)
{
    if(DELAY_POINT_MIN > start) {
        start = DELAY_POINT_MIN;
    } else
        if(start > (DELAY_POINT_MAX - delayoutInfo.countpoint)) {
            start = (DELAY_POINT_MAX - delayoutInfo.countpoint);
            IF_MsgBox_Tips_Mult(&mStr_DelaySet_MaxPoint);
        }
    delayoutInfo.startpoint = start;
    lv_event_send_refresh(ui.DelayPage_btn_start_label);
    lv_event_send_refresh(ui.DelayPage_cont_Table);
}

void UI_IF_Delay_Set_Count(int32_t count)
{
    if(DELAY_POINT_COUNT_MIN > count) {
        count = DELAY_POINT_COUNT_MIN;
    } else
        if(count > (DELAY_POINT_MAX - delayoutInfo.startpoint)) {
            count = (DELAY_POINT_MAX - delayoutInfo.startpoint);
            IF_MsgBox_Tips_Mult(&mStr_DelaySet_MaxPoint);
        }
    delayoutInfo.countpoint = count;
    lv_event_send_refresh(ui.DelayPage_btn_count_label);
    //    lv_event_send_refresh(ui.DelayPage_cont_Table);
}

void UI_IF_Delay_Set_Cycle(int32_t cycle)
{
    if(CYCLE_MIN > cycle) {
        cycle = CYCLE_MIN;
    } else
        if(cycle > CYCLE_MAX) {
            cycle = CYCLE_MAX;
            IF_MsgBox_Tips_Mult(&mStr_DelaySet_MaxCycles);
        }
    delayoutInfo.cycles = cycle;
    lv_event_send_refresh(ui.DelayPage_btn_cycle_label);
}

void UI_IF_Delay_Set_Stop(int8_t stop)
{
    if((DELAY_STOP_MIN <= stop) && (stop <= DELAY_STOP_MAX)) {
        delayoutInfo.stopCfg.stop = stop;
        lv_event_send_refresh(ui.DelayPage_btn_stopVal_label);
    }
}

void UI_IF_Delay_Set_StopValue(float value)
{
    switch(delayoutInfo.stopCfg.stop) {
        case DELAY_STOP_LESS_V:
        case DELAY_STOP_MORE_V: {
            if(VOL_MIN > value) {
                delayoutInfo.stopCfg.vol = VOL_MIN;
            } else
                if(value > VOL_MAX) {
                    delayoutInfo.stopCfg.vol = VOL_MAX;
                    IF_MsgBox_Tips_Mult(&mStr_OutSet_MaxVol);
                } else {
                    delayoutInfo.stopCfg.vol = value;
                }
        }
        break;
        case DELAY_STOP_LESS_C:
        case DELAY_STOP_MORE_C: {
            if(AMP_MIN > value) {
                delayoutInfo.stopCfg.amp = AMP_MIN;
            } else
                if(value > AMP_MAX) {
                    delayoutInfo.stopCfg.amp = AMP_MAX;
                    IF_MsgBox_Tips_Mult(&mStr_OutSet_MaxAmp);
                } else {
                    delayoutInfo.stopCfg.amp = value;
                }
        }
        break;
        case DELAY_STOP_LESS_P:
        case DELAY_STOP_MORE_P: {
            if(WAT_MIN > value) {
                delayoutInfo.stopCfg.wat = WAT_MIN;
            } else
                if(value > WAT_MAX) {
                    delayoutInfo.stopCfg.wat = WAT_MAX;
                    IF_MsgBox_Tips_Mult(&mStr_OutSet_MaxWat);
                } else {
                    delayoutInfo.stopCfg.wat = value;
                }
        }
        break;
    }
    lv_event_send_refresh(ui.DelayPage_btn_stopVal_label);
}

void UI_IF_Delay_Set_lastState(int8_t laststate)
{
    if((DELAY_ENDSTATE_MIN <= laststate) && (laststate <= DELAY_ENDSTATE_MAX)) {
        delayoutInfo.lastState = laststate;
        lv_event_send_refresh(ui.DelayPage_btn_lastState_label);
    }
}


#define VALUE_LIMIT(A,B,C)  \
    do{                     \
        A = MAX(A,B);       \
        A = MIN(A,C);       \
    }while(0)

void UI_IF_Delay_Set_PointParam(int32_t idx, uint8_t onoff, float time)
{
    if((DELAY_POINT_MIN <= idx) && (idx <= DELAY_POINT_MAX))
    {
        VALUE_LIMIT(time, KT_MIN, KT_MAX);
        delayoutInfo.points[idx].out = onoff;
        delayoutInfo.points[idx].dT = time;
        lv_event_send_refresh_recursive(ui.DelayPage_cont_Table);
    }
}

#include "TIM.h"
#include "DelayOut.h"
#include "DelayOutPage.h"
#include "DelayOutPage_Table.h"
#include "DelayPage_Option.h"

void UI_IF_Delay_Refresh_RemainTime(void)
{
    uint16_t cur = delayoutInfo.current;
    float progress = 1000 * delayoutInfo.holdtime / delayoutInfo.points[cur].dT;
    lv_bar_set_value(ui.DelayPage_bar, progress, LV_ANIM_ON);
}

/*
 * @brief       void UI_IF_Delay_Set_CurIdx(uint16_t value)
 * @details     设置当前Delay运行索引
 */
void UI_IF_Delay_Set_CurIdx(uint16_t value)
{
    delayoutInfo.current = value;
    if(lv_obj_is_visible(ui.DelayPage_cont_setParam) != 0) {
        char buffer[16] = {0};
        sprintf(buffer, POINT_DISP_FORM, value);
        lv_label_set_text(ui.DelayPage_btn_current_label, buffer);
        DelayPage_SetCurrent(value);
    }
}
/*
 * @brief       void UI_IF_Delay_Set_Loop(uint16_t value)
 * @details     设置当前Delay运行循环数
 */
void UI_IF_Delay_Set_Loop(uint16_t value)
{
    delayoutInfo.loop = value;
    static char buffer[16] = {0};
    sprintf(buffer, POINT_DISP_FORM, value);
    if(lv_obj_is_visible(ui.DelayPage_cont_setParam) != 0) {
        lv_label_set_text_static(ui.DelayPage_btn_loop_label, buffer);
    }
}
/*
 * @brief       void UI_IF_Delay_Set_State(uint16_t value)
 * @details     设置当前Delay运行状态
 */
void UI_IF_Delay_Set_State(uint16_t value)
{
    if(delayoutInfo.state == value) {
        return ;
    }
    switch(value)
    {
        case DELAY_STATE_RUNNING: {
            if(delayoutInfo.state != DELAY_STATE_RUNNING)
            {
                delayoutInfo.enable = 1;
                //                if(delayoutInfo.state != DELAY_STATE_HALT)
                {
                    delayoutInfo.current = delayoutInfo.startpoint;
                    delayoutInfo.loop = 0;
                    UI_IF_Delay_Set_CurIdx(delayoutInfo.current);
                    UI_IF_Delay_Set_Loop(delayoutInfo.loop);
                    IF_Power_OVP_Clean();
                    IF_Power_OCP_Clean();
                    UI_IF_Power_OnOff(delayoutInfo.points[0].out);
                }
                delayoutInfo.state = DELAY_STATE_RUNNING;
                Tree_Btnm_Replace(tree_delay, &btn_start, &btn_stop);
                Tree_Btnm_Replace(tree_delay, &btn_contiune, &btn_stop);
                delayoutInfo.tickRun = 1;
            }
        }
        break;
        case DELAY_STATE_HALT: {
            delayoutInfo.enable = 0;
            delayoutInfo.state = DELAY_STATE_HALT;
            //            Tree_Btnm_Replace(tree_delay, &btn_stop, &btn_contiune);
            //停止输出
            if(delayoutInfo.lastState == DELAY_ENDSTATE_ON) {
                UI_IF_Power_OnOff(1);
            } else
                if(delayoutInfo.lastState == DELAY_ENDSTATE_OFF) {
                    UI_IF_Power_OnOff(0);
                }
            //显示提示框
            IF_MsgBox_Tips_Mult(&mStr_delay_halt);
        }
        break;
        case DELAY_STATE_STOP: {
            //停止输出
            if(delayoutInfo.enable != 0) {
                if(delayoutInfo.lastState == DELAY_ENDSTATE_ON) {
                    UI_IF_Power_OnOff(1);
                } else
                    if(delayoutInfo.lastState == DELAY_ENDSTATE_OFF) {
                        UI_IF_Power_OnOff(0);
                    }
            }
            delayoutInfo.enable = 0;
            delayoutInfo.state = DELAY_STATE_STOP;
            Tree_Btnm_Replace(tree_delay, &btn_stop, &btn_start);
            Tree_Btnm_Replace(tree_delay, &btn_contiune, &btn_start);
            delayoutInfo.tickRun = 0;
        }
        break;
    }
    //若运行,Home页显示
    if(DelayOut_IsRunning()) {
        lv_label_set_text_static(ui.Bar_btn_List_Dly_label, "Delay");
        lv_obj_set_hidden(ui.Bar_btn_List_Dly, 0);
        lv_obj_set_hidden(ui.DelayPage_bar, 0);
        lv_color_t color = {0};
        switch(value) {
            case DELAY_STATE_RUNNING:
                color = lv_color_make(0, 255, 0);
                break;
            case DELAY_STATE_HALT:
                color = lv_color_make(255, 255, 0);
                break;
            case DELAY_STATE_STOP:
                color = lv_color_make(255, 0, 0);
                break;
        }
        lv_obj_set_style_local_text_color(ui.Bar_btn_List_Dly_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, color);
    } else {
        lv_obj_set_hidden(ui.Bar_btn_List_Dly, 1);
        lv_obj_set_hidden(ui.DelayPage_bar, 1);
    }
}
