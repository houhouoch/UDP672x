#include "Interface.h"
#include "BatTester_Interface.h"
#include "BatTester.h"

BatTester_InfoDef BatTester = {
    .startpoint = 0,
    .countpoint = BAT_TESTER_MAX_COUNT,
    .cycles = 0,
    .state = BAT_TESTER_STATE_NULL,
};




/*
 * @brief       void BatTester_Check(BatTester_Point_Def* point)
 * @details     BatTester数据点检查
 */
void BatTester_Check(BatTester_Point_Def *point)
{
    if(point == NULL) {
        return ;
    }
    //检查电压
    point->vol = MIN(VOL_MAX, point->vol);
    point->vol = MAX(VOL_MIN, point->vol);
    //检查电流
    float maxamp = WAT_MAX / (point->vol + 0.0001f);
    maxamp = MIN(maxamp, AMP_MAX);
    point->amp = MIN(maxamp, point->amp);
    point->amp = MAX(AMP_MIN, point->amp);
    //检查时间
    point->kT = MIN(KT_MAX, point->kT);
    point->kT = MAX(KT_MIN, point->kT);
}

/*
 * @brief       uint8_t BatTester_IsRunning(void)
 * @details     返回BatTester是否在运行
*/
uint8_t BatTester_IsRunning(void)
{
    return ((BatTester.state != BAT_TESTER_STATE_STOP)
            && (BatTester.state != BAT_TESTER_STATE_NULL)
            && (BatTester.state != BAT_TESTER_STATE_COMPLETED));
}

/*
 * @brief       float BatTester_RemainingTime(void)
 * @details     返回当前点剩余时间
 */
float BatTester_RemainingTime(void)
{
    return BatTester.points[BatTester.current].kT - BatTester.holdtime;
}

/*
 * @brief       static void BatTester_StateCheck(void)
 * @details     检测BatTester当前状态,并刷新
*/
static void BatTester_StateCheck(void)
{
    uint8_t newState = BAT_TESTER_STATE_NULL;
    if(BatTester.enable != 0) {
        if(IF_Power_Get_On_Off() == 0) {
            newState = BAT_TESTER_STATE_PAUSE;
        }
    } else {
        newState = BAT_TESTER_STATE_STOP;
    }
    //状态变化则更新
    static uint8_t lastState = BAT_TESTER_STATE_NULL;
    if(lastState != newState) {
        IF_BatTester_Set_State(newState);
        lastState = newState;
    }
    //    if(BatTester.errorFlag != 0) {
    //        gpio_troggle(Power_ledPin_Lock);
    //    } else {
    //        gpio_set(Power_ledPin_Lock, IF_Power_Get_Lock());
    //    }
}

uint8_t trigFlag[3] = {false};
void BatTester_ProtectTick(float time)
{
    float volt_now = IF_Power_Read_Vol();
    float curr_now = IF_Power_Read_Amp();
    float power_now = IF_Power_Read_Wat();
    float dvm_now = IF_Power_Read_Dvm();
    trigFlag[0] = false;
    trigFlag[1] = false;
    trigFlag[2] = false;
    char debug_str[2][128] = {0};
    for(uint8_t i = 0; i < ARRAY_COUNT(BatTester.stopCfg); ++i) {
        uint8_t trigFlag_temp = true;
        switch(BatTester.stopCfg[i].stop) {
            case __STOP_LESS_V:
            {trigFlag_temp = (BatTester.stopCfg[i].value > volt_now);}
            if(trigFlag_temp) {
                sprintf(debug_str[0], "%s\n[Vo(%0.3f)<%0.3f]", debug_str[0], volt_now, BatTester.stopCfg[i].value);
            }
            break;
            case __STOP_MORE_V:
            {trigFlag_temp = (BatTester.stopCfg[i].value < volt_now);}
            if(trigFlag_temp) {
                sprintf(debug_str[0], "%s\n[Vo(%0.3f)>%0.3f]", debug_str[0], volt_now, BatTester.stopCfg[i].value);
            }
            break;
            case __STOP_LESS_C:
            {trigFlag_temp = (BatTester.stopCfg[i].value > curr_now);}
            if(trigFlag_temp) {
                sprintf(debug_str[0], "%s\n[Io(%0.3f)<%0.3f]", debug_str[0], curr_now, BatTester.stopCfg[i].value);
            }
            break;
            case __STOP_MORE_C:
            {trigFlag_temp = (BatTester.stopCfg[i].value < curr_now);}
            if(trigFlag_temp) {
                sprintf(debug_str[0], "%s\n[Io(%0.3f)>%0.3f]", debug_str[0], curr_now, BatTester.stopCfg[i].value);
            }
            break;
            case __STOP_LESS_P:
            {trigFlag_temp = (BatTester.stopCfg[i].value > power_now);}
            if(trigFlag_temp) {
                sprintf(debug_str[0], "%s\n[Po(%0.3f)<%0.3f]", debug_str[0], power_now, BatTester.stopCfg[i].value);
            }
            break;
            case __STOP_MORE_P:
            {trigFlag_temp = (BatTester.stopCfg[i].value < power_now);}
            if(trigFlag_temp) {
                sprintf(debug_str[0], "%s\n[Po(%0.3f)>%0.3f]", debug_str[0], power_now, BatTester.stopCfg[i].value);
            }
            break;
            case __STOP_LESS_DVM:
            {trigFlag_temp = (BatTester.stopCfg[i].value > dvm_now);}
            if(trigFlag_temp) {
                sprintf(debug_str[0], "%s\n[Dvm(%0.3f)<%0.3f]", debug_str[0], dvm_now, BatTester.stopCfg[i].value);
            }
            break;
            case __STOP_MORE_DVM:
            {trigFlag_temp = (BatTester.stopCfg[i].value < dvm_now);}
            if(trigFlag_temp) {
                sprintf(debug_str[0], "%s\n[Dvm(%0.3f)>%0.3f]", debug_str[0], dvm_now, BatTester.stopCfg[i].value);
            }
            break;
        }
        if(__STOP_NONE != BatTester.stopCfg[i].stop)
        {
            if(i == 0) {
                trigFlag[0] |= trigFlag_temp;
            } else {
                switch(BatTester.stopCfg[i].logic) {
                    case _STOP_LOGIC_AND:
                        trigFlag[0] &= trigFlag_temp;
                        break;
                    case _STOP_LOGIC_OR:
                        trigFlag[0] |= trigFlag_temp;
                        break;
                }
            }
        }
    }
    for(uint8_t i = 0; i < ARRAY_COUNT(BatTester.points[BatTester.current].stopCfg); ++i) {
        uint8_t trigFlag_temp = false;
        switch(BatTester.points[BatTester.current].stopCfg[i].stop) {
            case __STOP_LESS_V:
            {trigFlag_temp = (BatTester.points[BatTester.current].stopCfg[i].value > volt_now);}
            if(trigFlag_temp) {
                sprintf(debug_str[1], "%s\n[Vo(%0.3f)<%0.3f]", debug_str[1], volt_now, BatTester.points[BatTester.current].stopCfg[i].value);
            }
            break;
            case __STOP_MORE_V:
            {trigFlag_temp = (BatTester.points[BatTester.current].stopCfg[i].value < volt_now);}
            if(trigFlag_temp) {
                sprintf(debug_str[1], "%s\n[Vo(%0.3f)>%0.3f]", debug_str[1], volt_now, BatTester.points[BatTester.current].stopCfg[i].value);
            }
            break;
            case __STOP_LESS_C:
            {trigFlag_temp = (BatTester.points[BatTester.current].stopCfg[i].value > curr_now);}
            if(trigFlag_temp) {
                sprintf(debug_str[1], "%s\n[Io(%0.3f)<%0.3f]", debug_str[1], curr_now, BatTester.points[BatTester.current].stopCfg[i].value);
            }
            break;
            case __STOP_MORE_C:
            {trigFlag_temp = (BatTester.points[BatTester.current].stopCfg[i].value < curr_now);}
            if(trigFlag_temp) {
                sprintf(debug_str[1], "%s\n[Io(%0.3f)>%0.3f]", debug_str[1], curr_now, BatTester.points[BatTester.current].stopCfg[i].value);
            }
            break;
            case __STOP_LESS_P:
            {trigFlag_temp = (BatTester.points[BatTester.current].stopCfg[i].value > power_now);}
            if(trigFlag_temp) {
                sprintf(debug_str[1], "%s\n[Po(%0.3f)<%0.3f]", debug_str[1], power_now, BatTester.points[BatTester.current].stopCfg[i].value);
            }
            break;
            case __STOP_MORE_P:
            {trigFlag_temp = (BatTester.points[BatTester.current].stopCfg[i].value < power_now);}
            if(trigFlag_temp) {
                sprintf(debug_str[1], "%s\n[Po(%0.3f)>%0.3f]", debug_str[1], power_now, BatTester.points[BatTester.current].stopCfg[i].value);
            }
            break;
            case __STOP_LESS_DVM:
            {trigFlag_temp = (BatTester.points[BatTester.current].stopCfg[i].value > dvm_now);}
            if(trigFlag_temp) {
                sprintf(debug_str[1], "%s\n[Dvm(%0.3f)<%0.3f]", debug_str[1], dvm_now, BatTester.points[BatTester.current].stopCfg[i].value);
            }
            break;
            case __STOP_MORE_DVM:
            {trigFlag_temp = (BatTester.points[BatTester.current].stopCfg[i].value < dvm_now);}
            if(trigFlag_temp) {
                sprintf(debug_str[1], "%s\n[Dvm(%0.3f)>%0.3f]", debug_str[1], dvm_now, BatTester.points[BatTester.current].stopCfg[i].value);
            }
            break;
        }
        if(i == 0) {
            trigFlag[1] |= trigFlag_temp;
        } else {
            switch(BatTester.points[BatTester.current].stopCfg[i].logic) {
                case _STOP_LOGIC_AND:
                    trigFlag[1] &= trigFlag_temp;
                    break;
                case _STOP_LOGIC_OR:
                    trigFlag[1] |= trigFlag_temp;
                    break;
            }
        }
    }
    trigFlag[2] = trigFlag[0] | trigFlag[1];
    if(trigFlag[2] != false) {
        if(BatTester.trigTime_now < (BatTester.trigTime - 0.001f)) {
            BatTester.trigTime_now += time;
        } else {
            IF_Power_Set_Lock(2);
            IF_Power_Set_On_Off(0);
            IF_BatTester_Set_State(BAT_TESTER_STATE_PAUSE);
            //BatTester.errorFlag = 1;
            if(trigFlag[0] != 0) {
                IF_MsgBox_BatTester_Error_Mult(&mStr_BatTester_Global_Protect_Trigged_Msg, &CurGroup.outset.lock, "%s", debug_str[0]);
            }
            if(trigFlag[1] != 0) {
                IF_MsgBox_BatTester_Error_Mult(&mStr_BatTester_Protect_Trigged_Msg, &CurGroup.outset.lock, "%s", debug_str[1]);
            }
        }
    } else {
        BatTester.trigTime_now = 0;
    }
}


void BatTester_Tick(void)
{
    BatTester_StateCheck();
    if(BatTester.enable == 0) {
        BatTester.trigTime_now = 0;
        BatTester.holdtime = 0;
        return;
    }
    if(BatTester.state != BAT_TESTER_STATE_RUNNING) {
        return ;
    }
    //若未开启,则进入
    if(IF_Power_Get_On_Off() == 0) {
        return ;
    }
    if((BatTester.loop == 0) && (BatTester.current == 0)) {
        //设置输出
        IF_BatTester_Set(BatTester.points[BatTester.current].vol, BatTester.points[BatTester.current].amp);
    }
    float time = BatTester.points[BatTester.current].kT;
    //刷新表格聚焦列
    if(BatTester.holdtime >= (time - 0.001f))    //kT
    {
        //等待时间够了,切换下一个点
        BatTester.holdtime = 0;
        BatTester.current += 1;
        if((BatTester.current >= BAT_TESTER_MAX_COUNT)
                || (BatTester.current >= (BatTester.startpoint + BatTester.countpoint)))
        {   //到达结束点
            BatTester.current = BatTester.startpoint;
            BatTester.loop += 1;
            IF_BatTester_Set_Loop(BatTester.loop);
            if(BatTester.cycles != 0)
            {
                if(BatTester.loop >= BatTester.cycles)
                {   //若到达一定次数,则关闭序列输出
                    IF_BatTester_Set_State(BAT_TESTER_STATE_COMPLETED);
                    IF_MsgBox_BatTester_Pass_Mult(&mStr_BatTester_Completed);
                    return;
                }
            }
        }
        IF_BatTester_Set(BatTester.points[BatTester.current].vol, BatTester.points[BatTester.current].amp);
        IF_BatTester_Set_CurIdx(BatTester.current);
    }
    IF_BatTester_Refresh_RemainTime();
    BatTester.holdtime += 0.1f;
    BatTester_ProtectTick(0.1f);
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

uint16_t BatTester_Load(BatTester_InfoDef *tempInfo, const char *name)
{
    if(tempInfo == NULL) {
        return 0;
    }
    FIL myFile;
    if(f_open(&myFile, name, FA_READ) != FR_OK) {
        //若无该文件,则新建
        BatTester_Save(tempInfo, name);
        if(f_open(&myFile, name, FA_READ) != FR_OK) {
            return 0;
        }
    }
    memset(tempInfo, 0, sizeof(BatTester_InfoDef));
    UINT bytesread = 0;
    uint16_t pointCount = 0;
    int start, count, cycles = 0;
    float trigTime = 0;
    while(1) {
        bytesread = 0;
        char fileBuffer[128] = {0};
        FRESULT fres = f_readline(&myFile, fileBuffer, sizeof(fileBuffer), (void *)&bytesread);
        if((fres == FR_OK) && (bytesread > 0)) {
            //解析数据
            //            printf("%s|\r\n", fileBuffer);
            int no = 0;
            float vol = 0, amp = 0, kT = 0;
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
            valibCount = sscanf(fileBuffer, "trigTime,%f", &trigTime);
            if(valibCount == 1) {
                tempInfo->trigTime = trigTime;
                continue;
            }
            //保护设置
            {
                int idx = 0;
                int stop = 0;
                int logic = 0;
                float value = 0;
                valibCount = sscanf(fileBuffer, "protect[%d],%d,%d,%f", &idx, &stop, &logic, &value);
                if(valibCount == 4) {
                    if((0 <= idx) && (idx < ARRAY_COUNT(BatTester.stopCfg))) {
                        BatTester.stopCfg[idx].stop = stop;
                        BatTester.stopCfg[idx].logic = logic;
                        BatTester.stopCfg[idx].value = value;
                    }
                }
            }
            {
                int stop[2] = {0};
                int logic[2] = {0};
                float value[2] = {0};
                valibCount = sscanf(fileBuffer, "%d,%f,%f,%f,%d,%d,%f,%d,%d,%f", &no, &vol, &amp, &kT,
                                    &stop[0], &logic[0], &value[0], &stop[1], &logic[1], &value[1]);
                if(valibCount == 10) {
                    if((0 <= no) && (no < BAT_TESTER_MAX_COUNT)) {
                        tempInfo->points[no].vol = vol;
                        tempInfo->points[no].amp = amp;
                        tempInfo->points[no].kT = kT;
                        tempInfo->points[no].stopCfg[0].stop = stop[0];
                        tempInfo->points[no].stopCfg[0].logic = logic[0];
                        tempInfo->points[no].stopCfg[0].value = value[0];
                        tempInfo->points[no].stopCfg[1].stop = stop[1];
                        tempInfo->points[no].stopCfg[1].logic = logic[1];
                        tempInfo->points[no].stopCfg[1].value = value[1];
                        BatTester_Check(&tempInfo->points[no]);
                        pointCount++;
                    } else {
                        IF_MsgBox_Error("Battery Tester Load Error", NULL);
                    }
                    continue;
                }
            }
        } else {
            if(strstr(name, "Demo.batt.csv") == NULL) {
                IF_BatTester_Set_Editable(0);
            } else {
                IF_BatTester_Set_Editable(1);
            }
            if(strlen(name) < (sizeof(systemInfo.userInfo.fileName_BatTester) - 1)) {
                strcpy(systemInfo.userInfo.fileName_BatTester, name);
                eeprom_UserInfo_RequestSave(0);
            }
            break;
        }
    }
    //关闭文件
    f_close(&myFile);
    return pointCount;
}


uint8_t BatTester_Save(BatTester_InfoDef *tempInfo, const char *name)
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
    uint32_t writePoints = ARRAY_COUNT(tempInfo->points);
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
    bufferLen = sprintf(buffer, "trigTime,%f\r\n", tempInfo->trigTime);
    f_write(&myFile, buffer, bufferLen, &byteswrite);
    //
    for(uint8_t i = 0; i < ARRAY_COUNT(tempInfo->stopCfg); ++i) {
        bufferLen = sprintf(buffer, "protect[%d],%d,%d,%f\r\n", i, tempInfo->stopCfg[i].stop, tempInfo->stopCfg[i].logic, tempInfo->stopCfg[i].value);
        f_write(&myFile, buffer, bufferLen, &byteswrite);
    }
    //写入点
    memset(buffer, 0, sizeof(buffer));
    bufferLen = sprintf(buffer, "No,Vol(V),Amp(A),keepT(s)\r\n");
    f_write(&myFile, buffer, bufferLen, &byteswrite);
    for(uint32_t i = 0; i < writePoints; ++i) {
        byteswrite = 0;
        memset(buffer, 0, sizeof(buffer));
        bufferLen = sprintf(buffer, "%d,"VOL_SET_FORM","AMP_SET_FORM","KEEP_TIME_FORM",%d,%d,%f,%d,%d,%f\r\n",
                            i,
                            tempInfo->points[i].vol,
                            tempInfo->points[i].amp,
                            tempInfo->points[i].kT,
                            tempInfo->points[i].stopCfg[0].stop,
                            tempInfo->points[i].stopCfg[0].logic,
                            tempInfo->points[i].stopCfg[0].value,
                            tempInfo->points[i].stopCfg[1].stop,
                            tempInfo->points[i].stopCfg[1].logic,
                            tempInfo->points[i].stopCfg[1].value);
        //        printf("%s", buffer);
        FRESULT fres = FR_OK;
        fres = f_write(&myFile, buffer, bufferLen, &byteswrite);
        if(fres != FR_OK) {
            break;
        }
        //        printf("Write %d Bytes!\r\n", byteswrite);
    }
    f_close(&myFile);
    return 1;
}

void BatTester_Delete(const char *name)
{
    f_unlink(name);
}

uint8_t BatTester_Rename(const char *oldname, const char *newname)
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
