#include "MonitorPage.h"
#include "SettingData.h"
#include "Monitor.h"

#include "Monitor_Interface.h"

Tree_Def *tree_monitor;


/* 监视器Monitor */

static void Set_RefreshUI(lv_obj_t *obj, uint8_t *editIndex, const char *name, const char *dispfmt, uint8_t monitor_state, double value)
{
    if(obj == NULL) {
        return ;
    }
    //
    char stringSet[64] = {0};
    char stringValue[16] = {0};
    switch(monitor_state) {
        case MONITOR_NONE:
            sprintf(stringSet, "None(true)");
            break;
        case MONITOR_LESS:
            sprintf(stringValue, dispfmt, value);
            sprintf(stringSet, "%s%s%s", name, "<", stringValue);
            break;
        case MONITOR_MORE:
            sprintf(stringValue, dispfmt, value);
            sprintf(stringSet, "%s%s%s", name, ">", stringValue);
            break;
    }
    lv_label_set_text(obj, stringSet);
    if(editIndex != NULL) {
        if(monitor_state != MONITOR_NONE) {
            label_setSelNum(obj, *editIndex, stringSet);
        } else {
            label_setSelStr(obj, "None(true)", stringSet);
        }
    }
    if(editIndex == NULL) {
        lv_obj_set_state(obj, LV_STATE_DEFAULT);
        lv_label_set_text_sel_start(obj, LV_LABEL_TEXT_SEL_OFF);
        lv_label_set_text_sel_end(obj, LV_LABEL_TEXT_SEL_OFF);
    } else {
        lv_obj_set_state(obj, LV_STATE_FOCUSED);
    }
}


/*!
 * @brief   void Monitor_Vol_Protect_handler(lv_obj_t *obj, lv_event_t event)
 *          保护电压设置
 */
void Monitor_Vol_Protect_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return ;
    }
    static uint8_t editIdx = 0;
    float temp = systemInfo.monitor.vol;
    if(systemInfo.monitor.vol_monitor != MONITOR_NONE) {
        NumberInput_Process(7, systemInfo.monitor.vol =);
    }
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                case LV_KEY_ENTER:
                case LV_KEY_ENCODER: {
                    if(systemInfo.monitor.vol_monitor < MONITOR_MAX) {
                        systemInfo.monitor.vol_monitor++;
                    } else {
                        systemInfo.monitor.vol_monitor = MONITOR_MIN;
                    }
                    UI_IF_Monitor_Set_Vol(systemInfo.monitor.vol_monitor, systemInfo.monitor.vol);
                }
                break;
                case LV_KEY_UP: {
                    if(systemInfo.monitor.vol_monitor == MONITOR_NONE) {
                        break;
                    }
                    temp += V_step[editIdx];
                    systemInfo.monitor.vol = temp;
                    UI_IF_Monitor_Set_Vol(systemInfo.monitor.vol_monitor, systemInfo.monitor.vol);
                }
                break;
                case LV_KEY_DOWN: {
                    if(systemInfo.monitor.vol_monitor == MONITOR_NONE) {
                        break;
                    }
                    temp -= V_step[editIdx];
                    systemInfo.monitor.vol = temp;
                    UI_IF_Monitor_Set_Vol(systemInfo.monitor.vol_monitor, systemInfo.monitor.vol);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(systemInfo.monitor.vol_monitor == MONITOR_NONE) {
                        break;
                    }
                    if(editIdx > 0)
                    {
                        editIdx--;
                    }
                    else
                    {
                        editIdx = sizeof(V_step) / sizeof(V_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(systemInfo.monitor.vol_monitor == MONITOR_NONE) {
                        break;
                    }
                    if(editIdx < (sizeof(V_step) / sizeof(V_step[0]) - 1))
                    {
                        editIdx++;
                    }
                    else
                    {
                        editIdx = 0;
                    }
                }
                break;
            }
            if(key != LV_KEY_ESC) {
                Set_RefreshUI(obj, &editIdx, "Vo", VOL_SET_FORM"V", systemInfo.monitor.vol_monitor, systemInfo.monitor.vol);
            } else {
                Set_RefreshUI(obj, NULL, "Vo", VOL_SET_FORM"V", systemInfo.monitor.vol_monitor, systemInfo.monitor.vol);
                return;
            }
        }
        break;
        case LV_EVENT_REFRESH: {
            BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_Monitor_Vol));
            Set_RefreshUI(obj, NULL, "Vo", VOL_SET_FORM"V", systemInfo.monitor.vol_monitor, systemInfo.monitor.vol);
        }
        return;
        case LV_EVENT_CLICKED: {
            editIdx = 0;
            eeprom_Monitor_RequestSave(0);
        }
        break;
    }
    if(systemInfo.monitor.vol > VOL_MAX) {
        systemInfo.monitor.vol = VOL_MAX;
        IF_MsgBox_Tips_Mult(&mStr_OutSet_MaxVol);
    } else
        if(systemInfo.monitor.vol < VOL_MIN) {
            systemInfo.monitor.vol = VOL_MIN;
        }
    Set_RefreshUI(obj, &editIdx, "Vo", VOL_SET_FORM"V", systemInfo.monitor.vol_monitor, systemInfo.monitor.vol);
}

/*!
 * @brief   void Monitor_Amp_Protect_handler(lv_obj_t *obj, lv_event_t event)
 *          保护电流设置
 */
void Monitor_Amp_Protect_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return ;
    }
    static uint8_t editIdx = 0;
    float temp = systemInfo.monitor.amp;
    if(systemInfo.monitor.amp_monitor != MONITOR_NONE) {
        NumberInput_Process(7, systemInfo.monitor.amp =);
    }
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                case LV_KEY_ENTER:
                case LV_KEY_ENCODER: {
                    if(systemInfo.monitor.amp_monitor < MONITOR_MAX) {
                        systemInfo.monitor.amp_monitor++;
                    } else {
                        systemInfo.monitor.amp_monitor = MONITOR_MIN;
                    }
                    UI_IF_Monitor_Set_Amp(systemInfo.monitor.amp_monitor, systemInfo.monitor.amp);
                }
                break;
                case LV_KEY_UP: {
                    if(systemInfo.monitor.amp_monitor == MONITOR_NONE) {
                        break;
                    }
                    temp += A_step[editIdx];
                    systemInfo.monitor.amp = temp;
                    UI_IF_Monitor_Set_Amp(systemInfo.monitor.amp_monitor, systemInfo.monitor.amp);
                }
                break;
                case LV_KEY_DOWN: {
                    if(systemInfo.monitor.amp_monitor == MONITOR_NONE) {
                        break;
                    }
                    temp -= A_step[editIdx];
                    systemInfo.monitor.amp = temp;
                    UI_IF_Monitor_Set_Amp(systemInfo.monitor.amp_monitor, systemInfo.monitor.amp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(systemInfo.monitor.amp_monitor == MONITOR_NONE) {
                        break;
                    }
                    if(editIdx > 0)
                    {
                        editIdx--;
                    }
                    else
                    {
                        editIdx = sizeof(A_step) / sizeof(A_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(systemInfo.monitor.amp_monitor == MONITOR_NONE) {
                        break;
                    }
                    if(editIdx < (sizeof(A_step) / sizeof(A_step[0]) - 1))
                    {
                        editIdx++;
                    }
                    else
                    {
                        editIdx = 0;
                    }
                }
                break;
            }
            if(key != LV_KEY_ESC) {
                Set_RefreshUI(obj, &editIdx, "Io", AMP_SET_FORM"A", systemInfo.monitor.amp_monitor, systemInfo.monitor.amp);
            } else {
                Set_RefreshUI(obj, NULL, "Io", AMP_SET_FORM"A", systemInfo.monitor.amp_monitor, systemInfo.monitor.amp);
                return;
            }
        }
        break;
        case LV_EVENT_REFRESH: {
            BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_Monitor_Amp));
            Set_RefreshUI(obj, NULL, "Io", AMP_SET_FORM"A", systemInfo.monitor.amp_monitor, systemInfo.monitor.amp);
        }
        return;
        case LV_EVENT_CLICKED: {
            editIdx = 0;
            eeprom_Monitor_RequestSave(0);
        }
        break;
    }
    if(systemInfo.monitor.amp > AMP_MAX) {
        systemInfo.monitor.amp = AMP_MAX;
        IF_MsgBox_Tips_Mult(&mStr_OutSet_MaxAmp);
    } else
        if(systemInfo.monitor.amp < AMP_MIN) {
            systemInfo.monitor.amp = AMP_MIN;
        }
    Set_RefreshUI(obj, &editIdx, "Io", AMP_SET_FORM"A", systemInfo.monitor.amp_monitor, systemInfo.monitor.amp);
}

/*!
 * @brief   void Monitor_Wat_Protect_handler(lv_obj_t *obj, lv_event_t event)
 *          保护功率设置
 */
void Monitor_Wat_Protect_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return ;
    }
    static uint8_t editIdx = 0;
    float temp = systemInfo.monitor.wat;
    if(systemInfo.monitor.wat_monitor != MONITOR_NONE) {
        NumberInput_Process(7, systemInfo.monitor.wat =);
    }
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                case LV_KEY_ENTER:
                case LV_KEY_ENCODER: {
                    if(systemInfo.monitor.wat_monitor < MONITOR_MAX) {
                        systemInfo.monitor.wat_monitor++;
                    } else {
                        systemInfo.monitor.wat_monitor = MONITOR_MIN;
                    }
                    UI_IF_Monitor_Set_Wat(systemInfo.monitor.wat_monitor, systemInfo.monitor.wat);
                }
                break;
                case LV_KEY_UP: {
                    if(systemInfo.monitor.wat_monitor == MONITOR_NONE) {
                        break;
                    }
                    temp += W_step[editIdx];
                    systemInfo.monitor.wat = temp;
                    UI_IF_Monitor_Set_Wat(systemInfo.monitor.wat_monitor, systemInfo.monitor.wat);
                }
                break;
                case LV_KEY_DOWN: {
                    if(systemInfo.monitor.wat_monitor == MONITOR_NONE) {
                        break;
                    }
                    temp -= W_step[editIdx];
                    systemInfo.monitor.wat = temp;
                    UI_IF_Monitor_Set_Wat(systemInfo.monitor.wat_monitor, systemInfo.monitor.wat);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(systemInfo.monitor.wat_monitor == MONITOR_NONE) {
                        break;
                    }
                    if(editIdx > 0)
                    {
                        editIdx--;
                    }
                    else
                    {
                        editIdx = sizeof(W_step) / sizeof(W_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(systemInfo.monitor.wat_monitor == MONITOR_NONE) {
                        break;
                    }
                    if(editIdx < (sizeof(W_step) / sizeof(W_step[0]) - 1))
                    {
                        editIdx++;
                    }
                    else
                    {
                        editIdx = 0;
                    }
                }
                break;
            }
            if(key != LV_KEY_ESC) {
                Set_RefreshUI(obj, &editIdx, "Po", WAT_SET_FORM"W", systemInfo.monitor.wat_monitor, systemInfo.monitor.wat);
            } else {
                Set_RefreshUI(obj, NULL, "Po", WAT_SET_FORM"W", systemInfo.monitor.wat_monitor, systemInfo.monitor.wat);
                return;
            }
        }
        break;
        case LV_EVENT_REFRESH: {
            BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_Monitor_Wat));
            Set_RefreshUI(obj, NULL, "Po", WAT_SET_FORM"W", systemInfo.monitor.wat_monitor, systemInfo.monitor.wat);
        }
        return;
        case LV_EVENT_CLICKED: {
            editIdx = 0;
            eeprom_Monitor_RequestSave(0);
        }
        break;
    }
    if(systemInfo.monitor.wat > WAT_MAX) {
        systemInfo.monitor.wat = WAT_MAX;
        IF_MsgBox_Tips_Mult(&mStr_OutSet_MaxWat);
    } else
        if(systemInfo.monitor.wat < WAT_MIN) {
            systemInfo.monitor.wat = WAT_MIN;
        }
    Set_RefreshUI(obj, &editIdx, "Po", WAT_SET_FORM"W", systemInfo.monitor.wat_monitor, systemInfo.monitor.wat);
}

/*!
 * @brief   void Monitor_Dvm_Protect_handler(lv_obj_t *obj, lv_event_t event)
 *          保护DVM表设置
 */
void Monitor_Dvm_Protect_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return ;
    }
    static uint8_t editIdx = 0;
    float temp = systemInfo.monitor.dvm;
    if(systemInfo.monitor.dvm_monitor != MONITOR_NONE) {
        NumberInput_Process(7, systemInfo.monitor.dvm =);
    }
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                case LV_KEY_ENTER:
                case LV_KEY_ENCODER: {
                    if(systemInfo.monitor.dvm_monitor < MONITOR_MAX) {
                        systemInfo.monitor.dvm_monitor++;
                    } else {
                        systemInfo.monitor.dvm_monitor = MONITOR_MIN;
                    }
                    UI_IF_Monitor_Set_Dvm(systemInfo.monitor.dvm_monitor, systemInfo.monitor.dvm);
                }
                break;
                case LV_KEY_UP: {
                    if(systemInfo.monitor.dvm_monitor == MONITOR_NONE) {
                        break;
                    }
                    temp += V_step[editIdx];
                    systemInfo.monitor.dvm = temp;
                    UI_IF_Monitor_Set_Dvm(systemInfo.monitor.dvm_monitor, systemInfo.monitor.dvm);
                }
                break;
                case LV_KEY_DOWN: {
                    if(systemInfo.monitor.dvm_monitor == MONITOR_NONE) {
                        break;
                    }
                    temp -= V_step[editIdx];
                    systemInfo.monitor.dvm = temp;
                    UI_IF_Monitor_Set_Dvm(systemInfo.monitor.dvm_monitor, systemInfo.monitor.dvm);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(systemInfo.monitor.dvm_monitor == MONITOR_NONE) {
                        break;
                    }
                    if(editIdx > 0)
                    {
                        editIdx--;
                    }
                    else
                    {
                        editIdx = sizeof(V_step) / sizeof(V_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(systemInfo.monitor.dvm_monitor == MONITOR_NONE) {
                        break;
                    }
                    if(editIdx < (sizeof(V_step) / sizeof(V_step[0]) - 1))
                    {
                        editIdx++;
                    }
                    else
                    {
                        editIdx = 0;
                    }
                }
                break;
            }
            if(key != LV_KEY_ESC) {
                Set_RefreshUI(obj, &editIdx, "DVM", VOL_SET_FORM"V", systemInfo.monitor.dvm_monitor, systemInfo.monitor.dvm);
            } else {
                Set_RefreshUI(obj, NULL, "DVM", VOL_SET_FORM"V", systemInfo.monitor.dvm_monitor, systemInfo.monitor.dvm);
                return;
            }
        }
        break;
        case LV_EVENT_REFRESH: {
            BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_Monitor_Dvm));
            Set_RefreshUI(obj, NULL, "DVM", VOL_SET_FORM"V", systemInfo.monitor.dvm_monitor, systemInfo.monitor.dvm);
        }
        return;
        case LV_EVENT_CLICKED: {
            editIdx = 0;
            eeprom_Monitor_RequestSave(0);
        }
        break;
    }
    if(systemInfo.monitor.dvm > DVM_MAX) {
        systemInfo.monitor.dvm = DVM_MAX;
        IF_MsgBox_Tips_Mult(&mStr_OutSet_MaxVol);
    } else
        if(systemInfo.monitor.dvm < DVM_MIN) {
            systemInfo.monitor.dvm = DVM_MIN;
        }
    Set_RefreshUI(obj, &editIdx, "DVM", VOL_SET_FORM"V", systemInfo.monitor.dvm_monitor, systemInfo.monitor.dvm);
}




/*!
 * @brief   void Monitor_Logic_handler(lv_obj_t *obj, lv_event_t event)
 *          保护逻辑设置
 */
enum {
    LOGIC_EDIT_V_I = 0,
    LOGIC_EDIT_I_W = 1,
    LOGIC_EDIT_W_DVM = 2,

    LOGIC_EDIT_MIN = LOGIC_EDIT_V_I,
    LOGIC_EDIT_MAX = LOGIC_EDIT_W_DVM,
};

void __Logic_Refresh(lv_obj_t *obj, uint8_t *index)
{
    const char *logic_ch[3]  = {0};
    logic_ch[0] = (systemInfo.monitor.logic[0] == LOGIC_AND) ? "&" : "|";
    logic_ch[1] = (systemInfo.monitor.logic[1] == LOGIC_AND) ? "&" : "|";
    logic_ch[2] = (systemInfo.monitor.logic[2] == LOGIC_AND) ? "&" : "|";
    char buffer[32] = {0};
    sprintf(buffer, "Vo %s Io %s Po %s Vdvm", logic_ch[0], logic_ch[1], logic_ch[2]);
    lv_label_set_text(obj, buffer);
    if(index == NULL) {
        lv_label_set_text_sel_start(obj, LV_LABEL_TEXT_SEL_OFF);
        lv_label_set_text_sel_end(obj, LV_LABEL_TEXT_SEL_OFF);
    } else {
        char sel_str[16] = "";
        switch(*index) {
            case LOGIC_EDIT_V_I:
                sprintf(sel_str, "Vo %s Io", logic_ch[0]);
                break;
            case LOGIC_EDIT_I_W:
                sprintf(sel_str, "Io %s Po", logic_ch[1]);
                break;
            case LOGIC_EDIT_W_DVM:
                sprintf(sel_str, "Po %s Vdvm", logic_ch[2]);
                break;
        }
        label_setSelStr(obj, sel_str, buffer);
    }
}

void Monitor_Logic_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return ;
    }
    static uint8_t editIdx = 0;
    static uint8_t editFlag = 0;
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                case LV_KEY_RIGHT: {
                    if(editIdx < LOGIC_EDIT_MAX) {
                        editIdx++;
                    }
                    else {
                        editIdx = LOGIC_EDIT_MIN;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(editIdx > LOGIC_EDIT_MIN) {
                        editIdx--;
                    }
                    else {
                        editIdx = LOGIC_EDIT_MAX;
                    }
                }
                break;
                case LV_KEY_UP:
                case LV_KEY_DOWN:
                case LV_KEY_ENTER:
                case LV_KEY_ENCODER: {
                    if(systemInfo.monitor.logic[editIdx] < LOGIC_MAX) {
                        systemInfo.monitor.logic[editIdx]++;
                    } else {
                        systemInfo.monitor.logic[editIdx] = LOGIC_MIN;
                    }
                    UI_IF_Monitor_Set_Logic(editIdx, systemInfo.monitor.logic[editIdx]);
                }
                break;
                case LV_KEY_RETURN:
                case LV_KEY_ESC:
                    editFlag = 0;
                    break;
            }
        }
        break;
        case LV_EVENT_CLICKED: {
            editFlag = 1;
            editIdx = LOGIC_EDIT_V_I;
        }
        break;
    }
    //刷新
    if(editFlag != 0) {
        __Logic_Refresh(obj, &editIdx);
    } else {
        __Logic_Refresh(obj, NULL);
    }
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_Monitor_Logic));
}




typedef struct {
    uint16_t value;
    const MultStr_Def *multStr;
} valueString_Def;

static const char *valueStr_GetStr(uint16_t value, const valueString_Def *valueStr)
{
    for(uint8_t i = 0; valueStr[i].multStr != NULL; ++i) {
        if(valueStr[i].value == value) {
            return MultStr_GetS(valueStr[i].multStr);
        }
    }
    return "";
}
void Monitor_Sensitivity_handler(lv_obj_t *obj, lv_event_t event)
{
    static uint8_t editFlag = 0;
    const valueString_Def valueStr[] = {
        {SENSITIVITY_LOW, &mStr_Monitor_Sensitivity_Low},
        {SENSITIVITY_MID, &mStr_Monitor_Sensitivity_Mid},
        {SENSITIVITY_HIGH, &mStr_Monitor_Sensitivity_High},
        {0},
    };
    uint8_t sensitivity = systemInfo.monitor.sensitivity;
    switch(event) {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key) {
                case LV_KEY_UP:
                case LV_KEY_DOWN: {
                    sensitivity = (sensitivity + 1) % (SENSITIVITY_MAX + 1);
                    //刷新
                    systemInfo.monitor.sensitivity = sensitivity;
                    UI_IF_Monitor_Set_Sensitivity(sensitivity);
                }
                break;
                case LV_KEY_ESC:
                    editFlag = 0;
                    break;
            }
        }
        break;
        case LV_EVENT_CLICKED:
            if(editFlag == 1) {
                sensitivity = (sensitivity + 1) % (SENSITIVITY_MAX + 1);
                //刷新
                systemInfo.monitor.sensitivity = sensitivity;
                UI_IF_Monitor_Set_Sensitivity(sensitivity);
            }
            editFlag = 1;
            break;
    }
    const char *str = valueStr_GetStr(systemInfo.monitor.sensitivity, valueStr);
    lv_label_set_text_static(obj, str);
    lv_obj_t *button = lv_obj_get_parent(obj);
    if(editFlag != 0) {
        label_setSelStr(obj, str, str);
    } else {
        lv_label_set_text_sel_start(obj, 0);
        lv_label_set_text_sel_end(obj, 0);
    }
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_Monitor_Sensitivity));
}

/*!
 * @brief   void Monitor_PowerOFF_handler(lv_obj_t *obj, lv_event_t event)
 *          动作
 */
void Monitor_PowerOFF_handler(lv_obj_t *obj, lv_event_t event)
{
    static uint8_t editFlag = 0;
    const valueString_Def valueStr[] = {
        {0, &mStr_NO},
        {1, &mStr_YES},
        {0},
    };
    uint8_t powerOFF = systemInfo.monitor.powerOFF;
    switch(event) {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key) {
                case LV_KEY_UP:
                case LV_KEY_DOWN: {
                    powerOFF = !powerOFF;
                    //刷新
                    systemInfo.monitor.powerOFF = powerOFF;
                    UI_IF_Monitor_Set_PowerOFF(powerOFF);
                }
                break;
                case LV_KEY_ESC:
                    editFlag = 0;
                    break;
            }
        }
        break;
        case LV_EVENT_CLICKED:
            if(editFlag == 1) {
                powerOFF = !powerOFF;
                //刷新
                systemInfo.monitor.powerOFF = powerOFF;
                UI_IF_Monitor_Set_PowerOFF(powerOFF);
            }
            editFlag = 1;
            break;
    }
    const char *str = valueStr_GetStr(systemInfo.monitor.powerOFF, valueStr);
    lv_label_set_text_static(obj, str);
    lv_obj_t *button = lv_obj_get_parent(obj);
    if(editFlag != 0) {
        label_setSelStr(obj, str, str);
    } else {
        lv_label_set_text_sel_start(obj, 0);
        lv_label_set_text_sel_end(obj, 0);
    }
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_Monitor_PowerOFF));
}

/*!
 * @brief   void Monitor_Beep_handler(lv_obj_t *obj, lv_event_t event)
 *          提示音
 */
void Monitor_Beep_handler(lv_obj_t *obj, lv_event_t event)
{
    static uint8_t editFlag = 0;
    const valueString_Def valueStr[] = {
        {0, &mStr_OFF},
        {1, &mStr_ON},
        {0},
    };
    uint8_t beep = systemInfo.monitor.beep;
    switch(event) {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key) {
                case LV_KEY_UP:
                case LV_KEY_DOWN: {
                    beep = !beep;
                    //刷新
                    systemInfo.monitor.beep = beep;
                    UI_IF_Monitor_Set_Beep(beep);
                }
                break;
                case LV_KEY_ESC:
                    editFlag = 0;
                    break;
            }
        }
        break;
        case LV_EVENT_CLICKED:
            if(editFlag == 1) {
                beep = !beep;
                //刷新
                systemInfo.monitor.beep = beep;
                UI_IF_Monitor_Set_Beep(beep);
            }
            editFlag = 1;
            break;
    }
    const char *str = valueStr_GetStr(systemInfo.monitor.beep, valueStr);
    lv_label_set_text_static(obj, str);
    lv_obj_t *button = lv_obj_get_parent(obj);
    if(editFlag != 0) {
        label_setSelStr(obj, str, str);
    } else {
        lv_label_set_text_sel_start(obj, 0);
        lv_label_set_text_sel_end(obj, 0);
    }
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_Monitor_Beeper));
}

/*!
 * @brief   void Monitor_Tips_handler(lv_obj_t *obj, lv_event_t event)
 *          提示框
 */
void Monitor_Tips_handler(lv_obj_t *obj, lv_event_t event)
{
    static uint8_t editFlag = 0;
    const valueString_Def valueStr[] = {
        {0, &mStr_OFF},
        {1, &mStr_ON},
        {0},
    };
    uint8_t tips = systemInfo.monitor.tips;
    switch(event) {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key) {
                case LV_KEY_UP:
                case LV_KEY_DOWN: {
                    tips = !tips;
                    systemInfo.monitor.tips = tips;
                    UI_IF_Monitor_Set_Tips(tips);
                }
                break;
                case LV_KEY_ESC:
                    editFlag = 0;
                    break;
            }
        }
        break;
        case LV_EVENT_CLICKED:
            if(editFlag == 1) {
                tips = !tips;
                systemInfo.monitor.tips = tips;
                UI_IF_Monitor_Set_Tips(tips);
            }
            editFlag = 1;
            break;
    }
    const char *str = valueStr_GetStr(systemInfo.monitor.tips, valueStr);
    lv_label_set_text_static(obj, str);
    lv_obj_t *button = lv_obj_get_parent(obj);
    if(editFlag != 0) {
        label_setSelStr(obj, str, str);
    } else {
        lv_label_set_text_sel_start(obj, 0);
        lv_label_set_text_sel_end(obj, 0);
    }
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_Monitor_Tips));
}



/*
 * @brief       void Monitor_handler(lv_obj_t *obj, lv_event_t event)
 * @details
 */
static void __button_Refresh(void);
void Monitor_handler(lv_obj_t *obj, lv_event_t event)
{
    switch(event) {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key) {
                case LV_KEY_ON:
                    systemInfo.monitor.enable = 1;
                    UI_IF_Monitor_Set_ON_OFF(systemInfo.monitor.enable);
                    __button_Refresh();
                    break;
                case LV_KEY_OFF:
                    systemInfo.monitor.enable = 0;
                    UI_IF_Monitor_Set_ON_OFF(systemInfo.monitor.enable);
                    __button_Refresh();
                    break;
            }
        }
        break;
        case  LV_EVENT_REFRESH: {
            UI_IF_Monitor_Set_Sensitivity(systemInfo.monitor.sensitivity);
            UI_IF_Monitor_Set_PowerOFF(systemInfo.monitor.powerOFF);
            UI_IF_Monitor_Set_Beep(systemInfo.monitor.beep);
            UI_IF_Monitor_Set_Tips(systemInfo.monitor.tips);
            UI_IF_Monitor_Set_ON_OFF(systemInfo.monitor.enable);
        }
        break;
    }
}



static void __button_Refresh(void)
{
    static struct BtnInfo_Def btn_Monitor_Vol = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.Monitor_btn_LogicV_label,
        .evencb = Monitor_Vol_Protect_handler,
        .multStr = &mStr_Monitor_Vol,
    };
    static struct BtnInfo_Def btn_Monitor_Amp = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.Monitor_btn_LogicA_label,
        .evencb = Monitor_Amp_Protect_handler,
        .multStr = &mStr_Monitor_Amp,
    };
    static struct BtnInfo_Def btn_Monitor_Wat = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.Monitor_btn_LogicW_label,
        .evencb = Monitor_Wat_Protect_handler,
        .multStr = &mStr_Monitor_Wat,
    };
    static struct BtnInfo_Def btn_Monitor_Dvm = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.Monitor_btn_LogicDvm_label,
        .evencb = Monitor_Dvm_Protect_handler,
        .multStr = &mStr_Monitor_Dvm,
    };
    //
    static struct BtnInfo_Def btn_Monitor_Logic = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.Monitor_btn_Logic_label,
        .evencb = Monitor_Logic_handler,
        .multStr = &mStr_Monitor_Logic,
    };
    static struct BtnInfo_Def btn_Monitor_Sensitivity = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.Monitor_btn_sensitivity_label,
        .evencb = Monitor_Sensitivity_handler,
        .multStr = &mStr_Monitor_Sensitivity,
    };
    static struct BtnInfo_Def btn_Monitor_PowerOFF = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.Monitor_btn_PowerOFF_label,
        .evencb = Monitor_PowerOFF_handler,
        .multStr = &mStr_Monitor_PowerOFF,
    };
    static struct BtnInfo_Def btn_Monitor_Beep = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.Monitor_btn_beep_label,
        .evencb = Monitor_Beep_handler,
        .multStr = &mStr_Monitor_Beeper,
    };
    static struct BtnInfo_Def btn_Monitor_Tips = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.Monitor_btn_Tips_label,
        .evencb = Monitor_Tips_handler,
        .multStr = &mStr_Monitor_Tips,
    };
    if(tree_monitor->child == NULL) {
        //        Tree_Delete(tree_monitor, tree_monitor->child);
        Tree_AddNode(tree_monitor, &btn_on);
        Tree_AddNode(tree_monitor, &btn_Monitor_Vol);
        Tree_AddNode(tree_monitor, &btn_Monitor_Amp);
        Tree_AddNode(tree_monitor, &btn_Monitor_Wat);
        Tree_AddNode(tree_monitor, &btn_Monitor_Dvm);
        Tree_AddNode(tree_monitor, &btn_Monitor_Logic);
        Tree_AddNode(tree_monitor, &btn_Monitor_Sensitivity);
        Tree_AddNode(tree_monitor, &btn_Monitor_PowerOFF);
        Tree_AddNode(tree_monitor, &btn_Monitor_Beep);
        Tree_AddNode(tree_monitor, &btn_Monitor_Tips);
    }
    if(systemInfo.monitor.enable == 0) {
        //        Tree_AddNode(tree_monitor, &btn_on);
        Tree_Btnm_Replace(tree_monitor, &btn_off, &btn_on);
        //        btn_Monitor_Vol.noVisable = 1;
        //        btn_Monitor_Amp.noVisable = 1;
        //        btn_Monitor_Wat.noVisable = 1;
        //        btn_Monitor_Dvm.noVisable = 1;
        //        btn_Monitor_Logic.noVisable = 1;
        //        btn_Monitor_Sensitivity.noVisable = 1;
        //        btn_Monitor_PowerOFF.noVisable = 1;
        //        btn_Monitor_Beep.noVisable = 1;
        //        btn_Monitor_Tips.noVisable = 1;
    } else {
        //        Tree_AddNode(tree_monitor, &btn_off);
        Tree_Btnm_Replace(tree_monitor, &btn_on, &btn_off);
        //        btn_Monitor_Vol.noVisable = 0;
        //        btn_Monitor_Amp.noVisable = 0;
        //        btn_Monitor_Wat.noVisable = 0;
        //        btn_Monitor_Dvm.noVisable = 0;
        //        btn_Monitor_Logic.noVisable = 0;
        //        btn_Monitor_Sensitivity.noVisable = 0;
        //        btn_Monitor_PowerOFF.noVisable = 0;
        //        btn_Monitor_Beep.noVisable = 0;
        //        btn_Monitor_Tips.noVisable = 0;
    }
    extern Tree_Def *Tree_UI_Set_EventCb(Tree_Def * tree);
    Tree_UI_Set_EventCb(tree_monitor);
    lv_event_send_refresh_recursive(ui.Monitor_cont);
    Tree_Btnm_Load(tree_monitor);
}



static void __Param_Btn_Style_Load(lv_obj_t *label)
{
    lv_obj_t *button = lv_obj_get_parent(label);
    if(button == NULL) {
        return ;
    }
    uint16_t button_width = lv_obj_get_width(button) - 10;
    uint16_t button_height = lv_obj_get_height(button);
    lv_label_set_long_mode(label, LV_LABEL_LONG_BREAK);
    lv_obj_set_size(label, button_width, button_height);
    lv_obj_align(label, button, LV_ALIGN_IN_RIGHT_MID, -10, 0);
    lv_label_set_align(label, LV_LABEL_ALIGN_RIGHT);
    extern lv_font_t MultFont_16;
    //标签
    lv_style_t *plabelStyle = lv_obj_get_local_style(label, LV_LABEL_PART_MAIN);
    static lv_style_t labelStyle = {0};
    lv_style_init(&labelStyle);
    lv_obj_clean_style_list(label, LV_LABEL_PART_MAIN);
    lv_style_set_text_letter_space(&labelStyle, LV_STATE_DEFAULT, 1);
    lv_style_set_text_letter_space(&labelStyle, LV_STATE_FOCUSED, 1);
    lv_style_set_text_font(&labelStyle, LV_STATE_DEFAULT, &MultFont_16);
    lv_style_set_text_font(&labelStyle, LV_STATE_FOCUSED, &MultFont_16);
    lv_style_set_text_color(&labelStyle, LV_STATE_DEFAULT, lv_color_make(255, 255, 255));
    lv_style_set_text_color(&labelStyle, LV_STATE_FOCUSED, lv_color_make(255, 255, 255));
    lv_style_set_text_sel_color(&labelStyle, LV_STATE_FOCUSED, lv_color_make(255, 255, 255));
    lv_style_set_text_sel_color(&labelStyle, LV_STATE_DEFAULT, lv_color_make(0, 255, 255));
    lv_style_set_text_sel_bg_color(&labelStyle, LV_STATE_FOCUSED, lv_color_make(0, 0, 255));
    lv_style_set_text_sel_bg_color(&labelStyle, LV_STATE_DEFAULT, lv_color_make(0, 0, 0));
    lv_obj_add_style(label, LV_LABEL_PART_MAIN, &labelStyle);
    //按键
    lv_style_t *pbtnStyle = lv_obj_get_local_style(button, LV_BTN_PART_MAIN);
    static lv_style_t btnStyle = {0};
    lv_style_init(&btnStyle);
    lv_obj_clean_style_list(button, LV_LABEL_PART_MAIN);
    lv_style_set_value_letter_space(&btnStyle, LV_STATE_DEFAULT, 2);
    lv_style_set_value_letter_space(&btnStyle, LV_STATE_FOCUSED, 2);
    lv_style_set_value_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(0, 255, 255));
    lv_style_set_value_color(&btnStyle, LV_STATE_FOCUSED, lv_color_make(0, 255, 255));
    lv_style_set_value_font(&btnStyle, LV_STATE_DEFAULT, &MultFont_16);
    lv_style_set_value_font(&btnStyle, LV_STATE_FOCUSED, &MultFont_16);
    lv_style_set_bg_opa(&btnStyle, LV_STATE_DEFAULT, 0x10);
    lv_style_set_bg_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_border_width(&btnStyle, LV_STATE_DEFAULT, 1);
    lv_style_set_border_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
    lv_style_set_bg_opa(&btnStyle, LV_STATE_FOCUSED, 0x50);
    lv_style_set_bg_color(&btnStyle, LV_STATE_FOCUSED, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_border_width(&btnStyle, LV_STATE_FOCUSED, 0);
    lv_style_set_border_color(&btnStyle, LV_STATE_FOCUSED, lv_color_make(0x50, 0x50, 0x50));
    lv_style_set_radius(&btnStyle, LV_STATE_DEFAULT, 0);
    lv_style_set_radius(&btnStyle, LV_STATE_FOCUSED, 0);
    lv_style_set_value_align(&btnStyle, LV_STATE_DEFAULT, LV_ALIGN_IN_LEFT_MID);
    lv_style_set_value_align(&btnStyle, LV_STATE_FOCUSED, LV_ALIGN_IN_LEFT_MID);
    lv_style_set_value_ofs_x(&btnStyle, LV_STATE_DEFAULT, 5);
    lv_style_set_value_ofs_x(&btnStyle, LV_STATE_FOCUSED, 5);
    lv_style_set_value_opa(&btnStyle, LV_STATE_DEFAULT, 255);
    lv_style_set_value_opa(&btnStyle, LV_STATE_FOCUSED, 255);
    lv_obj_add_style(button, LV_BTN_PART_MAIN, &btnStyle);
    //重绘
    lv_obj_invalidate(label);
    lv_obj_invalidate(button);
}

void MonitorPage_GroupCreate(void)
{
    //加载UI
    setup_scr_Monitor(&ui);
    lv_obj_set_parent(ui.Monitor_cont, ui.Back_cont_back);
    extern lv_font_t MultFont_16;
    lv_obj_set_style_local_text_font(ui.Monitor_btn_LogicTitle_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_16);
    lv_obj_set_style_local_text_font(ui.Monitor_btn_TriggerTitle_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_16);
    __Param_Btn_Style_Load(ui.Monitor_btn_LogicV_label);
    __Param_Btn_Style_Load(ui.Monitor_btn_LogicA_label);
    __Param_Btn_Style_Load(ui.Monitor_btn_LogicW_label);
    __Param_Btn_Style_Load(ui.Monitor_btn_LogicDvm_label);
    __Param_Btn_Style_Load(ui.Monitor_btn_Logic_label);
    __Param_Btn_Style_Load(ui.Monitor_btn_sensitivity_label);
    __Param_Btn_Style_Load(ui.Monitor_btn_PowerOFF_label);
    __Param_Btn_Style_Load(ui.Monitor_btn_beep_label);
    __Param_Btn_Style_Load(ui.Monitor_btn_Tips_label);
    MonitorPage_Enter();
    MonitorPage_Exit();
}

/*
 * @brief       void MonitorPage_Enter(void)
 * @details     进入Monitor页面
 */
void MonitorPage_Enter(void)
{
    lv_label_set_text_static(ui.Monitor_btn_LogicTitle_label, MultStr_GetS(&mStr_Monitor_Logic_Title));
    lv_label_set_text_static(ui.Monitor_btn_TriggerTitle_label, MultStr_GetS(&mStr_Monitor_Trigger_Title));
    lv_obj_set_hidden(ui.Monitor_cont, 0);
    __button_Refresh();
    lv_event_send_refresh_recursive(ui.Monitor_cont);
}

/*
 * @brief       void MonitorPage_Exit(void)
 * @details     退出Monitor页面
 */
void MonitorPage_Exit(void)
{
    lv_obj_set_hidden(ui.Monitor_cont, 1);
}



