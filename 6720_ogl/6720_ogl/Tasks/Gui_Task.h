#ifndef _GUI_TASK_H
#define _GUI_TASK_H
#include "main.h"
#include "lvgl.h"
#include "gui_guider.h"

/* 1) 页面 ID */
typedef enum {
    PAGE_HOME = 0,
    PAGE_SETUP,
    PAGE_MAX
} page_id_t;

/* 2) 导航状态 */
typedef struct {
    lv_obj_t   *content;             // 顶栏下的承载容器（screen_1_body）
    lv_obj_t   *pages[PAGE_MAX];     // 预留：如需存页面根
    page_id_t   current;             // 当前页
    lv_obj_t   *focuser;             // 1x1 焦点占位控件
    lv_group_t *group;               // 全局 group（复用 encoder_group）
} ui_nav_t;
extern bool handle_OUT_ONOFF_hotkey(uint32_t key, lv_event_t *e);
extern ui_nav_t g_nav;
extern bool OUT_ONOFF_led_on ;
extern void ui_onoff_update(bool on);
/* API */
void ui_build(void);                 // 创建 UI
void pages_build(lv_ui *ui);         // 创建两页并挂载
void show_page(page_id_t id);        // 切换页
void show_page_toggle(void);         // 来回切换
void bind_global_keys(lv_obj_t *root);
void GuiTask(void *argument);

#endif /* _GUI_TASK_H */
