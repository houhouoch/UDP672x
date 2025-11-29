#include "ListOut.h"
#include "ListPage.h"
#include "List_Interface.h"
#include "ListPage_Option.h"

#define STARTP_SET_VALUE        listoutInfo.startpoint
#define COUNT_SET_VALUE         listoutInfo.countpoint
#define CYCLES_SET_VALUE        listoutInfo.cycles
#define LASTSTATE_SET_VALUE     listoutInfo.lastState


static void startP_RefreshUI(uint8_t *editIndex)
{
    lv_obj_t *obj = ui.ListPage_btn_start_label;
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

void ListPage_Option_editStartP_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return;
    }
    static uint8_t edit_index = 0;
    NumberInput_Process(7, UI_IF_List_Set_Start);
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
                    UI_IF_List_Set_Start(temp);
                }
                break;
                //编码器左转,降低电压
                case LV_KEY_DOWN: {
                    int32_t temp = STARTP_SET_VALUE;
                    temp -= point_step[edit_index];
                    UI_IF_List_Set_Start(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(edit_index > 0)
                    {
                        edit_index--;
                    }
                    else
                    {
                        edit_index = sizeof(point_step) / sizeof(point_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_ENCODER:
                case LV_KEY_ENTER:
                case LV_KEY_LEFT: {
                    if(edit_index < (sizeof(point_step) / sizeof(point_step[0]) - 1))
                    {
                        edit_index++;
                    }
                    else
                    {
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
    lv_obj_t *obj = ui.ListPage_btn_count_label;
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

void ListPage_Option_editCount_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return;
    }
    static uint8_t edit_index = 0;
    NumberInput_Process(7, UI_IF_List_Set_Count);
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
                    UI_IF_List_Set_Count(temp);
                }
                break;
                //编码器左转,降低电压
                case LV_KEY_DOWN: {
                    int32_t temp = COUNT_SET_VALUE;
                    temp -= point_step[edit_index];
                    UI_IF_List_Set_Count(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(edit_index > 0)
                    {
                        edit_index--;
                    }
                    else
                    {
                        edit_index = sizeof(point_step) / sizeof(point_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_ENCODER:
                case LV_KEY_ENTER:
                case LV_KEY_LEFT: {
                    if(edit_index < (sizeof(point_step) / sizeof(point_step[0]) - 1))
                    {
                        edit_index++;
                    }
                    else
                    {
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
    lv_obj_t *obj = ui.ListPage_btn_cycle_label;
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


void ListPage_Option_editCycles_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return;
    }
    static uint8_t edit_index = 0;
    NumberInput_Process(7, UI_IF_List_Set_Cycle);
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
                    UI_IF_List_Set_Cycle(temp);
                }
                break;
                //编码器左转,降低电压
                case LV_KEY_DOWN: {
                    int32_t temp = CYCLES_SET_VALUE;
                    temp -= cycle_step[edit_index];
                    UI_IF_List_Set_Cycle(temp);
                }
                break;
                case LV_KEY_RIGHT: {
                    if(edit_index > 0)
                    {
                        edit_index--;
                    }
                    else
                    {
                        edit_index = sizeof(cycle_step) / sizeof(cycle_step[0]) - 1;
                    }
                }
                break;
                case LV_KEY_ENCODER:
                case LV_KEY_ENTER:
                case LV_KEY_LEFT: {
                    if(edit_index < (sizeof(cycle_step) / sizeof(cycle_step[0]) - 1))
                    {
                        edit_index++;
                    }
                    else
                    {
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

void ListPage_Option_LastState_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL) {
        return;
    }
    switch(event) {
        case LV_EVENT_CLICKED: {
            LASTSTATE_SET_VALUE += 1;
            if(LASTSTATE_SET_VALUE > LIST_LASTSTATE_MAX) {
                LASTSTATE_SET_VALUE = LIST_ENDSTATE_MIN;
            }
            GUI_SEND_KEY(LV_KEY_RETURN);
        }
        case LV_EVENT_FOCUSED:
        case LV_EVENT_REFRESH: {
            lv_label_set_text_static(obj, (LASTSTATE_SET_VALUE == LIST_ENDSTATE_OFF) ? "OFF" : "LAST");
        }
        break;
    }
}

