//无List

#include "BatTester.h"
#include "BatTesterPage.h"
#include "BatTesterPage_Table.h"
//#include "BatTesterPage_Option.h"
#include "BatTester_Interface.h"

#include "fatfs.h"


Tree_Def *tree_BatTester;
Tree_Def *tree_BatTester_option;
Tree_Def *tree_BatTester_start;
Tree_Def *tree_BatTester_end;
Tree_Def *tree_BatTester_cycles;

Tree_Def *tree_BatTester_table;
Tree_Def *tree_BatTester_Vout;
Tree_Def *tree_BatTester_Iout;
Tree_Def *tree_BatTester_keepT;

Tree_Def *tree_BatTester_tipsSet;
Tree_Def *tree_BatTester_protect;
Tree_Def *tree_BatTester_trigTime;

Tree_Def *tree_BatTester_manage;

Tree_Def *tree_BatTester_btn_start;
Tree_Def *tree_BatTester_btn_pause;


/*
 * @brief       void BatteryTest_Pageer_Enter(void)
 * @details     进入BatteryTester页面
 */
void BatteryTester_Page_Enter(void)
{
    lv_obj_set_hidden(ui.BatTester_cont_setParam, 0);
    lv_obj_set_hidden(ui.BatTester_cont_Table, 0);
    //BtnLabel_Set_Edit_Tag(ui.BatTester_btn_fileName_label, MultStr_GetS(&mStr_Battest_lab_FileName));
    BtnLabel_Set_Edit_Tag(ui.BatTester_btn_current_label, MultStr_GetS(&mStr_Battest_lab_Current));
    BtnLabel_Set_Edit_Tag(ui.BatTester_btn_loop_label, MultStr_GetS(&mStr_Battest_lab_Loop));
    BtnLabel_Set_Edit_Tag(ui.BatTester_btn_start_label, MultStr_GetS(&mStr_Battest_lab_Start));
    BtnLabel_Set_Edit_Tag(ui.BatTester_btn_count_label, MultStr_GetS(&mStr_Battest_lab_Groups));
    BtnLabel_Set_Edit_Tag(ui.BatTester_btn_cycle_label, MultStr_GetS(&mStr_Battest_lab_Cycles));
    BtnLabel_Set_Edit_Tag(ui.BatTester_btn_protect_label, MultStr_GetS(&mStr_Battest_Protect));
    BtnLabel_Set_Edit_Tag(ui.BatTester_btn_TrigTime_label, MultStr_GetS(&mStr_Battest_lab_TrigTime));
    //递归刷新
    lv_event_send_refresh_recursive(ui.BatTester_cont_setParam);
    lv_event_send_refresh_recursive(ui.BatTester_cont_Table);
    //
    lv_obj_set_size(ui.BatTester_btn_state_label, lv_obj_get_width(ui.BatTester_btn_state), lv_obj_get_height(ui.BatTester_btn_state) - 10);
    lv_label_set_long_mode(ui.BatTester_btn_state_label, LV_LABEL_LONG_SROLL);
    lv_label_set_align(ui.BatTester_btn_state_label, LV_LABEL_ALIGN_CENTER);
    lv_obj_align(ui.BatTester_btn_state_label, ui.BatTester_btn_state, LV_ALIGN_CENTER, 0, 10);
    //
    UI_IF_BatTester_Set_State(BatTester.state);
    UI_IF_BatTester_Set_Loop(BatTester.loop);
    UI_IF_BatTester_Set_CurIdx(BatTester.current);
    //lv_label_set_text_static(ui.BatTester_btn_fileName_label, systemInfo.userInfo.fileName_BatTester);
}

/*
 * @brief       void BatteryTester_Page_Exit(void)
 * @details     退出BatteryTest页面
 */
void BatteryTester_Page_Exit(void)
{
    lv_obj_set_hidden(ui.BatTester_cont_setParam, 1);
    lv_obj_set_hidden(ui.BatTester_cont_Table, 1);
}





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



static void __Refresh_Task(struct _lv_task_t *p)
{
    if(ui.BatTester_btn_state_label == NULL) { return ; }
    switch(BatTester.state)
    {
        case BAT_TESTER_STATE_COMPLETED: {
            extern lv_font_t MultFont_26;
            lv_obj_set_style_local_text_font(ui.BatTester_btn_state_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_26);
            lv_label_set_text_static(ui.BatTester_btn_state_label, MultStr_GetS(&mStr_State_Completed));
            lv_obj_set_style_local_text_color(ui.BatTester_btn_state_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0, 0xff, 0));
        }
        break;
        case BAT_TESTER_STATE_RUNNING: {
            extern lv_font_t MultFont_26;
            lv_obj_set_style_local_text_font(ui.BatTester_btn_state_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_26);
            lv_label_set_text_static(ui.BatTester_btn_state_label, MultStr_GetS(&mStr_State_Running));
            lv_obj_set_style_local_text_color(ui.BatTester_btn_state_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0, 0xff, 0));
        }
        break;
        case BAT_TESTER_STATE_PAUSE: {
            extern lv_font_t MultFont_26;
            lv_obj_set_style_local_text_font(ui.BatTester_btn_state_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_26);
            lv_label_set_text_static(ui.BatTester_btn_state_label, MultStr_GetS(&mStr_State_Paused));
            lv_obj_set_style_local_text_color(ui.BatTester_btn_state_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0));
        }
        break;
        case BAT_TESTER_STATE_STOP: {
            extern lv_font_t MultFont_26;
            lv_obj_set_style_local_text_font(ui.BatTester_btn_state_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_26);
            lv_label_set_text_static(ui.BatTester_btn_state_label, MultStr_GetS(&mStr_State_Stopped));
            lv_obj_set_style_local_text_color(ui.BatTester_btn_state_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0, 0));
        }
        break;
    }
    if((BatTester_IsRunning() != 0) || (lv_obj_get_hidden(ui.BatTester_cont_Table) == 0)) {
        lv_obj_set_hidden(ui.Bar_btn_fileName, 0);
        uint16_t fileName_len = strlen(systemInfo.userInfo.fileName_BatTester);
        const char *pFileName = "";
        for(uint16_t i = fileName_len; i > 0; --i) {
            if(systemInfo.userInfo.fileName_BatTester[i] == '/') {
                pFileName = &systemInfo.userInfo.fileName_BatTester[i] + 1;
            }
        }
        lv_label_set_text_static(ui.Bar_btn_fileName_label, pFileName);
    } else {
        lv_obj_set_hidden(ui.Bar_btn_fileName, 1);
    }
}




void BatteryTester_Page_GroupCreate(void)
{
    lv_task_create(__Refresh_Task, 100, LV_TASK_PRIO_MID, NULL);
    if(strlen(systemInfo.userInfo.fileName_BatTester) > 0) {
        if(BatTester_Load(&BatTester, systemInfo.userInfo.fileName_BatTester) > 0) {
        } else {
            BatTester_Load(&BatTester, BAT_TESTER_FILE_FLASH_PATH"/Demo.batt.csv");
        }
    } else {
        BatTester_Load(&BatTester, BAT_TESTER_FILE_FLASH_PATH"/Demo.batt.csv");
    }
    //
    {
        setup_scr_BatTester(&ui);
        lv_obj_set_parent(ui.BatTester_cont_Table, ui.Back_cont_back);
        lv_obj_set_parent(ui.BatTester_cont_setParam, ui.Back_cont_back);
        void batTester_btnTable_Init(void);
        batTester_btnTable_Init();
    }
    lv_obj_set_style_local_bg_color(ui.BatTester_cont_Table, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0, 0, 0));
    lv_obj_set_style_local_bg_color(ui.BatTester_cont_Table, LV_CONT_PART_MAIN, LV_STATE_FOCUSED, lv_color_make(0, 0, 0));
    lv_obj_set_style_local_border_width(ui.BatTester_cont_Table, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 1);
    lv_obj_set_style_local_border_width(ui.BatTester_cont_Table, LV_CONT_PART_MAIN, LV_STATE_FOCUSED, 1);
    lv_obj_set_style_local_border_color(ui.BatTester_cont_Table, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
    lv_obj_set_style_local_border_color(ui.BatTester_cont_Table, LV_CONT_PART_MAIN, LV_STATE_FOCUSED, lv_color_make(0x22, 0x22, 0x22));
    //__btnStyle_Init(ui.BatTester_btn_fileName_label);
    __btnStyle_Init(ui.BatTester_btn_current_label);
    __btnStyle_Init(ui.BatTester_btn_loop_label);
    __btnStyle_Init(ui.BatTester_btn_start_label);
    __btnStyle_Init(ui.BatTester_btn_count_label);
    __btnStyle_Init(ui.BatTester_btn_cycle_label);
    __btnStyle_Init(ui.BatTester_btn_protect_label);
    __btnStyle_Init(ui.BatTester_btn_TrigTime_label);
    extern void BatteryTester_Page_Table_Refresh(int16_t baseIndex);
    BatteryTester_Page_Table_Refresh(0);
    BatteryTester_Page_Enter();
    BatteryTester_Page_Exit();
    UI_IF_BatTester_Set_State(BAT_TESTER_STATE_STOP);
    lv_bar_set_anim_time(ui.BatTester_bar, 100);
    lv_bar_set_range(ui.BatTester_bar, 0, 1000);
    lv_bar_set_value(ui.BatTester_bar, 0, LV_ANIM_OFF);
    lv_obj_set_hidden(ui.BatTester_bar, 1);
    lv_label_set_long_mode(ui.Bar_btn_fileName_label, LV_LABEL_LONG_SROLL);  //LV_LABEL_LONG_SROLL_CIRC
    extern lv_font_t MultFont_16;
    lv_obj_set_style_local_text_font(ui.Bar_btn_fileName_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_16);
    lv_obj_set_style_local_text_color(ui.Bar_btn_fileName_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
    lv_obj_set_size(ui.Bar_btn_fileName_label, lv_obj_get_width(ui.Bar_btn_fileName) - 4, lv_obj_get_height(ui.Bar_btn_fileName));
    lv_label_set_align(ui.Bar_btn_fileName_label, LV_LABEL_ALIGN_CENTER);
    lv_obj_align(ui.Bar_btn_fileName_label, ui.Bar_btn_fileName, LV_ALIGN_CENTER, 0, 0);
}



