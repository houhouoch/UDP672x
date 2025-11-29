#include "SWPage.h"
#include "Style.h"
lv_group_t *Group_swPage = NULL;
lv_obj_t *swPageBtnm = NULL;
static void switchPage_event_handler(lv_obj_t *obj, lv_event_t event)
{
    switch(event)
    {
        case LV_EVENT_KEY:
        {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            int16_t focusIndex = lv_btnmatrix_get_focused_btn(obj);
            switch(key)
            {
                case LV_KEY_ENTER: {
                    SwitchPage(focusIndex);
                }
                break;
                case LV_KEY_ESC: {
                    SwitchPage(PAGE_BACK);
                }
                break;
            }
        }
        break;
    }
}


void SwitchPageCreate(void)
{
    static const char *btnm_map[] = {" 主页", " 输出设置", " List输出", "\n",
                                     " 系统设置", " 校准", ""
                                    };
    extern lv_font_t lv_userFont;
    swPageBtnm = lv_btnmatrix_create(lv_scr_act(), NULL);
    lv_btnmatrix_set_map(swPageBtnm, btnm_map);
    lv_obj_set_size(swPageBtnm, 320, 106);
    lv_btnmatrix_set_btn_width(swPageBtnm, 10, 2);        /*Make "Action1" twice as wide as "Action2"*/
    lv_obj_align(swPageBtnm, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_event_cb(swPageBtnm, switchPage_event_handler);
    lv_obj_set_style_local_bg_opa(swPageBtnm, LV_BTNMATRIX_PART_BTN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_text_font(swPageBtnm, LV_BTNMATRIX_PART_BTN, LV_STATE_DEFAULT, &lv_font_SourceHanSans_16);
    lv_obj_set_style_local_bg_opa(swPageBtnm, LV_BTNMATRIX_PART_BG, LV_STATE_DEFAULT, 200);
    lv_obj_set_style_local_border_opa(swPageBtnm, LV_BTNMATRIX_PART_BG, LV_STATE_DEFAULT, 200);
    lv_obj_set_style_local_border_color(swPageBtnm, LV_BTNMATRIX_PART_BG, LV_STATE_DEFAULT, lv_color_make(100, 205, 217));
    //lv_obj_set_style_local_opa_scale(btnm1,LV_BTNMATRIX_PART_BG,LV_STATE_DEFAULT,LV_OPA_80);
    lv_obj_set_top(swPageBtnm, 1);
    Group_swPage = lv_group_create();
    lv_group_add_obj(Group_swPage, swPageBtnm);
    lv_obj_set_hidden(swPageBtnm, 1);
    UI_BtnMatrix_Style_Load(swPageBtnm);
}
