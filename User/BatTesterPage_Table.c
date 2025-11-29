#include "BatTester.h"
#include "BatTesterPage.h"
#include "BatTesterPage_Table.h"
#include "BatTester_Interface.h"
#include "InputWidget.h"

#include "BtnTree.h"

#define __ROW_CNT 6 //行数
#define __COL_CNT 5 //列数

//按键表格
static lv_obj_t *__btnTable_label[__ROW_CNT][__COL_CNT] = {0};
static uint16_t __table_x = 1;
static const uint16_t __btnTable_y = 6;
static const uint16_t __btnTable_width[__COL_CNT] = {35, 65, 65, 70, 239};
static const uint16_t __btnTable_height = 21;


lv_obj_t *voltage_sel_node;
lv_obj_t *current_sel_node;
lv_obj_t *ktime_sel_node;
lv_obj_t *protect_param0_sel_node;
lv_obj_t *protect_logic1_sel_node;
lv_obj_t *protect_param1_sel_node;


static void __btnTable_DrawLine(lv_obj_t *backg)
{
    static lv_point_t line_point_V[] = {{0, 0}, {480, 0}};
    static lv_point_t line_point_H[] = {{0, 0}, {0, 215}};
    uint16_t line_V_Count = (sizeof(__btnTable_label) / sizeof(__btnTable_label[0]));
    for(uint8_t i = 0; i < line_V_Count; ++i) {
        //横线
        uint16_t x_v = lv_obj_get_x(__btnTable_label[i][0]) - 1;
        uint16_t y_v = lv_obj_get_y(__btnTable_label[i][0]) - 1;
        if(i == 0) {
            y_v = 0;
        }
        lv_obj_t *line_V = lv_line_create(backg, NULL);
        lv_obj_set_pos(line_V, x_v, y_v);
        lv_obj_set_size(line_V, 480, 0);
        lv_line_set_points(line_V, line_point_V, 2);
        lv_obj_set_style_local_line_color(line_V, LV_LINE_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x33, 0x33, 0x33));
        if(i == (line_V_Count - 1)) {
            y_v += __btnTable_height + 1 + 1;
            line_V = lv_line_create(backg, NULL);
            lv_obj_set_pos(line_V, x_v, y_v);
            lv_obj_set_size(line_V, 480, 0);
            lv_line_set_points(line_V, line_point_V, 2);
            lv_obj_set_style_local_line_color(line_V, LV_LINE_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x33, 0x33, 0x33));
        }
    }
    uint16_t line_H_Count = (sizeof(__btnTable_label[0]) / sizeof(__btnTable_label[0][0]));
    for(uint8_t j = 0; j < line_H_Count; ++j) {
        //竖线
        uint16_t x_h = lv_obj_get_x(__btnTable_label[0][j]) - 1;
        uint16_t y_h = 1;
        lv_obj_t *line_H = lv_line_create(backg, NULL);
        lv_obj_set_pos(line_H, x_h, y_h);
        lv_obj_set_size(line_H, 0, 215);
        lv_line_set_points(line_H, line_point_H, 2);
        lv_obj_set_style_local_line_color(line_H, LV_LINE_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x33, 0x33, 0x33));
        if(j == (line_H_Count - 1)) {
            x_h += lv_obj_get_width(__btnTable_label[0][j]) + 1;
            line_H = lv_line_create(backg, NULL);
            lv_obj_set_pos(line_H, x_h, y_h);
            lv_obj_set_size(line_H, 0, 215);
            lv_line_set_points(line_H, line_point_H, 2);
            lv_obj_set_style_local_line_color(line_H, LV_LINE_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x33, 0x33, 0x33));
        }
    }
}

void batTester_btnTable_Init(void)
{
    lv_obj_t *backg = ui.BatTester_cont_Table;
    for(uint8_t i = 0; i < (sizeof(__btnTable_label) / sizeof(__btnTable_label[0])); ++i)
    {
        __table_x = 1;
        for(uint8_t j = 0; j < (sizeof(__btnTable_label[0]) / sizeof(__btnTable_label[0][0])); ++j)
        {
            lv_obj_t *label = lv_label_create(backg, NULL);
            lv_label_set_long_mode(label, LV_LABEL_LONG_BREAK);
            if(j > 0)
            {
                __table_x += __btnTable_width[j - 1] + 1;
            }
            extern lv_font_t MultFont_16;
            lv_obj_set_style_local_text_letter_space(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 1);
            if(i == 0) {
                lv_obj_set_style_local_text_font(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_16);
                lv_obj_set_size(label, __btnTable_width[j], __btnTable_height);
                lv_obj_set_pos(label, __table_x, __btnTable_y);
                lv_obj_set_style_local_text_color(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0, 255, 255));
            } else {
                lv_obj_set_style_local_text_font(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_16);
                lv_obj_set_size(label, __btnTable_width[j], __btnTable_height);
                lv_obj_set_pos(label, __table_x, __btnTable_y + ((__btnTable_height + 1 + 1) + (i - 1) * (__btnTable_height + 1)));
                lv_obj_set_style_local_text_color(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(255, 255, 255));
            }
            //            lv_obj_set_style_local_text_sel_bg_color(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0, 255, 255));
            //            lv_obj_set_style_local_text_sel_color(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0, 0, 0));
            lv_label_set_align(label, LV_LABEL_ALIGN_CENTER);
            __btnTable_label[i][j] = label;
        }
    }
    __btnTable_DrawLine(backg);
    voltage_sel_node = __btnTable_label[3][1];
    current_sel_node = __btnTable_label[3][2];
    ktime_sel_node = __btnTable_label[3][3];
    protect_param0_sel_node = __btnTable_label[3][4];
    protect_logic1_sel_node = __btnTable_label[3][4];
    protect_param1_sel_node = __btnTable_label[3][4];
}





//BatTester表格强制刷新标志  1:需要刷新
static uint8_t __refreshFlag = 1;

/*
 * @brief       void BatteryTester_Page_Table_Refresh(int16_t baseIndex)
 * @details     刷新BatTester表格
 */
void BatteryTester_Page_Table_Refresh(int16_t baseIndex);

//聚焦特定行风格
static void __Table_setFocus(uint16_t *col_x, uint16_t *row_y);

#define MIN_ROW (1)
#define MAX_ROW (TABLE_ROW_CNT-1)
#define MIN_COL (1)
#define MAX_COL (TABLE_COL_CNT-1)
static uint16_t __edit_row_y = 4;  //行数 [1,11]
static uint16_t __edit_col_x = MIN_COL;  //列数 [1,5]


static int16_t __lastBaseIndex = 0;
/* ------------------------------------------------------------- */


void BatteryTester_Page_SetCurrent(int16_t no)
{
    int16_t disp_baseIndex = no - __edit_row_y + 1;
    if(disp_baseIndex < 0) {
        disp_baseIndex += BAT_TESTER_MAX_COUNT;
    }
    disp_baseIndex = disp_baseIndex % BAT_TESTER_MAX_COUNT;
    BatteryTester_Page_Table_Refresh(disp_baseIndex);
}


enum {
    EDIT_STATE_DEFAULT = 0,
    EDIT_STATE_VOLT,
    EDIT_STATE_CURR,
    EDIT_STATE_TIME,
    EDIT_STATE_PROTECT_VALUE_0,
    EDIT_STATE_PROTECT_LOGIC_1,
    EDIT_STATE_PROTECT_VALUE_1,
};
static uint8_t edit_State = EDIT_STATE_DEFAULT;


static void Set_RefreshUI(lv_obj_t *obj, uint8_t *editIndex, const char *dispfmt, double value)
{
    static char stringSet[64] = {0};
    if(obj == NULL) { return ; }
    //
    sprintf(stringSet, dispfmt, value);
    if(editIndex != NULL) {
        label_setSelNum(obj, *editIndex, stringSet);
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

void __Volt_Set_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //
    int16_t no = __lastBaseIndex + __edit_row_y - 1;
    if(no < 0) {
        no += BAT_TESTER_MAX_COUNT ;
    } else
        if(no > (BAT_TESTER_MAX_COUNT)) {
            no -= (BAT_TESTER_MAX_COUNT);
        }
    no %= BAT_TESTER_MAX_COUNT;
    float editMax = VOL_MAX;
    float editMin = VOL_MIN;
    float *editdata = &BatTester.points[no].vol;
    //
    static uint8_t index_v = 0;
    NumberInput_Process(7, *editdata =);
    *editdata = MIN(editMax, *editdata);
    *editdata = MAX(editMin, *editdata);
    switch(event)
    {
        case LV_EVENT_KEY: {
            switch(key) {
                case LV_KEY_UP: {
                    double temp = *editdata;
                    temp += BatteryTester_V_step[index_v];
                    temp = MIN(editMax, temp);
                    *editdata = temp;
                }
                break;
                case LV_KEY_DOWN: {
                    double temp = *editdata;
                    temp -= BatteryTester_V_step[index_v];
                    temp = MAX(editMin, temp);
                    *editdata = temp;
                }
                break;
                case LV_KEY_RIGHT: {
                    if(index_v > 0) {
                        index_v--;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(index_v < (sizeof(BatteryTester_V_step) / sizeof(BatteryTester_V_step[0]) - 1)) {
                        index_v++;
                    }
                }
                break;
                case LV_KEY_ENTER:
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
            edit_State = EDIT_STATE_VOLT;
            break;
    }
    if(edit_State != EDIT_STATE_VOLT) {
        Set_RefreshUI(obj, NULL, BAT_TESTER_VOL_SET_FORM, *editdata);
    } else {
        Set_RefreshUI(obj, &index_v, BAT_TESTER_VOL_SET_FORM, *editdata);
    }
}



void __Curr_Set_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //
    int16_t no = __lastBaseIndex + __edit_row_y - 1;
    if(no < 0) {
        no += BAT_TESTER_MAX_COUNT ;
    } else
        if(no > (BAT_TESTER_MAX_COUNT)) {
            no -= (BAT_TESTER_MAX_COUNT);
        }
    no %= BAT_TESTER_MAX_COUNT;
    float editMax = WAT_MAX / (BatTester.points[no].vol + 0.0001f);
    float editMin = AMP_MIN;
    float *editdata = &BatTester.points[no].amp;
    //
    static uint8_t index_a = 0;
    NumberInput_Process(7, *editdata =);
    *editdata = MIN(editMax, *editdata);
    *editdata = MAX(editMin, *editdata);
    switch(event)
    {
        case LV_EVENT_KEY: {
            switch(key) {
                case LV_KEY_UP: {
                    double temp = *editdata;
                    temp += BatteryTester_A_step[index_a];
                    temp = MIN(editMax, temp);
                    *editdata = temp;
                }
                break;
                case LV_KEY_DOWN: {
                    double temp = *editdata;
                    temp -= BatteryTester_A_step[index_a];
                    temp = MAX(editMin, temp);
                    *editdata = temp;
                }
                break;
                case LV_KEY_RIGHT: {
                    if(index_a > 0) {
                        index_a--;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(index_a < (sizeof(BatteryTester_A_step) / sizeof(BatteryTester_A_step[0]) - 1)) {
                        index_a++;
                    }
                }
                break;
                case LV_KEY_ENTER:
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
            edit_State = EDIT_STATE_CURR;
            break;
    }
    if(edit_State != EDIT_STATE_CURR) {
        Set_RefreshUI(obj, NULL, BAT_TESTER_AMP_SET_FORM, *editdata);
    } else {
        Set_RefreshUI(obj, &index_a, BAT_TESTER_AMP_SET_FORM, *editdata);
    }
}


void __Time_Set_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //
    int16_t no = __lastBaseIndex + __edit_row_y - 1;
    if(no < 0) {
        no += BAT_TESTER_MAX_COUNT ;
    } else
        if(no > (BAT_TESTER_MAX_COUNT)) {
            no -= (BAT_TESTER_MAX_COUNT);
        }
    no %= BAT_TESTER_MAX_COUNT;
    float editMax = KT_MAX;
    float editMin = KT_MIN;
    float *editdata = &BatTester.points[no].kT;
    //
    static uint8_t index_kt = 0;
    NumberInput_Process(7, *editdata =);
    *editdata = MIN(editMax, *editdata);
    *editdata = MAX(editMin, *editdata);
    switch(event)
    {
        case LV_EVENT_KEY: {
            switch(key) {
                case LV_KEY_UP: {
                    double temp = *editdata;
                    temp += BatteryTester_kT_step[index_kt];
                    temp = MIN(editMax, temp);
                    *editdata = temp;
                }
                break;
                case LV_KEY_DOWN: {
                    double temp = *editdata;
                    temp -= BatteryTester_kT_step[index_kt];
                    temp = MAX(editMin, temp);
                    *editdata = temp;
                }
                break;
                case LV_KEY_RIGHT: {
                    if(index_kt > 0) {
                        index_kt--;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(index_kt < (sizeof(BatteryTester_kT_step) / sizeof(BatteryTester_kT_step[0]) - 1)) {
                        index_kt++;
                    }
                }
                break;
                case LV_KEY_ENTER:
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
            edit_State = EDIT_STATE_TIME;
            break;
    }
    if(edit_State != EDIT_STATE_TIME) {
        Set_RefreshUI(obj, NULL, BAT_TESTER_KT_SET_FORM, *editdata);
    } else {
        Set_RefreshUI(obj, &index_kt, BAT_TESTER_KT_SET_FORM, *editdata);
    }
}




static void StopSet_RefreshUI(lv_obj_t *obj, uint8_t *editIndex, BatTester_Stop_Def stopcfg[2], uint8_t edit)
{
    char value_str[2][64] = {0};
    const char *logic_str[2] = {""};
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
    //
    lv_label_set_text(obj, disp_str);
    if(edit == EDIT_STATE_DEFAULT) {
        lv_label_set_text_sel_start(obj, LV_LABEL_TEXT_SEL_OFF);
        lv_label_set_text_sel_end(obj, LV_LABEL_TEXT_SEL_OFF);
    }
}

void __Protect_Set_Param0_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //
    int16_t no = __lastBaseIndex + __edit_row_y - 1;
    if(no < 0) {
        no += BAT_TESTER_MAX_COUNT ;
    } else
        if(no > (BAT_TESTER_MAX_COUNT)) {
            no -= (BAT_TESTER_MAX_COUNT);
        }
    no %= BAT_TESTER_MAX_COUNT;
    //
    static uint8_t index_kt = 0;
    float minValue = 0;
    float maxValue = 0;
    uint8_t stepCount = 0;
    const float *pStep = NULL;
    switch(BatTester.points[no].stopCfg[0].stop)
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
    if(BatTester.points[no].stopCfg[0].stop != __STOP_NONE) {
        NumberInput_Process(7, BatTester.points[no].stopCfg[0].value =);
    }
    switch(event)
    {
        case LV_EVENT_KEY: {
            switch(key) {
                case LV_KEY_MORE_VOLT:
                    BatTester.points[no].stopCfg[0].stop = __STOP_MORE_V;
                    break;
                case LV_KEY_LESS_VOLT:
                    BatTester.points[no].stopCfg[0].stop = __STOP_LESS_V;
                    break;
                case LV_KEY_MORE_CURR:
                    BatTester.points[no].stopCfg[0].stop = __STOP_MORE_C;
                    break;
                case LV_KEY_LESS_CURR:
                    BatTester.points[no].stopCfg[0].stop = __STOP_LESS_C;
                    break;
                case LV_KEY_MORE_POWER:
                    BatTester.points[no].stopCfg[0].stop = __STOP_MORE_P;
                    break;
                case LV_KEY_LESS_POWER:
                    BatTester.points[no].stopCfg[0].stop = __STOP_LESS_P;
                    break;
                case LV_KEY_MORE_DVM:
                    BatTester.points[no].stopCfg[0].stop = __STOP_MORE_DVM;
                    break;
                case LV_KEY_LESS_DVM:
                    BatTester.points[no].stopCfg[0].stop = __STOP_LESS_DVM;
                    break;
                case LV_KEY_NONE_PROTECT:
                    BatTester.points[no].stopCfg[0].stop = __STOP_NONE;
                    break;
                case LV_KEY_UP: {
                    if(BatTester.points[no].stopCfg[0].stop == __STOP_NONE) { break; }
                    float value = BatTester.points[no].stopCfg[0].value;
                    value += pStep[index_kt];
                    value = MIN(value, maxValue);
                    BatTester.points[no].stopCfg[0].value = value;
                }
                break;
                case LV_KEY_DOWN: {
                    if(BatTester.points[no].stopCfg[0].stop == __STOP_NONE) { break; }
                    float value = BatTester.points[no].stopCfg[0].value;
                    value -= pStep[index_kt];
                    value = MAX(value, minValue);
                    BatTester.points[no].stopCfg[0].value = value;
                }
                break;
                case LV_KEY_LEFT:
                    if(BatTester.points[no].stopCfg[0].stop == __STOP_NONE) { break; }
                    if(index_kt < (stepCount - 1)) { index_kt++; }
                    break;
                case LV_KEY_RIGHT:
                    if(BatTester.points[no].stopCfg[0].stop == __STOP_NONE) { break; }
                    if(index_kt > 0) { index_kt--; }
                    break;
                case LV_KEY_ENTER:
                case LV_KEY_ENCODER: {
                    BatTester.points[no].stopCfg[0].stop = (++BatTester.points[no].stopCfg[0].stop) % (__STOP_MAX + 1);
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
                BatTester.points[no].stopCfg[0].stop = (++BatTester.points[no].stopCfg[0].stop) % (__STOP_MAX + 1);
            }
            edit_State = EDIT_STATE_PROTECT_VALUE_0;
            break;
    }
    float value = BatTester.points[no].stopCfg[0].value;
    value = MIN(value, maxValue);
    value = MAX(value, minValue);
    BatTester.points[no].stopCfg[0].value = value;
    if(edit_State != EDIT_STATE_PROTECT_VALUE_0) {
        StopSet_RefreshUI(obj, NULL, BatTester.points[no].stopCfg, EDIT_STATE_DEFAULT);
    } else {
        StopSet_RefreshUI(obj, &index_kt, BatTester.points[no].stopCfg, edit_State);
    }
}

void __Protect_Set_Logic1_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //
    int16_t no = __lastBaseIndex + __edit_row_y - 1;
    if(no < 0) {
        no += BAT_TESTER_MAX_COUNT ;
    } else
        if(no > (BAT_TESTER_MAX_COUNT)) {
            no -= (BAT_TESTER_MAX_COUNT);
        }
    no %= BAT_TESTER_MAX_COUNT;
    //
    switch(event)
    {
        case LV_EVENT_KEY: {
            switch(key)
            {
                case LV_KEY_ENTER:
                case LV_KEY_ENCODER:
                    BatTester.points[no].stopCfg[1].logic = (++BatTester.points[no].stopCfg[1].logic) % 2;
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
                BatTester.points[no].stopCfg[1].logic = (++BatTester.points[no].stopCfg[1].logic) % 2;
            }
        }
        break;
    }
    if(edit_State != EDIT_STATE_PROTECT_LOGIC_1) {
        StopSet_RefreshUI(obj, NULL, BatTester.points[no].stopCfg, EDIT_STATE_DEFAULT);
    } else {
        StopSet_RefreshUI(obj, NULL, BatTester.points[no].stopCfg, edit_State);
    }
}


void __Protect_Set_Param1_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //
    int16_t no = __lastBaseIndex + __edit_row_y - 1;
    if(no < 0) {
        no += BAT_TESTER_MAX_COUNT ;
    } else
        if(no > (BAT_TESTER_MAX_COUNT)) {
            no -= (BAT_TESTER_MAX_COUNT);
        }
    no %= BAT_TESTER_MAX_COUNT;
    //
    static uint8_t index_kt = 0;
    float minValue = 0;
    float maxValue = 0;
    uint8_t stepCount = 0;
    const float *pStep = NULL;
    switch(BatTester.points[no].stopCfg[1].stop)
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
    if(BatTester.points[no].stopCfg[1].stop != __STOP_NONE) {
        NumberInput_Process(7, BatTester.points[no].stopCfg[1].value =);
    }
    switch(event)
    {
        case LV_EVENT_KEY: {
            switch(key) {
                case LV_KEY_MORE_VOLT:
                    BatTester.points[no].stopCfg[1].stop = __STOP_MORE_V;
                    break;
                case LV_KEY_LESS_VOLT:
                    BatTester.points[no].stopCfg[1].stop = __STOP_LESS_V;
                    break;
                case LV_KEY_MORE_CURR:
                    BatTester.points[no].stopCfg[1].stop = __STOP_MORE_C;
                    break;
                case LV_KEY_LESS_CURR:
                    BatTester.points[no].stopCfg[1].stop = __STOP_LESS_C;
                    break;
                case LV_KEY_MORE_POWER:
                    BatTester.points[no].stopCfg[1].stop = __STOP_MORE_P;
                    break;
                case LV_KEY_LESS_POWER:
                    BatTester.points[no].stopCfg[1].stop = __STOP_LESS_P;
                    break;
                case LV_KEY_MORE_DVM:
                    BatTester.points[no].stopCfg[1].stop = __STOP_MORE_DVM;
                    break;
                case LV_KEY_LESS_DVM:
                    BatTester.points[no].stopCfg[1].stop = __STOP_LESS_DVM;
                    break;
                case LV_KEY_NONE_PROTECT:
                    BatTester.points[no].stopCfg[1].stop = __STOP_NONE;
                    break;
                case LV_KEY_UP: {
                    if(BatTester.points[no].stopCfg[1].stop == __STOP_NONE) { break; }
                    float value = BatTester.points[no].stopCfg[1].value;
                    value += pStep[index_kt];
                    value = MIN(value, maxValue);
                    BatTester.points[no].stopCfg[1].value = value;
                }
                break;
                case LV_KEY_DOWN: {
                    if(BatTester.points[no].stopCfg[1].stop == __STOP_NONE) { break; }
                    float value = BatTester.points[no].stopCfg[1].value;
                    value -= pStep[index_kt];
                    value = MAX(value, minValue);
                    BatTester.points[no].stopCfg[1].value = value;
                }
                break;
                case LV_KEY_LEFT:
                    if(BatTester.points[no].stopCfg[1].stop == __STOP_NONE) { break; }
                    if(index_kt < (stepCount - 1)) { index_kt++; }
                    break;
                case LV_KEY_RIGHT:
                    if(BatTester.points[no].stopCfg[1].stop == __STOP_NONE) { break; }
                    if(index_kt > 0) { index_kt--; }
                    break;
                case LV_KEY_ENTER:
                case LV_KEY_ENCODER: {
                    BatTester.points[no].stopCfg[1].stop = (++BatTester.points[no].stopCfg[1].stop) % (__STOP_MAX + 1);
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
                BatTester.points[no].stopCfg[1].stop = (++BatTester.points[no].stopCfg[1].stop) % (__STOP_MAX + 1);
            }
            edit_State = EDIT_STATE_PROTECT_VALUE_1;
            break;
    }
    float value = BatTester.points[no].stopCfg[1].value;
    value = MIN(value, maxValue);
    value = MAX(value, minValue);
    BatTester.points[no].stopCfg[1].value = value;
    if(edit_State != EDIT_STATE_PROTECT_VALUE_1) {
        StopSet_RefreshUI(obj, NULL, BatTester.points[no].stopCfg, EDIT_STATE_DEFAULT);
    } else {
        StopSet_RefreshUI(obj, &index_kt, BatTester.points[no].stopCfg, edit_State);
    }
}




void BatteryTester_Page_Table_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    int16_t disp_baseIndex = __lastBaseIndex;
    switch(event)
    {
        case LV_EVENT_KEY:
        {
            switch(key)
            {
                case LV_KEY_START:
                    IF_BatTester_Set_State(BAT_TESTER_STATE_RUNNING);
                    break;
                case LV_KEY_STOP:
                    IF_BatTester_Set_State(BAT_TESTER_STATE_STOP);
                    break;
                case LV_KEY_CONTIUNE:
                    IF_BatTester_Set_State(BAT_TESTER_STATE_RUNNING);
                    break;
                case LV_KEY_PAUSE:
                    IF_BatTester_Set_State(BAT_TESTER_STATE_PAUSE);
                    break;
                case LV_KEY_UP:
                    BatteryTester_Page_SetCurrent((--disp_baseIndex) + __edit_row_y - 1);
                    break;
                case LV_KEY_DOWN:
                    BatteryTester_Page_SetCurrent((++disp_baseIndex) + __edit_row_y - 1);
                    break;
            }
        }
        break;
        case LV_EVENT_CLICKED: {
            __edit_col_x = 0;
        }
        case LV_EVENT_REFRESH:
        case LV_EVENT_FOCUSED: {
            lv_label_set_text_static(__btnTable_label[0][0], MultStr_GetS(&mStr_Battest_No));
            lv_label_set_text_static(__btnTable_label[0][1], MultStr_GetS(&mStr_Battest_Voltage));
            lv_label_set_text_static(__btnTable_label[0][2], MultStr_GetS(&mStr_Battest_Current));
            lv_label_set_text_static(__btnTable_label[0][3], MultStr_GetS(&mStr_Battest_keepT));
            lv_label_set_text_static(__btnTable_label[0][4], MultStr_GetS(&mStr_Battest_Protect));
            __refreshFlag = 1;
            __edit_row_y = 3;
            BatteryTester_Page_Table_Refresh(disp_baseIndex);
            if(__edit_col_x != 0) {
                __Table_setFocus(&__edit_col_x, &__edit_row_y);
            } else {
                __Table_setFocus(NULL, &__edit_row_y);
            }
        }
        break;
    }
}





//聚焦特定行风格
static void __Table_setFocus(uint16_t *col_x, uint16_t *row_y)
{
    if(row_y == NULL)
    {
        return ;
    }
    __edit_row_y = *row_y;
    uint16_t width = 0;
    uint16_t height = 0;
    uint16_t x = 0;
    uint16_t y = 0;
    for(uint8_t i = 0; i < __COL_CNT; ++i) {
        width += lv_obj_get_width(__btnTable_label[__edit_row_y][i]);
    }
    height = __btnTable_height;
    width += __COL_CNT - 1;
    x = lv_obj_get_x(__btnTable_label[__edit_row_y][0]);
    y = lv_obj_get_y(__btnTable_label[__edit_row_y][0]);
    lv_obj_set_size(ui.BatTester_img_back, width, height);
    lv_obj_set_pos(ui.BatTester_img_back, x, y);
    lv_obj_set_hidden(ui.BatTester_img_back, 0);
}


/*
 * @brief       static void __Tabel_Refresh_Row(uint16_t baseIndex,uint16_t no)
 * @details     刷新某一行
 */
static void __Tabel_Refresh_Row(uint16_t baseIndex, uint16_t no)
{
    baseIndex %= BAT_TESTER_MAX_COUNT;
    uint16_t i = no % BAT_TESTER_MAX_COUNT;
    int16_t idx = i - baseIndex;
    if(idx < 0) {
        idx += BAT_TESTER_MAX_COUNT ;
    } else
        if(idx > (BAT_TESTER_MAX_COUNT)) {
            idx -= (BAT_TESTER_MAX_COUNT);
        }
    //检查 & 纠正数据
    BatTester_Check(&BatTester.points[i]);
    //    lv_obj_set_style_local_text_color(__btnTable_label[ idx + MIN_ROW][0], LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, (i % 2) ? lv_color_hex(0xFFFFFF) : lv_color_hex(0xaaaaaa));
    //    lv_obj_set_style_local_text_color(__btnTable_label[ idx + MIN_ROW][1], LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, (i % 2) ? lv_color_hex(0xFFFFFF) : lv_color_hex(0xaaaaaa));
    //    lv_obj_set_style_local_text_color(__btnTable_label[ idx + MIN_ROW][2], LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, (i % 2) ? lv_color_hex(0xFFFFFF) : lv_color_hex(0xaaaaaa));
    //    lv_obj_set_style_local_text_color(__btnTable_label[ idx + MIN_ROW][3], LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, (i % 2) ? lv_color_hex(0xFFFFFF) : lv_color_hex(0xaaaaaa));
    //    lv_obj_set_style_local_text_color(__btnTable_label[ idx + MIN_ROW][4], LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, (i % 2) ? lv_color_hex(0xFFFFFF) : lv_color_hex(0xaaaaaa));
    static char tempString[64] = {0};
    sprintf(tempString, "%3d", i);
    lv_label_set_text(__btnTable_label[ idx + MIN_ROW][0], tempString);
    #if 1
    //    __Volt_Set_handler(__btnTable_label[ idx + MIN_ROW][1],LV_EVENT_REFRESH);
    //    __Curr_Set_handler(__btnTable_label[ idx + MIN_ROW][2],LV_EVENT_REFRESH);
    //    __Time_Set_handler(__btnTable_label[ idx + MIN_ROW][3],LV_EVENT_REFRESH);
    //    __Protect_Set_handler(__btnTable_label[ idx + MIN_ROW][4],LV_EVENT_REFRESH);
    Set_RefreshUI(__btnTable_label[ idx + MIN_ROW][1], NULL, BAT_TESTER_VOL_SET_FORM, BatTester.points[i].vol);
    Set_RefreshUI(__btnTable_label[ idx + MIN_ROW][2], NULL, BAT_TESTER_AMP_SET_FORM, BatTester.points[i].amp);
    Set_RefreshUI(__btnTable_label[ idx + MIN_ROW][3], NULL, BAT_TESTER_KT_SET_FORM, BatTester.points[i].kT);
    //StopSet_RefreshUI(__btnTable_label[ idx + MIN_ROW][4], NULL, &BatTester.points[i].stopCfg);
    StopSet_RefreshUI(__btnTable_label[ idx + MIN_ROW][4], NULL, BatTester.points[i].stopCfg, EDIT_STATE_DEFAULT);
    #else
    //
    float tempVol = 0.0f;
    float tempAmp = 0.0f;
    tempVol = BatTester.points[i].vol;
    tempAmp = BatTester.points[i].amp;
    sprintf(tempString, BAT_TESTER_VOL_SET_FORM, tempVol);
    lv_label_set_text(__btnTable_label[idx + MIN_ROW][1], tempString);
    sprintf(tempString, BAT_TESTER_AMP_SET_FORM, tempAmp);
    lv_label_set_text(__btnTable_label[idx + MIN_ROW][2], tempString);
    //保持时间 & 延迟时间
    sprintf(tempString, BAT_TESTER_KT_SET_FORM, BatTester.points[i].kT);
    lv_label_set_text(__btnTable_label[idx + MIN_ROW][3], tempString);
    //    sprintf(tempString, "V>60.00,I<60.00");
    //    lv_label_set_text(__btnTable_label[idx + MIN_ROW][4], tempString);
    #endif
}


/*
 * @brief       void BatteryTester_Page_Table_Refresh(int16_t baseIndex)
 * @details     刷新BatTester表格
 */
void BatteryTester_Page_Table_Refresh(int16_t baseIndex)
{
    if(lv_obj_is_visible(ui.BatTester_cont_Table) == 0)
    {
        return ;
    }
    //强制刷新 / 显示页变化时才刷新
    if((__refreshFlag == 1) || (__lastBaseIndex != baseIndex)) {
        __lastBaseIndex = baseIndex;
    } else {
        return;
    }
    __refreshFlag = 0;
    //循环刷新每一行
    for(uint16_t i = baseIndex; i < (baseIndex + (__ROW_CNT - MIN_ROW)); ++i) {
        __Tabel_Refresh_Row(baseIndex, i);
    }
}




#if 0

/*
 * @brief
 * @details
 */
static void StopSet_RefreshUI(lv_obj_t *obj, uint8_t *editIndex, BatTester_Stop_Def stopcfg[2], uint8_t edit)
{
    char volt_str[64] = {0};
    const char *logic_str = "";
    char curr_str[64] = {0};
    //电压
    switch(stopcfg[0].stop)
    {
        case _STOP_NONE:
            sprintf(volt_str, "true ");
            break;
        case _STOP_MORE:
            sprintf(volt_str, "Vo>"BAT_TESTER_VOL_SET_FORM"V", stopcfg[0].value);
            break;
        case _STOP_LESS:
            sprintf(volt_str, "Vo<"BAT_TESTER_VOL_SET_FORM"V", stopcfg[0].value);
            break;
    }
    switch(stopcfg[1].logic)
    {
        case _STOP_LOGIC_AND:
            logic_str = " & ";
            break;
        case _STOP_LOGIC_OR:
            logic_str = " | ";
            break;
    }
    //电流
    switch(stopcfg[1].stop)
    {
        case _STOP_NONE:
            sprintf(curr_str, " true");
            break;
        case _STOP_MORE:
            sprintf(curr_str, "Io>"BAT_TESTER_AMP_SET_FORM"A", stopcfg[1].value);
            break;
        case _STOP_LESS:
            sprintf(curr_str, "Io<"BAT_TESTER_AMP_SET_FORM"A", stopcfg[1].value);
            break;
    }
    //设置显示
    char disp_str[64] = {0};
    sprintf(disp_str, "%s%s%s", volt_str, logic_str, curr_str);
    //    if( (stopcfg[0].stop == _STOP_NONE) && (stopcfg[1].stop == _STOP_NONE)){
    //        lv_label_set_text(obj,disp_str);
    //        label_setSelStr(obj,disp_str,disp_str);
    //    }else
    {
        //设置聚焦
        switch(edit)
        {
            case EDIT_STATE_PROTECT_VOLT: {
                if((editIndex == NULL) || (stopcfg[0].stop == _STOP_NONE)) {
                    lv_label_set_text(obj, disp_str);
                    label_setSelStr(obj, volt_str, disp_str);
                } else {
                    label_setSelNum(obj, *editIndex, volt_str);
                    lv_label_set_text(obj, disp_str);
                }
            }
            break;
            case EDIT_STATE_PROTECT_LOGIC: {
                lv_label_set_text(obj, disp_str);
                label_setSelStr(obj, logic_str, disp_str);
            }
            break;
            case EDIT_STATE_PROTECT_CURR: {
                if((editIndex == NULL) || (stopcfg[1].stop == _STOP_NONE)) {
                    lv_label_set_text(obj, disp_str);
                    label_setSelStr(obj, curr_str, disp_str);
                } else {
                    lv_label_set_text(obj, disp_str);
                    label_setSelNum(obj, *editIndex, disp_str);
                }
            }
            break;
            default: {
                lv_label_set_text(obj, disp_str);
                lv_label_set_text_sel_start(obj, LV_LABEL_TEXT_SEL_OFF);
                lv_label_set_text_sel_end(obj, LV_LABEL_TEXT_SEL_OFF);
            }
            break;
        }
    }
}

void __Protect_Set_Volt_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //
    int16_t no = __lastBaseIndex + __edit_row_y - 1;
    if(no < 0) {
        no += BAT_TESTER_MAX_COUNT ;
    } else
        if(no > (BAT_TESTER_MAX_COUNT)) {
            no -= (BAT_TESTER_MAX_COUNT);
        }
    no %= BAT_TESTER_MAX_COUNT;
    //
    static uint8_t index_kt = 0;
    NumberInput_Process(7, BatTester.points[no].stopCfg[0].value =);
    float value = BatTester.points[no].stopCfg[0].value;
    value = MIN(value, VOL_MAX);
    value = MAX(value, VOL_MIN);
    BatTester.points[no].stopCfg[0].value = value;
    #if 1
    switch(event)
    {
        case LV_EVENT_KEY: {
            switch(key) {
                case LV_KEY_UP: {
                    float value = BatTester.points[no].stopCfg[0].value;
                    value += BatteryTester_V_step[index_kt];
                    value = MIN(value, VOL_MAX);
                    BatTester.points[no].stopCfg[0].value = value;
                }
                break;
                case LV_KEY_DOWN: {
                    float value = BatTester.points[no].stopCfg[0].value;
                    value -= BatteryTester_V_step[index_kt];
                    value = MAX(value, VOL_MIN);
                    BatTester.points[no].stopCfg[0].value = value;
                }
                break;
                case LV_KEY_LEFT:
                    if(index_kt < (ARRAY_COUNT(BatteryTester_V_step) - 1)) { index_kt++; }
                    break;
                case LV_KEY_RIGHT:
                    if(index_kt > 0) { index_kt--; }
                    break;
                case LV_KEY_ENTER:
                case LV_KEY_ENCODER: {
                    BatTester.points[no].stopCfg[0].stop = (++BatTester.points[no].stopCfg[0].stop) % (_STOP_MAX + 1);
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
            edit_State = EDIT_STATE_PROTECT_VOLT;
            break;
    }
    if(edit_State == EDIT_STATE_DEFAULT) {
        StopSet_RefreshUI(obj, NULL, BatTester.points[no].stopCfg, EDIT_STATE_DEFAULT);
    } else {
        StopSet_RefreshUI(obj, &index_kt, BatTester.points[no].stopCfg, edit_State);
    }
    #endif
}

void __Protect_Set_Logic_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //
    int16_t no = __lastBaseIndex + __edit_row_y - 1;
    if(no < 0) {
        no += BAT_TESTER_MAX_COUNT ;
    } else
        if(no > (BAT_TESTER_MAX_COUNT)) {
            no -= (BAT_TESTER_MAX_COUNT);
        }
    no %= BAT_TESTER_MAX_COUNT;
    //
    static uint8_t index_kt = 0;
    #if 1
    switch(event)
    {
        case LV_EVENT_DEFOCUSED:
            edit_State = EDIT_STATE_DEFAULT;
            break;
        case LV_EVENT_FOCUSED: {
            BatTester.points[no].stopCfg[1].logic = (++BatTester.points[no].stopCfg[1].logic) % 2;
        }
        break;
    }
    StopSet_RefreshUI(obj, NULL, BatTester.points[no].stopCfg, EDIT_STATE_DEFAULT);
    #endif
}

void __Protect_Set_Curr_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //
    int16_t no = __lastBaseIndex + __edit_row_y - 1;
    if(no < 0) {
        no += BAT_TESTER_MAX_COUNT ;
    } else
        if(no > (BAT_TESTER_MAX_COUNT)) {
            no -= (BAT_TESTER_MAX_COUNT);
        }
    no %= BAT_TESTER_MAX_COUNT;
    //
    static uint8_t index_kt = 0;
    NumberInput_Process(7, BatTester.points[no].stopCfg[1].value =);
    BatTester.points[no].stopCfg[1].value = MIN(BatTester.points[no].stopCfg[1].value, AMP_MAX);
    BatTester.points[no].stopCfg[1].value = MAX(BatTester.points[no].stopCfg[1].value, AMP_MIN);
    #if 1
    switch(event)
    {
        case LV_EVENT_KEY: {
            switch(key) {
                case LV_KEY_UP: {
                    float value = BatTester.points[no].stopCfg[1].value;
                    value += BatteryTester_A_step[index_kt];
                    value = MIN(value, AMP_MAX);
                    BatTester.points[no].stopCfg[1].value = value;
                }
                break;
                case LV_KEY_DOWN: {
                    float value = BatTester.points[no].stopCfg[1].value;
                    value -= BatteryTester_A_step[index_kt];
                    value = MAX(value, AMP_MIN);
                    BatTester.points[no].stopCfg[1].value = value;
                }
                break;
                case LV_KEY_LEFT:
                    if(index_kt < (ARRAY_COUNT(BatteryTester_A_step) - 1)) { index_kt++; }
                    break;
                case LV_KEY_RIGHT:
                    if(index_kt > 0) { index_kt--; }
                    break;
                case LV_KEY_ENTER:
                case LV_KEY_ENCODER: {
                    BatTester.points[no].stopCfg[1].stop = (++BatTester.points[no].stopCfg[1].stop) % (_STOP_MAX + 1);
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
            edit_State = EDIT_STATE_PROTECT_CURR;
            break;
    }
    if(edit_State == EDIT_STATE_DEFAULT) {
        StopSet_RefreshUI(obj, NULL, BatTester.points[no].stopCfg, EDIT_STATE_DEFAULT);
    } else {
        StopSet_RefreshUI(obj, &index_kt, BatTester.points[no].stopCfg, edit_State);
    }
    #endif
}

#endif
