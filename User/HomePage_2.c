#include "HomePage_2.h"
#include "ListOut.h"

#include "SettingData.h"

#include "Interface.h"
#include "InputWidget.h"

Tree_Def *tree_home_2;

void HomePage_2_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    switch(event)
    {
        case LV_EVENT_REFRESH: {
            lv_label_set_text_static(ui.HomePage2_btn_Set_label_label, MultStr_GetS(&mStr_home_Set));
            lv_label_set_text_static(ui.HomePage2_btn_Limit_label_label, MultStr_GetS(&mStr_home_Limit));
            lv_label_set_text_static(ui.HomePage2_btn_Timer_label_label, MultStr_GetS(&mStr_home_TimeSet));
        }
        break;
    }
}


/*
 * @brief       void HomePage_2_Enter(void)
 * @details     进入主页
 */
void HomePage_2_Enter(void)
{
    lv_obj_set_hidden(ui.HomePage2_cont_Out, 0);
    lv_obj_set_hidden(ui.HomePage2_cont_Set, 0);
    //
    lv_obj_set_hidden(ui.HomePage2_line_1, 0);
    lv_obj_set_hidden(ui.HomePage2_line_2, 0);
    lv_obj_set_hidden(ui.HomePage2_line_4, 0);
    lv_obj_set_hidden(ui.HomePage2_line_5, 0);
    //递归刷新
    lv_event_send_refresh_recursive(ui.HomePage2_cont_Out);
    lv_event_send_refresh_recursive(ui.HomePage2_cont_Set);
}


/*
 * @brief       void HomePage_2_Exit(void)
 * @details     退出主页
 */
void HomePage_2_Exit(void)
{
    lv_obj_set_hidden(ui.HomePage2_cont_Out, 1);
    lv_obj_set_hidden(ui.HomePage2_cont_Set, 1);
    //
    lv_obj_set_hidden(ui.HomePage2_line_1, 1);
    lv_obj_set_hidden(ui.HomePage2_line_2, 1);
    lv_obj_set_hidden(ui.HomePage2_line_4, 1);
    lv_obj_set_hidden(ui.HomePage2_line_5, 1);
}







void HomePage_2_GroupCreate(void)
{
    {
        setup_scr_HomePage2(&ui);
        lv_obj_set_parent(ui.HomePage2_cont_Set, ui.Back_cont_back);
        lv_obj_set_parent(ui.HomePage2_cont_Out, ui.Back_cont_back);
        lv_obj_set_parent(ui.HomePage2_line_1, ui.Back_cont_back);
        lv_obj_set_parent(ui.HomePage2_line_2, ui.Back_cont_back);
        lv_obj_set_parent(ui.HomePage2_line_4, ui.Back_cont_back);
        lv_obj_set_parent(ui.HomePage2_line_5, ui.Back_cont_back);
    }
    lv_obj_set_style_local_bg_color(ui.HomePage2_btn_Status, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x64, 0x64, 0x64));
    lv_obj_set_style_local_bg_opa(ui.HomePage2_btn_Status, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 200);
    lv_obj_set_style_local_radius(ui.HomePage2_btn_Status, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_border_width(ui.HomePage2_btn_Status, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 1);
    lv_obj_set_style_local_border_color(ui.HomePage2_btn_Status, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
    lv_obj_set_style_local_bg_color(ui.HomePage2_btn_Mode, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x00, 0xFF, 0x00));
    lv_obj_set_style_local_bg_opa(ui.HomePage2_btn_Mode, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 200);
    lv_obj_set_style_local_radius(ui.HomePage2_btn_Mode, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_border_width(ui.HomePage2_btn_Mode, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 1);
    lv_obj_set_style_local_border_color(ui.HomePage2_btn_Mode, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
    lv_obj_set_style_local_bg_color(ui.HomePage2_label_DVM, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xFF, 0x64, 0x00));
    lv_obj_set_style_local_bg_opa(ui.HomePage2_label_DVM, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 200);
    lv_obj_set_style_local_radius(ui.HomePage2_label_DVM, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_border_width(ui.HomePage2_label_DVM, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 1);
    lv_obj_set_style_local_border_color(ui.HomePage2_label_DVM, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
    lv_obj_set_style_local_text_sel_bg_color(ui.HomePage2_label_Vout_Set, LV_LABEL_PART_MAIN, LV_STATE_FOCUSED, lv_color_make(0, 0, 255));
    lv_obj_set_style_local_text_sel_bg_color(ui.HomePage2_label_Iout_Set, LV_LABEL_PART_MAIN, LV_STATE_FOCUSED, lv_color_make(0, 0, 255));
    lv_obj_set_style_local_text_sel_bg_color(ui.HomePage2_label_OVP_Set, LV_LABEL_PART_MAIN, LV_STATE_FOCUSED, lv_color_make(0, 0, 255));
    lv_obj_set_style_local_text_sel_bg_color(ui.HomePage2_label_OCP_Set, LV_LABEL_PART_MAIN, LV_STATE_FOCUSED, lv_color_make(0, 0, 255));
    lv_obj_set_style_local_text_sel_bg_color(ui.HomePage2_label_Time_Set, LV_LABEL_PART_MAIN, LV_STATE_FOCUSED, lv_color_make(0, 0, 255));
    HomePage_2_Exit();
}

