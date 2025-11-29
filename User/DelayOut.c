#include "Interface.h"
#include "Delay_Interface.h"
#include "DelayOut.h"

DelayOut_InfoDef delayoutInfo = {
    .startpoint = 0,
    .countpoint = DELAYOUT_MAX_COUNT,
    .cycles = 0,
    .state = DELAY_STATE_NULL,
};



#define PROTECT_COUNT 1

static void DelayOut_ProtectTick(void)
{
    DelayOut_Stop_Def *stop = &delayoutInfo.stopCfg;
    if(stop == NULL) {
        return ;
    }
    float value = 0;
    float valueCmp = 0;
    uint8_t flag = 0;
    static uint8_t count = 0;
    //获取比较值
    switch(stop->stop) {
        case DELAY_STOP_NONE:
        {
            return ;
        }
        case DELAY_STOP_LESS_V:
        case DELAY_STOP_MORE_V: {
            value = IF_Power_Read_Vol();
            valueCmp = stop->vol;
        }
        break;
        case DELAY_STOP_LESS_C:
        case DELAY_STOP_MORE_C: {
            value = IF_Power_Read_Amp();
            valueCmp = stop->amp;
        }
        break;
        case DELAY_STOP_LESS_P:
        case DELAY_STOP_MORE_P: {
            value = IF_Power_Read_Wat();
            valueCmp = stop->wat;
        }
        break;
    }
    //比较大小
    switch(stop->stop) {
        case DELAY_STOP_LESS_V:
        case DELAY_STOP_LESS_C:
        case DELAY_STOP_LESS_P: {
            flag = (value > valueCmp);
        }
        break;
        case DELAY_STOP_MORE_V:
        case DELAY_STOP_MORE_C:
        case DELAY_STOP_MORE_P: {
            flag = (value < valueCmp);
        }
        break;
    }
    //执行
    if(flag == 0) {
        count = 0;
    } else {
        if(count < PROTECT_COUNT) {
            count++;
        } else {
            IF_DelayOut_Set_State(DELAY_STATE_STOP);
            //根据保护发送消息
            switch(delayoutInfo.lastState) {
                case DELAY_ENDSTATE_LAST: {
                    IF_MsgBox_Warring_Mult(&mStr_Delay_Stop_Last, NULL);
                }
                break;
                case DELAY_ENDSTATE_OFF: {
                    IF_MsgBox_Warring_Mult(&mStr_Delay_Stop_OFF, NULL);
                }
                break;
                case DELAY_ENDSTATE_ON: {
                    IF_MsgBox_Warring_Mult(&mStr_Delay_Stop_ON, NULL);
                }
                break;
            }
        }
    }
}


/*
 * @brief       void DelayOut_Check(DelayPoint_Def* point)
 * @details     DelayOut数据点检查
 */
void DelayOut_Check(DelayPoint_Def *point)
{
    if(point == NULL) {
        return ;
    }
    point->out &= 0x01;
    //检查时间
    point->dT = MIN(DT_MAX, point->dT);
    point->dT = MAX(DT_MIN, point->dT);
}

/*
 * @brief       uint8_t DelayOut_IsRunning(void)
 * @details     返回Delay是否在运行
 */
uint8_t DelayOut_IsRunning(void)
{
    return ((delayoutInfo.state != DELAY_STATE_STOP)
            && (delayoutInfo.state != DELAY_STATE_NULL));
}

/*
 * @brief       float DelayOut_RemainingTime(void)
 * @details     返回当前点剩余时间
 */
float DelayOut_RemainingTime(void)
{
    return delayoutInfo.points[delayoutInfo.current].dT - delayoutInfo.holdtime;
}

/*
 * @brief       static void DelayOut_StateCheck(void)
 * @details     检测Delay当前状态,并刷新
 */
static void DelayOut_StateCheck(void)
{
    uint8_t newState = DELAY_STATE_NULL;
    if(delayoutInfo.enable != 0) {
        newState = DELAY_STATE_RUNNING;
    } else {
        newState = DELAY_STATE_STOP;
    }
    //状态变化则更新
    static uint8_t lastState = DELAY_STATE_NULL;
    if(lastState != newState) {
        IF_DelayOut_Set_State(newState);
        lastState = newState;
    }
}

float DelayOut_GetStopVal(void)
{
    switch(delayoutInfo.stopCfg.stop) {
        case DELAY_STOP_LESS_V:
        case DELAY_STOP_MORE_V: {
            return delayoutInfo.stopCfg.vol;
        }
        case DELAY_STOP_LESS_C:
        case DELAY_STOP_MORE_C: {
            return delayoutInfo.stopCfg.amp;
        }
        case DELAY_STOP_LESS_P:
        case DELAY_STOP_MORE_P: {
            return delayoutInfo.stopCfg.wat;
        }
    }
    return 0;
}


//Prescaler = 8000 - 1;
//Period = 10000;
void DelayOut_Tick(void)
{
    DelayOut_StateCheck();
    if(delayoutInfo.enable == 0) {
        delayoutInfo.holdtime = 0;
        return;
    }
    if((delayoutInfo.loop == 0) && (delayoutInfo.current == delayoutInfo.startpoint))
    {
        IF_Power_OnOff(delayoutInfo.points[delayoutInfo.current].out);
    }
    float time = delayoutInfo.points[delayoutInfo.current].dT;
    //刷新表格聚焦列
    if(delayoutInfo.holdtime >= (time - 0.001f))    //dT
    {
        //等待时间够了,切换下一个点
        delayoutInfo.holdtime = 0;
        delayoutInfo.current += 1;
        if((delayoutInfo.current >= DELAYOUT_MAX_COUNT)
                || (delayoutInfo.current >= (delayoutInfo.startpoint + delayoutInfo.countpoint)))
        {   //到达结束点
            delayoutInfo.current = delayoutInfo.startpoint;
            delayoutInfo.loop += 1;
            IF_DelayOut_Set_Loop(delayoutInfo.loop);
            if(delayoutInfo.cycles != 0)
            {
                if(delayoutInfo.loop >= delayoutInfo.cycles)
                {   //若到达一定次数,则关闭序列输出
                    IF_DelayOut_Set_State(DELAY_STATE_STOP);
                    IF_MsgBox_Warring_Mult(&mStr_Delay_Completed, NULL);
                    return;
                }
            }
        }
        IF_Power_OnOff(delayoutInfo.points[delayoutInfo.current].out);
    }
    delayoutInfo.holdtime += 0.1f;
    if(IF_Power_Get_On_Off() == 0) {
        DelayOut_ProtectTick();
    }
}
#include "fatfs.h"
#include "usbd_cdc_if.h"
static FRESULT f_readline(
                FIL *fp,    /* Pointer to the file object */
                void *buff, /* Pointer to data buffer */
                UINT btr,   /* Number of bytes to read */
                UINT *br    /* Pointer to number of bytes read */
)
{
    UINT readCount = 0;
    char *pbuff = (char *)buff;
    if((fp == NULL) || (buff == NULL)) {
        return FR_NO_FILE;
    }
    char ch = 0;
    UINT count = 0;
    while((btr > readCount) && (!f_eof(fp)) && (ch != '\n')) {
        ch = 0;
        count = 0;
        FRESULT res = f_read(fp, &ch, 1, &count);
        if((FR_OK == res) && (count == 1))
        {
            *pbuff = ch;
            pbuff++;
            readCount++;
        } else {
            break;
        }
    }
    if(br != NULL) {
        *br = count;
    }
    return FR_OK;
}
uint16_t DelayOut_Load(DelayOut_InfoDef *tempInfo, const char *name)
{
    if(tempInfo == NULL) {
        return 0;
    }
    FIL myFile;
    //打开文件
    if(f_open(&myFile, name, FA_READ) != FR_OK) {
        DelayOut_Save(tempInfo, name);
        if(f_open(&myFile, name, FA_READ) != FR_OK) {
            return 0;
        }
    }
    memset(tempInfo, 0, sizeof(DelayOut_InfoDef));
    UINT bytesread = 0;
    uint16_t pointCount = 0;
    int start, count, cycles, lastState = 0;
    while(1) {
        bytesread = 0;
        char fileBuffer[128] = {0};
        FRESULT fres = f_readline(&myFile, fileBuffer, sizeof(fileBuffer), (void *)&bytesread);
        if((fres == FR_OK) && (bytesread > 0)) {
            //解析数据
            //            printf("%s|\r\n", fileBuffer);
            int no = 0;
            float dT = 0;
            int32_t out = 0;
            uint8_t valibCount = 0;
            valibCount = sscanf(fileBuffer, "start,%d", &start);
            if(valibCount == 1) {
                tempInfo->startpoint = start;
                continue;
            }
            valibCount = sscanf(fileBuffer, "count,%d", &count);
            if(valibCount == 1) {
                tempInfo->countpoint = count;
                continue;
            }
            valibCount = sscanf(fileBuffer, "cycles,%d", &cycles);
            if(valibCount == 1) {
                tempInfo->cycles = cycles;
                continue;
            }
            valibCount = sscanf(fileBuffer, "lastState,%d", &lastState);
            if(valibCount == 1) {
                tempInfo->lastState = lastState;
                continue;
            }
            //
            int stop = 0;
            valibCount = sscanf(fileBuffer, "stopCondition,%d", &stop);
            if(valibCount == 1) {
                tempInfo->stopCfg.stop = stop;
                continue;
            }
            float vol = 0;
            valibCount = sscanf(fileBuffer, "stopVol,%f", &vol);
            if(valibCount == 1) {
                tempInfo->stopCfg.vol = vol;
                continue;
            }
            float amp = 0;
            valibCount = sscanf(fileBuffer, "stopAmp,%f", &amp);
            if(valibCount == 1) {
                tempInfo->stopCfg.amp = amp;
                continue;
            }
            float wat = 0;
            valibCount = sscanf(fileBuffer, "stopWat,%f", &wat);
            if(valibCount == 1) {
                tempInfo->stopCfg.wat = wat;
                continue;
            }
            //
            valibCount = sscanf(fileBuffer, "%d,%d,%f", &no, &out, &dT);
            if(valibCount == 3) {
                if((0 <= no) && (no < DELAYOUT_MAX_COUNT)) {
                    tempInfo->points[no].out = out;
                    tempInfo->points[no].dT = dT;
                    DelayOut_Check(&tempInfo->points[no]);
                    pointCount = no + 1;
                } else {
                    IF_MsgBox_Error("DelayOut Load Error", NULL);
                }
            }
        } else {
            if(strlen(name) < (sizeof(systemInfo.userInfo.fileName_Delayer) - 1)) {
                strcpy(systemInfo.userInfo.fileName_Delayer, name);
                eeprom_UserInfo_RequestSave(0);
            }
            break;
        }
    }
    //关闭文件
    f_close(&myFile);
    return pointCount;
}
uint8_t DelayOut_Save(DelayOut_InfoDef *tempInfo, const char *name)
{
    if(tempInfo == NULL) {
        return 0;
    }
    FIL myFile;
    UINT byteswrite = 0;
    //打开文件
    if(f_open(&myFile, name, FA_CREATE_ALWAYS | FA_WRITE) != FR_OK) {
        return 0;
    }
    //
    printf("%s,%s,%s\r\n", "No", "Out", "dT");
    uint32_t writePoints = sizeof(tempInfo->points) / sizeof(tempInfo->points[0]);
    char buffer[256] = {0};
    uint16_t bufferLen = 0;
    //写入设置参数
    memset(buffer, 0, sizeof(buffer));
    bufferLen = sprintf(buffer, "start,%d\r\n", tempInfo->startpoint);
    f_write(&myFile, buffer, bufferLen, &byteswrite);
    memset(buffer, 0, sizeof(buffer));
    bufferLen = sprintf(buffer, "count,%d\r\n", tempInfo->countpoint);
    f_write(&myFile, buffer, bufferLen, &byteswrite);
    memset(buffer, 0, sizeof(buffer));
    bufferLen = sprintf(buffer, "cycles,%d\r\n", tempInfo->cycles);
    f_write(&myFile, buffer, bufferLen, &byteswrite);
    memset(buffer, 0, sizeof(buffer));
    bufferLen = sprintf(buffer, "lastState,%d\r\n", tempInfo->lastState);
    f_write(&myFile, buffer, bufferLen, &byteswrite);
    //
    bufferLen = sprintf(buffer, "stopCondition,%d\r\n", tempInfo->stopCfg.stop);
    f_write(&myFile, buffer, bufferLen, &byteswrite);
    bufferLen = sprintf(buffer, "stopVol,%f\r\n", tempInfo->stopCfg.vol);
    f_write(&myFile, buffer, bufferLen, &byteswrite);
    bufferLen = sprintf(buffer, "stopAmp,%f\r\n", tempInfo->stopCfg.amp);
    f_write(&myFile, buffer, bufferLen, &byteswrite);
    bufferLen = sprintf(buffer, "stopWat,%f\r\n", tempInfo->stopCfg.wat);
    f_write(&myFile, buffer, bufferLen, &byteswrite);
    //写入点
    memset(buffer, 0, sizeof(buffer));
    bufferLen = sprintf(buffer, "No,State,delayT(s)\r\n");
    f_write(&myFile, buffer, bufferLen, &byteswrite);
    for(uint32_t i = 0; i < writePoints; ++i) {
        byteswrite = 0;
        FRESULT fres = FR_OK;
        memset(buffer, 0, sizeof(buffer));
        bufferLen = sprintf(buffer, "%d,%d,"DELAY_TIME_FORM"\r\n",
                            i,
                            tempInfo->points[i].out,
                            tempInfo->points[i].dT);
        printf("%s", buffer);
        fres = f_write(&myFile, buffer, bufferLen, &byteswrite);
        if(fres != FR_OK) {
            break;
        }
        printf("Write %d Bytes!\r\n", byteswrite);
    }
    f_close(&myFile);
    return 1;
}
void DelayOut_Delete(const char *name)
{
    f_unlink(name);
}
uint8_t DelayOut_Rename(const char *oldname, const char *newname)
{
    FIL readFile;
    FIL writeFile;
    //打开文件
    if(f_open(&readFile, oldname, FA_READ) != FR_OK) {
        return 0;
    }
    if(f_open(&writeFile, newname, FA_CREATE_ALWAYS | FA_WRITE) != FR_OK) {
        return 0;
    }
    for(uint32_t count = 0; count < f_size(&readFile);)
    {
        uint8_t buf[256] = {0};
        UINT bytesread = 0;
        UINT byteswrite = 0;
        if((FR_OK != f_read(&readFile, buf, sizeof(buf), &bytesread)) && (bytesread == 0)) {
            break;
        }
        if((FR_OK != f_write(&writeFile, buf, bytesread, &byteswrite)) && (byteswrite == 0)) {
            break;
        }
        if(bytesread != byteswrite) {
            break;
        } else {
            count += byteswrite;
        }
    }
    f_close(&readFile);
    f_close(&writeFile);
    return 1;
}