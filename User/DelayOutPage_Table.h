#ifndef _DELAYOUT_PAGE_TABLE_H_
#define _DELAYOUT_PAGE_TABLE_H_

#include "Commd.h"


/*
 * @brief       void DelayPage_Table_Refresh(int16_t baseIndex)
 * @details     Ë¢ÐÂDelay±í¸ñ
 */
void DelayPage_Table_Refresh(int16_t baseIndex);

void Delayer_State_Set_handler(lv_obj_t *obj, lv_event_t event);
void Delayer_dT_Set_handler(lv_obj_t *obj, lv_event_t event);

void DelayPage_Table_handler(lv_obj_t *obj, lv_event_t event);

void DelayPage_SetCurrent(int16_t no);
#endif
