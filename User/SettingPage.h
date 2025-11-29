#ifndef _SETTINGPAGE_H_
#define _SETTINGPAGE_H_

#include "Commd.h"
#include "SettingPage_item.h"

#define SETTING_MAX_DISP_COUNT  5

/*
 * @brief       void SettingPage_Enter(void)
 * @details     进入Setting页面
 */
void SettingPage_Enter(void);

/*
 * @brief       void SettingPage_Exit(void)
 * @details     退出Setting页面
 */
void SettingPage_Exit(void);

void SettingPage_GroupCreate(void);

void SettingTable_handler(lv_obj_t *obj, lv_event_t event);


#include "BtnTree.h"
extern Tree_Def *tree_setting;



/*
 * @brief       void About_Enter(void)
 * @details     进入About页面
 */
void About_Enter(void);
/*
 * @brief       void About_Exit(void)
 * @details     退出About页面
 */
void About_Exit(void);
void About_GroupCreate(void);
void About_handler(lv_obj_t *obj, lv_event_t event);
#endif
