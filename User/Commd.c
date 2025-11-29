#include "Commd.h"



//无校准点默�?系数(千万不�?动数�?,动了会�?人骂死的�?)
#if defined(UDP6922B)
    double K_V = ((double)127.186);
    double K_I = ((double)11.0);
    double Offset_V = 0;
    double Offset_I = 0;
#elif defined(UDP6932B)
    double K_V = ((double)131);
    double K_I = ((double)32);
    double Offset_V = 0;
    double Offset_I = 0;
#elif defined(UDP6933B)
    double K_V = ((double)317);
    double K_I = ((double)10);
    double Offset_V = 1.65;
    double Offset_I = 0;
#elif defined(UDP6942B)
    double K_V = ((double)127.186); //130
    double K_I = ((double)33.2);    //34
    double Offset_V = 0;
    double Offset_I = 0;
#elif defined(UDP6952B)
    double K_V = ((double)147.5);
    double K_I = ((double)53);
    double Offset_V = 0.33;
    double Offset_I = 0;
#elif defined(UDP6953B)
    double K_V = ((double)317);
    double K_I = ((double)25);
    double Offset_V = 0;
    double Offset_I = 0;
#elif defined(UDP40_40)
    double K_V = ((double)80); //130
    double K_I = ((double)80);    //34
    double Offset_V = 0;
    double Offset_I = 0;
#elif defined(UDP40_80)
    double K_V = ((double)80); //130
    double K_I = ((double)40);    //34
    double Offset_V = 0;
    double Offset_I = 0;
#elif defined(UDP6943B)
    double K_V = ((double)521);
    double K_I = ((double)8);
    double Offset_V = 0;
    double Offset_I = 0;
#endif
//无校准点默�?系数(千万不�?动数�?,动了会�?人骂死的�?)



//主页面�?�?
lv_ui ui;

//步进�?
const int32_t BaudRate_step[6] = {9600, 14400, 19200, 38400, 57600, 115200};

const double V_Calib_step[8] = {0.00001, 0.0001, 0.001, 0.01, 0.1, 1.0, 10.0, 100.0};
const double A_Calib_step[8] = {0.00001, 0.0001, 0.001, 0.01, 0.1, 1.0, 10.0, 100.0};



const float V_step[5] = {0.001, 0.01, 0.1, 1.0, 10.0};
const float A_step[6] = {0.0001, 0.001, 0.01, 0.1, 1.0, 10.0};



const float W_step[5] = {0.01, 0.1, 1.0, 10.0, 100.0};
const float timeoff_step[6] = {0.1, 1.0, 10.0, 100.0, 1000.0, 10000.0};

const float VSR_step[5] = {0.01, 0.1, 1.0, 10.0, 100.0};
const float ISR_step[4] = {0.01, 0.1, 1.0, 10.0};

const float kT_step[6] = {0.1, 1.0, 10.0, 100.0, 1000.0, 10000.0};
const float dT_step[6] = {0.1, 1.0, 10.0, 100.0, 1000.0, 10000.0};

const int cycle_step[4] = {1, 10, 100, 1000};
const int point_step[4] = {1, 10, 100, 1000};
const int baudR_step[5] = {1, 10, 100, 1000, 10000};

const int symmetry_step[2] = {1, 10.0};
const float exp_step[2] = {1, 10};

const int calib_passwd_step[6] = {1, 10, 100, 1000, 10000, 100000};
const float V_calib_step[6] = {0.00001, 0.0001, 0.001, 0.01, 0.1, 1.0};
const float A_calib_step[6] = {0.00001, 0.0001, 0.001, 0.01, 0.1, 1.0};


#if 1
const float BatteryTester_V_step[5] = {0.001, 0.01, 0.1, 1.0, 10.0};
const float BatteryTester_A_step[5] = {0.001, 0.01, 0.1, 1.0, 10.0};
const float BatteryTester_W_step[5] = {0.01, 0.1, 1.0, 10.0, 100.0};
const float BatteryTester_kT_step[6] = {0.1, 1.0, 10.0, 100.0, 1000.0, 10000.0};
#endif


//数据设置
void BtnLabel_Set_Edit_Tag(lv_obj_t *obj, const char *tag)
{
    if(obj == NULL) {
        return ;
    }
    if(tag == NULL) {
        return ;
    }
    obj = lv_obj_get_parent(obj);
    lv_obj_set_style_local_value_str(obj, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, tag);
    lv_obj_set_style_local_value_str(obj, LV_BTN_PART_MAIN, LV_STATE_FOCUSED, tag);
}

void BtnLabel_Set_Edit_Value(lv_obj_t *obj, const char *text)
{
    if(obj == NULL) {
        return ;
    }
    if(text == NULL) {
        return ;
    }
    lv_label_set_text(obj, text);
}




/*
 * @brief       void label_setSelNum(lv_obj_t* label,uint16_t numpos,const char* text)
 * @details     Label选择特定数字(用于设置参数)
 */
void label_setSelNum(lv_obj_t *label, uint16_t numpos, const char *text)
{
    if(label == NULL) {
        return;
    }
    uint16_t strLen = strlen(text);
    uint16_t bitindex = 0;
    for(int16_t i = strLen - 1; i >= 0; --i)
    {
        if((('0' <= text[i]) && (text[i] <= '9')) || (text[i] == ' '))
        {
            if(bitindex == numpos)
            {
                lv_label_set_text_sel_start(label, i);
                lv_label_set_text_sel_end(label, i + 1);
                return ;
            }
            bitindex++;
        }
    }
}

/*
 * @brief       void label_setSelStr(lv_obj_t* label,const char* str,const char* text)
 * @details     Label选择特定字�?(用于设置参数)
 */
void label_setSelStr(lv_obj_t *label, const char *str, const char *text)
{
    if(label == NULL) {
        return;
    }
    uint16_t strLen = strlen(str);
    uint16_t textLen = strlen(text);
    uint16_t bitindex = 0;
    for(uint16_t i = 0; i < textLen; ++i)
    {
        if(0 == strncmp(str, &text[i], strLen))
        {
            lv_label_set_text_sel_start(label, i);
            lv_label_set_text_sel_end(label, i + strLen);
            return ;
        }
        bitindex++;
    }
}

/*
 * @brief       void label_setSelIdx(lv_obj_t* label,const char* str,int idx)
 * @details     Label选择特定索引
 */
void label_setSelIdx(lv_obj_t *label, const char *str, int idx)
{
    if(label == NULL) {
        return;
    }
    if(idx != LV_LABEL_TEXT_SEL_OFF) {
        lv_label_set_text_sel_start(label, idx);
        lv_label_set_text_sel_end(label, idx + 1);
    } else {
        lv_label_set_text_sel_start(label, LV_LABEL_TEXT_SEL_OFF);
        lv_label_set_text_sel_end(label, LV_LABEL_TEXT_SEL_OFF);
    }
}





/* -------------------- 通用�?���??�? ---------------------- */



#include "Button_Device.h"
//按键映射
typedef struct {
    uint8_t buttonNum;
    uint8_t key_short;
    uint8_t key_long;
    uint8_t key_hold;
} Button_KeyTable_Def;

static const Button_KeyTable_Def Btn_KeyTable[] = {
    {BUTTON_F1,     LV_KEY_F1,      LV_KEY_F1_LONGP,    LV_KEY_F1_HOLD,},
    {BUTTON_F2,     LV_KEY_F2,      LV_KEY_F2_LONGP,    LV_KEY_F2_HOLD,},
    {BUTTON_F3,     LV_KEY_F3,      LV_KEY_F3_LONGP,    LV_KEY_F3_HOLD,},
    {BUTTON_F4,     LV_KEY_F4,      LV_KEY_F4_LONGP,    LV_KEY_F4_HOLD,},
    {BUTTON_F5,     LV_KEY_F5,      LV_KEY_F5_LONGP,    LV_KEY_F5_HOLD,},
    {BUTTON_F6,     LV_KEY_F6,      LV_KEY_F6_LONGP,    LV_KEY_F6_HOLD,},

    {BUTTON_LEFT,   LV_KEY_LEFT,    LV_KEY_LEFT,        LV_KEY_DEFAULT},
    {BUTTON_RIGHT,  LV_KEY_RIGHT,   LV_KEY_RIGHT,       LV_KEY_DEFAULT},

    
    {BUTTON_ESC,        LV_KEY_ESC,     LV_KEY_ESC_LONGP,       LV_KEY_DEFAULT},
    {BUTTON_ENCODER,    LV_KEY_ENCODER, LV_KEY_ENCODER_LONGP,   LV_KEY_DEFAULT},
    #ifdef HAOYI_VER
    {BUTTON_ENTER,      LV_KEY_ENCODER, LV_KEY_ENTER_LONGP,   LV_KEY_DEFAULT},
    #else
    #endif

    {BUTTON_LOCK,       LV_KEY_LOCK,        LV_KEY_LOCK_LONGP,      LV_KEY_DEFAULT},
    {BUTTON_MENU,       LV_KEY_MENU,        LV_KEY_MENU_LONGP,      LV_KEY_DEFAULT},
    {BUTTON_LIST,       LV_KEY_LIST,        LV_KEY_LIST,            LV_KEY_DEFAULT},

    #ifdef HAOYI_VER
    {BUTTON_WAVE,       LV_KEY_WAVE,        LV_KEY_WAVE,            LV_KEY_DEFAULT},
    #else
    {BUTTON_HOME,       LV_KEY_HOME,        LV_KEY_HOME,            LV_KEY_DEFAULT},
    #endif

    {BUTTON_OUTPUT,     LV_KEY_OUTPUT,      LV_KEY_OUTPUT,          LV_KEY_DEFAULT},

    #ifdef HAOYI_VER
    {BUTTON_DELAYER,    LV_KEY_DELAYER,     LV_KEY_DELAYER,         LV_KEY_DEFAULT},
    #else
    {BUTTON_PRESET,     LV_KEY_PRESET,      LV_KEY_PRESET_LONGP,    LV_KEY_DEFAULT},
    #endif

    {BUTTON_1,    '1',    '1',  LV_KEY_DEFAULT},
    {BUTTON_2,    '2',    '2',  LV_KEY_DEFAULT},
    {BUTTON_3,    '3',    '3',  LV_KEY_DEFAULT},
    {BUTTON_4,    '4',    '4',  LV_KEY_DEFAULT},
    {BUTTON_5,    '5',    '5',  LV_KEY_DEFAULT},
    {BUTTON_6,    '6',    '6',  LV_KEY_DEFAULT},
    {BUTTON_7,    '7',    '7',  LV_KEY_DEFAULT},
    {BUTTON_8,    '8',    '8',  LV_KEY_DEFAULT},
    {BUTTON_9,    '9',    '9',  LV_KEY_DEFAULT},

    {BUTTON_DOT,  '.',    '.',  LV_KEY_DEFAULT},
    {BUTTON_0,    '0',    '0',  LV_KEY_DEFAULT},
};


/*
 * @brief       lv_key_t Encoder_Get(void)
 * @details     将编码器值转化LV_KEY
 */
#include "TIM.h"
static lv_key_t Encoder_Get(void)
{
#define ENCODER_OFFSET (32768ul)
    static uint8_t flag = 0;
    if(flag == 0)
    {
        flag = 1;
        HAL_TIM_Base_Start(&htim2);
        htim2.Instance->CNT = ENCODER_OFFSET;
    }
    lv_key_t key = LV_KEY_DEFAULT;
    SCB_CleanInvalidateDCache();
    int32_t count = ENCODER_OFFSET - __HAL_TIM_GET_COUNTER(&htim2);
    __HAL_TIM_SET_COUNTER(&htim2, ENCODER_OFFSET);
    static int32_t diffCount = 0;
    diffCount += count;
    if(diffCount > 5) {
        diffCount = 5;
    }
    if(diffCount < -5) {
        diffCount = -5;
    }
    if(diffCount > 0)
    {
        key = LV_KEY_DOWN;
        --diffCount;
    }
    else
        if(diffCount < 0)
        {
            key = LV_KEY_UP;
            ++diffCount;
        }
    return key;
}

#include "Button_Device.h"
/*
 * @brief       lv_key_t Button_toKey(uint8_t buttonNum,uint8_t flag)
 * @details     将实体按�?��为LV_KEY事件
 */
lv_key_t Button_toKey(uint8_t buttonNum, uint8_t flag)
{
    static uint8_t waitCount = 0;
    if(buttonNum == 0xff) {
    } else {
        //实体按键
        uint16_t tablesize = sizeof(Btn_KeyTable) / sizeof(Btn_KeyTable[0]);
        for(uint8_t i = 0; i < tablesize; ++i)
        {
            if(buttonNum == Btn_KeyTable[i].buttonNum)
            {
                lv_key_t key = LV_KEY_DEFAULT;
                switch(flag)
                {
                    case KEY_STATE_HOLD:
                        key = Btn_KeyTable[i].key_hold;
                        break;
                    case KEY_STATE_CLICKED:
                        key = Btn_KeyTable[i].key_short;
                        break;
                    case KEY_STATE_LONGGP:
                        key = Btn_KeyTable[i].key_long;
                        break;
                    default:
                        key = LV_KEY_DEFAULT;
                        break;
                }
                //                if((key == LV_KEY_ENCODER) || (key == LV_KEY_ENCODER_LONGP))
                {
                    waitCount = 5;
                }
                return key;
            }
        }
    }
    //编码器转�?
    lv_key_t encoderKey = Encoder_Get();
    //防�?按下编码�? �?��发旋�?
    if(waitCount == 0) {
        if(encoderKey != LV_KEY_DEFAULT)
        {
            return encoderKey;
        }
    } else {
        waitCount--;
    }
    return LV_KEY_DEFAULT;
}


void GUI_KeySend(lv_obj_t *obj, lv_key_t key)
{
    if((obj != NULL) && (key != 0)) {
        lv_event_send(obj, LV_EVENT_KEY, &key);
    }
}





static const uint8_t userCRCHi[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40
};

static const uint8_t userCRCLo[] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7,
    0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,
    0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9,
    0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
    0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
    0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D,
    0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
    0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF,
    0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1,
    0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
    0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB,
    0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
    0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
    0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97,
    0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,
    0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89,
    0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83,
    0x41, 0x81, 0x80, 0x40
};

/*
 * @brief       uint16_t userCRC_Calculate(uint8_t *pucFrame, uint16_t usLen)
 * @details     计算CRC
 */
uint16_t userCRC_Calculate(uint8_t *pucFrame, uint16_t usLen)
{
    uint8_t ucCRCHi = 0xFF;
    uint8_t ucCRCLo = 0xFF;
    int iIndex;
    while(usLen--)
    {
        iIndex = ucCRCLo ^ *(pucFrame++);
        ucCRCLo = (uint8_t)(ucCRCHi ^ userCRCHi[iIndex]);
        ucCRCHi = userCRCLo[iIndex];
    }
    return (uint16_t)(ucCRCHi << 8 | ucCRCLo);
}


