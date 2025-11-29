#ifndef _DELAYOUT_PAGE_
#define _DELAYOUT_PAGE_

#include "Commd.h"




/*
 * @brief       void DelayPage_Enter(void)
 * @details     进入DelayOut页面
 */
void DelayPage_Enter(void);

/*
 * @brief       void DelayPage_Exit(void)
 * @details     退出DelayOut页面
 */
void DelayPage_Exit(void);

void DelayPage_GroupCreate(void);

#include "BtnTree.h"
//extern Tree_Def *tree_delay;
//extern Tree_Def *tree_delay_option;
//extern Tree_Def *tree_delay_start;
//extern Tree_Def *tree_delay_end;
//extern Tree_Def *tree_delay_cycles;
//extern Tree_Def *tree_delay_protect;
//extern Tree_Def *tree_delay_protectVal;
//extern Tree_Def *tree_delay_protectAction;

//extern Tree_Def *tree_delay_table;
//extern Tree_Def *tree_delay_Out;
//extern Tree_Def *tree_delay_delayT;


extern Tree_Def *tree_delay;
extern Tree_Def *tree_delay_option;
extern Tree_Def *tree_delay_start;
extern Tree_Def *tree_delay_end;
extern Tree_Def *tree_delay_cycles;
extern Tree_Def *tree_delay_protect;
extern Tree_Def *tree_delay_protectVal;
extern Tree_Def *tree_delay_protectAction;

extern Tree_Def *tree_delay_table;
extern Tree_Def *tree_delay_Out;
extern Tree_Def *tree_delay_delayT;

extern Tree_Def *tree_delay_manage;
extern Tree_Def *tree_delay_temp;


#endif
