#include "setup.h"
#include "lvgl.h"
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"
#include "events_init.h"


extern lv_ui guider_ui; // 如果你在别处定义了全局 ui



void Setup_Enter(void)
{
    lv_obj_clear_flag(guider_ui.screen_2_cont_1,   LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.screen_2_SetupContainer,   LV_OBJ_FLAG_HIDDEN);
    // 任选其一：递归发刷新事件，或简单无脑重绘
//    refresh_recursive(guider_ui.screen_cont_Set);
//    refresh_recursive(guider_ui.screen_cont_Out);
    // 或者：lv_obj_invalidate(ui.HomePage_cont_Out); ... 视实际需要
}

/* 退出主页：隐藏 */
void Setup_Exit(void)
{
    lv_obj_add_flag(guider_ui.screen_2_SetupContainer,   LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.screen_2_cont_1,   LV_OBJ_FLAG_HIDDEN);
}




void Setup_GroupCreate(void)
{ 
    lv_ui *ui = &guider_ui;
  
    setup_scr_screen_2(ui);
    lv_obj_set_parent(guider_ui.screen_2_cont_1,guider_ui.screen_1_body);
    lv_obj_set_parent(guider_ui.screen_2_SetupContainer,guider_ui.screen_1_body);
    Setup_Enter();
    Setup_Exit();


}

