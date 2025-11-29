#include "DelayOut.h"
#include "DelayOutPage.h"
#include "DelayOutPage_Table.h"
#include "Delay_Interface.h"

#include "fatfs.h"


Tree_Def *tree_delay;
Tree_Def *tree_delay_option;
Tree_Def *tree_delay_start;
Tree_Def *tree_delay_end;
Tree_Def *tree_delay_cycles;
Tree_Def *tree_delay_protect;
Tree_Def *tree_delay_protectVal;
Tree_Def *tree_delay_protectAction;

Tree_Def *tree_delay_table;
Tree_Def *tree_delay_Out;
Tree_Def *tree_delay_delayT;

Tree_Def *tree_delay_manage;
Tree_Def *tree_delay_temp;






static void __btnStyle_Init(lv_obj_t *label)
{
    if(label == NULL) {
        return ;
    }
    lv_obj_t *button = lv_obj_get_parent(label);
    uint16_t button_width = lv_obj_get_width(button);
    uint16_t button_height = lv_obj_get_height(button);
    lv_label_set_long_mode(label, LV_LABEL_LONG_BREAK);
    lv_obj_set_size(label, button_width - 10, button_height);
    lv_obj_align(label, button, LV_ALIGN_IN_RIGHT_MID, -10, 0);
    lv_label_set_align(label, LV_LABEL_ALIGN_RIGHT);
    extern lv_font_t MultFont_16;
    //标签
    lv_style_t *plabelStyle = lv_obj_get_local_style(label, LV_LABEL_PART_MAIN);
    static lv_style_t labelStyle = {0};
    //    lv_style_copy(&labelStyle, plabelStyle);
    lv_style_init(&labelStyle);
    lv_obj_clean_style_list(label, LV_LABEL_PART_MAIN);
    lv_style_set_text_letter_space(&labelStyle, LV_STATE_DEFAULT, 2);
    lv_style_set_text_letter_space(&labelStyle, LV_STATE_FOCUSED, 2);
    lv_style_set_text_font(&labelStyle, LV_STATE_DEFAULT, &MultFont_16);
    lv_style_set_text_font(&labelStyle, LV_STATE_FOCUSED, &MultFont_16);
    lv_style_set_text_color(&labelStyle, LV_STATE_DEFAULT, lv_color_make(255, 255, 255));
    lv_style_set_text_color(&labelStyle, LV_STATE_FOCUSED, lv_color_make(255, 255, 255));
    lv_style_set_text_sel_color(&labelStyle, LV_STATE_FOCUSED, lv_color_make(255, 255, 255));
    lv_style_set_text_sel_color(&labelStyle, LV_STATE_DEFAULT, lv_color_make(255, 255, 255));
    lv_style_set_text_sel_bg_color(&labelStyle, LV_STATE_FOCUSED, lv_color_make(0, 0, 255));
    lv_style_set_text_sel_bg_color(&labelStyle, LV_STATE_DEFAULT, lv_color_make(0x10, 0x10, 0x10));
    lv_obj_add_style(label, LV_LABEL_PART_MAIN, &labelStyle);
    //    UI_Label_Value_Style_Load(label);
    //按键
    lv_style_t *pbtnStyle = lv_obj_get_local_style(button, LV_BTN_PART_MAIN);
    static lv_style_t btnStyle = {0};
    //    lv_style_copy(&btnStyle, pbtnStyle);
    lv_style_init(&btnStyle);
    lv_obj_clean_style_list(button, LV_BTN_PART_MAIN);
    lv_style_set_bg_opa(&btnStyle, LV_STATE_DEFAULT, 0x10);
    lv_style_set_bg_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_border_width(&btnStyle, LV_STATE_DEFAULT, 1);
    lv_style_set_border_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
    lv_style_set_value_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(0, 255, 255));
    lv_style_set_value_font(&btnStyle, LV_STATE_DEFAULT, &MultFont_16);
    lv_style_set_radius(&btnStyle, LV_STATE_DEFAULT, 0);
    lv_style_set_value_align(&btnStyle, LV_STATE_DEFAULT, LV_ALIGN_IN_LEFT_MID);
    lv_style_set_value_ofs_x(&btnStyle, LV_STATE_DEFAULT, 5);
    lv_style_set_value_opa(&btnStyle, LV_STATE_DEFAULT, 255);
    lv_style_set_value_letter_space(&btnStyle, LV_STATE_DEFAULT, 1);
    lv_obj_add_style(button, LV_BTN_PART_MAIN, &btnStyle);
    //重绘
    lv_obj_invalidate(label);
    lv_obj_invalidate(button);
}



/*
 * @brief       void DelayPage_Enter(void)
 * @details     进入DelayOut页面
 */
void DelayPage_Enter(void)
{
    lv_obj_set_hidden(ui.DelayPage_cont_setParam, 0);
    lv_obj_set_hidden(ui.DelayPage_cont_Table, 0);
    BtnLabel_Set_Edit_Tag(ui.DelayPage_btn_current_label, MultStr_GetS(&mStr_delay_lab_Current));
    BtnLabel_Set_Edit_Tag(ui.DelayPage_btn_loop_label, MultStr_GetS(&mStr_delay_lab_Loop));
    BtnLabel_Set_Edit_Tag(ui.DelayPage_btn_start_label, MultStr_GetS(&mStr_delay_lab_Start));
    BtnLabel_Set_Edit_Tag(ui.DelayPage_btn_count_label, MultStr_GetS(&mStr_delay_lab_Groups));
    BtnLabel_Set_Edit_Tag(ui.DelayPage_btn_cycle_label, MultStr_GetS(&mStr_delay_lab_Cycles));
    BtnLabel_Set_Edit_Tag(ui.DelayPage_btn_stopVal_label, MultStr_GetS(&mStr_delay_lab_stopVal));
    BtnLabel_Set_Edit_Tag(ui.DelayPage_btn_lastState_label, MultStr_GetS(&mStr_delay_lab_EndState));
    //
    lv_obj_set_size(ui.DelayPage_btn_state_label, lv_obj_get_width(ui.DelayPage_btn_state), lv_obj_get_height(ui.DelayPage_btn_state) - 5);
    lv_label_set_long_mode(ui.DelayPage_btn_state_label, LV_LABEL_LONG_SROLL);
    lv_label_set_align(ui.DelayPage_btn_state_label, LV_LABEL_ALIGN_CENTER);
    lv_obj_align(ui.DelayPage_btn_state_label, ui.DelayPage_btn_state, LV_ALIGN_CENTER, 0, 5);
    //递归刷新
    lv_event_send_refresh_recursive(ui.DelayPage_cont_setParam);
    lv_event_send_refresh_recursive(ui.DelayPage_cont_Table);
    UI_IF_Delay_Set_State(delayoutInfo.state);
    UI_IF_Delay_Set_Loop(delayoutInfo.loop);
    UI_IF_Delay_Set_CurIdx(delayoutInfo.current);
}

/*
 * @brief       void DelayPage_Exit(void)
 * @details     退出DelayOut页面
 */
void DelayPage_Exit(void)
{
    lv_obj_set_hidden(ui.DelayPage_cont_setParam, 1);
    lv_obj_set_hidden(ui.DelayPage_cont_Table, 1);
}


static void __Refresh_Task(struct _lv_task_t *p)
{
    if(ui.DelayPage_btn_state_label == NULL) { return ; }
    switch(delayoutInfo.state)
    {
        case DELAY_STATE_RUNNING: {
            extern lv_font_t MultFont_26;
            lv_obj_set_style_local_text_font(ui.DelayPage_btn_state_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_26);
            lv_label_set_text_static(ui.DelayPage_btn_state_label, MultStr_GetS(&mStr_State_Running));
            lv_obj_set_style_local_text_color(ui.DelayPage_btn_state_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0, 0xff, 0));
        }
        break;
        case DELAY_STATE_HALT: {
            extern lv_font_t MultFont_26;
            lv_obj_set_style_local_text_font(ui.DelayPage_btn_state_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_26);
            lv_label_set_text_static(ui.DelayPage_btn_state_label, MultStr_GetS(&mStr_State_Paused));
            lv_obj_set_style_local_text_color(ui.DelayPage_btn_state_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0));
        }
        break;
        case DELAY_STATE_STOP: {
            extern lv_font_t MultFont_26;
            lv_obj_set_style_local_text_font(ui.DelayPage_btn_state_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_26);
            lv_label_set_text_static(ui.DelayPage_btn_state_label, MultStr_GetS(&mStr_State_Stopped));
            lv_obj_set_style_local_text_color(ui.DelayPage_btn_state_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0, 0));
        }
        break;
    }
}

/*
 * @brief       void Power_Read_Updata_Task(struct _lv_task_t *p)
 * @details     定时刷新输出显示
 */
static void __Updata_Task(struct _lv_task_t *p)
{
    if(DelayOut_IsRunning() != 0) {
        UI_IF_Delay_Set_CurIdx(delayoutInfo.current);
        UI_IF_Delay_Refresh_RemainTime();
    }
}

void DelayPage_GroupCreate(void)
{
    lv_task_create(__Refresh_Task, 100, LV_TASK_PRIO_MID, NULL);
    DelayOut_Load(&delayoutInfo, DELAYOUT_FILE_FLASH_PATH"/Demo.dly.csv");
    //
    {
        setup_scr_DelayPage(&ui);
        lv_obj_set_parent(ui.DelayPage_cont_Table, ui.Back_cont_back);
        lv_obj_set_parent(ui.DelayPage_cont_setParam, ui.Back_cont_back);
        extern void Delay_btnTable_Init(void);
        Delay_btnTable_Init();
    }
    lv_obj_set_style_local_bg_color(ui.DelayPage_cont_Table, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0, 0, 0));
    lv_obj_set_style_local_bg_color(ui.DelayPage_cont_Table, LV_CONT_PART_MAIN, LV_STATE_FOCUSED, lv_color_make(0, 0, 0));
    lv_obj_set_style_local_border_width(ui.DelayPage_cont_Table, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 1);
    lv_obj_set_style_local_border_width(ui.DelayPage_cont_Table, LV_CONT_PART_MAIN, LV_STATE_FOCUSED, 1);
    lv_obj_set_style_local_border_color(ui.DelayPage_cont_Table, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
    lv_obj_set_style_local_border_color(ui.DelayPage_cont_Table, LV_CONT_PART_MAIN, LV_STATE_FOCUSED, lv_color_make(0x22, 0x22, 0x22));
    __btnStyle_Init(ui.DelayPage_btn_current_label);
    __btnStyle_Init(ui.DelayPage_btn_loop_label);
    __btnStyle_Init(ui.DelayPage_btn_start_label);
    __btnStyle_Init(ui.DelayPage_btn_count_label);
    __btnStyle_Init(ui.DelayPage_btn_cycle_label);
    __btnStyle_Init(ui.DelayPage_btn_stopVal_label);
    __btnStyle_Init(ui.DelayPage_btn_lastState_label);
    DelayPage_Table_Refresh(0);
    DelayPage_Enter();
    DelayPage_Exit();
    UI_IF_Delay_Set_State(DELAY_STATE_STOP);
    lv_bar_set_anim_time(ui.DelayPage_bar, 100);
    lv_bar_set_range(ui.DelayPage_bar, 0, 1000);
    lv_bar_set_value(ui.DelayPage_bar, 0, LV_ANIM_OFF);
    lv_obj_set_hidden(ui.DelayPage_bar, 1);
    //
    lv_task_create(__Updata_Task, 100, LV_TASK_PRIO_MID, NULL);
}

