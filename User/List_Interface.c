#include "List_Interface.h"


//设置List开关
void IF_List_Set_On_Off(uint8_t onoff)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_LISTPAGE_SET_ONOFF;
    msg.data.data_u8 = onoff;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
//设置起始点
void IF_List_Set_Start(int32_t start)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_LISTPAGE_SET_START;
    msg.data.data_u16 = start;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
//设置总点数
void IF_List_Set_Count(int32_t count)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_LISTPAGE_SET_COUNT;
    msg.data.data_u16 = count;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
//设置循环次数
void IF_List_Set_Cycle(int32_t cycle)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_LISTPAGE_SET_CYCLE;
    msg.data.data_u16 = cycle;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}
//设置结束状态:Hold/Off
void IF_List_Set_lastState(int8_t laststate)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_LISTPAGE_SET_ENDSTATE;
    msg.data.data_u8 = laststate;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}


void IF_List_Set_PointParam(int32_t idx, float volt, float curr, float time)
{
    CMD_Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_LISTPAGE_SET_PARAM;
    msg.data.list_param.idx = idx;
    msg.data.list_param.vol = volt;
    msg.data.list_param.amp = curr;
    msg.data.list_param.time = time;
    msg.presult = &result;
    CMD_MsgQueue_Send(&msg);
}



/* ----------------------- List --------------------- */
/*
 * @brief       void IF_ListOut_Set(float vol,float amp)
 * @details     ListOut设置输出
 */
void IF_ListOut_Set(float vol, float amp)
{
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_LISTOUT_SET;
    msg.data.power.vol = vol;
    msg.data.power.amp = amp;
    CMD_MsgQueue_Send(&msg);
}

void IF_List_Refresh_RemainTime(void)
{
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_LISTOUT_REMAINTIME;
    CMD_MsgQueue_Send(&msg);
}

/*
 * @brief       void IF_ListOut_Set_CurIdx(uint16_t value)
 * @details     ListOut显示当前位置
 */
void IF_ListOut_Set_CurIdx(uint16_t value)
{
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_LISTOUT_SET_CURIDX;
    msg.data.data_u16 = value;
    CMD_MsgQueue_Send(&msg);
}

/*
 * @brief       void IF_ListOut_Set_Loop(uint16_t value)
 * @details     ListOut显示已循环次数
 */
void IF_ListOut_Set_Loop(uint16_t value)
{
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_LISTOUT_SET_LOOP;
    msg.data.data_u16 = value;
    CMD_MsgQueue_Send(&msg);
}

/*
 * @brief       void IF_ListOut_Set_State(uint16_t value)
 * @details     ListOut设置当前状态
 */
void IF_ListOut_Set_State(uint16_t value)
{
    CMD_Msg_Def msg = {0};
    msg.type = MSG_TYPE_LISTOUT_SET_STATE;
    msg.data.data_u16 = value;
    CMD_MsgQueue_Send(&msg);
}



/* ---------------------------------------------------------- */


void UI_IF_List_Set_On_Off(uint8_t onoff)
{
    //设置
    if(onoff != 0) {
        //        IF_ListOut_Set_State(LIST_STATE_RUNNING);
        UI_IF_List_Set_State(LIST_STATE_RUNNING);
    } else {
        //        IF_ListOut_Set_State(LIST_STATE_STOP);
        UI_IF_List_Set_State(LIST_STATE_STOP);
    }
}


void UI_IF_List_Set_Start(int32_t start)
{
    if(LIST_POINT_MIN > start) {
        start = LIST_POINT_MIN;
    } else
        if(start > (LIST_POINT_MAX - listoutInfo.countpoint)) {
            start = (LIST_POINT_MAX - listoutInfo.countpoint);
            IF_MsgBox_Tips_Mult(&mStr_ListSet_MaxPoint);
        }
    listoutInfo.startpoint = start;
    lv_event_send_refresh(ui.ListPage_btn_start_label);
}

void UI_IF_List_Set_Count(int32_t count)
{
    if(LIST_POINT_COUNT_MIN > count) {
        count = LIST_POINT_COUNT_MIN;
    } else
        if(count > (LIST_POINT_MAX - listoutInfo.startpoint)) {
            count = (LIST_POINT_MAX - listoutInfo.startpoint);
            IF_MsgBox_Tips_Mult(&mStr_ListSet_MaxPoint);
        }
    listoutInfo.countpoint = count;
    lv_event_send_refresh(ui.ListPage_btn_count_label);
}

void UI_IF_List_Set_Cycle(int32_t cycle)
{
    if(CYCLE_MIN > cycle) {
        cycle = CYCLE_MIN;
    } else
        if(cycle > CYCLE_MAX) {
            cycle = CYCLE_MAX;
            IF_MsgBox_Tips_Mult(&mStr_ListSet_MaxCycles);
        }
    listoutInfo.cycles = cycle;
    lv_event_send_refresh(ui.ListPage_btn_cycle_label);
}

void UI_IF_List_Set_lastState(int8_t laststate)
{
    if((LIST_ENDSTATE_MIN <= laststate) && (laststate <= LIST_LASTSTATE_MAX)) {
        listoutInfo.lastState = laststate;
        lv_event_send_refresh(ui.ListPage_btn_laststate_label);
    }
}


#define VALUE_LIMIT(A,B,C)  \
    do{                     \
        A = MAX(A,B);       \
        A = MIN(A,C);        \
    }while(0)

void UI_IF_List_Set_PointParam(int32_t idx, float volt, float curr, float time)
{
    if((LIST_POINT_MIN <= idx) && (idx <= LIST_POINT_MAX))
    {
        VALUE_LIMIT(volt, VOL_MIN, VOL_MAX);
        VALUE_LIMIT(curr, AMP_MIN, AMP_MAX);
        VALUE_LIMIT(time, KT_MIN, KT_MAX);
        listoutInfo.points[idx].vol = volt;
        listoutInfo.points[idx].amp = curr;
        listoutInfo.points[idx].kT = time;
        lv_event_send_refresh_recursive(ui.ListPage_cont_Table);
    }
}




#include "TIM.h"
#include "ListOut.h"
#include "ListPage.h"
#include "ListPage_Table.h"
#include "ListPage_Option.h"

void UI_IF_List_Refresh_RemainTime(void)
{
    uint16_t cur = listoutInfo.current;
    float progress = 1000 * listoutInfo.holdtime / listoutInfo.points[cur].kT;
    lv_bar_set_value(ui.ListPage_bar, progress, LV_ANIM_ON);
}

/*
 * @brief       void UI_IF_List_Set_CurIdx(uint16_t value)
 * @details     设置当前List运行索引
 */
void UI_IF_List_Set_CurIdx(uint16_t value)
{
    listoutInfo.current = value;
    if(lv_obj_is_visible(ui.ListPage_cont_setParam) != 0) {
        char buffer[16] = {0};
        sprintf(buffer, POINT_DISP_FORM, value);
        lv_label_set_text(ui.ListPage_btn_current_label, buffer);
        ListPage_SetCurrent(value);
    }
}
/*
 * @brief       void UI_IF_List_Set_Loop(uint16_t value)
 * @details     设置当前List运行循环数
 */
void UI_IF_List_Set_Loop(uint16_t value)
{
    listoutInfo.loop = value;
    static char buffer[16] = {0};
    sprintf(buffer, POINT_DISP_FORM, value);
    if(lv_obj_is_visible(ui.ListPage_cont_setParam) != 0) {
        lv_label_set_text_static(ui.ListPage_btn_loop_label, buffer);
    }
}
/*
 * @brief       void UI_IF_List_Set_State(uint16_t value)
 * @details     设置当前List运行状态
 */
void UI_IF_List_Set_State(uint16_t value)
{
    if(listoutInfo.state == value) {
        return ;
    }
    switch(value)
    {
        case LIST_STATE_RUNNING: {
            if(listoutInfo.state != LIST_STATE_RUNNING)
            {
                uint8_t state = listoutInfo.state;
                listoutInfo.enable = 1;
                listoutInfo.state = LIST_STATE_RUNNING;
                if(state != LIST_STATE_PAUSE)
                {
                    listoutInfo.current = listoutInfo.startpoint;
                    listoutInfo.loop = 0;
                    UI_IF_List_Set_CurIdx(listoutInfo.current);
                    UI_IF_List_Set_Loop(listoutInfo.loop);
                    UI_IF_Power_SetVol(listoutInfo.points[0].vol);
                    UI_IF_Power_SetAmp(listoutInfo.points[0].amp);
                }
                IF_Power_OVP_Clean();
                IF_Power_OCP_Clean();
                UI_IF_Power_Set_On_Off(1);
                Tree_Btnm_Replace(tree_list, &btn_start, &btn_stop);
                Tree_Btnm_Replace(tree_list, &btn_contiune, &btn_pause);
                //功能开关
                if(tree_list_btn_pause == NULL) {
                    tree_list_btn_pause = Tree_AddNode(tree_list, &btn_pause);
                }
                Tree_Btnm_Refresh();
            }
            listoutInfo.tickRun = 1;
        }
        break;
        case LIST_STATE_PAUSE: {
            //            listoutInfo.enable = 0;
            listoutInfo.state = LIST_STATE_PAUSE;
            //显示提示框
            IF_MsgBox_Tips_Mult(&mStr_list_Pause);
            Tree_Btnm_Replace(tree_list, &btn_start, &btn_stop);
            Tree_Btnm_Replace(tree_list, &btn_pause, &btn_contiune);
        }
        break;
        case LIST_STATE_STOP: {
            listoutInfo.tickRun = 0;
            //停止输出
            if(listoutInfo.enable != 0) {
                if(listoutInfo.lastState == LIST_ENDSTATE_OFF) {
                    UI_IF_Power_Set_On_Off(0);
                }
            }
            listoutInfo.enable = 0;
            listoutInfo.state = LIST_STATE_STOP;
            Tree_Btnm_Replace(tree_list, &btn_stop, &btn_start);
            //功能开关
            if(tree_list_btn_pause != NULL) {
                Tree_Delete(tree_list, tree_list_btn_pause);
                tree_list_btn_pause = NULL;
            }
            Tree_Btnm_Refresh();
        }
        break;
    }
    if(ListOut_IsRunning()) {
        lv_label_set_text_static(ui.Bar_btn_List_Dly_label, "List");
        lv_obj_set_hidden(ui.Bar_btn_List_Dly, 0);
        lv_obj_set_hidden(ui.ListPage_bar, 0);
        lv_color_t color = {0};
        switch(value) {
            case LIST_STATE_RUNNING:
                color = lv_color_make(0, 255, 0);
                break;
            case LIST_STATE_PAUSE:
                color = lv_color_make(255, 255, 0);
                break;
            case LIST_STATE_STOP:
                color = lv_color_make(255, 0, 0);
                break;
            default:
                return ;
        }
        lv_obj_set_style_local_text_color(ui.Bar_btn_List_Dly_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, color);
    } else {
        lv_obj_set_hidden(ui.Bar_btn_List_Dly, 1);
        lv_obj_set_hidden(ui.ListPage_bar, 1);
    }
}
