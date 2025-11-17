#ifndef _BEEP_DEVICE_H_
#define _BEEP_DEVICE_H_

#include "main.h"

void beep_init(void);

void beep_Set_Enable(uint8_t enable);
void beep_Set(int16_t time0, int16_t time1, int16_t time2);
void beep_Tick(int16_t tickTime);

//#define BEEP_TIPS()     beep_Set(50,0,0)
#define BEEP_OK()       beep_Set(50,0,0)
#define BEEP_ERR()      beep_Set(100,100,100)
#define BEEP_WARRING()  beep_Set(1000,100,100)
#define BEEP_ON()  HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET)
#define BEEP_OFF() HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET)



#define BEEP_BAT_TESTER_ERR()      beep_Set(200,200,200)
#endif
