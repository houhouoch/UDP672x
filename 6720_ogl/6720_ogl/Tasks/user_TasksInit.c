/* Private includes -----------------------------------------------------------*/
//includes
#include "user_TasksInit.h"
#include "stdio.h"
#include "lvgl.h"
#include "tim.h"
#include "Beep_Device.h"
#include "Button_Device.h"
#include "user_HardwareInitTask.h"
#include "Gui_Task.h"
/* Private typedef -----------------------------------------------------------*/
#include "gui_guider.h"
#include "sd6500.h"
#include "ADC_Task.h"
#include "EEPROM_Device.h"
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Timers --------------------------------------------------------------------*/
osTimerId_t IdleTimerHandle;
/* Tasks ---------------------------------------------------------------------*/
// Hardwares initialization
osThreadId_t HardwareInitTaskHandle;
const osThreadAttr_t HardwareInitTask_attributes = {
  .name = "HardwareInitTask",
  .stack_size = 128 * 10,
  .priority = (osPriority_t) osPriorityHigh3,
};
osThreadId_t GUIHandle;
const osThreadAttr_t GUI_attributes = {
  .name = "GuiTask",
  .stack_size = 128 * 20,
  .priority = (osPriority_t) osPriorityAboveNormal,
};

osThreadId_t RealDataTickHandle;
const osThreadAttr_t RealDataTick_attributes = {
  .name = "RealDataTick",
  .stack_size = 128 * 10,
  .priority = (osPriority_t) osPriorityNormal,
};

//osThreadId_t EEPROMHandle;
//const osThreadAttr_t REEPROM_attributes = {
//  .name = "EEPROM",
//  .stack_size = 128 * 10,
//  .priority = (osPriority_t) osPriorityNormal,
//};

void StartEepromTestTask(void *argument);
/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void User_Tasks_Init(void)
{
     HardwareInitTaskHandle  = osThreadNew(HardwareInitTask, NULL, &HardwareInitTask_attributes);//初始化硬件
     GUIHandle  = osThreadNew(GuiTask, NULL, &GUI_attributes);//LVGL的心跳循环 
     RealDataTickHandle = osThreadNew(SD6500_Task, NULL, &RealDataTick_attributes);//LVGL的心跳循环 
    // EEPROMHandle = osThreadNew(StartEepromTestTask, NULL, &REEPROM_attributes);//LVGL的心跳循环    
}
/* Private function prototypes -----------------------------------------------*/
/**
  * @brief  FreeRTOS Tick Hook, to increase the LVGL tick
  * @param  None
  * @retval None
  */
void TaskTickHook(void)
{
	//to increase the LVGL tick
	lv_tick_inc(1);
	//to increase the timerpage's timer(put in here is to ensure the Real Time)
}


//void StartEepromTestTask(void *argument)
//{
//    for(;;)
//    {
//        uint8_t res = eeprom_SimpleTest();

//        if(res == EEPROM_NO_ERROR)
//        {
//         printf("EEPROM SUCCESSFUL\r\n");   // 比如打印一条 log 或闪烁 LED 表示 OK
//        }
//        else
//        {
//         printf("EEPROM error\r\n");             // 打印错误码，或者进错误处理
//        }

//        vTaskDelay(pdMS_TO_TICKS(1000));
//    }
//}

