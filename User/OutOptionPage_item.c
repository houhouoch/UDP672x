#include "OutOptionPage.h"
#include "OutOptionPage_item.h"
#include "SettingData.h"

#include "Interface.h"
#include "Setting_Interface.h"

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


static char stringSet[32] = {0};

/*
 * @brief       void Mode_handler(lv_obj_t *obj,lv_event_t event)
 * @details     工作模式设置
 */
void Mode_handler(lv_obj_t *obj, lv_event_t event)
{
    static uint8_t editFlag = 0;
    const valueString_Def valueStr[] = {
        {POWER_MODE_NORMAL, &mStr_Mode_Normal},
        {POWER_MODE_EXT_V, &mStr_Mode_Ext_V},
        {POWER_MODE_EXT_D, &mStr_Mode_Ext_D},
        {0},
    };
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                case LV_KEY_F1: {
                    UI_IF_Power_Set_Mode(POWER_MODE_NORMAL);
                    editFlag = 0;
                }
                break;
                case LV_KEY_F2: {
                    UI_IF_Power_Set_Mode(POWER_MODE_EXT_V);
                    editFlag = 0;
                }
                break;
                case LV_KEY_F3: {
                    UI_IF_Power_Set_Mode(POWER_MODE_EXT_D);
                    editFlag = 0;
                }
                break;
                case LV_KEY_ESC:
                    editFlag = 0;
                    break;
            }
        }
        break;
        case LV_EVENT_CLICKED: {
            editFlag = 1;
        }
        break;
    }
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_Mode));
    const char *str = valueStr_GetStr(POWER_MODE, valueStr);
    lv_label_set_text_static(ui.HomePage_btn_Mode_label, str);
    lv_label_set_text_static(ui.HomePage2_btn_Mode_label, str);
    lv_label_set_text_static(obj, str);
    lv_obj_t *button = lv_obj_get_parent(obj);
    if(editFlag != 0) {
        lv_obj_set_state(button, LV_STATE_FOCUSED);
        lv_obj_set_state(obj, LV_STATE_FOCUSED);
        label_setSelStr(obj, str, str);
    } else {
        lv_obj_set_state(button, LV_STATE_DEFAULT);
        lv_obj_set_state(obj, LV_STATE_DEFAULT);
        lv_label_set_text_sel_start(obj, 0);
        lv_label_set_text_sel_end(obj, 0);
    }
}



/*
 * @brief       void P_Out_handler(lv_obj_t *obj,lv_event_t event)
 * @details     重开机自保持设置
 */
void P_Out_handler(lv_obj_t *obj, lv_event_t event)
{
    const valueString_Def valueStr[] = {
        {0, &mStr_P_Out_OFF},
        {1, &mStr_P_Out_Keep},
        {0},
    };
    static uint8_t editFlag = 0;
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                case LV_KEY_UP:
                case LV_KEY_DOWN: {
                    uint8_t temp = POWER_OUTKEEPON_SET;
                    temp = !temp;
                    UI_IF_System_POut_Onoff(temp);
                }
                break;
                case LV_KEY_ESC:
                    editFlag = 0;
                    break;
            }
        }
        break;
        case LV_EVENT_CLICKED: {
            if(editFlag == 1) {
                uint8_t temp = POWER_OUTKEEPON_SET;
                temp = !temp;
                UI_IF_System_POut_Onoff(temp);
            }
            editFlag = 1;
        }
        case LV_EVENT_REFRESH: {
        }
        break;
    }
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_P_Out));
    const char *str = valueStr_GetStr(POWER_OUTKEEPON_SET, valueStr);
    lv_label_set_text_static(obj, str);
    lv_obj_t *button = lv_obj_get_parent(obj);
    if(editFlag != 0) {
        lv_obj_set_state(button, LV_STATE_FOCUSED);
        lv_obj_set_state(obj, LV_STATE_FOCUSED);
        label_setSelStr(obj, str, str);
    } else {
        lv_obj_set_state(button, LV_STATE_DEFAULT);
        lv_obj_set_state(obj, LV_STATE_DEFAULT);
        lv_label_set_text_sel_start(obj, 0);
        lv_label_set_text_sel_end(obj, 0);
    }
}



/*
 * @brief       void DVM_Onoff_handler(lv_obj_t *obj,lv_event_t event)
 * @details     DVM电压表开关设置
 */
void DVM_Onoff_handler(lv_obj_t *obj, lv_event_t event)
{
    const valueString_Def valueStr[] = {
        {0, &mStr_OFF},
        {1, &mStr_ON},
        {0},
    };
    static uint8_t editFlag = 0;
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                case LV_KEY_UP:
                case LV_KEY_DOWN: {
                    uint8_t temp = DVM_ONOFF_SET;
                    temp = !temp;
                    UI_IF_System_DVM_Onoff(temp);
                }
                break;
                case LV_KEY_ESC:
                    editFlag = 0;
                    break;
            }
        }
        break;
        case LV_EVENT_CLICKED: {
            if(editFlag == 1) {
                uint8_t temp = DVM_ONOFF_SET;
                temp = !temp;
                UI_IF_System_DVM_Onoff(temp);
            }
            editFlag = 1;
        }
        case LV_EVENT_REFRESH: {
        }
        break;
    }
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_DVM_onoff));
    const char *str = valueStr_GetStr(DVM_ONOFF_SET, valueStr);
    lv_label_set_text_static(obj, str);
    lv_obj_t *button = lv_obj_get_parent(obj);
    if(editFlag != 0) {
        lv_obj_set_state(button, LV_STATE_FOCUSED);
        lv_obj_set_state(obj, LV_STATE_FOCUSED);
        label_setSelStr(obj, str, str);
    } else {
        lv_obj_set_state(button, LV_STATE_DEFAULT);
        lv_obj_set_state(obj, LV_STATE_DEFAULT);
        lv_label_set_text_sel_start(obj, 0);
        lv_label_set_text_sel_end(obj, 0);
    }
}


/*
 * @brief       void SRMode_handler(lv_obj_t *obj,lv_event_t event)
 * @details     斜率模式设置
 */
void SRMode_handler(lv_obj_t *obj, lv_event_t event)
{
    const valueString_Def valueStr[] = {
        {SR_MODE_NORMAL_MODE, &mStr_SR_Normal},
        {SR_MODE_VSR_MODE, &mStr_VSR_Mode},
        {SR_MODE_ISR_MODE, &mStr_ISR_Mode},
        {0},
    };
    static uint8_t editFlag = 0;
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                case LV_KEY_UP:
                case LV_KEY_DOWN: {
                    uint8_t mode = POWER_SR_MODE;
                    mode = (++POWER_SR_MODE) % (SR_MODE_MAX + 1);
                    //刷新
                    UI_IF_Power_Set_SR_Mode(mode);
                }
                break;
                case LV_KEY_ESC:
                    editFlag = 0;
                    break;
            }
        }
        break;
        case LV_EVENT_CLICKED: {
            if(editFlag == 1) {
                uint8_t mode = POWER_SR_MODE;
                mode = (++POWER_SR_MODE) % (SR_MODE_MAX + 1);
                //刷新
                UI_IF_Power_Set_SR_Mode(mode);
            }
            editFlag = 1;
        }
        case LV_EVENT_REFRESH: {
        }
        break;
    }
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_SR_Mode));
    const char *str = valueStr_GetStr(POWER_SR_MODE, valueStr);
    lv_label_set_text_static(obj, str);
    lv_obj_t *button = lv_obj_get_parent(obj);
    if(editFlag != 0) {
        lv_obj_set_state(button, LV_STATE_FOCUSED);
        lv_obj_set_state(obj, LV_STATE_FOCUSED);
        label_setSelStr(obj, str, str);
    } else {
        lv_obj_set_state(button, LV_STATE_DEFAULT);
        lv_obj_set_state(obj, LV_STATE_DEFAULT);
        lv_label_set_text_sel_start(obj, 0);
        lv_label_set_text_sel_end(obj, 0);
    }
    switch(POWER_SR_MODE)
    {
        case SR_MODE_VSR_MODE: {
            btn_SR_Set.noVisable = 0;
            if(tree_SR_Set->child != NULL) {
                Tree_Delete(tree_SR_Set, tree_SR_Set->child);
                Tree_AddNode(tree_SR_Set, &btn_VSR_Rising);
                Tree_AddNode(tree_SR_Set, &btn_VSR_Failing);
            }
        }
        break;
        case SR_MODE_ISR_MODE: {
            btn_SR_Set.noVisable = 0;
            if(tree_SR_Set->child != NULL) {
                Tree_Delete(tree_SR_Set, tree_SR_Set->child);
                Tree_AddNode(tree_SR_Set, &btn_ISR_Rising);
                Tree_AddNode(tree_SR_Set, &btn_ISR_Failing);
            }
        }
        break;
        default: {
            btn_SR_Set.noVisable = 1;
        }
        break;
    }
    Tree_Btnm_Refresh();
}


/*
 * @brief
 * @details     电压斜率设置(仅在电压斜率模式有效)
 */
static void VSR_RefreshUI(lv_obj_t *obj, uint8_t *editIndex, float value)
{
    lv_obj_t *button = lv_obj_get_parent(obj);
    if(editIndex == NULL) {
        lv_obj_set_state(button, LV_STATE_DEFAULT);
        lv_obj_set_state(obj, LV_STATE_DEFAULT);
    } else {
        lv_obj_set_state(button, LV_STATE_FOCUSED);
        lv_obj_set_state(obj, LV_STATE_FOCUSED);
    }
    sprintf(stringSet, VSR_SET_FORM"V/s", value);
    if(editIndex != NULL) {
        label_setSelNum(obj, *editIndex, stringSet);
    } else {
        lv_label_set_text_sel_start(obj, 0);
        lv_label_set_text_sel_end(obj, 0);
    }
    lv_label_set_text(obj, stringSet);
    lv_obj_invalidate(obj);
}

void VSR_Up_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    static uint8_t idx_VSR = 0;
    NumberInput_Process(7, UI_IF_Power_Set_VSR_Up);
    static uint8_t editFlag = 0;
    switch(event)
    {
        case LV_EVENT_KEY: {
            switch(key) {
                case LV_KEY_UP: {
                    float temp = POWER_VSR_UP;
                    temp += VSR_step[idx_VSR];
                    UI_IF_Power_Set_VSR_Up(temp);
                }
                break;
                case LV_KEY_DOWN: {
                    float temp = POWER_VSR_UP;
                    temp -= VSR_step[idx_VSR];
                    UI_IF_Power_Set_VSR_Up(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(idx_VSR > 0)
                    {
                        idx_VSR--;
                    } else {
                        idx_VSR = sizeof(VSR_step) / sizeof(VSR_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_ENTER:
                case LV_KEY_ENCODER:
                case LV_KEY_LEFT: {
                    if(idx_VSR < (sizeof(VSR_step) / sizeof(VSR_step[0]) - 1))
                    {
                        idx_VSR++;
                    } else {
                        idx_VSR = 0;
                    }
                }
                break;
            }
            if(key == LV_KEY_ESC) {
                editFlag = 0;
            }
        }
        break;
        case LV_EVENT_REFRESH:
            break;
        case LV_EVENT_CLICKED: {
            if(POWER_SR_MODE != SR_MODE_VSR_MODE) {
                GUI_SEND_KEY(LV_KEY_RETURN);
            }
            editFlag = 1;
        }
        break;
    }
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_VSR_U));
    float vsr_up = 0;
    lv_obj_t *parent = lv_obj_get_parent(obj);
    switch(POWER_SR_MODE)
    {
        case SR_MODE_VSR_MODE:
            lv_obj_set_hidden(parent, 0);
            vsr_up = POWER_VSR_UP;
            if(editFlag != 0) {
                VSR_RefreshUI(obj, &idx_VSR, vsr_up);
            } else {
                VSR_RefreshUI(obj, NULL, vsr_up);
            }
            break;
        default:
            lv_obj_set_hidden(parent, 1);
            break;
    }
}
void VSR_Down_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    static uint8_t idx_VSR = 0;
    NumberInput_Process(7, UI_IF_Power_Set_VSR_Down);
    static uint8_t editFlag = 0;
    switch(event)
    {
        case LV_EVENT_KEY: {
            switch(key) {
                case LV_KEY_UP: {
                    float temp = POWER_VSR_DOWN;
                    temp += VSR_step[idx_VSR];
                    UI_IF_Power_Set_VSR_Down(temp);
                }
                break;
                case LV_KEY_DOWN: {
                    float temp = POWER_VSR_DOWN;
                    temp -= VSR_step[idx_VSR];
                    UI_IF_Power_Set_VSR_Down(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(idx_VSR > 0)
                    {
                        idx_VSR--;
                    }
                    else
                    {
                        idx_VSR = sizeof(VSR_step) / sizeof(VSR_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_ENTER:
                case LV_KEY_ENCODER:
                case LV_KEY_LEFT: {
                    if(idx_VSR < (sizeof(VSR_step) / sizeof(VSR_step[0]) - 1))
                    {
                        idx_VSR++;
                    }
                    else
                    {
                        idx_VSR = 0;
                    }
                }
                break;
            }
            if(key == LV_KEY_ESC) {
                editFlag = 0;
            }
        }
        break;
        case LV_EVENT_REFRESH:
            break;
        case LV_EVENT_CLICKED: {
            if(POWER_SR_MODE != SR_MODE_VSR_MODE) {
                GUI_SEND_KEY(LV_KEY_RETURN);
            }
            editFlag = 1;
        }
        break;
    }
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_VSR_D));
    float vsr_down = 0;
    lv_obj_t *parent = lv_obj_get_parent(obj);
    switch(POWER_SR_MODE)
    {
        case SR_MODE_VSR_MODE:
            lv_obj_set_hidden(parent, 0);
            vsr_down = POWER_VSR_DOWN;
            if(editFlag != 0) {
                VSR_RefreshUI(obj, &idx_VSR, vsr_down);
            } else {
                VSR_RefreshUI(obj, NULL, vsr_down);
            }
            break;
        default:
            lv_obj_set_hidden(parent, 1);
            break;
    }
}


/*
 * @brief
 * @details     电流斜率设置(仅在电流斜率模式)
 */
static void ISR_RefreshUI(lv_obj_t *obj, uint8_t *editIndex, float value)
{
    lv_obj_t *button = lv_obj_get_parent(obj);
    if(editIndex == NULL) {
        lv_obj_set_state(button, LV_STATE_DEFAULT);
        lv_obj_set_state(obj, LV_STATE_DEFAULT);
    } else {
        lv_obj_set_state(button, LV_STATE_FOCUSED);
        lv_obj_set_state(obj, LV_STATE_FOCUSED);
    }
    sprintf(stringSet, ISR_SET_FORM"A/s", value);
    if(editIndex != NULL) {
        label_setSelNum(obj, *editIndex, stringSet);
    } else {
        lv_label_set_text_sel_start(obj, 0);
        lv_label_set_text_sel_end(obj, 0);
    }
    lv_label_set_text(obj, stringSet);
    lv_obj_invalidate(obj);
}
void ISR_Up_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    static uint8_t idx_ISR = 0;
    NumberInput_Process(7, UI_IF_Power_Set_ISR_Up);
    static uint8_t editFlag = 0;
    switch(event)
    {
        case LV_EVENT_KEY: {
            switch(key) {
                case LV_KEY_UP: {
                    float temp = POWER_ISR_UP;
                    temp += ISR_step[idx_ISR];
                    UI_IF_Power_Set_ISR_Up(temp);
                }
                break;
                case LV_KEY_DOWN: {
                    float temp = POWER_ISR_UP;
                    temp -= ISR_step[idx_ISR];
                    UI_IF_Power_Set_ISR_Up(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(idx_ISR > 0)
                    {
                        idx_ISR--;
                    } else {
                        idx_ISR = sizeof(ISR_step) / sizeof(ISR_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_ENTER:
                case LV_KEY_ENCODER:
                case LV_KEY_LEFT: {
                    if(idx_ISR < (sizeof(ISR_step) / sizeof(ISR_step[0]) - 1))
                    {
                        idx_ISR++;
                    } else {
                        idx_ISR = 0;
                    }
                }
                break;
            }
            if(key == LV_KEY_ESC) {
                editFlag = 0;
            }
        }
        break;
        case LV_EVENT_REFRESH:
            break;
        case LV_EVENT_CLICKED: {
            if(POWER_SR_MODE != SR_MODE_ISR_MODE) {
                GUI_SEND_KEY(LV_KEY_RETURN);
            }
            editFlag = 1;
        }
        break;
    }
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_ISR_U));
    //
    float isr_up = 0;
    lv_obj_t *parent = lv_obj_get_parent(obj);
    switch(POWER_SR_MODE)
    {
        case SR_MODE_ISR_MODE:
            lv_obj_set_hidden(parent, 0);
            isr_up = POWER_ISR_UP;
            if(editFlag != 0) {
                ISR_RefreshUI(obj, &idx_ISR, isr_up);
            } else {
                ISR_RefreshUI(obj, NULL, isr_up);
            }
            break;
        default:
            lv_obj_set_hidden(parent, 1);
            break;
    }
}
void ISR_Down_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    static uint8_t idx_ISR = 0;
    NumberInput_Process(7, UI_IF_Power_Set_ISR_Down);
    static uint8_t editFlag = 0;
    switch(event)
    {
        case LV_EVENT_KEY: {
            switch(key) {
                case LV_KEY_UP: {
                    float temp = POWER_ISR_DOWN;
                    temp += ISR_step[idx_ISR];
                    UI_IF_Power_Set_ISR_Down(temp);
                }
                break;
                case LV_KEY_DOWN: {
                    float temp = POWER_ISR_DOWN;
                    temp -= ISR_step[idx_ISR];
                    UI_IF_Power_Set_ISR_Down(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(idx_ISR > 0)
                    {
                        idx_ISR--;
                    } else {
                        idx_ISR = sizeof(ISR_step) / sizeof(ISR_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_ENTER:
                case LV_KEY_ENCODER:
                case LV_KEY_LEFT: {
                    if(idx_ISR < (sizeof(ISR_step) / sizeof(ISR_step[0]) - 1))
                    {
                        idx_ISR++;
                    } else {
                        idx_ISR = 0;
                    }
                }
                break;
            }
            if(key == LV_KEY_ESC) {
                editFlag = 0;
            }
        }
        break;
        case LV_EVENT_REFRESH:
            break;
        case LV_EVENT_CLICKED: {
            if(POWER_SR_MODE != SR_MODE_ISR_MODE) {
                GUI_SEND_KEY(LV_KEY_RETURN);
            }
            editFlag = 1;
        }
        break;
    }
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_ISR_D));
    float isr_down = 0;
    lv_obj_t *parent = lv_obj_get_parent(obj);
    switch(POWER_SR_MODE)
    {
        case SR_MODE_ISR_MODE:
            lv_obj_set_hidden(parent, 0);
            isr_down = POWER_ISR_DOWN;
            if(editFlag != 0) {
                ISR_RefreshUI(obj, &idx_ISR, isr_down);
            } else {
                ISR_RefreshUI(obj, NULL, isr_down);
            }
            break;
        default:
            lv_obj_set_hidden(parent, 1);
            break;
    }
}




