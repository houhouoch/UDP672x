#include "OutOptionPage.h"
#include "OutOptionPage_item.h"
#include "SettingData.h"

Tree_Def *tree_outoption;

static void __Param_Btn_Style_Load(lv_obj_t *label)
{
    lv_obj_t *button = lv_obj_get_parent(label);
    if(button == NULL) {
        return ;
    }
    uint16_t button_width = lv_obj_get_width(button) - 10;
    uint16_t button_height = lv_obj_get_height(button);
    lv_label_set_long_mode(label, LV_LABEL_LONG_BREAK);
    lv_obj_set_size(label, button_width, button_height);
    lv_obj_align(label, button, LV_ALIGN_IN_RIGHT_MID, -10, 0);
    lv_label_set_align(label, LV_LABEL_ALIGN_RIGHT);
    extern lv_font_t MultFont_16;
    //标签
    lv_style_t *plabelStyle = lv_obj_get_local_style(label, LV_LABEL_PART_MAIN);
    static lv_style_t labelStyle = {0};
    lv_style_init(&labelStyle);
    lv_obj_clean_style_list(label, LV_LABEL_PART_MAIN);
    lv_style_set_text_letter_space(&labelStyle, LV_STATE_DEFAULT, 1);
    lv_style_set_text_letter_space(&labelStyle, LV_STATE_FOCUSED, 1);
    lv_style_set_text_font(&labelStyle, LV_STATE_DEFAULT, &MultFont_16);
    lv_style_set_text_font(&labelStyle, LV_STATE_FOCUSED, &MultFont_16);
    lv_style_set_text_color(&labelStyle, LV_STATE_DEFAULT, lv_color_make(255, 255, 255));
    lv_style_set_text_color(&labelStyle, LV_STATE_FOCUSED, lv_color_make(255, 255, 255));
    lv_style_set_text_sel_color(&labelStyle, LV_STATE_FOCUSED, lv_color_make(255, 255, 255));
    lv_style_set_text_sel_color(&labelStyle, LV_STATE_DEFAULT, lv_color_make(0, 255, 255));
    lv_style_set_text_sel_bg_color(&labelStyle, LV_STATE_FOCUSED, lv_color_make(0, 0, 255));
    lv_style_set_text_sel_bg_color(&labelStyle, LV_STATE_DEFAULT, lv_color_make(0, 0, 0));
    lv_obj_add_style(label, LV_LABEL_PART_MAIN, &labelStyle);
    //按键
    lv_style_t *pbtnStyle = lv_obj_get_local_style(button, LV_BTN_PART_MAIN);
    static lv_style_t btnStyle = {0};
    lv_style_init(&btnStyle);
    lv_obj_clean_style_list(button, LV_LABEL_PART_MAIN);
    lv_style_set_value_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(0, 255, 255));
    lv_style_set_value_color(&btnStyle, LV_STATE_FOCUSED, lv_color_make(0, 255, 255));
    lv_style_set_value_font(&btnStyle, LV_STATE_DEFAULT, &MultFont_16);
    lv_style_set_value_font(&btnStyle, LV_STATE_FOCUSED, &MultFont_16);
    lv_style_set_bg_opa(&btnStyle, LV_STATE_DEFAULT, 0x10);
    lv_style_set_bg_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_border_width(&btnStyle, LV_STATE_DEFAULT, 1);
    lv_style_set_border_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
    lv_style_set_bg_opa(&btnStyle, LV_STATE_FOCUSED, 0x50);
    lv_style_set_bg_color(&btnStyle, LV_STATE_FOCUSED, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_border_width(&btnStyle, LV_STATE_FOCUSED, 0);
    lv_style_set_border_color(&btnStyle, LV_STATE_FOCUSED, lv_color_make(0x50, 0x50, 0x50));
    lv_style_set_radius(&btnStyle, LV_STATE_DEFAULT, 0);
    lv_style_set_radius(&btnStyle, LV_STATE_FOCUSED, 0);
    lv_style_set_value_align(&btnStyle, LV_STATE_DEFAULT, LV_ALIGN_IN_LEFT_MID);
    lv_style_set_value_align(&btnStyle, LV_STATE_FOCUSED, LV_ALIGN_IN_LEFT_MID);
    lv_style_set_value_ofs_x(&btnStyle, LV_STATE_DEFAULT, 5);
    lv_style_set_value_ofs_x(&btnStyle, LV_STATE_FOCUSED, 5);
    lv_style_set_value_opa(&btnStyle, LV_STATE_DEFAULT, 255);
    lv_style_set_value_opa(&btnStyle, LV_STATE_FOCUSED, 255);
    lv_obj_add_style(button, LV_BTN_PART_MAIN, &btnStyle);
    //重绘
    lv_obj_invalidate(label);
    lv_obj_invalidate(button);
}


void OutOptionPage_GroupCreate(void)
{
    //加载UI
    setup_scr_OutOptionPage(&ui);
    lv_obj_set_parent(ui.OutOptionPage_cont, ui.Back_cont_back);
    extern lv_font_t MultFont_16;
    lv_obj_set_style_local_text_font(ui.OutOptionPage_btn_baseTitle_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_16);
    lv_obj_set_style_local_text_font(ui.OutOptionPage_btn_SRTitle_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_16);
    __Param_Btn_Style_Load(ui.OutOptionPage_btn_mode_label);
    __Param_Btn_Style_Load(ui.OutOptionPage_btn_P_Out_label);
    __Param_Btn_Style_Load(ui.OutOptionPage_btn_DVM_label);
    //    lv_obj_set_hidden(ui.OutOptionPage_btn_DVM, 1);
    __Param_Btn_Style_Load(ui.OutOptionPage_btn_SRMode_label);
    __Param_Btn_Style_Load(ui.OutOptionPage_btn_VSR_Up_label);
    __Param_Btn_Style_Load(ui.OutOptionPage_btn_VSR_Dn_label);
    __Param_Btn_Style_Load(ui.OutOptionPage_btn_ISR_Up_label);
    __Param_Btn_Style_Load(ui.OutOptionPage_btn_ISR_Dn_label);
    lv_obj_align(ui.OutOptionPage_btn_VSR_Up, ui.OutOptionPage_btn_SRMode, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    lv_obj_align(ui.OutOptionPage_btn_VSR_Dn, ui.OutOptionPage_btn_VSR_Up, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    lv_obj_align(ui.OutOptionPage_btn_ISR_Up, ui.OutOptionPage_btn_SRMode, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    lv_obj_align(ui.OutOptionPage_btn_ISR_Dn, ui.OutOptionPage_btn_ISR_Up, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    OutOptionPage_Exit();
}

/*
 * @brief       void OutOptionPage_Enter(void)
 * @details     进入OutOption页面
 */
void OutOptionPage_Enter(void)
{
    lv_obj_set_hidden(ui.OutOptionPage_cont, 0);
    lv_event_send_refresh_recursive(ui.OutOptionPage_cont);
    lv_label_set_text_static(ui.OutOptionPage_btn_baseTitle_label, MultStr_GetS(&mStr_BaseTitle));
    lv_label_set_text_static(ui.OutOptionPage_btn_SRTitle_label, MultStr_GetS(&mStr_SR_Title));
}

/*
 * @brief       void OutOptionPage_Exit(void)
 * @details     退出OutOption页面
 */
void OutOptionPage_Exit(void)
{
    lv_obj_set_hidden(ui.OutOptionPage_cont, 1);
}




