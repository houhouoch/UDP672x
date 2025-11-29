#include "MenuPage.h"
#include "btnTree.h"
#include "MonitorPage.h"
#include "triggerPage.h"
#include "SettingPage.h"
#include "OutOptionPage.h"
#include "GroupPage.h"

#include "Interface.h"
#include "Setting_Interface.h"

Tree_Def *tree_menu;
Tree_Def *tree_language;



#define UTILITY_ITEM_COUNT 6

#if USE_BATTESTER
    #define ITEM_MIN_IDX 0
#else
    #define ITEM_MIN_IDX 1
#endif
#define ITEM_MAX_IDX (UTILITY_ITEM_COUNT-1)

int8_t selItem_idx = ITEM_MIN_IDX;
void Menu_SelItem(int8_t idx)
{
    lv_obj_t *btn_item = NULL;
    switch(idx)
    {
        case 0: {
            btn_item = ui.Menu_btn_batTester;
        }
        break;
        case 1: {
            btn_item = ui.Menu_btn_monitor;
        }
        break;
        case 2: {
            btn_item = ui.Menu_btn_outOption;
        }
        break;
        case 3: {
            btn_item = ui.Menu_btn_option;
        }
        break;
        case 4: {
            btn_item = ui.Menu_btn_group;
        }
        break;
        case 5: {
            btn_item = ui.Menu_btn_language;
        }
        break;
        default :
            return;
    }
    selItem_idx = idx;
    lv_obj_t *imgSel = ui.Menu_img_itemSel;
    uint16_t x = 0, y = 0;
    uint16_t width = 0, height = 0;
    x = lv_obj_get_x(btn_item);
    y = lv_obj_get_y(btn_item);
    width = lv_obj_get_width(btn_item);
    height = lv_obj_get_height(btn_item);
    lv_obj_set_pos(imgSel, x, y);
    lv_obj_set_size(imgSel, width, height);
    lv_obj_set_hidden(imgSel, 0);
}

#include "SettingData.h"

typedef struct {
    uint8_t value;
    const MultStr_Def *multStr;
} valueString_Def;
static const char *valueStr_GetStr(uint8_t value, const valueString_Def *valueStr)
{
    for(uint8_t i = 0; valueStr[i].multStr != NULL; ++i) {
        if(valueStr[i].value == value) {
            return MultStr_GetS(valueStr[i].multStr);
        }
    }
    return "";
}

/*
 * @brief       void Language_handler(lv_obj_t *obj,lv_event_t event)
 * @details     系统语言设置
 */
void Language_handler(lv_obj_t *obj, lv_event_t event)
{
    const valueString_Def valueStr[] = {
        {LANGUAGE_EN, &mStr_EN},
        {LANGUAGE_CH, &mStr_CH},
        {LANGUAGE_DE, &mStr_DE},
        {0},
    };
    switch(event)
    {
        case LV_EVENT_CLICKED: {
            uint8_t temp = LANGUAGE_SET;
            if(temp < LANGUAGE_MAX) { temp++; }
            else { temp = LANGUAGE_MIN; }
            UI_IF_System_Language_Set(temp);
            Tree_UI_Sel_Exit();
        }
        case LV_EVENT_REFRESH: {
            const char *str = valueStr_GetStr(LANGUAGE_SET, valueStr);
            BtnLabel_Set_Edit_Tag(obj, str);
        }
        break;
    }
}

void Menu_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    event = event;
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                case LV_KEY_DOWN: {
                    if(selItem_idx < ITEM_MAX_IDX) {
                        selItem_idx++;
                    }
                    Menu_SelItem(selItem_idx);
                }
                break;
                case LV_KEY_UP: {
                    if(selItem_idx > ITEM_MIN_IDX) {
                        selItem_idx--;
                    }
                    Menu_SelItem(selItem_idx);
                }
                break;
                case LV_KEY_ENCODER:
                case LV_KEY_ENTER: {
                    switch(selItem_idx)
                    {
                        case 0:     //电池测试器
                            Tree_UI_Sel_Enter(tree_BatTester, 0);;
                            break;
                        case 1:     //监视器
                            Tree_UI_Sel_Enter(tree_monitor, 0);;
                            break;
                        case 2:     //输出设置
                            Tree_UI_Sel_Enter(tree_outoption, 0);
                            break;
                        case 3:     //系统设置
                            Tree_UI_Sel_Enter(tree_setting, 0);
                            break;
                        case 4:     //用户组
                            Tree_UI_Sel_Enter(tree_group, 0);
                            break;
                        case 5:
                            Tree_UI_Sel_Enter(tree_language, 0);
                            break;
                    }
                }
                break;
            }
        }
        break;
        case LV_EVENT_REFRESH: {
            BtnLabel_Set_Edit_Value(ui.Menu_btn_batTester_label, MultStr_GetS(&mStr_BatteryTester));
            BtnLabel_Set_Edit_Value(ui.Menu_btn_monitor_label, MultStr_GetS(&mStr_Monitor));
            BtnLabel_Set_Edit_Value(ui.Menu_btn_outOption_label, MultStr_GetS(&mStr_OutOption));
            BtnLabel_Set_Edit_Value(ui.Menu_btn_option_label, MultStr_GetS(&mStr_Setting));
            BtnLabel_Set_Edit_Value(ui.Menu_btn_group_label, MultStr_GetS(&mStr_Group));
            BtnLabel_Set_Edit_Value(ui.Menu_btn_language_label, MultStr_GetS(&mStr_Language));
        }
        break;
    }
}



void Menu_btnStyle_Init(lv_obj_t *label)
{
    extern lv_font_t MultFont_16;
    if(label == NULL) {
        return ;
    }
    lv_obj_t *button = lv_obj_get_parent(label);
    if(button == NULL) {
        return ;
    }
    uint16_t button_width = lv_obj_get_width(button);
    uint16_t button_height = lv_obj_get_height(button);
    lv_label_set_long_mode(label, LV_LABEL_LONG_BREAK);
    lv_obj_set_size(label, button_width - 70, button_height);
    lv_obj_align(label, button, LV_ALIGN_IN_RIGHT_MID, 0, 0);
    lv_label_set_align(label, LV_LABEL_ALIGN_LEFT);
    //标签
    lv_style_t *plabelStyle = lv_obj_get_local_style(label, LV_LABEL_PART_MAIN);
    static lv_style_t labelStyle = {0};
    lv_style_copy(&labelStyle, plabelStyle);
    lv_obj_clean_style_list(label, LV_LABEL_PART_MAIN);
    lv_style_set_text_letter_space(&labelStyle, LV_STATE_DEFAULT, 1);
    lv_style_set_text_font(&labelStyle, LV_STATE_DEFAULT, &MultFont_16);
    lv_style_set_text_color(&labelStyle, LV_STATE_DEFAULT, lv_color_make(255, 255, 255));
    lv_style_set_text_sel_color(&labelStyle, LV_STATE_DEFAULT, lv_color_make(255, 255, 255));
    lv_style_set_text_sel_bg_color(&labelStyle, LV_STATE_DEFAULT, lv_color_make(0, 0, 0));
    lv_obj_add_style(label, LV_LABEL_PART_MAIN, &labelStyle);
    //按键
    lv_style_t *pbtnStyle = lv_obj_get_local_style(button, LV_BTN_PART_MAIN);
    static lv_style_t btnStyle = {0};
    lv_style_copy(&btnStyle, pbtnStyle);
    lv_obj_clean_style_list(button, LV_BTN_PART_MAIN);
    lv_style_set_value_line_space(&btnStyle, LV_STATE_DEFAULT, 1);
    lv_style_set_value_letter_space(&btnStyle, LV_STATE_DEFAULT, 1);
    lv_style_set_value_ofs_x(&btnStyle, LV_STATE_DEFAULT, -10);
    lv_style_set_value_align(&btnStyle, LV_STATE_DEFAULT, LV_ALIGN_IN_RIGHT_MID);
    lv_style_set_value_font(&btnStyle, LV_STATE_DEFAULT, &MultFont_16);
    lv_style_set_value_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(255, 255, 255));
    lv_style_set_bg_opa(&btnStyle, LV_STATE_DEFAULT, 0x10);
    lv_style_set_bg_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_border_width(&btnStyle, LV_STATE_DEFAULT, 1);
    lv_style_set_border_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
    lv_style_set_radius(&btnStyle, LV_STATE_DEFAULT, 0);
    lv_obj_add_style(button, LV_BTN_PART_MAIN, &btnStyle);
    //重绘
    lv_obj_invalidate(label);
    lv_obj_invalidate(button);
}





/*
 * @brief       void MenuPage_Enter(void)
 * @details     进入Menu页面
 */
void MenuPage_Enter(void)
{
    lv_obj_set_hidden(ui.Menu_cont, 0);
    lv_event_send_refresh_recursive(ui.Menu_cont);
    Menu_SelItem(ITEM_MIN_IDX);
}

/*
 * @brief       void MenuPage_Exit(void)
 * @details     退出Menu页面
 */
void MenuPage_Exit(void)
{
    lv_obj_set_hidden(ui.Menu_cont, 1);
}

extern void MenuPage_btnStyle_Init(lv_obj_t *label);
void MenuPage_GroupCreate(void)
{
    {
        setup_scr_Menu(&ui);
        lv_obj_set_parent(ui.Menu_cont, ui.Back_cont_back);
    }
    MenuPage_Exit();
    Menu_btnStyle_Init(ui.Menu_btn_batTester_label);
    Menu_btnStyle_Init(ui.Menu_btn_monitor_label);
    Menu_btnStyle_Init(ui.Menu_btn_outOption_label);
    Menu_btnStyle_Init(ui.Menu_btn_option_label);
    Menu_btnStyle_Init(ui.Menu_btn_group_label);
    Menu_btnStyle_Init(ui.Menu_btn_language_label);
    lv_obj_set_hidden(ui.Menu_list_1, 1);
    #if USE_BATTESTER
    #else
    lv_obj_set_hidden(ui.Menu_btn_batTester, 1);
    lv_obj_set_hidden(ui.Menu_img_batTester, 1);
    lv_obj_set_pos(ui.Menu_btn_monitor, lv_obj_get_x(ui.Menu_btn_monitor), lv_obj_get_y(ui.Menu_btn_monitor) - 25);
    lv_obj_set_pos(ui.Menu_btn_outOption, lv_obj_get_x(ui.Menu_btn_outOption), lv_obj_get_y(ui.Menu_btn_outOption) - 25);
    lv_obj_set_pos(ui.Menu_btn_option, lv_obj_get_x(ui.Menu_btn_option), lv_obj_get_y(ui.Menu_btn_option) - 25);
    lv_obj_set_pos(ui.Menu_btn_group, lv_obj_get_x(ui.Menu_btn_group), lv_obj_get_y(ui.Menu_btn_group) - 25);
    lv_obj_set_pos(ui.Menu_btn_language, lv_obj_get_x(ui.Menu_btn_language), lv_obj_get_y(ui.Menu_btn_language) - 25);
    lv_obj_set_pos(ui.Menu_img_monitor, lv_obj_get_x(ui.Menu_img_monitor), lv_obj_get_y(ui.Menu_img_monitor) - 25);
    lv_obj_set_pos(ui.Menu_img_outOption, lv_obj_get_x(ui.Menu_img_outOption), lv_obj_get_y(ui.Menu_img_outOption) - 25);
    lv_obj_set_pos(ui.Menu_img_option, lv_obj_get_x(ui.Menu_img_option), lv_obj_get_y(ui.Menu_img_option) - 25);
    lv_obj_set_pos(ui.Menu_img_group, lv_obj_get_x(ui.Menu_img_group), lv_obj_get_y(ui.Menu_img_group) - 25);
    lv_obj_set_pos(ui.Menu_img_language, lv_obj_get_x(ui.Menu_img_language), lv_obj_get_y(ui.Menu_img_language) - 25);
    #endif
    //    lv_obj_set_parent(ui.Menu_img_batTester,ui.Menu_btn_batTester);
    //    lv_obj_align(ui.Menu_img_batTester,ui.Menu_btn_batTester,LV_ALIGN_IN_LEFT_MID,0,0);
    //    lv_obj_set_
}


