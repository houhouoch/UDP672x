#include "SettingPage.h"
#include "SettingPage_item.h"
#include "SettingData.h"
#include "Setting_Interface.h"

Tree_Def *tree_setting;

#if 0
#include "BtnTree.h"
#define SETTING_ITEM_MAX_COUNT (6)
typedef struct {
    Tree_Def *tree;
    void (*handler)(lv_obj_t *obj, lv_event_t event);
} SettingItem_Def;

typedef struct {
    SettingItem_Def Item [SETTING_ITEM_MAX_COUNT];
    int16_t baseIdx;
} SettingTable_Def;

SettingTable_Def settingTable = {0};
#endif


void SettingTable_handler(lv_obj_t *obj, lv_event_t event)
{
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key) {
                case LV_KEY_SAVE: {
                    UI_IF_System_LAN_Apply(1);
                }
                break;
                //恢复出厂设置
                case LV_KEY_LOADDEFAULT: {
                    IF_MsgBox_Tips_Mult(&mStr_LoadDefault_Tips);
                }
                break;
                case LV_KEY_LOADDEFAULT_LONGP: {
                    //关闭电源输出
                    UI_IF_Power_Set_On_Off(0);
                    //加载默认设置
                    __System_LoadDefault();
                    //重新加载参数
                    void __Load_Option_Setting(void);
                    void __Load_OutPut_Setting(void);
                    __Load_Option_Setting();
                    __Load_OutPut_Setting();
                }
                break;
            }
        }
        break;
    }
}


static void Tabel_Btn_Style_Init(lv_obj_t *label)
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
    //    lv_style_set_bg_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(50, 50, 50));
    //    lv_style_set_bg_opa(&btnStyle, LV_STATE_DEFAULT, 0);
    //    lv_style_set_bg_color(&btnStyle, LV_STATE_FOCUSED, lv_color_make(50, 50, 50));
    //    lv_style_set_bg_opa(&btnStyle, LV_STATE_FOCUSED, 255);
    //    lv_style_set_border_width(&btnStyle, LV_STATE_DEFAULT, 0);
    //    lv_style_set_border_width(&btnStyle, LV_STATE_FOCUSED, 0);
    //    lv_style_set_border_color(&btnStyle, LV_STATE_FOCUSED, lv_color_make(255, 255, 255));
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




/*
 * @brief       void SettingPage_Enter(void)
 * @details     进入Setting页面
 */
void SettingPage_Enter(void)
{
    lv_obj_set_hidden(ui.Setting_cont_1, 0);
    lv_event_send_refresh_recursive(ui.Setting_cont_1);
    lv_label_set_text_static(ui.Setting_btn_BaseTitle_label, MultStr_GetS(&mStr_BaseTitle));
    lv_label_set_text_static(ui.Setting_btn_NetTitle_label, MultStr_GetS(&mStr_NetTitle));
    lv_label_set_text_static(ui.Setting_btn_CommTitle_label, MultStr_GetS(&mStr_CommTitle));
}

/*
 * @brief       void SettingPage_Exit(void)
 * @details     退出Setting页面
 */
void SettingPage_Exit(void)
{
    lv_obj_set_hidden(ui.Setting_cont_1, 1);
}

void SettingPage_GroupCreate(void)
{
    //加载UI
    {
        setup_scr_Setting(&ui);
        lv_obj_set_parent(ui.Setting_cont_1, ui.Back_cont_back);
    }
    extern lv_font_t MultFont_16;
    lv_obj_set_style_local_text_font(ui.Setting_btn_BaseTitle_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_16);
    Tabel_Btn_Style_Init(ui.Setting_btn_BackLight_label);
    Tabel_Btn_Style_Init(ui.Setting_btn_Beep_label);
    Tabel_Btn_Style_Init(ui.Setting_btn_PowerDown_label);
    //
    lv_obj_set_style_local_text_font(ui.Setting_btn_CommTitle_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_16);
    Tabel_Btn_Style_Init(ui.Setting_btn_Comm_BaudRate_label);
    Tabel_Btn_Style_Init(ui.Setting_btn_Comm_Protocol_label);
    Tabel_Btn_Style_Init(ui.Setting_btn_Comm_Address_label);
    //
    lv_obj_set_style_local_text_font(ui.Setting_btn_NetTitle_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_16);
    Tabel_Btn_Style_Init(ui.Setting_btn_NetIP_label);
    Tabel_Btn_Style_Init(ui.Setting_btn_GateWay_label);
    Tabel_Btn_Style_Init(ui.Setting_btn_NetMask_label);
    Tabel_Btn_Style_Init(ui.Setting_btn_DHCP_label);
    SettingPage_Exit();
}








/*
 * @brief       void About_Enter(void)
 * @details     进入About页面
 */
void About_Enter(void)
{
    lv_obj_set_hidden(ui.About_cont, 0);
    lv_event_send_refresh_recursive(ui.About_cont);
    lv_label_set_text_static(ui.About_btn_Title_label, MultStr_GetS(&mStr_About));
    //型号
    BtnLabel_Set_Edit_Tag(ui.About_btn_model_label, MultStr_GetS(&mStr_About_Model));
    BtnLabel_Set_Edit_Value(ui.About_btn_model_label, ABOUT_MODEL);
    //序列号
    BtnLabel_Set_Edit_Tag(ui.About_btn_SN_label, MultStr_GetS(&mStr_About_SN));
    if(strlen(systemInfo.about.SN) > 0) {
        BtnLabel_Set_Edit_Value(ui.About_btn_SN_label, systemInfo.about.SN);
    } else {
        BtnLabel_Set_Edit_Value(ui.About_btn_SN_label, "Unknow");
    }
    //引导版本
    BtnLabel_Set_Edit_Tag(ui.About_btn_BootVer_label, MultStr_GetS(&mStr_About_BootVer));
    char bootVer_str[16] = {0};
    extern uint16_t bootloaderVer[3];
    snprintf(bootVer_str, 16, "%d.%02d.%04d", bootloaderVer[0], bootloaderVer[1], bootloaderVer[2]);
    BtnLabel_Set_Edit_Value(ui.About_btn_BootVer_label, bootVer_str);
    //固件版本
    BtnLabel_Set_Edit_Tag(ui.About_btn_firmwVer_label, MultStr_GetS(&mStr_About_FirmwVer));
    BtnLabel_Set_Edit_Value(ui.About_btn_firmwVer_label, FIRMWARE_VER);
}

/*
 * @brief       void About_Exit(void)
 * @details     退出About页面
 */
void About_Exit(void)
{
    lv_obj_set_hidden(ui.About_cont, 1);
}

static void About_Btn_Style_Init(lv_obj_t *label);
void About_GroupCreate(void)
{
    //加载UI
    {
        setup_scr_About(&ui);
        lv_obj_set_parent(ui.About_cont, ui.Back_cont_back);
    }
    lv_obj_align(ui.About_cont, ui.Back_cont_back, LV_ALIGN_CENTER, 0, 0);
    extern lv_font_t MultFont_16;
    lv_obj_set_style_local_text_font(ui.About_btn_Title_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_16);
    About_Btn_Style_Init(ui.About_btn_model_label);
    About_Btn_Style_Init(ui.About_btn_SN_label);
    About_Btn_Style_Init(ui.About_btn_BootVer_label);
    About_Btn_Style_Init(ui.About_btn_firmwVer_label);
    lv_obj_set_style_local_border_color(ui.About_cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0x00, 0x00));
    lv_obj_set_style_local_bg_color(ui.About_cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
    About_Exit();
}


static void About_Btn_Style_Init(lv_obj_t *label)
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
    lv_style_set_text_letter_space(&labelStyle, LV_STATE_DEFAULT, 2);
    lv_style_set_text_font(&labelStyle, LV_STATE_DEFAULT, &MultFont_16);
    lv_style_set_text_color(&labelStyle, LV_STATE_DEFAULT, lv_color_make(255, 255, 255));
    lv_style_set_text_sel_color(&labelStyle, LV_STATE_DEFAULT, lv_color_make(0, 255, 255));
    lv_style_set_text_sel_bg_color(&labelStyle, LV_STATE_DEFAULT, lv_color_make(0, 0, 0));
    lv_obj_add_style(label, LV_LABEL_PART_MAIN, &labelStyle);
    //按键
    lv_style_t *pbtnStyle = lv_obj_get_local_style(button, LV_BTN_PART_MAIN);
    static lv_style_t btnStyle = {0};
    lv_style_init(&btnStyle);
    lv_obj_clean_style_list(button, LV_LABEL_PART_MAIN);
    lv_style_set_border_width(&btnStyle, LV_STATE_DEFAULT, 1);
    lv_style_set_border_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(0x33, 0x33, 0x33));
    lv_style_set_value_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(255, 255, 255));
    lv_style_set_value_font(&btnStyle, LV_STATE_DEFAULT, &MultFont_16);
    //
    //    lv_style_set_bg_opa(&btnStyle, LV_STATE_DEFAULT, 0x10);
    //    lv_style_set_bg_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    //    lv_style_set_border_width(&btnStyle, LV_STATE_DEFAULT, 1);
    //    lv_style_set_border_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
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


