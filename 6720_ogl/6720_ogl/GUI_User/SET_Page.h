#ifndef SET_PAGE_H
#define SET_PAGE_H

#include "lvgl.h"
#include "gui_guider.h"    // 提供 lv_ui

/* 初始化：记录 screen_2 上要参与导航的 7 个按钮 */
void SET_Page_init(lv_ui *ui);

/* 进入 screen_2：把按钮加入 encoder_group，并默认聚焦第一个 */
void SET_Page_enter(lv_group_t *group);

/* 离开 screen_2：把按钮从 group 移除，把焦点交还 fallback_focus（通常是你的 focuser） */
void SET_Page_leave(lv_group_t *group, lv_obj_t *fallback_focus);

/* 是否处于 screen_2 导航模式（用于避免你在按键尾部“抢回焦点”） */
bool SET_Page_is_active(void);


#endif /* SET_PAGE_H */
