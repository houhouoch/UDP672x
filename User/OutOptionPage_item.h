#ifndef _OUTOPTIONPAGE_ITEM_H_
#define _OUTOPTIONPAGE_ITEM_H_

#include "Commd.h"

void Mode_handler(lv_obj_t *obj, lv_event_t event);
void P_Out_handler(lv_obj_t *obj, lv_event_t event);
void DVM_Onoff_handler(lv_obj_t *obj, lv_event_t event);

void SRMode_handler(lv_obj_t *obj, lv_event_t event);
void VSR_Up_handler(lv_obj_t *obj, lv_event_t event);
void VSR_Down_handler(lv_obj_t *obj, lv_event_t event);
void ISR_Up_handler(lv_obj_t *obj, lv_event_t event);
void ISR_Down_handler(lv_obj_t *obj, lv_event_t event);



#endif
