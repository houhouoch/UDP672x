#ifndef _LIST_TEMP_PAGE_H_
#define _LIST_TEMP_PAGE_H_

#include "math.h"
#include "Commd.h"
#include "ListOut.h"

//编辑对象
enum {
    LISTTEMP_EDIT_OBJECT_VOL = 0,
    LISTTEMP_EDIT_OBJECT_AMP,

    LISTTEMP_EDIT_OBJECT_MIN = LISTTEMP_EDIT_OBJECT_VOL,
    LISTTEMP_EDIT_OBJECT_MAX = LISTTEMP_EDIT_OBJECT_AMP,
};

enum {
    TEMP_TYPE_Sin = 0,      //正弦波       反相/角度
    TEMP_TYPE_Pulse,        //脉冲波       占空比
    TEMP_TYPE_Ramp,         //斜波         对称性
    TEMP_TYPE_Stair_Up,     //阶梯上升
    TEMP_TYPE_Stair_Down,   //阶梯下降
    TEMP_TYPE_Stair_UpDown, //阶梯上下
    TEMP_TYPE_expUp,        //指数上升      指数
    TEMP_TYPE_expDown,      //指数下降      指数

    TEMP_TYPE_MIN = TEMP_TYPE_Sin,
    TEMP_TYPE_MAX = TEMP_TYPE_expDown,
};



typedef struct {
    uint8_t edit_obj;   //编辑变量
    int32_t startpoint;    //起始点
    int32_t totalCount;    //总点数
    float interval;         //时间间隔

    struct {
        uint8_t temp_type;      //模板种类
        float minValue;         //最小值
        float maxValue;         //最大值
        //特殊
        uint8_t invert;             //反相标志
        float plusePeriod;          //周期(脉冲类特有)
        float pluseWidth;           //脉宽(脉冲类特有)
        uint8_t Symmetry;           //对称性   [0~100]
        int16_t sinAngleRange[2];   //角度范围        [0.0~720.0]
        int16_t expValue;           //指数值
    } param[2];

    ListPoint_Def tempPoints[LISTOUT_MAX_COUNT];
} ListTempInfo_Def;

extern ListTempInfo_Def ListTempInfo;


void ListTempPage_Generate(void);

/*
 * @brief       void ListPage_Enter(void)
 * @details     进入List模板页面
 */
void ListTempPage_Enter(void);

/*
 * @brief       void ListPage_Exit(void)
 * @details     退出List模板页面
 */
void ListTempPage_Exit(void);

void ListTempPage_GroupCreate(void);

void ListTemp_Edit_Object_handler(lv_obj_t *obj, lv_event_t event);
void ListTemp_Edit_Type_handler(lv_obj_t *obj, lv_event_t event);

void ListTempPage_Cont_handler(lv_obj_t *obj, lv_event_t event);

#endif
