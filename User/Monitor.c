#include "Monitor.h"
#include "Interface.h"



void __Action(void)
{
    if(systemInfo.monitor.beep != 0) {
        BEEP_WARRING();
    }
    if(systemInfo.monitor.tips != 0) {
        IF_MsgBox_Warring_Mult(&mStr_Monitor_ActionMsg, NULL);
    }
    switch(systemInfo.monitor.powerOFF) {
        case 1:
            IF_Power_Set_On_Off(0);
            break;
    }
}


uint8_t Monitor_IsRunning(void)
{
    return systemInfo.monitor.enable;
}

void Monitor_Tick(uint8_t ms)
{
    //执行标志,防止重复执行
    static uint8_t actionFlag = 0;
    if(IF_Power_Get_On_Off() == 0) {
        actionFlag = 0;
        return;
    }
    static int16_t waitCount = 0;
    if(systemInfo.monitor.enable == 0) {
        waitCount = 0;
        return ;
    }
    uint8_t vol_flag = 1;
    uint8_t amp_flag = 1;
    uint8_t wat_flag = 1;
    uint8_t dvm_flag = 1;
    if((systemInfo.monitor.vol_monitor == MONITOR_NONE)
            && (systemInfo.monitor.amp_monitor == MONITOR_NONE)
            && (systemInfo.monitor.wat_monitor == MONITOR_NONE)
            && (systemInfo.monitor.dvm_monitor == MONITOR_NONE))
    {
        return ;
    }
    switch(systemInfo.monitor.vol_monitor) {
        case MONITOR_LESS:
            vol_flag = (IF_Power_Read_Vol() < systemInfo.monitor.vol);
            break;
        case MONITOR_MORE:
            vol_flag = (IF_Power_Read_Vol() > systemInfo.monitor.vol);
            break;
    }
    switch(systemInfo.monitor.amp_monitor) {
        case MONITOR_LESS:
            amp_flag = (IF_Power_Read_Amp() < systemInfo.monitor.amp);
            break;
        case MONITOR_MORE:
            amp_flag = (IF_Power_Read_Amp() > systemInfo.monitor.amp);
            break;
    }
    switch(systemInfo.monitor.wat_monitor) {
        case MONITOR_LESS:
            wat_flag = (IF_Power_Read_Wat() < systemInfo.monitor.wat);
            break;
        case MONITOR_MORE:
            wat_flag = (IF_Power_Read_Wat() > systemInfo.monitor.wat);
            break;
    }
    switch(systemInfo.monitor.dvm_monitor) {
        case MONITOR_LESS:
            dvm_flag = (IF_Power_Read_Dvm() < systemInfo.monitor.dvm);
            break;
        case MONITOR_MORE:
            dvm_flag = (IF_Power_Read_Dvm() > systemInfo.monitor.dvm);
            break;
    }
    int16_t triggerCount = 0;
    switch(systemInfo.monitor.sensitivity) {
        case SENSITIVITY_LOW:
            triggerCount = 500;
            break;
        case SENSITIVITY_MID:
            triggerCount = 250;
            break;
        case SENSITIVITY_HIGH:
            triggerCount = 50;
            break;
    }
    uint8_t triggeFlag = 0;
    if(systemInfo.monitor.logic[0] == LOGIC_AND)
    {
        triggeFlag = vol_flag & amp_flag;
    }
    else
    {
        triggeFlag = vol_flag | amp_flag;
    }
    if(systemInfo.monitor.logic[1] == LOGIC_AND)
    {
        triggeFlag = triggeFlag & wat_flag;
    }
    else
    {
        triggeFlag = triggeFlag | wat_flag;
    }
    if(systemInfo.monitor.logic[2] == LOGIC_AND)
    {
        triggeFlag = triggeFlag & dvm_flag;
    }
    else
    {
        triggeFlag = triggeFlag | dvm_flag;
    }
    if(triggeFlag != 0) {
        if(actionFlag == 0) {
            if(waitCount < triggerCount) {
                waitCount += ms;
            } else {
                waitCount = 0;
                //处理
                __Action();
                actionFlag = 1;
            }
        }
    } else {
        waitCount = 0;
    }
}
