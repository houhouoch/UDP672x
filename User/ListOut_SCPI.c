#include "ListOut_SCPI.h"

#include "main.h"
#include "Commd.h"


#include "List_Interface.h"
#include "ListTemp_Interface.h"

/*
 * @brief       List模板波形类型
 * @details
 */
static const scpi_choice_def_t scpi_listtemp_type_def[] = {
    {"SINE", TEMP_TYPE_Sin},            //正弦波       反相/角度
    {"PULSE", TEMP_TYPE_Pulse},         //脉冲波       占空比
    {"RAMP", TEMP_TYPE_Ramp},           //斜波         对称性
    {"UP", TEMP_TYPE_Stair_Up},         //阶梯上升
    {"DN", TEMP_TYPE_Stair_Down},       //阶梯下降
    {"UPDN", TEMP_TYPE_Stair_UpDown},   //阶梯上下
    {"RISE", TEMP_TYPE_expUp},          //指数上升      指数
    {"FALL", TEMP_TYPE_expDown},        //指数下降      指数

    SCPI_CHOICE_LIST_END /* termination of option list */
};
scpi_result_t Cmd_Set_ListTemp_Type(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    int32_t type = 0;
    if(SCPI_ParamChoice(context, scpi_listtemp_type_def, &type, false)) {
        IF_Display_Go_to_Page(PAGE_LIST_TEMP);
        IF_ListTemp_Set_Type(type);
    }
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_ListTemp_Type(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    const char *buffer = "";
    if(SCPI_ChoiceToName(scpi_listtemp_type_def, ListTempInfo.param[ListTempInfo.edit_obj].temp_type, &buffer) != 0) {
        uint16_t length = strlen(buffer);
        SCPI_ResultCharacters(context, buffer, length);
    }
    return SCPI_RES_OK;
}




/*
 * @brief       List模板变量
 * @details
 */
static const scpi_choice_def_t scpi_listtemp_obj_def[] = {
    {"V", LISTTEMP_EDIT_OBJECT_VOL},     //电压
    {"C", LISTTEMP_EDIT_OBJECT_AMP},     //电流

    SCPI_CHOICE_LIST_END /* termination of option list */
};
scpi_result_t Cmd_Set_ListTemp_Obj(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    int32_t obj = 0;
    if(SCPI_ParamChoice(context, scpi_listtemp_obj_def, &obj, false)) {
        IF_Display_Go_to_Page(PAGE_LIST_TEMP);
        IF_ListTemp_Set_Object(obj);
    }
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_ListTemp_Obj(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    const char *buffer = "";
    if(SCPI_ChoiceToName(scpi_listtemp_obj_def, ListTempInfo.edit_obj, &buffer) != 0) {
        uint16_t length = strlen(buffer);
        SCPI_ResultCharacters(context, buffer, length);
    }
    return SCPI_RES_OK;
}



/*
 * @brief       List模板起点
 * @details
 */
//起始点
scpi_result_t Cmd_Set_ListTemp_Start(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    scpi_number_t param1 = {0};
    if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &param1, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(param1.special != FALSE) {
        switch(param1.content.tag) {
            case SCPI_NUM_MIN:
                param1.content.value = LIST_POINT_MIN;
                break;
            case SCPI_NUM_MAX:
                param1.content.value = LIST_POINT_MAX;
                break;
        }
    }
    IF_Display_Go_to_Page(PAGE_LIST_TEMP);
    IF_ListTemp_Set_Start(param1.content.value);
    return SCPI_RES_OK;
}

scpi_result_t Cmd_Read_ListTemp_Start(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    char buffer[32] = {0};
    uint16_t length = sprintf(buffer, POINT_DISP_FORM, ListTempInfo.startpoint);
    SCPI_ResultCharacters(context, buffer, length);
    return SCPI_RES_OK;
}

/*
 * @brief       List模板总点数
 * @details
 */
//总点数
scpi_result_t Cmd_Set_ListTemp_Count(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    scpi_number_t param1 = {0};
    if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &param1, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(param1.special != FALSE) {
        switch(param1.content.tag) {
            case SCPI_NUM_MIN:
                param1.content.value = LIST_POINT_MIN;
                break;
            case SCPI_NUM_MAX:
                param1.content.value = LIST_POINT_MAX;
                break;
        }
    }
    IF_Display_Go_to_Page(PAGE_LIST_TEMP);
    IF_ListTemp_Set_Count(param1.content.value);
    return SCPI_RES_OK;
}

scpi_result_t Cmd_Read_ListTemp_Count(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    char buffer[32] = {0};
    uint16_t length = sprintf(buffer, POINT_DISP_FORM, ListTempInfo.totalCount);
    SCPI_ResultCharacters(context, buffer, length);
    return SCPI_RES_OK;
}




/*
 * @brief       List模板最大值
 * @details
 */
//最大值
scpi_result_t Cmd_Set_ListTemp_MaxValue(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    scpi_number_t param1 = {0};
    if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &param1, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(param1.special != FALSE) {
        switch(param1.content.tag) {
            case SCPI_NUM_MIN:
                param1.content.value = ListTempInfo.param[ListTempInfo.edit_obj].minValue;
                break;
            case SCPI_NUM_MAX: {
                switch(ListTempInfo.param[ListTempInfo.edit_obj].temp_type) {
                    case LISTTEMP_EDIT_OBJECT_VOL:
                        param1.content.value = VOL_MAX;
                        break;
                    case LISTTEMP_EDIT_OBJECT_AMP:
                        param1.content.value = AMP_MAX;
                        break;
                }
            }
            break;
        }
    }
    IF_Display_Go_to_Page(PAGE_LIST_TEMP);
    IF_ListTemp_Set_MaxValue(param1.content.value);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_ListTemp_MaxValue(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    char buffer[32] = {0};
    uint16_t length = 0;
    switch(ListTempInfo.param[ListTempInfo.edit_obj].temp_type) {
        case LISTTEMP_EDIT_OBJECT_VOL:
            length = sprintf(buffer, VOL_SET_FORM, ListTempInfo.param[ListTempInfo.edit_obj].maxValue);
            break;
        case LISTTEMP_EDIT_OBJECT_AMP:
            length = sprintf(buffer, AMP_SET_FORM, ListTempInfo.param[ListTempInfo.edit_obj].maxValue);
            break;
    }
    SCPI_ResultCharacters(context, buffer, length);
    return SCPI_RES_OK;
}


/*
 * @brief       List模板最小值
 * @details
 */
//最小值
scpi_result_t Cmd_Set_ListTemp_MinValue(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    scpi_number_t param1 = {0};
    if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &param1, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(param1.special != FALSE) {
        switch(param1.content.tag) {
            case SCPI_NUM_MIN: {
                switch(ListTempInfo.param[ListTempInfo.edit_obj].temp_type) {
                    case LISTTEMP_EDIT_OBJECT_VOL:
                        param1.content.value = VOL_MIN;
                        break;
                    case LISTTEMP_EDIT_OBJECT_AMP:
                        param1.content.value = AMP_MIN;
                        break;
                }
            }
            break;
            case SCPI_NUM_MAX:
                param1.content.value = ListTempInfo.param[ListTempInfo.edit_obj].maxValue;
                break;
        }
    }
    IF_Display_Go_to_Page(PAGE_LIST_TEMP);
    IF_ListTemp_Set_MinValue(param1.content.value);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_ListTemp_MinValue(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    char buffer[32] = {0};
    uint16_t length = 0;
    switch(ListTempInfo.param[ListTempInfo.edit_obj].temp_type) {
        case LISTTEMP_EDIT_OBJECT_VOL:
            length = sprintf(buffer, VOL_SET_FORM, ListTempInfo.param[ListTempInfo.edit_obj].minValue);
            break;
        case LISTTEMP_EDIT_OBJECT_AMP:
            length = sprintf(buffer, AMP_SET_FORM, ListTempInfo.param[ListTempInfo.edit_obj].minValue);
            break;
    }
    SCPI_ResultCharacters(context, buffer, length);
    return SCPI_RES_OK;
}

/*
 * @brief       List模板时间间隔
 * @details
 */
//时间间隔
scpi_result_t Cmd_Set_ListTemp_Interval(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    scpi_number_t param1 = {0};
    if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &param1, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(param1.special != FALSE) {
        switch(param1.content.tag) {
            case SCPI_NUM_MIN:
                param1.content.value = KT_MIN;
                break;
            case SCPI_NUM_MAX:
                param1.content.value = KT_MAX;
                break;
        }
    }
    IF_Display_Go_to_Page(PAGE_LIST_TEMP);
    IF_ListTemp_Set_Interval(param1.content.value);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_ListTemp_Interval(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    char buffer[32] = {0};
    uint16_t length = 0;
    length = sprintf(buffer, KEEP_TIME_FORM, ListTempInfo.interval);
    SCPI_ResultCharacters(context, buffer, length);
    return SCPI_RES_OK;
}


/*
 * @brief       List模板波形反相设置
 * @details
 */
//反相
scpi_result_t Cmd_Set_ListTemp_Invert(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    scpi_bool_t param1 = {0};
    if(!SCPI_ParamBool(context, &param1, FALSE)) {
        SCPI_ERR_RETURN;
    }
    IF_Display_Go_to_Page(PAGE_LIST_TEMP);
    IF_ListTemp_Set_Invert(param1);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_ListTemp_Invert(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    char buffer[32] = "";
    int length = snprintf(buffer, sizeof(buffer) - 1, "%s", (ListTempInfo.param[ListTempInfo.edit_obj].invert != 0) ? "ON" : "OFF");
    SCPI_ResultCharacters(context, buffer, length);
    return SCPI_RES_OK;
}


/*
 * @brief       List模板Pulse波形周期
 * @details
 */
//周期(仅pulse模式)
scpi_result_t Cmd_Set_ListTemp_Period(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    scpi_number_t param1 = {0};
    if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &param1, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(param1.special != FALSE) {
        switch(param1.content.tag) {
            case SCPI_NUM_MIN:
                param1.content.value = ListTempInfo.param[ListTempInfo.edit_obj].pluseWidth;
                break;
            case SCPI_NUM_MAX:
                param1.content.value = KT_MAX;
                break;
        }
    }
    IF_Display_Go_to_Page(PAGE_LIST_TEMP);
    IF_ListTemp_Set_Period(param1.content.value);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_ListTemp_Period(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    char buffer[32] = {0};
    uint16_t length = 0;
    length = sprintf(buffer, KEEP_TIME_FORM, ListTempInfo.param[ListTempInfo.edit_obj].plusePeriod);
    SCPI_ResultCharacters(context, buffer, length);
    return SCPI_RES_OK;
}


/*
 * @brief       List模板Pulse脉宽
 * @details
 */
//脉宽(仅pulse模式)
scpi_result_t Cmd_Set_ListTemp_Width(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    scpi_number_t param1 = {0};
    if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &param1, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(param1.special != FALSE) {
        switch(param1.content.tag) {
            case SCPI_NUM_MIN:
                param1.content.value = KT_MIN;
                break;
            case SCPI_NUM_MAX:
                param1.content.value = ListTempInfo.param[ListTempInfo.edit_obj].plusePeriod;
                break;
        }
    }
    IF_Display_Go_to_Page(PAGE_LIST_TEMP);
    IF_ListTemp_Set_Width(param1.content.value);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_ListTemp_Width(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    char buffer[32] = {0};
    uint16_t length = 0;
    length = sprintf(buffer, KEEP_TIME_FORM, ListTempInfo.param[ListTempInfo.edit_obj].pluseWidth);
    SCPI_ResultCharacters(context, buffer, length);
    return SCPI_RES_OK;
}


/*
 * @brief       List模板波形对称性
 * @details
 */
//对称性
scpi_result_t Cmd_Set_ListTemp_Symmetry(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    scpi_number_t param1 = {0};
    if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &param1, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(param1.special != FALSE) {
        switch(param1.content.tag) {
            case SCPI_NUM_MIN:
                param1.content.value = SYMMETRY_MIN;
                break;
            case SCPI_NUM_MAX:
                param1.content.value = SYMMETRY_MAX;
                break;
        }
    }
    IF_Display_Go_to_Page(PAGE_LIST_TEMP);
    IF_ListTemp_Set_Symmetry(param1.content.value);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_ListTemp_Symmetry(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    char buffer[32] = {0};
    uint16_t length = 0;
    length = sprintf(buffer, SYMMETRY_FORM, ListTempInfo.param[ListTempInfo.edit_obj].Symmetry);
    SCPI_ResultCharacters(context, buffer, length);
    return SCPI_RES_OK;
}


/*
 * @brief       List模板指数波形指数参数
 * @details
 */
//指数
scpi_result_t Cmd_Set_ListTemp_ExpValue(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    scpi_number_t param1 = {0};
    if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &param1, FALSE)) {
        SCPI_ERR_RETURN;
    }
    if(param1.special != FALSE) {
        switch(param1.content.tag) {
            case SCPI_NUM_MIN:
                param1.content.value = EXP_VALUE_MIN;
                break;
            case SCPI_NUM_MAX:
                param1.content.value = EXP_VALUE_MAX;
                break;
        }
    }
    IF_Display_Go_to_Page(PAGE_LIST_TEMP);
    IF_ListTemp_Set_expValue(param1.content.value);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_ListTemp_ExpValue(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    char buffer[32] = {0};
    uint16_t length = 0;
    length = sprintf(buffer, SYMMETRY_FORM, ListTempInfo.param[ListTempInfo.edit_obj].expValue);
    SCPI_ResultCharacters(context, buffer, length);
    return SCPI_RES_OK;
}


/*
 * @brief       List模板波形生成
 * @details
 */
scpi_result_t Cmd_ListTemp_Generate(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    IF_Display_Go_to_Page(PAGE_LIST_TEMP);
    IF_ListTemp_Generate();
    return SCPI_RES_OK;
}





/*
 * @brief       List开关
 * @details
 */
//结束状态
static const scpi_choice_def_t scpi_list_lastState_def[] = {
    {"OFF", LIST_ENDSTATE_OFF},     //关闭
    {"LAST", LIST_ENDSTATE_LAST},   //保持
    SCPI_CHOICE_LIST_END /* termination of option list */
};


static const scpi_choice_def_t scpi_list_state_def[] = {
    {"OFF", LIST_STATE_STOP},     //关闭
    {"ON", LIST_STATE_RUNNING},   //开启
    {"PAUSE", LIST_STATE_PAUSE},   //暂停
    SCPI_CHOICE_LIST_END /* termination of option list */
};
//List功能开关
scpi_result_t Cmd_Set_List_State(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //    scpi_bool_t param1 = {0};
    //    if(!SCPI_ParamBool(context, &param1, FALSE)) {
    //        SCPI_ERR_RETURN;
    //    }
    //    IF_List_Set_On_Off(param1);
    int32_t newstate = 0;
    if(!SCPI_ParamChoice(context, scpi_list_state_def, &newstate, false)) {
        SCPI_ERR_RETURN;
    }
    IF_Display_Go_to_Page(PAGE_LIST);
    IF_ListOut_Set_State(newstate);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_List_State(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //返回:状态,当前点剩余,当前点,终止点,剩余次数,终止状态
    const char *state_str = "";
    if(!SCPI_ChoiceToName(scpi_list_state_def, listoutInfo.state, &state_str) != 0) {
        SCPI_ERR_RETURN;
    }
    float remainingTime = ListOut_RemainingTime();
    int currPoint = listoutInfo.current;
    int endPoint = listoutInfo.startpoint + listoutInfo.countpoint;
    int remainingCycle = 0;
    if(listoutInfo.cycles != 0) {
        remainingCycle = listoutInfo.cycles - listoutInfo.loop;
    } else {
        remainingCycle = CYCLE_MAX;
    }
    const char *lastState_str = "";
    if(!SCPI_ChoiceToName(scpi_list_lastState_def, listoutInfo.lastState, &lastState_str) != 0) {
        SCPI_ERR_RETURN;
    }
    char buffer[128] = {0};
    uint16_t length = 0;
    length = sprintf(buffer, "%s,"KEEP_TIME_FORM","POINT_DISP_FORM","POINT_DISP_FORM","CYCLES_DISP_FORM",%s",
                     state_str, remainingTime, currPoint, endPoint,
                     remainingCycle, lastState_str);
    SCPI_ResultCharacters(context, buffer, length);
    return SCPI_RES_OK;
}


/*
 * @brief       List基础参数
 * @details
 */
//设置基本参数
scpi_result_t Cmd_Set_List_Base(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    scpi_number_t param_start = {0};
    if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &param_start, FALSE)) {
        SCPI_ERR_RETURN;
    }
    scpi_number_t param_count = {0};
    if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &param_count, FALSE)) {
        SCPI_ERR_RETURN;
    }
    scpi_number_t param_cycle = {0};
    if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &param_cycle, FALSE)) {
        SCPI_ERR_RETURN;
    }
    int32_t param_laststate = 0;
    if(!SCPI_ParamChoice(context, scpi_list_lastState_def, &param_laststate, false)) {
        SCPI_ERR_RETURN;
    }
    //运行中不能改变参数
    if(ListOut_IsRunning() != 0) {
        IF_MsgBox_Tips_Mult(&mStr_list_noedit);
        SCPI_ERR_RETURN;
    }
    IF_Display_Go_to_Page(PAGE_LIST);
    IF_List_Set_Start(param_start.content.value);
    IF_List_Set_Count(param_count.content.value);
    IF_List_Set_Cycle(param_cycle.content.value);
    IF_List_Set_lastState(param_laststate);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_List_Base(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //返回:起始点,总点数,循环次数,停止状态
    uint16_t startPoint = listoutInfo.startpoint;
    uint16_t countpoint = listoutInfo.countpoint;
    uint16_t cycles = listoutInfo.cycles;
    const char *lastState_str = "";
    if(!SCPI_ChoiceToName(scpi_list_lastState_def, listoutInfo.lastState, &lastState_str) != 0) {
        SCPI_ERR_RETURN;
    }
    char buffer[128] = {0};
    uint16_t length = 0;
    length = sprintf(buffer, POINT_DISP_FORM","POINT_DISP_FORM","CYCLES_DISP_FORM",""%s",
                     startPoint, countpoint, cycles, lastState_str);
    SCPI_ResultCharacters(context, buffer, length);
    return SCPI_RES_OK;
}





/*
 * @brief       List点参数
 * @details
 */
//设置点参数
scpi_result_t Cmd_Set_List_PointParam(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    scpi_number_t param_index = {0};
    if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &param_index, FALSE)) {
        SCPI_ERR_RETURN;
    }
    scpi_number_t param_volt = {0};
    if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &param_volt, FALSE)) {
        SCPI_ERR_RETURN;
    }
    scpi_number_t param_curr = {0};
    if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &param_curr, FALSE)) {
        SCPI_ERR_RETURN;
    }
    scpi_number_t param_time = {0};
    if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &param_time, FALSE)) {
        SCPI_ERR_RETURN;
    }
    //运行中不能改变参数
    if(ListOut_IsRunning() != 0) {
        IF_MsgBox_Tips_Mult(&mStr_list_noset);
        SCPI_ERR_RETURN;
    }
    IF_Display_Go_to_Page(PAGE_LIST);
    IF_List_Set_PointParam(param_index.content.value, param_volt.content.value,
                           param_curr.content.value, param_time.content.value);
    return SCPI_RES_OK;
}
scpi_result_t Cmd_Read_List_PointParam(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    uint16_t readPoint = 0;
    uint16_t readCount = 0;
    scpi_number_t param_readIdx = {0};
    if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &param_readIdx, FALSE)) {
        SCPI_ERR_RETURN;
    } else {
        readPoint = param_readIdx.content.value;
    }
    scpi_number_t param_readCount = {0};
    if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &param_readCount, FALSE)) {
        readCount = 1;
    } else {
        readCount = param_readCount.content.value;
    }
    if(readCount > 5) {
        readCount = 5;
    }
    //发送数据
    for(uint16_t i = 0; i < readCount; ++i) {
        //返回:索引,电压,电流,时长
        char buffer[128] = {0};
        uint16_t length = 0;
        uint16_t idx = (readPoint + i);
        length = sprintf(buffer, POINT_DISP_FORM","VOL_SET_FORM","AMP_SET_FORM","KEEP_TIME_FORM";",
                         idx, listoutInfo.points[idx].vol, listoutInfo.points[idx].amp, listoutInfo.points[idx].kT);
        SCPI_ResultArbitraryBlock(context, buffer, length);
    }
    return SCPI_RES_OK;
}



scpi_result_t Cmd_Read_List_FileName(scpi_t *context) {
    __MULT_SCPI_ADDR_CHECK();
    //
    SCPI_ResultCharacters(context, systemInfo.userInfo.fileName_Listout, strlen(systemInfo.userInfo.fileName_Listout));
    return SCPI_RES_OK;
}
