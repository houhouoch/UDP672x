#ifndef __LISTPAGE_MANAGER_H_
#define __LISTPAGE_MANAGER_H_

#include "Commd.h"

/*
 * @brief       void ListPage_Enter(void)
 * @details     进入List管理页面
 */
void ListPage_Manager_Enter(void);

/*
 * @brief       void ListPage_Exit(void)
 * @details     退出List管理页面
 */
void ListPage_Manager_Exit(void);

void ListPage_Manager_GroupCreate(void);

void ListPage_Manager_Table_handler(lv_obj_t *obj, lv_event_t event);
#endif
