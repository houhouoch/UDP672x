#include "MultString.h"
#include "SettingData.h"

/*
    1192-150-5
    1192-60-15
    1192-60-25
    1192-150-10
 */

/*
 * @brief       const char* MultStr_GetS(const MultStr_Def* multStr)
 * @details     返回当前语言的字符串
 */
const char *MultStr_GetS(const MultStr_Def *multStr)
{
    if(multStr == NULL) {
        return "";
    }
    switch(LANGUAGE_SET) {
        case LANGUAGE_CH: {
            return multStr->strCH;
        }
        case LANGUAGE_EN: {
            return multStr->strEN;
        }
        case LANGUAGE_DE: {
            return multStr->strDE;
        }
        default: {
            return "unknow";
        }
    }
}




VOID_MULTSTR(mStr_Root) = {"root", "root", "root"};

VOID_MULTSTR(mStr_Home) = {"主页", "Home", "Startseite"};
VOID_MULTSTR(mStr_Home_Switch) = {"切换主页", "Switch", "Schalter"};
VOID_MULTSTR(mStr_List) = {"列表模式", "List", "Liste"};
VOID_MULTSTR(mStr_Delayer) = {"延时器", "Delayer", "Verzögerer"};

VOID_MULTSTR(mStr_Menu) = {"菜单", "Menu", "Menü"};
VOID_MULTSTR(mStr_OutOption) = {"输出设置", "OutOption", "OutOption"};
VOID_MULTSTR(mStr_Setting) = {"系统设置", "Setting", "Einstellung"};
VOID_MULTSTR(mStr_Monitor) = {"监测器", "Monitor", "Monitor"};


VOID_MULTSTR(mStr_BatteryTester) = {"电池测试", "BattTest", "BattTest"};
VOID_MULTSTR(mStr_Battest_option) = {"基础设置", "Option", "Option"};
VOID_MULTSTR(mStr_Battest_lab_Current) = {"当前组", "Current", "Aktuell"};
VOID_MULTSTR(mStr_Battest_lab_Loop) = {"已循环", "Looped", "Schleife"};
VOID_MULTSTR(mStr_Battest_lab_Status) = {"状态", "State", "Staat"};
VOID_MULTSTR(mStr_Battest_lab_Start) = {"起始组", "Start", "Start"};
VOID_MULTSTR(mStr_Battest_lab_Groups) = {"总组数", "Groups", "Gruppen"};
VOID_MULTSTR(mStr_Battest_lab_Cycles) = {"循环数", "Cycles", "Zyklen"};
VOID_MULTSTR(mStr_Battest_lab_FileName) = {"文件名", "FileName", "DateiName"};


VOID_MULTSTR(mStr_Battest_lab_TrigTime) = {"触发时间", "TrigTime", "TrigTime"};

VOID_MULTSTR(mStr_Battest_edit) = {"编辑", "Edit", "bearbeiten"};
VOID_MULTSTR(mStr_Battest_No) = {"No", "No", "Nein"};
VOID_MULTSTR(mStr_Battest_Voltage) = {"电压(V)", "Volt(V)", "Volt(V)"};
VOID_MULTSTR(mStr_Battest_Current) = {"电流(A)", "Curr(A)", "Curr(A)"};
VOID_MULTSTR(mStr_Battest_keepT) = {"时间(s)", "kT(s)", "kT(s)"};
VOID_MULTSTR(mStr_Battest_Protect) = {"保护设置", "Protect", "Protect"};
VOID_MULTSTR(mStr_Battest_Protect_Logic) = {"逻辑", "Logic", "Logik"};

VOID_MULTSTR(mStr_Battest_Protect_Param_0) = {"参数0", "Param 0", "Param 0"};
VOID_MULTSTR(mStr_Battest_Protect_Param_1) = {"参数1", "Param 1", "Param 1"};
VOID_MULTSTR(mStr_Battest_Protect_Param_2) = {"参数2", "Param 2", "Param 2"};
VOID_MULTSTR(mStr_Battest_Protect_Param_3) = {"参数3", "Param 3", "Param 3"};
VOID_MULTSTR(mStr_Battest_Protect_Logic_1) = {"逻辑1", "Logic 1", "Logik 1"};
VOID_MULTSTR(mStr_Battest_Protect_Logic_2) = {"逻辑2", "Logic 2", "Logik 2"};
VOID_MULTSTR(mStr_Battest_Protect_Logic_3) = {"逻辑3", "Logic 3", "Logik 3"};

VOID_MULTSTR(mStr_Battest_Logic_OR) = {" or ", " or ", " or "};
VOID_MULTSTR(mStr_Battest_Logic_AND) = {" and ", " and ", " and "};

VOID_MULTSTR(mStr_Battest_MORE_VOLT) = {"Vo>", "Vo>", "Vo>"};
VOID_MULTSTR(mStr_Battest_LESS_VOLT) = {"Vo<", "Vo<", "Vo<"};
VOID_MULTSTR(mStr_Battest_MORE_CURR) = {"Io>", "Io>", "Io>"};
VOID_MULTSTR(mStr_Battest_LESS_CURR) = {"Io<", "Io<", "Io<"};
VOID_MULTSTR(mStr_Battest_MORE_POWER) = {"Po>", "Po>", "Po>"};
VOID_MULTSTR(mStr_Battest_LESS_POWER) = {"Po<", "Po<", "Po<"};
VOID_MULTSTR(mStr_Battest_MORE_DVM) = {"DVM>", "DVM>", "DVM>"};
VOID_MULTSTR(mStr_Battest_LESS_DVM) = {"DVM<", "DVM<", "DVM<"};
VOID_MULTSTR(mStr_Battest_None_Protect) = {"None", "None", "Keine"};

VOID_MULTSTR(mStr_Battest_manage) = {"管理", "Manage", "Verwalt."};

VOID_MULTSTR(mStr_Group) = {"用户组", "Group", "Gruppe"};


VOID_MULTSTR(mStr_PageUp) = {"", "", ""};
VOID_MULTSTR(mStr_PageDown) = {"", "", ""};

VOID_MULTSTR(mStr_Up) = {"↑", "↑", "↑",};
VOID_MULTSTR(mStr_Down) = {"↓", "↓", "↓",};

VOID_MULTSTR(mStr_Left) = {"<", "<", "<"};
VOID_MULTSTR(mStr_Right) = {">", ">", ">"};

VOID_MULTSTR(mStr_Enter) = {"确定", "Enter", "Enter"};
VOID_MULTSTR(mStr_Return) = {"返回", "Return", "Rückkehr"};

VOID_MULTSTR(mStr_Start) = {"启动", "Start", "Start"};
VOID_MULTSTR(mStr_Stop) = {"停止", "Stop", "Stopp"};
VOID_MULTSTR(mStr_Contiune) = {"继续", "contiune", "Weiter"};
VOID_MULTSTR(mStr_Pause) = {"暂停", "Pause", "Pause"};

VOID_MULTSTR(mStr_State_Stopped) = {"已停止", "Stopped", "Gestoppt"};
VOID_MULTSTR(mStr_State_Running) = {"运行中", "Running", "Laufen"};
VOID_MULTSTR(mStr_State_Completed) = {"已完成", "Completed", "Abgeschlossen"};
VOID_MULTSTR(mStr_State_Paused) = {"已暂停", "Paused", "Pausiert"};

VOID_MULTSTR(mStr_save) = {"保存", "Save", "Save"};
VOID_MULTSTR(mStr_load) = {"加载", "Load", "Laden"};
VOID_MULTSTR(mStr_saveAs) = {"另存为", "SaveAs", "SaveAs"};
VOID_MULTSTR(mStr_backspace) = {"BackSpace", "BackSpace", "BackSpace"};
VOID_MULTSTR(mStr_rename) = {"重命名", "Rename", "Rename"};
VOID_MULTSTR(mStr_delete) = {"删除", "Delete", "Delete"};

VOID_MULTSTR(mStr_save_Flash) = {"内部保存", "Save Flash", "Save Flash"};
VOID_MULTSTR(mStr_save_UDisk) = {"外部保存", "Save USB", "Save USB"};

VOID_MULTSTR(mStr_home_Set) = {"设置", "Set", "Einstellung"};
VOID_MULTSTR(mStr_home_Limit) = {"限制", "Limit", "Grenze"};
VOID_MULTSTR(mStr_home_TimeSet) = {"定时", "Timer", "Timer"};
VOID_MULTSTR(mStr_home_OutVol) = {"电压:", "Voltage:", "Spannung:"};
VOID_MULTSTR(mStr_home_OutCur) = {"电流:", "Current:", "Strom:"};
VOID_MULTSTR(mStr_home_OutPower) = {"功率:", "Power:", "Leistung:"};
VOID_MULTSTR(mStr_home_DVM) = {"DVM:", "DVM:", "DVM:"};
VOID_MULTSTR(mStr_home_OutState) = {"状态:", "State:", "Staat:"};
VOID_MULTSTR(mStr_home_Out_OnOff) = {"ON/OFF", "ON/OFF", "EIN/AUS"};

VOID_MULTSTR(mStr_home_VSet) = {"电压", "Voltage", "Spannung"};
VOID_MULTSTR(mStr_home_ISet) = {"电流", "Current", "Strom"};
VOID_MULTSTR(mStr_home_Vlimit) = {"限压", "OVP", "OVP"};
VOID_MULTSTR(mStr_home_Ilimit) = {"限流", "OCP", "OCP"};
VOID_MULTSTR(mStr_home_TimeOff) = {"定时关闭", "Timer", "Timer"};


VOID_MULTSTR(mStr_InputFileName_Title) = {"输入文件名:", "FileName:", "Dateiname:"};
VOID_MULTSTR(mStr_CalibPasswd_Title) = {"请输入校准密码:", "Input Calib Passwd:", "passwort eingeben:"};
VOID_MULTSTR(mStr_Calib_Enter_Tips) = {"进入校准模式", "Enter Calib Mode", "Kalibriermodus aufrufen"};
VOID_MULTSTR(mStr_CalibVol_Title) = {"校准电压:", "Calib Voltage:", "Kalibrier Spannung:"};
VOID_MULTSTR(mStr_CalibAmp_Title) = {"校准电流:", "Calib Current:", "Kalibrierter Strom:"};
VOID_MULTSTR(mStr_CalibDVM_Title) = {"校准DVM:", "Calib DVM:", "Kalib DVM:"};


VOID_MULTSTR(mStr_Preset) = {"预设值", "Preset", "Preset"};
VOID_MULTSTR(mStr_Preset_edit) = {"编辑", "Edit", "bearbeiten"};

VOID_MULTSTR(mStr_Preset_No) = {"No", "No", "Nein"};
VOID_MULTSTR(mStr_Preset_Vol) = {"电压(V)", "Volt(V)", "Volt(V)"};
VOID_MULTSTR(mStr_Preset_Cur) = {"电流(A)", "Curr(A)", "Curr(A)"};
VOID_MULTSTR(mStr_Preset_OVP) = {"限压(V)", "OVP(V)", "OVP(V)"};
VOID_MULTSTR(mStr_Preset_OCP) = {"限流(A)", "OCP(A)", "OCP(A)"};
VOID_MULTSTR(mStr_Preset_TimeOff) = {"定时关闭(s)", "TimeOff(s)", "TimeOff(s)"};

VOID_MULTSTR(mStr_Upper) = {"大写", "Upper", "Obere"};
VOID_MULTSTR(mStr_Lower) = {"小写", "Lower", "Unter"};
VOID_MULTSTR(mStr_Number) = {"数字", "Number", "Nummer"};



VOID_MULTSTR(mStr_list_option) = {"基础设置", "Option", "Option"};
VOID_MULTSTR(mStr_list_lab_Current) = {"当前组", "Current", "Strom"};
VOID_MULTSTR(mStr_list_lab_Loop) = {"已循环", "Looped", "Schleife"};
VOID_MULTSTR(mStr_list_lab_Status) = {"状态", "State", "Staat"};
VOID_MULTSTR(mStr_list_lab_Start) = {"起始组", "Start", "Start"};
VOID_MULTSTR(mStr_list_lab_Groups) = {"总组数", "Groups", "Gruppen"};
VOID_MULTSTR(mStr_list_lab_Cycles) = {"循环数", "Cycles", "Zyklen"};
VOID_MULTSTR(mStr_list_lab_EndState) = {"终止态", "EndState", "EndState"};
VOID_MULTSTR(mStr_list_lab_ONOFF) = {"开启/停止", "ON/OFF", "EIN/AUS"};

VOID_MULTSTR(mStr_list_edit) = {"编辑", "Edit", "Bearbeiten"};
VOID_MULTSTR(mStr_list_No) = {"No", "No", "Nein"};
VOID_MULTSTR(mStr_list_Voltage) = {"电压(V)", "Volt(V)", "Volt(V)"};
VOID_MULTSTR(mStr_list_Current) = {"电流(A)", "Curr(A)", "Curr(A)"};
VOID_MULTSTR(mStr_list_keepT) = {"时间(s)", "kT(s)", "kT(s)"};

//List管理页面
VOID_MULTSTR(mStr_list_manage) = {"管理", "Manage", "Verwaltung"};

//List模板
VOID_MULTSTR(mStr_list_temp) = {"模板", "Template", "Vorlage"};
VOID_MULTSTR(mStr_list_temp_Object) = {"编辑对象", "Object", "Objekt"};
VOID_MULTSTR(mStr_list_temp_Voltage) = {"电压", "Volt", "Spannung"};
VOID_MULTSTR(mStr_list_temp_Current) = {"电流", "Curr", "Strom"};

VOID_MULTSTR(mStr_list_temp_Type) = {"类型", "Type", "Typ"};
VOID_MULTSTR(mStr_list_temp_Sin) = {"正弦波", "Sin", "Sinus"};
VOID_MULTSTR(mStr_list_temp_Pluse) = {"脉冲波", "Pluse", "Puls"};
VOID_MULTSTR(mStr_list_temp_Ramp) = {"斜波", "Ramp", "Rampe"};
VOID_MULTSTR(mStr_list_temp_Stair_Up) = {"阶梯上升", "StairUp", "StairUp"};
VOID_MULTSTR(mStr_list_temp_Stair_Down) = {"阶梯下降", "StairDn", "StairDn"};
VOID_MULTSTR(mStr_list_temp_Stair_UD) = {"阶梯上下", "StairUpDn", "StairUpDn"};
VOID_MULTSTR(mStr_list_temp_exp_Up) = {"指数上升", "Exp Rise", "Exp-Anstieg"};
VOID_MULTSTR(mStr_list_temp_exp_Down) = {"指数下降", "Exp Fall", "Exp Fall"};

VOID_MULTSTR(mStr_list_temp_Edit) = {"编辑", "Edit", "bearbeiten"};
VOID_MULTSTR(mStr_list_temp_Start) = {"起始组", "Start", "Start"};
VOID_MULTSTR(mStr_list_temp_Groups) = {"总组数", "Groups", "Gruppen"};
VOID_MULTSTR(mStr_list_temp_MaxValue) = {"最大值", "MaxVal", "MaxVal"};
VOID_MULTSTR(mStr_list_temp_MinValue) = {"最小值", "MinVal", "MinVal"};
VOID_MULTSTR(mStr_list_temp_Interval) = {"时间间隔", "Interval", "Intervall"};
//特殊
VOID_MULTSTR(mStr_list_temp_Invert) = {"反相", "Invert", "Invertieren"};
VOID_MULTSTR(mStr_list_temp_Period) = {"周期", "Period", "Zeitraum"};         //脉冲波
VOID_MULTSTR(mStr_list_temp_Width) = {"脉宽", "Width", "Breite"};           //脉冲波
VOID_MULTSTR(mStr_list_temp_Symmetry) = {"对称性", "Symmetry", "Symmetrie"};   //斜波
VOID_MULTSTR(mStr_list_temp_AngleRange) = {"角度范围", "Angle", "Winkel"};  //正弦波
VOID_MULTSTR(mStr_list_temp_exp) = {"指数", "exp", "exp"};               //指数

VOID_MULTSTR(mStr_list_temp_Generate) = {"生成", "Generate", "Erzeugen Sie"};



//DelayOut
VOID_MULTSTR(mStr_delay_option) = {"基础设置", "Option", "Option"};
VOID_MULTSTR(mStr_delay_lab_Current) = {"当前组", "Current", "Strom"};
VOID_MULTSTR(mStr_delay_lab_Loop) = {"已循环", "Looped", "Schleife"};
VOID_MULTSTR(mStr_delay_lab_Status) = {"状态", "State", "Staat"};
VOID_MULTSTR(mStr_delay_lab_Start) = {"起始组", "Start", "Start"};
VOID_MULTSTR(mStr_delay_lab_Groups) = {"总组数", "Groups", "Gruppen"};
VOID_MULTSTR(mStr_delay_lab_Cycles) = {"循环数", "Cycles", "Zyklen"};
VOID_MULTSTR(mStr_delay_lab_stopVal) = {"停止", "Stop", "Stopp"};
VOID_MULTSTR(mStr_delay_lab_EndState) = {"终止态", "EndState", "EndState"};
VOID_MULTSTR(mStr_delay_lab_ONOFF) = {"开启/停止", "ON/OFF", "EIN/AUS"};

VOID_MULTSTR(mStr_delay_edit) = {"编辑", "Edit", "Bearbeiten"};
VOID_MULTSTR(mStr_delay_No) = {"No", "No", "Nein"};
VOID_MULTSTR(mStr_delay_State) = {"状态", "State", "Staat"};
VOID_MULTSTR(mStr_delay_dT) = {"时间(s)", "delayT(s)", "delayT(s)"};

VOID_MULTSTR(mStr_delay_manage) = {"管理", "Manage", "Verwaltung"};


VOID_MULTSTR(mStr_delay_temp) = {"模板", "Template", "Vorlage"};
VOID_MULTSTR(mStr_delay_temp_Type) = {"类型", "Type", "Typ"};
VOID_MULTSTR(mStr_delay_temp_Type_State) = {"状态码", "StateCode", "StateCode"};
VOID_MULTSTR(mStr_delay_temp_Type_Fix) = {"时长固定", "FixTime", "FixTime"};
VOID_MULTSTR(mStr_delay_temp_Type_Inc) = {"时长递增", "IncTime", "IncTime"};
VOID_MULTSTR(mStr_delay_temp_Type_Dec) = {"时长递减", "DecTime", "DecTime"};

VOID_MULTSTR(mStr_delay_temp_Start) = {"起始组", "Start", "Start"};
VOID_MULTSTR(mStr_delay_temp_Groups) = {"总组数", "Groups", "Gruppen"};
VOID_MULTSTR(mStr_delay_temp_Code) = {"波形码", "Code", "Code"};
VOID_MULTSTR(mStr_delay_temp_Ton) = {"Ton", "Ton", "Ton"};
VOID_MULTSTR(mStr_delay_temp_Toff) = {"Toff", "Toff", "Toff"};
VOID_MULTSTR(mStr_delay_temp_Tbase) = {"Tbase", "Tbase", "Tbase"};
VOID_MULTSTR(mStr_delay_temp_Tstep) = {"Tstep", "Tstep", "Tstep"};
VOID_MULTSTR(mStr_delay_temp_Generate) = {"生成", "Generate", "Erzeugen"};

#if 1
VOID_MULTSTR(mStr_trigger) = {"触发器", "Trigger"};
VOID_MULTSTR(mStr_trigger_ch) = {"通道", "Channel"};
VOID_MULTSTR(mStr_trigger_mode) = {"模式", "Mode"};
VOID_MULTSTR(mStr_trigger_sign) = {"信号", "Sign"};
VOID_MULTSTR(mStr_trigger_sign_rising) = {"上升沿", "rising"};
VOID_MULTSTR(mStr_trigger_sign_fall) = {"下降沿", "fall"};
VOID_MULTSTR(mStr_trigger_sign_high) = {"高电平", "high"};
VOID_MULTSTR(mStr_trigger_sign_low) = {"低电平", "low"};

VOID_MULTSTR(mStr_trigger_sense) = {"灵敏度", "Sense"};
VOID_MULTSTR(mStr_trigger_sense_high) = {"高", "high"};
VOID_MULTSTR(mStr_trigger_sense_mid) = {"中", "mid"};
VOID_MULTSTR(mStr_trigger_sense_low) = {"低", "low"};

VOID_MULTSTR(mStr_trigger_insourse) = {"受控源", "Slave"};
VOID_MULTSTR(mStr_trigger_insourse_ch1) = {"CH1", "CH1"};

VOID_MULTSTR(mStr_trigger_response) = {"响应", "Response"};
VOID_MULTSTR(mStr_trigger_response_on) = {"打开输出", "Out ON"};
VOID_MULTSTR(mStr_trigger_response_off) = {"关闭输出", "OUT OFF"};
VOID_MULTSTR(mStr_trigger_response_alter) = {"翻转输出", "OUT TRI"};
VOID_MULTSTR(mStr_trigger_response_list_on) = {"开启List", "List ON"};
VOID_MULTSTR(mStr_trigger_response_list_off) = {"关闭List", "List OFF"};
VOID_MULTSTR(mStr_trigger_response_delay_on) = {"开启延时器", "Delayer ON"};
VOID_MULTSTR(mStr_trigger_response_delay_off) = {"关闭延时器", "Delayer OFF"};

VOID_MULTSTR(mStr_trigger_source) = {"触发源", "source"};
VOID_MULTSTR(mStr_trigger_source_ch1) = {"CH1", "CH1"};

VOID_MULTSTR(mStr_trigger_condition) = {"条件", "Condition"};
VOID_MULTSTR(mStr_trigger_condition_outon) = {"打开输出", "Out ON"};
VOID_MULTSTR(mStr_trigger_condition_outoff) = {"关闭输出", "Out OFF"};

VOID_MULTSTR(mStr_trigger_polarity) = {"输出极性", "Polarity"};
VOID_MULTSTR(mStr_trigger_polarity_negative) = {"负极性", "Negative"};
VOID_MULTSTR(mStr_trigger_polarity_positive) = {"正极性", "Positive"};
#endif

VOID_MULTSTR(mStr_Monitor_Logic_Title) = {"逻辑设置", "Logic Option", "Logik-Option"};
VOID_MULTSTR(mStr_Monitor_Vol) = {"电压", "Voltage", "Spannung"};
VOID_MULTSTR(mStr_Monitor_Amp) = {"电流", "Current", "Strom"};
VOID_MULTSTR(mStr_Monitor_Wat) = {"功率", "Power", "Strom"};
VOID_MULTSTR(mStr_Monitor_Dvm) = {"DVM", "DVM", "DVM"};
VOID_MULTSTR(mStr_Monitor_Logic) = {"逻辑", "Logic", "Logik"};

VOID_MULTSTR(mStr_Monitor_Trigger_Title) = {"触发设置", "Trigger Option", "Auslöser-Option"};
VOID_MULTSTR(mStr_Monitor_Sensitivity) = {"灵敏度", "Sensitivity", "Empfindlichkeit"};
VOID_MULTSTR(mStr_Monitor_Sensitivity_Low) = {"500ms", "500ms", "500ms"};
VOID_MULTSTR(mStr_Monitor_Sensitivity_Mid) = {"250ms", "250ms", "250ms"};
VOID_MULTSTR(mStr_Monitor_Sensitivity_High) = {"50ms", "50ms", "50ms"};

VOID_MULTSTR(mStr_Monitor_PowerOFF) = {"停止输出", "Power-Off", "Ausschalten"};

VOID_MULTSTR(mStr_Monitor_Beeper) = {"提示音", "Beeper", "Summer"};
VOID_MULTSTR(mStr_Monitor_Tips) = {"提示框", "Tips", "Tipps"};


VOID_MULTSTR(mStr_SR_Mode) = {"斜率模式", "SR Mode", "SR-Modus"};
VOID_MULTSTR(mStr_SR_Title) = {"斜率设置", "SR Edit", "SR Bearbeiten"};
VOID_MULTSTR(mStr_VSR_U) = {"电压上升", "VSR Rising", "VSR Steigend"};
VOID_MULTSTR(mStr_VSR_D) = {"电压下降", "VSR Falling", "VSR fallend"};
VOID_MULTSTR(mStr_ISR_U) = {"电流上升", "ISR Rising", "ISR Aufschwung"};
VOID_MULTSTR(mStr_ISR_D) = {"电流下降", "ISR Falling", "ISR fallend"};
VOID_MULTSTR(mStr_SR_Normal) = {"普通", "Normal", "Normal"};
VOID_MULTSTR(mStr_VSR_Mode) = {"CV斜率", "CV SlewRate", "CV SlewRate"};
VOID_MULTSTR(mStr_ISR_Mode) = {"CC斜率", "CC SlewRate", "CC SlewRate"};


VOID_MULTSTR(mStr_Mode) = {"工作模式", "Mode", "Modus"};
VOID_MULTSTR(mStr_Mode_Normal) = {"Normal", "Normal", "Normal"};
VOID_MULTSTR(mStr_Mode_Ext_V) = {"Ext-V", "Ext-V", "Ext-V"};
VOID_MULTSTR(mStr_Mode_Ext_D) = {"Ext-D", "Ext-D", "Ext-D"};

VOID_MULTSTR(mStr_P_Out) = {"上电输出", "P-Out", "P-Out"};
VOID_MULTSTR(mStr_P_Out_OFF) = {"关闭", "OFF", "AUS"};
VOID_MULTSTR(mStr_P_Out_Keep) = {"保持", "Keep", "Behalten Sie"};

VOID_MULTSTR(mStr_DVM_onoff) = {"电压表", "DVM", "DVM"};


VOID_MULTSTR(mStr_BaseTitle) = {"基础设置", "Base", "Basis"};
VOID_MULTSTR(mStr_Language) = {"Language", "Language", "Language"};
VOID_MULTSTR(mStr_Brightness) = {"背光", "Brightness", "Helligkeit"};
VOID_MULTSTR(mStr_Beeper) = {"蜂鸣器", "Beeper", "Summer"};
VOID_MULTSTR(mStr_PowerDown) = {"掉电检测", "P-Down", "P-Down"};

VOID_MULTSTR(mStr_CommTitle) = {"通讯设置", "COM", "COM"};
VOID_MULTSTR(mStr_Comm_BaudRate) = {"波特率", "BaudRate", "BaudRate"};
VOID_MULTSTR(mStr_Comm_Protocol) = {"通讯协议", "Protocol", "Protokoll"};

VOID_MULTSTR(mStr_Comm_Protocol_SCPI) = {"SCPI", "SCPI", "SCPI"};
VOID_MULTSTR(mStr_Comm_Protocol_MultSCPI) = {"Mult-SCPI", "Mult-SCPI", "Mehrfach-SCPI"};
VOID_MULTSTR(mStr_Comm_Protocol_Modbus) = {"Modbus", "Modbus", "Modbus"};

VOID_MULTSTR(mStr_Comm_Address) = {"通讯地址", "Address", "Adresse"};

VOID_MULTSTR(mStr_NetTitle) = {"网络设置", "NetWork", "NetWork"};
VOID_MULTSTR(mStr_IP) = {"网络地址", "IP Addr", "IP-Adresse"};
VOID_MULTSTR(mStr_Gateway) = {"网关", "Gateway", "Gateway"};
VOID_MULTSTR(mStr_NetMask) = {"子网掩码", "NetMask", "Netzmaske"};
VOID_MULTSTR(mStr_DHCP) = {"DHCP", "DHCP", "DHCP"};


VOID_MULTSTR(mStr_Reboot) = {"重启", "Reboot", "Neustart"};

VOID_MULTSTR(mStr_About) = {"关于本机", "About", "Über"};
VOID_MULTSTR(mStr_About_Model) = {"型号", "Model", "Modell"};
VOID_MULTSTR(mStr_About_SN) = {"序列号", "Serial Number", "Seriennummer"};
VOID_MULTSTR(mStr_About_Boot) = {"启动次数", "Boot Count"};
VOID_MULTSTR(mStr_About_BootVer) = {"引导版本", "Bootloader Ver", "Bootloader Ver"};
VOID_MULTSTR(mStr_About_FirmwVer) = {"固件版本", "Firmware Ver", "Firmware Ver"};

VOID_MULTSTR(mStr_YES) = {"是", "YES", "YES"};
VOID_MULTSTR(mStr_NO) = {"否", "NO", "NO"};

VOID_MULTSTR(mStr_ON) = {"开启", "ON", "ON"};
VOID_MULTSTR(mStr_OFF) = {"关闭", "OFF", "AUS"};

VOID_MULTSTR(mStr_CH) = {"简体中文", "Chinese", "Chinesisch"};
VOID_MULTSTR(mStr_EN) = {"英文", "English", "Englisch"};
VOID_MULTSTR(mStr_DE) = {"德语", "German", "German"};




/* ------------------ 设置备注 -------------------- */

VOID_MULTSTR(mStr_BatTester_tips) = {
    .strCH = "电池测试:可按多组参数逐步运行,同时可设置触发条件进行保护",
    .strEN = "BatteryTester:Running step by step according to multiple sets of parameters, and can set trigger conditions for protection.",
};
VOID_MULTSTR(mStr_Monitor_tips) = {
    .strCH = "监测器:可按设置的检测条件实现:关闭输出、显示提示、发出报警",
    .strEN = "Monitior:According to the set detection conditions: Power-Off, tips, and beeper alarm.",
};
VOID_MULTSTR(mStr_Trigger_tips) = {
    .strCH = "触发器:可按需设置的IO的功能、触发条件、触发行为",
    .strEN = "Trigger:",
};
VOID_MULTSTR(mStr_OutOption_tips) = {
    .strCH = "输出设置:可设置电源工作模式、输出斜率、上电保持等",
    .strEN = "OutOption:Set the power working mode, SlewRate, and Power-Out.",
};
VOID_MULTSTR(mStr_Setting_tips) = {
    .strCH = "系统设置:可设置系统参数、通讯参数以及显示出厂信息",
    .strEN = "Menu:Set system parameters, communication and display information.",
};
VOID_MULTSTR(mStr_Group_tips) = {
    .strCH = "用户组:加载/存储用户输出设置与预设值",
    .strEN = "Group:Load and Store user Settings and presets.",
};


/*
 * @brief       文件操作提示
 * @details
 */
VOID_MULTSTR(mStr_Save_Tips) = {"保存完毕!", "Save OK!", "Gespeichert!"};

VOID_MULTSTR(mStr_NetSave_Tips) = {
    .strCH = "已保存,重启以生效网络设置!",
    .strEN = "Reboot to Apply Network Settings!",
    .strDE = "Reboot to Apply Network Settings!",
};

VOID_MULTSTR(mStr_Load_Tips) = {"加载完毕!", "Load OK!", "Geladet!"};
VOID_MULTSTR(mStr_Delete_Tips) = {"删除完毕!", "Delete OK!", "Gelöscht!"};
VOID_MULTSTR(mStr_FileName_Duplicate_Tips) = {"文件名已重复!", "The file is duplicated!", "Die Datei ist dupliziert!"};

/*
 * @brief       输出设置提示
 * @details
 */
VOID_MULTSTR(mStr_OutSet_MaxVol) = {
    .strCH = "电压设置达到最大值!",
    .strEN = "Over maximum voltage!",
    .strDE = "Über die maximale Spannung!",
};

VOID_MULTSTR(mStr_OutSet_MaxAmp) = {
    .strCH = "电流设置达到最大值!",
    .strEN = "Over maximum current!",
    .strDE = "Über den maximalen Strom!",
};

VOID_MULTSTR(mStr_OutSet_MaxWat) = {
    .strCH = "功率设置达到最大值!",
    .strEN = "Over maximum wattage!",
    .strDE = "Über die maximale Wattzahl hinaus!",
};

VOID_MULTSTR(mStr_OutSet_P_Out) = {
    .strCH = "\"上电保持\"已开启,打开输出!",
    .strEN = "\"P-Out\" is Enable,Turn-ON!",
    .strDE = "\"P-Out\" ist aktiviert, Turn-ON!",
};

/*
 * @brief       List页面操作提示
 * @details
 */
VOID_MULTSTR(mStr_ListSet_MaxkT) = {
    .strCH = "保持时间达到最大值!",
    .strEN = "Over maximum keepTimes!",
    .strDE = "Über maximale KeepTimes!",
};
VOID_MULTSTR(mStr_ListSet_MaxPoint) = {
    .strCH = "点数达到最大值!",
    .strEN = "Over maximum Point!",
    .strDE = "Über Höchstpunktzahl!",
};
VOID_MULTSTR(mStr_ListSet_MaxCycles) = {
    .strCH = "循环次数达到最大值!",
    .strEN = "Over maximum Cycles!",
    .strDE = "Über maximale Zyklen!",
};

VOID_MULTSTR(mStr_ListTemp_InvalidParam) = {
    .strCH = "当前模板无法设置此参数!",
    .strEN = "Invalid parameter!",
    .strDE = "Ungültiger Parameter!",
};
VOID_MULTSTR(mStr_ListTemp_MaxPeriod) = {
    .strCH = "周期设置达到最大值!",
    .strEN = "Over maximum Pulse Period!",
    .strDE = "Über maximale Impulsdauer!",
};


VOID_MULTSTR(mStr_ListTemp_MaxWidth) = {
    .strCH = "脉宽设置达到最大值!",
    .strEN = "Over maximum Pulse Width!",
    .strDE = "Über maximale Impulsbreite!",
};


VOID_MULTSTR(mStr_ListTemp_MaxSymmetry) = {
    .strCH = "斜波对称设置达到最大值!",
    .strEN = "Over maximum Ramp Symmetry!",
    .strDE = "Über maximale Rampensymmetrie!"
};


VOID_MULTSTR(mStr_ListTemp_MaxExp) = {
    .strCH = "指数设置达到最大值!",
    .strEN = "Over maximum Exp!",
    .strDE = "Über maximale Exp!",
};


/*
 * @brief       BatTester页面操作提示
 * @details
 */
VOID_MULTSTR(mStr_BatTester_MaxkT) = {
    .strCH = "保持时间达到最大值!",
    .strEN = "Over maximum keepTimes!",
    .strDE = "Über maximale KeepTimes!",
};
VOID_MULTSTR(mStr_BatTester_MaxPoint) = {
    .strCH = "点数达到最大值!",
    .strEN = "Over maximum Point!",
    .strDE = "Über Höchstpunktzahl!!",
};
VOID_MULTSTR(mStr_BatTester_MaxCycles) = {
    .strCH = "循环次数达到最大值!",
    .strEN = "Over maximum Cycles!",
    .strDE = "Über maximale Zyklen!",
};

/*
 * @brief       Delay页面操作提示
 * @details
 */
VOID_MULTSTR(mStr_DelaySet_MaxdT) = {
    .strCH = "延时设置达到最大值!",
    .strEN = "Over maximum delayTimes!",
};

VOID_MULTSTR(mStr_DelaySet_MaxPoint) = {
    .strCH = "点数达到最大值!",
    .strEN = "Over maximum Point!",
};

VOID_MULTSTR(mStr_DelaySet_MaxCycles) = {
    .strCH = "循环次数达到最大值!",
    .strEN = "Over maximum Cycles!",
};


/*
 * @brief       系统设置
 * @details
 */
VOID_MULTSTR(mStr_Comm_BaudRate_Min) = {
    .strCH = "小于接口最小波特率!",
    .strEN = "Below minimum BaudRate!",
    .strDE = "Unterhalb der minimalen BaudRate!",
};
VOID_MULTSTR(mStr_Comm_BaudRate_Max) = {
    .strCH = "超过接口最大波特率!",
    .strEN = "Over maximum BaudRate!",
    .strDE = "Über maximale BaudRate!",
};

/*
 * @brief       电源保护提示消息
 * @details
 */
VOID_MULTSTR(mStr_Power_OVP) = {
    .strCH = "过压保护,关闭输出!",
    .strEN = "Over-Voltage,Power-Off!",
    .strDE = "Überspannung, Ausschalten!",
};
VOID_MULTSTR(mStr_Power_OCP) = {
    .strCH = "过流保护,关闭输出!",
    .strEN = "Over-Current,Power-Off!",
    .strDE = "Überstrom, Ausschalten!",
};
VOID_MULTSTR(mStr_Power_OTP) = {
    .strCH = "过温保护,关闭输出!",
    .strEN = "Over-Temperature,Power-Off!",
    .strDE = "Übertemperatur, Abschaltung!",
};
VOID_MULTSTR(mStr_Power_OTP_Recovered) = {
    .strCH = "过温保护已解除!",
    .strEN = "The Over-Temperature has been removed!",
    .strDE = "Die Überhitzung wurde beseitigt!",
};
VOID_MULTSTR(mStr_Power_Over_Offset) = {
    .strCH = "补偿电压过大,关闭输出!",
    .strEN = "Over V-Offset,Power-Off!",
    .strDE = "Über V-Offset, Ausschalten!",
};
VOID_MULTSTR(mStr_Power_TimeOut) = {
    .strCH = "倒计时结束,关闭电源输出!",
    .strEN = "Timer TimeOut,Power-Off!",
    .strDE = "Timer TimeOut,Power-Off!",
};

/*
 * @brief       List运行消息
 * @details
 */
VOID_MULTSTR(mStr_List_Completed) = {
    .strCH = "列表模式运行完毕!",
    .strEN = "List is Completed!",
    .strDE = "Die Liste ist vollständig!",
};
VOID_MULTSTR(mStr_List_Temp_Generted) = {
    .strCH = "列表模板生成完毕!",
    .strEN = "List Temp is Generted!",
    .strDE = "Liste Temp ist generted!",
};


/*
 * @brief       BatteryTester运行消息
 * @details
 */
VOID_MULTSTR(mStr_BatTester_Completed) = {
    .strCH = "电池测试运行完毕!",
    .strEN = "Battery Tester is Completed!",
    .strDE = "Der Batterietester ist fertiggestellt!",
};


/*
 * @brief       Delay运行消息
 * @details
 */
VOID_MULTSTR(mStr_Delay_Completed) = {
    .strCH = "延时器模式运行完毕!",
    .strEN = "Delayer is Completed!",
    .strDE = "Delayer is Completed!",
};
VOID_MULTSTR(mStr_Delay_Temp_Generted) = {
    .strCH = "延时器模板生成完毕!",
    .strEN = "Delayer Temp is Generted!",
    .strDE = "Delayer Temp ist generted!",
};

VOID_MULTSTR(mStr_Delay_Stop_ON) = {
    .strCH = "延时器模式下触发停止,打开输出!",
    .strEN = "Trigger Delayer Stop,Turn ON!",
    .strDE = "Trigger Delayer Stop,Turn ON!",
};
VOID_MULTSTR(mStr_Delay_Stop_OFF) = {
    .strCH = "延时器模式下触发停止,关闭输出!",
    .strEN = "Trigger Delayer Stop,Turn OFF!",
    .strDE = "Trigger Delayer Stop,Turn OFF!",
};
VOID_MULTSTR(mStr_Delay_Stop_Last) = {
    .strCH = "延时器模式下触发停止,保持末态!",
    .strEN = "Trigger Delayer Stop,Hold Last State!",
    .strDE = "Trigger Delayer Stop,Hold Last State!",
};


/* -------------------- 工厂模式 ---------------- */
VOID_MULTSTR(mStr_CalibVol_Completed) = {"电压校准完毕!", "Voltage Calib Completed!", "Voltage Calib Completed!",};
VOID_MULTSTR(mStr_CalibAmp_Completed) = {"电流校准完毕!", "Current Calib Completed!", "Current Calib Completed!",};
VOID_MULTSTR(mStr_CalibDvm_Completed) = {"DVM校准完毕!", "DVM Calib Completed!", "DVM Calib Completed!",};

VOID_MULTSTR(mStr_Calib_Close) = {"校准点太近!", "Calib Point too Close!", "Calib Point too Close!",};
VOID_MULTSTR(mStr_Calib_NullValue) = {"校准点不足!", "校准点不足!", "校准点不足!",};

VOID_MULTSTR(mStr_Calib_Vol_Null) = {"无电压校准数据!", "Null Voltage Calib Data!", "Null Voltage Calib Data!"};
VOID_MULTSTR(mStr_Calib_Cur_Null) = {"无电流校准数据!", "Null Current Calib Data!", "Null Current Calib Data!"};
VOID_MULTSTR(mStr_Calib_DVM_Null) = {"无DVM校准数据!", "Null DVM Calib Data!", "Null DVM Calib Data!"};

VOID_MULTSTR(mStr_DelCalibVol_Completed) = {"删除电压校准点!", "删除电压校准点!", "删除电压校准点!",};
VOID_MULTSTR(mStr_DelCalibAmp_Completed) = {"删除电流校准点!", "删除电流校准点!", "删除电流校准点!",};
VOID_MULTSTR(mStr_DelCalibDvm_Completed) = {"删除DVM校准点!", "删除DVM校准点!", "删除DVM校准点!",};
VOID_MULTSTR(mStr_DelCalibAll_Completed) = {"删除所有校准点!", "删除所有校准点!", "删除所有校准点!",};


/* --------------------- 屏蔽 ------------------- */

VOID_MULTSTR(mStr_power_lock_tips) = {
    .strCH = "键盘已上锁,长按解锁!",
    .strEN = "KeyBoard is Locked,Long Press to UnLock!",
    .strDE = "Tastatur ist gesperrt, zum Entsperren lang drücken!",
};
VOID_MULTSTR(mStr_power_lock_noOperate) = {
    .strCH = "键盘已上锁,不可操作!",
    .strEN = "KeyBoard is Locked,Can't Operate!",
    .strDE = "Tastatur ist gesperrt, kann nicht bedient werden!",
};

VOID_MULTSTR(mStr_list_Pause) = {
    .strCH = "List模式暂停!",
    .strEN = "List is paused !",
    .strDE = "Liste ist angehalten!",
};
VOID_MULTSTR(mStr_list_noset) = {
    .strCH = "List模式下不可设置输出!",
    .strEN = "Can't Set OutPut Under List Mode!",
    .strDE = "Can't Set OutPut Under List Mode!",
};
VOID_MULTSTR(mStr_list_noedit) = {
    .strCH = "List模式下不可编辑参数!",
    .strEN = "Can't Edit Param Under List Mode!",
    .strDE = "Can't Edit Param Under List Mode!",
};
VOID_MULTSTR(mStr_list_noDelay) = {
    .strCH = "List模式下不可开启此功能!",
    .strEN = "Can't Open this function Under List Mode!",
    .strDE = "Can't Open this function Under List Mode!",
};


VOID_MULTSTR(mStr_BatTester_Pause) = {
    .strCH = "电池测试功能暂停!",
    .strEN = "BatTester is paused !",
    .strDE = "BatTester ist pausiert!",
};
VOID_MULTSTR(mStr_BatTester_noset) = {
    .strCH = "电池测试功能模式下不可设置输出!",
    .strEN = "Can't Set OutPut Under BatTester!",
    .strDE = "Can't Set OutPut Under BatTester!",
};
VOID_MULTSTR(mStr_BatTester_noedit) = {
    .strCH = "电池测试功能模式下不可编辑参数!",
    .strEN = "Can't Edit Param Under BatTester!",
    .strDE = "Can't Edit Param Under BatTester!",
};

VOID_MULTSTR(mStr_BatTester_loadFile_noedit) = {
    .strCH = "加载文件模式下,不可编辑参数!",
    .strEN = "Can't Edit Param Under Load File!",
    .strDE = "Can't Edit Param Under Load File!",
};
VOID_MULTSTR(mStr_BatTester_noDelay) = {
    .strCH = "电池测试功能模式下不可开启此功能!",
    .strEN = "Can't Open this function Under BatTester!",
    .strDE = "Can't Open this function Under BatTester!",
};


VOID_MULTSTR(mStr_BatTester_Global_Protect_Trigged_Msg) = {
    .strCH = "电池测试功能全局保护触发!",
    .strEN = "BatTester Global Protect is triggered!",
    .strDE = "BatTester Global Protect is triggered!",
};
VOID_MULTSTR(mStr_BatTester_Protect_Trigged_Msg) = {
    .strCH = "电池测试功能组内保护触发!",
    .strEN = "BatTester Groups Protect is triggered!",
    .strDE = "BatTester Groups Protect is triggered!",
};





VOID_MULTSTR(mStr_delay_halt) = {
    .strCH = "手动关闭,延时器模式停止!",
    .strEN = "Delayer is halted due to manual off!",
    .strDE = "Delayer is halted due to manual off!",
};
VOID_MULTSTR(mStr_delay_noset) = {
    .strCH = "延时器模式下不可设置输出!",
    .strEN = "Can't Set OutPut Under Delayer Mode!",
    .strDE = "Can't Set OutPut Under Delayer Mode!",
};
VOID_MULTSTR(mStr_delay_noedit) = {
    .strCH = "延时器模式下不可编辑参数!",
    .strEN = "Can't Edit Param Under Delayer Mode!",
    .strDE = "Can't Edit Param Under Delayer Mode!",
};
VOID_MULTSTR(mStr_delay_noList) = {
    .strCH = "延时器模式下不可开启此功能!",
    .strEN = "Can't Open this function Under Delayer Mode!",
    .strDE = "Can't Open this function Under Delayer Mode!",
};

VOID_MULTSTR(mStr_ExtC_noSet) = {
    .strCH = "外部控制模式时,此参数/功能不可用!",
    .strEN = "Can't Set Under Ext-C Mode!",
    .strDE = "Can't Set Under Ext-C Mode!",
};

VOID_MULTSTR(mStr_Setting_DHCP_noSet) = {
    .strCH = "DHCP开启时,此参数不可设置!",
    .strEN = "Can't Set Under DHCP is on!",
    .strDE = "Can't Set Under DHCP is on!",
};

VOID_MULTSTR(mStr_SR_mode_noSet) = {
    .strCH = "当前斜率模式下,此参数不可设置!",
    .strEN = "Can't Set Under Current SlewRate Mode!",
    .strDE = "Can't Set Under Current SlewRate Mode!",
};



VOID_MULTSTR(mStr_ScreenShot_OK_Event) = {
    .strCH = "截图成功!",
    .strEN = "Screenshot OK!",
    .strDE = "Screenshot OK!",
};
VOID_MULTSTR(mStr_ScreenShot_Failed_Event) = {
    .strCH = "截图失败!",
    .strEN = "Screenshot Failed!",
    .strDE = "Screenshot Failed!",
};


VOID_MULTSTR(mStr_PowerDown_Event) = {
    .strCH = "AC掉电事件,已保存数据!",
    .strEN = "AC Power-Down,Setting had been Saved!",
    .strDE = "AC Power-Down,Setting had been Saved!",
};
VOID_MULTSTR(mStr_PowerDown_ShutDown) = {
    .strCH = "AC掉电事件,系统关机...",
    .strEN = "AC Power Down Event,Shut Down...",
    .strDE = "AC Power Down Event,Shut Down...",
};

VOID_MULTSTR(mStr_Power_DVM_OverLoad) = {
    .strCH = "DVM电压表电压过高!",
    .strEN = "DVM Input OverLoad!",
    .strDE = "DVM Input OverLoad!",
};

VOID_MULTSTR(mStr_Monitor_ActionMsg) = {
    .strCH = "监测器事件触发!",
    .strEN = "Monitor Event triggered!",
    .strDE = "Monitor Ereignis ausgelöst!",
};

VOID_MULTSTR(mStr_System_WatchDog_Error) = {
    .strCH = "系统看门狗异常重启!",
    .strEN = "WatchDog Reset!",
    .strDE = "WatchDog Reset!",
};


VOID_MULTSTR(mStr_LoadDefault) = {
    .strCH = "重置设置",
    .strEN = "Reset Conf",
    .strDE = "Reset Conf",
};

VOID_MULTSTR(mStr_LoadDefault_Tips) = {
    .strCH = "长按以恢复出厂参数设置!",
    .strEN = "Long-Press to restore Settings!",
    .strDE = "Long-Press to restore Settings!",
};


VOID_MULTSTR(mStr_Exit_extMode_Tips) = {
    .strCH = "手动关闭,退出外部控制模式!",
    .strEN = "Exit the external control mode due to manual off!",
    .strDE = "Exit the external control mode due to manual off!",
};


VOID_MULTSTR(mStr_Web_Submit) = {"提交", "Submit", "Submit"};
VOID_MULTSTR(mStr_Web_SubmitAll) = {"全部提交", "Submit All", "Submit All"};
VOID_MULTSTR(mStr_Web_Refresh) = {"刷新", "Refresh", "Refresh"};
VOID_MULTSTR(mStr_Web_Next) = {"下一页", "Next", "Next"};
VOID_MULTSTR(mStr_Web_Previous) = {"上一页", "Previous", "Previous"};
VOID_MULTSTR(mStr_Web_Operation) = {"操作", "Operation", "Operation"};