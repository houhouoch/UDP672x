#ifndef _LISTPAGE_TABLE_H_
#define _LISTPAGE_TABLE_H_

#include "Commd.h"

void List_Volt_Set_handler(lv_obj_t *obj, lv_event_t event);
void List_Curr_Set_handler(lv_obj_t *obj, lv_event_t event);
void List_Time_Set_handler(lv_obj_t *obj, lv_event_t event);

void ListPage_Table_handler(lv_obj_t *obj, lv_event_t event);

void ListPage_SetCurrent(int16_t no);
#endif
