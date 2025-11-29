#include "PresetPage.h"
#include "SettingData.h"
#include "InputWidget.h"

Tree_Def *tree_preset;

#undef TABLE_ROW_CNT
#undef TABLE_COL_CNT
#define TABLE_ROW_CNT 9 //行数
#define TABLE_COL_CNT 6 //列数

#define MIN_ROW (1)
#define MAX_ROW (TABLE_ROW_CNT-1)
#define MIN_COL (1)
#define MAX_COL (TABLE_COL_CNT-1)
static lv_obj_t *table_label[TABLE_ROW_CNT][TABLE_COL_CNT] = {0};
static uint16_t table_x = 1;
static const uint16_t table_y = 6;
static const uint16_t table_width[TABLE_COL_CNT] = {33, 80, 80, 89, 89, 102};
static const uint16_t table_height = 22;

static void preset_btnTable_Init(void);
static void Preset_btnTable_DrawLine(lv_obj_t *backg);

lv_obj_t *preset_voltage_sel_node;
lv_obj_t *preset_current_sel_node;
lv_obj_t *preset_ovp_sel_node;
lv_obj_t *preset_ocp_sel_node;
lv_obj_t *preset_time_sel_node;


void preset_btnTable_Init(void)
{
    lv_obj_t *backg = ui.Preset_cont;
    for(uint8_t i = 0; i < (sizeof(table_label) / sizeof(table_label[0])); ++i)
    {
        table_x = 1;
        for(uint8_t j = 0; j < (sizeof(table_label[0]) / sizeof(table_label[0][0])); ++j)
        {
            lv_obj_t *label = lv_label_create(backg, NULL);
            lv_label_set_long_mode(label, LV_LABEL_LONG_BREAK);
            if(j > 0)
            {
                table_x += table_width[j - 1] + 1;
            }
            extern lv_font_t MultFont_16;
            if(i == 0) {
                lv_obj_set_size(label, table_width[j], table_height);
                lv_obj_set_pos(label, table_x, table_y);
                lv_obj_set_style_local_text_color(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0, 255, 255));
                lv_obj_set_style_local_text_font(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_16);
                lv_obj_set_style_local_text_letter_space(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 1);
            } else {
                lv_obj_set_size(label, table_width[j], table_height);
                lv_obj_set_pos(label, table_x, table_y + ((table_height + 1 + 1) + (i - 1) * (table_height + 1)));
                lv_obj_set_style_local_text_color(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(255, 255, 255));
                lv_obj_set_style_local_text_font(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_AlibabaPuHuiTi_Light_16);
                lv_obj_set_style_local_text_letter_space(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 2);
            }
            lv_label_set_align(label, LV_LABEL_ALIGN_CENTER);
            table_label[i][j] = label;
        }
    }
    Preset_btnTable_DrawLine(backg);
}
static void Preset_btnTable_DrawLine(lv_obj_t *backg)
{
    static lv_point_t line_point_V[] = {{0, 0}, {480, 0}};
    static lv_point_t line_point_H[] = {{0, 0}, {0, 210}};
    uint16_t line_V_Count = (sizeof(table_label) / sizeof(table_label[0]));
    for(uint8_t i = 0; i < line_V_Count; ++i) {
        //横线
        uint16_t x_v = lv_obj_get_x(table_label[i][0]) - 1;
        uint16_t y_v = lv_obj_get_y(table_label[i][0]) - 1;
        if(i == 0) {
            y_v = 2;
        }
        lv_obj_t *line_V = lv_line_create(backg, NULL);
        lv_obj_set_pos(line_V, x_v, y_v);
        lv_obj_set_size(line_V, 480, 0);
        lv_line_set_points(line_V, line_point_V, 2);
        lv_obj_set_style_local_line_color(line_V, LV_LINE_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
        if(i == (line_V_Count - 1)) {
            y_v += table_height + 1;
            line_V = lv_line_create(backg, NULL);
            lv_obj_set_pos(line_V, x_v, y_v);
            lv_obj_set_size(line_V, 480, 0);
            lv_line_set_points(line_V, line_point_V, 2);
            lv_obj_set_style_local_line_color(line_V, LV_LINE_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
        }
    }
    uint16_t line_H_Count = (sizeof(table_label[0]) / sizeof(table_label[0][0]));
    for(uint8_t j = 0; j < line_H_Count; ++j) {
        //竖线
        uint16_t x_h = lv_obj_get_x(table_label[0][j]) - 1;
        uint16_t y_h = 3;
        lv_obj_t *line_H = lv_line_create(backg, NULL);
        lv_obj_set_pos(line_H, x_h, y_h);
        lv_obj_set_size(line_H, 0, 210);
        lv_line_set_points(line_H, line_point_H, 2);
        lv_obj_set_style_local_line_color(line_H, LV_LINE_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
        if(j == (line_H_Count - 1)) {
            x_h += lv_obj_get_width(table_label[0][j]) + 1;
            line_H = lv_line_create(backg, NULL);
            lv_obj_set_pos(line_H, x_h, y_h);
            lv_obj_set_size(line_H, 0, 210);
            lv_line_set_points(line_H, line_point_H, 2);
            lv_obj_set_style_local_line_color(line_H, LV_LINE_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
        }
    }
}





static void __Table_setFocus(uint16_t row_y);

void Preset_Table_Refresh(int16_t baseIndex);
static void Preset_Table_Refresh_Row(uint16_t i);

#define CUR_EDIT_IDX (disp_baseIndex - MIN_ROW)
static int16_t disp_baseIndex = MIN_ROW;
static uint16_t edit_row_y = MIN_ROW;  //行数 [1,11]
static uint16_t edit_col_x = MIN_COL;  //列数 [1,5]



enum {
    EDIT_STATE_DEFAULT = 0,
    EDIT_STATE_VOLT,
    EDIT_STATE_CURR,
    EDIT_STATE_OCP,
    EDIT_STATE_OVP,
    EDIT_STATE_TIME,
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
void Preset_Volt_Set_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = table_label[disp_baseIndex][1];
    preset_voltage_sel_node = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //
    float editMax = VOL_MAX;
    float editMin = VOL_MIN;
    float *editdata = &CurGroup.groupData.Preset[CUR_EDIT_IDX].V_Set;
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
                    temp += V_step[index_v];
                    temp = MIN(editMax, temp);
                    *editdata = temp;
                }
                break;
                case LV_KEY_DOWN: {
                    double temp = *editdata;
                    temp -= V_step[index_v];
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
                    if(index_v < (sizeof(V_step) / sizeof(V_step[0]) - 1)) {
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
        Set_RefreshUI(obj, NULL, VOL_SET_FORM, *editdata);
    } else {
        Set_RefreshUI(obj, &index_v, VOL_SET_FORM, *editdata);
        eeprom_OutSet_RequestSave(0);
    }
}
void Preset_Curr_Set_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = table_label[disp_baseIndex][2];
    preset_current_sel_node = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //
    float editMax = AMP_MAX;
    float editMin = AMP_MIN;
    float *editdata = &CurGroup.groupData.Preset[CUR_EDIT_IDX].I_Set;
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
                    temp += A_step[index_a];
                    temp = MIN(editMax, temp);
                    *editdata = temp;
                }
                break;
                case LV_KEY_DOWN: {
                    double temp = *editdata;
                    temp -= A_step[index_a];
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
                    if(index_a < (sizeof(A_step) / sizeof(A_step[0]) - 1)) {
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
        Set_RefreshUI(obj, NULL, AMP_SET_FORM, *editdata);
    } else {
        Set_RefreshUI(obj, &index_a, AMP_SET_FORM, *editdata);
        eeprom_OutSet_RequestSave(0);
    }
}


static void __Protect_RefreshUI(lv_obj_t *obj, uint8_t *editIndex, const char *dispfmt, double value, uint8_t onoff)
{
    static char stringSet[64] = {0};
    if(obj == NULL) { return ; }
    //
    sprintf(stringSet, dispfmt, value);
    sprintf(stringSet, "%s%s", stringSet, (onoff) ? LV_SYMBOL_OK : LV_SYMBOL_CLOSE);
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
void Preset_OVP_Set_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = table_label[disp_baseIndex][3];
    preset_ovp_sel_node = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //
    float editMax = VOL_MAX;
    float editMin = VOL_MIN;
    float *editdata = &CurGroup.groupData.Preset[CUR_EDIT_IDX].OVP;
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
                    temp += V_step[index_v];
                    temp = MIN(editMax, temp);
                    *editdata = temp;
                }
                break;
                case LV_KEY_DOWN: {
                    double temp = *editdata;
                    temp -= V_step[index_v];
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
                    if(index_v < (sizeof(V_step) / sizeof(V_step[0]) - 1)) {
                        index_v++;
                    }
                }
                break;
                case LV_KEY_ENTER:
                    CurGroup.groupData.Preset[CUR_EDIT_IDX].OVP_onoff = !CurGroup.groupData.Preset[CUR_EDIT_IDX].OVP_onoff;
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
            if(edit_State != EDIT_STATE_OVP) {
                edit_State = EDIT_STATE_OVP;
            } else {
                CurGroup.groupData.Preset[CUR_EDIT_IDX].OVP_onoff = !CurGroup.groupData.Preset[CUR_EDIT_IDX].OVP_onoff;
            }
            break;
    }
    if(edit_State != EDIT_STATE_OVP) {
        __Protect_RefreshUI(obj, NULL, VOL_SET_FORM, *editdata, CurGroup.groupData.Preset[CUR_EDIT_IDX].OVP_onoff);
    } else {
        __Protect_RefreshUI(obj, &index_v, VOL_SET_FORM, *editdata, CurGroup.groupData.Preset[CUR_EDIT_IDX].OVP_onoff);
        eeprom_OutSet_RequestSave(0);
    }
}
void Preset_OCP_Set_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = table_label[disp_baseIndex][4];
    preset_ocp_sel_node = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //
    float editMax = AMP_MAX;
    float editMin = AMP_MIN;
    float *editdata = &CurGroup.groupData.Preset[CUR_EDIT_IDX].OCP;
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
                    temp += A_step[index_a];
                    temp = MIN(editMax, temp);
                    *editdata = temp;
                }
                break;
                case LV_KEY_DOWN: {
                    double temp = *editdata;
                    temp -= A_step[index_a];
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
                    if(index_a < (sizeof(A_step) / sizeof(A_step[0]) - 1)) {
                        index_a++;
                    }
                }
                break;
                case LV_KEY_ENTER:
                    CurGroup.groupData.Preset[CUR_EDIT_IDX].OVP_onoff = !CurGroup.groupData.Preset[CUR_EDIT_IDX].OVP_onoff;
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
            if(edit_State != EDIT_STATE_OCP) {
                edit_State = EDIT_STATE_OCP;
            } else {
                CurGroup.groupData.Preset[CUR_EDIT_IDX].OCP_onoff = !CurGroup.groupData.Preset[CUR_EDIT_IDX].OCP_onoff;
            }
            break;
    }
    if(edit_State != EDIT_STATE_OCP) {
        __Protect_RefreshUI(obj, NULL, AMP_SET_FORM, *editdata, CurGroup.groupData.Preset[CUR_EDIT_IDX].OCP_onoff);
    } else {
        __Protect_RefreshUI(obj, &index_a, AMP_SET_FORM, *editdata, CurGroup.groupData.Preset[CUR_EDIT_IDX].OCP_onoff);
        eeprom_OutSet_RequestSave(0);
    }
}
void Preset_Time_Set_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = table_label[disp_baseIndex][5];
    preset_ocp_sel_node = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //
    float editMax = TIMEOFF_MAX;
    float editMin = TIMEOFF_MIN;
    float *editdata = &CurGroup.groupData.Preset[CUR_EDIT_IDX].TimeOff;
    //
    static uint8_t index_t = 0;
    NumberInput_Process(7, *editdata =);
    *editdata = MIN(editMax, *editdata);
    *editdata = MAX(editMin, *editdata);
    switch(event)
    {
        case LV_EVENT_KEY: {
            switch(key) {
                case LV_KEY_UP: {
                    double temp = *editdata;
                    temp += timeoff_step[index_t];
                    temp = MIN(editMax, temp);
                    *editdata = temp;
                }
                break;
                case LV_KEY_DOWN: {
                    double temp = *editdata;
                    temp -= timeoff_step[index_t];
                    temp = MAX(editMin, temp);
                    *editdata = temp;
                }
                break;
                case LV_KEY_RIGHT: {
                    if(index_t > 0) {
                        index_t--;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(index_t < (sizeof(timeoff_step) / sizeof(timeoff_step[0]) - 1)) {
                        index_t++;
                    }
                }
                break;
                case LV_KEY_ENTER:
                    CurGroup.groupData.Preset[CUR_EDIT_IDX].Timeout_onoff = !CurGroup.groupData.Preset[CUR_EDIT_IDX].Timeout_onoff;
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
            if(edit_State != EDIT_STATE_TIME) {
                edit_State = EDIT_STATE_TIME;
            } else {
                CurGroup.groupData.Preset[CUR_EDIT_IDX].Timeout_onoff = !CurGroup.groupData.Preset[CUR_EDIT_IDX].Timeout_onoff;
            }
            break;
    }
    if(edit_State != EDIT_STATE_TIME) {
        __Protect_RefreshUI(obj, NULL, TIMEOFF_SET_FORM, *editdata, CurGroup.groupData.Preset[CUR_EDIT_IDX].Timeout_onoff);
    } else {
        __Protect_RefreshUI(obj, &index_t, TIMEOFF_SET_FORM, *editdata, CurGroup.groupData.Preset[CUR_EDIT_IDX].Timeout_onoff);
        eeprom_OutSet_RequestSave(0);
    }
}
//eeprom_OutSet_RequestSave(0);

#include "Interface.h"
static void Preset_Save(void)
{
    UI_IF_Power_Preset_Save(CUR_EDIT_IDX);
}

static void Preset_Load(void)
{
    UI_IF_Power_Preset_Load(CUR_EDIT_IDX);
}


void PresetCont_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    switch(event)
    {
        case LV_EVENT_KEY: {
            switch(key)
            {
                case LV_KEY_SAVE: {
                    Preset_Save();
                    Preset_Table_Refresh_Row(disp_baseIndex - MIN_ROW);
                    IF_MsgBox_Tips_Mult(&mStr_Save_Tips);
                }
                break;
                case LV_KEY_LOAD: {
                    Preset_Load();
                    Preset_Table_Refresh_Row(disp_baseIndex - MIN_ROW);
                    UI_IF_Display_Go_to_Page(PAGE_HOME);
                    IF_MsgBox_Tips_Mult(&mStr_Load_Tips);
                }
                break;
                case LV_KEY_UP: {
                    disp_baseIndex--;
                    if(MIN_ROW > disp_baseIndex) {
                        disp_baseIndex = MIN_ROW;
                    }
                    __Table_setFocus(disp_baseIndex);
                }
                break;
                case LV_KEY_DOWN: {
                    disp_baseIndex++;
                    if(MAX_ROW < disp_baseIndex) {
                        disp_baseIndex = MAX_ROW;
                    }
                    __Table_setFocus(disp_baseIndex);
                }
                break;
                case LV_KEY_ENTER: {
                } break;
            }
        }
        break;
        case LV_EVENT_CLICKED:
        case LV_EVENT_REFRESH: {
            __Table_setFocus(disp_baseIndex);
            Preset_Table_Refresh(0);
        }
        break;
    }
    preset_voltage_sel_node = table_label[disp_baseIndex][1];
    preset_current_sel_node = table_label[disp_baseIndex][2];
    preset_ovp_sel_node = table_label[disp_baseIndex][3];
    preset_ocp_sel_node = table_label[disp_baseIndex][4];
    preset_time_sel_node = table_label[disp_baseIndex][5];
}



void PresetPage_GroupCreate(void)
{
    //加载UI
    setup_scr_Preset(&ui);
    lv_obj_set_parent(ui.Preset_cont, ui.Back_cont_back);
    preset_btnTable_Init();
    PresetPage_Enter();
    PresetPage_Exit();
}

/*
 * @brief       void PresetPage_Enter(void)
 * @details     进入OutOption页面
 */
void PresetPage_Enter(void)
{
    lv_obj_set_hidden(ui.Preset_cont, 0);
    lv_event_send_refresh_recursive(ui.Preset_cont);
    //
    lv_label_set_text_static(table_label[0][0], MultStr_GetS(&mStr_Preset_No));
    lv_label_set_text_static(table_label[0][1], MultStr_GetS(&mStr_Preset_Vol));
    lv_label_set_text_static(table_label[0][2], MultStr_GetS(&mStr_Preset_Cur));
    lv_label_set_text_static(table_label[0][3], MultStr_GetS(&mStr_Preset_OVP));
    lv_label_set_text_static(table_label[0][4], MultStr_GetS(&mStr_Preset_OCP));
    lv_label_set_text_static(table_label[0][5], MultStr_GetS(&mStr_Preset_TimeOff));
}

/*
 * @brief       void PresetPage_Exit(void)
 * @details     退出OutOption页面
 */
void PresetPage_Exit(void)
{
    lv_obj_set_hidden(ui.Preset_cont, 1);
}


/*
 * @brief       static void Preset_Table_Refresh_Row(uint16_t baseIndex,uint16_t list_no)
 * @details     刷新某一行
 */
static void Preset_Table_Refresh_Row(uint16_t i)
{
    static char tempString[64] = {0};
    sprintf(tempString, "%3d", i);
    lv_label_set_text(table_label[ i + MIN_ROW][0], tempString);
    //电压 & 电流 (当out = 0时,电压 电流为 0)
    float tempVol = 0.0f;
    float tempAmp = 0.0f;
    float tempOvp = 0.0f;
    float tempOcp = 0.0f;
    float tempTimeOff = 0.0f;
    uint8_t timeout_onoff = 0;
    uint8_t ovp_onoff = 0;
    uint8_t ocp_onoff = 0;
    tempVol = CurGroup.groupData.Preset[i].V_Set;
    tempAmp = CurGroup.groupData.Preset[i].I_Set;
    tempOvp = CurGroup.groupData.Preset[i].OVP;
    tempOcp = CurGroup.groupData.Preset[i].OCP;
    tempTimeOff = CurGroup.groupData.Preset[i].TimeOff;
    timeout_onoff = CurGroup.groupData.Preset[i].Timeout_onoff;
    ovp_onoff = CurGroup.groupData.Preset[i].OVP_onoff;
    ocp_onoff = CurGroup.groupData.Preset[i].OCP_onoff;
    #if 1
    Set_RefreshUI(table_label[i + MIN_ROW][1], NULL, VOL_SET_FORM, tempVol);
    Set_RefreshUI(table_label[i + MIN_ROW][2], NULL, AMP_SET_FORM, tempAmp);
    __Protect_RefreshUI(table_label[i + MIN_ROW][3], NULL, VOL_SET_FORM, tempOvp, ovp_onoff);
    __Protect_RefreshUI(table_label[i + MIN_ROW][4], NULL, AMP_SET_FORM, tempOcp, ocp_onoff);
    __Protect_RefreshUI(table_label[i + MIN_ROW][5], NULL, TIMEOFF_SET_FORM, tempTimeOff, timeout_onoff);
    #else
    //VOL
    sprintf(tempString, VOL_SET_FORM, tempVol);
    lv_label_set_text(table_label[i + MIN_ROW][1], tempString);
    //AMP
    sprintf(tempString, AMP_SET_FORM, tempAmp);
    lv_label_set_text(table_label[i + MIN_ROW][2], tempString);
    //OVP
    sprintf(tempString, VOL_LIMIT_FORM"%s", tempOvp, (ovp_onoff) ? LV_SYMBOL_OK : LV_SYMBOL_CLOSE);
    lv_label_set_text(table_label[i + MIN_ROW][3], tempString);
    //OCP
    sprintf(tempString, AMP_LIMIT_FORM"%s", tempOcp, (ocp_onoff) ? LV_SYMBOL_OK : LV_SYMBOL_CLOSE);
    lv_label_set_text(table_label[i + MIN_ROW][4], tempString);
    //定时关闭
    sprintf(tempString, TIMEOFF_SET_FORM"%s", tempTimeOff, (timeout_onoff) ? LV_SYMBOL_OK : LV_SYMBOL_CLOSE);
    lv_label_set_text(table_label[i + MIN_ROW][5], tempString);
    #endif
}


/*
 * @brief       void Preset_Table_Refresh(int16_t baseIndex)
 * @details     刷新Preset表格
 */
void Preset_Table_Refresh(int16_t baseIndex)
{
    if(lv_obj_is_visible(ui.Preset_cont) == 0)
    {
        return ;
    }
    //循环刷新每一行
    for(uint16_t i = baseIndex; i < (baseIndex + (TABLE_ROW_CNT - MIN_ROW)); ++i) {
        Preset_Table_Refresh_Row(i);
    }
}




#if 1



//聚焦特定行风格
void __Table_setFocus(uint16_t row_y)
{
    uint16_t width = 0;
    uint16_t height = 0;
    uint16_t x = 0;
    uint16_t y = 0;
    for(uint8_t i = 0; i < TABLE_COL_CNT; ++i) {
        width += lv_obj_get_width(table_label[row_y][i]);
    }
    height = table_height;
    width += TABLE_COL_CNT - 1;
    x = lv_obj_get_x(table_label[row_y][0]);
    y = lv_obj_get_y(table_label[row_y][0]);
    lv_obj_set_size(ui.Preset_img_itemSel, width, height);
    lv_obj_set_pos(ui.Preset_img_itemSel, x, y);
    lv_obj_set_hidden(ui.Preset_img_itemSel, 0);
}

#endif


