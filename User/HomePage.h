#ifndef _HOMEPAGE_H_
#define _HOMEPAGE_H_

#include "Commd.h"



void volSet_handler(lv_obj_t *obj, lv_event_t event);
void ampSet_handler(lv_obj_t *obj, lv_event_t event);
void volLimit_handler(lv_obj_t *obj, lv_event_t event);
void ampLimit_handler(lv_obj_t *obj, lv_event_t event);
void TimeOff_handler(lv_obj_t *obj, lv_event_t event);

void HomePage_handler(lv_obj_t *obj, lv_event_t event);
/*
 * @brief       void HomePage_Enter(void)
 * @details     进入主页
 */
void HomePage_Enter(void);

/*
 * @brief       void HomePage_Exit(void)
 * @details     退出主页
 */
void HomePage_Exit(void);




void HomePage_GroupCreate(void);

#include "BtnTree.h"
extern Tree_Def *tree_home;
extern Tree_Def *tree_VSet;
extern Tree_Def *tree_ISet;
extern Tree_Def *tree_Vlimit;
extern Tree_Def *tree_Ilimit;
extern Tree_Def *tree_TimeOff;
#endif
