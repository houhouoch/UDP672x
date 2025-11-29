#ifndef _MENU_PAGE_H_
#define _MENU_PAGE_H_

#include "Commd.h"

/*
 * @brief       void Language_handler(lv_obj_t *obj,lv_event_t event)
 * @details     系统语言设置
 */
void Language_handler(lv_obj_t *obj, lv_event_t event);
void Menu_handler(lv_obj_t *obj, lv_event_t event);

/*
 * @brief       void MenuPage_Enter(void)
 * @details     进入Menu页面
 */
void MenuPage_Enter(void);

/*
 * @brief       void MenuPage_Exit(void)
 * @details     退出Menu页面
 */
void MenuPage_Exit(void);

void MenuPage_GroupCreate(void);

#include "BtnTree.h"
extern Tree_Def *tree_menu;
extern Tree_Def *tree_language;
#endif