#ifndef _LISTPAGE_H_
#define _LISTPAGE_H_

#include "Commd.h"





/*
 * @brief       void ListPage_Enter(void)
 * @details     进入List页面
 */
void ListPage_Enter(void);

/*
 * @brief       void ListPage_Exit(void)
 * @details     退出List页面
 */
void ListPage_Exit(void);

void ListPage_GroupCreate(void);



#include "BtnTree.h"

extern Tree_Def *tree_list;
extern Tree_Def *tree_list_option;
extern Tree_Def *tree_list_start;
extern Tree_Def *tree_list_end;
extern Tree_Def *tree_list_cycles;
extern Tree_Def *tree_list_lastState;

extern Tree_Def *tree_list_table;
extern Tree_Def *tree_list_Vout;
extern Tree_Def *tree_list_Iout;
extern Tree_Def *tree_list_keepT;

extern Tree_Def *tree_list_preview;
extern Tree_Def *tree_list_manage;
extern Tree_Def *tree_list_temp;
extern Tree_Def *tree_list_tempEdit;

extern Tree_Def *tree_list_btn_start;
extern Tree_Def *tree_list_btn_pause;
#endif
