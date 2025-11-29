#include "HomePage.h"
#include "ListOut.h"

#include "SettingData.h"

#include "Interface.h"
#include "InputWidget.h"


#include "DAC8562_Device.h"
#include "PowerTask.h"

Tree_Def *tree_home;
Tree_Def *tree_VSet;
Tree_Def *tree_ISet;
Tree_Def *tree_Vlimit;
Tree_Def *tree_Ilimit;
Tree_Def *tree_TimeOff;



/*!
 * @brief   校准�?
 */
static double calibVol = 0;
static void CalibVol_CallBack(void)
{
    UI_IF_Power_Calib_Vol(calibVol);
}
static double calibAmp = 0;
static void CalibAmp_CallBack(void)
{
    UI_IF_Power_Calib_Amp(calibAmp);
}
static double calibDVM = 0;
static void CalibDVM_CallBack(void)
{
    UI_IF_Power_Calib_Dvm(calibDVM);
}


static char stringSet[64] = {0};
static void Set_RefreshUI(lv_obj_t *obj, uint8_t *editIndex, const char *dispfmt, double value)
{
    if(obj == NULL) {
        return ;
    }
    //
    sprintf(stringSet, dispfmt, value);
    if(editIndex != NULL) {
        label_setSelNum(obj, *editIndex, stringSet);
    } else {
    }
    lv_label_set_text(obj, stringSet);
    //
    if(editIndex == NULL) {
        lv_obj_set_state(obj, LV_STATE_DEFAULT);
        lv_label_set_text_sel_start(obj, LV_LABEL_TEXT_SEL_OFF);
        lv_label_set_text_sel_end(obj, LV_LABEL_TEXT_SEL_OFF);
    } else {
        lv_obj_set_state(obj, LV_STATE_FOCUSED);
    }
}

void volSet_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    static uint8_t index_v = 0;
    NumberInput_Process(7, UI_IF_Power_SetVol);
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key) {
                case LV_KEY_UP: {
                    double temp = IF_Power_Get_SetVol();
                    temp += V_step[index_v];
                    UI_IF_Power_SetVol(temp);
                }
                break;
                case LV_KEY_DOWN: {
                    double temp = IF_Power_Get_SetVol();
                    temp -= V_step[index_v];
                    UI_IF_Power_SetVol(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(index_v > 0)
                    {
                        index_v--;
                    }
                    else
                    {
                        index_v = sizeof(V_step) / sizeof(V_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(index_v < (sizeof(V_step) / sizeof(V_step[0]) - 1))
                    {
                        index_v++;
                    }
                    else
                    {
                        index_v = 0;
                    }
                }
                break;
                //校准�?
                case LV_KEY_ESC_LONGP: {
                    if(POWER_CALIB_MODE == 1) {
                        UI_IF_Power_Calib_Delete("VOLT");
                    }
                }
                break;
                case LV_KEY_ENCODER_LONGP:
                case LV_KEY_ENTER: {
                    if(POWER_CALIB_MODE == 1) {
                        calibVol = IF_Power_Get_SetVol();
                        InputVal_DoubleEdit(&mStr_CalibVol_Title, &calibVol, VOL_CALIB_FORM,
                                            V_Calib_step, ARRAY_COUNT(V_Calib_step),
                                            VOL_MAX, VOL_MIN, NULL, NULL, CalibVol_CallBack);
                        break;
                    }
                }
                break;
                case LV_KEY_ESC:
                    Set_RefreshUI(obj, NULL, VOL_SET_FORM, IF_Power_Get_SetVol());
                    return;
                default:
                    break;
            }
        }
        break;
        case LV_EVENT_REFRESH:
        case LV_EVENT_FOCUSED: {
            Set_RefreshUI(obj, NULL, VOL_SET_FORM, IF_Power_Get_SetVol());
        }
        return;
        case LV_EVENT_CLICKED: {
        }
        break;
    }
    Set_RefreshUI(obj, &index_v, VOL_SET_FORM, IF_Power_Get_SetVol());
}

void ampSet_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    static uint8_t index_a = 0;
    NumberInput_Process(7, UI_IF_Power_SetAmp);
    switch(event)
    {
        case LV_EVENT_KEY:
        {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                case LV_KEY_UP: {
                    double temp = IF_Power_Get_SetAmp();
                    temp += A_step[index_a];
                    UI_IF_Power_SetAmp(temp);
                }
                break;
                case LV_KEY_DOWN: {
                    double temp = IF_Power_Get_SetAmp();
                    temp -= A_step[index_a];
                    UI_IF_Power_SetAmp(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(index_a > 0)
                    {
                        index_a--;
                    }
                    else
                    {
                        index_a = sizeof(A_step) / sizeof(A_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(index_a < (sizeof(A_step) / sizeof(A_step[0]) - 1))
                    {
                        index_a++;
                    }
                    else
                    {
                        index_a = 0;
                    }
                }
                break;
                //校准�?
                case LV_KEY_ESC_LONGP: {
                    if(POWER_CALIB_MODE == 1) {
                        UI_IF_Power_Calib_Delete("CURR");
                    }
                }
                break;
                case LV_KEY_ENCODER_LONGP:
                case LV_KEY_ENTER: {
                    if(POWER_CALIB_MODE == 1) {
                        calibAmp = IF_Power_Get_SetAmp();
                        InputVal_DoubleEdit(&mStr_CalibAmp_Title, &calibAmp, AMP_CALIB_FORM,
                                            A_Calib_step, sizeof(A_Calib_step) / sizeof(A_Calib_step[0]),
                                            AMP_MAX, AMP_MIN, NULL, NULL, CalibAmp_CallBack);
                        break;
                    }
                }
                break;
                case LV_KEY_ESC:
                    Set_RefreshUI(obj, NULL, AMP_SET_FORM, IF_Power_Get_SetAmp());
                    return;
                default:
                    break;
            }
        }
        break;
        case LV_EVENT_REFRESH:
        case LV_EVENT_FOCUSED: {
            Set_RefreshUI(obj, NULL, AMP_SET_FORM, IF_Power_Get_SetAmp());
        }
        return;
        case LV_EVENT_CLICKED: {
        }
        break;
    }
    Set_RefreshUI(obj, &index_a, AMP_SET_FORM, IF_Power_Get_SetAmp());
}

/* ------------------------------------------------------------------ */
void volLimit_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    static uint8_t index_v = 0;
    NumberInput_Process(6, UI_IF_Power_SetOVP);
    if(IF_Power_GetOVP_onoff() != 0) {
        lv_obj_set_hidden(ui.HomePage_img_OVP_OFF, 1);
        lv_obj_set_hidden(ui.HomePage_img_OVP_ON, 0);
        //
        lv_obj_set_hidden(ui.HomePage2_img_OVP_OFF, 1);
        lv_obj_set_hidden(ui.HomePage2_img_OVP_ON, 0);
    }
    else {
        lv_obj_set_hidden(ui.HomePage_img_OVP_OFF, 0);
        lv_obj_set_hidden(ui.HomePage_img_OVP_ON, 1);
        //
        lv_obj_set_hidden(ui.HomePage2_img_OVP_OFF, 0);
        lv_obj_set_hidden(ui.HomePage2_img_OVP_ON, 1);
    }
    static uint8_t editFlag = 0;
    switch(event)
    {
        case LV_EVENT_KEY:
        {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                case LV_KEY_ENCODER_LONGP: {
                    UI_IF_Power_SetOVP_onoff(!IF_Power_GetOVP_onoff());
                }
                break;
                case LV_KEY_UP: {
                    float temp = IF_Power_GetOVP();
                    temp += V_step[index_v];
                    if(temp > VOL_MAX) {
                        temp = VOL_MAX;
                        IF_MsgBox_Tips_Mult(&mStr_OutSet_MaxVol);
                    }
                    UI_IF_Power_SetOVP(temp);
                }
                break;
                case LV_KEY_DOWN: {
                    float temp = IF_Power_GetOVP();
                    temp -= V_step[index_v];
                    if(temp < VOL_MIN) {
                        temp = VOL_MIN;
                    }
                    UI_IF_Power_SetOVP(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(index_v > 0)
                    {
                        index_v--;
                    }
                    else
                    {
                        index_v = sizeof(V_step) / sizeof(V_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(index_v < (sizeof(V_step) / sizeof(V_step[0]) - 1))
                    {
                        index_v++;
                    }
                    else
                    {
                        index_v = 0;
                    }
                }
                break;
                default:
                    break;
            }
            if(key != LV_KEY_ESC) {
                Set_RefreshUI(obj, &index_v, VOL_LIMIT_FORM, IF_Power_GetOVP());
            } else {
                editFlag = 0;
                Set_RefreshUI(obj, NULL, VOL_LIMIT_FORM, IF_Power_GetOVP());
                return;
            }
        }
        break;
        case LV_EVENT_DEFOCUSED:
            editFlag = 0;
            break;
        case LV_EVENT_FOCUSED: {
            if(editFlag == 1) {
                UI_IF_Power_SetOVP_onoff(!IF_Power_GetOVP_onoff());
            }
            editFlag = 1;
        }
        break;
        case LV_EVENT_REFRESH: {
            Set_RefreshUI(obj, NULL, VOL_LIMIT_FORM, IF_Power_GetOVP());
        }
        break;
        case LV_EVENT_CLICKED: {
            Set_RefreshUI(obj, &index_v, VOL_LIMIT_FORM, IF_Power_GetOVP());
        }
        break;
    }
}

void ampLimit_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    static uint8_t index_a = 0;
    NumberInput_Process(6, UI_IF_Power_SetOCP);
    if(IF_Power_GetOCP_onoff() != 0) {
        lv_obj_set_hidden(ui.HomePage_img_OCP_OFF, 1);
        lv_obj_set_hidden(ui.HomePage_img_OCP_ON, 0);
        lv_obj_set_hidden(ui.HomePage2_img_OCP_OFF, 1);
        lv_obj_set_hidden(ui.HomePage2_img_OCP_ON, 0);
    } else {
        lv_obj_set_hidden(ui.HomePage_img_OCP_OFF, 0);
        lv_obj_set_hidden(ui.HomePage_img_OCP_ON, 1);
        lv_obj_set_hidden(ui.HomePage2_img_OCP_OFF, 0);
        lv_obj_set_hidden(ui.HomePage2_img_OCP_ON, 1);
    }
    static uint8_t editFlag = 0;
    switch(event)
    {
        case LV_EVENT_KEY:
        {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                case LV_KEY_ENCODER_LONGP: {
                    UI_IF_Power_SetOCP_onoff(!IF_Power_GetOCP_onoff());
                }
                break;
                case LV_KEY_UP: {
                    float temp = IF_Power_GetOCP();
                    temp += A_step[index_a];
                    if(temp > AMP_MAX) {
                        temp = AMP_MAX;
                        IF_MsgBox_Tips_Mult(&mStr_OutSet_MaxAmp);
                    }
                    UI_IF_Power_SetOCP(temp);
                }
                break;
                case LV_KEY_DOWN: {
                    float temp = IF_Power_GetOCP();
                    temp -= A_step[index_a];
                    if(temp < AMP_MIN) {
                        temp = AMP_MIN;
                    }
                    UI_IF_Power_SetOCP(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(index_a > 0)
                    {
                        index_a--;
                    }
                    else
                    {
                        index_a = sizeof(A_step) / sizeof(A_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(index_a < (sizeof(A_step) / sizeof(A_step[0]) - 1))
                    {
                        index_a++;
                    }
                    else
                    {
                        index_a = 0;
                    }
                }
                break;
                default:
                    break;
            }
            if(key != LV_KEY_ESC) {
                Set_RefreshUI(obj, &index_a, AMP_LIMIT_FORM, IF_Power_GetOCP());
            } else {
                editFlag = 0;
                Set_RefreshUI(obj, NULL, AMP_LIMIT_FORM, IF_Power_GetOCP());
                return;
            }
        }
        break;
        case LV_EVENT_DEFOCUSED:
            editFlag = 0;
            break;
        case LV_EVENT_FOCUSED: {
            if(editFlag == 1) {
                UI_IF_Power_SetOCP_onoff(!IF_Power_GetOCP_onoff());
            }
            editFlag = 1;
        }
        break;
        case LV_EVENT_REFRESH:
        {
            Set_RefreshUI(obj, NULL, AMP_LIMIT_FORM, IF_Power_GetOCP());
        }
        break;
        case LV_EVENT_CLICKED: {
            Set_RefreshUI(obj, &index_a, AMP_LIMIT_FORM, IF_Power_GetOCP());
        }
        break;
    }
}

/*
 * @brief       void TimeOff_handler(lv_obj_t *obj, lv_event_t event)
 * @details     定时关闭处理
 */
void TimeOff_RefreshUI(lv_obj_t *obj, uint8_t *editIndex)
{
    if(obj == NULL) {
        return;
    }
    if(TIMEOFF_SET_ONOFF != 0)
    {
        sprintf(stringSet, TIMEOFF_SET_FORM, TIMEOFF_SET_VALUE);
        if(editIndex != NULL) {
            label_setSelNum(obj, *editIndex, stringSet);
        } else {
        }
        lv_label_set_text(obj, stringSet);
        //
        lv_obj_set_hidden(ui.HomePage_edit_TUnit, 0);
        lv_obj_set_hidden(ui.HomePage2_edit_TUnit, 0);
    } else {
        lv_label_set_text_sel_start(obj, 0);
        lv_label_set_text_sel_end(obj, 0xff);
        lv_label_set_text_static(obj, "Disable");
        //
        lv_obj_set_hidden(ui.HomePage_edit_TUnit, 1);
        lv_obj_set_hidden(ui.HomePage2_edit_TUnit, 1);
    }
    if(editIndex == NULL) {
        lv_obj_set_state(obj, LV_STATE_DEFAULT);
        lv_label_set_text_sel_start(obj, LV_LABEL_TEXT_SEL_OFF);
        lv_label_set_text_sel_end(obj, LV_LABEL_TEXT_SEL_OFF);
    } else {
        lv_obj_set_state(obj, LV_STATE_FOCUSED);
    }
}

void TimeOff_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    static uint8_t idnex_timeoff = 0;
    static uint8_t editFlag = 0;
    NumberInput_Process(7, UI_IF_Power_Set_TimeOff);
    switch(event)
    {
        case LV_EVENT_KEY:
        {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                case LV_KEY_UP: {
                    if(IF_Power_Get_TimeOff_onoff() != 0)
                    {
                        TIMEOFF_SET_VALUE += timeoff_step[idnex_timeoff];
                        if(TIMEOFF_SET_VALUE > TIMEOFF_MAX) {
                            TIMEOFF_SET_VALUE = TIMEOFF_MAX;
                        }
                        UI_IF_Power_Set_TimeOff(TIMEOFF_SET_VALUE);
                    }
                }
                break;
                case LV_KEY_DOWN: {
                    if(IF_Power_Get_TimeOff_onoff() != 0)
                    {
                        TIMEOFF_SET_VALUE -= timeoff_step[idnex_timeoff];
                        if(TIMEOFF_SET_VALUE < TIMEOFF_MIN) {
                            TIMEOFF_SET_VALUE = TIMEOFF_MIN;
                        }
                        UI_IF_Power_Set_TimeOff(TIMEOFF_SET_VALUE);
                    }
                }
                break;
                case LV_KEY_RIGHT: {
                    if(IF_Power_Get_TimeOff_onoff() != 0)
                    {
                        if(idnex_timeoff > 0)
                        {
                            idnex_timeoff--;
                        }
                        else
                        {
                            idnex_timeoff = sizeof(timeoff_step) / sizeof(timeoff_step[0]) - 1;
                        }
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(IF_Power_Get_TimeOff_onoff() != 0)
                    {
                        if(idnex_timeoff < (sizeof(timeoff_step) / sizeof(timeoff_step[0]) - 1))
                        {
                            idnex_timeoff++;
                        }
                        else
                        {
                            idnex_timeoff = 0;
                        }
                    }
                }
                break;
                //校准DVM�?
                case LV_KEY_ESC_LONGP: {
                    if(POWER_CALIB_MODE == 1) {
                        UI_IF_Power_Calib_Delete("DVM");
                    }
                }
                break;
                case LV_KEY_ENCODER_LONGP:
                case LV_KEY_ENTER: {
                    if(POWER_CALIB_MODE == 1) {
                        calibDVM = IF_Power_Read_Dvm();
                        InputVal_DoubleEdit(&mStr_CalibDVM_Title, &calibDVM, VOL_CALIB_FORM,
                                            V_Calib_step, ARRAY_COUNT(V_Calib_step),
                                            VOL_MAX, VOL_MIN, NULL, NULL, CalibDVM_CallBack);
                    }
                }
                break;
                case LV_KEY_ENCODER: {
                    UI_IF_Power_Set_TimeOff_onoff(!IF_Power_Get_TimeOff_onoff());
                }
                break;
                default:
                    break;
            }
            if(key != LV_KEY_ESC) {
                TimeOff_RefreshUI(obj, &idnex_timeoff);
            } else {
                editFlag = 0;
                TimeOff_RefreshUI(obj, NULL);
                return;
            }
        }
        break;
        case LV_EVENT_DEFOCUSED:
            editFlag = 0;
            break;
        case LV_EVENT_FOCUSED: {
            if(editFlag == 1) {
                UI_IF_Power_Set_TimeOff_onoff(!IF_Power_Get_TimeOff_onoff());
            }
            editFlag = 1;
        }
        break;
        case LV_EVENT_REFRESH: {
            TimeOff_RefreshUI(obj, NULL);
        }
        break;
        case LV_EVENT_CLICKED: {
            TimeOff_RefreshUI(obj, &idnex_timeoff);
        }
        break;
    }
}

void HomePage_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    switch(event)
    {
        case LV_EVENT_REFRESH: {
            lv_label_set_text_static(ui.HomePage_label_Set, MultStr_GetS(&mStr_home_Set));
            lv_label_set_text_static(ui.HomePage_label_Limit, MultStr_GetS(&mStr_home_Limit));
            lv_label_set_text_static(ui.HomePage_label_timeOff, MultStr_GetS(&mStr_home_TimeSet));
        }
        break;
    }
}


/*
 * @brief       void HomePage_Enter(void)
 * @details     进入主页
 */
void HomePage_Enter(void)
{
    lv_obj_set_hidden(ui.HomePage_cont_Out, 0);
    lv_obj_set_hidden(ui.HomePage_cont_Set, 0);
    lv_obj_set_hidden(ui.HomePage_cont_Chart, 0);
    lv_obj_set_hidden(ui.HomePage_line_3, 0);
    lv_obj_set_hidden(ui.HomePage_line_4, 0);
    //递归刷新
    lv_event_send_refresh_recursive(ui.HomePage_cont_Out);
    lv_event_send_refresh_recursive(ui.HomePage_cont_Set);
    lv_event_send_refresh_recursive(ui.HomePage_cont_Chart);
}


/*
 * @brief       void HomePage_Exit(void)
 * @details     退出主�?
 */
void HomePage_Exit(void)
{
    lv_obj_set_hidden(ui.HomePage_cont_Out, 1);
    lv_obj_set_hidden(ui.HomePage_cont_Set, 1);
    lv_obj_set_hidden(ui.HomePage_cont_Chart, 1);
    lv_obj_set_hidden(ui.HomePage_line_3, 1);
    lv_obj_set_hidden(ui.HomePage_line_4, 1);
}





/*
 * @brief       void Power_Read_Updata_Task(struct _lv_task_t *p)
 * @details     定时刷新输出显示
 */
static void Power_Read_Updata_Task(struct _lv_task_t *p)
{
    UI_IF_Power_SetDisplay(IF_Power_Read_Vol(), IF_Power_Read_Amp());
}




void HomePage_GroupCreate(void)
{
    lv_task_create(Power_Read_Updata_Task, 100, LV_TASK_PRIO_MID, NULL);
    {
        setup_scr_HomePage(&ui);
        lv_obj_set_parent(ui.HomePage_cont_Set, ui.Back_cont_back);
        lv_obj_set_parent(ui.HomePage_cont_Out, ui.Back_cont_back);
        lv_obj_set_parent(ui.HomePage_cont_Chart, ui.Back_cont_back);
        lv_obj_set_parent(ui.HomePage_line_3, ui.Back_cont_back);
        lv_obj_set_parent(ui.HomePage_line_4, ui.Back_cont_back);
    }
    lv_obj_set_hidden(ui.HomePage_btn_SR, 1);
    //设置风格
    extern VOID_MULTSTR(mStr_home_Set);
    extern VOID_MULTSTR(mStr_home_Limit);
    extern VOID_MULTSTR(mStr_home_TimeSet);
    extern lv_font_t MultFont_16;
    lv_obj_set_style_local_text_font(ui.HomePage_label_Set, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_16);
    lv_obj_set_style_local_text_font(ui.HomePage_label_Limit, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_16);
    lv_obj_set_style_local_text_font(ui.HomePage_label_timeOff, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_16);
    UI_Label_Value_Style_Load(ui.HomePage_edit_Vset);
    UI_Label_Value_Style_Load(ui.HomePage_edit_Iset);
    UI_Label_Value_Style_Load(ui.HomePage_edit_OVP);
    UI_Label_Value_Style_Load(ui.HomePage_edit_OCP);
    UI_Label_Value_Style_Load(ui.HomePage_edit_timeOff);
    HomePage_Enter();
    HomePage_Exit();
    //波形图表初�?�?
    {
        lv_obj_t *chart = NULL;
        //
        chart = ui.HomePage_chart_v;
        lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
        lv_obj_clean_style_list(chart, LV_CHART_PART_BG);
        lv_obj_set_style_local_size(chart, LV_CHART_PART_SERIES, LV_STATE_DEFAULT, 0);
        lv_obj_invalidate(chart);
        chart = ui.HomePage_chart_i;
        lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
        lv_obj_clean_style_list(chart, LV_CHART_PART_BG);
        lv_obj_set_style_local_size(chart, LV_CHART_PART_SERIES, LV_STATE_DEFAULT, 0);
        lv_obj_invalidate(chart);
        chart = ui.HomePage_chart_w;
        lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
        lv_obj_clean_style_list(chart, LV_CHART_PART_BG);
        lv_obj_set_style_local_size(chart, LV_CHART_PART_SERIES, LV_STATE_DEFAULT, 0);
        lv_obj_invalidate(chart);
        extern lv_chart_series_t *HomePage_chart_v_0;
        extern lv_chart_series_t *HomePage_chart_i_0;
        extern lv_chart_series_t *HomePage_chart_w_0;
        lv_chart_set_point_count(ui.HomePage_chart_v, 250);
        lv_chart_set_point_count(ui.HomePage_chart_i, 250);
        lv_chart_set_point_count(ui.HomePage_chart_w, 250);
        //设置左边空间
        lv_obj_set_style_local_pad_left(ui.HomePage_chart_v, LV_CHART_PART_BG, LV_STATE_DEFAULT, 5);
        lv_obj_set_style_local_pad_left(ui.HomePage_chart_i, LV_CHART_PART_BG, LV_STATE_DEFAULT, 5);
        lv_obj_set_style_local_pad_left(ui.HomePage_chart_w, LV_CHART_PART_BG, LV_STATE_DEFAULT, 5);
        //设置右边空间
        lv_obj_set_style_local_pad_right(ui.HomePage_chart_v, LV_CHART_PART_BG, LV_STATE_DEFAULT, 30);
        lv_obj_set_style_local_pad_right(ui.HomePage_chart_i, LV_CHART_PART_BG, LV_STATE_DEFAULT, 30);
        lv_obj_set_style_local_pad_right(ui.HomePage_chart_w, LV_CHART_PART_BG, LV_STATE_DEFAULT, 30);
        //设置顶部空间
        lv_obj_set_style_local_pad_top(ui.HomePage_chart_v, LV_CHART_PART_BG, LV_STATE_DEFAULT, 5);
        lv_obj_set_style_local_pad_top(ui.HomePage_chart_i, LV_CHART_PART_BG, LV_STATE_DEFAULT, 5);
        lv_obj_set_style_local_pad_top(ui.HomePage_chart_w, LV_CHART_PART_BG, LV_STATE_DEFAULT, 5);
        //设置底部空间
        lv_obj_set_style_local_pad_bottom(ui.HomePage_chart_v, LV_CHART_PART_BG, LV_STATE_DEFAULT, 5);
        lv_obj_set_style_local_pad_bottom(ui.HomePage_chart_i, LV_CHART_PART_BG, LV_STATE_DEFAULT, 5);
        lv_obj_set_style_local_pad_bottom(ui.HomePage_chart_w, LV_CHART_PART_BG, LV_STATE_DEFAULT, 5);
        //设置线�?
        lv_obj_set_style_local_line_width(ui.HomePage_chart_v, LV_CHART_PART_SERIES, LV_STATE_DEFAULT, 2);
        lv_obj_set_style_local_line_width(ui.HomePage_chart_i, LV_CHART_PART_SERIES, LV_STATE_DEFAULT, 2);
        lv_obj_set_style_local_line_width(ui.HomePage_chart_w, LV_CHART_PART_SERIES, LV_STATE_DEFAULT, 2);
        //设置刻度长度
        lv_chart_set_secondary_y_tick_length(ui.HomePage_chart_v, 0, 0);
        lv_chart_set_secondary_y_tick_length(ui.HomePage_chart_i, 0, 0);
        lv_chart_set_secondary_y_tick_length(ui.HomePage_chart_w, 0, 0);
        //设置刻度字体
        lv_obj_set_style_local_text_font(ui.HomePage_chart_v, LV_CHART_PART_BG, LV_STATE_DEFAULT, &lv_font_AlibabaPuHuiTi_Light_10);
        lv_obj_set_style_local_text_font(ui.HomePage_chart_i, LV_CHART_PART_BG, LV_STATE_DEFAULT, &lv_font_AlibabaPuHuiTi_Light_10);
        lv_obj_set_style_local_text_font(ui.HomePage_chart_w, LV_CHART_PART_BG, LV_STATE_DEFAULT, &lv_font_AlibabaPuHuiTi_Light_10);
        //
        lv_obj_set_style_local_text_color(ui.HomePage_chart_v, LV_CHART_PART_BG, LV_STATE_DEFAULT, lv_color_make(0xff, 0x96, 0));
        lv_obj_set_style_local_text_color(ui.HomePage_chart_i, LV_CHART_PART_BG, LV_STATE_DEFAULT, lv_color_make(0, 0xff, 0xff));
        lv_obj_set_style_local_text_color(ui.HomePage_chart_w, LV_CHART_PART_BG, LV_STATE_DEFAULT, lv_color_make(0xff, 0, 0));
        //
        #if defined(UDP6922B)
        lv_chart_set_div_line_count(ui.HomePage_chart_v, 13, 4);
        lv_chart_set_div_line_count(ui.HomePage_chart_i, 13, 4);
        lv_chart_set_div_line_count(ui.HomePage_chart_w, 7, 4);
        lv_chart_set_secondary_y_tick_texts(ui.HomePage_chart_v, "70V\n\n60V\n\n50V\n\n40V\n\n30V\n\n20V\n\n10V\n\n0V", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
        lv_chart_set_secondary_y_tick_texts(ui.HomePage_chart_i, "\n6.5A\n\n5.5A\n\n4.5A\n\n3.5A\n\n2.5A\n\n1.5A\n\n0.5A\n", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
        lv_chart_set_secondary_y_tick_texts(ui.HomePage_chart_w, "120\n\n90W\n\n60W\n\n30W\n\n0W", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
        //设置范围
        lv_chart_set_range(ui.HomePage_chart_v, -1, 700);
        lv_chart_set_range(ui.HomePage_chart_i, -1, 70);
        lv_chart_set_range(ui.HomePage_chart_w, -1, 120);
        #elif defined(UDP6932B)
        lv_chart_set_div_line_count(ui.HomePage_chart_v, 13, 4);
        lv_chart_set_div_line_count(ui.HomePage_chart_i, 13, 4);
        lv_chart_set_div_line_count(ui.HomePage_chart_w, 7, 4);
        lv_chart_set_secondary_y_tick_texts(ui.HomePage_chart_v, "70V\n\n60V\n\n50V\n\n40V\n\n30V\n\n20V\n\n10V\n\n0V", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
        lv_chart_set_secondary_y_tick_texts(ui.HomePage_chart_i, "\n13A\n\n11A\n\n9A\n\n7A\n\n5A\n\n3A\n\n1A\n", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
        lv_chart_set_secondary_y_tick_texts(ui.HomePage_chart_w, "240\n\n180\n\n120\n\n60W\n\n0W", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
        //设置范围
        lv_chart_set_range(ui.HomePage_chart_v, -1, 700);
        lv_chart_set_range(ui.HomePage_chart_i, -1, 140);
        lv_chart_set_range(ui.HomePage_chart_w, -1, 240);
        #elif defined(UDP6933B)
        lv_chart_set_div_line_count(ui.HomePage_chart_v, 7, 4);
        lv_chart_set_div_line_count(ui.HomePage_chart_i, 7, 4);
        lv_chart_set_div_line_count(ui.HomePage_chart_w, 7, 4);
        lv_chart_set_secondary_y_tick_texts(ui.HomePage_chart_v, "\n140\n\n100\n\n60V\n\n20V\n", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
        lv_chart_set_secondary_y_tick_texts(ui.HomePage_chart_i, "8A\n\n6A\n\n4A\n\n2A\n\n0A", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
        lv_chart_set_secondary_y_tick_texts(ui.HomePage_chart_w, "240\n\n180\n\n120\n\n60\n\n0W", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
        //设置范围
        lv_chart_set_range(ui.HomePage_chart_v, -1, 1600);
        lv_chart_set_range(ui.HomePage_chart_i, -1, 80);
        lv_chart_set_range(ui.HomePage_chart_w, -1, 240);
        #elif defined(UDP6942B)
        lv_chart_set_div_line_count(ui.HomePage_chart_v, 7, 4);
        lv_chart_set_div_line_count(ui.HomePage_chart_i, 7, 4);
        lv_chart_set_div_line_count(ui.HomePage_chart_w, 6, 4);
        lv_chart_set_secondary_y_tick_texts(ui.HomePage_chart_v, "\n70V\n\n50V\n\n30V\n\n10V\n", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
        lv_chart_set_secondary_y_tick_texts(ui.HomePage_chart_i, "16A\n\n12A\n\n8A\n\n4A\n\n0A", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
        lv_chart_set_secondary_y_tick_texts(ui.HomePage_chart_w, "\n360\n\n240\n\n120\n\n0W", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
        //设置范围
        lv_chart_set_range(ui.HomePage_chart_v, -1, 800);
        lv_chart_set_range(ui.HomePage_chart_i, -1, 160);
        lv_chart_set_range(ui.HomePage_chart_w, -1, 400);
        #elif defined(UDP6943B)
        lv_chart_set_div_line_count(ui.HomePage_chart_v, 13, 4);
        lv_chart_set_div_line_count(ui.HomePage_chart_i, 13, 4);
        lv_chart_set_div_line_count(ui.HomePage_chart_w, 6, 4);
        lv_chart_set_secondary_y_tick_texts(ui.HomePage_chart_v, "280V\n\n240V\n\n200V\n\n160V\n\n120V\n\n80V\n\n40V\n\n0V", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
        lv_chart_set_secondary_y_tick_texts(ui.HomePage_chart_i, "\n6.5A\n\n5.5A\n\n4.5A\n\n3.5A\n\n2.5A\n\n1.5A\n\n0.5A\n", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
        lv_chart_set_secondary_y_tick_texts(ui.HomePage_chart_w, "\n360\n\n240\n\n120\n\n0W", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
        //设置范围
        lv_chart_set_range(ui.HomePage_chart_v, -1, 2800);
        lv_chart_set_range(ui.HomePage_chart_i, -1, 70);
        lv_chart_set_range(ui.HomePage_chart_w, -1, 700);
        #elif defined(UDP6952B)
        lv_chart_set_div_line_count(ui.HomePage_chart_v, 13, 4);
        lv_chart_set_div_line_count(ui.HomePage_chart_i, 13, 4);
        lv_chart_set_div_line_count(ui.HomePage_chart_w, 6, 4);
        lv_chart_set_secondary_y_tick_texts(ui.HomePage_chart_v, "70V\n\n60V\n\n50V\n\n40V\n\n30V\n\n20V\n\n10V\n\n0V", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
        lv_chart_set_secondary_y_tick_texts(ui.HomePage_chart_i, "\n26A\n\n22A\n\n18A\n\n14A\n\n10A\n\n6A\n\n2A\n", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
        lv_chart_set_secondary_y_tick_texts(ui.HomePage_chart_w, "\n600\n\n400\n\n200\n\n0W", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
        //设置范围
        lv_chart_set_range(ui.HomePage_chart_v, -1, 700);
        lv_chart_set_range(ui.HomePage_chart_i, -1, 280);
        lv_chart_set_range(ui.HomePage_chart_w, -1, 700);
        #elif defined(UDP6953B)
        lv_chart_set_div_line_count(ui.HomePage_chart_v, 7, 4);
        lv_chart_set_div_line_count(ui.HomePage_chart_i, 7, 4);
        lv_chart_set_div_line_count(ui.HomePage_chart_w, 6, 4);
        lv_chart_set_secondary_y_tick_texts(ui.HomePage_chart_v, "\n140\n\n100\n\n60V\n\n20V\n", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
        lv_chart_set_secondary_y_tick_texts(ui.HomePage_chart_i, "16A\n\n12A\n\n8A\n\n4A\n\n0A", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
        lv_chart_set_secondary_y_tick_texts(ui.HomePage_chart_w, "\n600\n\n400\n\n200\n\n0W", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
        //设置范围
        lv_chart_set_range(ui.HomePage_chart_v, -1, 1600);
        lv_chart_set_range(ui.HomePage_chart_i, -1, 160);
        lv_chart_set_range(ui.HomePage_chart_w, -1, 700);
        #elif defined(UDP40_40)
        lv_chart_set_div_line_count(ui.HomePage_chart_v, 0, 4);
        lv_chart_set_div_line_count(ui.HomePage_chart_i, 0, 4);
        lv_chart_set_div_line_count(ui.HomePage_chart_w, 6, 4);
        lv_chart_set_secondary_y_tick_texts(ui.HomePage_chart_w, "\n720\n\n480\n\n240\n\n0W", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
        //设置范围
        lv_chart_set_range(ui.HomePage_chart_v, -1, 400);
        lv_chart_set_range(ui.HomePage_chart_i, -1, 400);
        lv_chart_set_range(ui.HomePage_chart_w, -1, 800);
        #elif defined(UDP40_80)
        lv_chart_set_div_line_count(ui.HomePage_chart_v, 0, 4);
        lv_chart_set_div_line_count(ui.HomePage_chart_i, 0, 4);
        lv_chart_set_div_line_count(ui.HomePage_chart_w, 6, 4);
        lv_chart_set_secondary_y_tick_texts(ui.HomePage_chart_w, "\n360\n\n240\n\n120\n\n0W", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
        //设置范围
        lv_chart_set_range(ui.HomePage_chart_v, -1, 400);
        lv_chart_set_range(ui.HomePage_chart_i, -1, 800);
        lv_chart_set_range(ui.HomePage_chart_w, -1, 400);
        #endif
        lv_chart_clear_series(ui.HomePage_chart_v, HomePage_chart_v_0);
        lv_chart_clear_series(ui.HomePage_chart_i, HomePage_chart_i_0);
        lv_chart_clear_series(ui.HomePage_chart_w, HomePage_chart_w_0);
    }
}

