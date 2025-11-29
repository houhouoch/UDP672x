#ifndef __BATTESTER_MANAGER_H_
#define __BATTESTER_MANAGER_H_

#include "Commd.h"

/*
 * @brief       void ListPage_Enter(void)
 * @details     进入BatTester管理页面
 */
void BatTester_Page_Manager_Enter(void);

/*
 * @brief       void BatTester_Page_Exit(void)
 * @details     退出BatTester管理页面
 */
void BatTester_Page_Manager_Exit(void);

void BatTester_Page_Manager_GroupCreate(void);

void BatTester_Page_Manager_Table_handler(lv_obj_t *obj, lv_event_t event);
#endif
