#ifndef _BUTTON_DEVICE_H_
#define _BUTTON_DEVICE_H_

#include "main.h"

#include "GPIO_Device.h"
//***********************//
//  KEY_M1 ：0       KEY_V ：1            KEY_LEFT ：2
//  KEY_M2 ：3       KEY_A ：4            KEY_RIGHT ：5
//  KEY_M3 ：6       KEY_MENU ：7         KEY_ESC ：8
//  KEY_LOCK ：9     KEY_OUTPUT ：10      KEY_ENTER ：11
//  KEY_CODER_OK：12
enum {
    KEY_M1 = 0,
    KEY_M2 = 3,
    KEY_M3 = 6,
    KEY_LOCK = 9, 
  
    KEY_V = 1,
    KEY_A = 4,
    KEY_MENU = 7, 
    KEY_OUTPUT = 10,
  
    KEY_LEFT = 2,
    KEY_RIGHT = 5,
    KEY_ESC = 8,
    KEY_ENTER = 11,

    KEY_CODER_OK =12,    
    KEY_ENCODER = 13, 

};

enum {
    KEY_DEFAULT = 0,
    KEY_STATE_RELEASED,                 //按键释放
    KEY_STATE_HOLD,                     //按键保持
    KEY_STATE_CLICKED,                  //按键点击
    KEY_STATE_LONGGP,                   //按键长按
};


//检测按键被按下
uint8_t matrixButton_CalibModeCheck(uint8_t button);



uint8_t keyScan(uint8_t *returnKey);

#endif
