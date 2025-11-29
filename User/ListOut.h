#ifndef _LISTOUT_H_
#define _LISTOUT_H_

#include "Commd.h"


#define LISTOUT_FILE_FLASH_PATH "FLASH:ListOut"
#define LISTOUT_FILE_USB_PATH   "USB:ListOut"


enum {
    LIST_ENDSTATE_OFF = 0,
    LIST_ENDSTATE_LAST,
    LIST_ENDSTATE_MIN = LIST_ENDSTATE_OFF,
    LIST_LASTSTATE_MAX = LIST_ENDSTATE_LAST,
};

//enum {
//    DISABLE = 0,
//    ENABLE,
//};

#pragma pack (4)

typedef struct {
    float vol;  //电压
    float amp;  //电流
    float kT;   //保持,单位:s
} ListPoint_Def;

#define LISTOUT_MAX_COUNT (512)

//运行中
enum {
    LIST_STATE_NULL = 0,
    LIST_STATE_STOP,     //OFF,只能重新启动
    LIST_STATE_RUNNING,  //运行中,按下"ON/OFF",暂停保持/停止关断
    LIST_STATE_PAUSE,    //暂停,按下"List ONOFF" -> RUNNING
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
    ListPoint_Def points[LISTOUT_MAX_COUNT];
} ListOut_InfoDef;

extern ListOut_InfoDef listoutInfo;

#pragma pack ()

/*
 * @brief       void ListOut_Check(ListPoint_Def* point)
 * @details     ListOut数据点检查
 */
void ListOut_Check(ListPoint_Def *point);


//inline void ListOut_Check(ListPoint_Def *point)
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



void ListOut_Tick(void);

uint16_t ListOut_Load(ListOut_InfoDef *tempInfo, const char *name);
uint8_t ListOut_Save(ListOut_InfoDef *tempInfo, const char *name);
void ListOut_Delete(const char *name);
uint8_t ListOut_Rename(const char *oldname, const char *newname);

uint8_t ListOut_IsRunning(void);
float ListOut_RemainingTime(void);
#endif
