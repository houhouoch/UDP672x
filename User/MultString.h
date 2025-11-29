#ifndef _MULT_STRING_H_
#define _MULT_STRING_H_


#include <stdint.h>

//多国语言结构体定义
typedef struct {
    const char *strCH;
    const char *strEN;
    const char *strDE;
} MultStr_Def;

/*
 * @brief       const char* MultStr_GetS(const MultStr_Def* multStr)
 * @details     返回当前语言的字符串
 */
const char *MultStr_GetS(const MultStr_Def *multStr);


#define VOID_MULTSTR(X) const MultStr_Def X

extern VOID_MULTSTR(mStr_Root);

extern VOID_MULTSTR(mStr_Home);
extern VOID_MULTSTR(mStr_Home_Switch);
extern VOID_MULTSTR(mStr_List);
extern VOID_MULTSTR(mStr_Delayer);

extern VOID_MULTSTR(mStr_Menu);
extern VOID_MULTSTR(mStr_OutOption);
extern VOID_MULTSTR(mStr_Setting);
extern VOID_MULTSTR(mStr_Monitor);

extern VOID_MULTSTR(mStr_BatteryTester);
extern VOID_MULTSTR(mStr_Battest_option);
extern VOID_MULTSTR(mStr_Battest_lab_Current);
extern VOID_MULTSTR(mStr_Battest_lab_Loop);
extern VOID_MULTSTR(mStr_Battest_lab_Status);
extern VOID_MULTSTR(mStr_Battest_lab_Start);
extern VOID_MULTSTR(mStr_Battest_lab_Groups);
extern VOID_MULTSTR(mStr_Battest_lab_Cycles);
extern VOID_MULTSTR(mStr_Battest_lab_FileName);

extern VOID_MULTSTR(mStr_Battest_lab_TrigTime);

extern VOID_MULTSTR(mStr_Battest_edit);
extern VOID_MULTSTR(mStr_Battest_No);
extern VOID_MULTSTR(mStr_Battest_Voltage);
extern VOID_MULTSTR(mStr_Battest_Current);
extern VOID_MULTSTR(mStr_Battest_keepT);
extern VOID_MULTSTR(mStr_Battest_Protect);
extern VOID_MULTSTR(mStr_Battest_Protect_Logic);

extern VOID_MULTSTR(mStr_Battest_Protect_Param_0);
extern VOID_MULTSTR(mStr_Battest_Protect_Param_1);
extern VOID_MULTSTR(mStr_Battest_Protect_Param_2);
extern VOID_MULTSTR(mStr_Battest_Protect_Param_3);
extern VOID_MULTSTR(mStr_Battest_Protect_Logic_1);
extern VOID_MULTSTR(mStr_Battest_Protect_Logic_2);
extern VOID_MULTSTR(mStr_Battest_Protect_Logic_3);
extern VOID_MULTSTR(mStr_Battest_Logic_OR);
extern VOID_MULTSTR(mStr_Battest_Logic_AND);

extern VOID_MULTSTR(mStr_Battest_MORE_VOLT);
extern VOID_MULTSTR(mStr_Battest_LESS_VOLT);
extern VOID_MULTSTR(mStr_Battest_MORE_CURR);
extern VOID_MULTSTR(mStr_Battest_LESS_CURR);
extern VOID_MULTSTR(mStr_Battest_MORE_POWER);
extern VOID_MULTSTR(mStr_Battest_LESS_POWER);
extern VOID_MULTSTR(mStr_Battest_MORE_DVM);
extern VOID_MULTSTR(mStr_Battest_LESS_DVM);
extern VOID_MULTSTR(mStr_Battest_None_Protect);

extern VOID_MULTSTR(mStr_Battest_manage);


extern VOID_MULTSTR(mStr_Group);


extern VOID_MULTSTR(mStr_PageUp);
extern VOID_MULTSTR(mStr_PageDown);

extern VOID_MULTSTR(mStr_Up);
extern VOID_MULTSTR(mStr_Down);

extern VOID_MULTSTR(mStr_Left);
extern VOID_MULTSTR(mStr_Right);

extern VOID_MULTSTR(mStr_Enter);
extern VOID_MULTSTR(mStr_Return);

extern VOID_MULTSTR(mStr_Start);
extern VOID_MULTSTR(mStr_Stop);
extern VOID_MULTSTR(mStr_Contiune);
extern VOID_MULTSTR(mStr_Pause);

extern VOID_MULTSTR(mStr_State_Stopped);
extern VOID_MULTSTR(mStr_State_Running);
extern VOID_MULTSTR(mStr_State_Completed);
extern VOID_MULTSTR(mStr_State_Paused);

extern VOID_MULTSTR(mStr_save);
extern VOID_MULTSTR(mStr_load);
extern VOID_MULTSTR(mStr_saveAs);
extern VOID_MULTSTR(mStr_backspace);
extern VOID_MULTSTR(mStr_rename);
extern VOID_MULTSTR(mStr_delete);

extern VOID_MULTSTR(mStr_save_Flash);
extern VOID_MULTSTR(mStr_save_UDisk);

extern VOID_MULTSTR(mStr_home_Set);
extern VOID_MULTSTR(mStr_home_Limit);
extern VOID_MULTSTR(mStr_home_TimeSet);
extern VOID_MULTSTR(mStr_home_OutVol);
extern VOID_MULTSTR(mStr_home_OutCur);
extern VOID_MULTSTR(mStr_home_OutPower);
extern VOID_MULTSTR(mStr_home_DVM);
extern VOID_MULTSTR(mStr_home_OutState);
extern VOID_MULTSTR(mStr_home_Out_OnOff);

extern VOID_MULTSTR(mStr_home_VSet);
extern VOID_MULTSTR(mStr_home_ISet);
extern VOID_MULTSTR(mStr_home_Vlimit);
extern VOID_MULTSTR(mStr_home_Ilimit);
extern VOID_MULTSTR(mStr_home_TimeOff);


extern VOID_MULTSTR(mStr_InputFileName_Title);
extern VOID_MULTSTR(mStr_CalibPasswd_Title);
extern VOID_MULTSTR(mStr_Calib_Enter_Tips);
extern VOID_MULTSTR(mStr_CalibVol_Title);
extern VOID_MULTSTR(mStr_CalibAmp_Title);
extern VOID_MULTSTR(mStr_CalibDVM_Title);


extern VOID_MULTSTR(mStr_Preset);
extern VOID_MULTSTR(mStr_Preset_edit);

extern VOID_MULTSTR(mStr_Preset_No);
extern VOID_MULTSTR(mStr_Preset_Vol);
extern VOID_MULTSTR(mStr_Preset_Cur);
extern VOID_MULTSTR(mStr_Preset_OVP);
extern VOID_MULTSTR(mStr_Preset_OCP);
extern VOID_MULTSTR(mStr_Preset_TimeOff);

extern VOID_MULTSTR(mStr_Upper);
extern VOID_MULTSTR(mStr_Lower);
extern VOID_MULTSTR(mStr_Number);



extern VOID_MULTSTR(mStr_list_option);
extern VOID_MULTSTR(mStr_list_lab_Current);
extern VOID_MULTSTR(mStr_list_lab_Loop);
extern VOID_MULTSTR(mStr_list_lab_Status);
extern VOID_MULTSTR(mStr_list_lab_Start);
extern VOID_MULTSTR(mStr_list_lab_Groups);
extern VOID_MULTSTR(mStr_list_lab_Cycles);
extern VOID_MULTSTR(mStr_list_lab_EndState);
extern VOID_MULTSTR(mStr_list_lab_ONOFF);

extern VOID_MULTSTR(mStr_list_edit);
extern VOID_MULTSTR(mStr_list_No);
extern VOID_MULTSTR(mStr_list_Voltage);
extern VOID_MULTSTR(mStr_list_Current);
extern VOID_MULTSTR(mStr_list_keepT);

//List管理页面
extern VOID_MULTSTR(mStr_list_manage);


//List模板
extern VOID_MULTSTR(mStr_list_temp);
extern VOID_MULTSTR(mStr_list_temp_Object);
extern VOID_MULTSTR(mStr_list_temp_Voltage);
extern VOID_MULTSTR(mStr_list_temp_Current);

extern VOID_MULTSTR(mStr_list_temp_Type);
extern VOID_MULTSTR(mStr_list_temp_Sin);
extern VOID_MULTSTR(mStr_list_temp_Pluse);
extern VOID_MULTSTR(mStr_list_temp_Ramp);
extern VOID_MULTSTR(mStr_list_temp_Stair_Up);
extern VOID_MULTSTR(mStr_list_temp_Stair_Down);
extern VOID_MULTSTR(mStr_list_temp_Stair_UD);
extern VOID_MULTSTR(mStr_list_temp_exp_Up);
extern VOID_MULTSTR(mStr_list_temp_exp_Down);

extern VOID_MULTSTR(mStr_list_temp_Edit);
extern VOID_MULTSTR(mStr_list_temp_Start);
extern VOID_MULTSTR(mStr_list_temp_Groups);
extern VOID_MULTSTR(mStr_list_temp_MaxValue);
extern VOID_MULTSTR(mStr_list_temp_MinValue);
extern VOID_MULTSTR(mStr_list_temp_Interval);
//特殊
extern VOID_MULTSTR(mStr_list_temp_Invert);
extern VOID_MULTSTR(mStr_list_temp_Period);
extern VOID_MULTSTR(mStr_list_temp_Width);
extern VOID_MULTSTR(mStr_list_temp_Symmetry);
extern VOID_MULTSTR(mStr_list_temp_AngleRange);
extern VOID_MULTSTR(mStr_list_temp_exp);

extern VOID_MULTSTR(mStr_list_temp_Generate);



//DelayOut
extern VOID_MULTSTR(mStr_delay_option);
extern VOID_MULTSTR(mStr_delay_lab_Current);
extern VOID_MULTSTR(mStr_delay_lab_Loop);
extern VOID_MULTSTR(mStr_delay_lab_Status);
extern VOID_MULTSTR(mStr_delay_lab_Start);
extern VOID_MULTSTR(mStr_delay_lab_Groups);
extern VOID_MULTSTR(mStr_delay_lab_Cycles);
extern VOID_MULTSTR(mStr_delay_lab_stopVal);
extern VOID_MULTSTR(mStr_delay_lab_EndState);
extern VOID_MULTSTR(mStr_delay_lab_ONOFF);

extern VOID_MULTSTR(mStr_delay_edit);
extern VOID_MULTSTR(mStr_delay_No);
extern VOID_MULTSTR(mStr_delay_State);
extern VOID_MULTSTR(mStr_delay_dT);

extern VOID_MULTSTR(mStr_delay_manage);

extern VOID_MULTSTR(mStr_delay_temp);
extern VOID_MULTSTR(mStr_delay_temp_Type);
extern VOID_MULTSTR(mStr_delay_temp_Type_State);
extern VOID_MULTSTR(mStr_delay_temp_Type_Fix);
extern VOID_MULTSTR(mStr_delay_temp_Type_Inc);
extern VOID_MULTSTR(mStr_delay_temp_Type_Dec);

extern VOID_MULTSTR(mStr_delay_temp_Start);
extern VOID_MULTSTR(mStr_delay_temp_Groups);
extern VOID_MULTSTR(mStr_delay_temp_Code);
extern VOID_MULTSTR(mStr_delay_temp_Ton);
extern VOID_MULTSTR(mStr_delay_temp_Toff);
extern VOID_MULTSTR(mStr_delay_temp_Tbase);
extern VOID_MULTSTR(mStr_delay_temp_Tstep);
extern VOID_MULTSTR(mStr_delay_temp_Generate);


extern VOID_MULTSTR(mStr_trigger);
extern VOID_MULTSTR(mStr_trigger_ch);
extern VOID_MULTSTR(mStr_trigger_mode);
extern VOID_MULTSTR(mStr_trigger_sign);
extern VOID_MULTSTR(mStr_trigger_sign_rising);
extern VOID_MULTSTR(mStr_trigger_sign_fall);
extern VOID_MULTSTR(mStr_trigger_sign_high);
extern VOID_MULTSTR(mStr_trigger_sign_low);

extern VOID_MULTSTR(mStr_trigger_sense);
extern VOID_MULTSTR(mStr_trigger_sense_high);
extern VOID_MULTSTR(mStr_trigger_sense_mid);
extern VOID_MULTSTR(mStr_trigger_sense_low);

extern VOID_MULTSTR(mStr_trigger_insourse);
extern VOID_MULTSTR(mStr_trigger_insourse_ch1);

extern VOID_MULTSTR(mStr_trigger_response);
extern VOID_MULTSTR(mStr_trigger_response_on);
extern VOID_MULTSTR(mStr_trigger_response_off);
extern VOID_MULTSTR(mStr_trigger_response_alter);
extern VOID_MULTSTR(mStr_trigger_response_list_on);
extern VOID_MULTSTR(mStr_trigger_response_list_off);
extern VOID_MULTSTR(mStr_trigger_response_delay_on);
extern VOID_MULTSTR(mStr_trigger_response_delay_off);

extern VOID_MULTSTR(mStr_trigger_source);
extern VOID_MULTSTR(mStr_trigger_source_ch1);

extern VOID_MULTSTR(mStr_trigger_condition);
extern VOID_MULTSTR(mStr_trigger_condition_outon);
extern VOID_MULTSTR(mStr_trigger_condition_outoff);

extern VOID_MULTSTR(mStr_trigger_polarity);
extern VOID_MULTSTR(mStr_trigger_polarity_negative);
extern VOID_MULTSTR(mStr_trigger_polarity_positive);



extern VOID_MULTSTR(mStr_Monitor_Logic_Title);
extern VOID_MULTSTR(mStr_Monitor_Vol);
extern VOID_MULTSTR(mStr_Monitor_Amp);
extern VOID_MULTSTR(mStr_Monitor_Wat);
extern VOID_MULTSTR(mStr_Monitor_Dvm);
extern VOID_MULTSTR(mStr_Monitor_Logic);

extern VOID_MULTSTR(mStr_Monitor_Trigger_Title);
extern VOID_MULTSTR(mStr_Monitor_Sensitivity);
extern VOID_MULTSTR(mStr_Monitor_Sensitivity_Low);
extern VOID_MULTSTR(mStr_Monitor_Sensitivity_Mid);
extern VOID_MULTSTR(mStr_Monitor_Sensitivity_High);
extern VOID_MULTSTR(mStr_Monitor_PowerOFF);

extern VOID_MULTSTR(mStr_Monitor_Beeper);
extern VOID_MULTSTR(mStr_Monitor_Tips);



extern VOID_MULTSTR(mStr_SR_Mode);
extern VOID_MULTSTR(mStr_SR_Title);
extern VOID_MULTSTR(mStr_VSR_U);
extern VOID_MULTSTR(mStr_VSR_D);
extern VOID_MULTSTR(mStr_ISR_U);
extern VOID_MULTSTR(mStr_ISR_D);
extern VOID_MULTSTR(mStr_SR_Normal);
extern VOID_MULTSTR(mStr_VSR_Mode);
extern VOID_MULTSTR(mStr_ISR_High);
extern VOID_MULTSTR(mStr_ISR_Mode);


extern VOID_MULTSTR(mStr_Mode);
extern VOID_MULTSTR(mStr_Mode_Normal);
extern VOID_MULTSTR(mStr_Mode_Ext_V);
extern VOID_MULTSTR(mStr_Mode_Ext_D);

extern VOID_MULTSTR(mStr_P_Out);
extern VOID_MULTSTR(mStr_P_Out_OFF);
extern VOID_MULTSTR(mStr_P_Out_Keep);

extern VOID_MULTSTR(mStr_DVM_onoff);


extern VOID_MULTSTR(mStr_BaseTitle);
extern VOID_MULTSTR(mStr_Language);
extern VOID_MULTSTR(mStr_Brightness);
extern VOID_MULTSTR(mStr_Beeper);
extern VOID_MULTSTR(mStr_PowerDown);

extern VOID_MULTSTR(mStr_CommTitle);
extern VOID_MULTSTR(mStr_Comm_BaudRate);
extern VOID_MULTSTR(mStr_Comm_Protocol);
extern VOID_MULTSTR(mStr_Comm_Protocol_SCPI);
extern VOID_MULTSTR(mStr_Comm_Protocol_MultSCPI);
extern VOID_MULTSTR(mStr_Comm_Protocol_Modbus);

extern VOID_MULTSTR(mStr_Comm_Address);

extern VOID_MULTSTR(mStr_NetTitle);
extern VOID_MULTSTR(mStr_IP);
extern VOID_MULTSTR(mStr_Gateway);
extern VOID_MULTSTR(mStr_NetMask);
extern VOID_MULTSTR(mStr_DHCP);


extern VOID_MULTSTR(mStr_Reboot);

extern VOID_MULTSTR(mStr_About);
extern VOID_MULTSTR(mStr_About_Model);
extern VOID_MULTSTR(mStr_About_SN);
extern VOID_MULTSTR(mStr_About_Boot);
extern VOID_MULTSTR(mStr_About_BootVer);
extern VOID_MULTSTR(mStr_About_FirmwVer);

extern VOID_MULTSTR(mStr_YES);
extern VOID_MULTSTR(mStr_NO);

extern VOID_MULTSTR(mStr_ON);
extern VOID_MULTSTR(mStr_OFF);
extern VOID_MULTSTR(mStr_CH);
extern VOID_MULTSTR(mStr_EN);
extern VOID_MULTSTR(mStr_DE);



/* ------------------ 设置备注 -------------------- */
extern VOID_MULTSTR(mStr_BatTester_tips);
extern VOID_MULTSTR(mStr_Monitor_tips);
extern VOID_MULTSTR(mStr_Trigger_tips);
extern VOID_MULTSTR(mStr_OutOption_tips);
extern VOID_MULTSTR(mStr_Setting_tips);
extern VOID_MULTSTR(mStr_Group_tips);


/* ---------------- 设置提示 ----------------- */
extern VOID_MULTSTR(mStr_Save_Tips);
extern VOID_MULTSTR(mStr_NetSave_Tips);
extern VOID_MULTSTR(mStr_Load_Tips);
extern VOID_MULTSTR(mStr_Delete_Tips);
extern VOID_MULTSTR(mStr_FileName_Duplicate_Tips);

extern VOID_MULTSTR(mStr_OutSet_MaxVol);
extern VOID_MULTSTR(mStr_OutSet_MaxAmp);
extern VOID_MULTSTR(mStr_OutSet_MaxWat);
extern VOID_MULTSTR(mStr_OutSet_P_Out);


/*
 * @brief       List页面操作提示
 * @details
 */
extern VOID_MULTSTR(mStr_ListSet_MaxkT);
extern VOID_MULTSTR(mStr_ListSet_MaxPoint);
extern VOID_MULTSTR(mStr_ListSet_MaxCycles);

extern VOID_MULTSTR(mStr_ListTemp_InvalidParam);

extern VOID_MULTSTR(mStr_ListTemp_MaxPeriod);
extern VOID_MULTSTR(mStr_ListTemp_MaxWidth);
extern VOID_MULTSTR(mStr_ListTemp_MaxSymmetry);
extern VOID_MULTSTR(mStr_ListTemp_MaxExp);

/*
 * @brief       BatTester页面操作提示
 * @details
 */
extern VOID_MULTSTR(mStr_BatTester_MaxkT);
extern VOID_MULTSTR(mStr_BatTester_MaxPoint);
extern VOID_MULTSTR(mStr_BatTester_MaxCycles);

/*
 * @brief       Delay页面操作提示
 * @details
 */
extern VOID_MULTSTR(mStr_DelaySet_MaxdT);
extern VOID_MULTSTR(mStr_DelaySet_MaxPoint);
extern VOID_MULTSTR(mStr_DelaySet_MaxCycles);

/*
 * @brief       系统设置
 * @details
 */
extern VOID_MULTSTR(mStr_Comm_BaudRate_Min);
extern VOID_MULTSTR(mStr_Comm_BaudRate_Max);

/*
 * @brief       电源保护
 * @details
 */
extern VOID_MULTSTR(mStr_Power_OVP);
extern VOID_MULTSTR(mStr_Power_OCP);
extern VOID_MULTSTR(mStr_Power_OTP);
extern VOID_MULTSTR(mStr_Power_OTP_Recovered);
extern VOID_MULTSTR(mStr_Power_TimeOut);
extern VOID_MULTSTR(mStr_Power_Over_Offset);

extern VOID_MULTSTR(mStr_List_Completed);
extern VOID_MULTSTR(mStr_List_Temp_Generted);

extern VOID_MULTSTR(mStr_BatTester_Completed);

extern VOID_MULTSTR(mStr_Delay_Completed);
extern VOID_MULTSTR(mStr_Delay_Temp_Generted);

extern VOID_MULTSTR(mStr_Delay_Stop_ON);
extern VOID_MULTSTR(mStr_Delay_Stop_OFF);
extern VOID_MULTSTR(mStr_Delay_Stop_Last);

/* -------------------- 工厂模式 ---------------- */
extern VOID_MULTSTR(mStr_CalibVol_Completed);
extern VOID_MULTSTR(mStr_CalibAmp_Completed);
extern VOID_MULTSTR(mStr_CalibDvm_Completed);

extern VOID_MULTSTR(mStr_Calib_Close);
extern VOID_MULTSTR(mStr_Calib_NullValue);

extern VOID_MULTSTR(mStr_Calib_Vol_Null);
extern VOID_MULTSTR(mStr_Calib_Cur_Null);
extern VOID_MULTSTR(mStr_Calib_DVM_Null);

extern VOID_MULTSTR(mStr_DelCalibVol_Completed);
extern VOID_MULTSTR(mStr_DelCalibAmp_Completed);
extern VOID_MULTSTR(mStr_DelCalibDvm_Completed);
extern VOID_MULTSTR(mStr_DelCalibAll_Completed);

/* --------------------- 屏蔽 ------------------- */

extern VOID_MULTSTR(mStr_power_lock_tips);
extern VOID_MULTSTR(mStr_power_lock_noOperate);

extern VOID_MULTSTR(mStr_list_Pause);
extern VOID_MULTSTR(mStr_list_noset);
extern VOID_MULTSTR(mStr_list_noedit);
extern VOID_MULTSTR(mStr_list_noDelay);

extern VOID_MULTSTR(mStr_BatTester_Pause);
extern VOID_MULTSTR(mStr_BatTester_noset);
extern VOID_MULTSTR(mStr_BatTester_noedit);
extern VOID_MULTSTR(mStr_BatTester_loadFile_noedit);
extern VOID_MULTSTR(mStr_BatTester_noDelay);
extern VOID_MULTSTR(mStr_BatTester_Global_Protect_Trigged_Msg);
extern VOID_MULTSTR(mStr_BatTester_Protect_Trigged_Msg);

extern VOID_MULTSTR(mStr_delay_halt);
extern VOID_MULTSTR(mStr_delay_noset);
extern VOID_MULTSTR(mStr_delay_noedit);
extern VOID_MULTSTR(mStr_delay_noList);

extern VOID_MULTSTR(mStr_ExtC_noSet);
extern VOID_MULTSTR(mStr_Setting_DHCP_noSet);
extern VOID_MULTSTR(mStr_SR_mode_noSet);

extern VOID_MULTSTR(mStr_ScreenShot_OK_Event);
extern VOID_MULTSTR(mStr_ScreenShot_Failed_Event);

extern VOID_MULTSTR(mStr_PowerDown_Event);
extern VOID_MULTSTR(mStr_PowerDown_ShutDown);

extern VOID_MULTSTR(mStr_Power_DVM_OverLoad);
extern VOID_MULTSTR(mStr_Monitor_ActionMsg);

extern VOID_MULTSTR(mStr_System_WatchDog_Error);


extern VOID_MULTSTR(mStr_LoadDefault);
extern VOID_MULTSTR(mStr_LoadDefault_Tips);

extern VOID_MULTSTR(mStr_Exit_extMode_Tips);

extern VOID_MULTSTR(mStr_Web_Submit);
extern VOID_MULTSTR(mStr_Web_SubmitAll);
extern VOID_MULTSTR(mStr_Web_Refresh);
extern VOID_MULTSTR(mStr_Web_Next);
extern VOID_MULTSTR(mStr_Web_Previous);
extern VOID_MULTSTR(mStr_Web_Operation);
#endif
