#include "DelayTempPage.h"
#include "DelayTemp_Interface.h"


DelayTempInfo_Def DelayTempInfo = {
    .temp_type = DELAYTEMP_TYPE_STATE,
    .startpoint = 0,
    .totalCount = DELAYOUT_MAX_COUNT,
    .code = DELAYTEMP_CODE_O1P,
    .fix = {
        .time_on = 1.0f,
        .time_off = 1.0f,
    },
    .inc_dec = {
        .time_base = 1.0f,
        .time_step = 1.0f,
    },
};

static void _generate_Wave_State(void)
{
    uint16_t startPoint = DelayTempInfo.startpoint;
    uint8_t code = DelayTempInfo.code;
    uint16_t pointCount = DelayTempInfo.totalCount;
    for(uint16_t i = 0; i < pointCount; ++i)
    {
        uint8_t out = 0;
        switch(code) {
            case DELAYTEMP_CODE_O1P:
                out = (i % 2);
                break;
            case DELAYTEMP_CODE_10P:
                out = !(i % 2);
                break;
        }
        delayoutInfo.points[startPoint + i].out = out;
    }
}

static void _generate_Wave_Fix(void)
{
    uint16_t startPoint = DelayTempInfo.startpoint;
    uint16_t pointCount = DelayTempInfo.totalCount;
    float time_on = DelayTempInfo.fix.time_on;
    float time_off = DelayTempInfo.fix.time_off;
    for(uint16_t i = 0; i < pointCount; ++i)
    {
        uint8_t out = delayoutInfo.points[startPoint + i].out;
        delayoutInfo.points[startPoint + i].dT = (out) ? time_on : time_off;
    }
}

static void _generate_Wave_Inc(void)
{
    uint16_t startPoint = DelayTempInfo.startpoint;
    uint16_t pointCount = DelayTempInfo.totalCount;
    float time_step = DelayTempInfo.inc_dec.time_step;
    float time_dt = DelayTempInfo.inc_dec.time_base;
    for(uint16_t i = 0; i < pointCount; ++i)
    {
        delayoutInfo.points[startPoint + i].dT = time_dt;
        time_dt += time_step;
    }
}

static void _generate_Wave_Dec(void)
{
    uint16_t startPoint = DelayTempInfo.startpoint;
    uint16_t pointCount = DelayTempInfo.totalCount;
    float time_step = DelayTempInfo.inc_dec.time_step;
    float time_dt = DelayTempInfo.inc_dec.time_base;
    for(uint16_t i = 0; i < pointCount; ++i)
    {
        delayoutInfo.points[startPoint + i].dT = time_dt;
        time_dt -= time_step;
    }
}

void Delay_Temp_Generate(void)
{
    switch(DelayTempInfo.temp_type) {
        case DELAYTEMP_TYPE_STATE: {
            _generate_Wave_State();
        }
        break;
        case DELAYTEMP_TYPE_FIXT: {
            _generate_Wave_Fix();
        }
        break;
        case DELAYTEMP_TYPE_INCT: {
            _generate_Wave_Inc();
        }
        break;
        case DELAYTEMP_TYPE_DECT: {
            _generate_Wave_Dec();
        }
        break;
    }
    if(lv_obj_is_visible(ui.DelayPage_cont_Table) != 0) {
        lv_event_send_refresh_recursive(ui.DelayPage_cont_Table);
    }
}





static void __button_refresh(void);





void Delay_Temp_Cont_EventHandler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    switch(event) {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key) {
                case LV_KEY_UP: {
                    DelayTempInfo.temp_type++;
                    if(DelayTempInfo.temp_type > DELAYTEMP_TYPE_MAX) {
                        DelayTempInfo.temp_type = DELAYTEMP_TYPE_MAX;
                    }
                    __button_refresh();
                }
                break;
                case LV_KEY_DOWN: {
                    DelayTempInfo.temp_type--;
                    if(DelayTempInfo.temp_type < DELAYTEMP_TYPE_MIN) {
                        DelayTempInfo.temp_type = DELAYTEMP_TYPE_MIN;
                    }
                    __button_refresh();
                }
                break;
            }
        }
        break;
    }
}



/*
 * @brief       void DelayTempPage_Enter(void)
 * @details     进入Delay模板页面
 */
void DelayTempPage_Enter(void)
{
    lv_obj_set_hidden(ui.DelayTempPage_cont_1, 0);
    UI_IF_DelayTemp_Set_Type(DELAYTEMP_TYPE_STATE);
    lv_event_send_refresh_recursive(ui.DelayTempPage_cont_1);
    BtnLabel_Set_Edit_Value(ui.DelayTempPage_btn_title_label, MultStr_GetS(&mStr_delay_temp));
    BtnLabel_Set_Edit_Value(ui.DelayTempPage_btn_state_label, MultStr_GetS(&mStr_delay_temp_Type_State));
    BtnLabel_Set_Edit_Value(ui.DelayTempPage_btn_fixT_label, MultStr_GetS(&mStr_delay_temp_Type_Fix));
    BtnLabel_Set_Edit_Value(ui.DelayTempPage_btn_incT_label, MultStr_GetS(&mStr_delay_temp_Type_Inc));
    BtnLabel_Set_Edit_Value(ui.DelayTempPage_btn_decT_label, MultStr_GetS(&mStr_delay_temp_Type_Dec));
}

/*
 * @brief       void DelayTempPage_Exit(void)
 * @details     退出Delay模板页面
 */
void DelayTempPage_Exit(void)
{
    lv_obj_set_hidden(ui.DelayTempPage_cont_1, 1);
}

extern void DelayTempPage_btnStyle_Init(lv_obj_t *label);
void DelayTempPage_GroupCreate(void)
{
    {
        setup_scr_DelayTempPage(&ui);
        lv_obj_set_parent(ui.DelayTempPage_cont_1, ui.Back_cont_back);
        lv_obj_set_top(ui.DelayTempPage_cont_1, 1);
    }
    extern lv_font_t MultFont_16;
    lv_obj_set_style_local_text_font(ui.DelayTempPage_btn_title_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_16);
    lv_obj_set_style_local_text_font(ui.DelayTempPage_btn_state_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_16);
    lv_obj_set_style_local_text_font(ui.DelayTempPage_btn_fixT_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_16);
    lv_obj_set_style_local_text_font(ui.DelayTempPage_btn_incT_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_16);
    lv_obj_set_style_local_text_font(ui.DelayTempPage_btn_decT_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_16);
    //类型
    DelayTempPage_btnStyle_Init(ui.DelayTempPage_btn_start_label);
    DelayTempPage_btnStyle_Init(ui.DelayTempPage_btn_count_label);
    //参数
    DelayTempPage_btnStyle_Init(ui.DelayTempPage_btn_param1_label);
    DelayTempPage_btnStyle_Init(ui.DelayTempPage_btn_param2_label);
    DelayTempPage_Exit();
}




void __set_Sel(lv_obj_t *obj)
{
    lv_obj_t *img_Sel = ui.DelayTempPage_img_sel;
    if(obj == NULL) {
        lv_obj_set_hidden(img_Sel, 1);
        return ;
    } else {
        lv_obj_set_hidden(img_Sel, 0);
    }
    uint16_t width = lv_obj_get_width(obj);
    uint16_t height = lv_obj_get_height(obj);
    uint16_t x = lv_obj_get_x(obj);
    uint16_t y = lv_obj_get_y(obj);
    lv_obj_set_pos(img_Sel, x, y);
    lv_obj_set_width(img_Sel, width);
    lv_obj_set_height(img_Sel, height);
}

/*
 * @brief       void Delay_Temp_Set_Type(uint8_t tpye)
 * @details     设置Delay模板类型
 */
void Delay_Temp_Set_Type(uint8_t tpye)
{
    DelayTempInfo.temp_type = tpye;
    if(0 != lv_obj_is_visible(ui.DelayTempPage_cont_1)) {
        __button_refresh();
    }
}


/*
 * @brief       void Delay_Temp_Type_EventHandler(lv_obj_t *obj, lv_event_t event)
 * @details     模板类型选择
 */
void Delay_Temp_Type_EventHandler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    switch(event) {
        case LV_EVENT_CLICKED: {
            DelayTempInfo.temp_type += 1;
            if(DelayTempInfo.temp_type > DELAYTEMP_TYPE_MAX) {
                DelayTempInfo.temp_type = DELAYTEMP_TYPE_MIN;
            }
            UI_IF_DelayTemp_Set_Type(DelayTempInfo.temp_type);
            GUI_SEND_KEY(LV_KEY_RETURN);
        }
        case LV_EVENT_REFRESH: {
            switch(DelayTempInfo.temp_type) {
                case DELAYTEMP_TYPE_STATE:
                    __set_Sel(ui.DelayTempPage_btn_state);
                    break;
                case DELAYTEMP_TYPE_FIXT:
                    __set_Sel(ui.DelayTempPage_btn_fixT);
                    break;
                case DELAYTEMP_TYPE_INCT:
                    __set_Sel(ui.DelayTempPage_btn_incT);
                    break;
                case DELAYTEMP_TYPE_DECT:
                    __set_Sel(ui.DelayTempPage_btn_decT);
                    break;
            }
        }
        break;
    }
}




/*
 * @brief       void Delay_Temp_Code_EventHandler(lv_obj_t *obj, lv_event_t event)
 * @details     模板类型选择
 */
void Delay_Temp_Code_EventHandler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    switch(event) {
        case LV_EVENT_CLICKED: {
            DelayTempInfo.code += 1;
            if(DelayTempInfo.code > DELAYTEMP_CODE_MAX) {
                DelayTempInfo.code = DELAYTEMP_CODE_MIN;
            }
            UI_IF_DelayTemp_Set_Code(DelayTempInfo.code);
            GUI_SEND_KEY(LV_KEY_RETURN);
        }
        case LV_EVENT_REFRESH: {
            BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_delay_temp_Code));
            switch(DelayTempInfo.code) {
                case DELAYTEMP_CODE_O1P:
                    lv_label_set_text_static(obj, "01P");
                    break;
                case DELAYTEMP_CODE_10P:
                    lv_label_set_text_static(obj, "10P");
                    break;
            }
        }
        break;
    }
}


/*
 * @brief       void Delay_Temp_Start_EventHandler(lv_obj_t *obj, lv_event_t event)
 * @details     模板生成起点
 */
static void Start_RefreshUI(lv_obj_t *obj, uint8_t *editIndex) {
    if(editIndex == NULL) {
        lv_obj_set_state(obj, LV_STATE_DEFAULT);
    } else {
        lv_obj_set_state(obj, LV_STATE_FOCUSED);
    }
    static char stringSet[64] = {0};
    sprintf(stringSet, POINT_DISP_FORM, DelayTempInfo.startpoint);
    if(editIndex != NULL) {
        label_setSelNum(obj, *editIndex, stringSet);
    } else {
        lv_label_set_text_sel_start(obj, LV_LABEL_TEXT_SEL_OFF);
        lv_label_set_text_sel_end(obj, LV_LABEL_TEXT_SEL_OFF);
    }
    lv_label_set_text_static(obj, stringSet);
}
void Delay_Temp_Start_EventHandler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    static uint8_t enditIndex = 0 ;
    NumberInput_Process(7, UI_IF_DelayTemp_Set_Start);
    switch(event) {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key) {
                case LV_KEY_UP: {
                    int32_t temp = DelayTempInfo.startpoint;
                    temp += point_step[enditIndex];
                    UI_IF_DelayTemp_Set_Start(temp);
                }
                break;
                case LV_KEY_DOWN: {
                    int32_t temp = DelayTempInfo.startpoint;
                    temp -= point_step[enditIndex];
                    UI_IF_DelayTemp_Set_Start(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(enditIndex > 0)
                    {
                        enditIndex--;
                    }
                    else
                    {
                        enditIndex = sizeof(point_step) / sizeof(point_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_ENCODER:
                case LV_KEY_ENTER:
                case LV_KEY_LEFT: {
                    if(enditIndex < (sizeof(point_step) / sizeof(point_step[0]) - 1))
                    {
                        enditIndex++;
                    }
                    else
                    {
                        enditIndex = 0;
                    }
                }
                break;
            }
            if(key != LV_KEY_ESC) {
                //更新显示选定 & 步进位
                Start_RefreshUI(obj, &enditIndex);
            } else {
                Start_RefreshUI(obj, NULL);
            }
        }
        break;
        case LV_EVENT_REFRESH: {
            BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_delay_temp_Start));
            Start_RefreshUI(obj, NULL);
        }
        break;
        case LV_EVENT_CLICKED: {
            enditIndex = 0;
            Start_RefreshUI(obj, &enditIndex);
        }
        break;
    }
}

/*
 * @brief       void Delay_Temp_Count_EventHandler(lv_obj_t *obj, lv_event_t event)
 * @details     模板生成总数
 */
static void Count_RefreshUI(lv_obj_t *obj, uint8_t *editIndex) {
    if(editIndex == NULL) {
        lv_obj_set_state(obj, LV_STATE_DEFAULT);
    } else {
        lv_obj_set_state(obj, LV_STATE_FOCUSED);
    }
    static char stringSet[64] = {0};
    sprintf(stringSet, POINT_DISP_FORM, DelayTempInfo.totalCount);
    if(editIndex != NULL) {
        label_setSelNum(obj, *editIndex, stringSet);
    } else {
        lv_label_set_text_sel_start(obj, LV_LABEL_TEXT_SEL_OFF);
        lv_label_set_text_sel_end(obj, LV_LABEL_TEXT_SEL_OFF);
    }
    lv_label_set_text_static(obj, stringSet);
}
void Delay_Temp_Count_EventHandler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    static uint8_t enditIndex = 0 ;
    NumberInput_Process(7, UI_IF_DelayTemp_Set_Count);
    switch(event) {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key) {
                case LV_KEY_UP: {
                    int32_t temp = DelayTempInfo.totalCount;
                    temp += point_step[enditIndex];
                    UI_IF_DelayTemp_Set_Count(temp);
                }
                break;
                case LV_KEY_DOWN: {
                    int32_t temp = DelayTempInfo.totalCount;
                    temp -= point_step[enditIndex];
                    UI_IF_DelayTemp_Set_Count(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(enditIndex > 0)
                    {
                        enditIndex--;
                    }
                    else
                    {
                        enditIndex = sizeof(point_step) / sizeof(point_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_ENCODER:
                case LV_KEY_ENTER:
                case LV_KEY_LEFT: {
                    if(enditIndex < (sizeof(point_step) / sizeof(point_step[0]) - 1))
                    {
                        enditIndex++;
                    }
                    else
                    {
                        enditIndex = 0;
                    }
                }
                break;
            }
            if(key != LV_KEY_ESC) {
                //更新显示选定 & 步进位
                Count_RefreshUI(obj, &enditIndex);
            } else {
                Count_RefreshUI(obj, NULL);
            }
        }
        break;
        case LV_EVENT_REFRESH: {
            BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_delay_temp_Groups));
            Count_RefreshUI(obj, NULL);
        }
        break;
        case LV_EVENT_CLICKED: {
            enditIndex = 0;
            Count_RefreshUI(obj, &enditIndex);
        }
        break;
    }
}









/*
 * @brief       void Delay_Temp_Ton_EventHandler(lv_obj_t *obj, lv_event_t event)
 * @details     模板打开时间设置
 */
static void Ton_RefreshUI(lv_obj_t *obj, uint8_t *editIndex) {
    if(editIndex == NULL) {
        lv_obj_set_state(obj, LV_STATE_DEFAULT);
    } else {
        lv_obj_set_state(obj, LV_STATE_FOCUSED);
    }
    static char stringSet[64] = {0};
    sprintf(stringSet, DELAY_TIME_FORM"s", DelayTempInfo.fix.time_on);
    if(editIndex != NULL) {
        label_setSelNum(obj, *editIndex, stringSet);
    } else {
        lv_label_set_text_sel_start(obj, LV_LABEL_TEXT_SEL_OFF);
        lv_label_set_text_sel_end(obj, LV_LABEL_TEXT_SEL_OFF);
    }
    lv_label_set_text_static(obj, stringSet);
}
void Delay_Temp_Ton_EventHandler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    static uint8_t enditIndex = 0 ;
    NumberInput_Process(7, UI_IF_DelayTemp_Set_Ton);
    switch(event) {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key) {
                case LV_KEY_UP: {
                    float temp = DelayTempInfo.fix.time_on;
                    temp += dT_step[enditIndex];
                    UI_IF_DelayTemp_Set_Ton(temp);
                }
                break;
                case LV_KEY_DOWN: {
                    float temp = DelayTempInfo.fix.time_on;
                    temp -= dT_step[enditIndex];
                    UI_IF_DelayTemp_Set_Ton(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(enditIndex > 0)
                    {
                        enditIndex--;
                    }
                    else
                    {
                        enditIndex = sizeof(dT_step) / sizeof(dT_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_ENCODER:
                case LV_KEY_ENTER:
                case LV_KEY_LEFT: {
                    if(enditIndex < (sizeof(dT_step) / sizeof(dT_step[0]) - 1))
                    {
                        enditIndex++;
                    }
                    else
                    {
                        enditIndex = 0;
                    }
                }
                break;
            }
            if(key != LV_KEY_ESC) {
                //更新显示选定 & 步进位
                Ton_RefreshUI(obj, &enditIndex);
            } else {
                Ton_RefreshUI(obj, NULL);
            }
        }
        break;
        case LV_EVENT_REFRESH: {
            BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_delay_temp_Ton));
            Ton_RefreshUI(obj, NULL);
        }
        break;
        case LV_EVENT_CLICKED: {
            enditIndex = 0;
            Ton_RefreshUI(obj, &enditIndex);
        }
        break;
    }
}




/*
 * @brief       void Delay_Temp_Toff_EventHandler(lv_obj_t *obj, lv_event_t event)
 * @details     模板关闭时间设置
 */
static void Toff_RefreshUI(lv_obj_t *obj, uint8_t *editIndex) {
    if(editIndex == NULL) {
        lv_obj_set_state(obj, LV_STATE_DEFAULT);
    } else {
        lv_obj_set_state(obj, LV_STATE_FOCUSED);
    }
    static char stringSet[64] = {0};
    sprintf(stringSet, DELAY_TIME_FORM"s", DelayTempInfo.fix.time_off);
    if(editIndex != NULL) {
        label_setSelNum(obj, *editIndex, stringSet);
    } else {
        lv_label_set_text_sel_start(obj, LV_LABEL_TEXT_SEL_OFF);
        lv_label_set_text_sel_end(obj, LV_LABEL_TEXT_SEL_OFF);
    }
    lv_label_set_text_static(obj, stringSet);
}
void Delay_Temp_Toff_EventHandler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    static uint8_t enditIndex = 0 ;
    NumberInput_Process(7, UI_IF_DelayTemp_Set_Toff);
    switch(event) {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key) {
                case LV_KEY_UP: {
                    float temp = DelayTempInfo.fix.time_off;
                    temp += dT_step[enditIndex];
                    UI_IF_DelayTemp_Set_Toff(temp);
                }
                break;
                case LV_KEY_DOWN: {
                    float temp = DelayTempInfo.fix.time_off;
                    temp -= dT_step[enditIndex];
                    UI_IF_DelayTemp_Set_Toff(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(enditIndex > 0)
                    {
                        enditIndex--;
                    }
                    else
                    {
                        enditIndex = sizeof(dT_step) / sizeof(dT_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_ENCODER:
                case LV_KEY_ENTER:
                case LV_KEY_LEFT: {
                    if(enditIndex < (sizeof(dT_step) / sizeof(dT_step[0]) - 1))
                    {
                        enditIndex++;
                    }
                    else
                    {
                        enditIndex = 0;
                    }
                }
                break;
            }
            if(key != LV_KEY_ESC) {
                //更新显示选定 & 步进位
                Toff_RefreshUI(obj, &enditIndex);
            } else {
                Toff_RefreshUI(obj, NULL);
            }
        }
        break;
        case LV_EVENT_REFRESH: {
            BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_delay_temp_Toff));
            Toff_RefreshUI(obj, NULL);
        }
        break;
        case LV_EVENT_CLICKED: {
            enditIndex = 0;
            Toff_RefreshUI(obj, &enditIndex);
        }
        break;
    }
}










/*
 * @brief       void Delay_Temp_TBase_EventHandler(lv_obj_t *obj, lv_event_t event)
 * @details     模板基本时间设置
 */
static void Base_RefreshUI(lv_obj_t *obj, uint8_t *editIndex) {
    if(editIndex == NULL) {
        lv_obj_set_state(obj, LV_STATE_DEFAULT);
    } else {
        lv_obj_set_state(obj, LV_STATE_FOCUSED);
    }
    static char stringSet[64] = {0};
    sprintf(stringSet, DELAY_TIME_FORM"s", DelayTempInfo.inc_dec.time_base);
    if(editIndex != NULL) {
        label_setSelNum(obj, *editIndex, stringSet);
    } else {
        lv_label_set_text_sel_start(obj, LV_LABEL_TEXT_SEL_OFF);
        lv_label_set_text_sel_end(obj, LV_LABEL_TEXT_SEL_OFF);
    }
    lv_label_set_text_static(obj, stringSet);
}
void Delay_Temp_Base_EventHandler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    static uint8_t enditIndex = 0 ;
    NumberInput_Process(7, UI_IF_DelayTemp_Set_Base);
    switch(event) {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key) {
                case LV_KEY_UP: {
                    float temp = DelayTempInfo.inc_dec.time_base;
                    temp += dT_step[enditIndex];
                    UI_IF_DelayTemp_Set_Base(temp);
                }
                break;
                case LV_KEY_DOWN: {
                    float temp = DelayTempInfo.inc_dec.time_base;
                    temp -= dT_step[enditIndex];
                    UI_IF_DelayTemp_Set_Base(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(enditIndex > 0)
                    {
                        enditIndex--;
                    }
                    else
                    {
                        enditIndex = sizeof(dT_step) / sizeof(dT_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_ENCODER:
                case LV_KEY_ENTER:
                case LV_KEY_LEFT: {
                    if(enditIndex < (sizeof(dT_step) / sizeof(dT_step[0]) - 1))
                    {
                        enditIndex++;
                    }
                    else
                    {
                        enditIndex = 0;
                    }
                }
                break;
            }
            if(key != LV_KEY_ESC) {
                //更新显示选定 & 步进位
                Base_RefreshUI(obj, &enditIndex);
            } else {
                Base_RefreshUI(obj, NULL);
            }
        }
        break;
        case LV_EVENT_REFRESH: {
            BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_delay_temp_Tbase));
            Base_RefreshUI(obj, NULL);
        }
        break;
        case LV_EVENT_CLICKED: {
            enditIndex = 0;
            Base_RefreshUI(obj, &enditIndex);
        }
        break;
    }
}


/*
 * @brief       void Delay_Temp_Step_EventHandler(lv_obj_t *obj, lv_event_t event)
 * @details     模板步进时间设置
 */
static void Step_RefreshUI(lv_obj_t *obj, uint8_t *editIndex) {
    if(editIndex == NULL) {
        lv_obj_set_state(obj, LV_STATE_DEFAULT);
    } else {
        lv_obj_set_state(obj, LV_STATE_FOCUSED);
    }
    static char stringSet[64] = {0};
    sprintf(stringSet, DELAY_TIME_FORM"s", DelayTempInfo.inc_dec.time_step);
    if(editIndex != NULL) {
        label_setSelNum(obj, *editIndex, stringSet);
    } else {
        lv_label_set_text_sel_start(obj, LV_LABEL_TEXT_SEL_OFF);
        lv_label_set_text_sel_end(obj, LV_LABEL_TEXT_SEL_OFF);
    }
    lv_label_set_text_static(obj, stringSet);
}
void Delay_Temp_Step_EventHandler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    static uint8_t enditIndex = 0 ;
    NumberInput_Process(7, UI_IF_DelayTemp_Set_Step);
    switch(event) {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key) {
                case LV_KEY_UP: {
                    float temp = DelayTempInfo.inc_dec.time_step;
                    temp += dT_step[enditIndex];
                    UI_IF_DelayTemp_Set_Step(temp);
                }
                break;
                case LV_KEY_DOWN: {
                    float temp = DelayTempInfo.inc_dec.time_step;
                    temp -= dT_step[enditIndex];
                    UI_IF_DelayTemp_Set_Step(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(enditIndex > 0)
                    {
                        enditIndex--;
                    }
                    else
                    {
                        enditIndex = sizeof(dT_step) / sizeof(dT_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_ENCODER:
                case LV_KEY_ENTER:
                case LV_KEY_LEFT: {
                    if(enditIndex < (sizeof(dT_step) / sizeof(dT_step[0]) - 1))
                    {
                        enditIndex++;
                    }
                    else
                    {
                        enditIndex = 0;
                    }
                }
                break;
            }
            if(key != LV_KEY_ESC) {
                //更新显示选定 & 步进位
                Step_RefreshUI(obj, &enditIndex);
            } else {
                Step_RefreshUI(obj, NULL);
            }
        }
        break;
        case LV_EVENT_REFRESH: {
            BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_delay_temp_Tstep));
            Step_RefreshUI(obj, NULL);
        }
        break;
        case LV_EVENT_CLICKED: {
            enditIndex = 0;
            Step_RefreshUI(obj, &enditIndex);
        }
        break;
    }
}





static void Delay_Temp_GenerateCall(void)
{
    //    GUI_SEND_KEY(LV_KEY_RETURN);
    UI_IF_DelayTemp_Generate();
}





#include "btnTree.h"
extern Tree_Def *tree_delay_temp;
//刷新底部操作按键
static void __button_refresh(void)
{
    //类型
    static const struct BtnInfo_Def btn_delay_temp_type = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.DelayTempPage_img_sel,
        .evencb = Delay_Temp_Type_EventHandler,
        .multStr = &mStr_delay_temp_Type,
    };
    //起始点
    static const struct BtnInfo_Def btn_delay_temp_start = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.DelayTempPage_btn_start_label,
        .evencb = Delay_Temp_Start_EventHandler,
        .multStr = &mStr_delay_temp_Start,
    };
    //总点数
    static const struct BtnInfo_Def btn_delay_temp_count = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.DelayTempPage_btn_count_label,
        .evencb = Delay_Temp_Count_EventHandler,
        .multStr = &mStr_delay_temp_Groups,
    };
    //生成
    static const struct BtnInfo_Def btn_delay_temp_generate = {
        .type = BTN_TYPE_CALL,
        .call = Delay_Temp_GenerateCall,
        .multStr = &mStr_delay_temp_Generate,
    };
    //波形码
    static const struct BtnInfo_Def btn_delay_temp_code = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.DelayTempPage_btn_param1_label,
        .evencb = Delay_Temp_Code_EventHandler,
        .multStr = &mStr_delay_temp_Code,
    };
    //打开时长
    static const struct BtnInfo_Def btn_delay_temp_ton = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.DelayTempPage_btn_param1_label,
        .evencb = Delay_Temp_Ton_EventHandler,
        .multStr = &mStr_delay_temp_Ton,
    };
    //关断时长
    static const struct BtnInfo_Def btn_delay_temp_toff = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.DelayTempPage_btn_param2_label,
        .evencb = Delay_Temp_Toff_EventHandler,
        .multStr = &mStr_delay_temp_Toff,
    };
    //基础时长
    static const struct BtnInfo_Def btn_delay_temp_tbase = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.DelayTempPage_btn_param1_label,
        .evencb = Delay_Temp_Base_EventHandler,
        .multStr = &mStr_delay_temp_Tbase,
    };
    //步进时长
    static const struct BtnInfo_Def btn_delay_temp_tstep = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.DelayTempPage_btn_param2_label,
        .evencb = Delay_Temp_Step_EventHandler,
        .multStr = &mStr_delay_temp_Tstep,
    };
    if(tree_delay_temp->child != NULL) {
        Tree_Delete(tree_delay_temp, tree_delay_temp->child);
    }
    lv_obj_set_event_cb(ui.DelayTempPage_btn_param1_label, NULL);
    lv_obj_set_event_cb(ui.DelayTempPage_btn_param2_label, NULL);
    lv_obj_set_hidden(ui.DelayTempPage_btn_param1, 1);
    lv_obj_set_hidden(ui.DelayTempPage_btn_param2, 1);
    Tree_AddNode(tree_delay_temp, &btn_delay_temp_type);
    Tree_AddNode(tree_delay_temp, &btn_delay_temp_start);
    Tree_AddNode(tree_delay_temp, &btn_delay_temp_count);
    Tree_AddNode(tree_delay_temp, &btn_delay_temp_generate);
    uint8_t type = DelayTempInfo.temp_type;
    switch(type) {
        case DELAYTEMP_TYPE_STATE: {
            Tree_AddNode(tree_delay_temp, &btn_delay_temp_code);
            lv_obj_set_hidden(ui.DelayTempPage_btn_param1, 0);
        }
        break;
        case DELAYTEMP_TYPE_FIXT: {
            Tree_AddNode(tree_delay_temp, &btn_delay_temp_ton);
            Tree_AddNode(tree_delay_temp, &btn_delay_temp_toff);
            lv_obj_set_hidden(ui.DelayTempPage_btn_param1, 0);
            lv_obj_set_hidden(ui.DelayTempPage_btn_param2, 0);
        }
        break;
        case DELAYTEMP_TYPE_INCT:
        case DELAYTEMP_TYPE_DECT: {
            Tree_AddNode(tree_delay_temp, &btn_delay_temp_tbase);
            Tree_AddNode(tree_delay_temp, &btn_delay_temp_tstep);
            lv_obj_set_hidden(ui.DelayTempPage_btn_param1, 0);
            lv_obj_set_hidden(ui.DelayTempPage_btn_param2, 0);
        }
        break;
    }
    extern Tree_Def *Tree_UI_Set_EventCb(Tree_Def * tree);
    Tree_UI_Set_EventCb(tree_delay_temp);
    lv_event_send_refresh_recursive(ui.DelayTempPage_cont_1);
    Tree_Btnm_Load(tree_delay_temp);
}




