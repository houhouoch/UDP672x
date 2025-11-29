#ifndef _SETTINGPAGE_ITEM_H_
#define _SETTINGPAGE_ITEM_H_

#include "Commd.h"



void Brightness_handler(lv_obj_t *obj, lv_event_t event);
void Beep_handler(lv_obj_t *obj, lv_event_t event);
void Power_Setting_handler(lv_obj_t *obj, lv_event_t event);

void Comm_BaudRate_handler(lv_obj_t *obj, lv_event_t event);
void Comm_Protocol_handler(lv_obj_t *obj, lv_event_t event);
void Comm_Protocol_Address_handler(lv_obj_t *obj, lv_event_t event);

void IP_handler(lv_obj_t *obj, lv_event_t event);
void GateWay_handler(lv_obj_t *obj, lv_event_t event);
void NetMask_handler(lv_obj_t *obj, lv_event_t event);
void DHCP_handler(lv_obj_t *obj, lv_event_t event);


void Reboot_handler(lv_obj_t *obj, lv_event_t event);

#endif
