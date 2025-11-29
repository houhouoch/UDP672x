#ifndef _INPUT_WIDGET_H_
#define _INPUT_WIDGET_H_

#include "Commd.h"


//呼出Double编辑窗口
void InputVal_DoubleEdit(const MultStr_Def *title, double *data, const char *dispfmt,
                         const double *stepArray, uint8_t arraySize,
                         double max, double min,
                         const MultStr_Def *minTips, const MultStr_Def *maxTips,
                         void (*enterCb)(void));
//Double编辑窗口事件回调函数
void InputVal_Double_handler(lv_obj_t *obj, lv_event_t event);

//呼出Double编辑窗口
void InputVal_IntEdit(const MultStr_Def *title, int *data, const char *dispfmt,
                      const int *stepArray, uint8_t arraySize,
                      int max, int min,
                      const MultStr_Def *minTips, const MultStr_Def *maxTips,
                      void (*enterCb)(void));
//Double编辑窗口事件回调函数
void InputVal_Int_handler(lv_obj_t *obj, lv_event_t event);



void InputVal_StringEdit_SetCall(const MultStr_Def *title, char *string, int maxLen);
void InputVal_StringEdit_handler(lv_obj_t *obj, lv_event_t event);



/*
 * @brief       void Boot_CalibMode_Check(void)
 * @details     校准模式按键进入检测(PRESET)
 */
void Boot_CalibMode_Check(void);

void InputWidget_Create(void);

#endif
