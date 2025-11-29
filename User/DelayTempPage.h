#ifndef _DELAY_TEMP_PAGE_H_
#define _DELAY_TEMP_PAGE_H_

#include "Commd.h"
#include "DelayOut.h"

enum {
    DELAYTEMP_CODE_O1P,
    DELAYTEMP_CODE_10P,
    DELAYTEMP_CODE_MIN = DELAYTEMP_CODE_O1P,
    DELAYTEMP_CODE_MAX = DELAYTEMP_CODE_10P,
};

//模板类型
enum {
    DELAYTEMP_TYPE_STATE,   //状态生成
    DELAYTEMP_TYPE_FIXT,    //固定时长
    DELAYTEMP_TYPE_INCT,    //递增时长
    DELAYTEMP_TYPE_DECT,    //递减时长

    DELAYTEMP_TYPE_MIN = DELAYTEMP_TYPE_STATE,
    DELAYTEMP_TYPE_MAX = DELAYTEMP_TYPE_DECT,
};

typedef struct {
    int8_t temp_type;  //模板类型
    int32_t startpoint;
    int32_t totalCount;
    uint8_t code;
    struct {
        float time_on;
        float time_off;
    } fix;
    struct {
        float time_base;
        float time_step;
    } inc_dec;
} DelayTempInfo_Def;

extern DelayTempInfo_Def DelayTempInfo;


/*
 * @brief       void Delay_Temp_Set_Type(uint8_t tpye)
 * @details     设置Delay模板类型
 */
void Delay_Temp_Set_Type(uint8_t tpye);

void Delay_Temp_Generate(void);


/*
 * @brief       void DelayTempPage_Enter(void)
 * @details     进入Delay模板页面
 */
void DelayTempPage_Enter(void);

/*
 * @brief       void DelayTempPage_Exit(void)
 * @details     退出Delay模板页面
 */
void DelayTempPage_Exit(void);

void DelayTempPage_GroupCreate(void);

#endif