#include "Commd.h"
#include "Style.h"


extern lv_font_t MultFont_16;


void ICON_StyleInit(lv_obj_t *img)
{
    //按键
    lv_style_t *pbtnStyle = lv_obj_get_local_style(img, LV_IMG_PART_MAIN);
    static lv_style_t btnStyle = {0};
    lv_style_init(&btnStyle);
    lv_obj_clean_style_list(img, LV_BTN_PART_MAIN);
    lv_style_set_bg_opa(&btnStyle, LV_STATE_DEFAULT, 0);
    //    lv_style_set_border_width(&btnStyle, LV_STATE_DEFAULT, 1);
    //    lv_style_set_border_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(255, 255, 255));
    lv_style_set_radius(&btnStyle, LV_STATE_DEFAULT, 2);
    //    lv_style_set_image_blend_mode(&btnStyle, LV_STATE_DEFAULT, LV_BLEND_MODE_ADDITIVE);
    lv_style_set_image_opa(&btnStyle, LV_STATE_DEFAULT, 255);
    lv_obj_add_style(img, LV_IMG_PART_MAIN, &btnStyle);
}

void UI_Label_Value_Style_Load(lv_obj_t *label)
{
    lv_style_t *style = NULL;
    static lv_style_t newStyle = {0};
    style = lv_obj_get_local_style(label, LV_LABEL_PART_MAIN);
    lv_style_copy(&newStyle, style);
    lv_obj_clean_style_list(label, LV_LABEL_PART_MAIN);
    //    //字体
    //    extern lv_font_t MultFont_16;
    lv_style_set_text_font(&newStyle, LV_STATE_FOCUSED, &lv_font_AlibabaPuHuiTi_Light_16);
    lv_style_set_text_font(&newStyle, LV_STATE_DEFAULT, &lv_font_AlibabaPuHuiTi_Light_16);
    lv_style_set_text_letter_space(&newStyle, LV_STATE_FOCUSED, 1);
    lv_style_set_text_letter_space(&newStyle, LV_STATE_DEFAULT, 1);
    //字体颜色
    lv_style_set_text_color(&newStyle, LV_STATE_FOCUSED, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_text_color(&newStyle, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_text_opa(&newStyle, LV_STATE_FOCUSED, 255);
    lv_style_set_text_opa(&newStyle, LV_STATE_DEFAULT, 255);
    //背景�?
    lv_style_set_bg_opa(&newStyle, LV_STATE_FOCUSED, 0);
    lv_style_set_bg_opa(&newStyle, LV_STATE_DEFAULT, 0);
    //选中编辑效果
    lv_style_set_text_sel_color(&newStyle, LV_STATE_FOCUSED, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_text_sel_bg_color(&newStyle, LV_STATE_FOCUSED, lv_color_make(0, 0, 255));
    lv_style_set_text_sel_color(&newStyle, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_text_sel_bg_color(&newStyle, LV_STATE_DEFAULT, lv_color_make(20, 20, 20));
    //加载Style
    lv_obj_clean_style_list(label, LV_LABEL_PART_MAIN);
    lv_style_set_bg_main_stop(&newStyle, LV_STATE_FOCUSED, 50);
    lv_style_set_bg_grad_stop(&newStyle, LV_STATE_FOCUSED, 255 - 50);
    lv_style_set_bg_main_stop(&newStyle, LV_STATE_DEFAULT, 50);
    lv_style_set_bg_grad_stop(&newStyle, LV_STATE_DEFAULT, 255 - 50);
    lv_obj_add_style(label, LV_LABEL_PART_MAIN, &newStyle);
    lv_obj_invalidate(label);
}


void UI_BtnMatrix_Style_Load(lv_obj_t *label)
{
    lv_obj_t *btn = lv_obj_get_parent(label);
    extern lv_font_t lv_userFont;
    static lv_style_t *style = NULL;
    static lv_style_t newStyle = {0};
    style = lv_obj_get_local_style(btn, LV_BTN_PART_MAIN);
    lv_style_copy(&newStyle, style);
    lv_obj_clean_style_list(btn, LV_BTN_PART_MAIN);
    lv_style_set_border_color(&newStyle, LV_STATE_FOCUSED, lv_color_make(0x11, 0x11, 0x11));
    lv_style_set_border_color(&newStyle, LV_STATE_DEFAULT, lv_color_make(0x11, 0x11, 0x11));
    lv_style_set_border_width(&newStyle, LV_STATE_FOCUSED, 1);
    lv_style_set_border_width(&newStyle, LV_STATE_DEFAULT, 1);
    //Focus
    lv_style_set_text_color(&newStyle, LV_STATE_FOCUSED, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_text_font(&newStyle, LV_STATE_FOCUSED, &MultFont_16);
    //Defocus
    lv_style_set_text_color(&newStyle, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_text_font(&newStyle, LV_STATE_DEFAULT, &MultFont_16);
    lv_obj_add_style(btn, LV_BTN_PART_MAIN, &newStyle);
    lv_obj_invalidate(btn);
    //    lv_obj_set_style_local_border_opa(label,LV_LABEL_PART_MAIN, LV_STATE_DEFAULT,255);
    //    lv_obj_set_style_local_border_color(label,LV_LABEL_PART_MAIN, LV_STATE_DEFAULT,lv_color_hex(0xffffff));
    //    lv_obj_set_style_local_border_width(label,LV_LABEL_PART_MAIN, LV_STATE_DEFAULT,1);
    lv_obj_set_style_local_text_font(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_16);
    lv_label_set_long_mode(label, LV_LABEL_LONG_SROLL);
    lv_label_set_align(label, LV_LABEL_ALIGN_CENTER);
    lv_obj_set_size(label, lv_obj_get_width(btn) - 4, 24);
    lv_obj_align(label, btn, LV_ALIGN_CENTER, 0, 4);
}






/*
 * @brief       void ListTempPge_TypeImg_StyleInit(lv_obj_t* button)
 * @details     波形图片风格Style设置(浅蓝色�?边�?)
 */
void ListTempPge_TypeImg_StyleInit(lv_obj_t *button)
{
    //按键
    lv_style_t *pbtnStyle = lv_obj_get_local_style(button, LV_BTN_PART_MAIN);
    static lv_style_t btnStyle = {0};
    //    lv_style_copy(&btnStyle, pbtnStyle);
    lv_style_init(&btnStyle);
    lv_obj_clean_style_list(button, LV_BTN_PART_MAIN);
    lv_style_set_bg_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(0, 0, 0));
    lv_style_set_bg_opa(&btnStyle, LV_STATE_DEFAULT, 0);
    lv_style_set_border_width(&btnStyle, LV_STATE_DEFAULT, 1);
    lv_style_set_border_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(0, 255, 255));
    lv_style_set_radius(&btnStyle, LV_STATE_DEFAULT, 0);
    //    lv_style_set_image_blend_mode(&btnStyle, LV_STATE_DEFAULT, LV_BLEND_MODE_ADDITIVE);
    lv_style_set_image_opa(&btnStyle, LV_STATE_DEFAULT, 255);
    lv_obj_add_style(button, LV_BTN_PART_MAIN, &btnStyle);
}



/*
 * @brief       void ListTempPage_btnStyle_Init(lv_obj_t *label)
 * @details     编辑参数 按键风格初�?�?(无边�?,标�?蓝色,参数白色)
 */
void ListTempPage_btnStyle_Init(lv_obj_t *label)
{
    if(label == NULL) {
        return ;
    }
    lv_obj_t *button = lv_obj_get_parent(label);
    uint16_t button_width = lv_obj_get_width(button);
    uint16_t button_height = lv_obj_get_height(button);
    lv_label_set_long_mode(label, LV_LABEL_LONG_BREAK);
    lv_obj_set_size(label, button_width, button_height);
    lv_obj_align(label, button, LV_ALIGN_IN_RIGHT_MID, 0, 0);
    lv_label_set_align(label, LV_LABEL_ALIGN_RIGHT);
    extern lv_font_t MultFont_16;
    //标�?
    lv_style_t *plabelStyle = lv_obj_get_local_style(label, LV_LABEL_PART_MAIN);
    static lv_style_t labelStyle = {0};
    //    lv_style_copy(&labelStyle, plabelStyle);
    lv_style_init(&labelStyle);
    lv_obj_clean_style_list(label, LV_LABEL_PART_MAIN);
    lv_style_set_text_font(&labelStyle, LV_STATE_DEFAULT, &MultFont_16);
    lv_style_set_text_font(&labelStyle, LV_STATE_FOCUSED, &MultFont_16);
    lv_style_set_text_color(&labelStyle, LV_STATE_DEFAULT, lv_color_make(255, 255, 255));
    lv_style_set_text_color(&labelStyle, LV_STATE_FOCUSED, lv_color_make(255, 255, 255));
    lv_style_set_text_sel_color(&labelStyle, LV_STATE_FOCUSED, lv_color_make(255, 255, 255));
    lv_style_set_text_sel_color(&labelStyle, LV_STATE_DEFAULT, lv_color_make(255, 255, 255));
    lv_style_set_text_sel_bg_color(&labelStyle, LV_STATE_FOCUSED, lv_color_make(0, 0, 255));
    lv_style_set_text_sel_bg_color(&labelStyle, LV_STATE_DEFAULT, lv_color_make(0, 0, 0));
    lv_style_set_text_letter_space(&labelStyle, LV_STATE_FOCUSED, 2);
    lv_style_set_text_letter_space(&labelStyle, LV_STATE_DEFAULT, 2);
    lv_obj_add_style(label, LV_LABEL_PART_MAIN, &labelStyle);
    //    UI_Label_Value_Style_Load(label);
    //按键
    lv_style_t *pbtnStyle = lv_obj_get_local_style(button, LV_BTN_PART_MAIN);
    static lv_style_t btnStyle = {0};
    //    lv_style_copy(&btnStyle, pbtnStyle);
    lv_style_init(&btnStyle);
    lv_obj_clean_style_list(button, LV_BTN_PART_MAIN);
    lv_style_set_bg_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(50, 50, 50));
    lv_style_set_bg_opa(&btnStyle, LV_STATE_DEFAULT, 0);
    lv_style_set_border_width(&btnStyle, LV_STATE_DEFAULT, 0);
    lv_style_set_border_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(0, 255, 255));
    lv_style_set_value_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(0, 255, 255));
    lv_style_set_value_font(&btnStyle, LV_STATE_DEFAULT, &MultFont_16);
    lv_style_set_radius(&btnStyle, LV_STATE_DEFAULT, 0);
    lv_style_set_value_align(&btnStyle, LV_STATE_DEFAULT, LV_ALIGN_IN_LEFT_MID);
    lv_style_set_value_ofs_x(&btnStyle, LV_STATE_DEFAULT, 5);
    lv_style_set_value_opa(&btnStyle, LV_STATE_DEFAULT, 255);
    lv_obj_add_style(button, LV_BTN_PART_MAIN, &btnStyle);
    //重绘
    lv_obj_invalidate(label);
    lv_obj_invalidate(button);
}


/*
 * @brief       void DelayTempPage_btnStyle_Init(lv_obj_t *label)
 * @details     编辑参数 按键风格初�?�?(无边�?,标�?浅蓝�?,参数白色)
 */
void DelayTempPage_btnStyle_Init(lv_obj_t *label)
{
    extern lv_font_t MultFont_16;
    if(label == NULL) {
        return ;
    }
    lv_obj_t *button = lv_obj_get_parent(label);
    uint16_t button_width = lv_obj_get_width(button);
    uint16_t button_height = lv_obj_get_height(button);
    lv_label_set_long_mode(label, LV_LABEL_LONG_BREAK);
    lv_obj_set_size(label, button_width - 40, button_height);
    lv_obj_align(label, button, LV_ALIGN_IN_RIGHT_MID, -20, 0);
    lv_label_set_align(label, LV_LABEL_ALIGN_RIGHT);
    //标�?
    lv_style_t *plabelStyle = lv_obj_get_local_style(label, LV_LABEL_PART_MAIN);
    static lv_style_t labelStyle = {0};
    //    lv_style_copy(&labelStyle, plabelStyle);
    lv_style_init(&labelStyle);
    lv_obj_clean_style_list(label, LV_LABEL_PART_MAIN);
    lv_style_set_text_font(&labelStyle, LV_STATE_DEFAULT, &MultFont_16);
    lv_style_set_text_font(&labelStyle, LV_STATE_FOCUSED, &MultFont_16);
    lv_style_set_text_color(&labelStyle, LV_STATE_DEFAULT, lv_color_make(255, 255, 255));
    lv_style_set_text_color(&labelStyle, LV_STATE_FOCUSED, lv_color_make(255, 255, 255));
    lv_style_set_text_sel_color(&labelStyle, LV_STATE_FOCUSED, lv_color_make(255, 255, 255));
    lv_style_set_text_sel_color(&labelStyle, LV_STATE_DEFAULT, lv_color_make(255, 255, 255));
    lv_style_set_text_sel_bg_color(&labelStyle, LV_STATE_FOCUSED, lv_color_make(0, 0, 255));
    lv_style_set_text_sel_bg_color(&labelStyle, LV_STATE_DEFAULT, lv_color_make(0, 0, 0));
    lv_style_set_text_letter_space(&labelStyle, LV_STATE_FOCUSED, 2);
    lv_style_set_text_letter_space(&labelStyle, LV_STATE_DEFAULT, 2);
    lv_obj_add_style(label, LV_LABEL_PART_MAIN, &labelStyle);
    //    UI_Label_Value_Style_Load(label);
    //按键
    lv_style_t *pbtnStyle = lv_obj_get_local_style(button, LV_BTN_PART_MAIN);
    static lv_style_t btnStyle = {0};
    //    lv_style_copy(&btnStyle, pbtnStyle);
    lv_style_init(&btnStyle);
    lv_obj_clean_style_list(button, LV_BTN_PART_MAIN);
    lv_style_set_bg_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(50, 50, 50));
    lv_style_set_bg_opa(&btnStyle, LV_STATE_DEFAULT, 0);
    lv_style_set_border_width(&btnStyle, LV_STATE_DEFAULT, 0);
    lv_style_set_value_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(0, 255, 255));
    lv_style_set_value_font(&btnStyle, LV_STATE_DEFAULT, &MultFont_16);
    lv_style_set_radius(&btnStyle, LV_STATE_DEFAULT, 0);
    lv_style_set_value_align(&btnStyle, LV_STATE_DEFAULT, LV_ALIGN_IN_LEFT_MID);
    lv_style_set_value_ofs_x(&btnStyle, LV_STATE_DEFAULT, 5);
    lv_style_set_value_opa(&btnStyle, LV_STATE_DEFAULT, 255);
    lv_obj_add_style(button, LV_BTN_PART_MAIN, &btnStyle);
    //重绘
    lv_obj_invalidate(label);
    lv_obj_invalidate(button);
}


