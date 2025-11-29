#include "ListOut.h"
#include "ListPage.h"
#include "ListPage_Table.h"
#include "List_Interface.h"
#include "InputWidget.h"

#include "BtnTree.h"

#define __ROW_CNT 9 //行数
#define __COL_CNT 4 //列数

//按键表格
static lv_obj_t *__btnTable_label[__ROW_CNT][__COL_CNT] = {0};
static uint16_t __table_x = 1;
static const uint16_t __btnTable_y = 6;
static const uint16_t __btnTable_width[__COL_CNT] = {60, 90, 90, 85};
static const uint16_t __btnTable_height = 22;


lv_obj_t *list_voltage_sel_node;
lv_obj_t *list_current_sel_node;
lv_obj_t *list_ktime_sel_node;

static void __btnTable_DrawLine(lv_obj_t *backg)
{
    static lv_point_t line_point_V[] = {{0, 0}, {330, 0}};
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
        lv_obj_set_size(line_V, 330, 0);
        lv_line_set_points(line_V, line_point_V, 2);
        lv_obj_set_style_local_line_color(line_V, LV_LINE_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
        if(i == (line_V_Count - 1)) {
            y_v += __btnTable_height + 1 + 1;
            line_V = lv_line_create(backg, NULL);
            lv_obj_set_pos(line_V, x_v, y_v);
            lv_obj_set_size(line_V, 330, 0);
            lv_line_set_points(line_V, line_point_V, 2);
            lv_obj_set_style_local_line_color(line_V, LV_LINE_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
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
        lv_obj_set_style_local_line_color(line_H, LV_LINE_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
        if(j == (line_H_Count - 1)) {
            x_h += lv_obj_get_width(__btnTable_label[0][j]) + 1;
            line_H = lv_line_create(backg, NULL);
            lv_obj_set_pos(line_H, x_h, y_h);
            lv_obj_set_size(line_H, 0, 215);
            lv_line_set_points(line_H, line_point_H, 2);
            lv_obj_set_style_local_line_color(line_H, LV_LINE_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
        }
    }
}

void list_btnTable_Init(void)
{
    lv_obj_t *backg = ui.ListPage_cont_Table;
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
            lv_obj_set_style_local_text_letter_space(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 2);
            if(i == 0) {
                lv_obj_set_style_local_text_font(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_16);
                lv_obj_set_size(label, __btnTable_width[j], __btnTable_height);
                lv_obj_set_pos(label, __table_x, __btnTable_y);
                lv_obj_set_style_local_text_color(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0, 255, 255));
            } else {
                lv_obj_set_style_local_text_font(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_AlibabaPuHuiTi_Light_16);
                lv_obj_set_size(label, __btnTable_width[j], __btnTable_height);
                lv_obj_set_pos(label, __table_x, __btnTable_y + ((__btnTable_height + 1 + 1) + (i - 1) * (__btnTable_height + 1)));
                lv_obj_set_style_local_text_color(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(255, 255, 255));
            }
            lv_label_set_align(label, LV_LABEL_ALIGN_CENTER);
            __btnTable_label[i][j] = label;
        }
    }
    __btnTable_DrawLine(backg);
    list_voltage_sel_node = __btnTable_label[4][1];
    list_current_sel_node = __btnTable_label[4][2];
    list_ktime_sel_node = __btnTable_label[4][3];
}





//List表格强制刷新标志  1:需要刷新
static uint8_t __refreshFlag = 1;

/*
 * @brief       void ListPage_Table_Refresh(int16_t baseIndex)
 * @details     刷新List表格
 */
void ListPage_Table_Refresh(int16_t baseIndex);

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


//编辑数据
static uint8_t edit_flag = 0;
static float editMax = 0;
static float editMin = 0;
static float *editdata = NULL;
static const char *dispfmt = "%f";
static const float *stepArray = NULL;
static uint16_t arraySize = 0;
static const MultStr_Def *edit_minTips = NULL;
static const MultStr_Def *edit_maxTips = NULL;
static uint16_t editStep = 0;
static void ListPage_Table_Edit_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return ;
    }
    NumberInput_Process(7, *editdata =);
    float temp = *editdata;
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key) {
                case LV_KEY_UP: {
                    temp += stepArray[editStep];
                }
                break;
                case LV_KEY_DOWN: {
                    temp -= stepArray[editStep];
                }
                break;
                case LV_KEY_LEFT: {
                    if(editStep < (arraySize - 1))
                    {
                        editStep++;
                    }
                    else
                    {
                        editStep = 0;
                    }
                }
                break;
                case LV_KEY_RIGHT: {
                    if(editStep > 0)
                    {
                        editStep--;
                    }
                    else
                    {
                        editStep = arraySize - 1;
                    }
                }
                break;
                case LV_KEY_ENCODER:
                case LV_KEY_ENTER:
                case LV_KEY_ESC:
                case LV_KEY_RETURN: {
                    edit_flag = 0;
                    editMax = 0;
                    editMin = 0;
                    editdata = NULL;
                    dispfmt = "";
                    stepArray = NULL;
                    arraySize = 0;
                    edit_minTips = NULL;
                    edit_maxTips = NULL;
                    editStep = 0;
                    //lv_obj_set_style_local_text_sel_bg_color(obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0, 0, 0));
                    lv_label_set_text_sel_start(obj, LV_LABEL_TEXT_SEL_OFF);
                    lv_label_set_text_sel_end(obj, LV_LABEL_TEXT_SEL_OFF);
                }
                break;
            }
        }
        break;
        case LV_EVENT_CLICKED: {
            editStep = 0;
            lv_obj_set_style_local_text_sel_bg_color(obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0, 0, 255));
            lv_color_t color = lv_obj_get_style_text_color(obj, LV_LABEL_PART_MAIN);
            lv_obj_set_style_local_text_sel_color(obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, color);
        }
        break;
    }
    if(temp < editMin) {
        IF_MsgBox_Tips_Mult(edit_minTips);
        temp = editMin;
    }
    if(temp > editMax) {
        IF_MsgBox_Tips_Mult(edit_maxTips);
        temp = editMax;
    }
    *editdata = temp;
    if(edit_flag != 0) {
        char buf[32] = {0};
        sprintf(buf, dispfmt, *editdata);
        lv_label_set_text(obj, buf);
        label_setSelNum(obj, editStep, buf);
    }
}


void ListPage_SetCurrent(int16_t no)
{
    int16_t disp_baseIndex = no - __edit_row_y + 1;
    if(disp_baseIndex < 0) {
        disp_baseIndex += LISTOUT_MAX_COUNT;
    }
    disp_baseIndex = disp_baseIndex % LISTOUT_MAX_COUNT;
    ListPage_Table_Refresh(disp_baseIndex);
}



enum {
    EDIT_STATE_DEFAULT = 0,
    EDIT_STATE_VOLT,
    EDIT_STATE_CURR,
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

void List_Volt_Set_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //
    int16_t no = __lastBaseIndex + __edit_row_y - 1;
    if(no < 0) {
        no += LISTOUT_MAX_COUNT ;
    } else
        if(no > (LISTOUT_MAX_COUNT)) {
            no -= (LISTOUT_MAX_COUNT);
        }
    no %= LISTOUT_MAX_COUNT;
    float editMax = VOL_MAX;
    float editMin = VOL_MIN;
    float *editdata = &listoutInfo.points[no].vol;
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
    }
}



void List_Curr_Set_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //
    int16_t no = __lastBaseIndex + __edit_row_y - 1;
    if(no < 0) {
        no += LISTOUT_MAX_COUNT ;
    } else
        if(no > (LISTOUT_MAX_COUNT)) {
            no -= (LISTOUT_MAX_COUNT);
        }
    no %= LISTOUT_MAX_COUNT;
    float editMax = WAT_MAX / (listoutInfo.points[no].vol + 0.0001f);
    float editMin = AMP_MIN;
    float *editdata = &listoutInfo.points[no].amp;
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
    }
}


void List_Time_Set_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    //
    int16_t no = __lastBaseIndex + __edit_row_y - 1;
    if(no < 0) {
        no += LISTOUT_MAX_COUNT ;
    } else
        if(no > (LISTOUT_MAX_COUNT)) {
            no -= (LISTOUT_MAX_COUNT);
        }
    no %= LISTOUT_MAX_COUNT;
    float editMax = KT_MAX;
    float editMin = KT_MIN;
    float *editdata = &listoutInfo.points[no].kT;
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
                    temp += kT_step[index_kt];
                    temp = MIN(editMax, temp);
                    *editdata = temp;
                }
                break;
                case LV_KEY_DOWN: {
                    double temp = *editdata;
                    temp -= kT_step[index_kt];
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
                    if(index_kt < (sizeof(kT_step) / sizeof(kT_step[0]) - 1)) {
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
        Set_RefreshUI(obj, NULL, KEEP_TIME_FORM, *editdata);
    } else {
        Set_RefreshUI(obj, &index_kt, KEEP_TIME_FORM, *editdata);
    }
}



void ListPage_Table_handler(lv_obj_t *obj, lv_event_t event)
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
                    IF_ListOut_Set_State(LIST_STATE_RUNNING);
                    break;
                case LV_KEY_STOP:
                    IF_ListOut_Set_State(LIST_STATE_STOP);
                    break;
                case LV_KEY_CONTIUNE:
                    IF_ListOut_Set_State(LIST_STATE_RUNNING);
                    break;
                case LV_KEY_PAUSE:
                    IF_ListOut_Set_State(LIST_STATE_PAUSE);
                    break;
                case LV_KEY_UP:
                    ListPage_SetCurrent((--disp_baseIndex) + __edit_row_y - 1);
                    break;
                case LV_KEY_DOWN:
                    ListPage_SetCurrent((++disp_baseIndex) + __edit_row_y - 1);
                    break;
            }
        }
        break;
        case LV_EVENT_CLICKED: {
            __edit_col_x = 0;
        }
        case LV_EVENT_REFRESH:
        case LV_EVENT_FOCUSED: {
            lv_label_set_text_static(__btnTable_label[0][0], MultStr_GetS(&mStr_list_No));
            lv_label_set_text_static(__btnTable_label[0][1], MultStr_GetS(&mStr_list_Voltage));
            lv_label_set_text_static(__btnTable_label[0][2], MultStr_GetS(&mStr_list_Current));
            lv_label_set_text_static(__btnTable_label[0][3], MultStr_GetS(&mStr_list_keepT));
            __refreshFlag = 1;
            __edit_row_y = 4;
            ListPage_Table_Refresh(disp_baseIndex);
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
    lv_obj_set_size(ui.ListPage_img_back, width, height);
    lv_obj_set_pos(ui.ListPage_img_back, x, y);
    lv_obj_set_hidden(ui.ListPage_img_back, 0);
}


/*
 * @brief       static void __Tabel_Refresh_Row(uint16_t baseIndex,uint16_t list_no)
 * @details     刷新某一行
 */
static void __Tabel_Refresh_Row(uint16_t baseIndex, uint16_t list_no)
{
    baseIndex %= LISTOUT_MAX_COUNT;
    uint16_t i = list_no % LISTOUT_MAX_COUNT;
    int16_t idx = i - baseIndex;
    if(idx < 0) {
        idx += LISTOUT_MAX_COUNT ;
    } else
        if(idx > (LISTOUT_MAX_COUNT)) {
            idx -= (LISTOUT_MAX_COUNT);
        }
    static char tempString[64] = {0};
    sprintf(tempString, "%3d", i);
    lv_label_set_text(__btnTable_label[ idx + MIN_ROW][0], tempString);
    //检查 & 纠正数据
    ListOut_Check(&listoutInfo.points[i]);
    //
    #if 1
    Set_RefreshUI(__btnTable_label[ idx + MIN_ROW][1], NULL, VOL_SET_FORM, listoutInfo.points[i].vol);
    Set_RefreshUI(__btnTable_label[ idx + MIN_ROW][2], NULL, AMP_SET_FORM, listoutInfo.points[i].amp);
    Set_RefreshUI(__btnTable_label[ idx + MIN_ROW][3], NULL, KEEP_TIME_FORM, listoutInfo.points[i].kT);
    #else
    float tempVol = 0.0f;
    float tempAmp = 0.0f;
    tempVol = listoutInfo.points[i].vol;
    tempAmp = listoutInfo.points[i].amp;
    sprintf(tempString, VOL_SET_FORM, tempVol);
    lv_label_set_text(__btnTable_label[idx + MIN_ROW][1], tempString);
    sprintf(tempString, AMP_SET_FORM, tempAmp);
    lv_label_set_text(__btnTable_label[idx + MIN_ROW][2], tempString);
    //保持时间 & 延迟时间
    sprintf(tempString, KEEP_TIME_FORM, listoutInfo.points[i].kT);
    lv_label_set_text(__btnTable_label[idx + MIN_ROW][3], tempString);
    #endif
}


/*
 * @brief       void ListPage_Table_Refresh(int16_t baseIndex)
 * @details     刷新List表格
 */
void ListPage_Table_Refresh(int16_t baseIndex)
{
    if(lv_obj_is_visible(ui.ListPage_cont_Table) == 0)
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

