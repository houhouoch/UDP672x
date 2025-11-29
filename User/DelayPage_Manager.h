#ifndef __DELAYPAGE_MANAGER_H_
#define __DELAYPAGE_MANAGER_H_

#include "Commd.h"

/*
 * @brief       void DelayPage_Enter(void)
 * @details     进入List管理页面
 */
void DelayPage_Manager_Enter(void);

/*
 * @brief       void DelayPage_Exit(void)
 * @details     退出Delay管理页面
 */
void DelayPage_Manager_Exit(void);

void DelayPage_Manager_GroupCreate(void);

void DelayPage_Manager_Table_handler(lv_obj_t *obj, lv_event_t event);
#endif
