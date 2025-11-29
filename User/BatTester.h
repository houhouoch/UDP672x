#ifndef _BATTERY_TESTER_H_
#define _BATTERY_TESTER_H_

#include "Commd.h"


#define BAT_TESTER_FILE_FLASH_PATH "FLASH:BatTester"
#define BAT_TESTER_FILE_USB_PATH   "USB:BatTester"



//enum {
//    DISABLE = 0,
//    ENABLE,
//};

#pragma pack (4)


enum {
    __STOP_NONE = 0,

    __STOP_MORE_V,
    __STOP_LESS_V,

    __STOP_MORE_C,
    __STOP_LESS_C,

    __STOP_MORE_P,
    __STOP_LESS_P,

    __STOP_MORE_DVM,
    __STOP_LESS_DVM,

    __STOP_MIN = __STOP_NONE,
    __STOP_MAX = __STOP_LESS_DVM,
};


enum {
    _STOP_LOGIC_OR = 0,
    _STOP_LOGIC_AND,

    _STOP_LOGIC_MIN = _STOP_LOGIC_OR,
    _STOP_LOGIC_MAX = _STOP_LOGIC_AND,
};

typedef struct {
    uint8_t logic;
    uint8_t stop;
    float value;
} BatTester_Stop_Def;

typedef struct {
    float vol;  //电压
    float amp;  //电流
    float kT;   //保持,单位:s
    BatTester_Stop_Def stopCfg[2];
} BatTester_Point_Def;

#define BAT_TESTER_MAX_COUNT (64)

//运行中
enum {
    BAT_TESTER_STATE_NULL = 0,
    BAT_TESTER_STATE_STOP,     //OFF,只能重新启动
    BAT_TESTER_STATE_RUNNING,  //运行中,按下"ON/OFF",暂停保持/停止关断
    BAT_TESTER_STATE_PAUSE,    //暂停,按下"BatTester ONOFF" -> RUNNING
    BAT_TESTER_STATE_COMPLETED, //成功
    BAT_TESTER_STATE_FAILED,    //失败
};



typedef struct {
    //当前
    uint8_t tickRun;
    uint8_t enable;
    int current;
    int loop;
    uint8_t state;
    //uint8_t errorFlag;
    //设定
    int startpoint;
    int countpoint;
    int cycles;

    uint8_t editable;
    float holdtime;
    BatTester_Point_Def points[BAT_TESTER_MAX_COUNT];

    BatTester_Stop_Def stopCfg[3];
    float trigTime;
    float trigTime_now;
} BatTester_InfoDef;

extern BatTester_InfoDef BatTester;

#pragma pack ()

/*
 * @brief       void BatTester_Check(BatTester_Point_Def* point)
 * @details     BatTester数据点检查
 */
void BatTester_Check(BatTester_Point_Def *point);


//inline void BatTester_Check(ListPoint_Def *point)
//{
//    if(point == NULL) { return ; }
//    //检查电压
//    point->vol = MIN(VOL_MAX, point->vol);
//    point->vol = MAX(VOL_MIN, point->vol);
//    //检查电流
//    float maxamp = WAT_MAX / (point->vol + 0.0001f);
//    maxamp = MIN(maxamp, AMP_MAX);
//    point->amp = MIN(maxamp, point->amp);
//    point->amp = MAX(AMP_MIN, point->amp);
//    //检查时间
//    point->kT = MIN(KT_MAX, point->kT);
//    point->kT = MAX(KT_MIN, point->kT);
//}



void BatTester_Tick(void);

uint16_t BatTester_Load(BatTester_InfoDef *tempInfo, const char *name);
uint8_t BatTester_Save(BatTester_InfoDef *tempInfo, const char *name);
void BatTester_Delete(const char *name);
uint8_t BatTester_Rename(const char *oldname, const char *newname);

uint8_t BatTester_IsRunning(void);
float BatTester_RemainingTime(void);
#endif
