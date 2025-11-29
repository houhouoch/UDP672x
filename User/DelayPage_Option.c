#include "DelayOut.h"
#include "DelayOutPage.h"
#include "Delay_Interface.h"
#include "DelayPage_Option.h"

#define STARTP_SET_VALUE        delayoutInfo.startpoint
#define COUNT_SET_VALUE         delayoutInfo.countpoint
#define CYCLES_SET_VALUE        delayoutInfo.cycles
#define LASTSTATE_SET_VALUE     delayoutInfo.lastState


#define PROTECT_STOP            delayoutInfo.stopCfg.stop
#define PROTECT_VOL_VALUE       delayoutInfo.stopCfg.vol
#define PROTECT_AMP_VALUE       delayoutInfo.stopCfg.amp
#define PROTECT_WAT_VALUE       delayoutInfo.stopCfg.wat


static void startP_RefreshUI(uint8_t *editIndex)
{
    lv_obj_t *obj = ui.DelayPage_btn_start_label;
    if(editIndex == NULL) {
        lv_obj_set_state(obj, LV_STATE_DEFAULT);
    } else {
        lv_obj_set_state(obj, LV_STATE_FOCUSED);
    }
    char stringSet[64] = {0};
    sprintf(stringSet, POINT_DISP_FORM, STARTP_SET_VALUE);
    if(editIndex != NULL) {
        label_setSelNum(obj, *editIndex, stringSet);
    } else {
    }
    lv_label_set_text(obj, stringSet);
}

void DelayPage_Option_editStartP_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return;
    }
    static uint8_t edit_index = 0;
    NumberInput_Process(7, UI_IF_Delay_Set_Start);
    switch(event)
    {
        case LV_EVENT_KEY:
        {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                //编码器右转,增大电压
                case LV_KEY_UP: {
                    int32_t temp = STARTP_SET_VALUE;
                    temp += point_step[edit_index];
                    UI_IF_Delay_Set_Start(temp);
                }
                break;
                //编码器左转,降低电压
                case LV_KEY_DOWN: {
                    int32_t temp = STARTP_SET_VALUE;
                    temp -= point_step[edit_index];
                    UI_IF_Delay_Set_Start(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(edit_index > 0)
                    {
                        edit_index--;
                    }
                    else
                    {
                        edit_index = sizeof(point_step) / sizeof(point_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_ENCODER:
                case LV_KEY_ENTER:
                case LV_KEY_LEFT: {
                    if(edit_index < (sizeof(point_step) / sizeof(point_step[0]) - 1))
                    {
                        edit_index++;
                    }
                    else
                    {
                        edit_index = 0;
                    }
                }
                break;
            }
            if(key != LV_KEY_ESC) {
                //更新显示选定 & 步进位
                startP_RefreshUI(&edit_index);
            } else {
                startP_RefreshUI(NULL);
            }
        }
        break;
        case LV_EVENT_REFRESH: {
            startP_RefreshUI(NULL);
        }
        break;
        case LV_EVENT_CLICKED: {
            edit_index = 0;
            startP_RefreshUI(&edit_index);
        }
        break;
    }
}

static void Count_RefreshUI(uint8_t *editIndex)
{
    lv_obj_t *obj = ui.DelayPage_btn_count_label;
    if(editIndex == NULL) {
        lv_obj_set_state(obj, LV_STATE_DEFAULT);
    } else {
        lv_obj_set_state(obj, LV_STATE_FOCUSED);
    }
    char stringSet[64] = {0};
    sprintf(stringSet, POINT_DISP_FORM, COUNT_SET_VALUE);
    if(editIndex != NULL) {
        label_setSelNum(obj, *editIndex, stringSet);
    } else {
    }
    lv_label_set_text(obj, stringSet);
}

void DelayPage_Option_editCount_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return;
    }
    static uint8_t edit_index = 0;
    NumberInput_Process(7, UI_IF_Delay_Set_Count);
    switch(event)
    {
        case LV_EVENT_KEY:
        {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                //编码器右转,增大电压
                case LV_KEY_UP: {
                    int32_t temp = COUNT_SET_VALUE;
                    temp += point_step[edit_index];
                    UI_IF_Delay_Set_Count(temp);
                }
                break;
                //编码器左转,降低电压
                case LV_KEY_DOWN: {
                    int32_t temp = COUNT_SET_VALUE;
                    temp -= point_step[edit_index];
                    UI_IF_Delay_Set_Count(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(edit_index > 0)
                    {
                        edit_index--;
                    }
                    else
                    {
                        edit_index = sizeof(point_step) / sizeof(point_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_ENCODER:
                case LV_KEY_ENTER:
                case LV_KEY_LEFT: {
                    if(edit_index < (sizeof(point_step) / sizeof(point_step[0]) - 1))
                    {
                        edit_index++;
                    }
                    else
                    {
                        edit_index = 0;
                    }
                }
                break;
            }
            if(key != LV_KEY_ESC) {
                //更新显示选定 & 步进位
                Count_RefreshUI(&edit_index);
            } else {
                Count_RefreshUI(NULL);
            }
        }
        break;
        case LV_EVENT_REFRESH: {
            Count_RefreshUI(NULL);
        }
        break;
        case LV_EVENT_CLICKED: {
            edit_index = 0;
            Count_RefreshUI(&edit_index);
        }
        break;
    }
}



static void Cycles_RefreshUI(uint8_t *editIndex)
{
    lv_obj_t *obj = ui.DelayPage_btn_cycle_label;
    if(editIndex == NULL) {
        lv_obj_set_state(obj, LV_STATE_DEFAULT);
    } else {
        lv_obj_set_state(obj, LV_STATE_FOCUSED);
    }
    //设置显示
    char stringSet[64] = {0};
    const char *str_Irf = "Inf";
    if(CYCLES_SET_VALUE > 0)
    {
        sprintf(stringSet, CYCLES_DISP_FORM, CYCLES_SET_VALUE);
        label_setSelNum(obj, *editIndex, stringSet);
    } else {
        sprintf(stringSet, "%s", str_Irf);
        label_setSelStr(obj, str_Irf, stringSet);
    }
    lv_label_set_text(obj, stringSet);
}


void DelayPage_Option_editCycles_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return;
    }
    static uint8_t edit_index = 0;
    NumberInput_Process(7, UI_IF_Delay_Set_Cycle);
    switch(event)
    {
        case LV_EVENT_KEY:
        {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                //编码器右转,增大电压
                case LV_KEY_UP: {
                    int32_t temp = CYCLES_SET_VALUE;
                    temp += cycle_step[edit_index];
                    UI_IF_Delay_Set_Cycle(temp);
                }
                break;
                //编码器左转,降低电压
                case LV_KEY_DOWN: {
                    int32_t temp = CYCLES_SET_VALUE;
                    temp -= cycle_step[edit_index];
                    UI_IF_Delay_Set_Cycle(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(edit_index > 0)
                    {
                        edit_index--;
                    }
                    else
                    {
                        edit_index = sizeof(cycle_step) / sizeof(cycle_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_ENCODER:
                case LV_KEY_ENTER:
                case LV_KEY_LEFT: {
                    if(edit_index < (sizeof(cycle_step) / sizeof(cycle_step[0]) - 1))
                    {
                        edit_index++;
                    }
                    else
                    {
                        edit_index = 0;
                    }
                }
                break;
            }
            if(key != LV_KEY_ESC) {
                //更新显示选定 & 步进位
                Cycles_RefreshUI(&edit_index);
            } else {
                Cycles_RefreshUI(NULL);
            }
        }
        break;
        case LV_EVENT_REFRESH: {
            Cycles_RefreshUI(NULL);
        }
        break;
        case LV_EVENT_CLICKED: {
            edit_index = 0;
            Cycles_RefreshUI(&edit_index);
        }
        break;
    }
}


#if 1

enum {
    STATE_NULL = 0,
    STATE_STOP_VAL,
    STATE_STOP,
    STATE_MIN = STATE_STOP_VAL,
    STATE_MAX = STATE_STOP,
};

static void Refresh(lv_obj_t *obj, uint8_t editState, uint8_t *editIndex)
{
    static char string[64] = {0};
    const char *rules_str = "";
    char val_str[32] = {0};
    memset(string, 0, sizeof(string));
    switch(PROTECT_STOP) {
        case DELAY_STOP_NONE: {
            rules_str = "NONE";
        }
        break;
        case DELAY_STOP_LESS_V: {
            rules_str = ">";
            sprintf(val_str, VOL_SET_FORM"V", PROTECT_VOL_VALUE);
        }
        break;
        case DELAY_STOP_MORE_V: {
            rules_str = "<";
            sprintf(val_str, VOL_SET_FORM"V", PROTECT_VOL_VALUE);
        }
        break;
        case DELAY_STOP_LESS_C: {
            rules_str = ">";
            sprintf(val_str, AMP_SET_FORM"A", PROTECT_AMP_VALUE);
        }
        break;
        case DELAY_STOP_MORE_C: {
            rules_str = "<";
            sprintf(val_str, AMP_SET_FORM"A", PROTECT_AMP_VALUE);
        }
        break;
        case DELAY_STOP_LESS_P: {
            rules_str = ">";
            sprintf(val_str, WAT_SET_FORM"W", PROTECT_WAT_VALUE);
        }
        break;
        case DELAY_STOP_MORE_P: {
            rules_str = "<";
            sprintf(val_str, WAT_SET_FORM"W", PROTECT_WAT_VALUE);
        }
        break;
    }
    strcat(string, rules_str);
    strcat(string, val_str);
    lv_label_set_text_static(obj, string);
    //高亮编辑项
    lv_obj_set_state(obj, LV_STATE_FOCUSED);
    switch(editState)
    {
        case STATE_NULL:
            lv_obj_set_state(obj, LV_STATE_DEFAULT);
            break;
        //条件
        case STATE_STOP:
            label_setSelStr(obj, rules_str, string);
            break;
        //数值
        case STATE_STOP_VAL:
            if(editIndex != NULL) {
                label_setSelNum(obj, *editIndex, string);
            }
            else  {
                label_setSelStr(obj, val_str, string);
            }
            break;
    }
}

void DelayPage_Option_stopVal_handler(lv_obj_t *obj, lv_event_t event)
{
    static uint8_t editState = STATE_NULL;
    lv_key_t key = 0;
    if(event == LV_EVENT_KEY) {
        key = *(lv_key_t *)lv_event_get_data();
    }
    static uint8_t editFlag = 0;
    static uint8_t edit_index = 0;
    static uint8_t editstepMax = 0;
    static uint8_t editstepMin = 0;
    static float editMax = 0;
    static float editMin = 0;
    static const float *edit_step = NULL;
    static float *edit_data = NULL;
    static const MultStr_Def *edit_minTips = NULL;
    static const MultStr_Def *edit_maxTips = NULL;
    //
    switch(PROTECT_STOP) {
        case DELAY_STOP_LESS_V:
        case DELAY_STOP_MORE_V: {
            edit_data = &PROTECT_VOL_VALUE;
        }
        break;
        case DELAY_STOP_LESS_C:
        case DELAY_STOP_MORE_C: {
            edit_data = &PROTECT_AMP_VALUE;
        }
        break;
        case DELAY_STOP_LESS_P:
        case DELAY_STOP_MORE_P: {
            edit_data = &PROTECT_WAT_VALUE;
        }
        break;
    }
    NumberInput_Process(7, UI_IF_Delay_Set_StopValue);
    //
    switch(event)
    {
        case LV_EVENT_KEY: {
            switch(key) {
                case LV_KEY_LEFT:
                {
                    if(editFlag != 0) {
                        if(edit_index < editstepMax)
                        {
                            edit_index++;
                        }
                        else
                        {
                            edit_index = editstepMin;
                        }
                        break;
                    } else {
                        if(PROTECT_STOP != DELAY_STOP_NONE) {
                            editState = (editState >= STATE_MAX) ? STATE_MIN : (editState + 1);
                        } else {
                            editState = STATE_STOP;
                        }
                    }
                }
                break;
                case LV_KEY_RIGHT:
                {
                    if(editFlag != 0) {
                        if(edit_index > editstepMin)
                        {
                            edit_index--;
                        }
                        else
                        {
                            edit_index = editstepMax;
                        }
                        break;
                    } else {
                        if(PROTECT_STOP != DELAY_STOP_NONE) {
                            editState = (editState <= STATE_MIN) ? STATE_MAX : (editState - 1);
                        } else {
                            editState = STATE_STOP;
                        }
                    }
                }
                break;
                case LV_KEY_UP: {
                    if(editFlag != 0) {
                        *edit_data += edit_step[edit_index];
                        if(*edit_data > editMax) {
                            *edit_data = editMax;
                            IF_MsgBox_Tips_Mult(edit_maxTips);
                        }
                    } else {
                        if(PROTECT_STOP != DELAY_STOP_NONE) {
                            editState = (editState >= STATE_MAX) ? STATE_MIN : (editState + 1);
                        } else {
                            editState = STATE_STOP;
                        }
                    }
                }
                break;
                case LV_KEY_DOWN: {
                    if(editFlag != 0) {
                        *edit_data -= edit_step[edit_index];
                        if(*edit_data < editMin) {
                            *edit_data = editMin;
                            IF_MsgBox_Tips_Mult(edit_minTips);
                        }
                    } else {
                        if(PROTECT_STOP != DELAY_STOP_NONE) {
                            editState = (editState <= STATE_MIN) ? STATE_MAX : (editState - 1);
                        } else {
                            editState = STATE_STOP;
                        }
                    }
                }
                break;
                //修改变量
                case LV_KEY_ENCODER:
                case LV_KEY_ENTER: {
                    if(editFlag != 0) {
                        if(edit_index < editstepMax) {
                            edit_index = edit_index + 1;
                        } else {
                            edit_index = editstepMin;
                            editFlag = 0;   //退出编辑
                        }
                    } else {
                        switch(editState) {
                            case STATE_STOP: {
                                PROTECT_STOP = (PROTECT_STOP < DELAY_STOP_MAX) ? (PROTECT_STOP + 1) : DELAY_STOP_MIN;
                            }
                            break;
                            case STATE_STOP_VAL: {
                                editFlag = 1;
                                switch(PROTECT_STOP) {
                                    case DELAY_STOP_LESS_V:
                                    case DELAY_STOP_MORE_V: {
                                        editstepMax = sizeof(V_step) / sizeof(V_step[0]) - 1;
                                        editstepMin = 0;
                                        edit_step = V_step;
                                        editMax = VOL_MAX;
                                        editMin = VOL_MIN;
                                        edit_data = &PROTECT_VOL_VALUE;
                                        edit_index = 0;
                                        edit_maxTips = &mStr_OutSet_MaxVol;
                                    }
                                    break;
                                    case DELAY_STOP_LESS_C:
                                    case DELAY_STOP_MORE_C: {
                                        editstepMax = sizeof(A_step) / sizeof(A_step[0]) - 1;
                                        editstepMin = 0;
                                        edit_step = A_step;
                                        editMax = AMP_MAX;
                                        editMin = AMP_MIN;
                                        edit_data = &PROTECT_AMP_VALUE;
                                        edit_index = 0;
                                        edit_maxTips = &mStr_OutSet_MaxAmp;
                                    }
                                    break;
                                    case DELAY_STOP_LESS_P:
                                    case DELAY_STOP_MORE_P: {
                                        editstepMax = sizeof(W_step) / sizeof(W_step[0]) - 1;
                                        editstepMin = 0;
                                        edit_step = W_step;
                                        editMax = WAT_MAX;
                                        editMin = WAT_MIN;
                                        edit_data = &PROTECT_WAT_VALUE;
                                        edit_index = 0;
                                        edit_maxTips = &mStr_OutSet_MaxWat;
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }
                break;
                case LV_KEY_ESC: {
                    if(editFlag == 0) {
                        editState = STATE_NULL;
                    }
                    editFlag = 0;
                    Refresh(obj, STATE_NULL, NULL);
                    return;
                }
            }
        }
        break;
        case LV_EVENT_CLICKED: {
            editFlag = 0;
            edit_index = 0;
            editState = STATE_STOP;
        }
        break;
    }
    if(editFlag == 0) {
        Refresh(obj, editState, NULL);
    } else {
        Refresh(obj, editState, &edit_index);
    }
}






static void editLastState_Refresh(lv_obj_t *obj)
{
    //刷新显示
    switch(LASTSTATE_SET_VALUE) {
        case DELAY_ENDSTATE_OFF: {
            lv_label_set_text_static(obj, "OFF");
        }
        break;
        case DELAY_ENDSTATE_ON: {
            lv_label_set_text_static(obj, "ON");
        }
        break;
        case DELAY_ENDSTATE_LAST: {
            lv_label_set_text_static(obj, "LAST");
        }
        break;
    }
}

void DelayPage_Option_lastState_handler(lv_obj_t *obj, lv_event_t event)
{
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                case LV_KEY_ENCODER:
                case LV_KEY_ENTER: {
                    LASTSTATE_SET_VALUE += 1;
                    if(LASTSTATE_SET_VALUE > DELAY_ENDSTATE_MAX)
                    {
                        LASTSTATE_SET_VALUE = DELAY_ENDSTATE_MIN;
                    }
                }
                break;
            }
        }
        break;
        case LV_EVENT_CLICKED: {
            LASTSTATE_SET_VALUE += 1;
            if(LASTSTATE_SET_VALUE > DELAY_ENDSTATE_MAX)
            {
                LASTSTATE_SET_VALUE = DELAY_ENDSTATE_MIN;
            }
            GUI_SEND_KEY(LV_KEY_RETURN);
        }
        break;
    }
    editLastState_Refresh(obj);
}

#endif
