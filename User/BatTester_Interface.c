//无List

#include "BatTester_Interface.h"


void IF_BatTester_Set_Editable(uint8_t editable)
{
    BatTester.editable = editable;
}
uint8_t IF_BatTester_Get_Editable(void)
{
    return BatTester.editable;
}


//设置BatteryTester开关
void IF_BatTester_Set_On_Off(uint8_t onoff)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_BATTESTER_SET_ONOFF;
    msg.data.data_u8 = onoff;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
//设置起始点
void IF_BatTester_Set_Start(int32_t start)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_BATTESTER_SET_START;
    msg.data.data_u16 = start;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
//设置总点数
void IF_BatTester_Set_Count(int32_t count)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_BATTESTER_SET_COUNT;
    msg.data.data_u16 = count;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
//设置循环次数
void IF_BatTester_Set_Cycle(int32_t cycle)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_BATTESTER_SET_CYCLE;
    msg.data.data_u16 = cycle;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
//设置结束状态:Hold/Off
void IF_BatTester_Set_lastState(int8_t laststate)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_BATTESTER_SET_ENDSTATE;
    msg.data.data_u8 = laststate;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}


void IF_BatTester_Set_PointParam(int32_t idx, float volt, float curr, float time)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_BATTESTER_SET_PARAM;
    msg.data.battest_param.idx = idx;
    msg.data.battest_param.vol = volt;
    msg.data.battest_param.amp = curr;
    msg.data.battest_param.time = time;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}



/* ----------------------- BatteryTester --------------------- */
/*
 * @brief       void IF_BatTester_Set(float vol,float amp)
 * @details     BatTester设置输出
 */
void IF_BatTester_Set(float vol, float amp)
{
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_BATTESTER_SET;
    msg.data.power.vol = vol;
    msg.data.power.amp = amp;
    CMD_MsgQueue_Send(&msg);
}

void IF_BatTester_Refresh_RemainTime(void)
{
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_BATTESTER_REMAINTIME;
    CMD_MsgQueue_Send(&msg);
}

/*
 * @brief       void IF_BatTester_Set_CurIdx(uint16_t value)
 * @details     BatTester显示当前位置
 */
void IF_BatTester_Set_CurIdx(uint16_t value)
{
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_BATTESTER_SET_CURIDX;
    msg.data.data_u16 = value;
    CMD_MsgQueue_Send(&msg);
}

/*
 * @brief       void IF_BatTester_Set_Loop(uint16_t value)
 * @details     BatTester显示已循环次数
 */
void IF_BatTester_Set_Loop(uint16_t value)
{
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_BATTESTER_SET_LOOP;
    msg.data.data_u16 = value;
    CMD_MsgQueue_Send(&msg);
}

/*
 * @brief       void IF_BatTester_Set_State(uint16_t value)
 * @details     BatTester设置当前状态
 */
void IF_BatTester_Set_State(uint16_t value)
{
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_BATTESTER_SET_STATE;
    msg.data.data_u16 = value;
    CMD_MsgQueue_Send(&msg);
}



/* ---------------------------------------------------------- */


void UI_IF_BatTester_Set_On_Off(uint8_t onoff)
{
    //设置
    if(onoff != 0) {
        //        IF_BatTester_Set_State(BAT_TESTER_STATE_RUNNING);
        UI_IF_BatTester_Set_State(BAT_TESTER_STATE_RUNNING);
    } else {
        //        IF_BatTester_Set_State(BAT_TESTER_STATE_STOP);
        UI_IF_BatTester_Set_State(BAT_TESTER_STATE_STOP);
    }
}


void UI_IF_BatTester_Set_Start(int32_t start)
{
    if(BAT_TESTER_POINT_MIN > start) {
        start = BAT_TESTER_POINT_MIN;
    } else
        if(start > (BAT_TESTER_MAX_COUNT - BatTester.countpoint)) {
            start = (BAT_TESTER_MAX_COUNT - BatTester.countpoint);
            IF_MsgBox_Tips_Mult(&mStr_BatTester_MaxPoint);
        }
    BatTester.startpoint = start;
    lv_event_send_refresh(ui.BatTester_btn_start_label);
}

void UI_IF_BatTester_Set_Count(int32_t count)
{
    if(BAT_TESTER_POINT_COUNT_MIN > count) {
        count = BAT_TESTER_POINT_COUNT_MIN;
    } else
        if(count > (BAT_TESTER_MAX_COUNT - BatTester.startpoint)) {
            count = (BAT_TESTER_MAX_COUNT - BatTester.startpoint);
            IF_MsgBox_Tips_Mult(&mStr_BatTester_MaxPoint);
        }
    BatTester.countpoint = count;
    lv_event_send_refresh(ui.BatTester_btn_count_label);
}

void UI_IF_BatTester_Set_Cycle(int32_t cycle)
{
    if(CYCLE_MIN > cycle) {
        cycle = CYCLE_MIN;
    } else
        if(cycle > CYCLE_MAX) {
            cycle = CYCLE_MAX;
            IF_MsgBox_Tips_Mult(&mStr_BatTester_MaxCycles);
        }
    BatTester.cycles = cycle;
    lv_event_send_refresh(ui.BatTester_btn_cycle_label);
}


#define VALUE_LIMIT(A,B,C)  \
    do{                     \
        A = MAX(A,B);       \
        A = MIN(A,C);        \
    }while(0)

void UI_IF_BatTester_Set_PointParam(int32_t idx, float volt, float curr, float time)
{
    if((BAT_TESTER_POINT_MIN <= idx) && (idx <= BAT_TESTER_MAX_COUNT))
    {
        VALUE_LIMIT(volt, VOL_MIN, VOL_MAX);
        VALUE_LIMIT(curr, AMP_MIN, AMP_MAX);
        VALUE_LIMIT(time, KT_MIN, KT_MAX);
        BatTester.points[idx].vol = volt;
        BatTester.points[idx].amp = curr;
        BatTester.points[idx].kT = time;
        lv_event_send_refresh_recursive(ui.BatTester_cont_Table);
    }
}




#include "TIM.h"
#include "BatTester.h"
#include "BatTesterPage.h"
#include "BatTesterPage_Table.h"
//#include "ListPage_Option.h"

void UI_IF_BatTester_Refresh_RemainTime(void)
{
    uint16_t cur = BatTester.current;
    float progress = 1000 * BatTester.holdtime / BatTester.points[cur].kT;
    lv_bar_set_value(ui.BatTester_bar, progress, LV_ANIM_ON);
}

/*
 * @brief       void UI_IF_BatTester_Set_CurIdx(uint16_t value)
 * @details     设置当前BatTester运行索引
 */
void UI_IF_BatTester_Set_CurIdx(uint16_t value)
{
    BatTester.current = value;
    if(lv_obj_is_visible(ui.BatTester_cont_setParam) != 0) {
        static char buffer[16] = {0};
        sprintf(buffer, POINT_DISP_FORM, value);
        lv_label_set_text_static(ui.BatTester_btn_current_label, buffer);
        BatteryTester_Page_SetCurrent(value);
    }
}
/*
 * @brief       void UI_IF_BatTester_Set_Loop(uint16_t value)
 * @details     设置当前BatTester运行循环数
 */
void UI_IF_BatTester_Set_Loop(uint16_t value)
{
    BatTester.loop = value;
    static char buffer[16] = {0};
    sprintf(buffer, POINT_DISP_FORM, value);
    if(lv_obj_is_visible(ui.BatTester_cont_setParam) != 0) {
        lv_label_set_text_static(ui.BatTester_btn_loop_label, buffer);
    }
}
/*
 * @brief       void UI_IF_BatTester_Set_State(uint16_t value)
 * @details     设置当前BatTester运行状态
 */
void UI_IF_BatTester_Set_State(uint16_t value)
{
    if(BatTester.state == value) {
        return ;
    }
    switch(value)
    {
        case BAT_TESTER_STATE_COMPLETED: {
            BatTester.tickRun = 0;
            BatTester.trigTime_now = 0;
            BatTester.holdtime = 0;
            //BatTester.errorFlag = 0;
            //停止输出
            if(BatTester.enable != 0) {
                UI_IF_Power_Set_On_Off(0);
            }
            BatTester.enable = 0;
            BatTester.state = BAT_TESTER_STATE_COMPLETED;
            Tree_Btnm_Replace(tree_BatTester, &btn_stop, &btn_start);
            //功能开关
            if(tree_BatTester_btn_pause != NULL) {
                Tree_Delete(tree_BatTester, tree_BatTester_btn_pause);
                tree_BatTester_btn_pause = NULL;
            }
            Tree_Btnm_Refresh();
        }
        break;
        case BAT_TESTER_STATE_RUNNING: {
            if(BatTester.state != BAT_TESTER_STATE_RUNNING)
            {
                uint8_t state = BatTester.state;
                BatTester.enable = 1;
                BatTester.state = BAT_TESTER_STATE_RUNNING;
                if(state != BAT_TESTER_STATE_PAUSE)
                {
                    BatTester.current = BatTester.startpoint;
                    BatTester.loop = 0;
                    UI_IF_BatTester_Set_CurIdx(BatTester.current);
                    UI_IF_BatTester_Set_Loop(BatTester.loop);
                    UI_IF_Power_SetVol(BatTester.points[0].vol);
                    UI_IF_Power_SetAmp(BatTester.points[0].amp);
                }
                IF_Power_OVP_Clean();
                IF_Power_OCP_Clean();
                UI_IF_Power_Set_On_Off(1);
                Tree_Btnm_Replace(tree_BatTester, &btn_start, &btn_stop);
                Tree_Btnm_Replace(tree_BatTester, &btn_contiune, &btn_pause);
                //功能开关
                if(tree_BatTester_btn_pause == NULL) {
                    tree_BatTester_btn_pause = Tree_AddNode(tree_BatTester, &btn_pause);
                }
                Tree_Btnm_Refresh();
            }
            BatTester.tickRun = 1;
        }
        break;
        case BAT_TESTER_STATE_PAUSE: {
            BatTester.trigTime_now = 0;
            //            BatTester.enable = 0;
            BatTester.state = BAT_TESTER_STATE_PAUSE;
            //显示提示框
            //IF_MsgBox_Tips_Mult(&mStr_BatTester_Pause);
            Tree_Btnm_Replace(tree_BatTester, &btn_start, &btn_stop);
            Tree_Btnm_Replace(tree_BatTester, &btn_pause, &btn_contiune);
        }
        break;
        case BAT_TESTER_STATE_STOP: {
            BatTester.tickRun = 0;
            BatTester.trigTime_now = 0;
            BatTester.holdtime = 0;
            //BatTester.errorFlag = 0;
            //停止输出
            if(BatTester.enable != 0) {
                UI_IF_Power_Set_On_Off(0);
            }
            BatTester.enable = 0;
            BatTester.state = BAT_TESTER_STATE_STOP;
            Tree_Btnm_Replace(tree_BatTester, &btn_stop, &btn_start);
            //功能开关
            if(tree_BatTester_btn_pause != NULL) {
                Tree_Delete(tree_BatTester, tree_BatTester_btn_pause);
                tree_BatTester_btn_pause = NULL;
            }
            Tree_Btnm_Refresh();
        }
        break;
    }
    if(BatTester_IsRunning()) {
        lv_label_set_text_static(ui.Bar_btn_List_Dly_label, "BatTester");
        lv_obj_set_hidden(ui.Bar_btn_List_Dly, 0);
        lv_obj_set_hidden(ui.BatTester_bar, 0);
        lv_color_t color = {0};
        switch(value) {
            case BAT_TESTER_STATE_RUNNING:
                color = lv_color_make(0, 255, 0);
                break;
            case BAT_TESTER_STATE_PAUSE:
                color = lv_color_make(255, 255, 0);
                break;
            case BAT_TESTER_STATE_STOP:
                color = lv_color_make(255, 0, 0);
                break;
            default:
                return ;
        }
        #if 1
        lv_obj_set_style_local_text_color(ui.Bar_btn_List_Dly_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, color);
        #else
        lv_obj_set_style_local_text_color(ui.Bar_btn_List_Dly_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0, 0, 0));
        lv_obj_set_style_local_bg_color(ui.Bar_btn_List_Dly, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, color);
        lv_obj_set_style_local_bg_opa(ui.Bar_btn_List_Dly, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
        lv_obj_set_style_local_radius(ui.Bar_btn_List_Dly, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 2);
        #endif
    } else {
        lv_obj_set_hidden(ui.Bar_btn_List_Dly, 1);
        lv_obj_set_hidden(ui.BatTester_bar, 1);
    }
}



void IF_BatTester_Set_Gobal_Protect(uint8_t idx, uint8_t logic, uint8_t stop, float value)
{
    if(idx >= ARRAY_COUNT(BatTester.stopCfg)) { return; }
    BatTester.stopCfg[idx].logic = logic;
    BatTester.stopCfg[idx].stop = stop;
    BatTester.stopCfg[idx].value = value;
    //
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_BATTESTER_SET_REFRESH;
    CMD_MsgQueue_Send(&msg);
}
void IF_BatTester_Set_Group_Protect(uint8_t no, uint8_t idx, uint8_t logic, uint8_t stop, float value)
{
    if(no >= ARRAY_COUNT(BatTester.points)) { return; }
    if(idx >= ARRAY_COUNT(BatTester.points[no].stopCfg)) { return; }
    BatTester.points[no].stopCfg[idx].stop = stop;
    BatTester.points[no].stopCfg[idx].logic = logic;
    BatTester.points[no].stopCfg[idx].value = value;
    //
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_BATTESTER_SET_REFRESH;
    CMD_MsgQueue_Send(&msg);
}


void IF_BatTester_Set_TrigTime(float time) {
    BatTester.trigTime = time;
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_BATTESTER_SET_REFRESH;
    CMD_MsgQueue_Send(&msg);
}
float IF_BatTester_Get_TrigTime(void) {
    return BatTester.trigTime;
}