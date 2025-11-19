#ifndef _SystemSetting_H_
#define _SystemSetting_H_
#include "EEPROM_Device.h"
#include "main.h"
#include "Beep_Device.h"
typedef struct {
    uint8_t beep_state;         // 蜂鸣器状态
    uint8_t backlight_brightness; // 背光亮度（0-100）
    uint8_t storage_group;      // 存储组（0-200）
    uint8_t output_status;      // 输出状态
} SystemSettings;

// 声明外部变量
extern SystemSettings current_settings;  // 声明为外部变量

#endif
