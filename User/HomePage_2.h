#ifndef _HOMEPAGE_2_H_
#define _HOMEPAGE_2_H_

#include "Commd.h"




void HomePage_2_handler(lv_obj_t *obj, lv_event_t event);
/*
 * @brief       void HomePage_2_Enter(void)
 * @details     进入主页
 */
void HomePage_2_Enter(void);

/*
 * @brief       void HomePage_2_Exit(void)
 * @details     退出主页
 */
void HomePage_2_Exit(void);

void HomePage_2_GroupCreate(void);


#include "BtnTree.h"
extern Tree_Def *tree_home_2;

#endif
