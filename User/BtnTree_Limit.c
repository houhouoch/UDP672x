#include "BtnTree_Limit.h"

#include "Commd.h"

#include "HomePage.h"
#include "HomePage_2.h"

#include "ListOut.h"
#include "ListPage.h"
#include "ListPage_Table.h"
#include "ListPage_Option.h"
#include "ListPage_Manager.h"
#include "ListTempPage.h"

#include "MonitorPage.h"

#include "OutOptionPage.h"
#include "OutOptionPage_item.h"

#include "SettingPage.h"

#include "DelayOut.h"
#include "DelayOutPage.h"
#include "DelayOutPage_Table.h"
#include "DelayPage_Option.h"
#include "DelayPage_Manager.h"
#include "DelayTempPage.h"

#include "Trigger.h"
#include "TriggerPage.h"

#include "PresetPage.h"

#include "MenuPage.h"
#include "GroupPage.h"
#include "CalibPage.h"
#include "MsgBox.h"


typedef struct {
    lv_key_t key;
    const struct BtnInfo_Def *btn;
    //提示
    uint8_t msgtype;
    const MultStr_Def *msg;
} InvalidBtn_Key_Def;

//List功能无效按键 & 节点
//1.无法手动设置电源输出
//2.无法改变电源工作模式
//3.无法保存/加载用户�?
//4.无法保存/加载预�?�?
//5.List的基础参数与点参数无法编辑
//6.无法加载/保存List文件
//7.无法开启Delay模式
static const InvalidBtn_Key_Def listout_Running_invalid[]  = {
    //输出设置
    {.btn = &btn_VSet,      .msgtype = MSG_TYPE_TIPS, .msg = &mStr_list_noset},
    {.btn = &btn_ISet,      .msgtype = MSG_TYPE_TIPS, .msg = &mStr_list_noset},
    {.btn = &btn_Ilimit,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_list_noset},
    {.btn = &btn_Vlimit,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_list_noset},
    {.btn = &btn_TimeOff,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_list_noset},
    {.btn = &btn_VSet_2,      .msgtype = MSG_TYPE_TIPS, .msg = &mStr_list_noset},
    {.btn = &btn_ISet_2,      .msgtype = MSG_TYPE_TIPS, .msg = &mStr_list_noset},
    {.btn = &btn_Ilimit_2,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_list_noset},
    {.btn = &btn_Vlimit_2,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_list_noset},
    {.btn = &btn_TimeOff_2,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_list_noset},
    //电源工作模式
    {.btn = &btn_Mode,          .msgtype = MSG_TYPE_TIPS, .msg = &mStr_list_noset},
    //用户�?
    {.btn = &btn_group_save,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_list_noset},
    {.btn = &btn_group_saveAs,  .msgtype = MSG_TYPE_TIPS, .msg = &mStr_list_noset},
    {.btn = &btn_group_load,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_list_noset},
    //预�?�?
    {.btn = &btn_preset_save,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_list_noset},
    {.btn = &btn_preset_load,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_list_noset},
    //ListOut编辑
    {.btn = &btn_list_start,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_list_noedit},
    {.btn = &btn_list_Groups,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_list_noedit},
    {.btn = &btn_list_cycle,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_list_noedit},
    //{.btn = &btn_list_endState,  .msgtype = MSG_TYPE_TIPS, .msg = &mStr_list_noedit},
    {.btn = &btn_list_table,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_list_noedit},
    {.btn = &btn_list_manage,   .msgtype = MSG_TYPE_TIPS, .msg = &mStr_list_noedit},
    {.btn = &btn_start,          .msgtype = MSG_TYPE_TIPS, .msg = &mStr_list_noDelay},
    {.btn = NULL,   .key = LV_KEY_DEFAULT},
};

//Delay功能无效按键 & 节点
//1.Delay基�?参数与点参数无法设置
//2.无法开启List模式
static const InvalidBtn_Key_Def delayout_Running_invalid[]  = {
    {.btn = &btn_delay_start,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_delay_noedit},
    {.btn = &btn_delay_Groups,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_delay_noedit},
    {.btn = &btn_delay_cycle,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_delay_noedit},
    {.btn = &btn_delay_table,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_delay_noedit},
    {.btn = &btn_start,          .msgtype = MSG_TYPE_TIPS, .msg = &mStr_delay_noList},
    {.btn = NULL,   .key = LV_KEY_DEFAULT},
};

static const InvalidBtn_Key_Def batteryTester_Running_invalid[] = {
    //输出设置
    {.btn = &btn_VSet,      .msgtype = MSG_TYPE_TIPS, .msg = &mStr_BatTester_noset},
    {.btn = &btn_ISet,      .msgtype = MSG_TYPE_TIPS, .msg = &mStr_BatTester_noset},
    {.btn = &btn_Ilimit,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_BatTester_noset},
    {.btn = &btn_Vlimit,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_BatTester_noset},
    {.btn = &btn_TimeOff,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_BatTester_noset},
    {.btn = &btn_VSet_2,      .msgtype = MSG_TYPE_TIPS, .msg = &mStr_BatTester_noset},
    {.btn = &btn_ISet_2,      .msgtype = MSG_TYPE_TIPS, .msg = &mStr_BatTester_noset},
    {.btn = &btn_Ilimit_2,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_BatTester_noset},
    {.btn = &btn_Vlimit_2,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_BatTester_noset},
    {.btn = &btn_TimeOff_2,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_BatTester_noset},
    //电源工作模式
    {.btn = &btn_Mode,          .msgtype = MSG_TYPE_TIPS, .msg = &mStr_BatTester_noset},
    //用户�?
    {.btn = &btn_group_save,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_BatTester_noset},
    {.btn = &btn_group_saveAs,  .msgtype = MSG_TYPE_TIPS, .msg = &mStr_BatTester_noset},
    {.btn = &btn_group_load,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_BatTester_noset},
    //预�?�?
    {.btn = &btn_preset_save,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_BatTester_noset},
    {.btn = &btn_preset_load,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_BatTester_noset},
    //BatTester编辑
    {.btn = &btn_Battest_option,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_BatTester_noedit},

    //{.btn = &btn_list_endState,  .msgtype = MSG_TYPE_TIPS, .msg = &mStr_BatTester_noedit},
    {.btn = &btn_Battest_table,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_BatTester_noedit},
    {.btn = &btn_Battest_manage,   .msgtype = MSG_TYPE_TIPS, .msg = &mStr_BatTester_noedit},
    {.btn = &btn_start,          .msgtype = MSG_TYPE_TIPS, .msg = &mStr_BatTester_noDelay},
    {.btn = NULL,   .key = LV_KEY_DEFAULT},
};

//面板用户按键�?
//1.无法手动设置电源输出
//2.无法开启List和Delay模式
//3.无法保存/加载用户�?
//4.无法保存/加载预�?�?
//5.无法改变电源工作模式
//6.无法改变电源斜率模式和参�?
//7.�?��解锁弹出提示需�?"长按解锁"
static const InvalidBtn_Key_Def power_Lock_invalid[]  = {
    //    //输出设置
    //    {.btn = &btn_VSet,      .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    //    {.btn = &btn_ISet,      .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    //    {.btn = &btn_Ilimit,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    //    {.btn = &btn_Vlimit,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    //    {.btn = &btn_TimeOff,   .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    //    {.btn = &btn_VSet_2,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    //    {.btn = &btn_ISet_2,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    //    {.btn = &btn_Ilimit_2,  .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    //    {.btn = &btn_Vlimit_2,  .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    //    {.btn = &btn_TimeOff_2, .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    //    //List �? Delay开�?
    //    {.btn = &btn_start,     .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    //    //用户�?
    //    {.btn = &btn_group_save,   .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    //    {.btn = &btn_group_saveAs, .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    //    {.btn = &btn_group_load,   .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    //    //预�?�?
    //    {.btn = &btn_preset_save,   .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    //    {.btn = &btn_preset_load,   .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    //    //电源工作模式
    //    {.btn = &btn_Mode,          .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    //    //电源斜率
    //    {.btn = &btn_SR_Mode,       .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    //    {.btn = &btn_VSR_Rising,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    //    {.btn = &btn_VSR_Failing,   .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    //    {.btn = &btn_ISR_Rising,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    //    {.btn = &btn_ISR_Failing,   .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},




    //长按解锁
    {.key = LV_KEY_LOCK,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_tips},
    //
    {.key = LV_KEY_F1,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = LV_KEY_F2,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = LV_KEY_F3,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = LV_KEY_F4,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = LV_KEY_F5,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = LV_KEY_F6,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    //
    {.key = LV_KEY_F1_LONGP,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = LV_KEY_F2_LONGP,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = LV_KEY_F3_LONGP,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = LV_KEY_F4_LONGP,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = LV_KEY_F5_LONGP,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = LV_KEY_F6_LONGP,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    //
    #ifdef HAOYI_VER
    {.key = LV_KEY_WAVE,            .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = LV_KEY_DELAYER,          .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    #else
    {.key = LV_KEY_HOME,            .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = LV_KEY_PRESET,          .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = LV_KEY_PRESET_LONGP,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    #endif
    {.key = LV_KEY_MENU,            .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = LV_KEY_MENU_LONGP,      .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = LV_KEY_LIST,            .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},

    //
    {.key = LV_KEY_LEFT,            .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = LV_KEY_RIGHT,           .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = LV_KEY_ESC,             .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},

    {.key = LV_KEY_UP,              .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = LV_KEY_DOWN,            .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = LV_KEY_ENCODER,         .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = LV_KEY_ENCODER_LONGP,   .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    //
    {.key = '0',            .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = '1',            .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = '2',            .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = '3',            .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = '4',            .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = '5',            .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = '6',            .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = '7',            .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = '8',            .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = '9',            .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},
    {.key = '.',            .msgtype = MSG_TYPE_TIPS, .msg = &mStr_power_lock_noOperate},

    {.btn = NULL,   .key = LV_KEY_DEFAULT},
};

#if 1
//外部控制模式
//1.无法手动设置电源输出
//2.无法开启List与Delay
//3.无法加载/保存用户�?
//4.无法保存/加载预�?�?
static const InvalidBtn_Key_Def power_ExtC_invalid[]  = {
    //输出设置
    {.btn = &btn_VSet,      .msgtype = MSG_TYPE_TIPS, .msg = &mStr_ExtC_noSet},
    {.btn = &btn_ISet,      .msgtype = MSG_TYPE_TIPS, .msg = &mStr_ExtC_noSet},
    {.btn = &btn_VSet_2,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_ExtC_noSet},
    {.btn = &btn_ISet_2,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_ExtC_noSet},
    //用户�?
    {.btn = &btn_group_save,   .msgtype = MSG_TYPE_TIPS, .msg = &mStr_ExtC_noSet},
    {.btn = &btn_group_saveAs, .msgtype = MSG_TYPE_TIPS, .msg = &mStr_ExtC_noSet},
    {.btn = &btn_group_load,   .msgtype = MSG_TYPE_TIPS, .msg = &mStr_ExtC_noSet},
    //预�?值不允�?加载/保存
    {.btn = &btn_preset_save,     .msgtype = MSG_TYPE_TIPS, .msg = &mStr_ExtC_noSet},
    {.btn = &btn_preset_load,     .msgtype = MSG_TYPE_TIPS, .msg = &mStr_ExtC_noSet},
    //不允许开启List/Delay功能
    {.btn = &btn_start,          .msgtype = MSG_TYPE_TIPS, .msg = &mStr_ExtC_noSet},
    //
    {.btn = NULL,   .key = LV_KEY_DEFAULT},
};
#endif

#if 1
//DHCP�?��地址分配
//开�?��无法设置IP地址、网关、子网掩�?
static const InvalidBtn_Key_Def Setting_DHCP_invalid[]  = {
    {.btn = &btn_ip,        .msgtype = MSG_TYPE_TIPS, .msg = &mStr_Setting_DHCP_noSet},
    {.btn = &btn_netway,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_Setting_DHCP_noSet},
    {.btn = &btn_gateway,   .msgtype = MSG_TYPE_TIPS, .msg = &mStr_Setting_DHCP_noSet},
    {.btn = NULL,   .key = LV_KEY_DEFAULT},
};
#endif


//�?��斜率模式下,无法编辑电压&电流上升&下降斜率
static const InvalidBtn_Key_Def SlawRate_Normal_invalid[]  = {
    {.btn = &btn_VSR_Rising,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_SR_mode_noSet},
    {.btn = &btn_VSR_Failing,   .msgtype = MSG_TYPE_TIPS, .msg = &mStr_SR_mode_noSet},
    {.btn = &btn_ISR_Rising,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_SR_mode_noSet},
    {.btn = &btn_ISR_Failing,   .msgtype = MSG_TYPE_TIPS, .msg = &mStr_SR_mode_noSet},
    {.btn = NULL,   .key = LV_KEY_DEFAULT},
};

//电压斜率仅在电压斜率模式下�?�?
static const InvalidBtn_Key_Def SlawRate_VSR_invalid[]  = {
    {.btn = &btn_ISR_Rising,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_SR_mode_noSet},
    {.btn = &btn_ISR_Failing,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_SR_mode_noSet},
    {.btn = NULL,   .key = LV_KEY_DEFAULT},
};

//电流斜率仅在电流斜率模式下�?�?
static const InvalidBtn_Key_Def SlawRate_ISR_invalid[]  = {
    {.btn = &btn_VSR_Rising,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_SR_mode_noSet},
    {.btn = &btn_VSR_Failing,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_SR_mode_noSet},
    {.btn = NULL,   .key = LV_KEY_DEFAULT},
};


//电池检测功能加载文件无法编�?
static const InvalidBtn_Key_Def BatTester_NoEditable_invalid[]  = {
    {.btn = &btn_Battest_option,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_BatTester_loadFile_noedit},
    {.btn = &btn_Battest_table,    .msgtype = MSG_TYPE_TIPS, .msg = &mStr_BatTester_loadFile_noedit},

    {.btn = NULL,   .key = LV_KEY_DEFAULT},
};


static uint8_t Btn_InvalidKey_Check(const InvalidBtn_Key_Def *invBtnKey_Table, const struct BtnInfo_Def *btn, lv_key_t key)
{
    if(invBtnKey_Table == NULL) while(1);
    //    if(btn == NULL) while(1);
    const MultStr_Def *msg = NULL;
    uint8_t msgtype = 0;
    //比较按键
    for(uint16_t i = 0; ; ++i) {
        //
        if((invBtnKey_Table[i].key == LV_KEY_DEFAULT) && (invBtnKey_Table[i].btn == NULL)) {
            break;
        }
        if(btn != NULL) {
            if(memcmp(invBtnKey_Table[i].btn, btn, sizeof(const struct BtnInfo_Def)) == 0) {
                msg = invBtnKey_Table[i].msg;
                msgtype = invBtnKey_Table[i].msgtype;
                printf("%s\r\n", MultStr_GetS(msg));
                break;
            }
        } else
            if(key != LV_KEY_DEFAULT) {
                if(invBtnKey_Table[i].key == key) {
                    msg = invBtnKey_Table[i].msg;
                    msgtype = invBtnKey_Table[i].msgtype;
                    break;
                }
            }
    }
    //发送消�??
    if(msg != NULL) {
        switch(msgtype) {
            case MSG_TYPE_TIPS:
                IF_MsgBox_Tips_Mult(msg);
                break;
            case MSG_TYPE_WARRING:
                IF_MsgBox_Warring_Mult(msg, NULL);
                break;
            case MSG_TYPE_ERROR:
                IF_MsgBox_Error_Mult(msg, NULL);
                break;
        }
    }
    return (msg != NULL);
}


#include "Interface.h"
#include "List_Interface.h"
#include "Delay_Interface.h"
#include "BatTester_Interface.h"
#include "Setting_Interface.h"

//无效化虚拟按�??�?
uint8_t Btn_KeyInvalid_CheckBtn(const struct BtnInfo_Def *btn)
{
    if(btn != NULL) {
        //List输出
        if(ListOut_IsRunning() != 0) {
            if(0 != Btn_InvalidKey_Check(listout_Running_invalid, btn, LV_KEY_DEFAULT))
            {
                return 1;
            }
        }
        //Delay输出
        if(DelayOut_IsRunning() != 0) {
            if(0 != Btn_InvalidKey_Check(delayout_Running_invalid, btn, LV_KEY_DEFAULT))
            {
                return 1;
            }
        }
        //BatteryTester
        if(BatTester_IsRunning() != 0) {
            if(0 != Btn_InvalidKey_Check(batteryTester_Running_invalid, btn, LV_KEY_DEFAULT))
            {
                return 1;
            }
        }
        if(IF_BatTester_Get_Editable() == 0) {
            if(0 != Btn_InvalidKey_Check(BatTester_NoEditable_invalid, btn, LV_KEY_DEFAULT))
            {
                return 1;
            }
        }
        //Lock按键�?
        if(IF_Power_Get_Lock()) {
            if(0 != Btn_InvalidKey_Check(power_Lock_invalid, btn, LV_KEY_DEFAULT))
            {
                return 1;
            }
        }
        //斜率模式
        if(POWER_SR_MODE == SR_MODE_NORMAL_MODE) {
            if(0 != Btn_InvalidKey_Check(SlawRate_Normal_invalid, btn, LV_KEY_DEFAULT))
            {
                return 1;
            }
        } else
            if(POWER_SR_MODE == SR_MODE_VSR_MODE) {
                if(0 != Btn_InvalidKey_Check(SlawRate_VSR_invalid, btn, LV_KEY_DEFAULT))
                {
                    return 1;
                }
            } else
                if(POWER_SR_MODE == SR_MODE_ISR_MODE) {
                    if(0 != Btn_InvalidKey_Check(SlawRate_ISR_invalid, btn, LV_KEY_DEFAULT))
                    {
                        return 1;
                    }
                }
        //DHCP
        if(IF_System_Get_DHCP_TMP_Onoff() != 0) {
            if(0 != Btn_InvalidKey_Check(Setting_DHCP_invalid, btn, LV_KEY_DEFAULT))
            {
                return 1;
            }
        }
        //电源工作模式
        if(POWER_MODE_NORMAL != POWER_MODE) {
            if(0 != Btn_InvalidKey_Check(power_ExtC_invalid, btn, LV_KEY_DEFAULT))
            {
                return 1;
            }
        }
    }
    return IF_System_Get_AC_Power_Fault();
}
//无效实体按键检�?
uint8_t Btn_KeyInvalid_CheckKey(lv_key_t key)
{
    if(key != LV_KEY_DEFAULT) {
        //List输出
        if(ListOut_IsRunning() != 0) {
            if(0 != Btn_InvalidKey_Check(listout_Running_invalid, NULL, key))
            {
                return 1;
            }
        }
        //Delay输出
        if(DelayOut_IsRunning() != 0) {
            if(0 != Btn_InvalidKey_Check(delayout_Running_invalid, NULL, key))
            {
                return 1;
            }
        }
        //BatteryTester
        if(BatTester_IsRunning() != 0) {
            if(0 != Btn_InvalidKey_Check(batteryTester_Running_invalid, NULL, key))
            {
                return 1;
            }
        }
        if(IF_BatTester_Get_Editable() != 0) {
            if(0 != Btn_InvalidKey_Check(BatTester_NoEditable_invalid, NULL, key))
            {
                return 1;
            }
        }
        //Lock按键�?
        if(IF_Power_Get_Lock()) {
            if(0 != Btn_InvalidKey_Check(power_Lock_invalid, NULL, key))
            {
                return 1;
            }
        }
        //斜率模式
        if(POWER_SR_MODE == SR_MODE_NORMAL_MODE) {
            if(0 != Btn_InvalidKey_Check(SlawRate_Normal_invalid, NULL, key))
            {
                return 1;
            }
        } else
            if(POWER_SR_MODE == SR_MODE_VSR_MODE) {
                if(0 != Btn_InvalidKey_Check(SlawRate_VSR_invalid, NULL, key))
                {
                    return 1;
                }
            } else
                if(POWER_SR_MODE == SR_MODE_ISR_MODE) {
                    if(0 != Btn_InvalidKey_Check(SlawRate_ISR_invalid, NULL, key))
                    {
                        return 1;
                    }
                }
        //DHCP
        if(IF_System_Get_DHCP_TMP_Onoff() != 0) {
            if(0 != Btn_InvalidKey_Check(Setting_DHCP_invalid, NULL, key))
            {
                return 1;
            }
        }
        //电源工作模式
        if(POWER_MODE_NORMAL != POWER_MODE) {
            if(0 != Btn_InvalidKey_Check(power_ExtC_invalid, NULL, key))
            {
                return 1;
            }
        }
    }
    return IF_System_Get_AC_Power_Fault();
}

