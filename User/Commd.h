#ifndef __UI_COMMD_H_
#define __UI_COMMD_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lvgl/lvgl.h"
#include "gui_guider.h"
#include "Style.h"
#include "MultString.h"
#include "Beep_Device.h"
#include "Task_Manager.h"


//使用看门狗
#define USE_WDG (1)


//#define USE_BATTESTER (1)

/*
定时器:
TIM7: List & Delay运行定时器,默认开启
TIM2: 编码器输入
TIM3: 蜂鸣器PWM 4Khz
TIM4: CH3 假负载PD14
TIM16:CH1:屏幕背光(5Khz)
TIM17:斜率/回读等
 */
#define CALIB_MODE_PASSWD (1218ul)
#define FIRMWARE_VER    "1.02.0901"
#if defined(UDP6922B)
    #ifdef HAOYI_VER
        #define ABOUT_MODEL     "HY6922B"
    #else
        #ifndef VER_A
            #define ABOUT_MODEL     "UDP6922B"
        #else
            #define ABOUT_MODEL     "UDP69100"
        #endif
    #endif
    //电压
    #define VOL_MIN     (0.000f)
    #define VOL_MAX     (62.000f)
    //电流
    #define AMP_MIN     (0.000f)
    #define AMP_MAX     (5.500f)
    #define AMP_ZERO    (0.004f)
    //功率
    #define WAT_MIN     (0.000f)
    #define WAT_MAX     (115.0f)
    //电压表
    #define DVM_MIN     (0.000f)
    #define DVM_MAX     (65.00f)
    #define ELOAD_AMP_MAX   (0.300f)     //500mA假负载,Max
    #define ELOAD_AMP       (ELOAD_AMP_MAX/2)     //150mA假负载(恒电流)
    #define ELOAD_AMP_MIN   (0.01f)
    //斜率
    #define VSR_MIN     (0.01f)
    #define VSR_MAX     (2*VOL_MAX)
    #define VSR_NORMAL_UP   (10*VOL_MAX)
    #define VSR_NORMAL_DOWN (10*VOL_MAX)

    #define ISR_MIN     (0.01f)
    #define ISR_MAX     (2*AMP_MAX)
    #define ISR_NORMAL_UP   (10*AMP_MAX)
    #define ISR_NORMAL_DOWN (10*AMP_MAX)
#elif defined(UDP6932B)
    #ifndef HAOYI_VER
        #ifndef VER_A
            #define ABOUT_MODEL     "UDP6932B"
        #else
            #define ABOUT_MODEL     "UDP69200"
        #endif
    #else
        #define ABOUT_MODEL     "HY6932B"
    #endif
    //电压
    #define VOL_MIN     (0.000f)
    #define VOL_MAX     (62.000f)
    //电流
    #define AMP_MIN     (0.000f)
    #define AMP_MAX     (10.500f)
    #define AMP_ZERO    (0.004f)
    //功率
    #define WAT_MIN     (0.000f)
    #define WAT_MAX     (210.0f)
    //电压表
    #define DVM_MIN     (0.000f)
    #define DVM_MAX     (65.00f)
    #define ELOAD_AMP_MAX   (0.300f)     //500mA假负载,Max
    #define ELOAD_AMP       (ELOAD_AMP_MAX/2)     //150mA假负载(恒电流)
    #define ELOAD_AMP_MIN   (0.01f)
    //斜率
    #define VSR_MIN     (0.01f)
    #define VSR_MAX     (2*VOL_MAX)
    #define VSR_NORMAL_UP   (10*VOL_MAX)
    #define VSR_NORMAL_DOWN (10*VOL_MAX)

    #define ISR_MIN     (0.01f)
    #define ISR_MAX     (2*AMP_MAX)
    #define ISR_NORMAL_UP   (10*AMP_MAX)
    #define ISR_NORMAL_DOWN (10*AMP_MAX)
#elif defined(UDP6933B)
    #if defined(HAOYI_VER)
        #define ABOUT_MODEL     "HY6933B"
    #elif defined(DC_POWER_VER)
        #define ABOUT_MODEL     "1192-150-5"
    #else
        #define ABOUT_MODEL     "UDP6933B"
    #endif
    //电压
    #define VOL_MIN     (0.000f)
    #define VOL_MAX     (152.000f)
    //电流
    #define AMP_MIN     (0.000f)
    #define AMP_MAX     (5.500f)
    #define AMP_ZERO    (0.002f)
    //功率
    #define WAT_MIN     (0.000f)
    #define WAT_MAX     (220.0f)
    //电压表
    #define DVM_MIN     (0.000f)
    #define DVM_MAX     (155.00f)
    #define ELOAD_AMP_MAX   (0.300f)     //500mA假负载,Max
    #define ELOAD_AMP       (ELOAD_AMP_MAX/2)     //150mA假负载(恒电流)
    #define ELOAD_AMP_MIN   (0.01f)
    //斜率
    #define VSR_MIN     (0.01f)
    #define VSR_MAX     (50*VOL_MAX)
    #define VSR_NORMAL_UP   (50*VOL_MAX)
    #define VSR_NORMAL_DOWN (50*VOL_MAX)

    #define ISR_MIN     (0.01f)
    #define ISR_MAX     (50*AMP_MAX)
    #define ISR_NORMAL_UP   (50*AMP_MAX)
    #define ISR_NORMAL_DOWN (50*AMP_MAX)
#elif defined(UDP6942B)
    #if defined(HAOYI_VER)
        #define ABOUT_MODEL     "HY6933B"
    #elif defined(JINGHUI_VER)
        #define ABOUT_MODEL     "JDP6942B"
    #elif defined(DC_POWER_VER)
        #define ABOUT_MODEL     "1192-60-15"
    #else
        #ifndef VER_A
            #define ABOUT_MODEL     "UDP6942B"
        #else
            #define ABOUT_MODEL     "UDP69360"
        #endif
    #endif
    //电压
    #define VOL_MIN     (0.000f)
    #define VOL_MAX     (62.000f)
    //电流
    #define AMP_MIN     (0.000f)
    #define AMP_MAX     (15.500f)
    #define AMP_ZERO    (0.000f)
    //功率
    #define WAT_MIN     (0.000f)
    #define WAT_MAX     (365.0f)
    //电压表
    #define DVM_MIN     (0.000f)
    #define DVM_MAX     (65.00f)
    #define ELOAD_AMP_MAX   (0.300f)     //500mA假负载,Max
    #define ELOAD_AMP       (ELOAD_AMP_MAX/2)     //150mA假负载(恒电流)
    #define ELOAD_AMP_MIN   (0.01f)
    //斜率
    #define VSR_MIN     (0.01f)
    #define VSR_MAX     (2*VOL_MAX)
    #define VSR_NORMAL_UP   (100*VOL_MAX)
    #define VSR_NORMAL_DOWN (100*VOL_MAX)

    #define ISR_MIN     (0.01f)
    #define ISR_MAX     (2*AMP_MAX)
    #define ISR_NORMAL_UP   (10*AMP_MAX)
    #define ISR_NORMAL_DOWN (10*AMP_MAX)
#elif  defined(UDP6952B)
    #if defined(HAOYI_VER)
        #define ABOUT_MODEL     "HY6952B"
    #elif defined(JINGHUI_VER)
        #define ABOUT_MODEL     "JDP6952B"
    #elif defined(DC_POWER_VER)
        #define ABOUT_MODEL     "1192-60-25"
    #else
        #ifndef VER_A
            #define ABOUT_MODEL     "UDP6952B"
        #else
            #define ABOUT_MODEL     "UDP6952A"
        #endif
    #endif
    //电压
    #define VOL_MIN     (0.000f)
    #define VOL_MAX     (62.00f)
    //电流
    #define AMP_MIN     (0.000f)
    #define AMP_MAX     (25.500f)
    #define AMP_ZERO    (0.004f)
    //功率
    #define WAT_MIN     (0.000f)
    #define WAT_MAX     (615.0f)
    //电压表
    #define DVM_MIN     (0.000f)
    #define DVM_MAX     (65.00f)
    #define ELOAD_AMP_MAX   (0.150f)     //500mA假负载,Max
    #define ELOAD_AMP       (ELOAD_AMP_MAX)     //150mA假负载(恒电流)
    #define ELOAD_AMP_MIN   (0.04f)
    //斜率
    #define VSR_MIN     (0.01f)
    #define VSR_MAX     (2*VOL_MAX)
    #define VSR_NORMAL_UP   (5*VOL_MAX)
    #define VSR_NORMAL_DOWN (5*VOL_MAX)

    #define ISR_MIN     (0.01f)
    #define ISR_MAX     (2*AMP_MAX)
    #define ISR_NORMAL_UP   (10*AMP_MAX)
    #define ISR_NORMAL_DOWN (10*AMP_MAX)
#elif  defined(UDP6953B)
    #if defined(HAOYI_VER)
        #define ABOUT_MODEL     "HY6953B"
    #elif defined(JINGHUI_VER)
        #define ABOUT_MODEL     "JDP6953B"
    #elif defined(DC_POWER_VER)
        #define ABOUT_MODEL     "1192-150-10"
    #else
        #ifndef VER_A
            #define ABOUT_MODEL     "UDP6953B"
        #else
            #define ABOUT_MODEL     "UDP6953A"
        #endif
    #endif

    //电压
    #define VOL_MIN     (0.000f)
    #define VOL_MAX     (152.00f)
    //电流
    #define AMP_MIN     (0.000f)
    #define AMP_MAX     (10.500f)
    #define AMP_ZERO    (0.004f)
    //功率
    #define WAT_MIN     (0.000f)
    #define WAT_MAX     (615.0f)
    //电压表
    #define DVM_MIN     (0.000f)
    #define DVM_MAX     (155.00f)
    #define ELOAD_AMP_MAX   (0.150f)     //500mA假负载,Max
    #define ELOAD_AMP       (ELOAD_AMP_MAX)     //150mA假负载(恒电流)
    #define ELOAD_AMP_MIN   (0.04f)
    //斜率
    #define VSR_MIN     (0.01f)
    #define VSR_MAX     (2*VOL_MAX)
    #define VSR_NORMAL_UP   (7*VOL_MAX)
    #define VSR_NORMAL_DOWN (7*VOL_MAX)

    #define ISR_MIN     (0.01f)
    #define ISR_MAX     (2*AMP_MAX)
    #define ISR_NORMAL_UP   (10*AMP_MAX)
    #define ISR_NORMAL_DOWN (10*AMP_MAX)


#elif defined(UDP40_40)
    #define ABOUT_MODEL     "UDP4040"
    //电压
    #define VOL_MIN     (0.000f)
    #define VOL_MAX     (41.000f)
    //电流
    #define AMP_MIN     (0.000f)
    #define AMP_MAX     (41.000f)
    #define AMP_ZERO    (0.000f)
    //功率
    #define WAT_MIN     (0.000f)
    #define WAT_MAX     (410.0f)
    //电压表
    #define DVM_MIN     (0.000f)
    #define DVM_MAX     (65.00f)
    #define ELOAD_AMP_MAX   (0.150f)     //500mA假负载,Max
    #define ELOAD_AMP       (ELOAD_AMP_MAX/2)     //150mA假负载(恒电流)
    #define ELOAD_AMP_MIN   (0.01f)
    //斜率
    #define VSR_MIN     (0.01f)
    #define VSR_MAX     (500*VOL_MAX)
    #define VSR_NORMAL_UP   (500*VOL_MAX)
    #define VSR_NORMAL_DOWN (500*VOL_MAX)

    #define ISR_MIN     (0.01f)
    #define ISR_MAX     (500*AMP_MAX)
    #define ISR_NORMAL_UP   (500*AMP_MAX)
    #define ISR_NORMAL_DOWN (500*AMP_MAX)
#elif defined(UDP40_80)
    #define ABOUT_MODEL     "UDP4080"
    //电压
    #define VOL_MIN     (0.000f)
    #define VOL_MAX     (41.000f)
    //电流
    #define AMP_MIN     (0.000f)
    #define AMP_MAX     (82.000f)
    #define AMP_ZERO    (0.000f)
    //功率
    #define WAT_MIN     (0.000f)
    #define WAT_MAX     (820.0f)
    //电压表
    #define DVM_MIN     (0.000f)
    #define DVM_MAX     (65.00f)
    #define ELOAD_AMP_MAX   (0.150f)     //500mA假负载,Max
    #define ELOAD_AMP       (ELOAD_AMP_MAX/2)     //150mA假负载(恒电流)
    #define ELOAD_AMP_MIN   (0.01f)
    //斜率
    #define VSR_MIN     (0.01f)
    #define VSR_MAX     (500*VOL_MAX)
    #define VSR_NORMAL_UP   (500*VOL_MAX)
    #define VSR_NORMAL_DOWN (500*VOL_MAX)

    #define ISR_MIN     (0.01f)
    #define ISR_MAX     (500*AMP_MAX)
    #define ISR_NORMAL_UP   (500*AMP_MAX)
    #define ISR_NORMAL_DOWN (500*AMP_MAX)



#elif  defined(UDP6943B)
    #ifndef VER_A
        #define ABOUT_MODEL     "UDP6943B"
    #else
        #define ABOUT_MODEL     "UDP6943A"
    #endif
    //电压
    #define VOL_MIN     (0.000f)
    #define VOL_MAX     (255.00f)
    //电流
    #define AMP_MIN     (0.000f)
    #define AMP_MAX     (3.800f)
    #define AMP_ZERO    (0.000f)
    //功率
    #define WAT_MIN     (0.000f)
    #define WAT_MAX     (365.0f)
    //电压表
    #define DVM_MIN     (0.000f)
    #define DVM_MAX     (255.00f)
    #define ELOAD_AMP_MAX   (0.330f)     //500mA假负载,Max
    #define ELOAD_AMP       (ELOAD_AMP_MAX)     //150mA假负载(恒电流)
    #define ELOAD_AMP_MIN   (0.04f)
    //斜率
    #define VSR_MIN     (0.01f)
    #define VSR_MAX     (2*VOL_MAX)
    #define VSR_NORMAL_UP   (7*VOL_MAX)
    #define VSR_NORMAL_DOWN (7*VOL_MAX)

    #define ISR_MIN     (0.01f)
    #define ISR_MAX     (2*AMP_MAX)
    #define ISR_NORMAL_UP   (10*AMP_MAX)
    #define ISR_NORMAL_DOWN (10*AMP_MAX)
#endif

/*
 * @brief
 * @details
 */
extern double K_V;
extern double K_I;
extern double Offset_V;
extern double Offset_I;
#define ADC_MAX_VOL     ((double)(5.0))
#define ADC_MAX_COUNT   (0xffffff)
#define K_V_ADC         (K_V/ADC_MAX_VOL)
#define K_I_ADC         (K_I/ADC_MAX_VOL)

#define DAC_MAX_VOL     ((double)(2.5))
#define DAC_MAX_COUNT   (0xffff)
#define K_V_DAC         (DAC_MAX_COUNT/(K_V/(ADC_MAX_VOL/DAC_MAX_VOL)))
#define K_I_DAC         (DAC_MAX_COUNT/(K_I/(ADC_MAX_VOL/DAC_MAX_VOL)))




#define TIMEOFF_MIN (0.5f)
#define TIMEOFF_MAX (99999.9f)



//保持时间
#define KT_MIN      (0.1f)
#define KT_MAX      (99999.9f)
//延迟时间
#define DT_MIN      (1.0f)
#define DT_MAX      (99999.9f)
//保护延时
#define TRIG_TIME_MIN   (0.0f)
#define TRIG_TIME_MAX   (99.9f)
//循环次数
#define CYCLE_MIN   (0)
#define CYCLE_MAX   (99999)
//点数
#define LIST_POINT_MIN          (0)
#define LIST_POINT_COUNT_MIN    (1)
#define LIST_POINT_MAX          (LISTOUT_MAX_COUNT)

#define BAT_TESTER_POINT_MIN        (0)
#define BAT_TESTER_POINT_COUNT_MIN  (1)
#define BAT_TESTER_POINT_MAX        (BAT_TESTER_MAX_COUNT)

#define DELAY_POINT_MIN         (0)
#define DELAY_POINT_COUNT_MIN   (1)
#define DELAY_POINT_MAX         (DELAYOUT_MAX_COUNT)
//波特率
#define BAUDR_MIN   (9600)
#define BAUDR_MAX   (115200)
//通讯地址
#define PROTOCOL_ADDR_MIN        (1)
#define PROTOCOL_ADDR_MAX        (32)
//背光
#define BACK_LIGHT_MIN  (20)
#define BACK_LIGHT_MAX  (100)

//占空比/对称
#define SYMMETRY_MIN   (0.0f)
#define SYMMETRY_MAX   (100.0f)
//指数值
#define EXP_VALUE_MIN   (0)
#define EXP_VALUE_MAX   (10)



#define NumberInput_Process(maxLen,SetFunction)            \
    static uint8_t inputIdx = 0;                    \
    static char inputBuf[32] = {0};                 \
    static uint8_t numInput_flag = 0;               \
    if(event == LV_EVENT_KEY){                          \
        lv_key_t key = *(lv_key_t*)lv_event_get_data(); \
        if((key == '.') || (('0' <= key) && (key <= '9'))) {       \
            numInput_flag = 1;                          \
            if( (inputIdx>=maxLen)){                    \
            }else{                                      \
                inputBuf[inputIdx] = key;                   \
                inputBuf[inputIdx + 1] = '\0';              \
                lv_label_set_text_static(obj, inputBuf);    \
                lv_label_set_text_sel_start(obj, inputIdx); \
                lv_label_set_text_sel_end(obj, inputIdx+1); \
                inputIdx += 1;                              \
            }                                           \
        }                                               \
        if(numInput_flag == 1){                         \
            switch(key){                                \
                case LV_KEY_LEFT:                       \
                    if(inputIdx>0){                     \
                        inputBuf[--inputIdx] = 0;       \
                        lv_label_set_text_static(obj, inputBuf);    \
                        lv_label_set_text_sel_start(obj, inputIdx-1); \
                        lv_label_set_text_sel_end(obj, inputIdx); \
                    }                                   \
                    return;                             \
                case LV_KEY_RETURN:                     \
                case LV_KEY_ESC:                        \
                    numInput_flag = 0;                  \
                    inputIdx = 0;                       \
                    memset(inputBuf, 0, sizeof(inputBuf));      \
                    inputBuf[0] = '0';                          \
                    /*lv_label_set_text_static(obj, inputBuf);    */\
                    lv_label_set_text_sel_start(obj, LV_LABEL_TEXT_SEL_OFF); \
                    lv_label_set_text_sel_end(obj, LV_LABEL_TEXT_SEL_OFF); \
                    return;                             \
                case LV_KEY_ENCODER:                    \
                case LV_KEY_ENTER:                      \
                    inputIdx = 0; numInput_flag = 0;    \
                    SetFunction(atof(inputBuf));        \
                    memset(inputBuf, 0, sizeof(inputBuf));     \
                    lv_event_send(obj,LV_EVENT_CLICKED,NULL);         \
                    return;                             \
                default:return ;                        \
            }                                           \
        }                                               \
    }










#define GUI_SEND_KEY(K) UI_KeyQueue_Send(K)

//主页面对象
extern lv_ui ui;

extern const int32_t BaudRate_step[6];
//步进值
extern const int calib_passwd_step[6];
extern const double V_Calib_step[8];
extern const double A_Calib_step[8];


extern const float V_step[5];
extern const float A_step[6];

extern const float W_step[5];
extern const float timeoff_step[6];

extern const float VSR_step[5];
extern const float ISR_step[4];

extern const float kT_step[6];
extern const float dT_step[6];

extern const int cycle_step[4];
extern const int point_step[4];
extern const int baudR_step[5];

extern const int symmetry_step[2];
extern const float exp_step[2];


extern const float BatteryTester_V_step[5];
extern const float BatteryTester_A_step[5];
extern const float BatteryTester_W_step[5];
extern const float BatteryTester_kT_step[6];
#define BAT_TESTER_VOL_SET_FORM     "%6.3f"
#define BAT_TESTER_AMP_SET_FORM     "%6.3f"
#define BAT_TESTER_WAT_SET_FORM     "%06.2f"
#define BAT_TESTER_DVM_SET_FORM     "%6.3f"
#define BAT_TESTER_KT_SET_FORM      "%7.1f"


//显示格式
#define VOL_CALIB_FORM      "%09.5f"
#define AMP_CALIB_FORM      "%09.5f"

#define VOL_SET_FORM        "%0.3f"
#define AMP_SET_FORM        "%0.4f"


#define WAT_SET_FORM        "%06.2f"
#define TIMEOFF_SET_FORM    "%07.1f"

#if defined(USER_DEBUG)
    #define VOL_DISP_FORM_H     "%0.3f"
    #define VOL_DISP_FORM_M     "%0.4f"
    #define VOL_DISP_FORM_L     "%0.5f"
    #define AMP_DISP_FORM_H     "%0.4f"
    #define AMP_DISP_FORM_L     "%0.5f"
    #define WAT_DISP_FORM_H     "%0.3f"
    #define WAT_DISP_FORM_M     "%0.4f"
    #define WAT_DISP_FORM_L     "%0.5f"
#else
    #define VOL_DISP_FORM_H     "%0.2f"
    #define VOL_DISP_FORM_M     "%0.3f"
    #define VOL_DISP_FORM_L     "%0.4f"
    #define AMP_DISP_FORM_H     "%0.3f"
    #define AMP_DISP_FORM_L     "%0.4f"
    #define WAT_DISP_FORM_H     "%0.2f"
    #define WAT_DISP_FORM_M     "%0.3f"
    #define WAT_DISP_FORM_L     "%0.4f"
#endif

#define VSR_SET_FORM        "%05.2f"
#define ISR_SET_FORM        "%04.2f"

#define VOL_LIMIT_FORM      "%06.3f"
#define AMP_LIMIT_FORM      "%07.4f"

#define KEEP_TIME_FORM      "%7.1f"
#define DELAY_TIME_FORM     "%7.1f"
#define POINT_DISP_FORM     "%03d"
#define CYCLES_DISP_FORM    "%05d"

#define SYMMETRY_FORM       "%3d"
#define EXP_VALUE_FORM      "%02d"

//校准模式
#define POWER_CALIB_MODE    (systemInfo.calibMode)
#define SCPI_REMOTE_MODE    (systemInfo.status.bits.scpi_remote)

#define VOL_SET_VALUE       (CurGroup.outset.V_Set)
#define AMP_SET_VALUE       (CurGroup.outset.I_Set)
#define VOL_LIMIT_VALUE     (CurGroup.outset.V_OVP)
#define AMP_LIMIT_VALUE     (CurGroup.outset.I_OCP)
#define VOL_OVP_EN          (CurGroup.outset.OVP_onoff)
#define AMP_OCP_EN          (CurGroup.outset.OCP_onoff)
#define TIMEOFF_SET_ONOFF   (CurGroup.outset.Timeout_onoff)
#define TIMEOFF_SET_VALUE   (CurGroup.outset.TimeOff)

#define DVM_ONOFF_SET       (CurGroup.outset.dvm_onoff)
#define POWER_MODE          (CurGroup.outset.mode)
#define POWER_SR_MODE       (CurGroup.outset.SR_Mode)
#define POWER_VSR_UP        (CurGroup.outset.V_SR_U)
#define POWER_VSR_DOWN      (CurGroup.outset.V_SR_D)
#define POWER_ISR_UP        (CurGroup.outset.I_SR_U)
#define POWER_ISR_DOWN      (CurGroup.outset.I_SR_D)

#define POWER_OUTKEEPON_SET (CurGroup.outset.P_Out)
//
#define BACKLIGHT_SET   (systemInfo.option.base.backLight)
#define BEEP_SET        (systemInfo.option.base.beep)
#define POWERDOWN_SET   (systemInfo.option.base.powerDown)
//
#define COMM_BAUDR_SET          (systemInfo.option.comm_uart.baudRate)
#define COMM_PROTOL_SET         (systemInfo.option.comm_uart.protolType)
#define COMM_PROTOL_ADDR_SET    (systemInfo.option.comm_uart.protolAddr)
//
#define IP_SET_TMP      (systemInfo.option.net.ipAddr_tmp)
#define NETMASK_SET_TMP (systemInfo.option.net.netMask_tmp)
#define GW_SET_TMP      (systemInfo.option.net.gateWay_tmp)
#define DHCP_SET_TMP    (systemInfo.option.net.dhcp_onoff_tmp)
//
#define IP_SET          (systemInfo.option.net.ipAddr)
#define NETMASK_SET     (systemInfo.option.net.netMask)
#define GW_SET          (systemInfo.option.net.gateWay)
#define DHCP_SET        (systemInfo.option.net.dhcp_onoff)

#define LANGUAGE_SET    (systemInfo.option.language)

//不保存
#define VOL_DAC_V_UP_DELTA      (systemInfo.OutPut.dac.DAC_Vol_Up_delta)
#define VOL_DAC_V_DOWN_DELTA    (systemInfo.OutPut.dac.DAC_Vol_Down_delta)
#define AMP_DAC_A_UP_DELTA      (systemInfo.OutPut.dac.DAC_Amp_Up_delta)
#define AMP_DAC_A_DOWN_DELTA    (systemInfo.OutPut.dac.DAC_Amp_Down_delta)

#define VOL_DAC_V_TARGET    (systemInfo.OutPut.dac.DAC_Vol_target)
#define AMP_DAC_A_TARGET    (systemInfo.OutPut.dac.DAC_Amp_target)
#define VOL_DAC_V_NOW       (systemInfo.OutPut.dac.DAC_Vol_now)
#define AMP_DAC_A_NOW       (systemInfo.OutPut.dac.DAC_Amp_now)




#define NULL_ERROR()      do{printf("\r\n\r\nError at :%s %d\r\n\r\n",__FILE__,__LINE__);while(1);}while(0)





#include "MsgBox.h"
#define DEBUG(s)    do{printf(s);fflush(stdout);}while(0);



#ifndef MIN
    #define MIN(a,b) ((a<b)?a:b)
#endif
#ifndef MAX
    #define MAX(a,b) ((a>b)?a:b)
#endif

#ifndef ARRAY_COUNT
    #define ARRAY_COUNT(x) (sizeof(x)/sizeof(x[0]))
#endif




//数据设置
void BtnLabel_Set_Edit_Tag(lv_obj_t *obj, const char *tag);

void BtnLabel_Set_Edit_Value(lv_obj_t *obj, const char *text);



/*
 * @brief       void label_setSelNum(lv_obj_t* label,uint16_t numpos,const char* text)
 * @details     Label选择特定字符(用于设置数字)
 */
void label_setSelNum(lv_obj_t *label, uint16_t numpos, const char *text);
/*
 * @brief       void label_setSelStr(lv_obj_t* label,const char* str,const char* text)
 * @details     Label选择特定字符(用于设置参数)
 */
void label_setSelStr(lv_obj_t *label, const char *str, const char *text);
/*
 * @brief       void label_setSelIdx(lv_obj_t* label,const char* str,int idx)
 * @details     Label选择特定索引
 */
void label_setSelIdx(lv_obj_t *label, const char *str, int idx);


/*
 * @brief       lv_key_t Button_toKey(uint8_t buttonNum,uint8_t flag)
 * @details     将实体按键转为LV_KEY事件
 */
lv_key_t Button_toKey(uint8_t buttonNum, uint8_t flag);

void GUI_KeySend(lv_obj_t *obj, lv_key_t key);










/*
 * @brief       uint16_t userCRC_Calculate(uint8_t *pucFrame, uint16_t usLen)
 * @details     计算CRC
 */
uint16_t userCRC_Calculate(uint8_t *pucFrame, uint16_t usLen);

#endif
