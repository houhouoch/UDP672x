#include "Interface.h"
#include "List_Interface.h"
#include "ListOut.h"

ListOut_InfoDef listoutInfo = {
    .startpoint = 0,
    .countpoint = LISTOUT_MAX_COUNT,
    .cycles = 0,
    .state = LIST_STATE_NULL,
};




/*
 * @brief       void ListOut_Check(ListPoint_Def* point)
 * @details     ListOut数据点�?�?
 */
void ListOut_Check(ListPoint_Def *point)
{
    if(point == NULL) {
        return ;
    }
    //检查电�?
    point->vol = MIN(VOL_MAX, point->vol);
    point->vol = MAX(VOL_MIN, point->vol);
    //检查电�?
    float maxamp = WAT_MAX / (point->vol + 0.0001f);
    maxamp = MIN(maxamp, AMP_MAX);
    point->amp = MIN(maxamp, point->amp);
    point->amp = MAX(AMP_MIN, point->amp);
    //检查时�?
    point->kT = MIN(KT_MAX, point->kT);
    point->kT = MAX(KT_MIN, point->kT);
}

/*
 * @brief       uint8_t ListOut_IsRunning(void)
 * @details     返回List�?��在运�?
 */
uint8_t ListOut_IsRunning(void)
{
    return ((listoutInfo.state != LIST_STATE_STOP)
            && (listoutInfo.state != LIST_STATE_NULL));
}

/*
 * @brief       float ListOut_RemainingTime(void)
 * @details     返回当前点剩余时�?
 */
float ListOut_RemainingTime(void)
{
    return listoutInfo.points[listoutInfo.current].kT - listoutInfo.holdtime;
}

/*
 * @brief       static void ListOut_StateCheck(void)
 * @details     检测List当前状�?,并刷�?
 */
static void ListOut_StateCheck(void)
{
    uint8_t newState = LIST_STATE_NULL;
    if(listoutInfo.enable != 0) {
        if(IF_Power_Get_On_Off() == 0) {
            newState = LIST_STATE_PAUSE;
            //        } else {
            //            newState = LIST_STATE_RUNNING;
        }
    } else {
        newState = LIST_STATE_STOP;
    }
    //状态变化则更新
    static uint8_t lastState = LIST_STATE_NULL;
    if(lastState != newState) {
        IF_ListOut_Set_State(newState);
        lastState = newState;
    }
}


//Prescaler = 8000 - 1;
//Period = 10000;
void ListOut_Tick(void)
{
    ListOut_StateCheck();
    if(listoutInfo.enable == 0) {
        listoutInfo.holdtime = 0;
        return;
    }
    if(listoutInfo.state != LIST_STATE_RUNNING) {
        return ;
    }
    //若未开�?,则进�?
    if(IF_Power_Get_On_Off() == 0) {
        return ;
    }
    if((listoutInfo.loop == 0) && (listoutInfo.current == listoutInfo.startpoint)) {
        //设置输出
        IF_ListOut_Set(listoutInfo.points[listoutInfo.current].vol, listoutInfo.points[listoutInfo.current].amp);
    }
    float time = listoutInfo.points[listoutInfo.current].kT;
    //刷新表格聚焦�?
    if(listoutInfo.holdtime >= (time - 0.001f))    //kT
    {
        //等待时间够了,切换下一�?��
        listoutInfo.holdtime = 0;
        listoutInfo.current += 1;
        if((listoutInfo.current >= LISTOUT_MAX_COUNT)
                || (listoutInfo.current >= (listoutInfo.startpoint + listoutInfo.countpoint)))
        {   //到达结束�?
            listoutInfo.current = listoutInfo.startpoint;
            listoutInfo.loop += 1;
            IF_ListOut_Set_Loop(listoutInfo.loop);
            if(listoutInfo.cycles != 0)
            {
                if(listoutInfo.loop >= listoutInfo.cycles)
                {   //若到达一定�?�?,则关�?��列输�?
                    IF_ListOut_Set_State(LIST_STATE_STOP);
                    IF_MsgBox_Warring_Mult(&mStr_List_Completed, NULL);
                    return;
                }
            }
        }
        IF_ListOut_Set(listoutInfo.points[listoutInfo.current].vol, listoutInfo.points[listoutInfo.current].amp);
    }
    listoutInfo.holdtime += 0.1f;
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

uint16_t ListOut_Load(ListOut_InfoDef *tempInfo, const char *name)
{
    if(tempInfo == NULL) {
        return 0;
    }
    FIL myFile;
    if(f_open(&myFile, name, FA_READ) != FR_OK) {
        //若无该文�?,则新�?
        ListOut_Save(tempInfo, name);
        if(f_open(&myFile, name, FA_READ) != FR_OK) {
            return 0;
        }
    }
    memset(tempInfo, 0, sizeof(ListOut_InfoDef));
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
            valibCount = sscanf(fileBuffer, "lastState,%d", &lastState);
            if(valibCount == 1) {
                tempInfo->lastState = lastState;
                continue;
            }
            valibCount = sscanf(fileBuffer, "%d,%f,%f,%f", &no, &vol, &amp, &kT);
            if(valibCount == 4) {
                if((0 <= no) && (no < LISTOUT_MAX_COUNT)) {
                    tempInfo->points[no].vol = vol;
                    tempInfo->points[no].amp = amp;
                    tempInfo->points[no].kT = kT;
                    ListOut_Check(&tempInfo->points[no]);
                    pointCount = no + 1;
                } else {
                    IF_MsgBox_Error("ListOut Load Error", NULL);
                }
                continue;
            }
        } else {
            if(strlen(name) < (sizeof(systemInfo.userInfo.fileName_Listout) - 1)) {
                strcpy(systemInfo.userInfo.fileName_Listout, name);
                eeprom_UserInfo_RequestSave(0);
            }
            break;
        }
    }
    //关闭文件
    f_close(&myFile);
    return pointCount;
}


uint8_t ListOut_Save(ListOut_InfoDef *tempInfo, const char *name)
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
    memset(buffer, 0, sizeof(buffer));
    bufferLen = sprintf(buffer, "lastState,%d\r\n", tempInfo->lastState);
    f_write(&myFile, buffer, bufferLen, &byteswrite);
    //写入�?
    memset(buffer, 0, sizeof(buffer));
    bufferLen = sprintf(buffer, "No,Vol(V),Amp(A),keepT(s)\r\n");
    f_write(&myFile, buffer, bufferLen, &byteswrite);
    for(uint32_t i = 0; i < writePoints; ++i) {
        byteswrite = 0;
        memset(buffer, 0, sizeof(buffer));
        bufferLen = sprintf(buffer, "%d,"VOL_SET_FORM","AMP_SET_FORM","KEEP_TIME_FORM"\r\n",
                            i,
                            tempInfo->points[i].vol,
                            tempInfo->points[i].amp,
                            tempInfo->points[i].kT);
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

void ListOut_Delete(const char *name)
{
    f_unlink(name);
}

uint8_t ListOut_Rename(const char *oldname, const char *newname)
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
