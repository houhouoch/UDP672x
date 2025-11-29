#ifndef _TRIGGER_PAGE_H_
#define _TRIGGER_PAGE_H_

#include "Commd.h"
#include "Trigger.h"
#include "btnTree.h"
extern Tree_Def *tree_trigger;

void TriggerPage_Enter(void);
void TriggerPage_Exit(void);
void TriggerPage_GroupCreate(void);

/*
 * @brief       void TriggerPage_handler(lv_obj_t *obj, lv_event_t event)
 * @details     TriggerPage触发器事件处理
 */
void TriggerPage_handler(lv_obj_t *obj, lv_event_t event);

#endif
