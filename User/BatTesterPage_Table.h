#ifndef _BATTERY_TESTER_PAGE_TABLE_H_
#define _BATTERY_TESTER_PAGE_TABLE_H_

#include "Commd.h"




void BatteryTester_Page_Table_handler(lv_obj_t *obj, lv_event_t event);

void BatteryTester_Page_SetCurrent(int16_t no);
#endif
