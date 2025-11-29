#include "Monitor_SCPI.h"

#include "main.h"
#include "Commd.h"

#include "Monitor.h"
#include "Interface.h"
#include "Monitor_Interface.h"


/*
 * @brief       监测器开关
 * @details
 */
scpi_result_t Cmd_Set_Monitor_State(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    scpi_bool_t param1 = {0};
    if(!SCPI_ParamBool(context, &param1, FALSE)) {
        SCPI_ERR_RETURN;
    }
    IF_Display_Go_to_Page(PAGE_MONITOR);
    IF_Monitor_Set_ON_OFF(param1);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_Monitor_State(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //返回:状态,当前开关
    const char *state_str = "";
    state_str = (IF_Monitor_Get_ON_OFF()) ? "ON" : "OFF";
    char buffer[128] = {0};
    uint16_t length = 0;
    length = sprintf(buffer, "%s", state_str);
    SCPI_ResultCharacters(context, buffer, length);
    return SCPI_RES_OK;
}

/*
 * @brief       监测器电压判定
 * @details
 */
static const scpi_choice_def_t scpi_monitor_Vol_def[] = {
    {"NONE", MONITOR_NONE},     //关闭
    {"<V", MONITOR_LESS},       //电压大于
    {">V", MONITOR_MORE},       //电压小于
    SCPI_CHOICE_LIST_END /* termination of option list */
};
scpi_result_t Cmd_Set_Monitor_Vol(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //判定条件
    int32_t monitor = {0};
    if(!SCPI_ParamChoice(context, scpi_monitor_Vol_def, &monitor, FALSE)) {
        SCPI_ERR_RETURN;
    }
    //数值
    scpi_number_t value = {0};
    if(SCPI_ParamNumber(context, scpi_special_numbers_def, &value, FALSE)) {
        if(value.special != FALSE) {
            switch(value.content.tag) {
                case SCPI_NUM_MIN:
                    value.content.value = VOL_MIN;
                    break;
                case SCPI_NUM_MAX:
                    value.content.value = VOL_MAX;
                    break;
            }
        }
    }
    IF_Display_Go_to_Page(PAGE_MONITOR);
    IF_Monitor_Set_Vol(monitor, value.content.value);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_Monitor_Vol(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //
    const char *monitor_str = "";
    if(!SCPI_ChoiceToName(scpi_monitor_Vol_def, systemInfo.monitor.vol_monitor, &monitor_str) != 0) {
        SCPI_ERR_RETURN;
    }
    SCPI_ResultCharacters(context, monitor_str, strlen(monitor_str));
    if(systemInfo.monitor.vol_monitor != MONITOR_NONE) {
        float stopValue = systemInfo.monitor.vol;
        SCPI_ResultFloat(context, stopValue);
    }
    return SCPI_RES_OK;
}


/*
 * @brief       监测器电流判定
 * @details
 */
static const scpi_choice_def_t scpi_monitor_Amp_def[] = {
    {"NONE", MONITOR_NONE},     //关闭
    {"<C", MONITOR_LESS},       //电流大于
    {">C", MONITOR_MORE},       //电流小于
    SCPI_CHOICE_LIST_END /* termination of option list */
};
scpi_result_t Cmd_Set_Monitor_Amp(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //判定条件
    int32_t monitor = {0};
    if(!SCPI_ParamChoice(context, scpi_monitor_Amp_def, &monitor, FALSE)) {
        SCPI_ERR_RETURN;
    }
    //数值
    scpi_number_t value = {0};
    if(SCPI_ParamNumber(context, scpi_special_numbers_def, &value, FALSE)) {
        if(value.special != FALSE) {
            switch(value.content.tag) {
                case SCPI_NUM_MIN:
                    value.content.value = AMP_MIN;
                    break;
                case SCPI_NUM_MAX:
                    value.content.value = AMP_MAX;
                    break;
            }
        }
    }
    IF_Display_Go_to_Page(PAGE_MONITOR);
    IF_Monitor_Set_Amp(monitor, value.content.value);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_Monitor_Amp(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //
    const char *monitor_str = "";
    if(!SCPI_ChoiceToName(scpi_monitor_Amp_def, systemInfo.monitor.amp_monitor, &monitor_str) != 0) {
        SCPI_ERR_RETURN;
    }
    SCPI_ResultCharacters(context, monitor_str, strlen(monitor_str));
    if(systemInfo.monitor.amp_monitor != MONITOR_NONE) {
        float stopValue = systemInfo.monitor.amp;
        SCPI_ResultFloat(context, stopValue);
    }
    return SCPI_RES_OK;
}


/*
 * @brief       监测器功率判定
 * @details
 */
static const scpi_choice_def_t scpi_monitor_Wat_def[] = {
    {"NONE", MONITOR_NONE},     //关闭
    {"<P", MONITOR_LESS},       //功率大于
    {">P", MONITOR_MORE},       //功率小于
    SCPI_CHOICE_LIST_END /* termination of option list */
};
scpi_result_t Cmd_Set_Monitor_Wat(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //判定条件
    int32_t monitor = {0};
    if(!SCPI_ParamChoice(context, scpi_monitor_Wat_def, &monitor, FALSE)) {
        SCPI_ERR_RETURN;
    }
    //数值
    scpi_number_t value = {0};
    if(SCPI_ParamNumber(context, scpi_special_numbers_def, &value, FALSE)) {
        if(value.special != FALSE) {
            switch(value.content.tag) {
                case SCPI_NUM_MIN:
                    value.content.value = WAT_MIN;
                    break;
                case SCPI_NUM_MAX:
                    value.content.value = WAT_MAX;
                    break;
            }
        }
    }
    IF_Display_Go_to_Page(PAGE_MONITOR);
    IF_Monitor_Set_Wat(monitor, value.content.value);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_Monitor_Wat(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //
    const char *monitor_str = "";
    if(!SCPI_ChoiceToName(scpi_monitor_Wat_def, systemInfo.monitor.wat_monitor, &monitor_str) != 0) {
        SCPI_ERR_RETURN;
    }
    SCPI_ResultCharacters(context, monitor_str, strlen(monitor_str));
    if(systemInfo.monitor.wat_monitor != MONITOR_NONE) {
        float stopValue = systemInfo.monitor.wat;
        SCPI_ResultFloat(context, stopValue);
    }
    return SCPI_RES_OK;
}



/*
 * @brief       监测器DVM判定
 * @details
 */
static const scpi_choice_def_t scpi_monitor_Dvm_def[] = {
    {"NONE", MONITOR_NONE},     //关闭
    {"<DVM", MONITOR_LESS},       //功率大于
    {">DVM", MONITOR_MORE},       //功率小于
    SCPI_CHOICE_LIST_END /* termination of option list */
};
scpi_result_t Cmd_Set_Monitor_Dvm(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //判定条件
    int32_t monitor = {0};
    if(!SCPI_ParamChoice(context, scpi_monitor_Dvm_def, &monitor, FALSE)) {
        SCPI_ERR_RETURN;
    }
    //数值
    scpi_number_t value = {0};
    if(SCPI_ParamNumber(context, scpi_special_numbers_def, &value, FALSE)) {
        if(value.special != FALSE) {
            switch(value.content.tag) {
                case SCPI_NUM_MIN:
                    value.content.value = DVM_MIN;
                    break;
                case SCPI_NUM_MAX:
                    value.content.value = DVM_MAX;
                    break;
            }
        }
    }
    IF_Display_Go_to_Page(PAGE_MONITOR);
    IF_Monitor_Set_Dvm(monitor, value.content.value);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_Monitor_Dvm(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //
    const char *monitor_str = "";
    if(!SCPI_ChoiceToName(scpi_monitor_Dvm_def, systemInfo.monitor.dvm_monitor, &monitor_str) != 0) {
        SCPI_ERR_RETURN;
    }
    SCPI_ResultCharacters(context, monitor_str, strlen(monitor_str));
    if(systemInfo.monitor.dvm_monitor != MONITOR_NONE) {
        float stopValue = systemInfo.monitor.dvm;
        SCPI_ResultFloat(context, stopValue);
    }
    return SCPI_RES_OK;
}



/*
 * @brief       监测器逻辑
 * @details
 */
static const scpi_choice_def_t scpi_monitor_Logic_def[] = {
    {"OR", LOGIC_OR},   //或
    {"AND", LOGIC_AND}, //与
    SCPI_CHOICE_LIST_END /* termination of option list */
};
scpi_result_t Cmd_Set_Monitor_Logic(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //数值
    uint8_t idx = 0;
    scpi_number_t value = {0};
    if(SCPI_ParamNumber(context, scpi_special_numbers_def, &value, FALSE)) {
        idx = value.content.value;
    }
    //判定条件
    int32_t monitor = {0};
    if(!SCPI_ParamChoice(context, scpi_monitor_Logic_def, &monitor, FALSE)) {
        SCPI_ERR_RETURN;
    }
    IF_Display_Go_to_Page(PAGE_MONITOR);
    IF_Monitor_Set_Logic(idx - 1, monitor);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_Monitor_Logic(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //数值
    uint8_t idx = 0;
    scpi_number_t value = {0};
    if(SCPI_ParamNumber(context, scpi_special_numbers_def, &value, FALSE)) {
        idx = value.content.value;
    } else {
        SCPI_ERR_RETURN
    }
    if(idx > ARRAY_COUNT(systemInfo.monitor.logic)) {
        SCPI_ERR_RETURN;
    }
    //
    const char *monitor_logic_str = "";
    if(!SCPI_ChoiceToName(scpi_monitor_Logic_def, systemInfo.monitor.logic[idx - 1], &monitor_logic_str) != 0) {
        SCPI_ERR_RETURN;
    }
    SCPI_ResultCharacters(context, monitor_logic_str, strlen(monitor_logic_str));
    return SCPI_RES_OK;
}

/*
 * @brief       监测器动作
 * @details
 */
enum {
    MONITOR_STOPWAY_BEEP = 0,
    MONITOR_STOPWAY_MSG,
    MONITOR_STOPWAY_OUTOFF,
};
static const scpi_choice_def_t scpi_monitor_stopWay_def[] = {
    {"BEEPER", MONITOR_STOPWAY_BEEP},
    {"MSG", MONITOR_STOPWAY_MSG},
    {"OUTOFF", MONITOR_STOPWAY_OUTOFF},
    SCPI_CHOICE_LIST_END /* termination of option list */
};
scpi_result_t Cmd_Set_Monitor_StopWay(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //设置对象
    int32_t monitor_stopWay = {0};
    if(!SCPI_ParamChoice(context, scpi_monitor_stopWay_def, &monitor_stopWay, FALSE)) {
        SCPI_ERR_RETURN;
    }
    scpi_bool_t param1 = {0};
    if(!SCPI_ParamBool(context, &param1, FALSE)) {
        SCPI_ERR_RETURN;
    }
    switch(monitor_stopWay)
    {
        case MONITOR_STOPWAY_BEEP:
            IF_Display_Go_to_Page(PAGE_MONITOR);
            IF_Monitor_Set_Beep(param1);
            break;
        case MONITOR_STOPWAY_MSG:
            IF_Display_Go_to_Page(PAGE_MONITOR);
            IF_Monitor_Set_Tips(param1);
            break;
        case MONITOR_STOPWAY_OUTOFF:
            IF_Display_Go_to_Page(PAGE_MONITOR);
            IF_Monitor_Set_PowerOFF(param1);
            break;
        default :
            SCPI_ERR_RETURN;
    }
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_Monitor_StopWay(scpi_t *context)
{
    __MULT_SCPI_ADDR_CHECK();
    //设置对象
    int32_t monitor_stopWay = {0};
    if(!SCPI_ParamChoice(context, scpi_monitor_stopWay_def, &monitor_stopWay, FALSE)) {
        SCPI_ERR_RETURN;
    }
    //
    const char *monitor_logic_str = "";
    switch(monitor_stopWay)
    {
        case MONITOR_STOPWAY_BEEP:
            monitor_logic_str = (systemInfo.monitor.beep) ? "ON" : "OFF";
            break;
        case MONITOR_STOPWAY_MSG:
            monitor_logic_str = (systemInfo.monitor.tips) ? "ON" : "OFF";
            break;
        case MONITOR_STOPWAY_OUTOFF:
            monitor_logic_str = (systemInfo.monitor.powerOFF) ? "ON" : "OFF";
            break;
        default :
            SCPI_ERR_RETURN;
    }
    SCPI_ResultCharacters(context, monitor_logic_str, strlen(monitor_logic_str));
    return SCPI_RES_OK;
}