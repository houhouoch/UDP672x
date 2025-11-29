#include "ListTempPage.h"
#include "ListTemp_Interface.h"

ListTempInfo_Def ListTempInfo = {
    .startpoint = 0,
    .totalCount = LISTOUT_MAX_COUNT,
    .interval = KT_MIN,

    .param[LISTTEMP_EDIT_OBJECT_VOL] = {
        .minValue = VOL_MIN,
        .maxValue = VOL_MAX,
        .Symmetry = 50,
        .pluseWidth = 0.1,
        .plusePeriod = 0.2,
    },
    .param[LISTTEMP_EDIT_OBJECT_AMP] = {
        .minValue = AMP_MIN,
        .maxValue = AMP_MAX,
        .Symmetry = 50,
        .pluseWidth = 0.1,
        .plusePeriod = 0.2,
    },
};


/*
 * @brief       static void _Set_TempType(uint8_t type)
 * @details     修改模板类型
 */
static void _Set_TempType(uint8_t type);

/*
 * @brief       static void _Chart_Update(lv_obj_t* chart)
 * @details     更新波形图
 */
static void _Chart_Update(lv_obj_t *chart);
/*
 * @brief       static void _Chart_SetPointCount(uint16_t count)
 * @details     设置点数
 */
static void _Chart_SetPointCount(lv_obj_t *chart, uint16_t count);
/*
 * @brief       static void _Chart_SetEdit(uint8_t edit)
 * @details     设置波形编辑对象(改刻度尺)
 */
static void _Chart_SetEdit(lv_obj_t *chart, float maxValue);






/*
 * @brief       static void _Set_TempType(uint8_t type)
 * @details     修改模板类型
 */
static void _Set_TempType(uint8_t type)
{
    uint16_t x, y = 0;
    lv_obj_t *obj = NULL;
    const char *string = "";
    switch(type)
    {
        case TEMP_TYPE_Sin:          //正弦波       反相/角度
            string = MultStr_GetS(&mStr_list_temp_Sin);
            obj = ui.ListTempPage_imgbtn_sin;
            break;
        case TEMP_TYPE_Pulse:        //脉冲波       占空比
            string = MultStr_GetS(&mStr_list_temp_Pluse);
            obj = ui.ListTempPage_imgbtn_pluse;
            break;
        case TEMP_TYPE_Ramp:         //斜波         对称性
            string = MultStr_GetS(&mStr_list_temp_Ramp);
            obj = ui.ListTempPage_imgbtn_Ramp;
            break;
        case TEMP_TYPE_Stair_Up:     //阶梯上升
            string = MultStr_GetS(&mStr_list_temp_Stair_Up);
            obj = ui.ListTempPage_imgbtn_StairUp;
            break;
        case TEMP_TYPE_Stair_Down:   //阶梯下降
            string = MultStr_GetS(&mStr_list_temp_Stair_Down);
            obj = ui.ListTempPage_imgbtn_StairDn;
            break;
        case TEMP_TYPE_Stair_UpDown: //阶梯上下
            string = MultStr_GetS(&mStr_list_temp_Stair_UD);
            obj = ui.ListTempPage_imgbtn_StairUD;
            break;
        case TEMP_TYPE_expUp:        //指数上升      指数
            string = MultStr_GetS(&mStr_list_temp_exp_Up);
            obj = ui.ListTempPage_imgbtn_expUp;
            break;
        case TEMP_TYPE_expDown:      //指数下降      指数
            string = MultStr_GetS(&mStr_list_temp_exp_Down);
            obj = ui.ListTempPage_imgbtn_expDn;
            break;
    }
    if(obj != NULL) {
        x = lv_obj_get_x(obj);
        y = lv_obj_get_y(obj);
        BtnLabel_Set_Edit_Value(ui.ListTempPage_btn_type_label, string);
        lv_obj_set_pos(ui.ListTempPage_imgbtn_sel, x, y);
    }
}



#define PI (3.1415)
static void _generate_Wave_Sin(void)
{
    float interval = ListTempInfo.interval;         //时间间隔
    uint16_t pointCount = ListTempInfo.totalCount;  //生成点数
    #if 0
    float startAngle = ListTempInfo.param[ListTempInfo.edit_obj].sinAngleRange[0];
    float endAngle = ListTempInfo.param[ListTempInfo.edit_obj].sinAngleRange[1];
    #else
    float startAngle = 0;
    float endAngle = 360;
    #endif
    float angleStep = (endAngle - startAngle) / (pointCount);
    //步进角度
    for(uint16_t i = 0; i < pointCount; ++i)
    {
        switch(ListTempInfo.edit_obj) {
            case LISTTEMP_EDIT_OBJECT_VOL: {
                float min = ListTempInfo.param[LISTTEMP_EDIT_OBJECT_VOL].minValue;      //最小值
                float max = ListTempInfo.param[LISTTEMP_EDIT_OBJECT_VOL].maxValue;      //最大值
                if(ListTempInfo.param[LISTTEMP_EDIT_OBJECT_VOL].invert == 0) {
                    ListTempInfo.tempPoints[i].vol = min + (max - min) / 2 * (1 + sin((startAngle + (float)i * angleStep) * (2 * PI / 360.0f)));
                } else {
                    ListTempInfo.tempPoints[i].vol = min + (max - min) / 2 * (1 - sin((startAngle + (float)i * angleStep) * (2 * PI / 360.0f)));
                }
            }
            break;
            case LISTTEMP_EDIT_OBJECT_AMP: {
                float min = ListTempInfo.param[LISTTEMP_EDIT_OBJECT_AMP].minValue;      //最小值
                float max = ListTempInfo.param[LISTTEMP_EDIT_OBJECT_AMP].maxValue;      //最大值
                if(ListTempInfo.param[LISTTEMP_EDIT_OBJECT_AMP].invert == 0) {
                    ListTempInfo.tempPoints[i].amp = min + (max - min) / 2 * (1 + sin((startAngle + (float)i * angleStep) * (2 * PI / 360.0f)));
                } else {
                    ListTempInfo.tempPoints[i].amp = min + (max - min) / 2 * (1 - sin((startAngle + (float)i * angleStep) * (2 * PI / 360.0f)));
                }
            }
            break;
        }
        ListTempInfo.tempPoints[i].kT = interval;
    }
}


static void _generate_Wave_Pluse(void)
{
    float min = ListTempInfo.param[ListTempInfo.edit_obj].minValue;      //最小值
    float max = ListTempInfo.param[ListTempInfo.edit_obj].maxValue;      //最大值
    uint8_t flag_inverte = ListTempInfo.param[ListTempInfo.edit_obj].invert;
    switch(ListTempInfo.edit_obj) {
        case LISTTEMP_EDIT_OBJECT_VOL: {
            ListTempInfo.tempPoints[0].vol = (!flag_inverte) ? max : min;
            ListTempInfo.tempPoints[1].vol = (!flag_inverte) ? min : max;
        }
        break;
        case LISTTEMP_EDIT_OBJECT_AMP: {
            ListTempInfo.tempPoints[0].amp = (!flag_inverte) ? max : min;
            ListTempInfo.tempPoints[1].amp = (!flag_inverte) ? min : max;
        }
        break;
    }
    ListTempInfo.tempPoints[flag_inverte].kT = ListTempInfo.param[ListTempInfo.edit_obj].pluseWidth;
    ListTempInfo.tempPoints[!flag_inverte].kT = ListTempInfo.param[ListTempInfo.edit_obj].plusePeriod - ListTempInfo.tempPoints[0].kT;
}

static void _generate_Wave_Ramp(void)
{
    uint16_t pointCount = ListTempInfo.totalCount;
    float interval = ListTempInfo.interval;         //时间间隔
    float min = ListTempInfo.param[ListTempInfo.edit_obj].minValue;      //最小值
    float max = ListTempInfo.param[ListTempInfo.edit_obj].maxValue;      //最大值
    uint8_t flag_inverte = ListTempInfo.param[ListTempInfo.edit_obj].invert;
    //占空比[0,100],步进0.1
    float duty = ListTempInfo.param[ListTempInfo.edit_obj].Symmetry;
    //翻转点
    uint16_t invertPoint = pointCount * (float)(duty / 100);
    for(uint16_t i = 0; i < pointCount; ++i)
    {
        switch(ListTempInfo.edit_obj) {
            case LISTTEMP_EDIT_OBJECT_VOL: {
                if(i < invertPoint) {
                    ListTempInfo.tempPoints[i].vol = (flag_inverte) ?
                                                     max - (max - min) / (invertPoint) * i :  min + (max - min) / (invertPoint) * i;
                } else {
                    ListTempInfo.tempPoints[i].vol = (flag_inverte) ?
                                                     min + (max - min) / (pointCount - invertPoint - 1) * (i - invertPoint) : max - (max - min) / (pointCount - invertPoint - 1) * (i - invertPoint);
                }
            }
            break;
            case LISTTEMP_EDIT_OBJECT_AMP: {
                if(i < invertPoint) {
                    ListTempInfo.tempPoints[i].amp = (flag_inverte) ?
                                                     max - (max - min) / (invertPoint) * i : min + (max - min) / (invertPoint) * i;
                } else {
                    ListTempInfo.tempPoints[i].amp = (flag_inverte) ?
                                                     min + (max - min) / (pointCount - invertPoint - 1) * (i - invertPoint) : max - (max - min) / (pointCount - invertPoint - 1) * (i - invertPoint);
                }
            }
            break;
        }
        ListTempInfo.tempPoints[i].kT = interval;
    }
}


static void _generate_Wave_StairUp(void)
{
    uint16_t pointCount = ListTempInfo.totalCount;
    float interval = ListTempInfo.interval;         //时间间隔
    float min = ListTempInfo.param[ListTempInfo.edit_obj].minValue;      //最小值
    float max = ListTempInfo.param[ListTempInfo.edit_obj].maxValue;      //最大值
    for(uint16_t i = 0; i < pointCount; ++i)
    {
        switch(ListTempInfo.edit_obj) {
            case LISTTEMP_EDIT_OBJECT_VOL: {
                ListTempInfo.tempPoints[i].vol = min + (max - min) / (pointCount - 1) * i;
            }
            break;
            case LISTTEMP_EDIT_OBJECT_AMP: {
                ListTempInfo.tempPoints[i].amp = min + (max - min) / (pointCount - 1) * i;
            }
            break;
        }
        ListTempInfo.tempPoints[i].kT = interval;
    }
}

static void _generate_Wave_StairDown(void)
{
    uint16_t pointCount = ListTempInfo.totalCount;
    float interval = ListTempInfo.interval;         //时间间隔
    float min = ListTempInfo.param[ListTempInfo.edit_obj].minValue;      //最小值
    float max = ListTempInfo.param[ListTempInfo.edit_obj].maxValue;      //最大值
    for(uint16_t i = 0; i < pointCount; ++i)
    {
        switch(ListTempInfo.edit_obj) {
            case LISTTEMP_EDIT_OBJECT_VOL: {
                ListTempInfo.tempPoints[i].vol = max - (max - min) / (pointCount - 1) * i;
            }
            break;
            case LISTTEMP_EDIT_OBJECT_AMP: {
                ListTempInfo.tempPoints[i].amp = max - (max - min) / (pointCount - 1) * i;
            }
            break;
        }
        ListTempInfo.tempPoints[i].kT = interval;
    }
}


static void _generate_Wave_StairUpDown(void)
{
    uint16_t pointCount = ListTempInfo.totalCount;
    float interval = ListTempInfo.interval;         //时间间隔
    float min = ListTempInfo.param[ListTempInfo.edit_obj].minValue;      //最小值
    float max = ListTempInfo.param[ListTempInfo.edit_obj].maxValue;      //最大值
    uint16_t divPoint = pointCount / 2;
    for(uint16_t i = 0; i < pointCount; ++i)
    {
        switch(ListTempInfo.edit_obj) {
            case LISTTEMP_EDIT_OBJECT_VOL: {
                if(i < divPoint) {
                    ListTempInfo.tempPoints[i].vol = min + (max - min) / (divPoint) * i;
                } else {
                    ListTempInfo.tempPoints[i].vol = max - (max - min) / (pointCount - divPoint - 1) * (i - divPoint);
                }
            }
            break;
            case LISTTEMP_EDIT_OBJECT_AMP: {
                if(i < divPoint) {
                    ListTempInfo.tempPoints[i].amp = min + (max - min) / (divPoint) * i;
                } else {
                    ListTempInfo.tempPoints[i].amp = max - (max - min) / (pointCount - divPoint - 1) * (i - divPoint);
                }
            }
            break;
        }
        ListTempInfo.tempPoints[i].kT = interval;
    }
}



static void _generate_Wave_expUp(void)
{
    uint16_t pointCount = ListTempInfo.totalCount;
    float interval = ListTempInfo.interval;         //时间间隔
    float min = ListTempInfo.param[ListTempInfo.edit_obj].minValue;      //最小值
    float max = ListTempInfo.param[ListTempInfo.edit_obj].maxValue;      //最大值
    int32_t exp_V = ListTempInfo.param[ListTempInfo.edit_obj].expValue;
    for(uint16_t i = 0; i < pointCount; ++i)
    {
        switch(ListTempInfo.edit_obj) {
            case LISTTEMP_EDIT_OBJECT_VOL: {
                ListTempInfo.tempPoints[i].vol = min + (max - min) * (1 - exp(-(float)exp_V * i / (pointCount - 1)));
            }
            break;
            case LISTTEMP_EDIT_OBJECT_AMP: {
                ListTempInfo.tempPoints[i].amp = min + (max - min) * (1 - exp(-(float)exp_V * i / (pointCount - 1)));
            }
            break;
        }
        ListTempInfo.tempPoints[i].kT = interval;
    }
}

static void _generate_Wave_expDown(void)
{
    uint16_t pointCount = ListTempInfo.totalCount;
    float interval = ListTempInfo.interval;         //时间间隔
    float min = ListTempInfo.param[ListTempInfo.edit_obj].minValue;      //最小值
    float max = ListTempInfo.param[ListTempInfo.edit_obj].maxValue;      //最大值
    int32_t exp_V = ListTempInfo.param[ListTempInfo.edit_obj].expValue;
    for(uint16_t i = 0; i < pointCount; ++i)
    {
        switch(ListTempInfo.edit_obj) {
            case LISTTEMP_EDIT_OBJECT_VOL: {
                ListTempInfo.tempPoints[i].vol = min + (max - min) * (exp(-(float)exp_V * i / (pointCount - 1)));
            }
            break;
            case LISTTEMP_EDIT_OBJECT_AMP: {
                ListTempInfo.tempPoints[i].amp = min + (max - min) * (exp(-(float)exp_V * i / (pointCount - 1)));
            }
            break;
        }
        ListTempInfo.tempPoints[i].kT = interval;
    }
}


static void _generate_Wave(lv_obj_t *chart)
{
    if(chart == NULL) {
        return;
    }
    for(uint16_t i = 0; i < (sizeof(ListTempInfo.tempPoints) / sizeof(ListTempInfo.tempPoints[0])); ++i)
    {
        switch(ListTempInfo.edit_obj) {
            case LISTTEMP_EDIT_OBJECT_VOL: {
                ListTempInfo.tempPoints[i].vol = 0;
            }
            break;
            case LISTTEMP_EDIT_OBJECT_AMP: {
                ListTempInfo.tempPoints[i].amp = 0;
            }
            break;
        }
        float interval = ListTempInfo.interval;         //时间间隔
        ListTempInfo.tempPoints[i].kT = interval;
    }
    uint8_t type = ListTempInfo.param[ListTempInfo.edit_obj].temp_type;
    switch(type)
    {
        case TEMP_TYPE_Sin: {         //正弦波       反相/角度
            _generate_Wave_Sin();
        }
        break;
        case TEMP_TYPE_Pulse: {       //脉冲波       占空比
            _generate_Wave_Pluse();
        }
        break;
        case TEMP_TYPE_Ramp: {        //斜波         对称性
            _generate_Wave_Ramp();
        }
        break;
        case TEMP_TYPE_Stair_Up: {    //阶梯上升
            _generate_Wave_StairUp();
        }
        break;
        case TEMP_TYPE_Stair_Down: {  //阶梯下降
            _generate_Wave_StairDown();
        }
        break;
        case TEMP_TYPE_Stair_UpDown: { //阶梯上下
            _generate_Wave_StairUpDown();
        }
        break;
        case TEMP_TYPE_expUp: {       //指数上升      指数
            _generate_Wave_expUp();
        }
        break;
        case TEMP_TYPE_expDown: {     //指数下降      指数
            _generate_Wave_expDown();
        }
        break;
        default: {
        } break;
    }
    //清空列表,设置点数
    extern lv_chart_series_t *ListTempPage_chart_1_0;
    extern lv_chart_series_t *ListTempPage_chart_1_1;
    lv_chart_series_t *target_series = NULL;
    switch(ListTempInfo.edit_obj) {
        case LISTTEMP_EDIT_OBJECT_VOL: {
            target_series = ListTempPage_chart_1_0;
            lv_chart_hide_series(chart, ListTempPage_chart_1_0, 0);
            lv_chart_hide_series(chart, ListTempPage_chart_1_1, 1);
        }
        break;
        case LISTTEMP_EDIT_OBJECT_AMP: {
            target_series = ListTempPage_chart_1_1;
            lv_chart_hide_series(chart, ListTempPage_chart_1_0, 1);
            lv_chart_hide_series(chart, ListTempPage_chart_1_1, 0);
        }
        break;
    }
    if(target_series == NULL) {
        return;
    }
    lv_chart_clear_series(chart, target_series);
    if(ListTempInfo.param[ListTempInfo.edit_obj].temp_type == TEMP_TYPE_Pulse) {
        float duty = ListTempInfo.param[ListTempInfo.edit_obj].pluseWidth * 100 / (ListTempInfo.param[ListTempInfo.edit_obj].plusePeriod + 0.0001f);
        float min = ListTempInfo.param[ListTempInfo.edit_obj].minValue;      //最小值
        float max = ListTempInfo.param[ListTempInfo.edit_obj].maxValue;      //最大值
        uint8_t flag_inverte = !ListTempInfo.param[ListTempInfo.edit_obj].invert;
        _Chart_SetPointCount(chart, 100);
        for(uint16_t i = 0; i < 100; ++i) {
            if(i < duty) {
                lv_chart_set_next(chart, target_series, 10 * ((flag_inverte) ? max : min));
            } else {
                lv_chart_set_next(chart, target_series, 10 * ((flag_inverte) ? min : max));
            }
        }
    } else {
        _Chart_SetPointCount(chart, ListTempInfo.totalCount);
        for(uint16_t i = 0; i < ListTempInfo.totalCount; ++i) {
            switch(ListTempInfo.edit_obj) {
                case LISTTEMP_EDIT_OBJECT_VOL: {
                    lv_chart_set_next(chart, target_series, ListTempInfo.tempPoints[i].vol * 10);
                }
                break;
                case LISTTEMP_EDIT_OBJECT_AMP: {
                    lv_chart_set_next(chart, target_series, ListTempInfo.tempPoints[i].amp * 10);
                }
                break;
            }
        }
    }
}






/*
 * @brief       static void _Chart_Update(lv_obj_t* chart,uint8_t editFlag)
 * @details     更新波形图
 */
static void _Chart_Update(lv_obj_t *chart)
{
    if(chart == NULL) {
        return;
    }
    //设置刻度尺
    int32_t range = 0;
    //设置
    switch(ListTempInfo.edit_obj) {
        case LISTTEMP_EDIT_OBJECT_VOL: {
            const float VK = 20;
            range = ((uint16_t)(VOL_MAX / VK) + 1) * VK;
        }
        break;
        case LISTTEMP_EDIT_OBJECT_AMP: {
            const float IK = 5;
            range = ((uint16_t)(AMP_MAX / IK) + 1) * IK;
            break;
        }
    }
    _Chart_SetEdit(chart, range);
    _generate_Wave(chart);
}

/*
 * @brief       static void _Chart_SetEdit(uint8_t edit)
 * @details     设置波形编辑对象(改刻度尺)
 */
static void _Chart_SetEdit(lv_obj_t *chart, float maxValue)
{
    if(chart == NULL) {
        return;
    }
    static char string[64] = {0};
    switch(ListTempInfo.edit_obj) {
        case LISTTEMP_EDIT_OBJECT_VOL: {
            sprintf(string, "%3.1f\n\n%3.1f\n\n0V", maxValue, maxValue / 2);
        }
        break;
        case LISTTEMP_EDIT_OBJECT_AMP: {
            sprintf(string, "%3.1f\n\n%3.1f\n\n0A", maxValue, maxValue / 2);
        }
        break;
    }
    maxValue *= 10;
    lv_chart_set_range(chart, 0, maxValue);
    lv_chart_set_secondary_y_tick_texts(chart, string, 0, LV_CHART_AXIS_DRAW_LAST_TICK);
    lv_chart_set_secondary_y_tick_length(chart, 0, 0);
}

/*
 * @brief       static void _Chart_SetPointCount(uint16_t count)
 * @details     设置点数
 */
static void _Chart_SetPointCount(lv_obj_t *chart, uint16_t count)
{
    if(chart == NULL) {
        return;
    }
    lv_chart_set_point_count(chart, count);
    static char string[32] = {0};
    sprintf(string, "0\n%d\n%d", count / 2, count);
    lv_chart_set_x_tick_texts(chart, string, 0, LV_CHART_AXIS_DRAW_LAST_TICK);
    lv_chart_set_x_tick_length(chart, 0, 0);
}






/*
 * @brief       static void ListTempPage_Refresh(void)
 * @details     模板页面刷新
 */
static void ListTempPage_Refresh(void)
{
    _Set_TempType(ListTempInfo.param[ListTempInfo.edit_obj].temp_type);
    //重新加载图表
    lv_obj_t *chart = ui.ListTempPage_chart_1;
    _Chart_Update(chart);
}



static void button_refresh(void);


void ListTemp_Edit_Type_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return ;
    }
    switch(event)
    {
        case LV_EVENT_CLICKED: {
            uint8_t type = ListTempInfo.param[ListTempInfo.edit_obj].temp_type;
            if(type < TEMP_TYPE_MAX) {
                type += 1;
            } else {
                type = TEMP_TYPE_MIN;
            }
            UI_IF_ListTemp_Set_Type(type);
        }
        case LV_EVENT_REFRESH: {
            lv_event_send_refresh(ui.ListTempPage_btn_cout_label);
            extern void button_refresh(void);
            button_refresh();
        }
        break;
    }
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_list_temp_Type));
    ListTempPage_Refresh();
}

void ListTemp_Edit_Object_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return ;
    }
    switch(event)
    {
        case LV_EVENT_CLICKED: {
            if(ListTempInfo.edit_obj < LISTTEMP_EDIT_OBJECT_MAX) {
                ListTempInfo.edit_obj += 1;
            } else {
                ListTempInfo.edit_obj = LISTTEMP_EDIT_OBJECT_MIN;
            }
        }
        case LV_EVENT_REFRESH: {
            //更新变量显示
            lv_color_t color = {0};
            switch(ListTempInfo.edit_obj)
            {
                case LISTTEMP_EDIT_OBJECT_VOL: {
                    color = lv_color_make(0xff, 0x96, 0x00);
                    //                    color = lv_color_make(0x00, 0xff, 0xff);
                    BtnLabel_Set_Edit_Value(obj, MultStr_GetS(&mStr_list_temp_Voltage));
                }
                break;
                case LISTTEMP_EDIT_OBJECT_AMP: {
                    color = lv_color_make(0x00, 0xff, 0xff);
                    BtnLabel_Set_Edit_Value(obj, MultStr_GetS(&mStr_list_temp_Current));
                }
                break;
            }
            lv_obj_set_style_local_text_color(ui.ListTempPage_chart_1, LV_CHART_PART_BG, LV_STATE_DEFAULT, color);
            //            lv_obj_set_style_local_line_color(ui.ListTempPage_chart_1, LV_CHART_PART_SERIES_BG, LV_STATE_DEFAULT, color);
            //            lv_obj_set_style_local_line_opa(ui.ListTempPage_chart_1, LV_CHART_PART_SERIES_BG, LV_STATE_DEFAULT, 0xbb);
            lv_obj_set_style_local_border_color(ui.ListTempPage_imgbtn_sin, LV_IMGBTN_PART_MAIN, LV_STATE_DEFAULT, color);
            lv_obj_set_style_local_border_color(ui.ListTempPage_imgbtn_pluse, LV_IMGBTN_PART_MAIN, LV_STATE_DEFAULT, color);
            lv_obj_set_style_local_border_color(ui.ListTempPage_imgbtn_Ramp, LV_IMGBTN_PART_MAIN, LV_STATE_DEFAULT, color);
            lv_obj_set_style_local_border_color(ui.ListTempPage_imgbtn_StairUp, LV_IMGBTN_PART_MAIN, LV_STATE_DEFAULT, color);
            lv_obj_set_style_local_border_color(ui.ListTempPage_imgbtn_StairDn, LV_IMGBTN_PART_MAIN, LV_STATE_DEFAULT, color);
            lv_obj_set_style_local_border_color(ui.ListTempPage_imgbtn_StairUD, LV_IMGBTN_PART_MAIN, LV_STATE_DEFAULT, color);
            lv_obj_set_style_local_border_color(ui.ListTempPage_imgbtn_expUp, LV_IMGBTN_PART_MAIN, LV_STATE_DEFAULT, color);
            lv_obj_set_style_local_border_color(ui.ListTempPage_imgbtn_expDn, LV_IMGBTN_PART_MAIN, LV_STATE_DEFAULT, color);
            lv_obj_set_style_local_value_color(ui.ListTempPage_btn_0, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, color);
            lv_obj_set_style_local_value_color(ui.ListTempPage_btn_1, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, color);
            lv_obj_set_style_local_value_color(ui.ListTempPage_btn_2, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, color);
            lv_obj_set_style_local_value_color(ui.ListTempPage_btn_obj, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, color);
            lv_obj_set_style_local_value_color(ui.ListTempPage_btn_type, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, color);
            lv_obj_set_style_local_value_color(ui.ListTempPage_btn_start, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, color);
            lv_obj_set_style_local_value_color(ui.ListTempPage_btn_cout, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, color);
            lv_obj_set_style_local_value_color(ui.ListTempPage_btn_maxValue, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, color);
            lv_obj_set_style_local_value_color(ui.ListTempPage_btn_minValue, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, color);
            BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_list_temp_Object));
            ListTempPage_Refresh();
            button_refresh();
        }
        break;
    }
}


//编辑起始点
static void Edit_Start_RefreshUI(lv_obj_t *obj, uint8_t *editIndex)
{
    lv_obj_set_state(obj, (editIndex == NULL) ? LV_STATE_DEFAULT : LV_STATE_FOCUSED);
    static char stringSet[64] = {0};
    sprintf(stringSet, POINT_DISP_FORM, ListTempInfo.startpoint);
    if(editIndex != NULL) {
        label_setSelNum(obj, *editIndex, stringSet);
    } else {
    }
    lv_label_set_text_static(obj, stringSet);
}
void Edit_Start_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return ;
    }
    static uint8_t editIdx = 0;
    int32_t temp = ListTempInfo.startpoint;
    NumberInput_Process(7, UI_IF_ListTemp_Set_Start);
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                //编码器右转,增大电压
                case LV_KEY_UP: {
                    temp += point_step[editIdx];
                    UI_IF_ListTemp_Set_Start(temp);
                }
                break;
                //编码器左转,降低电压
                case LV_KEY_DOWN: {
                    temp -= point_step[editIdx];
                    UI_IF_ListTemp_Set_Start(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(editIdx > 0)
                    {
                        editIdx--;
                    }
                    else
                    {
                        editIdx = sizeof(point_step) / sizeof(point_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(editIdx < (sizeof(point_step) / sizeof(point_step[0]) - 1))
                    {
                        editIdx++;
                    }
                    else
                    {
                        editIdx = 0;
                    }
                }
                break;
                default: {
                } break;
            }
            if(key != LV_KEY_ESC) {
                //更新显示选定 & 步进位
                Edit_Start_RefreshUI(obj, &editIdx);
            } else {
                Edit_Start_RefreshUI(obj, NULL);
            }
        }
        break;
        case LV_EVENT_FOCUSED:
        case LV_EVENT_REFRESH: {
            Edit_Start_RefreshUI(obj, NULL);
        }
        break;
        case LV_EVENT_CLICKED: {
            editIdx = 0;
            Edit_Start_RefreshUI(obj, &editIdx);
        }
        break;
    }
    ListTempPage_Refresh();
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_list_temp_Start));
}







//编辑总点数
static void Edit_Count_RefreshUI(lv_obj_t *obj, uint8_t *editIndex)
{
    lv_obj_set_state(obj, (editIndex == NULL) ? LV_STATE_DEFAULT : LV_STATE_FOCUSED);
    static char stringSet[64] = {0};
    sprintf(stringSet, POINT_DISP_FORM, ListTempInfo.totalCount);
    if(editIndex != NULL) {
        label_setSelNum(obj, *editIndex, stringSet);
    } else {
    }
    lv_label_set_text_static(obj, stringSet);
}
void Edit_Count_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return ;
    }
    static uint8_t editIdx = 0;
    int32_t temp = ListTempInfo.totalCount;
    NumberInput_Process(7, UI_IF_ListTemp_Set_Count);
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                //编码器右转,增大电压
                case LV_KEY_UP: {
                    temp += point_step[editIdx];
                    UI_IF_ListTemp_Set_Count(temp);
                }
                break;
                //编码器左转,降低电压
                case LV_KEY_DOWN: {
                    temp -= point_step[editIdx];
                    UI_IF_ListTemp_Set_Count(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(editIdx > 0)
                    {
                        editIdx--;
                    }
                    else
                    {
                        editIdx = sizeof(point_step) / sizeof(point_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(editIdx < (sizeof(point_step) / sizeof(point_step[0]) - 1))
                    {
                        editIdx++;
                    }
                    else
                    {
                        editIdx = 0;
                    }
                }
                break;
                default: {
                } break;
            }
            if(key != LV_KEY_ESC) {
                //更新显示选定 & 步进位
                Edit_Count_RefreshUI(obj, &editIdx);
            } else {
                Edit_Count_RefreshUI(obj, NULL);
            }
        }
        break;
        case LV_EVENT_FOCUSED:
        case LV_EVENT_REFRESH: {
            Edit_Count_RefreshUI(obj, NULL);
        }
        break;
        case LV_EVENT_CLICKED: {
            editIdx = 0;
            Edit_Count_RefreshUI(obj, &editIdx);
        }
        break;
    }
    ListTempPage_Refresh();
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_list_temp_Groups));
}








//编辑最大值
static void Edit_Max_RefreshUI(lv_obj_t *obj, uint8_t *editIndex)
{
    lv_obj_set_state(obj, (editIndex == NULL) ? LV_STATE_DEFAULT : LV_STATE_FOCUSED);
    static char stringSet[64] = {0};
    switch(ListTempInfo.edit_obj) {
        case LISTTEMP_EDIT_OBJECT_VOL:
            sprintf(stringSet, VOL_SET_FORM"V", ListTempInfo.param[LISTTEMP_EDIT_OBJECT_VOL].maxValue);
            break;
        case LISTTEMP_EDIT_OBJECT_AMP:
            sprintf(stringSet, AMP_SET_FORM"A", ListTempInfo.param[LISTTEMP_EDIT_OBJECT_AMP].maxValue);
            break;
    }
    if(editIndex != NULL) {
        label_setSelNum(obj, *editIndex, stringSet);
    } else {
    }
    lv_label_set_text_static(obj, stringSet);
}
void Edit_Max_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return ;
    }
    static uint8_t editIdx = 0;
    NumberInput_Process(7, UI_IF_ListTemp_Set_MaxValue);
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            float temp = 0;
            switch(key)
            {
                //编码器右转,增大电压
                case LV_KEY_UP: {
                    switch(ListTempInfo.edit_obj) {
                        case LISTTEMP_EDIT_OBJECT_VOL: {
                            temp = ListTempInfo.param[LISTTEMP_EDIT_OBJECT_VOL].maxValue;
                            temp += V_step[editIdx];
                            UI_IF_ListTemp_Set_MaxValue(temp);
                        }
                        break;
                        case LISTTEMP_EDIT_OBJECT_AMP: {
                            temp = ListTempInfo.param[LISTTEMP_EDIT_OBJECT_AMP].maxValue;
                            temp += A_step[editIdx];
                            UI_IF_ListTemp_Set_MaxValue(temp);
                        }
                        break;
                    }
                }
                break;
                //编码器左转,降低电压
                case LV_KEY_DOWN: {
                    switch(ListTempInfo.edit_obj) {
                        case LISTTEMP_EDIT_OBJECT_VOL: {
                            temp = ListTempInfo.param[LISTTEMP_EDIT_OBJECT_VOL].maxValue;
                            temp -= V_step[editIdx];
                            UI_IF_ListTemp_Set_MaxValue(temp);
                        }
                        break;
                        case LISTTEMP_EDIT_OBJECT_AMP: {
                            temp = ListTempInfo.param[LISTTEMP_EDIT_OBJECT_AMP].maxValue;
                            temp -= A_step[editIdx];
                            UI_IF_ListTemp_Set_MaxValue(temp);
                        }
                        break;
                    }
                }
                break;
                case LV_KEY_RIGHT: {
                    if(editIdx > 0)
                    {
                        editIdx--;
                    }
                    else
                    {
                        editIdx = sizeof(point_step) / sizeof(point_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(editIdx < (sizeof(point_step) / sizeof(point_step[0]) - 1))
                    {
                        editIdx++;
                    }
                    else
                    {
                        editIdx = 0;
                    }
                }
                break;
                default: {
                } break;
            }
            if(key != LV_KEY_ESC) {
                //更新显示选定 & 步进位
                Edit_Max_RefreshUI(obj, &editIdx);
            } else {
                Edit_Max_RefreshUI(obj, NULL);
            }
        }
        break;
        case LV_EVENT_FOCUSED:
        case LV_EVENT_REFRESH: {
            Edit_Max_RefreshUI(obj, NULL);
        }
        break;
        case LV_EVENT_CLICKED: {
            editIdx = 0;
            Edit_Max_RefreshUI(obj, &editIdx);
        }
        break;
    }
    ListTempPage_Refresh();
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_list_temp_MaxValue));
}






//编辑最小值
static void Edit_Min_RefreshUI(lv_obj_t *obj, uint8_t *editIndex)
{
    lv_obj_set_state(obj, (editIndex == NULL) ? LV_STATE_DEFAULT : LV_STATE_FOCUSED);
    static char stringSet[64] = {0};
    switch(ListTempInfo.edit_obj) {
        case LISTTEMP_EDIT_OBJECT_VOL:
            sprintf(stringSet, VOL_SET_FORM"V", ListTempInfo.param[LISTTEMP_EDIT_OBJECT_VOL].minValue);
            break;
        case LISTTEMP_EDIT_OBJECT_AMP:
            sprintf(stringSet, AMP_SET_FORM"A", ListTempInfo.param[LISTTEMP_EDIT_OBJECT_AMP].minValue);
            break;
    }
    if(editIndex != NULL) {
        label_setSelNum(obj, *editIndex, stringSet);
    } else {
    }
    lv_label_set_text_static(obj, stringSet);
}
void Edit_Min_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return ;
    }
    static uint8_t editIdx = 0;
    NumberInput_Process(7, UI_IF_ListTemp_Set_MinValue);
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            float temp = 0;
            switch(key)
            {
                //编码器右转,增大电压
                case LV_KEY_UP: {
                    switch(ListTempInfo.edit_obj) {
                        case LISTTEMP_EDIT_OBJECT_VOL: {
                            temp = ListTempInfo.param[LISTTEMP_EDIT_OBJECT_VOL].minValue;
                            temp += V_step[editIdx];
                            UI_IF_ListTemp_Set_MinValue(temp);
                        }
                        break;
                        case LISTTEMP_EDIT_OBJECT_AMP: {
                            temp = ListTempInfo.param[LISTTEMP_EDIT_OBJECT_AMP].minValue;
                            temp += A_step[editIdx];
                            UI_IF_ListTemp_Set_MinValue(temp);
                        }
                        break;
                    }
                }
                break;
                //编码器左转,降低电压
                case LV_KEY_DOWN: {
                    switch(ListTempInfo.edit_obj) {
                        case LISTTEMP_EDIT_OBJECT_VOL: {
                            temp = ListTempInfo.param[LISTTEMP_EDIT_OBJECT_VOL].minValue;
                            temp -= V_step[editIdx];
                            UI_IF_ListTemp_Set_MinValue(temp);
                        }
                        break;
                        case LISTTEMP_EDIT_OBJECT_AMP: {
                            temp = ListTempInfo.param[LISTTEMP_EDIT_OBJECT_AMP].minValue;
                            temp -= A_step[editIdx];
                            UI_IF_ListTemp_Set_MinValue(temp);
                        }
                        break;
                    }
                }
                break;
                case LV_KEY_RIGHT: {
                    if(editIdx > 0)
                    {
                        editIdx--;
                    }
                    else
                    {
                        editIdx = sizeof(point_step) / sizeof(point_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(editIdx < (sizeof(point_step) / sizeof(point_step[0]) - 1))
                    {
                        editIdx++;
                    }
                    else
                    {
                        editIdx = 0;
                    }
                }
                break;
                default: {
                } break;
            }
            if(key != LV_KEY_ESC) {
                //更新显示选定 & 步进位
                Edit_Min_RefreshUI(obj, &editIdx);
            } else {
                Edit_Min_RefreshUI(obj, NULL);
            }
        }
        break;
        case LV_EVENT_FOCUSED:
        case LV_EVENT_REFRESH: {
            Edit_Min_RefreshUI(obj, NULL);
        }
        break;
        case LV_EVENT_CLICKED: {
            editIdx = 0;
            Edit_Min_RefreshUI(obj, &editIdx);
        }
        break;
    }
    ListTempPage_Refresh();
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_list_temp_MinValue));
}






//编辑时间间隔
static void Edit_Interval_RefreshUI(lv_obj_t *obj, uint8_t *editIndex)
{
    lv_obj_set_state(obj, (editIndex == NULL) ? LV_STATE_DEFAULT : LV_STATE_FOCUSED);
    static char stringSet[64] = {0};
    sprintf(stringSet, KEEP_TIME_FORM"s", ListTempInfo.interval);
    if(editIndex != NULL) {
        label_setSelNum(obj, *editIndex, stringSet);
    } else {
    }
    lv_label_set_text_static(obj, stringSet);
}
void Edit_Interval_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return ;
    }
    static uint8_t editIdx = 0;
    NumberInput_Process(7, UI_IF_ListTemp_Set_Interval);
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                //编码器右转,增大电压
                case LV_KEY_UP: {
                    float temp = ListTempInfo.interval;
                    temp += kT_step[editIdx];
                    UI_IF_ListTemp_Set_Interval(temp);
                }
                break;
                //编码器左转,降低电压
                case LV_KEY_DOWN: {
                    float temp = ListTempInfo.interval;
                    temp -= kT_step[editIdx];
                    UI_IF_ListTemp_Set_Interval(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(editIdx > 0)
                    {
                        editIdx--;
                    }
                    else
                    {
                        editIdx = sizeof(kT_step) / sizeof(kT_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(editIdx < (sizeof(kT_step) / sizeof(kT_step[0]) - 1))
                    {
                        editIdx++;
                    }
                    else
                    {
                        editIdx = 0;
                    }
                }
                break;
                default: {
                } break;
            }
            if(key != LV_KEY_ESC) {
                //更新显示选定 & 步进位
                Edit_Interval_RefreshUI(obj, &editIdx);
            } else {
                Edit_Interval_RefreshUI(obj, NULL);
            }
        }
        break;
        case LV_EVENT_FOCUSED:
        case LV_EVENT_REFRESH: {
            Edit_Interval_RefreshUI(obj, NULL);
        }
        break;
        case LV_EVENT_CLICKED: {
            editIdx = 0;
            Edit_Interval_RefreshUI(obj, &editIdx);
        }
        break;
    }
    ListTempPage_Refresh();
    lv_obj_set_hidden(lv_obj_get_parent(obj), 0);
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_list_temp_Interval));
}




//波形反相
void Edit_Invert_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return ;
    }
    switch(event)
    {
        case LV_EVENT_CLICKED: {
            switch(ListTempInfo.edit_obj) {
                case LISTTEMP_EDIT_OBJECT_VOL: {
                    ListTempInfo.param[LISTTEMP_EDIT_OBJECT_VOL].invert = !ListTempInfo.param[LISTTEMP_EDIT_OBJECT_VOL].invert;
                }
                break;
                case LISTTEMP_EDIT_OBJECT_AMP: {
                    ListTempInfo.param[LISTTEMP_EDIT_OBJECT_AMP].invert = !ListTempInfo.param[LISTTEMP_EDIT_OBJECT_AMP].invert;
                }
                break;
            }
            GUI_SEND_KEY(LV_KEY_RETURN);
        }
        case LV_EVENT_FOCUSED:
        case LV_EVENT_REFRESH: {
            switch(ListTempInfo.edit_obj) {
                case LISTTEMP_EDIT_OBJECT_VOL: {
                    if(ListTempInfo.param[LISTTEMP_EDIT_OBJECT_VOL].invert) {
                        BtnLabel_Set_Edit_Value(obj, MultStr_GetS(&mStr_ON));
                    } else {
                        BtnLabel_Set_Edit_Value(obj, MultStr_GetS(&mStr_OFF));
                    }
                }
                break;
                case LISTTEMP_EDIT_OBJECT_AMP: {
                    if(ListTempInfo.param[LISTTEMP_EDIT_OBJECT_AMP].invert) {
                        BtnLabel_Set_Edit_Value(obj, MultStr_GetS(&mStr_ON));
                    } else {
                        BtnLabel_Set_Edit_Value(obj, MultStr_GetS(&mStr_OFF));
                    }
                }
                break;
            }
        }
        break;
    }
    ListTempPage_Refresh();
    lv_obj_set_hidden(lv_obj_get_parent(obj), 0);
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_list_temp_Invert));
}




//周期
static void Edit_Period_RefreshUI(lv_obj_t *obj, uint8_t *editIndex)
{
    lv_obj_set_state(obj, (editIndex == NULL) ? LV_STATE_DEFAULT : LV_STATE_FOCUSED);
    static char stringSet[64] = {0};
    sprintf(stringSet, KEEP_TIME_FORM"s", ListTempInfo.param[ListTempInfo.edit_obj].plusePeriod);
    if(editIndex != NULL) {
        label_setSelNum(obj, *editIndex, stringSet);
    } else {
    }
    lv_label_set_text_static(obj, stringSet);
}
void Edit_Period_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return ;
    }
    static uint8_t editIdx = 0;
    NumberInput_Process(7, UI_IF_ListTemp_Set_Period);
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                //编码器右转,增大电压
                case LV_KEY_UP: {
                    float temp = ListTempInfo.param[ListTempInfo.edit_obj].plusePeriod;
                    temp += kT_step[editIdx];
                    UI_IF_ListTemp_Set_Period(temp);
                }
                break;
                //编码器左转,降低电压
                case LV_KEY_DOWN: {
                    float temp = ListTempInfo.param[ListTempInfo.edit_obj].plusePeriod;
                    temp -= kT_step[editIdx];
                    UI_IF_ListTemp_Set_Period(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(editIdx > 0)
                    {
                        editIdx--;
                    }
                    else
                    {
                        editIdx = sizeof(kT_step) / sizeof(kT_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(editIdx < (sizeof(kT_step) / sizeof(kT_step[0]) - 1))
                    {
                        editIdx++;
                    }
                    else
                    {
                        editIdx = 0;
                    }
                }
                break;
                default: {
                } break;
            }
            if(key != LV_KEY_ESC) {
                //更新显示选定 & 步进位
                Edit_Period_RefreshUI(obj, &editIdx);
            } else {
                Edit_Period_RefreshUI(obj, NULL);
            }
        }
        break;
        case LV_EVENT_FOCUSED:
        case LV_EVENT_REFRESH: {
            Edit_Period_RefreshUI(obj, NULL);
        }
        break;
        case LV_EVENT_CLICKED: {
            editIdx = 0;
            Edit_Period_RefreshUI(obj, &editIdx);
        }
        break;
    }
    ListTempPage_Refresh();
    lv_obj_set_hidden(lv_obj_get_parent(obj), 0);
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_list_temp_Period));
}




//脉宽
static void Edit_Width_RefreshUI(lv_obj_t *obj, uint8_t *editIndex)
{
    lv_obj_set_state(obj, (editIndex == NULL) ? LV_STATE_DEFAULT : LV_STATE_FOCUSED);
    static char stringSet[64] = {0};
    sprintf(stringSet, KEEP_TIME_FORM"s", ListTempInfo.param[ListTempInfo.edit_obj].pluseWidth);
    if(editIndex != NULL) {
        label_setSelNum(obj, *editIndex, stringSet);
    } else {
    }
    lv_label_set_text_static(obj, stringSet);
}
void Edit_Width_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return ;
    }
    static uint8_t editIdx = 0;
    NumberInput_Process(7, UI_IF_ListTemp_Set_Width);
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                //编码器右转,增大电压
                case LV_KEY_UP: {
                    float temp = ListTempInfo.param[ListTempInfo.edit_obj].pluseWidth;
                    temp += kT_step[editIdx];
                    UI_IF_ListTemp_Set_Width(temp);
                }
                break;
                //编码器左转,降低电压
                case LV_KEY_DOWN: {
                    float temp = ListTempInfo.param[ListTempInfo.edit_obj].pluseWidth;
                    temp -= kT_step[editIdx];
                    UI_IF_ListTemp_Set_Width(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(editIdx > 0)
                    {
                        editIdx--;
                    }
                    else
                    {
                        editIdx = sizeof(kT_step) / sizeof(kT_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(editIdx < (sizeof(kT_step) / sizeof(kT_step[0]) - 1))
                    {
                        editIdx++;
                    }
                    else
                    {
                        editIdx = 0;
                    }
                }
                break;
                default: {
                } break;
            }
            if(key != LV_KEY_ESC) {
                //更新显示选定 & 步进位
                Edit_Width_RefreshUI(obj, &editIdx);
            } else {
                Edit_Width_RefreshUI(obj, NULL);
            }
        }
        break;
        case LV_EVENT_FOCUSED:
        case LV_EVENT_REFRESH: {
            Edit_Width_RefreshUI(obj, NULL);
        }
        break;
        case LV_EVENT_CLICKED: {
            editIdx = 0;
            Edit_Width_RefreshUI(obj, &editIdx);
        }
        break;
    }
    ListTempPage_Refresh();
    lv_obj_set_hidden(lv_obj_get_parent(obj), 0);
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_list_temp_Width));
}


//编辑对称性
static void Edit_Symmetry_RefreshUI(lv_obj_t *obj, uint8_t *editIndex)
{
    lv_obj_set_state(obj, (editIndex == NULL) ? LV_STATE_DEFAULT : LV_STATE_FOCUSED);
    static char stringSet[64] = {0};
    sprintf(stringSet, SYMMETRY_FORM, ListTempInfo.param[ListTempInfo.edit_obj].Symmetry);
    if(editIndex != NULL) {
        label_setSelNum(obj, *editIndex, stringSet);
    } else {
    }
    lv_label_set_text_static(obj, stringSet);
}
void Edit_Symmetry_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return ;
    }
    static uint8_t editIdx = 0;
    NumberInput_Process(7, UI_IF_ListTemp_Set_Symmetry);
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                //编码器右转,增大电压
                case LV_KEY_UP: {
                    float temp = ListTempInfo.param[ListTempInfo.edit_obj].Symmetry;
                    temp += symmetry_step[editIdx];
                    UI_IF_ListTemp_Set_Symmetry(temp);
                }
                break;
                //编码器左转,降低电压
                case LV_KEY_DOWN: {
                    float temp = ListTempInfo.param[ListTempInfo.edit_obj].Symmetry;
                    temp -= symmetry_step[editIdx];
                    UI_IF_ListTemp_Set_Symmetry(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(editIdx > 0)
                    {
                        editIdx--;
                    }
                    else
                    {
                        editIdx = sizeof(symmetry_step) / sizeof(symmetry_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(editIdx < (sizeof(symmetry_step) / sizeof(symmetry_step[0]) - 1))
                    {
                        editIdx++;
                    }
                    else
                    {
                        editIdx = 0;
                    }
                }
                break;
                default: {
                } break;
            }
            if(key != LV_KEY_ESC) {
                //更新显示选定 & 步进位
                Edit_Symmetry_RefreshUI(obj, &editIdx);
            } else {
                Edit_Symmetry_RefreshUI(obj, NULL);
            }
        }
        break;
        case LV_EVENT_FOCUSED:
        case LV_EVENT_REFRESH: {
            Edit_Symmetry_RefreshUI(obj, NULL);
        }
        break;
        case LV_EVENT_CLICKED: {
            Edit_Symmetry_RefreshUI(obj, &editIdx);
        }
        break;
    }
    ListTempPage_Refresh();
    lv_obj_set_hidden(lv_obj_get_parent(obj), 0);
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_list_temp_Symmetry));
}




//指数值
static void Edit_Exp_RefreshUI(lv_obj_t *obj, uint8_t *editIndex)
{
    lv_obj_set_state(obj, (editIndex == NULL) ? LV_STATE_DEFAULT : LV_STATE_FOCUSED);
    static char stringSet[64] = {0};
    sprintf(stringSet, EXP_VALUE_FORM, ListTempInfo.param[ListTempInfo.edit_obj].expValue);
    if(editIndex != NULL) {
        label_setSelNum(obj, *editIndex, stringSet);
    } else {
    }
    lv_label_set_text_static(obj, stringSet);
}
void Edit_Exp_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return ;
    }
    static uint8_t editIdx = 0;
    NumberInput_Process(7, UI_IF_ListTemp_Set_expValue);
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                //编码器右转,增大电压
                case LV_KEY_UP: {
                    float temp = ListTempInfo.param[ListTempInfo.edit_obj].expValue;
                    temp += exp_step[editIdx];
                    UI_IF_ListTemp_Set_expValue(temp);
                }
                break;
                //编码器左转,降低电压
                case LV_KEY_DOWN: {
                    float temp = ListTempInfo.param[ListTempInfo.edit_obj].expValue;
                    temp -= exp_step[editIdx];
                    UI_IF_ListTemp_Set_expValue(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(editIdx > 0)
                    {
                        editIdx--;
                    }
                    else
                    {
                        editIdx = sizeof(exp_step) / sizeof(exp_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(editIdx < (sizeof(exp_step) / sizeof(exp_step[0]) - 1))
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
                //更新显示选定 & 步进位
                Edit_Exp_RefreshUI(obj, &editIdx);
            } else {
                Edit_Exp_RefreshUI(obj, NULL);
            }
        }
        break;
        case LV_EVENT_FOCUSED:
        case LV_EVENT_REFRESH: {
            Edit_Exp_RefreshUI(obj, NULL);
        }
        break;
        case LV_EVENT_CLICKED: {
            Edit_Exp_RefreshUI(obj, &editIdx);
        }
        break;
    }
    ListTempPage_Refresh();
    lv_obj_set_hidden(lv_obj_get_parent(obj), 0);
    BtnLabel_Set_Edit_Tag(obj, MultStr_GetS(&mStr_list_temp_exp));
}


#include "ListOut.h"
void ListTempPage_Generate(void)
{
    uint16_t start = ListTempInfo.startpoint;
    uint16_t end = ListTempInfo.startpoint + ListTempInfo.totalCount;
    for(uint16_t i = start; i < end; ++i) {
        switch(ListTempInfo.edit_obj) {
            case LISTTEMP_EDIT_OBJECT_VOL: {
                listoutInfo.points[i].vol = ListTempInfo.tempPoints[i - start].vol;
            }
            break;
            case LISTTEMP_EDIT_OBJECT_AMP: {
                listoutInfo.points[i].amp = ListTempInfo.tempPoints[i - start].amp;
            }
            break;
        }
        listoutInfo.points[i].kT = ListTempInfo.tempPoints[i - start].kT;
        ListOut_Check(&listoutInfo.points[i]);
    }
    if(lv_obj_is_visible(ui.ListPage_cont_Table) != 0) {
        lv_event_send_refresh_recursive(ui.ListPage_cont_Table);
    }
}


void ListTempPage_Cont_handler(lv_obj_t *obj, lv_event_t event)
{
    switch(event)
    {
        case LV_EVENT_KEY: {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                //生成
                case 'C': {
                    UI_IF_ListTemp_Generate();
                }
                break;
                default:
                {} break;
            }
        }
        break;
        case LV_EVENT_FOCUSED: {
        } break;
        case LV_EVENT_REFRESH:
        case LV_EVENT_CLICKED: {
            ListTempPage_Refresh();
        }
        break;
    }
}




/*
 * @brief       void ListTempPage_Enter(void)
 * @details     进入List模板页面
 */
void ListTempPage_Enter(void)
{
    lv_obj_set_hidden(ui.ListTempPage_cont_1, 0);
    button_refresh();
    lv_event_send_refresh_recursive(ui.ListTempPage_cont_1);
}

/*
 * @brief       void ListTempPage_Exit(void)
 * @details     退出List模板页面
 */
void ListTempPage_Exit(void)
{
    lv_obj_set_hidden(ui.ListTempPage_cont_1, 1);
}

void ListTempPage_GroupCreate(void)
{
    {
        setup_scr_ListTempPage(&ui);
        lv_obj_set_parent(ui.ListTempPage_cont_1, ui.Back_cont_back);
    }
    //图表风格
    {
        lv_obj_t *chart = ui.ListTempPage_chart_1;
        lv_obj_set_style_local_size(chart, LV_CHART_PART_SERIES, LV_STATE_DEFAULT, 1);
        lv_obj_set_style_local_bg_opa(chart, LV_CHART_PART_BG, LV_STATE_DEFAULT, 255);
        lv_obj_set_style_local_bg_color(chart, LV_CHART_PART_BG, LV_STATE_DEFAULT, lv_color_make(0, 0, 0));
        lv_obj_set_style_local_bg_grad_color(chart, LV_CHART_PART_BG, LV_STATE_DEFAULT, lv_color_make(0, 0, 0));
        lv_obj_set_style_local_border_width(chart, LV_CHART_PART_BG, LV_STATE_DEFAULT, 0);
        lv_obj_set_style_local_pad_left(chart, LV_CHART_PART_BG, LV_STATE_DEFAULT, 0); //40
        lv_obj_set_style_local_pad_right(chart, LV_CHART_PART_BG, LV_STATE_DEFAULT, 40); //10
        lv_obj_set_style_local_pad_top(chart, LV_CHART_PART_BG, LV_STATE_DEFAULT, 5); //20
        lv_obj_set_style_local_pad_bottom(chart, LV_CHART_PART_BG, LV_STATE_DEFAULT, 5); //20
        lv_obj_set_style_local_text_font(chart, LV_CHART_PART_BG, LV_STATE_DEFAULT, &lv_font_montserrat_10);
        lv_obj_set_style_local_text_color(chart, LV_CHART_PART_BG, LV_STATE_DEFAULT, lv_color_make(0, 255, 255));
        lv_chart_set_div_line_count(chart, 7, 1);
    }
    ListTempPage_btnStyle_Init(ui.ListTempPage_btn_obj_label);
    ListTempPage_btnStyle_Init(ui.ListTempPage_btn_type_label);
    ListTempPage_btnStyle_Init(ui.ListTempPage_btn_start_label);
    ListTempPage_btnStyle_Init(ui.ListTempPage_btn_cout_label);
    ListTempPage_btnStyle_Init(ui.ListTempPage_btn_maxValue_label);
    ListTempPage_btnStyle_Init(ui.ListTempPage_btn_minValue_label);
    ListTempPage_btnStyle_Init(ui.ListTempPage_btn_0_label);
    ListTempPage_btnStyle_Init(ui.ListTempPage_btn_1_label);
    ListTempPage_btnStyle_Init(ui.ListTempPage_btn_2_label);
    ListTempPge_TypeImg_StyleInit(ui.ListTempPage_imgbtn_sin);
    ListTempPge_TypeImg_StyleInit(ui.ListTempPage_imgbtn_pluse);
    ListTempPge_TypeImg_StyleInit(ui.ListTempPage_imgbtn_Ramp);
    ListTempPge_TypeImg_StyleInit(ui.ListTempPage_imgbtn_StairUp);
    ListTempPge_TypeImg_StyleInit(ui.ListTempPage_imgbtn_StairDn);
    ListTempPge_TypeImg_StyleInit(ui.ListTempPage_imgbtn_StairUD);
    ListTempPge_TypeImg_StyleInit(ui.ListTempPage_imgbtn_expUp);
    ListTempPge_TypeImg_StyleInit(ui.ListTempPage_imgbtn_expDn);
    ListTempPge_TypeImg_StyleInit(ui.ListTempPage_imgbtn_sel);
    ListTempPage_Exit();
    //    ListTempPage_Enter();
}





#include "btnTree.h"
extern Tree_Def *tree_list_temp;
extern Tree_Def *tree_list_tempEdit;
static void button_refresh(void)
{
    //起始点
    static const struct BtnInfo_Def btn_list_temp_start = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.ListTempPage_btn_start_label,
        .evencb = Edit_Start_handler,
        .multStr = &mStr_list_temp_Start,
    };
    //总点数
    static const struct BtnInfo_Def btn_list_temp_count = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.ListTempPage_btn_cout_label,
        .evencb = Edit_Count_handler,
        .multStr = &mStr_list_temp_Groups,
    };
    //最大值
    static const struct BtnInfo_Def btn_list_temp_maxvalue = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.ListTempPage_btn_maxValue_label,
        .evencb = Edit_Max_handler,
        .multStr = &mStr_list_temp_MaxValue,
    };
    //最小值
    static const struct BtnInfo_Def btn_list_temp_minvalue = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.ListTempPage_btn_minValue_label,
        .evencb = Edit_Min_handler,
        .multStr = &mStr_list_temp_MinValue,
    };
    //时间间隔
    static const struct BtnInfo_Def btn_list_temp_interval = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.ListTempPage_btn_0_label,
        .evencb = Edit_Interval_handler,
        .multStr = &mStr_list_temp_Interval,
    };
    //反相
    static const struct BtnInfo_Def btn_list_temp_invert = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.ListTempPage_btn_1_label,
        .evencb = Edit_Invert_handler,
        .multStr = &mStr_list_temp_Invert,
    };
    //周期
    static const struct BtnInfo_Def btn_list_temp_period = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.ListTempPage_btn_0_label,
        .evencb = Edit_Period_handler,
        .multStr = &mStr_list_temp_Period,
    };
    //脉宽
    static const struct BtnInfo_Def btn_list_temp_width = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.ListTempPage_btn_2_label,
        .evencb = Edit_Width_handler,
        .multStr = &mStr_list_temp_Width,
    };
    //对称性
    static const struct BtnInfo_Def btn_list_temp_symmetry = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.ListTempPage_btn_2_label,
        .evencb = Edit_Symmetry_handler,
        .multStr = &mStr_list_temp_Symmetry,
    };
    //指数
    static const struct BtnInfo_Def btn_list_temp_exp = {
        .type = BTN_TYPE_SEL,
        .obj = &ui.ListTempPage_btn_1_label,
        .evencb = Edit_Exp_handler,
        .multStr = &mStr_list_temp_exp,
    };
    //    //角度范围
    //    static const struct BtnInfo_Def btn_list_temp_angle = {
    //        .type = BTN_TYPE_SEL,
    //        .obj = &ui.ListTempPage_btn_2_label,
    //        .evencb = Edit_Angle_handler,
    //        .multStr = &mStr_list_temp_AngleRange,
    //    };
    if(tree_list_tempEdit->child != NULL)
    {
        Tree_Delete(tree_list_tempEdit, tree_list_tempEdit->child);
    }
    Tree_AddNode(tree_list_tempEdit, &btn_list_temp_start);
    Tree_AddNode(tree_list_tempEdit, &btn_list_temp_count);
    Tree_AddNode(tree_list_tempEdit, &btn_list_temp_maxvalue);
    Tree_AddNode(tree_list_tempEdit, &btn_list_temp_minvalue);
    //隐藏标签
    lv_obj_set_hidden(lv_obj_get_parent(ui.ListTempPage_btn_0_label), 1);
    lv_obj_set_hidden(lv_obj_get_parent(ui.ListTempPage_btn_1_label), 1);
    lv_obj_set_hidden(lv_obj_get_parent(ui.ListTempPage_btn_2_label), 1);
    lv_obj_set_event_cb(ui.ListTempPage_btn_0_label, NULL);
    lv_obj_set_event_cb(ui.ListTempPage_btn_1_label, NULL);
    lv_obj_set_event_cb(ui.ListTempPage_btn_2_label, NULL);
    extern Tree_Def *Tree_UI_Set_EventCb(Tree_Def * tree);
    uint8_t type = ListTempInfo.param[ListTempInfo.edit_obj].temp_type;
    switch(type) {
        case TEMP_TYPE_Sin: {
            Tree_AddNode(tree_list_tempEdit, &btn_list_temp_interval);
            Tree_AddNode(tree_list_tempEdit, &btn_list_temp_invert);    //反相
            //            Tree_AddNode(tree_list_tempEdit,&btn_list_temp_angle);      //角度范围
        }
        break;
        case TEMP_TYPE_Pulse: {
            Tree_AddNode(tree_list_tempEdit, &btn_list_temp_invert);    //反相
            Tree_AddNode(tree_list_tempEdit, &btn_list_temp_period);
            Tree_AddNode(tree_list_tempEdit, &btn_list_temp_width);
        }
        break;
        case TEMP_TYPE_Ramp: {
            Tree_AddNode(tree_list_tempEdit, &btn_list_temp_interval);
            Tree_AddNode(tree_list_tempEdit, &btn_list_temp_invert);    //反相
            Tree_AddNode(tree_list_tempEdit, &btn_list_temp_symmetry);  //对称度
        }
        break;
        case TEMP_TYPE_Stair_Up:
        case TEMP_TYPE_Stair_Down:
        case TEMP_TYPE_Stair_UpDown: {
            Tree_AddNode(tree_list_tempEdit, &btn_list_temp_interval);
        }
        break;
        case TEMP_TYPE_expUp:
        case TEMP_TYPE_expDown: {
            Tree_AddNode(tree_list_tempEdit, &btn_list_temp_interval);
            Tree_AddNode(tree_list_tempEdit, &btn_list_temp_exp);       //指数
        }
        break;
    }
    Tree_UI_Set_EventCb(tree_list_tempEdit);
    lv_event_send_refresh(ui.ListTempPage_btn_maxValue_label);
    lv_event_send_refresh(ui.ListTempPage_btn_minValue_label);
    lv_event_send_refresh(ui.ListTempPage_btn_start_label);
    lv_event_send_refresh(ui.ListTempPage_btn_cout_label);
    lv_event_send_refresh(ui.ListTempPage_btn_0_label);
    lv_event_send_refresh(ui.ListTempPage_btn_1_label);
    lv_event_send_refresh(ui.ListTempPage_btn_2_label);
}
