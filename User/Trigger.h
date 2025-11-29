#ifndef _TRIGGER_H_
#define _TRIGGER_H_

#include <stdint.h>
#include <GPIO_Device.h>

#ifndef ARRAY_COUNT
    #define ARRAY_COUNT(x) (sizeof(x)/sizeof(x[0]))
#endif

#define SENS_HIGH_TIME  (5)     //ms
#define SENS_MID_TIME   (10)    //ms
#define SENS_LOW_TIME   (20)    //ms

//触发器通道
enum {
    TRIGGER_CH_D0 = 0,
    TRIGGER_CH_D1,
    TRIGGER_CH_D2,
    TRIGGER_CH_D3,

    //最大最小值
    TRIGGER_CH_MIN = TRIGGER_CH_D0,
    TRIGGER_CH_MAX = TRIGGER_CH_D3,
};

//Dx通道模式 关闭/输出/输入
enum {
    TRIGGER_MODE_OFF = 0,
    TRIGGER_MODE_OUT,
    TRIGGER_MODE_IN,
    //最大最小值
    TRIGGER_MODE_MIN = TRIGGER_MODE_OFF,
    TRIGGER_MODE_MAX = TRIGGER_MODE_IN,
};

#if 1
//受控源
enum {
    IN_SOURCE_NULL = 0,
    IN_SOURCE_CH1,
    //最大最小值
    IN_SOURCE_MIN = IN_SOURCE_CH1,
    IN_SOURCE_MAX = IN_SOURCE_CH1,
};
//触发信号类型
enum {
    IN_TYPE_NULL = 0,
    IN_TYPE_RISE,
    IN_TYPE_FALL,
    IN_TYPE_HIGH,
    IN_TYPE_LOW,
    //最大最小值
    IN_TYPE_MIN = IN_TYPE_RISE,
    IN_TYPE_MAX = IN_TYPE_LOW,
};
//灵敏度
enum {
    IN_SENS_NULL = 0,
    IN_SENS_HIGH,
    IN_SENS_MID,
    IN_SENS_LOW,
    //最大最小值
    IN_SENS_MIN = IN_SENS_HIGH,
    IN_SENS_MAX = IN_SENS_LOW,
};
//响应
enum {
    IN_RESP_NULL = 0,
    IN_RESP_ON,     //打开
    IN_RESP_OFF,    //关闭
    IN_RESP_ALTER,  //翻转

    //新增
    IN_RESP_LIST_ON,
    IN_RESP_LIST_OFF,
    IN_RESP_DELAY_ON,
    IN_RESP_DELAY_OFF,
    //最大最小值
    IN_RESP_MIN = IN_RESP_ON,
    IN_RESP_MAX = IN_RESP_DELAY_OFF,
};
#endif

#if 1
enum {
    OUT_SOURCE_NULL = 0,
    OUT_SOURCE_CH1,
    //最大最小值
    OUT_SOURCE_MIN = OUT_SOURCE_CH1,
    OUT_SOURCE_MAX = OUT_SOURCE_CH1,
};
enum {
    CONDITION_NULL = 0,
    CONDITION_OUT_OFF,
    CONDITION_OUT_ON,

    CONDITION_V_MORE,
    CONDITION_V_LESS,
    CONDITION_V_EQUAL,

    CONDITION_C_MORE,
    CONDITION_C_LESS,
    CONDITION_C_EQUAL,

    CONDITION_P_MORE,
    CONDITION_P_LESS,
    CONDITION_P_EQUAL,
    //最大最小值
    CONDITION_MIN = CONDITION_OUT_OFF,
    CONDITION_MAX = CONDITION_P_EQUAL,
};
enum {
    POLARITY_NEGATIVE = 0,  //负极性
    POLARITY_POSITIVE,      //正极性
    POLARITY_RISE_PLUSE,    //上升沿脉冲
    POLARITY_FALL_PLUSE,    //下降沿脉冲

    POLARITY_MIN = POLARITY_NEGATIVE,
    POLARITY_MAX = POLARITY_POSITIVE,
};
#endif

typedef struct {
    uint8_t mode;       //通道模式

    struct {
        uint8_t inSlave;   //受控源
        uint8_t inType;     //信号类型
        uint8_t inSens;     //灵敏度
        uint8_t inRespon;   //响应

        //不保存
        uint8_t lastVal;
        int16_t trgTime;
    } inConf;

    struct {
        uint8_t outSource;  //输出触发源
        uint8_t condition;  //条件
        struct {
            float vol;
            float amp;
            float wat;
        } value;
        uint8_t outPolarity;    //输出极性
    } outConf;
} Trigger_Def;

#define TRIGGER_IN_ISVALIB(T) (\
                               (T->inConf.inSlave != IN_SOURCE_NULL)  \
                               &&(T->inConf.inType != IN_TYPE_NULL)  \
                               &&(T->inConf.inSens != IN_SENS_NULL)  \
                               &&(T->inConf.inRespon != IN_RESP_NULL) \
                              )

#define TRIGGER_OUT_ISVALIB(T)  (\
                                 ( T->outConf.outSource != OUT_SOURCE_NULL) \
                                 &&( T->outConf.condition != CONDITION_NULL)  \
                                )


#define TRIGGER_COUNT 4
extern Trigger_Def Trigger[TRIGGER_COUNT];


float *Trigger_Get_ConditionValue(uint8_t ch, uint8_t condition);

/*
 * @brief       void Trigger_Init(void)
 * @details     触发器初始化
 */
void Trigger_Init(void);


/*
 * @brief       void Trigger_Tick(uint16_t ms)
 * @details     触发器心跳函数
 */
void Trigger_Tick(uint16_t ms);


#endif