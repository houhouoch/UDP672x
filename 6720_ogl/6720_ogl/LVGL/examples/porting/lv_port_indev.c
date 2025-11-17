#include "lv_port_indev.h"
#include "lvgl.h"
#include "Button_Device.h"
#include "Commd.h"

/* -------- 全局 -------- */
lv_indev_t *indev_encoder = NULL;
lv_group_t *encoder_group = NULL;

/* -------- 本地状态 -------- */
static volatile int16_t rot_pending = 0;        // 待输出的旋钮步数（>0: NEXT / <0: PREV）
static volatile lv_key_t key_pending = 0;       // 待注入的单次按键
static bool edge_release_pending = false;       // 为了产生 press/release 成对事件
static uint32_t last_key = 0;


volatile int16_t pend_right;  // 你的工程已存在
 volatile int16_t pend_left;

static const char* key_name(uint32_t k)
{
    switch(k){
    case LV_KEY_UP:     return "UP";
    case LV_KEY_DOWN:   return "DOWN";
    case LV_KEY_LEFT:   return "LEFT";
    case LV_KEY_RIGHT:  return "RIGHT";
    case LV_KEY_ENTER:  return "ENTER";
    case LV_KEY_ESC:    return "ESC";
    case LV_KEY_MENU:   return "MENU";
    case LV_KEY_NEXT:   return "NEXT";
    case LV_KEY_PREV:   return "PREV";
    /* 你的自定义键，随需添加 */
    case LV_KEY_M1:     return "M1";
    case LV_KEY_M2:     return "M2";
    case LV_KEY_M3:     return "M3";
    case LV_KEY_V:      return "LV_KEY_V";
    case LV_KEY_A:      return "LV_KEY_A";
    case LV_KEY_OUTPUT: return "LV_KEY_OUTPUT";
    case LV_KEY_LOCK:   return "LV_KEY_LOCK";
    case LV_KEY_ENCODER:return "LV_KEY_ENCODER";
    default:            return "UNKNOWN";
    }
}





/* 注入 API（在中断/其他线程里调用） */
void indev_encoder_push_rotate(int steps) {
    rot_pending += steps;
}

void indev_encoder_push_key(lv_key_t key) {
    key_pending = key;
}

/* ---------- read_cb ---------- */
static bool encoder_read(lv_indev_drv_t * drv, lv_indev_data_t * data)
{
    /* 先补 release 边沿 */
    if(edge_release_pending){
        data->key   = last_key;
        data->state = LV_INDEV_STATE_RELEASED;
        edge_release_pending = false;
        //printf("[INDEV][KP] RELEASE key=%s (%d)\r\n", key_name(last_key), (unsigned)last_key);
        return false;
    }

    /* 实体独立按键（MENU/ENTER 等） */
    uint8_t returnKey = 0xff;
    uint8_t stateFlag = keyScan(&returnKey);
    lv_key_t lv_key = Button_toKey(returnKey, stateFlag);   // 你的映射函数
    if(lv_key != LV_KEY_DEFAULT){
        last_key = lv_key;
        data->key   = last_key;
        data->state = LV_INDEV_STATE_PRESSED;
        edge_release_pending = true;

   //  printf("[INDEV][KP] PRESS  key=%s (raw=%d state=%u data:state=%u)\r\n",key_name(last_key), returnKey, stateFlag,data->state);
        return false;
    }

    /* 旋钮转动 -> 映射成 UP/DOWN（或 NEXT/PREV），并打印 */
    if(pend_right > 0){
        pend_right--;
        last_key = LV_KEY_UP;    // 你项目的约定：顺时针=UP
        data->key   = last_key;
        data->state = LV_INDEV_STATE_PRESSED;
        edge_release_pending = true;

       // printf("[ROT->KP] PRESS  key=%s (+1)\r\n", key_name(last_key));
        return false;
    }
    if(pend_left > 0){
        pend_left--;
        last_key = LV_KEY_DOWN;  // 逆时针=DOWN
        data->key   = last_key;
        data->state = LV_INDEV_STATE_PRESSED;
        edge_release_pending = true;

       // printf("[ROT->KP] PRESS  key=%s (-1)\r\n", key_name(last_key));
        return false;
    }

    /* 无输入 */
    data->key   = 0;
    data->state = LV_INDEV_STATE_RELEASED;
    return false;
}

/* ---------- 初始化：只建一个 keypad indev + 一个 group ---------- */
void lv_port_indev_init(void)
{
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type    = LV_INDEV_TYPE_KEYPAD;
    indev_drv.read_cb = encoder_read;
    indev_encoder = lv_indev_drv_register(&indev_drv);

    /* 全局 group：UI 里直接使用 encoder_group（不要再建第二个） */
    encoder_group = lv_group_create();
    lv_indev_set_group(indev_encoder, encoder_group);

    /* 可选：设为默认组，后续创建的可聚焦控件会自动进组 */
    // lv_group_set_default(encoder_group);
}
