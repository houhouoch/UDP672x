#ifndef _OUTOPTIONPAGE_H_
#define _OUTOPTIONPAGE_H_

#include "Commd.h"

#define OUTOPTION_MAX_DISP_COUNT  6

/*
 * @brief       void OutOptionPage_Enter(void)
 * @details     进入OutOption页面
 */
void OutOptionPage_Enter(void);

/*
 * @brief       void OutOptionPage_Exit(void)
 * @details     退出OutOption页面
 */
void OutOptionPage_Exit(void);

void OutOptionPage_GroupCreate(void);

void OutOptionTable_handler(lv_obj_t *obj, lv_event_t event);


#include "BtnTree.h"
extern Tree_Def *tree_outoption;

#endif
