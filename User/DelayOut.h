#ifndef _DELAYOUT_H_
#define _DELAYOUT_H_

#include "Commd.h"


#define DELAYOUT_FILE_FLASH_PATH "FLASH:DelayOut"
#define DELAYOUT_FILE_USB_PATH   "USB:DelayOut"

enum {
    DELAY_ENDSTATE_OFF = 0,
    DELAY_ENDSTATE_ON,
    DELAY_ENDSTATE_LAST,
    DELAY_ENDSTATE_MIN = DELAY_ENDSTATE_OFF,
    DELAY_ENDSTATE_MAX = DELAY_ENDSTATE_LAST,
};

enum {
    DELAY_STOP_NONE = 0,

    DELAY_STOP_MORE_V,
    DELAY_STOP_LESS_V,

    DELAY_STOP_MORE_C,
    DELAY_STOP_LESS_C,

    DELAY_STOP_MORE_P,
    DELAY_STOP_LESS_P,

    DELAY_STOP_MIN = DELAY_STOP_NONE,
    DELAY_STOP_MAX = DELAY_STOP_LESS_P,
};


//#pragma pack (0)

typedef struct {
    uint8_t stop;
    float vol;
    float amp;
    float wat;
} DelayOut_Stop_Def;


typedef struct {
    uint8_t out;
    float dT;
} DelayPoint_Def;

#define DELAYOUT_MAX_COUNT 512

//运行中
enum {
    DELAY_STATE_NULL = 0,
    DELAY_STATE_STOP,     //OFF,只能重新启动
    DELAY_STATE_RUNNING,  //运行中,按下"ON/OFF",暂停保持/停止关断
    DELAY_STATE_HALT,    //暂停,按下"Delay ONOFF" -> RUNNING
};

typedef struct {
    //当前
    uint8_t tickRun;
    uint8_t enable;
    int current;
    int loop;
    uint8_t state;

    //设定
    int startpoint;
    int countpoint;
    int cycles;
    uint8_t lastState;

    float holdtime;
    //保护
    DelayOut_Stop_Def stopCfg;
    DelayPoint_Def points[DELAYOUT_MAX_COUNT];
    uint8_t md5Value[16];
} DelayOut_InfoDef;

extern DelayOut_InfoDef delayoutInfo;

#pragma pack ()


/*
 * @brief       void DelayOut_Check(DelayPoint_Def* point)
 * @details     DelayOut数据点检查
 */
void DelayOut_Check(DelayPoint_Def *point);

void DelayOut_Tick(void);

uint16_t DelayOut_Load(DelayOut_InfoDef *tempInfo, const char *name);
uint8_t DelayOut_Save(DelayOut_InfoDef *tempInfo, const char *name);

void DelayOut_Delete(const char *name);
uint8_t DelayOut_Rename(const char *oldname, const char *newname);

uint8_t DelayOut_IsRunning(void);
float DelayOut_RemainingTime(void);
float DelayOut_GetStopVal(void);
#endif
