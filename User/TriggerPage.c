#include "Trigger.h"
#include "TriggerPage.h"
#include "Trigger_Interface.h"

Tree_Def *tree_trigger;

static void __button_refresh(void);
//当前选择的通道
static uint8_t Trigger_chSel = 0;

/*
 * @brief       void TriggerPage_SelChannel(int8_t ch)
 * @details     设置选定的通道
 */
void TriggerPage_SelChannel(int8_t ch)
{
    if(!((ch >= TRIGGER_CH_MIN) && (ch <= TRIGGER_CH_MAX))) {
        return;
    }
    Trigger_chSel = ch;
    lv_obj_t *btn_ch = NULL;
    switch(Trigger_chSel) {
        case TRIGGER_CH_D0:
            btn_ch = ui.TriggerPage_btn_D0;
            break;
        case TRIGGER_CH_D1:
            btn_ch = ui.TriggerPage_btn_D1;
            break;
        case TRIGGER_CH_D2:
            btn_ch = ui.TriggerPage_btn_D2;
            break;
        case TRIGGER_CH_D3:
            btn_ch = ui.TriggerPage_btn_D3;
            break;
    }
    if(btn_ch == NULL) {
        return ;
    }
    {
        lv_obj_t *imgSel = ui.TriggerPage_img_chSel;
        uint16_t x = 0, y = 0;
        uint16_t width = 0, height = 0;
        x = lv_obj_get_x(btn_ch);
        y = lv_obj_get_y(btn_ch);
        width = lv_obj_get_width(btn_ch);
        height = lv_obj_get_height(btn_ch);
        lv_obj_set_pos(imgSel, x, y);
        lv_obj_set_size(imgSel, width, height);
        lv_obj_set_hidden(imgSel, 0);
    }
}

/*
 * @brief       void TriggerPage_SetMode(int8_t ch, int8_t mode)
 * @details     设置触发器的工作模式 (输入/输出/关闭)
 */
void TriggerPage_SetMode(int8_t ch, int8_t mode)
{
    if(!((ch >= TRIGGER_CH_MIN) && (ch <= TRIGGER_CH_MAX))) {
        return;
    }
    if(!((mode >= TRIGGER_MODE_MIN) && (mode <= TRIGGER_MODE_MAX))) {
        return;
    }
    Trigger[ch].mode = mode;
}





/*
 * @brief       void TriggerPage_ch_handler(lv_obj_t *obj, lv_event_t event)
 * @details     TriggerPage触发器通道事件处理
 */
void TriggerPage_ch_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    event = event;
    switch(event)
    {
        case LV_EVENT_CLICKED: {
            uint8_t ch = Trigger_chSel;
            ch += 1;
            if(ch > TRIGGER_CH_MAX) {
                ch = TRIGGER_CH_MIN;
            }
            TriggerPage_SelChannel(ch);
            __button_refresh();
        }
        case LV_EVENT_FOCUSED:
        case LV_EVENT_REFRESH: {
        } break;
    }
}


/*
 * @brief       void TriggerPage_mode_handler(lv_obj_t *obj, lv_event_t event)
 * @details     TriggerPage触发器模式事件处理
 */
void TriggerPage_mode_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    event = event;
    switch(event)
    {
        case LV_EVENT_CLICKED: {
            uint8_t ch = Trigger_chSel;
            uint8_t mode = Trigger[ch].mode;
            mode += 1;
            if(mode > TRIGGER_MODE_MAX) {
                mode = TRIGGER_MODE_MIN;
            }
            TriggerPage_SetMode(ch, mode);
            __button_refresh();
        }
        case LV_EVENT_FOCUSED:
        case LV_EVENT_REFRESH: {
        } break;
    }
}


/*
 * @brief       void TriggerPage_handler(lv_obj_t *obj, lv_event_t event)
 * @details     TriggerPage触发器事件处理
 */
void TriggerPage_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    event = event;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    switch(event)
    {
        case LV_EVENT_FOCUSED:
        case LV_EVENT_REFRESH: {
            for(uint8_t i = 0; i < TRIGGER_COUNT; ++i)
            {
                const char *mode_Str = "";
                lv_color_t str_Color = {0};
                uint8_t mode = Trigger[i].mode;
                switch(mode)
                {
                    case TRIGGER_MODE_IN: {
                        mode_Str = "IN";
                        str_Color = lv_color_make(0x00, 0xff, 0x00);
                    }
                    break;
                    case TRIGGER_MODE_OUT: {
                        mode_Str = "OUT";
                        str_Color = lv_color_make(0x00, 0xff, 0x00);
                    }
                    break;
                    case TRIGGER_MODE_OFF:
                        mode_Str = "OFF";
                        str_Color = lv_color_make(0x9A, 0x9A, 0x9A);
                        break;
                }
                switch(i)
                {
                    case TRIGGER_CH_D0:
                        lv_obj_set_style_local_text_color(ui.TriggerPage_btn_D0_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, str_Color);
                        BtnLabel_Set_Edit_Value(ui.TriggerPage_btn_D0_label, mode_Str);
                        break;
                    case TRIGGER_CH_D1:
                        lv_obj_set_style_local_text_color(ui.TriggerPage_btn_D1_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, str_Color);
                        BtnLabel_Set_Edit_Value(ui.TriggerPage_btn_D1_label, mode_Str);
                        break;
                    case TRIGGER_CH_D2:
                        lv_obj_set_style_local_text_color(ui.TriggerPage_btn_D2_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, str_Color);
                        BtnLabel_Set_Edit_Value(ui.TriggerPage_btn_D2_label, mode_Str);
                        break;
                    case TRIGGER_CH_D3:
                        lv_obj_set_style_local_text_color(ui.TriggerPage_btn_D3_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, str_Color);
                        BtnLabel_Set_Edit_Value(ui.TriggerPage_btn_D3_label, mode_Str);
                        break;
                }
            }
        }
        break;
    }
}


/* ------------------------------------------ INPUT ------------------------------------------ */

/*
 * @brief       void TriggerPage_InSign_handler(lv_obj_t *obj, lv_event_t event)
 * @details     触发器输入信号
 */
void TriggerPage_InSign_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    event = event;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //当重复选中时,改变参数
    if(event == LV_EVENT_CLICKED) {
        if(lv_obj_get_state(obj, LV_LABEL_PART_MAIN) == LV_STATE_FOCUSED) {
            event = LV_EVENT_KEY;
            key = LV_KEY_UP;
        }
    }
    //
    uint8_t ch = Trigger_chSel;
    switch(event)
    {
        case LV_EVENT_KEY: {
            int8_t inSign = Trigger[ch].inConf.inType;
            switch(key) {
                case LV_KEY_UP: {
                    inSign += 1;
                    if(inSign > IN_TYPE_MAX) {
                        inSign = IN_TYPE_MIN;
                    }
                }
                break;
                case LV_KEY_DOWN: {
                    inSign -= 1;
                    if(inSign < IN_TYPE_MIN) {
                        inSign = IN_TYPE_MAX;
                    }
                }
                break;
                case LV_KEY_ESC: {
                    lv_obj_set_state(obj, LV_STATE_DEFAULT);
                    lv_label_set_text_sel_start(obj, LV_LABEL_TEXT_SEL_OFF);
                    lv_label_set_text_sel_end(obj, LV_LABEL_TEXT_SEL_OFF);
                }
                break;
            }
            Trigger[ch].inConf.inType = inSign;
        }
        break;
        case LV_EVENT_CLICKED: {
            lv_obj_set_state(obj, LV_STATE_FOCUSED);
            lv_label_set_text_sel_start(obj, 0x00);
            lv_label_set_text_sel_end(obj, 0xff);
        }
        break;
    }
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_trigger_sign));
    switch(Trigger[ch].inConf.inType) {
        case IN_TYPE_NULL:
            Trigger[ch].inConf.inType = IN_TYPE_RISE;
        case IN_TYPE_RISE:
            BtnLabel_Set_Edit_Value(obj, MultStr_GetS(&mStr_trigger_sign_rising));
            break;
        case IN_TYPE_FALL:
            BtnLabel_Set_Edit_Value(obj, MultStr_GetS(&mStr_trigger_sign_fall));
            break;
        case IN_TYPE_HIGH:
            BtnLabel_Set_Edit_Value(obj, MultStr_GetS(&mStr_trigger_sign_high));
            break;
        case IN_TYPE_LOW:
            BtnLabel_Set_Edit_Value(obj, MultStr_GetS(&mStr_trigger_sign_low));
            break;
        default:
            BtnLabel_Set_Edit_Value(obj, "");
            break;
    }
}


/*
 * @brief       void TriggerPage_InSense_handler(lv_obj_t *obj, lv_event_t event)
 * @details     触发器输入灵敏度
 */
void TriggerPage_InSense_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    event = event;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //当重复选中时,改变参数
    if(event == LV_EVENT_CLICKED) {
        if(lv_obj_get_state(obj, LV_LABEL_PART_MAIN) == LV_STATE_FOCUSED) {
            event = LV_EVENT_KEY;
            key = LV_KEY_UP;
        }
    }
    //
    uint8_t ch = Trigger_chSel;
    switch(event)
    {
        case LV_EVENT_KEY: {
            int8_t inSens = Trigger[ch].inConf.inSens;
            switch(key) {
                case LV_KEY_UP: {
                    inSens += 1;
                    if(inSens > IN_SENS_MAX) {
                        inSens = IN_SENS_MIN;
                    }
                }
                break;
                case LV_KEY_DOWN: {
                    inSens -= 1;
                    if(inSens < IN_SENS_MIN) {
                        inSens = IN_SENS_MAX;
                    }
                }
                break;
                case LV_KEY_ESC: {
                    lv_obj_set_state(obj, LV_STATE_DEFAULT);
                    lv_label_set_text_sel_start(obj, LV_LABEL_TEXT_SEL_OFF);
                    lv_label_set_text_sel_end(obj, LV_LABEL_TEXT_SEL_OFF);
                }
                break;
            }
            Trigger[ch].inConf.inSens = inSens;
        }
        break;
        case LV_EVENT_CLICKED: {
            lv_obj_set_state(obj, LV_STATE_FOCUSED);
            lv_label_set_text_sel_start(obj, 0x00);
            lv_label_set_text_sel_end(obj, 0xff);
        }
        break;
    }
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_trigger_sense));
    switch(Trigger[ch].inConf.inSens) {
        case IN_SENS_NULL:
            Trigger[ch].inConf.inSens = IN_SENS_HIGH;
        case IN_SENS_HIGH:
            BtnLabel_Set_Edit_Value(obj, MultStr_GetS(&mStr_trigger_sense_high));
            break;
        case IN_SENS_MID:
            BtnLabel_Set_Edit_Value(obj, MultStr_GetS(&mStr_trigger_sense_mid));
            break;
        case IN_SENS_LOW:
            BtnLabel_Set_Edit_Value(obj, MultStr_GetS(&mStr_trigger_sense_low));
            break;
        default:
            BtnLabel_Set_Edit_Value(obj, "");
            break;
    }
}


/*
 * @brief       void TriggerPage_InSlave_handler(lv_obj_t *obj, lv_event_t event)
 * @details     触发器输入受控源
 */
void TriggerPage_InSlave_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    event = event;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //当重复选中时,改变参数
    if(event == LV_EVENT_CLICKED) {
        if(lv_obj_get_state(obj, LV_LABEL_PART_MAIN) == LV_STATE_FOCUSED) {
            event = LV_EVENT_KEY;
            key = LV_KEY_UP;
        }
    }
    //
    uint8_t ch = Trigger_chSel;
    switch(event)
    {
        case LV_EVENT_KEY: {
            int8_t inSlave = Trigger[ch].inConf.inSlave;
            switch(key) {
                case LV_KEY_UP: {
                    inSlave += 1;
                    if(inSlave > IN_SOURCE_MAX) {
                        inSlave = IN_SOURCE_MIN;
                    }
                }
                break;
                case LV_KEY_DOWN: {
                    inSlave -= 1;
                    if(inSlave < IN_SOURCE_MIN) {
                        inSlave = IN_SOURCE_MAX;
                    }
                }
                break;
                case LV_KEY_ESC: {
                    lv_obj_set_state(obj, LV_STATE_DEFAULT);
                    lv_label_set_text_sel_start(obj, LV_LABEL_TEXT_SEL_OFF);
                    lv_label_set_text_sel_end(obj, LV_LABEL_TEXT_SEL_OFF);
                }
                break;
            }
            Trigger[ch].inConf.inSlave = inSlave;
        }
        break;
        case LV_EVENT_CLICKED: {
            lv_obj_set_state(obj, LV_STATE_FOCUSED);
            lv_label_set_text_sel_start(obj, 0x00);
            lv_label_set_text_sel_end(obj, 0xff);
        }
        break;
    }
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_trigger_insourse));
    switch(Trigger[ch].inConf.inSlave) {
        case IN_SOURCE_NULL:
            Trigger[ch].inConf.inSlave = IN_SOURCE_CH1;
        case IN_SOURCE_CH1:
            BtnLabel_Set_Edit_Value(obj, MultStr_GetS(&mStr_trigger_insourse_ch1));
            break;
        default:
            BtnLabel_Set_Edit_Value(obj, "");
            break;
    }
}


/*
 * @brief       void TriggerPage_InResponse_handler(lv_obj_t *obj, lv_event_t event)
 * @details     触发器输入响应
 */
void TriggerPage_InResponse_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    event = event;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //当重复选中时,改变参数
    if(event == LV_EVENT_CLICKED) {
        if(lv_obj_get_state(obj, LV_LABEL_PART_MAIN) == LV_STATE_FOCUSED) {
            event = LV_EVENT_KEY;
            key = LV_KEY_UP;
        }
    }
    //
    uint8_t ch = Trigger_chSel;
    switch(event)
    {
        case LV_EVENT_KEY: {
            int8_t inResponse = Trigger[ch].inConf.inRespon;
            switch(key) {
                case LV_KEY_UP: {
                    inResponse += 1;
                    if(inResponse > IN_RESP_MAX) {
                        inResponse = IN_RESP_MIN;
                    }
                }
                break;
                case LV_KEY_DOWN: {
                    inResponse -= 1;
                    if(inResponse < IN_RESP_MIN) {
                        inResponse = IN_RESP_MAX;
                    }
                }
                break;
                case LV_KEY_ESC: {
                    lv_obj_set_state(obj, LV_STATE_DEFAULT);
                    lv_label_set_text_sel_start(obj, LV_LABEL_TEXT_SEL_OFF);
                    lv_label_set_text_sel_end(obj, LV_LABEL_TEXT_SEL_OFF);
                }
                break;
            }
            Trigger[ch].inConf.inRespon = inResponse;
        }
        break;
        case LV_EVENT_CLICKED: {
            lv_obj_set_state(obj, LV_STATE_FOCUSED);
            lv_label_set_text_sel_start(obj, 0x00);
            lv_label_set_text_sel_end(obj, 0xff);
        }
        break;
    }
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_trigger_response));
    switch(Trigger[ch].inConf.inRespon) {
        case IN_RESP_NULL:
            Trigger[ch].inConf.inRespon = IN_RESP_ON;
        case IN_RESP_ON:
            BtnLabel_Set_Edit_Value(obj, MultStr_GetS(&mStr_trigger_response_on));
            break;
        case IN_RESP_OFF:
            BtnLabel_Set_Edit_Value(obj, MultStr_GetS(&mStr_trigger_response_off));
            break;
        case IN_RESP_ALTER:
            BtnLabel_Set_Edit_Value(obj, MultStr_GetS(&mStr_trigger_response_alter));
            break;
        case IN_RESP_LIST_ON:
            BtnLabel_Set_Edit_Value(obj, MultStr_GetS(&mStr_trigger_response_list_on));
            break;
        case IN_RESP_LIST_OFF:
            BtnLabel_Set_Edit_Value(obj, MultStr_GetS(&mStr_trigger_response_list_off));
            break;
        case IN_RESP_DELAY_ON:
            BtnLabel_Set_Edit_Value(obj, MultStr_GetS(&mStr_trigger_response_delay_on));
            break;
        case IN_RESP_DELAY_OFF:
            BtnLabel_Set_Edit_Value(obj, MultStr_GetS(&mStr_trigger_response_delay_off));
            break;
    }
}



/* ------------------------------------------ OUTPUT ------------------------------------------ */


/*
 * @brief       void TriggerPage_OutSource_handler(lv_obj_t *obj, lv_event_t event)
 * @details     触发器输出源
 */
void TriggerPage_OutSource_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    event = event;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //当重复选中时,改变参数
    if(event == LV_EVENT_CLICKED) {
        if(lv_obj_get_state(obj, LV_LABEL_PART_MAIN) == LV_STATE_FOCUSED) {
            event = LV_EVENT_KEY;
            key = LV_KEY_UP;
        }
    }
    uint8_t ch = Trigger_chSel;
    switch(event)
    {
        case LV_EVENT_KEY: {
            int8_t outSource = Trigger[ch].outConf.outSource;
            switch(key) {
                case LV_KEY_UP: {
                    outSource += 1;
                    if(outSource > OUT_SOURCE_MAX) {
                        outSource = OUT_SOURCE_MIN;
                    }
                }
                break;
                case LV_KEY_DOWN: {
                    outSource -= 1;
                    if(outSource > OUT_SOURCE_MIN) {
                        outSource = OUT_SOURCE_MAX;
                    }
                }
                break;
                case LV_KEY_ESC: {
                    lv_obj_set_state(obj, LV_STATE_DEFAULT);
                    lv_label_set_text_sel_start(obj, LV_LABEL_TEXT_SEL_OFF);
                    lv_label_set_text_sel_end(obj, LV_LABEL_TEXT_SEL_OFF);
                }
                break;
            }
            Trigger[ch].outConf.outSource = outSource;
        }
        break;
        case LV_EVENT_CLICKED: {
            lv_obj_set_state(obj, LV_STATE_FOCUSED);
            lv_label_set_text_sel_start(obj, 0x00);
            lv_label_set_text_sel_end(obj, 0xff);
        }
        break;
    }
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_trigger_source));
    switch(Trigger[ch].outConf.outSource) {
        case OUT_SOURCE_NULL:
            Trigger[ch].outConf.outSource = OUT_SOURCE_CH1;
        case OUT_SOURCE_CH1:
            BtnLabel_Set_Edit_Value(obj, MultStr_GetS(&mStr_trigger_source_ch1));
            break;
        default:
            BtnLabel_Set_Edit_Value(obj, "");
            break;
    }
}


static uint8_t _editSize = 0;
static const float *_editStep = NULL;
static void __Condition_Refresh(lv_obj_t *obj, uint8_t *idx)
{
    static char disBuf[64] = {0};
    memset(disBuf, 0, sizeof(disBuf));
    uint8_t ch = Trigger_chSel;
    float *val = Trigger_Get_ConditionValue(ch, Trigger[ch].outConf.condition);
    switch(Trigger[ch].outConf.condition) {
        case CONDITION_NULL:
            Trigger[ch].outConf.condition = CONDITION_OUT_ON;
        case CONDITION_OUT_ON:
            sprintf(disBuf, "%s", MultStr_GetS(&mStr_trigger_condition_outon));
            BtnLabel_Set_Edit_Value(obj, disBuf);
            label_setSelStr(obj, disBuf, disBuf);
            _editSize = 0;
            _editStep = NULL;
            return;
        case CONDITION_OUT_OFF:
            sprintf(disBuf, "%s", MultStr_GetS(&mStr_trigger_condition_outoff));
            BtnLabel_Set_Edit_Value(obj, disBuf);
            label_setSelStr(obj, disBuf, disBuf);
            _editSize = 0;
            _editStep = NULL;
            return;
        //电压
        case CONDITION_V_MORE: {
            if(val == NULL) {
                return ;
            }
            sprintf(disBuf, VOL_SET_FORM"V""<Vo", *val);
            _editSize = ARRAY_COUNT(V_step);
            _editStep = V_step;
        }
        break;
        case CONDITION_V_LESS: {
            if(val == NULL) {
                return ;
            }
            sprintf(disBuf, VOL_SET_FORM"V"">Vo", *val);
            _editSize = ARRAY_COUNT(V_step);
            _editStep = V_step;
        }
        break;
        case CONDITION_V_EQUAL: {
            if(val == NULL) {
                return ;
            }
            sprintf(disBuf, VOL_SET_FORM"V""=Vo", *val);
            _editSize = ARRAY_COUNT(V_step);
            _editStep = V_step;
        }
        break;
        //电流
        case CONDITION_C_MORE: {
            if(val == NULL) {
                return ;
            }
            sprintf(disBuf, AMP_SET_FORM"A""<Io", *val);
            _editSize = ARRAY_COUNT(A_step);
            _editStep = A_step;
        }
        break;
        case CONDITION_C_LESS: {
            if(val == NULL) {
                return ;
            }
            sprintf(disBuf, AMP_SET_FORM"A"">Io", *val);
            _editSize = ARRAY_COUNT(A_step);
            _editStep = A_step;
        }
        break;
        case CONDITION_C_EQUAL: {
            if(val == NULL) {
                return ;
            }
            sprintf(disBuf, AMP_SET_FORM"A""=Io", *val);
            _editSize = ARRAY_COUNT(A_step);
            _editStep = A_step;
        }
        break;
        //功率
        case CONDITION_P_MORE: {
            if(val == NULL) {
                return ;
            }
            sprintf(disBuf, WAT_SET_FORM"W""<Wo", *val);
            _editSize = ARRAY_COUNT(W_step);
            _editStep = W_step;
        }
        break;
        case CONDITION_P_LESS: {
            if(val == NULL) {
                return ;
            }
            sprintf(disBuf, WAT_SET_FORM"W"">Wo", *val);
            _editSize = ARRAY_COUNT(W_step);
            _editStep = W_step;
        }
        break;
        case CONDITION_P_EQUAL: {
            if(val == NULL) {
                return ;
            }
            sprintf(disBuf, WAT_SET_FORM"W""=Wo", *val);
            _editSize = ARRAY_COUNT(W_step);
            _editStep = W_step;
        }
        break;
        default:
            break;
    }
    BtnLabel_Set_Edit_Value(obj, disBuf);
    if(idx != NULL) {
        label_setSelNum(obj, *idx, disBuf);
        lv_obj_set_state(obj, LV_STATE_FOCUSED);
        lv_label_set_text_sel_start(obj, 0x00);
        lv_label_set_text_sel_end(obj, 0xff);
    } else {
        label_setSelStr(obj, disBuf, disBuf);
        lv_obj_set_state(obj, LV_STATE_DEFAULT);
        lv_label_set_text_sel_start(obj, LV_LABEL_TEXT_SEL_OFF);
        lv_label_set_text_sel_end(obj, LV_LABEL_TEXT_SEL_OFF);
    }
}
/*
 * @brief       void TriggerPage_Condition_handler(lv_obj_t *obj, lv_event_t event)
 * @details     触发器输出条件
 */
void TriggerPage_Condition_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    event = event;
    static uint8_t idx = 0;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //当重复选中时,改变参数
    if(event == LV_EVENT_CLICKED) {
        if(lv_obj_get_state(obj, LV_LABEL_PART_MAIN) == LV_STATE_FOCUSED) {
            event = LV_EVENT_KEY;
            key = LV_KEY_ENTER;
        }
    }
    uint8_t ch = Trigger_chSel;
    switch(event)
    {
        case LV_EVENT_KEY: {
            switch(key)
            {
                case LV_KEY_ENCODER:
                case LV_KEY_ENTER: {
                    int8_t condition = Trigger[ch].outConf.condition;
                    condition += 1;
                    if(condition > CONDITION_MAX) {
                        condition = CONDITION_MIN;
                    }
                    Trigger[ch].outConf.condition = condition;
                    idx = 0;
                }
                break;
                case LV_KEY_UP: {
                    if((_editSize > 0) && (_editStep != NULL)) {
                        float *val = Trigger_Get_ConditionValue(ch, Trigger[ch].outConf.condition);
                        if(val != NULL) {
                            *val += _editStep[idx];
                            UI_IF_Trigger_Set_Out_Condition_Val(ch, *val);
                        }
                    }
                }
                break;
                case LV_KEY_DOWN: {
                    if((_editSize > 0) && (_editStep != NULL)) {
                        float *val = Trigger_Get_ConditionValue(ch, Trigger[ch].outConf.condition);
                        if(val != NULL) {
                            *val -= _editStep[idx];
                            UI_IF_Trigger_Set_Out_Condition_Val(ch, *val);
                        }
                    }
                }
                break;
                case LV_KEY_RIGHT: {
                    if((_editSize > 0) && (_editStep != NULL)) {
                        if(idx > 0) {
                            idx -= 1;
                        } else {
                            idx = (_editSize - 1);
                        }
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if((_editSize > 0) && (_editStep != NULL)) {
                        if(idx < (_editSize - 1)) {
                            idx += 1;
                        } else {
                            idx = 0;
                        }
                    }
                }
                break;
            }
            if((key != LV_KEY_ESC) && (key != LV_KEY_RETURN)) {
                __Condition_Refresh(obj, &idx);
            } else {
                __Condition_Refresh(obj, NULL);
            }
        }
        break;
        case LV_EVENT_CLICKED: {
            idx = 0;
            __Condition_Refresh(obj, &idx);
        }
        break;
        case LV_EVENT_FOCUSED:
        case LV_EVENT_REFRESH: {
            BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_trigger_condition));
            __Condition_Refresh(obj, NULL);
        }
        break;
    }
}


/*
 * @brief       void TriggerPage_Polarity_handler(lv_obj_t *obj, lv_event_t event)
 * @details     触发器输出极性
 */
void TriggerPage_Polarity_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    event = event;
    uint8_t ch = Trigger_chSel;
    switch(event)
    {
        case LV_EVENT_CLICKED: {
            uint8_t polarity = Trigger[ch].outConf.outPolarity;
            polarity += 1;
            if(polarity > POLARITY_MAX) {
                polarity = POLARITY_MIN;
            }
            Trigger[ch].outConf.outPolarity = polarity;
            GUI_SEND_KEY(LV_KEY_RETURN);
        }
        case LV_EVENT_FOCUSED:
        case LV_EVENT_REFRESH: {
            BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_trigger_polarity));
            switch(Trigger[ch].outConf.outPolarity) {
                case POLARITY_NEGATIVE:
                    BtnLabel_Set_Edit_Value(obj, MultStr_GetS(&mStr_trigger_polarity_negative));
                    break;
                case POLARITY_POSITIVE:
                    BtnLabel_Set_Edit_Value(obj, MultStr_GetS(&mStr_trigger_polarity_positive));
                    break;
                default:
                    BtnLabel_Set_Edit_Value(obj, "");
                    break;
            }
        }
        break;
    }
}



static void __Param_Btn_Style_Load(lv_obj_t *label)
{
    extern lv_font_t MultFont_16;
    if(label == NULL) {
        return ;
    }
    lv_obj_t *button = lv_obj_get_parent(label);
    uint16_t button_width = lv_obj_get_width(button);
    uint16_t button_height = lv_obj_get_height(button);
    lv_label_set_long_mode(label, LV_LABEL_LONG_BREAK);
    lv_obj_set_size(label, button_width - 90, button_height);
    lv_obj_align(label, button, LV_ALIGN_IN_RIGHT_MID, 0, 0);
    lv_label_set_align(label, LV_LABEL_ALIGN_RIGHT);
    //标签
    lv_style_t *plabelStyle = lv_obj_get_local_style(label, LV_LABEL_PART_MAIN);
    static lv_style_t labelStyle = {0};
    lv_style_copy(&labelStyle, plabelStyle);
    lv_obj_clean_style_list(label, LV_LABEL_PART_MAIN);
    lv_style_set_text_letter_space(&labelStyle, LV_STATE_DEFAULT, 1);
    lv_style_set_text_letter_space(&labelStyle, LV_STATE_FOCUSED, 1);
    lv_style_set_text_font(&labelStyle, LV_STATE_DEFAULT, &MultFont_16);
    lv_style_set_text_font(&labelStyle, LV_STATE_FOCUSED, &MultFont_16);
    lv_style_set_text_color(&labelStyle, LV_STATE_DEFAULT, lv_color_make(255, 255, 255));
    lv_style_set_text_color(&labelStyle, LV_STATE_FOCUSED, lv_color_make(255, 255, 255));
    lv_style_set_text_sel_color(&labelStyle, LV_STATE_FOCUSED, lv_color_make(255, 255, 255));
    lv_style_set_text_sel_color(&labelStyle, LV_STATE_DEFAULT, lv_color_make(255, 255, 255));
    lv_style_set_text_sel_bg_color(&labelStyle, LV_STATE_FOCUSED, lv_color_make(0, 0, 255));
    lv_style_set_text_sel_bg_color(&labelStyle, LV_STATE_DEFAULT, lv_color_make(0, 0, 0));
    lv_obj_add_style(label, LV_LABEL_PART_MAIN, &labelStyle);
    //    UI_Label_Value_Style_Load(label);
    //按键
    lv_style_t *pbtnStyle = lv_obj_get_local_style(button, LV_BTN_PART_MAIN);
    static lv_style_t btnStyle = {0};
    lv_style_copy(&btnStyle, pbtnStyle);
    lv_obj_clean_style_list(button, LV_BTN_PART_MAIN);
    //    lv_style_set_bg_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(50, 50, 50));
    lv_style_set_bg_opa(&btnStyle, LV_STATE_DEFAULT, 0);
    lv_style_set_border_width(&btnStyle, LV_STATE_DEFAULT, 1);
    lv_style_set_value_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(0, 255, 255));
    lv_style_set_value_font(&btnStyle, LV_STATE_DEFAULT, &MultFont_16);
    lv_style_set_radius(&btnStyle, LV_STATE_DEFAULT, 0);
    lv_style_set_value_align(&btnStyle, LV_STATE_DEFAULT, LV_ALIGN_IN_LEFT_MID);
    lv_style_set_value_ofs_x(&btnStyle, LV_STATE_DEFAULT, 5);
    //    lv_style_set_value_opa(&btnStyle, LV_STATE_DEFAULT, 255);
    lv_obj_add_style(button, LV_BTN_PART_MAIN, &btnStyle);
    //重绘
    lv_obj_invalidate(label);
    lv_obj_invalidate(button);
}



/*
 * @brief       void TriggerPage_Enter(void)
 * @details     进入Trigger触发器页面
 */
void TriggerPage_Enter(void)
{
    lv_label_set_text_static(ui.TriggerPage_btn_Title_label, MultStr_GetS(&mStr_trigger));
    TriggerPage_SelChannel(TRIGGER_CH_D0);
    __button_refresh();
    lv_event_send_refresh_recursive(ui.TriggerPage_cont_1);
    lv_obj_set_hidden(ui.TriggerPage_cont_1, 0);
}

/*
 * @brief       void TriggerPage_Exit(void)
 * @details     退出Trigger触发器页面
 */
void TriggerPage_Exit(void)
{
    lv_obj_set_hidden(ui.TriggerPage_cont_1, 1);
}






/*
 * @brief       void Trigger_btnStyle_Init(lv_obj_t *label)
 * @details     编辑参数 按键风格初始化(无边框,标签蓝色,参数白色)
 */
void Trigger_btnStyle_Init(lv_obj_t *label)
{
    if(label == NULL) {
        return ;
    }
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
    lv_style_set_text_font(&labelStyle, LV_STATE_DEFAULT, &MultFont_16);
    lv_style_set_text_color(&labelStyle, LV_STATE_DEFAULT, lv_color_make(255, 255, 255));
    lv_style_set_text_sel_color(&labelStyle, LV_STATE_DEFAULT, lv_color_make(255, 255, 255));
    lv_style_set_text_sel_bg_color(&labelStyle, LV_STATE_DEFAULT, lv_color_make(0, 0, 0));
    lv_obj_add_style(label, LV_LABEL_PART_MAIN, &labelStyle);
    //按键
    lv_style_t *pbtnStyle = lv_obj_get_local_style(button, LV_BTN_PART_MAIN);
    static lv_style_t btnStyle = {0};
    lv_style_init(&btnStyle);
    lv_obj_clean_style_list(button, LV_BTN_PART_MAIN);
    lv_style_set_bg_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(50, 50, 50));
    lv_style_set_bg_opa(&btnStyle, LV_STATE_DEFAULT, 0);
    lv_style_set_border_width(&btnStyle, LV_STATE_DEFAULT, 1);
    lv_style_set_border_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(0, 255, 255));
    lv_style_set_value_color(&btnStyle, LV_STATE_DEFAULT, lv_color_make(0, 255, 255));
    lv_style_set_value_font(&btnStyle, LV_STATE_DEFAULT, &MultFont_16);
    lv_style_set_radius(&btnStyle, LV_STATE_DEFAULT, 0);
    lv_style_set_value_align(&btnStyle, LV_STATE_DEFAULT, LV_ALIGN_IN_LEFT_MID);
    lv_style_set_value_ofs_x(&btnStyle, LV_STATE_DEFAULT, 5);
    lv_style_set_value_opa(&btnStyle, LV_STATE_DEFAULT, 255);
    lv_obj_add_style(button, LV_BTN_PART_MAIN, &btnStyle);
    //重绘
    lv_obj_invalidate(label);
    lv_obj_invalidate(button);
}




void TriggerPage_GroupCreate(void)
{
    {
        setup_scr_TriggerPage(&ui);
        lv_obj_set_parent(ui.TriggerPage_cont_1, ui.Back_cont_back);
    }
    Trigger_btnStyle_Init(ui.TriggerPage_btn_D0_label);
    Trigger_btnStyle_Init(ui.TriggerPage_btn_D1_label);
    Trigger_btnStyle_Init(ui.TriggerPage_btn_D2_label);
    Trigger_btnStyle_Init(ui.TriggerPage_btn_D3_label);
    //
    BtnLabel_Set_Edit_Tag(ui.TriggerPage_btn_D0_label, "D0");
    BtnLabel_Set_Edit_Tag(ui.TriggerPage_btn_D1_label, "D1");
    BtnLabel_Set_Edit_Tag(ui.TriggerPage_btn_D2_label, "D2");
    BtnLabel_Set_Edit_Tag(ui.TriggerPage_btn_D3_label, "D3");
    __Param_Btn_Style_Load(ui.TriggerPage_btn_Param1_label);
    __Param_Btn_Style_Load(ui.TriggerPage_btn_Param2_label);
    __Param_Btn_Style_Load(ui.TriggerPage_btn_Param3_label);
    __Param_Btn_Style_Load(ui.TriggerPage_btn_Param4_label);
    TriggerPage_Exit();
    extern lv_font_t MultFont_16;
    lv_obj_set_style_local_text_font(ui.TriggerPage_btn_Title_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_16);
}












//刷新底部操作按键
static void __button_refresh(void)
{
    //通道
    static const struct BtnInfo_Def btn_trigger_ch = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.TriggerPage_btn_Title_label,
        .evencb = TriggerPage_ch_handler,
        .multStr = &mStr_trigger_ch,
    };
    //模式
    static const struct BtnInfo_Def btn_trigger_mode = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.TriggerPage_img_chSel,
        .evencb = TriggerPage_mode_handler,
        .multStr = &mStr_trigger_mode,
    };
    //类型
    static const struct BtnInfo_Def btn_trigger_sign = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.TriggerPage_btn_Param1_label,
        .evencb = TriggerPage_InSign_handler,
        .multStr = &mStr_trigger_sign,
    };
    //灵敏度
    static const struct BtnInfo_Def btn_trigger_sense = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.TriggerPage_btn_Param2_label,
        .evencb = TriggerPage_InSense_handler,
        .multStr = &mStr_trigger_sense,
    };
    //受控源
    static const struct BtnInfo_Def btn_trigger_insourse = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.TriggerPage_btn_Param3_label,
        .evencb = TriggerPage_InSlave_handler,
        .multStr = &mStr_trigger_insourse,
    };
    //响应
    static const struct BtnInfo_Def btn_trigger_response = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.TriggerPage_btn_Param4_label,
        .evencb = TriggerPage_InResponse_handler,
        .multStr = &mStr_trigger_response,
    };
    //触发源
    static const struct BtnInfo_Def btn_trigger_sourcce = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.TriggerPage_btn_Param1_label,
        .evencb = TriggerPage_OutSource_handler,
        .multStr = &mStr_trigger_source,
    };
    //条件
    static const struct BtnInfo_Def btn_trigger_condition = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.TriggerPage_btn_Param2_label,
        .evencb = TriggerPage_Condition_handler,
        .multStr = &mStr_trigger_condition,
    };
    //输出极性
    static const struct BtnInfo_Def btn_trigger_polarity = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.TriggerPage_btn_Param3_label,
        .evencb = TriggerPage_Polarity_handler,
        .multStr = &mStr_trigger_polarity,
    };
    if(Tree_GetChildCount(tree_trigger) < 2) {
        Tree_AddNode(tree_trigger, &btn_trigger_ch);
        Tree_AddNode(tree_trigger, &btn_trigger_mode);
    }
    Tree_Def *temp = Tree_GetItem_At(tree_trigger, 2);
    if(temp != NULL) {
        Tree_Delete(tree_trigger, temp);
    }
    SCB_CleanDCache();
    lv_obj_set_event_cb(ui.TriggerPage_btn_Param1_label, NULL);
    lv_obj_set_event_cb(ui.TriggerPage_btn_Param2_label, NULL);
    lv_obj_set_event_cb(ui.TriggerPage_btn_Param3_label, NULL);
    lv_obj_set_event_cb(ui.TriggerPage_btn_Param4_label, NULL);
    lv_obj_set_hidden(ui.TriggerPage_btn_Param1, 1);
    lv_obj_set_hidden(ui.TriggerPage_btn_Param2, 1);
    lv_obj_set_hidden(ui.TriggerPage_btn_Param3, 1);
    lv_obj_set_hidden(ui.TriggerPage_btn_Param4, 1);
    uint8_t mode = Trigger[Trigger_chSel].mode;
    switch(mode) {
        case TRIGGER_MODE_IN: {
            Tree_AddNode(tree_trigger, &btn_trigger_sourcce);
            Tree_AddNode(tree_trigger, &btn_trigger_condition);
            Tree_AddNode(tree_trigger, &btn_trigger_polarity);
            lv_obj_set_hidden(ui.TriggerPage_btn_Param1, 0);
            lv_obj_set_hidden(ui.TriggerPage_btn_Param2, 0);
            lv_obj_set_hidden(ui.TriggerPage_btn_Param3, 0);
        }
        break;
        case TRIGGER_MODE_OUT: {
            Tree_AddNode(tree_trigger, &btn_trigger_sign);
            Tree_AddNode(tree_trigger, &btn_trigger_sense);
            Tree_AddNode(tree_trigger, &btn_trigger_insourse);
            Tree_AddNode(tree_trigger, &btn_trigger_response);
            lv_obj_set_hidden(ui.TriggerPage_btn_Param1, 0);
            lv_obj_set_hidden(ui.TriggerPage_btn_Param2, 0);
            lv_obj_set_hidden(ui.TriggerPage_btn_Param3, 0);
            lv_obj_set_hidden(ui.TriggerPage_btn_Param4, 0);
        }
        break;
    }
    extern Tree_Def *Tree_UI_Set_EventCb(Tree_Def * tree);
    Tree_UI_Set_EventCb(tree_trigger);
    lv_event_send_refresh_recursive(ui.TriggerPage_cont_1);
    Tree_Btnm_Load(tree_trigger);
    SCB_CleanDCache();
}

