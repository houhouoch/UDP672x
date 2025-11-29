#ifndef __MSG_BOX_H
#define __MSG_BOX_H

#include <stdarg.h>
#include "Commd.h"

enum {
    MSG_TYPE_TIPS = 1,
    MSG_TYPE_WARRING,
    MSG_TYPE_ERROR,

    MSG_TYPE_COM
};

void MsgBox_GroupCreate(void);
void MsgBox_Exit(void);

void IF_MsgBox_Tips(const char *str);
void IF_MsgBox_Warring(const char *str, uint8_t *pflag);
void IF_MsgBox_Error(const char *str, uint8_t *pflag);

void IF_MsgBox_Tips_Mult(const MultStr_Def *multMsg);
void IF_MsgBox_Warring_Mult(const MultStr_Def *multMsg, uint8_t *pflag);
void IF_MsgBox_Error_Mult(const MultStr_Def *multMsg, uint8_t *pflag);


void IF_MsgBox_BatTester_Pass(const char *str);
void IF_MsgBox_BatTester_Pass_Mult(const MultStr_Def *multMsg);
void IF_MsgBox_BatTester_Error(const char *str, uint8_t *pflag, const char *fmt, ...);
void IF_MsgBox_BatTester_Error_Mult(const MultStr_Def *multMsg, uint8_t *pflag, const char *fmt, ...);


void MsgBox_Event_handler(lv_obj_t *obj, lv_event_t event);

void MsgBox_Tick(uint16_t tickTime);
#endif
