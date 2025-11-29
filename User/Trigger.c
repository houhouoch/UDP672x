#include "Trigger.h"
#include "InterFace.h"
#include "List_InterFace.h"
#include "Delay_InterFace.h"

Trigger_Def Trigger[TRIGGER_COUNT] = {
    {TRIGGER_MODE_IN},
    {TRIGGER_MODE_IN},
    {TRIGGER_MODE_IN},
    {TRIGGER_MODE_IN},
};




static const GPIO_Def Trigger_D0 = {
    .port = IO_PD12_D0_GPIO_Port,
    .pin = IO_PD12_D0_Pin,
};
static const GPIO_Def Trigger_D1 = {
    .port = IO_PD13_D1_GPIO_Port,
    .pin = IO_PD13_D1_Pin,
};
static const GPIO_Def Trigger_D2 = {
    .port = IO_PE3_D2_GPIO_Port,
    .pin = IO_PE3_D2_Pin,
};
static const GPIO_Def Trigger_D3 = {
    .port = IO_PE4_D3_GPIO_Port,
    .pin = IO_PE4_D3_Pin,
};

/*
 * @brief       static void _Set_Out(uint8_t i)
 * @details     设置为输出模式
 */
static void _Set_Out(uint8_t i)
{
    if(i >= TRIGGER_COUNT) {
        return ;
    }
    static const GPIO_Def *gpio = NULL;
    switch(i) {
        case TRIGGER_CH_D0:
            gpio = &Trigger_D0;
            break;
        case TRIGGER_CH_D1:
            gpio = &Trigger_D1;
            break;
        case TRIGGER_CH_D2:
            gpio = &Trigger_D2;
            break;
        case TRIGGER_CH_D3:
            gpio = &Trigger_D3;
            break;
    }
    GPIO_InitTypeDef gpio_initType = {0};
    gpio_initType.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_initType.Pull = GPIO_NOPULL;
    gpio_initType.Pin = gpio->pin;
    HAL_GPIO_Init(gpio->port, &gpio_initType);
}

/*
 * @brief       static void _Set_In(uint8_t i,uint16_t ms)
 * @details     设置为输入模式
 */
static void _Set_In(uint8_t i, uint16_t ms)
{
    if(i >= TRIGGER_COUNT) {
        return ;
    }
    static GPIO_Def *gpio = NULL;
    switch(i) {
        case TRIGGER_CH_D0:
            gpio = &Trigger_D0;
            break;
        case TRIGGER_CH_D1:
            gpio = &Trigger_D1;
            break;
        case TRIGGER_CH_D2:
            gpio = &Trigger_D2;
            break;
        case TRIGGER_CH_D3:
            gpio = &Trigger_D3;
            break;
    }
    GPIO_InitTypeDef gpio_initType = {0};
    gpio_initType.Mode = GPIO_MODE_INPUT;
    gpio_initType.Pull = GPIO_NOPULL;
    gpio_initType.Pin = gpio->pin;
    HAL_GPIO_Init(gpio->port, &gpio_initType);
}

/*
 * @brief       static void _Out_Set(uint8_t i, uint8_t polarity)
 * @details     设置输出电平
 */
static void _Out_Set(uint8_t i, uint8_t polarity)
{
    if(i >= TRIGGER_COUNT) {
        return ;
    }
    switch(i) {
        case TRIGGER_CH_D0:
            gpio_set(Trigger_D0, (polarity == POLARITY_POSITIVE));
            break;
        case TRIGGER_CH_D1:
            gpio_set(Trigger_D1, (polarity == POLARITY_POSITIVE));
            break;
        case TRIGGER_CH_D2:
            gpio_set(Trigger_D2, (polarity == POLARITY_POSITIVE));
            break;
        case TRIGGER_CH_D3:
            gpio_set(Trigger_D3, (polarity == POLARITY_POSITIVE));
            break;
    }
}

/*
 * @brief       static uint8_t _In_Read(uint8_t i)
 * @details     读取输入电平
 */
static uint8_t _In_Read(uint8_t i)
{
    if(i >= TRIGGER_COUNT) {
        return 0;
    }
    switch(i) {
        case TRIGGER_CH_D0:
            return gpio_get(Trigger_D0);
        case TRIGGER_CH_D1:
            return gpio_get(Trigger_D1);
        case TRIGGER_CH_D2:
            return gpio_get(Trigger_D2);
        case TRIGGER_CH_D3:
            return gpio_get(Trigger_D3);
    }
    return 0;
}

float *Trigger_Get_ConditionValue(uint8_t ch, uint8_t condition)
{
    if(ch >= TRIGGER_COUNT) {
        return NULL;
    }
    switch(condition)
    {
        case CONDITION_OUT_OFF:
            break;
        case CONDITION_OUT_ON:
            break;
        case CONDITION_V_MORE:
        case CONDITION_V_LESS:
        case CONDITION_V_EQUAL: {
            return &Trigger[ch].outConf.value.vol;
        }
        case CONDITION_C_LESS:
        case CONDITION_C_MORE:
        case CONDITION_C_EQUAL: {
            return &Trigger[ch].outConf.value.amp;
        }
        case CONDITION_P_LESS:
        case CONDITION_P_MORE:
        case CONDITION_P_EQUAL: {
            return &Trigger[ch].outConf.value.wat;
        }
    }
    return NULL;
}


static void Trigger_Out_Tick(uint8_t i)
{
    if(i >= TRIGGER_COUNT) {
        return ;
    }
    Trigger_Def *t = &Trigger[i];
    if(t == NULL) {
        return;
    }
    if(TRIGGER_OUT_ISVALIB(t) == 0) {
        return ;
    }
    //输入源
    float cur_onoff = 0;
    float cur_vol = 0;
    float cur_amp = 0;
    float cur_wat = 0;
    switch(t->outConf.outSource) {
        case OUT_SOURCE_CH1: {
            cur_onoff = IF_Power_Get_On_Off();
            cur_vol = IF_Power_Read_Vol();
            cur_amp = IF_Power_Read_Amp();
            cur_wat = IF_Power_Read_Wat();
        }
        break;
        default:
            return;
    }
    //结果
    uint8_t outPolarity = 0;
    float Polarity = t->outConf.outPolarity;
    //触发条件
    switch(t->outConf.condition) {
        case CONDITION_OUT_OFF:
            outPolarity = (cur_onoff == 0) ? Polarity : !Polarity;
            break;
        case CONDITION_OUT_ON:
            outPolarity = (cur_onoff != 0) ? Polarity : !Polarity;
            break;
        case CONDITION_V_MORE:
            outPolarity = (cur_vol > t->outConf.value.vol) ? Polarity : !Polarity;
            break;
        case CONDITION_V_LESS:
            outPolarity = (cur_vol < t->outConf.value.vol) ? Polarity : !Polarity;
            break;
        case CONDITION_V_EQUAL:
            outPolarity = (cur_vol == t->outConf.value.vol) ? Polarity : !Polarity;
            break;
        case CONDITION_C_LESS:
            outPolarity = (cur_amp > t->outConf.value.amp) ? Polarity : !Polarity;
            break;
        case CONDITION_C_MORE:
            outPolarity = (cur_amp < t->outConf.value.amp) ? Polarity : !Polarity;
            break;
        case CONDITION_C_EQUAL:
            outPolarity = (cur_amp == t->outConf.value.amp) ? Polarity : !Polarity;
            break;
        case CONDITION_P_LESS:
            outPolarity = (cur_wat > t->outConf.value.wat) ? Polarity : !Polarity;
            break;
        case CONDITION_P_MORE:
            outPolarity = (cur_wat < t->outConf.value.wat) ? Polarity : !Polarity;
            break;
        case CONDITION_P_EQUAL:
            outPolarity = (cur_wat == t->outConf.value.wat) ? Polarity : !Polarity;
            break;
    }
    //设置输出
    _Out_Set(i, outPolarity);
}

static void _TrgTime_Reload(uint8_t i)
{
    if(i >= TRIGGER_COUNT) {
        return ;
    }
    Trigger_Def *t = &Trigger[i];
    switch(t->inConf.inSens) {
        case IN_SENS_HIGH:
            t->inConf.trgTime = SENS_HIGH_TIME;
            break;
        case IN_SENS_MID:
            t->inConf.trgTime = SENS_MID_TIME;
            break;
        case IN_SENS_LOW:
            t->inConf.trgTime = SENS_LOW_TIME;
            break;
    }
}


/*
 * @brief       static void _Trg_In_Action(uint8_t i)
 * @details     触发器输入动作执行
 */
static void _Trg_In_Action(uint8_t i)
{
    if(i >= TRIGGER_COUNT) {
        return ;
    }
    Trigger_Def *t = &Trigger[i];
    switch(t->inConf.inSlave) {
        case IN_SOURCE_CH1: {
            switch(t->inConf.inRespon)
            {
                case IN_RESP_ON:
                    IF_Power_Set_On_Off(1);
                    break;     //打开输出
                case IN_RESP_OFF:
                    IF_Power_Set_On_Off(0);
                    break;    //关闭输出
                case IN_RESP_ALTER: {   //翻转输出
                    uint8_t lastonoff = IF_Power_Get_On_Off();
                    IF_Power_Set_On_Off(!lastonoff);
                }
                break;
                //
                case IN_RESP_LIST_ON:
                    IF_ListOut_Set_State(LIST_STATE_RUNNING);
                    break;
                case IN_RESP_LIST_OFF:
                    IF_ListOut_Set_State(LIST_STATE_STOP);
                    break;
                case IN_RESP_DELAY_ON:
                    IF_DelayOut_Set_State(DELAY_STATE_RUNNING);
                    break;
                case IN_RESP_DELAY_OFF:
                    IF_DelayOut_Set_State(DELAY_STATE_STOP);
                    break;
            }
        }
        break;
    }
}

/*
 * @brief       static void _Trg_In_Val_Process(uint8_t i,uint8_t curV,uint8_t lastV)
 * @details     触发器输入处理,并执行动作
 */
static void _Trg_In_Val_Process(uint8_t i, uint8_t curV, uint8_t lastV)
{
    if(i >= TRIGGER_COUNT) {
        return ;
    }
    Trigger_Def *t = &Trigger[i];
    switch(t->inConf.inType) {
        case IN_TYPE_RISE: {
            if((curV == 1) && (lastV == 0)) {
                _Trg_In_Action(i);
            }
        }
        break;
        case IN_TYPE_FALL: {
            if((curV == 0) && (lastV == 1)) {
                _Trg_In_Action(i);
            }
        }
        break;
        case IN_TYPE_HIGH: {
            if(curV == 1) {
                _Trg_In_Action(i);
            }
        }
        break;
        case IN_TYPE_LOW: {
            if(curV == 0) {
                _Trg_In_Action(i);
            }
        }
        break;
    }
}

static void Trigger_In_Tick(uint8_t i, uint16_t ms)
{
    if(i >= TRIGGER_COUNT) {
        return ;
    }
    Trigger_Def *t = &Trigger[i];
    if(t == NULL) {
        return;
    }
    uint8_t curVal = _In_Read(i);
    t->inConf.trgTime -= ms;
    if(t->inConf.trgTime < 0) {
        //极性发生变化
        if(curVal != t->inConf.lastVal) {
            _Trg_In_Val_Process(i, curVal, t->inConf.lastVal); //判断触发沿并动作
            curVal = t->inConf.lastVal;
        }
        //无变化
        else {
            _Trg_In_Val_Process(i, curVal, t->inConf.lastVal);
        }
        _TrgTime_Reload(i);
    }
}


/*
 * @brief       void Trigger_Init(void)
 * @details     触发器初始化
 */
void Trigger_Init(void)
{
    for(uint8_t i = 0; i < ARRAY_COUNT(Trigger); ++i) {
        memset(&Trigger[i], 0, sizeof(Trigger[i]));
        Trigger[i].inConf.lastVal = 0xff;
        Trigger[i].inConf.trgTime = 0xffff;
    }
}

/*
 * @brief       void Trigger_Tick(uint16_t ms)
 * @details     触发器心跳函数
 */
void Trigger_Tick(uint16_t ms)
{
    for(uint8_t i = 0; i < ARRAY_COUNT(Trigger); ++i) {
        switch(Trigger[i].mode) {
            case TRIGGER_MODE_OUT:
                Trigger_Out_Tick(i);
                break;
            case TRIGGER_MODE_IN:
                Trigger_In_Tick(i, ms);
                break;
            case TRIGGER_MODE_OFF:
                break;
        }
    }
}

