#include "Beep_Device.h"
#include "GPIO_Device.h"
#include "main.h"
//#include "tim.h"
//#include "Task_Manager.h"

#define BEEP_TICK_ms (20)


typedef struct {
    int16_t time[6];
    uint8_t run_i;
    uint8_t reset;
    uint8_t enable;
} BeepInfo_Def;
__IO BeepInfo_Def  beepInfo = {0};

void beep_init(void)
{
    beep_Set_Enable(0);
    BEEP_OFF();
}


void beep_Set_Enable(uint8_t enable)
{
    //    OS_LOCK();
    beepInfo.enable = enable;
    
    //    OS_UNLOCK();
}


void beep_Set(int16_t time0, int16_t time1, int16_t time2)
{
    //    OS_LOCK();
    if(beepInfo.enable == 0)
    {
        BEEP_OFF();
        //        OS_UNLOCK();
        return ;
    }
    beepInfo.reset = 1;
    beepInfo.run_i = 0;
    beepInfo.time[0] = time0;
    beepInfo.time[1] = time1;
    beepInfo.time[2] = time2;
    beepInfo.time[3] = 0;
    BEEP_OFF();
    //    OS_UNLOCK();
}

/*
 * @brief       void beep_Tick(int16_t tickTime)
 * @details     蜂鸣器Tick控制，10ms控制一次 tickTime<=10ms
 */
void beep_Tick(int16_t tickTime)
{
    if(beepInfo.enable == 0) {
        BEEP_OFF();
        return ;
    }
    //    OS_LOCK();
    if(beepInfo.reset == 1)
    {
        BEEP_ON();
      
        beepInfo.reset = 0;
    }
    else
    {
        if(beepInfo.time[beepInfo.run_i] != 0)
        {
            beepInfo.time[beepInfo.run_i] -= tickTime;
            if(beepInfo.time[beepInfo.run_i] <= 0)
            {
                beepInfo.time[beepInfo.run_i] = 0;
                beepInfo.run_i++;
                if((beepInfo.time[beepInfo.run_i] != 0) && (!(beepInfo.run_i & 1)))
                {
                    BEEP_ON();
                } else {
                    BEEP_OFF();
                }
            }
        }
    }
    //    OS_UNLOCK();
}


