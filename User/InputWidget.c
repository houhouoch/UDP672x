#include "InputWidget.h"

#include "Button_Device.h"
#include "SettingData.h"

#include "Setting_Interface.h"

enum {
    INPUT_TYPE_NULL,
    INPUT_TYPE_DOUBLE,
    INPUT_TYPE_INT,
    INPUT_TYPE_FLOAT,
};
uint8_t input_type = INPUT_TYPE_NULL;

typedef struct {
    const MultStr_Def *maxTips;
    const MultStr_Def *minTips;
    const MultStr_Def *title;
    uint8_t type;
    uint8_t index;
    void (*enterCb)(void);  //�??
    struct {
        double *data;
        const double *stepArray;
        uint8_t arraySize;
        const char *dispfmt;
        double max;
        double min;
    } edit_double;
    struct {
        int *data;
        const int *stepArray;
        uint8_t arraySize;
        const char *dispfmt;
        int max;
        int min;
    } edit_int;
} InputInfo_Def;

InputInfo_Def InputInfo = {0};


void InputVal_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    event = event;
    switch(InputInfo.type)
    {
        case INPUT_TYPE_DOUBLE:
            InputVal_Double_handler(obj, event);
            break;
        case INPUT_TYPE_INT:
            InputVal_Int_handler(obj, event);
            break;
    }
}




static int password = 0;
static void Boot_Enter_BootMode(void)
{
    //校验密码�?��正确,正确进入校准模式
    if(password == CALIB_MODE_PASSWD) {
        UI_IF_System_Set_CalibMode(1);
    }
}

/*
 * @brief       void Boot_CalibMode_Check(void)
 * @details     校准模式按键进入检�?(PRESET)
 */
void Boot_CalibMode_Check(void)
{
    #ifdef HAOYI_VER
    if(matrixButton_CalibModeCheck(BUTTON_ENTER) != 0)
    #else
    if(matrixButton_CalibModeCheck(BUTTON_PRESET) != 0)
    #endif
    {
        InputVal_IntEdit(&mStr_CalibPasswd_Title, &password, "%06d",
                         calib_passwd_step, ARRAY_COUNT(calib_passwd_step),
                         999999, 0, NULL, NULL, Boot_Enter_BootMode);
    }
}




#if 1
/* ------------------------- Double编辑窗口 --------------------------------*/
//呼出Double编辑窗口
void InputVal_IntEdit(const MultStr_Def *title, int *data, const char *dispfmt,
                      const int *stepArray, uint8_t arraySize,
                      int max, int min,
                      const MultStr_Def *minTips, const MultStr_Def *maxTips, void (*enterCb)(void))
{
    InputInfo.enterCb = enterCb;
    InputInfo.type = INPUT_TYPE_INT;
    //
    InputInfo.title = title;
    InputInfo.edit_int.max = max;
    InputInfo.edit_int.min = min;
    InputInfo.minTips = minTips;
    InputInfo.maxTips = maxTips;
    InputInfo.edit_int.data = data;
    InputInfo.edit_int.stepArray = stepArray;
    InputInfo.edit_int.dispfmt = dispfmt;
    InputInfo.edit_int.arraySize = arraySize;
    InputInfo.index = arraySize - 1;
    if(InputInfo.title != NULL) {
        lv_label_set_text_static(ui.InputWidget_btn_ValTitle_label, MultStr_GetS(InputInfo.title));
    }
    lv_obj_set_hidden(ui.InputWidget_cont_inputVal, 0);
    InputVal_Int_handler(ui.InputWidget_cont_inputVal, LV_EVENT_FOCUSED);
}

//Double编辑窗口事件回调函数
static void IntEdit_RefreshUI(lv_obj_t *obj, uint8_t *editIndex)
{
    if(obj == NULL) {
        return ;
    }
    static char stringSet[64] = {0};
    sprintf(stringSet, InputInfo.edit_int.dispfmt, *InputInfo.edit_int.data);
    if(editIndex != NULL) {
        label_setSelNum(obj, *editIndex, stringSet);
    } else {
    }
    lv_label_set_text_static(obj, stringSet);
}
void InputVal_Int_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = ui.InputWidget_btn_ValInput_label;
    event = event;
    NumberInput_Process(8, *InputInfo.edit_int.data =);
    switch(event)
    {
        case LV_EVENT_KEY:
        {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                case LV_KEY_UP: {
                    *InputInfo.edit_int.data += InputInfo.edit_int.stepArray[InputInfo.index];
                    if(*InputInfo.edit_int.data > InputInfo.edit_int.max) {
                        *InputInfo.edit_int.data = InputInfo.edit_int.max;
                        IF_MsgBox_Tips_Mult(InputInfo.maxTips);
                    }
                }
                break;
                case LV_KEY_DOWN: {
                    *InputInfo.edit_int.data -= InputInfo.edit_int.stepArray[InputInfo.index];
                    if(*InputInfo.edit_int.data < InputInfo.edit_int.min) {
                        *InputInfo.edit_int.data = InputInfo.edit_int.min;
                        IF_MsgBox_Tips_Mult(InputInfo.minTips);
                    }
                }
                break;
                case LV_KEY_RIGHT: {
                    if(InputInfo.index > 0)
                    {
                        InputInfo.index--;
                    }
                    else {
                        InputInfo.index = InputInfo.edit_int.arraySize - 1;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(InputInfo.index < (InputInfo.edit_int.arraySize - 1))
                    {
                        InputInfo.index++;
                    }
                    else {
                        InputInfo.index = 0;
                    }
                }
                break;
                case(LV_KEY_ENCODER): {
                    if(InputInfo.enterCb != NULL) {
                        InputInfo.enterCb();
                        InputInfo.enterCb = NULL;
                    }
                }
                case LV_KEY_ESC: {
                    InputInfo.type = INPUT_TYPE_NULL;
                    memset(&InputInfo.edit_int, 0, sizeof(InputInfo.edit_int));
                    lv_obj_set_hidden(ui.InputWidget_cont_inputVal, 1);
                }
                return;
            }
        }
        break;
        //聚焦 / 刷新事件
        case LV_EVENT_FOCUSED:
        case LV_EVENT_CLICKED: {
        }
        case LV_EVENT_REFRESH: {
        }
        break;
    }
    IntEdit_RefreshUI(obj, &InputInfo.index);
}
#endif


#if 1
/* ------------------------- Double编辑窗口 --------------------------------*/
//呼出Double编辑窗口
void InputVal_DoubleEdit(const MultStr_Def *title, double *data, const char *dispfmt,
                         const double *stepArray, uint8_t arraySize,
                         double max, double min,
                         const MultStr_Def *minTips, const MultStr_Def *maxTips, void (*enterCb)(void))
{
    InputInfo.enterCb = enterCb;
    InputInfo.type = INPUT_TYPE_DOUBLE;
    //
    InputInfo.title = title;
    InputInfo.edit_double.max = max;
    InputInfo.edit_double.min = min;
    InputInfo.minTips = minTips;
    InputInfo.maxTips = maxTips;
    InputInfo.edit_double.data = data;
    InputInfo.edit_double.stepArray = stepArray;
    InputInfo.edit_double.dispfmt = dispfmt;
    InputInfo.edit_double.arraySize = arraySize;
    InputInfo.index = arraySize - 1;
    if(InputInfo.title != NULL) {
        lv_label_set_text_static(ui.InputWidget_btn_ValTitle_label, MultStr_GetS(InputInfo.title));
    }
    lv_obj_set_hidden(ui.InputWidget_cont_inputVal, 0);
    InputVal_Double_handler(ui.InputWidget_cont_inputVal, LV_EVENT_FOCUSED);
}

//Double编辑窗口事件回调函数
static void DoubleEdit_RefreshUI(lv_obj_t *obj, uint8_t *editIndex)
{
    if(obj == NULL) {
        return ;
    }
    static char stringSet[64] = {0};
    sprintf(stringSet, InputInfo.edit_double.dispfmt, *InputInfo.edit_double.data);
    if(editIndex != NULL) {
        label_setSelNum(obj, *editIndex, stringSet);
    } else {
    }
    lv_label_set_text_static(obj, stringSet);
}
void InputVal_Double_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = ui.InputWidget_btn_ValInput_label;
    event = event;
    NumberInput_Process(8, *InputInfo.edit_double.data =);
    switch(event)
    {
        case LV_EVENT_KEY:
        {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            switch(key)
            {
                case LV_KEY_UP: {
                    *InputInfo.edit_double.data += InputInfo.edit_double.stepArray[InputInfo.index];
                    if(*InputInfo.edit_double.data > InputInfo.edit_double.max) {
                        *InputInfo.edit_double.data = InputInfo.edit_double.max;
                        IF_MsgBox_Tips_Mult(InputInfo.maxTips);
                    }
                }
                break;
                case LV_KEY_DOWN: {
                    *InputInfo.edit_double.data -= InputInfo.edit_double.stepArray[InputInfo.index];
                    if(*InputInfo.edit_double.data < InputInfo.edit_double.min) {
                        *InputInfo.edit_double.data = InputInfo.edit_double.min;
                        IF_MsgBox_Tips_Mult(InputInfo.minTips);
                    }
                }
                break;
                case LV_KEY_RIGHT: {
                    if(InputInfo.index > 0)
                    {
                        InputInfo.index--;
                    }
                    else {
                        InputInfo.index = InputInfo.edit_double.arraySize - 1;
                    }
                }
                break;
                case LV_KEY_LEFT: {
                    if(InputInfo.index < (InputInfo.edit_double.arraySize - 1))
                    {
                        InputInfo.index++;
                    }
                    else {
                        InputInfo.index = 0;
                    }
                }
                break;
                case LV_KEY_ENCODER: {
                    if(InputInfo.enterCb != NULL) {
                        InputInfo.enterCb();
                        InputInfo.enterCb = NULL;
                    }
                }
                case LV_KEY_ESC: {
                    InputInfo.type = INPUT_TYPE_NULL;
                    memset(&InputInfo.edit_double, 0, sizeof(InputInfo.edit_double));
                    lv_obj_set_hidden(ui.InputWidget_cont_inputVal, 1);
                }
                return;
            }
        }
        break;
        //聚焦 / 刷新事件
        case LV_EVENT_FOCUSED:
        case LV_EVENT_CLICKED: {
        }
        case LV_EVENT_REFRESH: {
        }
        break;
    }
    DoubleEdit_RefreshUI(obj, &InputInfo.index);
}
#endif





static char *edit_string = NULL;
static uint8_t edit_string_index = 0;
static int edit_maxLen = 0;


#include "BtnTree.h"
#include "VirtualBtnm.h"
lv_obj_t *keyboard = NULL;

void InputVal_StringEdit_SetCall(const MultStr_Def *title, char *string, int maxLen)
{
    InputInfo.title = title;
    edit_string = string;
    edit_maxLen = maxLen;
    if(InputInfo.title != NULL) {
        lv_label_set_text_static(ui.InputWidget_btn_StrTitle_label, MultStr_GetS(InputInfo.title));
    }
    if(keyboard != 0) {
        lv_obj_set_hidden(keyboard, 0);
    }
    lv_obj_set_hidden(ui.InputWidget_cont_inputString, 0);
    InputVal_StringEdit_handler(ui.InputWidget_cont_inputString, LV_EVENT_FOCUSED);
}

static void StringEdit_RefreshUI(uint8_t *editIndex)
{
    lv_obj_t *obj = ui.InputWidget_btn_StrInput_label;
    static char stringSet[64] = {0};
    sprintf(stringSet, "%s", edit_string);
    if(editIndex != NULL) {
        label_setSelIdx(obj, stringSet, *editIndex);
    } else {
    }
    lv_label_set_text_static(obj, stringSet);
}



static const char *default_kb_map_lc[] = {
    "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", LV_SYMBOL_BACKSPACE, "\n",
    "a", "s", "d", "f", "g", "h", "j", "k", "l", "\n",
    "_", "z", "x", "c", "v", "b", "n", "m", ".", ""
};
static const char *default_kb_map_uc[] = {
    "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", LV_SYMBOL_BACKSPACE, "\n",
    "A", "S", "D", "F", "G", "H", "J", "K", "L", "\n",
    "_", "Z", "X", "C", "V", "B", "N", "M", ".", ""
};
static const char *default_kb_map_spec[] = {
    "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", LV_SYMBOL_BACKSPACE, "\n",
    "<", ">", "(", ")", "[", "]",  ""
};
/*
 * @brief       切换�?��
 */
static void KeyBoard_Switch(lv_obj_t *keyboard, const char **map)
{
    lv_btnmatrix_set_map(keyboard, map);
    lv_btnmatrix_set_focused_btn(keyboard, 0);
    lv_obj_invalidate(keyboard);
}

static void KeyBoard_Enter(lv_obj_t *keyboard, const char *txt)
{
    if(0 == strcmp(txt, LV_SYMBOL_BACKSPACE)) {     //回退一�?���?
        uint16_t strlength = strlen(edit_string);
        if(strlength > 0) {
            edit_string[strlength - 1] = '\0';
        }
    } else
        if(0 == strcmp(txt, LV_SYMBOL_CLOSE)) { //取消输入
            GUI_SEND_KEY(LV_KEY_ESC);
        } else
            if(0 == strcmp(txt, LV_SYMBOL_LEFT)) {
            } else
                if(0 == strcmp(txt, LV_SYMBOL_RIGHT)) {
                } else
                    if(0 == strcmp(txt, LV_SYMBOL_OK)) {
                        GUI_SEND_KEY(LV_KEY_ENCODER_LONGP);
                    } else {
                        if((strlen(edit_string) + 1) < edit_maxLen) {
                            strcat(edit_string, txt);
                        }
                    }
}


void InputVal_StringEdit_handler(lv_obj_t *obj, lv_event_t event)
{
    switch(event)
    {
        //按键事件
        case LV_EVENT_KEY:
        {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            int focusedId = lv_btnmatrix_get_focused_btn(keyboard);
            const char *txt = lv_btnmatrix_get_btn_text(keyboard, focusedId);
            switch(key)
            {
                case LV_KEY_UP:
                    lv_btnmatrix_set_focused_btn(keyboard, focusedId + 1);
                    break;
                case LV_KEY_DOWN:
                    if(focusedId > 0) {
                        lv_btnmatrix_set_focused_btn(keyboard, focusedId - 1);
                    }
                    break;
                case LV_KEY_ENCODER:
                    KeyBoard_Enter(keyboard, txt);
                    break;
                //�?��切换
                case LV_KEY_UPPER:
                    KeyBoard_Switch(keyboard, default_kb_map_uc);
                    break;
                case LV_KEY_LOWER:
                    KeyBoard_Switch(keyboard, default_kb_map_lc);
                    break;
                case LV_KEY_NUMBER:
                    KeyBoard_Switch(keyboard, default_kb_map_spec);
                    break;
                case LV_KEY_LEFT: {
                    uint16_t strlength = strlen(edit_string);
                    if(strlength > 0) {
                        edit_string[strlength - 1] = '\0';
                    }
                }
                break;
                default: {
                    //数字�?��输入
                    if(('0' <= key) && (key <= '9')) {
                        char ch[2] = {0};
                        ch[0] = key;
                        if((strlen(edit_string) + 1) < edit_maxLen) {
                            strcat(edit_string, ch);
                        }
                    }
                }
                break;
            }
            if((key == LV_KEY_ESC)
                    || (key == LV_KEY_SAVE_FLASH)
                    || (key == LV_KEY_SAVE_UDISK)
                    || (key == LV_KEY_ENTER))
            {
                StringEdit_RefreshUI(NULL);
                lv_obj_set_hidden(ui.InputWidget_cont_inputString, 1);
                lv_obj_set_hidden(keyboard, 1);
                if(key != LV_KEY_ESC) {
                    GUI_SEND_KEY(LV_KEY_RETURN);
                }
            }
        }
        break;
        //聚焦 / 刷新事件
        case LV_EVENT_FOCUSED:
        case LV_EVENT_CLICKED: {
        }
        case LV_EVENT_REFRESH: {
        }
        break;
    }
    edit_string_index = strlen(edit_string) - 1;
    StringEdit_RefreshUI(&edit_string_index);
}


void InputWidget_Create(void)
{
    //编辑窗口
    setup_scr_InputWidget(&ui);
    lv_obj_set_parent(ui.InputWidget_cont_inputVal, ui.Back_cont_back);
    lv_obj_set_parent(ui.InputWidget_cont_inputString, ui.Back_cont_back);
    lv_obj_set_hidden(ui.InputWidget_cont_inputVal, 1);
    lv_obj_set_hidden(ui.InputWidget_cont_inputString, 1);
    lv_obj_set_event_cb(ui.InputWidget_btn_ValInput_label, InputVal_handler);
    extern lv_font_t MultFont_16;
    //数据输入
    {
        lv_obj_t *obj = ui.InputWidget_btn_ValInput_label;
        lv_obj_set_style_local_text_letter_space(obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 2);
        lv_obj_set_style_local_text_font(obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_AlibabaPuHuiTi_Light_26);
        lv_obj_set_style_local_text_sel_color(obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(255, 255, 255));
        lv_obj_set_style_local_text_sel_bg_color(obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0, 0, 255));
        //标�?
        lv_obj_t *tipLabel = ui.InputWidget_btn_ValTitle_label;
        lv_obj_set_style_local_text_letter_space(tipLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 3);
        lv_obj_set_style_local_text_font(tipLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_16);
        //
        lv_label_set_align(tipLabel, LV_LABEL_ALIGN_LEFT);
        lv_obj_align(tipLabel, ui.InputWidget_btn_ValTitle, LV_ALIGN_IN_LEFT_MID, 0, 0);
    }
    //字�?串输�?
    {
        lv_obj_t *obj = ui.InputWidget_btn_StrInput_label;
        lv_obj_set_style_local_text_letter_space(obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 2);
        lv_obj_set_style_local_text_font(obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_AlibabaPuHuiTi_Light_26);
        lv_obj_set_style_local_text_sel_color(obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(255, 255, 255));
        lv_obj_set_style_local_text_sel_bg_color(obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0, 0, 255));
        //标�?
        lv_obj_t *tipLabel = ui.InputWidget_btn_StrTitle_label;
        lv_obj_set_style_local_text_letter_space(tipLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 3);
        lv_obj_set_style_local_text_font(tipLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_16);
        //
        lv_label_set_align(tipLabel, LV_LABEL_ALIGN_LEFT);
        lv_obj_align(tipLabel, ui.InputWidget_btn_StrTitle, LV_ALIGN_IN_LEFT_MID, 0, 0);
        //虚拟按键
        keyboard = lv_keyboard_create(ui.Back_cont_back, NULL);
        lv_obj_set_size(keyboard, 360, 80);
        lv_obj_set_pos(keyboard, 20, 150);
        lv_obj_set_top(keyboard, 1);
        lv_obj_set_hidden(keyboard, 1);
        lv_obj_align(keyboard, ui.InputWidget_cont_inputString, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
        lv_btnmatrix_set_map(keyboard, default_kb_map_uc);
        lv_theme_apply(keyboard, LV_THEME_KEYBOARD);
        lv_obj_set_style_local_border_color(keyboard, LV_BTNMATRIX_PART_BTN, LV_STATE_FOCUSED, lv_color_make(0x00, 0xff, 0xff));
        lv_obj_set_style_local_border_width(keyboard, LV_BTNMATRIX_PART_BTN, LV_STATE_FOCUSED, 2);
        lv_obj_set_style_local_bg_color(keyboard, LV_BTNMATRIX_PART_BTN, LV_STATE_DEFAULT, lv_color_make(0, 0, 0));
        lv_obj_set_style_local_bg_color(keyboard, LV_BTNMATRIX_PART_BTN, LV_STATE_FOCUSED, lv_color_make(0, 0, 0xff));
    }
}

