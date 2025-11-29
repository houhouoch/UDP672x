#include "Trigger_SCPI.h"

#include "main.h"
#include "Commd.h"

#include "Trigger_Interface.h"

//通道
static const scpi_choice_def_t scpi_trigger_ch[] = {
    {"D0", TRIGGER_CH_D0},
    {"D1", TRIGGER_CH_D1},
    {"D2", TRIGGER_CH_D2},
    {"D3", TRIGGER_CH_D3},
    SCPI_CHOICE_LIST_END /* termination of option list */
};
//状态
static const scpi_choice_def_t scpi_trigger_onoff[] = {
    {"ON", 1},
    {"OFF", 0},
    SCPI_CHOICE_LIST_END /* termination of option list */
};

/* -------------------- 输入模式配置 -------------------- */
scpi_result_t Cmd_Set_Trigger_In_Enable(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //
    int32_t ch = {0};       //通道
    if(!SCPI_ParamChoice(context, scpi_trigger_ch, &ch, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(!(TRIGGER_CH_MIN <= ch) || !(ch <= TRIGGER_CH_MAX))
    {
        return SCPI_RES_OK;
    }
    int32_t state = {0};    //状态
    if(!SCPI_ParamChoice(context, scpi_trigger_onoff, &state, FALSE)) {
        SCPI_ERR_RETURN;
    }
    IF_Trigger_Set_Mode(ch, (state != 0) ? TRIGGER_MODE_IN : TRIGGER_MODE_OFF);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_Trigger_In_Enable(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //
    int32_t ch = {0};       //通道
    if(!SCPI_ParamChoice(context, scpi_trigger_ch, &ch, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(!(TRIGGER_CH_MIN <= ch) || !(ch <= TRIGGER_CH_MAX))
    {
        return SCPI_RES_OK;
    }
    const char *state = ""; //状态
    uint8_t curState = Trigger[ch].mode == TRIGGER_MODE_IN;
    if(!SCPI_ChoiceToName(scpi_trigger_onoff, curState, &state) != 0) {
        SCPI_ERR_RETURN;
    }
    SCPI_ResultCharacters(context, state, strlen(state));
    return SCPI_RES_OK;
}


//受控源
static const scpi_choice_def_t scpi_trigger_inSlave[] = {
    {"CH1", IN_SOURCE_CH1},
    SCPI_CHOICE_LIST_END /* termination of option list */
};
scpi_result_t Cmd_Set_Trigger_In_Source(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //
    int32_t ch = {0};       //通道
    if(!SCPI_ParamChoice(context, scpi_trigger_ch, &ch, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(!(TRIGGER_CH_MIN <= ch) || !(ch <= TRIGGER_CH_MAX))
    {
        return SCPI_RES_OK;
    }
    int32_t inSlave = {0};
    if(!SCPI_ParamChoice(context, scpi_trigger_inSlave, &inSlave, FALSE)) {
        SCPI_ERR_RETURN;
    }
    IF_Trigger_Set_In_Source(ch, inSlave);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_Trigger_In_Source(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //
    int32_t ch = {0};       //通道
    if(!SCPI_ParamChoice(context, scpi_trigger_ch, &ch, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(!(TRIGGER_CH_MIN <= ch) || !(ch <= TRIGGER_CH_MAX))
    {
        return SCPI_RES_OK;
    }
    const char *insource_str = ""; //状态
    uint8_t inSlave = Trigger[ch].inConf.inSlave;
    if(!SCPI_ChoiceToName(scpi_trigger_inSlave, inSlave, &insource_str) != 0) {
        SCPI_ERR_RETURN;
    }
    SCPI_ResultCharacters(context, insource_str, strlen(insource_str));
    return SCPI_RES_OK;
}


//输入信号类型
static const scpi_choice_def_t scpi_trigger_inType[] = {
    {"RISE", IN_TYPE_RISE},
    {"FALL", IN_TYPE_FALL},
    {"HIGH", IN_TYPE_HIGH},
    {"LOW", IN_TYPE_LOW},
    SCPI_CHOICE_LIST_END /* termination of option list */
};
scpi_result_t Cmd_Set_Trigger_In_Type(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //
    int32_t ch = {0};       //通道
    if(!SCPI_ParamChoice(context, scpi_trigger_ch, &ch, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(!(TRIGGER_CH_MIN <= ch) || !(ch <= TRIGGER_CH_MAX))
    {
        return SCPI_RES_OK;
    }
    int32_t type = 0;
    if(!SCPI_ParamChoice(context, scpi_trigger_inType, &type, FALSE)) {
        SCPI_ERR_RETURN;
    }
    IF_Trigger_Set_In_Type(ch, type);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_Trigger_In_Type(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //
    int32_t ch = {0};       //通道
    if(!SCPI_ParamChoice(context, scpi_trigger_ch, &ch, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(!(TRIGGER_CH_MIN <= ch) || !(ch <= TRIGGER_CH_MAX))
    {
        return SCPI_RES_OK;
    }
    const char *intype_str = ""; //状态
    uint8_t inType = Trigger[ch].inConf.inType;
    if(!SCPI_ChoiceToName(scpi_trigger_inType, inType, &intype_str) != 0) {
        SCPI_ERR_RETURN;
    }
    SCPI_ResultCharacters(context, intype_str, strlen(intype_str));
    return SCPI_RES_OK;
}


//灵敏度
static const scpi_choice_def_t scpi_trigger_inSense[] = {
    {"HIGH", IN_SENS_HIGH},
    {"MID", IN_SENS_MID},
    {"LOW", IN_SENS_LOW},
    SCPI_CHOICE_LIST_END /* termination of option list */
};
scpi_result_t Cmd_Set_Trigger_In_Sensitivity(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //
    int32_t ch = {0};       //通道
    if(!SCPI_ParamChoice(context, scpi_trigger_ch, &ch, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(!(TRIGGER_CH_MIN <= ch) || !(ch <= TRIGGER_CH_MAX))
    {
        return SCPI_RES_OK;
    }
    int32_t inSens = 0;
    if(!SCPI_ParamChoice(context, scpi_trigger_inSense, &inSens, FALSE)) {
        SCPI_ERR_RETURN;
    }
    IF_Trigger_Set_In_Sens(ch, inSens);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_Trigger_In_Sensitivity(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //
    int32_t ch = {0};       //通道
    if(!SCPI_ParamChoice(context, scpi_trigger_ch, &ch, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(!(TRIGGER_CH_MIN <= ch) || !(ch <= TRIGGER_CH_MAX))
    {
        return SCPI_RES_OK;
    }
    const char *insense_str = ""; //状态
    uint8_t inSens = Trigger[ch].inConf.inSens;
    if(!SCPI_ChoiceToName(scpi_trigger_inSense, inSens, &insense_str) != 0) {
        SCPI_ERR_RETURN;
    }
    SCPI_ResultCharacters(context, insense_str, strlen(insense_str));
    return SCPI_RES_OK;
}


//响应
static const scpi_choice_def_t scpi_trigger_inRespron[] = {
    {"ON", IN_RESP_ON},
    {"OFF", IN_RESP_OFF},
    {"ALTER", IN_RESP_ALTER},
    SCPI_CHOICE_LIST_END /* termination of option list */
};
scpi_result_t Cmd_Set_Trigger_In_Response(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //
    int32_t ch = {0};       //通道
    if(!SCPI_ParamChoice(context, scpi_trigger_ch, &ch, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(!(TRIGGER_CH_MIN <= ch) || !(ch <= TRIGGER_CH_MAX))
    {
        return SCPI_RES_OK;
    }
    int32_t inRespron = 0;
    if(!SCPI_ParamChoice(context, scpi_trigger_inRespron, &inRespron, FALSE)) {
        SCPI_ERR_RETURN;
    }
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_Trigger_In_Response(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //
    int32_t ch = {0};       //通道
    if(!SCPI_ParamChoice(context, scpi_trigger_ch, &ch, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(!(TRIGGER_CH_MIN <= ch) || !(ch <= TRIGGER_CH_MAX))
    {
        return SCPI_RES_OK;
    }
    const char *inRespon_str = ""; //状态
    uint8_t inRespon = Trigger[ch].inConf.inRespon;
    if(!SCPI_ChoiceToName(scpi_trigger_inRespron, inRespon, &inRespon_str) != 0) {
        SCPI_ERR_RETURN;
    }
    SCPI_ResultCharacters(context, inRespon_str, strlen(inRespon_str));
    return SCPI_RES_OK;
}












/* -------------------- 输出模式配置 -------------------- */
scpi_result_t Cmd_Set_Trigger_Out_Enable(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //
    int32_t ch = {0};       //通道
    if(!SCPI_ParamChoice(context, scpi_trigger_ch, &ch, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(!(TRIGGER_CH_MIN <= ch) || !(ch <= TRIGGER_CH_MAX))
    {
        return SCPI_RES_OK;
    }
    int32_t state = {0};    //状态
    if(!SCPI_ParamChoice(context, scpi_trigger_onoff, &state, FALSE)) {
        SCPI_ERR_RETURN;
    }
    IF_Trigger_Set_Mode(ch, (state != 0) ? TRIGGER_MODE_OUT : TRIGGER_MODE_OFF);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_Trigger_Out_Enable(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //
    int32_t ch = {0};       //通道
    if(!SCPI_ParamChoice(context, scpi_trigger_ch, &ch, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(!(TRIGGER_CH_MIN <= ch) || !(ch <= TRIGGER_CH_MAX))
    {
        return SCPI_RES_OK;
    }
    const char *state = ""; //状态
    uint8_t curState = Trigger[ch].mode == TRIGGER_MODE_OUT;
    if(!SCPI_ChoiceToName(scpi_trigger_onoff, curState, &state) != 0) {
        SCPI_ERR_RETURN;
    }
    SCPI_ResultCharacters(context, state, strlen(state));
    return SCPI_RES_OK;
}


//触发源
static const scpi_choice_def_t scpi_trigger_outSource[] = {
    {"CH1", OUT_SOURCE_CH1},
    SCPI_CHOICE_LIST_END /* termination of option list */
};
scpi_result_t Cmd_Set_Trigger_Out_Source(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //
    int32_t ch = {0};       //通道
    if(!SCPI_ParamChoice(context, scpi_trigger_ch, &ch, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(!(TRIGGER_CH_MIN <= ch) || !(ch <= TRIGGER_CH_MAX))
    {
        return SCPI_RES_OK;
    }
    int32_t outSource = {0};
    if(!SCPI_ParamChoice(context, scpi_trigger_outSource, &outSource, FALSE)) {
        SCPI_ERR_RETURN;
    }
    IF_Trigger_Set_Out_Source(ch, outSource);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_Trigger_Out_Source(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //
    int32_t ch = {0};       //通道
    if(!SCPI_ParamChoice(context, scpi_trigger_ch, &ch, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(!(TRIGGER_CH_MIN <= ch) || !(ch <= TRIGGER_CH_MAX))
    {
        return SCPI_RES_OK;
    }
    const char *outSource_str = ""; //状态
    uint8_t outSource = Trigger[ch].outConf.outSource;
    if(!SCPI_ChoiceToName(scpi_trigger_outSource, outSource, &outSource_str) != 0) {
        SCPI_ERR_RETURN;
    }
    SCPI_ResultCharacters(context, outSource_str, strlen(outSource_str));
    return SCPI_RES_OK;
}


//触发条件
static const scpi_choice_def_t scpi_trigger_outCondition[] = {
    {">V", CONDITION_V_MORE},
    {"<V", CONDITION_V_LESS},
    {"=V", CONDITION_V_EQUAL},

    {">C", CONDITION_C_MORE},
    {"<C", CONDITION_C_LESS},
    {"=C", CONDITION_C_EQUAL},

    {">P", CONDITION_P_MORE},
    {"<P", CONDITION_P_LESS},
    {"=P", CONDITION_P_EQUAL},

    {"OUTON", CONDITION_OUT_ON},
    {"OUTOFF", CONDITION_OUT_OFF},
    SCPI_CHOICE_LIST_END /* termination of option list */
};
scpi_result_t Cmd_Set_Trigger_Out_Condition(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //
    int32_t ch = {0};       //通道
    if(!SCPI_ParamChoice(context, scpi_trigger_ch, &ch, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(!(TRIGGER_CH_MIN <= ch) || !(ch <= TRIGGER_CH_MAX))
    {
        return SCPI_RES_OK;
    }
    int32_t outCondition = {0}; //条件
    if(!SCPI_ParamChoice(context, scpi_trigger_outCondition, &outCondition, FALSE)) {
        SCPI_ERR_RETURN;
    }
    IF_Trigger_Set_Out_Condition(ch, outCondition);
    float outConditionVal = 0;  //数值
    if(!SCPI_ParamFloat(context, &outConditionVal, FALSE)) {
        IF_Trigger_Set_Out_Condition_Val(ch, outConditionVal);
    }
    return SCPI_RES_OK;
}

scpi_result_t Cmd_Read_Trigger_Out_Condition(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //
    int32_t ch = {0};       //通道
    if(!SCPI_ParamChoice(context, scpi_trigger_ch, &ch, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(!(TRIGGER_CH_MIN <= ch) || !(ch <= TRIGGER_CH_MAX))
    {
        return SCPI_RES_OK;
    }
    const char *outCondition_str = ""; //状态
    uint8_t condition = Trigger[ch].outConf.condition;
    if(!SCPI_ChoiceToName(scpi_trigger_outSource, condition, &outCondition_str) != 0) {
        SCPI_ERR_RETURN;
    }
    SCPI_ResultCharacters(context, outCondition_str, strlen(outCondition_str));
    switch(condition)
    {
        case CONDITION_OUT_OFF:
            break;
        case CONDITION_OUT_ON:
            break;
        case CONDITION_V_MORE:
        case CONDITION_V_LESS:
        case CONDITION_V_EQUAL: {
            SCPI_ResultFloat(context, Trigger[ch].outConf.value.vol);
        }
        break;
        case CONDITION_C_LESS:
        case CONDITION_C_MORE:
        case CONDITION_C_EQUAL: {
            SCPI_ResultFloat(context, Trigger[ch].outConf.value.amp);
        }
        break;
        case CONDITION_P_LESS:
        case CONDITION_P_MORE:
        case CONDITION_P_EQUAL: {
            SCPI_ResultFloat(context, Trigger[ch].outConf.value.wat);
        }
        break;
    }
    return SCPI_RES_OK;
}


//输出极性
static const scpi_choice_def_t scpi_trigger_outPolarity[] = {
    {"NEGAtive", POLARITY_NEGATIVE},
    {"POSItive", POLARITY_POSITIVE},
    SCPI_CHOICE_LIST_END /* termination of option list */
};
scpi_result_t Cmd_Set_Trigger_Out_Polarity(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //
    int32_t ch = {0};       //通道
    if(!SCPI_ParamChoice(context, scpi_trigger_ch, &ch, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(!(TRIGGER_CH_MIN <= ch) || !(ch <= TRIGGER_CH_MAX))
    {
        return SCPI_RES_OK;
    }
    int32_t outPolarity = {0};
    if(!SCPI_ParamChoice(context, scpi_trigger_outPolarity, &outPolarity, FALSE)) {
        SCPI_ERR_RETURN;
    }
    IF_Trigger_Set_Out_Polarity(ch, outPolarity);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_Trigger_Out_Polarity(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //
    int32_t ch = {0};       //通道
    if(!SCPI_ParamChoice(context, scpi_trigger_ch, &ch, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(!(TRIGGER_CH_MIN <= ch) || !(ch <= TRIGGER_CH_MAX))
    {
        return SCPI_RES_OK;
    }
    const char *outPolarity_str = ""; //状态
    uint8_t outPolarity = Trigger[ch].outConf.outPolarity;
    if(!SCPI_ChoiceToName(scpi_trigger_outSource, outPolarity, &outPolarity_str) != 0) {
        SCPI_ERR_RETURN;
    }
    SCPI_ResultCharacters(context, outPolarity_str, strlen(outPolarity_str));
    return SCPI_RES_OK;
}

