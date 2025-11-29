//无List

#ifndef _BATTERY_TESTER_PAGE_H_
#define _BATTERY_TESTER_PAGE_H_

#include "Commd.h"





/*
 * @brief       void BatteryTester_Page_Enter(void)
 * @details     进入BatteryTester页面
 */
void BatteryTester_Page_Enter(void);

/*
 * @brief       void BatteryTester_Page_Exit(void)
 * @details     退出BatteryTester页面
 */
void BatteryTester_Page_Exit(void);

void BatteryTester_Page_GroupCreate(void);

void BatteryTester_Page_Table_handler(lv_obj_t *obj, lv_event_t event);

#include "BtnTree.h"

extern Tree_Def *tree_BatTester;
extern Tree_Def *tree_BatTester_option;
extern Tree_Def *tree_BatTester_start;
extern Tree_Def *tree_BatTester_end;
extern Tree_Def *tree_BatTester_cycles;

extern Tree_Def *tree_BatTester_table;
extern Tree_Def *tree_BatTester_Vout;
extern Tree_Def *tree_BatTester_Iout;
extern Tree_Def *tree_BatTester_keepT;

extern Tree_Def *tree_BatTester_tipsSet;
extern Tree_Def *tree_BatTester_protect;
extern Tree_Def *tree_BatTester_trigTime;

extern Tree_Def *tree_BatTester_manage;

extern Tree_Def *tree_BatTester_btn_start;
extern Tree_Def *tree_BatTester_btn_pause;
#endif
