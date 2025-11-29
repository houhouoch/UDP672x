#ifndef _BATTERYTESTER_PAGE_OPTION_H_
#define _BATTERYTESTER_PAGE_OPTION_H_

#include "Commd.h"

void BatTester_Option_editStartP_handler(lv_obj_t *obj, lv_event_t event);
void BatTester_Option_editCount_handler(lv_obj_t *obj, lv_event_t event);
void BatTester_Option_editCycles_handler(lv_obj_t *obj, lv_event_t event);
void BatTester_Option_editValue_handler(lv_obj_t *obj, lv_event_t event);
void BatTester_Option_editAction_handler(lv_obj_t *obj, lv_event_t event);
void BatTester_Option_LastState_handler(lv_obj_t *obj, lv_event_t event);

void BatTester_Option_TipsSet_handler(lv_obj_t *obj, lv_event_t event);
void BatTester_Option_Protect_Value_0_handler(lv_obj_t *obj, lv_event_t event);
void BatTester_Option_Protect_Logic_1_handler(lv_obj_t *obj, lv_event_t event);
void BatTester_Option_Protect_Value_1_handler(lv_obj_t *obj, lv_event_t event);
void BatTester_Option_Protect_Logic_2_handler(lv_obj_t *obj, lv_event_t event);
void BatTester_Option_Protect_Value_2_handler(lv_obj_t *obj, lv_event_t event);

void BatTester_Option_TrigTime_handler(lv_obj_t *obj, lv_event_t event);


#endif
