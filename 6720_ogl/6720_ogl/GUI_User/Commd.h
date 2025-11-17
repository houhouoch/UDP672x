#ifndef __UI_COMMD_H_
#define __UI_COMMD_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lvgl.h"
#include "gui_guider.h"

#include "Beep_Device.h"



//使用看门狗
#define USE_WDG (1)




/*
 * @brief       lv_key_t Button_toKey(uint8_t buttonNum,uint8_t flag)
 * @details     将实体按键转为LV_KEY事件
 */
lv_key_t Button_toKey(uint8_t buttonNum, uint8_t flag);

void GUI_KeySend(lv_obj_t *obj, lv_key_t key);









#endif
