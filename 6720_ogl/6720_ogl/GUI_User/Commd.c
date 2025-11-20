#include "Commd.h"

//主页面对象


/* -------------------- 通用快捷键处理 ---------------------- */



#include "Button_Device.h"
//按键映射
typedef struct {
    uint8_t buttonNum;
    uint8_t key_short;
    uint8_t key_long;
    uint8_t key_hold;
} Button_KeyTable_Def;

static const Button_KeyTable_Def Btn_KeyTable[] = {
    {KEY_M1,     LV_KEY_M1,      LV_KEY_M1_LONGP,    LV_KEY_DEFAULT,},
    {KEY_M2,     LV_KEY_M2,      LV_KEY_M2_LONGP,    LV_KEY_DEFAULT,},
    {KEY_M3,     LV_KEY_M3,      LV_KEY_M3_LONGP,    LV_KEY_DEFAULT,},    
    {KEY_LOCK,   LV_KEY_LOCK,    LV_KEY_LOCK_LONGP,  LV_KEY_DEFAULT},  

    {KEY_V,      LV_KEY_V,       LV_KEY_V_LONGP,     LV_KEY_DEFAULT},
    {KEY_A,      LV_KEY_A,       LV_KEY_A_LONGP,     LV_KEY_DEFAULT},
    {KEY_MENU,   LV_KEY_MENU,    LV_KEY_MENU_LONGP,  LV_KEY_DEFAULT}, 
    {KEY_OUTPUT, LV_KEY_OUTPUT,  LV_KEY_OUTPUT,      LV_KEY_DEFAULT},
    
    {KEY_LEFT,   LV_KEY_LEFT,    LV_KEY_LEFT,        LV_KEY_DEFAULT},
    {KEY_RIGHT,  LV_KEY_RIGHT,   LV_KEY_RIGHT,       LV_KEY_DEFAULT}, 
    {KEY_ESC,    LV_KEY_ESC,     LV_KEY_ESC_LONGP,   LV_KEY_DEFAULT},
    {KEY_ENTER,  LV_KEY_ENTER,   LV_KEY_ENTER_LONGP, LV_KEY_DEFAULT},
        
    {KEY_CODER_OK,    LV_KEY_ENCODER, LV_KEY_ENCODER_LONGP,   LV_KEY_DEFAULT},
};


/*
 * @brief       lv_key_t Encoder_Get(void)
 * @details     将编码器值转化LV_KEY
 */
#include "TIM.h"
static lv_key_t Encoder_Get(void)
{
#define ENCODER_OFFSET (2000ul)
    static uint8_t flag = 0;
    if(flag == 0)
    {
        flag = 1;
        HAL_TIM_Base_Start(&htim2);
        htim2.Instance->CNT = ENCODER_OFFSET;
    }
    lv_key_t key = LV_KEY_DEFAULT;
    int32_t count = ENCODER_OFFSET - __HAL_TIM_GET_COUNTER(&htim2);
    __HAL_TIM_SET_COUNTER(&htim2, ENCODER_OFFSET);
    static int32_t diffCount = 0;
    diffCount += count;
    if(diffCount > 5) {
        diffCount = 5;
    }
    if(diffCount < -5) {
        diffCount = -5;
    }
    if(diffCount > 0)
    {
        key = LV_KEY_DOWN;
        --diffCount;
    }
    else
        if(diffCount < 0)
        {
            key = LV_KEY_UP;
            ++diffCount;
        }
       
    return key;
}

#include "Button_Device.h"
/*
 * @brief       lv_key_t Button_toKey(uint8_t buttonNum,uint8_t flag)
 * @details     将实体按键转为LV_KEY事件
 */
lv_key_t Button_toKey(uint8_t buttonNum, uint8_t flag)
{
    static uint8_t waitCount = 0;
    if(buttonNum == 0xff) {
    } else {
        //实体按键
        uint16_t tablesize = sizeof(Btn_KeyTable) / sizeof(Btn_KeyTable[0]);
        for(uint8_t i = 0; i < tablesize; ++i)
        {
            if(buttonNum == Btn_KeyTable[i].buttonNum)
            {
                lv_key_t key = LV_KEY_DEFAULT;
                switch(flag)
                {
                    case KEY_STATE_HOLD:
                        key = Btn_KeyTable[i].key_hold;
                        break;
                    case KEY_STATE_CLICKED:
                        key = Btn_KeyTable[i].key_short;
                        break;
                    case KEY_STATE_LONGGP:
                        key = Btn_KeyTable[i].key_long;
                        break;
                    default:
                        key = LV_KEY_DEFAULT;
                        break;
                }
                //                if((key == LV_KEY_ENCODER) || (key == LV_KEY_ENCODER_LONGP))
                {
                    waitCount = 5;
                }
                return key;
            }
        }
    }
    //编码器转换
    lv_key_t encoderKey = Encoder_Get();
    
    //防止按下编码器 误触发旋转
    if(waitCount == 0) {
        if(encoderKey != LV_KEY_DEFAULT)
        {
            return encoderKey;
        }
    } else {
        waitCount--;
    }
    return LV_KEY_DEFAULT;
}


void GUI_KeySend(lv_obj_t *obj, lv_key_t key)
{
    if((obj != NULL) && (key != 0)) {
        lv_event_send(obj, LV_EVENT_KEY, &key);
    }
}




