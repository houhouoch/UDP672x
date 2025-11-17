#include "Button_Device.h"
#include "stdio.h"
#include "string.h"

#include "main.h"
static const GPIO_Def Key_H[] = {   
    {KEY_out1_GPIO_Port, KEY_out1_Pin},
    {KEY_out2_GPIO_Port, KEY_out2_Pin},
    {KEY_out3_GPIO_Port, KEY_out3_Pin},
    {KEY_out4_GPIO_Port, KEY_out4_Pin},
};

static const GPIO_Def Key_V[] = {
    {KEY_in1_GPIO_Port, KEY_in1_Pin},
    {KEY_in2_GPIO_Port, KEY_in2_Pin},
    {KEY_in3_GPIO_Port, KEY_in3_Pin},
};


static void delay(void)
{
    uint16_t i;
    for(i = 0; i < 50; i++);
}
/*
 * @brief       uint8_t matrixButton_Scan(void)
 * @details     矩阵键盘扫描
 */
//  KEY_M1 ：0       KEY_V ：1            KEY_LEFT ：2
//  KEY_M2 ：3       KEY_A ：4            KEY_RIGHT ：5
//  KEY_M3 ：6       KEY_MENU ：7         KEY_ESC ：8
//  KEY_LOCK ：9     KEY_OUTPUT ：10      KEY_ENTER ：11
//  KEY_CODER_OK：12
static uint8_t matrixButton_Scan(void)
{
    uint8_t H_count = sizeof(Key_H) / sizeof(Key_H[0]);
    uint8_t V_count = sizeof(Key_V) / sizeof(Key_V[0]);
    uint8_t key = 0xff;
//编码器按钮
    if(HAL_GPIO_ReadPin(CODER_OK_GPIO_Port, CODER_OK_Pin) == 0) {
        return H_count * V_count;
    }
    for(uint8_t h = 0; h < H_count; ++h) {
        gpio_set(Key_H[h], 0);
        delay();
        for(uint8_t v = 0; v < V_count; ++v) {
            gpio_set(Key_V[v], 1);
            if(gpio_get(Key_V[v]) == 0) {
                key = (h * V_count) + v;
            }
        }
        gpio_set(Key_H[h], 1);
        if(key != 0xff) {
            break;
        }
        delay();
    }
    return key;
}



//检测按键被按下
uint8_t matrixButton_CalibModeCheck(uint8_t button)
{
    uint8_t flag = 0;
    uint8_t buttonCnt = 0;
    for(uint8_t i = 0; i < 10; ++i) {
        if(matrixButton_Scan() == button) {
            if(buttonCnt < 3) {
                buttonCnt++;
            } else {
                flag = 1;
                break;
            }
        }
        HAL_Delay(10);
    }
    return flag;
}



#define LONGPPRESS_TIME 1500
#define SHORTPRESS_TIME 50
//长按键自动跳出
#define BUTTON_LONGPRESS_AUTO_RETURN 1

static uint32_t timeDiff(uint16_t t0, uint16_t t1)
{
    uint32_t time = 0;
    if(t0 > t1) {
        time = 65536 + t1 - t0;
    } else {
        time = t1 - t0;
    }
    return time;
}



uint8_t keyScan(uint8_t *pkey)
{
    if(pkey == NULL)
    { return KEY_STATE_RELEASED; }
    //返回值(按键状态)
    uint8_t keystate = KEY_DEFAULT;
    *pkey = 0xff;
    //开始矩阵扫描
    uint8_t keyValue = matrixButton_Scan();
    static uint8_t lastKey = 0xff;
    static uint8_t triggerFlag = 0;
    static uint8_t holdSendFlag = 0;
    //计算时间差
    static uint16_t t0 = 0;
    uint16_t t1 = HAL_GetTick();
    uint32_t count = timeDiff(t0, t1);
    *pkey = 0xff;
    {
        //按键状态发生变化
        if(lastKey != keyValue)
        {
            //按下记录时间
            if(lastKey == 0xff) {
                triggerFlag = 0;
                holdSendFlag = 0;
                //锚定时间
                t0 = HAL_GetTick();
            }
            if((lastKey != 0xff) && (keyValue == 0xff))
            {
                if(triggerFlag == 0)
                {
                    //释放计算时间
                    if((count  < LONGPPRESS_TIME) && (count  > SHORTPRESS_TIME))
                    {
                        //短按
                        triggerFlag = 1;
                        printf("ShortPress %d \r\n", lastKey);
                        *pkey = lastKey;
                        keystate = KEY_STATE_CLICKED;
                    } else
                        if(count > LONGPPRESS_TIME) {
                            //长按
                            triggerFlag = 1;
                            printf("LongPress %d \r\n", lastKey);
                            *pkey = lastKey;
                            keystate = KEY_STATE_LONGGP;
                        }
                }
            }
            lastKey = keyValue;
        } else
            if(keyValue != 0xff)     //按键已被按下
            {
                if(triggerFlag == 0)
                {
                    //已按下,超过长按时间自动跳出
                    #if (BUTTON_LONGPRESS_AUTO_RETURN != 0)
                    if(count >= LONGPPRESS_TIME) {
                        triggerFlag = 1;
                        printf("LongPress H %d\r\n", lastKey);
                        *pkey = lastKey;
                        keystate = KEY_STATE_LONGGP;
                    }
                    #endif
                }
                if(holdSendFlag == 0)
                {
                    if(count > (SHORTPRESS_TIME + 1)) {
                        *pkey = lastKey;
                        keystate = KEY_STATE_HOLD;
                        holdSendFlag = 1;
                    }
                }
            }
    }
    return keystate;
}
