#ifndef _GROUP_PAGE_H_
#define _GROUP_PAGE_H_

#include "Commd.h"
#include "SettingData.h"

#define GROUP_FILE_FLASH_PATH   "FLASH:Group"
#define GROUP_FILE_USB_PATH     "USB:Group"

void GroupTable_handler(lv_obj_t *obj, lv_event_t event);

/*
 * @brief       void GroupPage_Enter(void)
 * @details     进入Group页面
 */
void GroupPage_Enter(void);

/*
 * @brief       void GroupPage_Exit(void)
 * @details     退出Group页面
 */
void GroupPage_Exit(void);

void GroupPage_GroupCreate(void);

void Group_Create(const char *name);
uint8_t Group_Save(Group_Def *pGroup, const char *name);
void Group_Load(Group_Def *pGroup, const char *name);


#include "BtnTree.h"
extern Tree_Def *tree_group;

#endif