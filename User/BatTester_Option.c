#include "BatTester.h"
#include "BatTesterPage.h"
#include "BatTester_Interface.h"
#include "BatTester_Option.h"

#define STARTP_SET_VALUE        BatTester.startpoint
#define COUNT_SET_VALUE         BatTester.countpoint
#define CYCLES_SET_VALUE        BatTester.cycles
#define LASTSTATE_SET_VALUE     BatTester.lastState


#define TRIG_TIME_SET_VALUE     BatTester.trigTime


void BatTester_Option_TipsSet_handler(lv_obj_t *obj, lv_event_t event) {}



enum {
    EDIT_STATE_DEFAULT = 0,
    EDIT_STATE_PROTECT_VALUE_0,
    EDIT_STATE_PROTECT_LOGIC_1,
    EDIT_STATE_PROTECT_VALUE_1,
    EDIT_STATE_PROTECT_LOGIC_2,
    EDIT_STATE_PROTECT_VALUE_2,
    EDIT_STATE_PROTECT_LOGIC_3,
    EDIT_STATE_PROTECT_VALUE_3,
};
static uint8_t edit_State = EDIT_STATE_DEFAULT;
/*
 * @brief
 * @details
 */
static void StopSet_RefreshUI(lv_obj_t *obj, uint8_t *editIndex, BatTester_Stop_Def stopcfg[3], uint8_t edit)
{
    char value_str[3][64] = {0};
    const char *logic_str[3] = {""};
    //参数0
    switch(stopcfg[0].stop)
    {
        case __STOP_NONE:
            sprintf(value_str[0], "False");
            break;
        case __STOP_MORE_V:
            sprintf(value_str[0], "Vo>"BAT_TESTER_VOL_SET_FORM, stopcfg[0].value);
            break;
        case __STOP_LESS_V:
            sprintf(value_str[0], "Vo<"BAT_TESTER_VOL_SET_FORM, stopcfg[0].value);
            break;
        case __STOP_MORE_C:
            sprintf(value_str[0], "Io>"BAT_TESTER_AMP_SET_FORM, stopcfg[0].value);
            break;
        case __STOP_LESS_C:
            sprintf(value_str[0], "Io<"BAT_TESTER_AMP_SET_FORM, stopcfg[0].value);
            break;
        case __STOP_MORE_P:
            sprintf(value_str[0], "Po>"BAT_TESTER_WAT_SET_FORM, stopcfg[0].value);
            break;
        case __STOP_LESS_P:
            sprintf(value_str[0], "Po<"BAT_TESTER_WAT_SET_FORM, stopcfg[0].value);
            break;
        case __STOP_MORE_DVM:
            sprintf(value_str[0], "Dvm>"BAT_TESTER_DVM_SET_FORM, stopcfg[0].value);
            break;
        case __STOP_LESS_DVM:
            sprintf(value_str[0], "Dvm<"BAT_TESTER_DVM_SET_FORM, stopcfg[0].value);
            break;
    }
    //参数1
    switch(stopcfg[1].logic)
    {
        case _STOP_LOGIC_AND:
            logic_str[1] = MultStr_GetS(&mStr_Battest_Logic_AND);
            break;
        case _STOP_LOGIC_OR:
            logic_str[1] = MultStr_GetS(&mStr_Battest_Logic_OR);
            break;
    }
    switch(stopcfg[1].stop)
    {
        case __STOP_NONE:
            sprintf(value_str[1], "False");
            break;
        case __STOP_MORE_V:
            sprintf(value_str[1], "Vo>"BAT_TESTER_VOL_SET_FORM, stopcfg[1].value);
            break;
        case __STOP_LESS_V:
            sprintf(value_str[1], "Vo<"BAT_TESTER_VOL_SET_FORM, stopcfg[1].value);
            break;
        case __STOP_MORE_C:
            sprintf(value_str[1], "Io>"BAT_TESTER_AMP_SET_FORM, stopcfg[1].value);
            break;
        case __STOP_LESS_C:
            sprintf(value_str[1], "Io<"BAT_TESTER_AMP_SET_FORM, stopcfg[1].value);
            break;
        case __STOP_MORE_P:
            sprintf(value_str[1], "Po>"BAT_TESTER_WAT_SET_FORM, stopcfg[1].value);
            break;
        case __STOP_LESS_P:
            sprintf(value_str[1], "Po<"BAT_TESTER_WAT_SET_FORM, stopcfg[1].value);
            break;
        case __STOP_MORE_DVM:
            sprintf(value_str[1], "Dvm>"BAT_TESTER_DVM_SET_FORM, stopcfg[1].value);
            break;
        case __STOP_LESS_DVM:
            sprintf(value_str[1], "Dvm<"BAT_TESTER_DVM_SET_FORM, stopcfg[1].value);
            break;
    }
    //参数2
    switch(stopcfg[2].logic)
    {
        case _STOP_LOGIC_AND:
            logic_str[2] = MultStr_GetS(&mStr_Battest_Logic_AND);
            break;
        case _STOP_LOGIC_OR:
            logic_str[2] = MultStr_GetS(&mStr_Battest_Logic_OR);
            break;
    }
    switch(stopcfg[2].stop)
    {
        case __STOP_NONE:
            sprintf(value_str[2], "False");
            break;
        case __STOP_MORE_V:
            sprintf(value_str[2], "Vo>"BAT_TESTER_VOL_SET_FORM, stopcfg[2].value);
            break;
        case __STOP_LESS_V:
            sprintf(value_str[2], "Vo<"BAT_TESTER_VOL_SET_FORM, stopcfg[2].value);
            break;
        case __STOP_MORE_C:
            sprintf(value_str[2], "Io>"BAT_TESTER_AMP_SET_FORM, stopcfg[2].value);
            break;
        case __STOP_LESS_C:
            sprintf(value_str[2], "Io<"BAT_TESTER_AMP_SET_FORM, stopcfg[2].value);
            break;
        case __STOP_MORE_P:
            sprintf(value_str[2], "Po>"BAT_TESTER_WAT_SET_FORM, stopcfg[2].value);
            break;
        case __STOP_LESS_P:
            sprintf(value_str[2], "Po<"BAT_TESTER_WAT_SET_FORM, stopcfg[2].value);
            break;
        case __STOP_MORE_DVM:
            sprintf(value_str[2], "Dvm>"BAT_TESTER_DVM_SET_FORM, stopcfg[2].value);
            break;
        case __STOP_LESS_DVM:
            sprintf(value_str[2], "Dvm<"BAT_TESTER_DVM_SET_FORM, stopcfg[2].value);
            break;
    }
    uint16_t sel_idx[2] = {0};
    char disp_str[128] = {0};
    sel_idx[0] = strlen(disp_str);
    sprintf(disp_str, "%s", value_str[0]);
    sel_idx[1] = strlen(disp_str);
    if(edit == EDIT_STATE_PROTECT_VALUE_0) {
        if((editIndex == NULL) || (stopcfg[0].stop == __STOP_NONE)) {
            lv_label_set_text_sel_start(obj, sel_idx[0]);
            lv_label_set_text_sel_end(obj, sel_idx[1]);
        } else {
            label_setSelNum(obj, *editIndex, disp_str);
        }
    }
    sel_idx[0] = strlen(disp_str);
    sprintf(disp_str, "%s%s", disp_str, logic_str[1]);
    sel_idx[1] = strlen(disp_str);
    if(edit == EDIT_STATE_PROTECT_LOGIC_1) {
        lv_label_set_text_sel_start(obj, sel_idx[0]);
        lv_label_set_text_sel_end(obj, sel_idx[1]);
    }
    sel_idx[0] = strlen(disp_str);
    sprintf(disp_str, "%s%s", disp_str, value_str[1]);
    sel_idx[1] = strlen(disp_str);
    if(edit == EDIT_STATE_PROTECT_VALUE_1) {
        if((editIndex == NULL) || (stopcfg[1].stop == __STOP_NONE)) {
            lv_label_set_text_sel_start(obj, sel_idx[0]);
            lv_label_set_text_sel_end(obj, sel_idx[1]);
        } else {
            label_setSelNum(obj, *editIndex, disp_str);
        }
    }
    sel_idx[0] = strlen(disp_str);
    sprintf(disp_str, "%s%s", disp_str, logic_str[2]);
    sel_idx[1] = strlen(disp_str);
    if(edit == EDIT_STATE_PROTECT_LOGIC_2) {
        lv_label_set_text_sel_start(obj, sel_idx[0]);
        lv_label_set_text_sel_end(obj, sel_idx[1]);
    }
    sel_idx[0] = strlen(disp_str);
    sprintf(disp_str, "%s%s", disp_str, value_str[2]);
    sel_idx[1] = strlen(disp_str);
    if(edit == EDIT_STATE_PROTECT_VALUE_2) {
        if((editIndex == NULL) || (stopcfg[2].stop == __STOP_NONE)) {
            lv_label_set_text_sel_start(obj, sel_idx[0]);
            lv_label_set_text_sel_end(obj, sel_idx[1]);
        } else {
            label_setSelNum(obj, *editIndex, disp_str);
        }
    }
    //
    lv_label_set_text(obj, disp_str);
    if(edit == EDIT_STATE_DEFAULT) {
        lv_label_set_text_sel_start(obj, LV_LABEL_TEXT_SEL_OFF);
        lv_label_set_text_sel_end(obj, LV_LABEL_TEXT_SEL_OFF);
    }
}

void BatTester_Option_Protect_Value_0_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //
    static uint8_t index_kt = 0;
    float minValue = 0;
    float maxValue = 0;
    uint8_t stepCount = 0;
    const float *pStep = NULL;
    switch(BatTester.stopCfg[0].stop)
    {
        case __STOP_MORE_V:
        case __STOP_LESS_V: {
            minValue = VOL_MIN;
            maxValue = VOL_MAX;
            stepCount = ARRAY_COUNT(BatteryTester_V_step);
            pStep = BatteryTester_V_step;
        }
        break;
        case __STOP_MORE_C:
        case __STOP_LESS_C: {
            minValue = AMP_MIN;
            maxValue = AMP_MAX;
            stepCount = ARRAY_COUNT(BatteryTester_A_step);
            pStep = BatteryTester_A_step;
        }
        break;
        case __STOP_MORE_P:
        case __STOP_LESS_P: {
            minValue = WAT_MIN;
            maxValue = WAT_MAX;
            stepCount = ARRAY_COUNT(BatteryTester_W_step);;
            pStep = BatteryTester_W_step;
        }
        break;
        case __STOP_MORE_DVM:
        case __STOP_LESS_DVM: {
            minValue = VOL_MIN;
            maxValue = VOL_MAX;
            stepCount = ARRAY_COUNT(BatteryTester_V_step);
            pStep = BatteryTester_V_step;
        }
        break;
    }
    //
    if(BatTester.stopCfg[0].stop != __STOP_NONE) {
        NumberInput_Process(7, BatTester.stopCfg[0].value =);
    }
    switch(event)
    {
        case LV_EVENT_KEY: {
            switch(key) {
                case LV_KEY_MORE_VOLT:
                    BatTester.stopCfg[0].stop = __STOP_MORE_V;
                    break;
                case LV_KEY_LESS_VOLT:
                    BatTester.stopCfg[0].stop = __STOP_LESS_V;
                    break;
                case LV_KEY_MORE_CURR:
                    BatTester.stopCfg[0].stop = __STOP_MORE_C;
                    break;
                case LV_KEY_LESS_CURR:
                    BatTester.stopCfg[0].stop = __STOP_LESS_C;
                    break;
                case LV_KEY_MORE_POWER:
                    BatTester.stopCfg[0].stop = __STOP_MORE_P;
                    break;
                case LV_KEY_LESS_POWER:
                    BatTester.stopCfg[0].stop = __STOP_LESS_P;
                    break;
                case LV_KEY_MORE_DVM:
                    BatTester.stopCfg[0].stop = __STOP_MORE_DVM;
                    break;
                case LV_KEY_LESS_DVM:
                    BatTester.stopCfg[0].stop = __STOP_LESS_DVM;
                    break;
                case LV_KEY_NONE_PROTECT:
                    BatTester.stopCfg[0].stop = __STOP_NONE;
                    break;
                case LV_KEY_UP: {
                    if(BatTester.stopCfg[0].stop == __STOP_NONE) { break; }
                    float value = BatTester.stopCfg[0].value;
                    value += pStep[index_kt];
                    value = MIN(value, maxValue);
                    BatTester.stopCfg[0].value = value;
                }
                break;
                case LV_KEY_DOWN: {
                    if(BatTester.stopCfg[0].stop == __STOP_NONE) { break; }
                    float value = BatTester.stopCfg[0].value;
                    value -= pStep[index_kt];
                    value = MAX(value, minValue);
                    BatTester.stopCfg[0].value = value;
                }
                break;
                case LV_KEY_LEFT:
                    if(BatTester.stopCfg[0].stop == __STOP_NONE) { break; }
                    if(index_kt < (stepCount - 1)) { index_kt++; }
                    break;
                case LV_KEY_RIGHT:
                    if(BatTester.stopCfg[0].stop == __STOP_NONE) { break; }
                    if(index_kt > 0) { index_kt--; }
                    break;
                case LV_KEY_ENTER:
                case LV_KEY_ENCODER: {
                    BatTester.stopCfg[0].stop = (++BatTester.stopCfg[0].stop) % (__STOP_MAX + 1);
                }
                break;
                case LV_KEY_ESC:
                    edit_State = EDIT_STATE_DEFAULT;
                    break;
            }
        }
        break;
        case LV_EVENT_DEFOCUSED:
            edit_State = EDIT_STATE_DEFAULT;
            break;
        case LV_EVENT_FOCUSED:
            if(edit_State == EDIT_STATE_PROTECT_VALUE_0) {
                BatTester.stopCfg[0].stop = (++BatTester.stopCfg[0].stop) % (__STOP_MAX + 1);
            }
            edit_State = EDIT_STATE_PROTECT_VALUE_0;
            break;
    }
    float value = BatTester.stopCfg[0].value;
    value = MIN(value, maxValue);
    value = MAX(value, minValue);
    BatTester.stopCfg[0].value = value;
    if(edit_State != EDIT_STATE_PROTECT_VALUE_0) {
        StopSet_RefreshUI(obj, NULL, BatTester.stopCfg, EDIT_STATE_DEFAULT);
    } else {
        StopSet_RefreshUI(obj, &index_kt, BatTester.stopCfg, edit_State);
    }
}

void BatTester_Option_Protect_Logic_1_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //
    switch(event)
    {
        case LV_EVENT_KEY: {
            switch(key)
            {
                case LV_KEY_ENTER:
                case LV_KEY_ENCODER:
                    BatTester.stopCfg[1].logic = (++BatTester.stopCfg[1].logic) % 2;
                    break;
                case LV_KEY_ESC:
                    edit_State = EDIT_STATE_DEFAULT;
                    break;
            }
        }
        break;
        case LV_EVENT_DEFOCUSED:
            edit_State = EDIT_STATE_DEFAULT;
            break;
        case LV_EVENT_FOCUSED: {
            if(edit_State != EDIT_STATE_PROTECT_LOGIC_1) {
                edit_State = EDIT_STATE_PROTECT_LOGIC_1;
            } else {
                BatTester.stopCfg[1].logic = (++BatTester.stopCfg[1].logic) % 2;
            }
        }
        break;
    }
    if(edit_State != EDIT_STATE_PROTECT_LOGIC_1) {
        StopSet_RefreshUI(obj, NULL, BatTester.stopCfg, EDIT_STATE_DEFAULT);
    } else {
        StopSet_RefreshUI(obj, NULL, BatTester.stopCfg, edit_State);
    }
}


void BatTester_Option_Protect_Value_1_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //
    static uint8_t index_kt = 0;
    float minValue = 0;
    float maxValue = 0;
    uint8_t stepCount = 0;
    const float *pStep = NULL;
    switch(BatTester.stopCfg[1].stop)
    {
        case __STOP_MORE_V:
        case __STOP_LESS_V: {
            minValue = VOL_MIN;
            maxValue = VOL_MAX;
            stepCount = ARRAY_COUNT(BatteryTester_V_step);
            pStep = BatteryTester_V_step;
        }
        break;
        case __STOP_MORE_C:
        case __STOP_LESS_C: {
            minValue = AMP_MIN;
            maxValue = AMP_MAX;
            stepCount = ARRAY_COUNT(BatteryTester_A_step);
            pStep = BatteryTester_A_step;
        }
        break;
        case __STOP_MORE_P:
        case __STOP_LESS_P: {
            minValue = WAT_MIN;
            maxValue = WAT_MAX;
            stepCount = ARRAY_COUNT(BatteryTester_W_step);;
            pStep = BatteryTester_W_step;
        }
        break;
        case __STOP_MORE_DVM:
        case __STOP_LESS_DVM: {
            minValue = VOL_MIN;
            maxValue = VOL_MAX;
            stepCount = ARRAY_COUNT(BatteryTester_V_step);
            pStep = BatteryTester_V_step;
        }
        break;
    }
    //
    if(BatTester.stopCfg[1].stop != __STOP_NONE) {
        NumberInput_Process(7, BatTester.stopCfg[1].value =);
    }
    switch(event)
    {
        case LV_EVENT_KEY: {
            switch(key) {
                case LV_KEY_MORE_VOLT:
                    BatTester.stopCfg[1].stop = __STOP_MORE_V;
                    break;
                case LV_KEY_LESS_VOLT:
                    BatTester.stopCfg[1].stop = __STOP_LESS_V;
                    break;
                case LV_KEY_MORE_CURR:
                    BatTester.stopCfg[1].stop = __STOP_MORE_C;
                    break;
                case LV_KEY_LESS_CURR:
                    BatTester.stopCfg[1].stop = __STOP_LESS_C;
                    break;
                case LV_KEY_MORE_POWER:
                    BatTester.stopCfg[1].stop = __STOP_MORE_P;
                    break;
                case LV_KEY_LESS_POWER:
                    BatTester.stopCfg[1].stop = __STOP_LESS_P;
                    break;
                case LV_KEY_MORE_DVM:
                    BatTester.stopCfg[1].stop = __STOP_MORE_DVM;
                    break;
                case LV_KEY_LESS_DVM:
                    BatTester.stopCfg[1].stop = __STOP_LESS_DVM;
                    break;
                case LV_KEY_NONE_PROTECT:
                    BatTester.stopCfg[1].stop = __STOP_NONE;
                    break;
                case LV_KEY_UP: {
                    if(BatTester.stopCfg[1].stop == __STOP_NONE) { break; }
                    float value = BatTester.stopCfg[1].value;
                    value += pStep[index_kt];
                    value = MIN(value, maxValue);
                    BatTester.stopCfg[1].value = value;
                }
                break;
                case LV_KEY_DOWN: {
                    if(BatTester.stopCfg[1].stop == __STOP_NONE) { break; }
                    float value = BatTester.stopCfg[1].value;
                    value -= pStep[index_kt];
                    value = MAX(value, minValue);
                    BatTester.stopCfg[1].value = value;
                }
                break;
                case LV_KEY_LEFT:
                    if(BatTester.stopCfg[1].stop == __STOP_NONE) { break; }
                    if(index_kt < (stepCount - 1)) { index_kt++; }
                    break;
                case LV_KEY_RIGHT:
                    if(BatTester.stopCfg[1].stop == __STOP_NONE) { break; }
                    if(index_kt > 0) { index_kt--; }
                    break;
                case LV_KEY_ENTER:
                case LV_KEY_ENCODER: {
                    BatTester.stopCfg[1].stop = (++BatTester.stopCfg[1].stop) % (__STOP_MAX + 1);
                }
                break;
                case LV_KEY_ESC:
                    edit_State = EDIT_STATE_DEFAULT;
                    break;
            }
        }
        break;
        case LV_EVENT_DEFOCUSED:
            edit_State = EDIT_STATE_DEFAULT;
            break;
        case LV_EVENT_FOCUSED:
            if(edit_State == EDIT_STATE_PROTECT_VALUE_1) {
                BatTester.stopCfg[1].stop = (++BatTester.stopCfg[1].stop) % (__STOP_MAX + 1);
            }
            edit_State = EDIT_STATE_PROTECT_VALUE_1;
            break;
    }
    float value = BatTester.stopCfg[1].value;
    value = MIN(value, maxValue);
    value = MAX(value, minValue);
    BatTester.stopCfg[1].value = value;
    if(edit_State != EDIT_STATE_PROTECT_VALUE_1) {
        StopSet_RefreshUI(obj, NULL, BatTester.stopCfg, EDIT_STATE_DEFAULT);
    } else {
        StopSet_RefreshUI(obj, &index_kt, BatTester.stopCfg, edit_State);
    }
}


void BatTester_Option_Protect_Logic_2_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //
    switch(event)
    {
        case LV_EVENT_KEY: {
            switch(key)
            {
                case LV_KEY_ENTER:
                case LV_KEY_ENCODER:
                    BatTester.stopCfg[2].logic = (++BatTester.stopCfg[2].logic) % 2;
                    break;
                case LV_KEY_ESC:
                    edit_State = EDIT_STATE_DEFAULT;
                    break;
            }
        }
        break;
        case LV_EVENT_DEFOCUSED:
            edit_State = EDIT_STATE_DEFAULT;
            break;
        case LV_EVENT_FOCUSED: {
            if(edit_State != EDIT_STATE_PROTECT_LOGIC_2) {
                edit_State = EDIT_STATE_PROTECT_LOGIC_2;
            } else {
                BatTester.stopCfg[2].logic = (++BatTester.stopCfg[2].logic) % 2;
            }
        }
        break;
    }
    if(edit_State != EDIT_STATE_PROTECT_LOGIC_2) {
        StopSet_RefreshUI(obj, NULL, BatTester.stopCfg, EDIT_STATE_DEFAULT);
    } else {
        StopSet_RefreshUI(obj, NULL, BatTester.stopCfg, edit_State);
    }
}


void BatTester_Option_Protect_Value_2_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //
    static uint8_t index_kt = 0;
    float minValue = 0;
    float maxValue = 0;
    uint8_t stepCount = 0;
    const float *pStep = NULL;
    switch(BatTester.stopCfg[2].stop)
    {
        case __STOP_MORE_V:
        case __STOP_LESS_V: {
            minValue = VOL_MIN;
            maxValue = VOL_MAX;
            stepCount = ARRAY_COUNT(BatteryTester_V_step);
            pStep = BatteryTester_V_step;
        }
        break;
        case __STOP_MORE_C:
        case __STOP_LESS_C: {
            minValue = AMP_MIN;
            maxValue = AMP_MAX;
            stepCount = ARRAY_COUNT(BatteryTester_A_step);
            pStep = BatteryTester_A_step;
        }
        break;
        case __STOP_MORE_P:
        case __STOP_LESS_P: {
            minValue = WAT_MIN;
            maxValue = WAT_MAX;
            stepCount = ARRAY_COUNT(BatteryTester_W_step);;
            pStep = BatteryTester_W_step;
        }
        break;
        case __STOP_MORE_DVM:
        case __STOP_LESS_DVM: {
            minValue = VOL_MIN;
            maxValue = VOL_MAX;
            stepCount = ARRAY_COUNT(BatteryTester_V_step);
            pStep = BatteryTester_V_step;
        }
        break;
    }
    //
    if(BatTester.stopCfg[2].stop != __STOP_NONE) {
        NumberInput_Process(7, BatTester.stopCfg[2].value =);
    }
    switch(event)
    {
        case LV_EVENT_KEY: {
            switch(key) {
                case LV_KEY_MORE_VOLT:
                    BatTester.stopCfg[2].stop = __STOP_MORE_V;
                    break;
                case LV_KEY_LESS_VOLT:
                    BatTester.stopCfg[2].stop = __STOP_LESS_V;
                    break;
                case LV_KEY_MORE_CURR:
                    BatTester.stopCfg[2].stop = __STOP_MORE_C;
                    break;
                case LV_KEY_LESS_CURR:
                    BatTester.stopCfg[2].stop = __STOP_LESS_C;
                    break;
                case LV_KEY_MORE_POWER:
                    BatTester.stopCfg[2].stop = __STOP_MORE_P;
                    break;
                case LV_KEY_LESS_POWER:
                    BatTester.stopCfg[2].stop = __STOP_LESS_P;
                    break;
                case LV_KEY_MORE_DVM:
                    BatTester.stopCfg[2].stop = __STOP_MORE_DVM;
                    break;
                case LV_KEY_LESS_DVM:
                    BatTester.stopCfg[2].stop = __STOP_LESS_DVM;
                    break;
                case LV_KEY_NONE_PROTECT:
                    BatTester.stopCfg[2].stop = __STOP_NONE;
                    break;
                case LV_KEY_UP: {
                    if(BatTester.stopCfg[2].stop == __STOP_NONE) { break; }
                    float value = BatTester.stopCfg[2].value;
                    value += pStep[index_kt];
                    value = MIN(value, maxValue);
                    BatTester.stopCfg[2].value = value;
                }
                break;
                case LV_KEY_DOWN: {
                    if(BatTester.stopCfg[2].stop == __STOP_NONE) { break; }
                    float value = BatTester.stopCfg[2].value;
                    value -= pStep[index_kt];
                    value = MAX(value, minValue);
                    BatTester.stopCfg[2].value = value;
                }
                break;
                case LV_KEY_LEFT:
                    if(BatTester.stopCfg[2].stop == __STOP_NONE) { break; }
                    if(index_kt < (stepCount - 1)) { index_kt++; }
                    break;
                case LV_KEY_RIGHT:
                    if(BatTester.stopCfg[2].stop == __STOP_NONE) { break; }
                    if(index_kt > 0) { index_kt--; }
                    break;
                case LV_KEY_ENTER:
                case LV_KEY_ENCODER: {
                    BatTester.stopCfg[2].stop = (++BatTester.stopCfg[2].stop) % (__STOP_MAX + 1);
                }
                break;
                case LV_KEY_ESC:
                    edit_State = EDIT_STATE_DEFAULT;
                    break;
            }
        }
        break;
        case LV_EVENT_DEFOCUSED:
            edit_State = EDIT_STATE_DEFAULT;
            break;
        case LV_EVENT_FOCUSED:
            if(edit_State == EDIT_STATE_PROTECT_VALUE_2) {
                BatTester.stopCfg[2].stop = (++BatTester.stopCfg[2].stop) % (__STOP_MAX + 1);
            }
            edit_State = EDIT_STATE_PROTECT_VALUE_2;
            break;
    }
    float value = BatTester.stopCfg[2].value;
    value = MIN(value, maxValue);
    value = MAX(value, minValue);
    BatTester.stopCfg[2].value = value;
    if(edit_State != EDIT_STATE_PROTECT_VALUE_2) {
        StopSet_RefreshUI(obj, NULL, BatTester.stopCfg, EDIT_STATE_DEFAULT);
    } else {
        StopSet_RefreshUI(obj, &index_kt, BatTester.stopCfg, edit_State);
    }
}



/*
 * @brief       BatTester_Option_TrigTime_handler(lv_obj_t *obj, lv_event_t event)
 * @details     设置保护延时
 */
void BatTester_Option_TrigTime_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    if(obj == NULL) { return ; }
    static uint8_t edit_index = 0;
    static uint8_t editFlag = 0;
    NumberInput_Process(7, TRIG_TIME_SET_VALUE =);
    float value = TRIG_TIME_SET_VALUE;
    value = MIN(value, TRIG_TIME_MAX);
    value = MAX(value, TRIG_TIME_MIN);
    TRIG_TIME_SET_VALUE = value;
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key) {
                //编码器右转,增大电压
                case LV_KEY_UP: {
                    float temp = TRIG_TIME_SET_VALUE;
                    temp += BatteryTester_kT_step[edit_index];
                    TRIG_TIME_SET_VALUE = MIN(temp, TRIG_TIME_MAX);
                }
                break;
                //编码器左转,降低电压
                case LV_KEY_DOWN: {
                    float temp = TRIG_TIME_SET_VALUE;
                    temp -= BatteryTester_kT_step[edit_index];
                    TRIG_TIME_SET_VALUE = MAX(temp, TRIG_TIME_MIN);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(edit_index > 0) {
                        edit_index--;
                    } else {
                        edit_index = ARRAY_COUNT(BatteryTester_kT_step) - 1;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(edit_index < (ARRAY_COUNT(BatteryTester_kT_step) - 1)) {
                        edit_index++;
                    } else {
                        edit_index = 0;
                    }
                }
                break;
                case LV_KEY_ESC:
                    editFlag = 0;
            }
        }
        break;
        case LV_EVENT_DEFOCUSED:
            editFlag = 0;
            break;
        case LV_EVENT_FOCUSED:
            editFlag = 1;
            break;
    }
    //obj = lv_obj_get_child(obj, NULL);
    static char str[32] = {0};
    sprintf(str, BAT_TESTER_KT_SET_FORM"s", TRIG_TIME_SET_VALUE);
    lv_label_set_text(obj, str);
    if(editFlag != 0) {
        label_setSelNum(obj, edit_index, str);
    } else {
        label_setSelIdx(obj, str, LV_LABEL_TEXT_SEL_OFF);
    }
}


static void startP_RefreshUI(uint8_t *editIndex)
{
    lv_obj_t *obj = ui.BatTester_btn_start_label;
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

void BatTester_Option_editStartP_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return;
    }
    static uint8_t edit_index = 0;
    NumberInput_Process(7, UI_IF_BatTester_Set_Start);
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
                    UI_IF_BatTester_Set_Start(temp);
                }
                break;
                //编码器左转,降低电压
                case LV_KEY_DOWN: {
                    int32_t temp = STARTP_SET_VALUE;
                    temp -= point_step[edit_index];
                    UI_IF_BatTester_Set_Start(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(edit_index > 0)
                    {
                        edit_index--;
                    } else {
                        edit_index = ARRAY_COUNT(point_step) - 1;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(edit_index < (ARRAY_COUNT(point_step) - 1))
                    {
                        edit_index++;
                    } else {
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
        case LV_EVENT_REFRESH:
        case LV_EVENT_FOCUSED: {
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
    lv_obj_t *obj = ui.BatTester_btn_count_label;
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

void BatTester_Option_editCount_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return;
    }
    static uint8_t edit_index = 0;
    NumberInput_Process(7, UI_IF_BatTester_Set_Count);
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
                    UI_IF_BatTester_Set_Count(temp);
                }
                break;
                //编码器左转,降低电压
                case LV_KEY_DOWN: {
                    int32_t temp = COUNT_SET_VALUE;
                    temp -= point_step[edit_index];
                    UI_IF_BatTester_Set_Count(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(edit_index > 0)
                    {
                        edit_index--;
                    } else {
                        edit_index = ARRAY_COUNT(point_step) - 1;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(edit_index < (ARRAY_COUNT(point_step) - 1))
                    {
                        edit_index++;
                    } else {
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
        case LV_EVENT_REFRESH:
        case LV_EVENT_FOCUSED: {
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
    lv_obj_t *obj = ui.BatTester_btn_cycle_label;
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


void BatTester_Option_editCycles_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return;
    }
    static uint8_t edit_index = 0;
    NumberInput_Process(7, UI_IF_BatTester_Set_Cycle);
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
                    UI_IF_BatTester_Set_Cycle(temp);
                }
                break;
                //编码器左转,降低电压
                case LV_KEY_DOWN: {
                    int32_t temp = CYCLES_SET_VALUE;
                    temp -= cycle_step[edit_index];
                    UI_IF_BatTester_Set_Cycle(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(edit_index > 0)
                    {
                        edit_index--;
                    } else {
                        edit_index = ARRAY_COUNT(cycle_step) - 1;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(edit_index < (ARRAY_COUNT(cycle_step) - 1))
                    {
                        edit_index++;
                    } else {
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
        case LV_EVENT_REFRESH:
        case LV_EVENT_FOCUSED: {
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


