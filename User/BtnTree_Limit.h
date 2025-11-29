#ifndef _BTNTREE_LIMIT_H_
#define _BTNTREE_LIMIT_H_

#include "Btntree.h"

//无效化虚拟按键检测
uint8_t Btn_KeyInvalid_CheckBtn(const struct BtnInfo_Def *btn);

//无效实体按键检测
uint8_t Btn_KeyInvalid_CheckKey(lv_key_t key);

#endif