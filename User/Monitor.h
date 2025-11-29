#ifndef _MONITOR_H_
#define _MONITOR_H_

#include "Commd.h"

enum {
    MONITOR_NONE = 0,
    MONITOR_LESS,
    MONITOR_MORE,
    //最大最小值
    MONITOR_MIN = MONITOR_NONE,
    MONITOR_MAX = MONITOR_MORE,
};

enum {
    SENSITIVITY_LOW = 0,
    SENSITIVITY_MID,
    SENSITIVITY_HIGH,

    SENSITIVITY_MIN = SENSITIVITY_LOW,
    SENSITIVITY_MAX = SENSITIVITY_HIGH,
};

enum {
    LOGIC_AND = 0,
    LOGIC_OR,

    LOGIC_MIN = LOGIC_AND,
    LOGIC_MAX = LOGIC_OR,
};

#pragma pack (1)

typedef struct {
    float vol;
    float amp;
    float wat;
    float dvm;
    uint8_t vol_monitor;
    uint8_t amp_monitor;
    uint8_t wat_monitor;
    uint8_t dvm_monitor;

    uint8_t enable;
    uint8_t logic[3];
    //触发灵敏度
    uint16_t sensitivity;
    //触发动作
    uint8_t powerOFF;
    //提示音
    uint8_t beep;
    //提示框
    uint8_t tips;
    uint8_t md5Value[16];
} Monitor_Def;

#pragma pack ()

void Monitor_Tick(uint8_t ms);

uint8_t Monitor_IsRunning(void);

#endif