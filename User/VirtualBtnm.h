#ifndef _VIRTUAL_BTNM_H_
#define _VIRTUAL_BTNM_H_

#include "Commd.h"

enum {
    BTN_TYPE_DEFAULT = 0,
    BTN_TYPE_SEL,       //对象选择
    BTN_TYPE_KEY,       //虚拟按键
    BTN_TYPE_MORE,      //更多按键
    BTN_TYPE_UI,

    BTN_TYPE_CALL,

    BTN_TYPE_PGUP,      //上一页
    BTN_TYPE_PGDN,      //下一页
};

#pragma pack (1)

//每个按键
struct BtnInfo_Def {
    const MultStr_Def *multStr; //字符串

    uint8_t type;              //虚拟按键类型
    uint8_t noVisable;          //按键不可见

    //BTN_TYPE_SEL
    lv_obj_t **obj;             //事件接收对象(点击后选中)
    lv_event_cb_t evencb;

    //BTN_TYPE_KEY
    lv_key_t key_short;         //虚拟按键
    lv_key_t key_long;

    //BTN_TYPE_UI
    void (*ui_enter)(void);     //UI回调
    void (*ui_exit)(void);      //UI回调

    void (*call)(void);
};

#pragma pack ()


void VirtualBtnm_GroupCreate(void);

/*
 * @brief       void VirtualBtnm_SetBtnmInfo(const struct BtnInfo_Def* info)
 * @details     设置按键表信息
 */
void VirtualBtnm_SetBtnmInfo(const struct BtnInfo_Def *info);



#endif
