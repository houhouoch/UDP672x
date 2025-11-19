#include "usart.h"
#include "tim.h"
#include "stm32L4xx_it.h"
// user
#include "user_TasksInit.h"
#include "stdio.h"
#include "Button_Device.h"
#include "Beep_Device.h"
#include "core_cm4.h"
#include "stdint.h"
#include "st7789.h"
// ui
#include "events_init.h"
#include "gui_guider.h"
#include "sd6500.h"  
lv_ui guider_ui;

#include "custom.h"//GUI客户代码文件
//gui
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"

#include "gui_custom.h"
// APP SYS setting
#include "SystemSetting.h"

void APP_LVGL(void);

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/**
  * @brief  hardwares init task
  * @param  argument: Not used
  * @retval None
  */
void HardwareInitTask(void *argument)
{         
	while(1)
	{
    vTaskSuspendAll();  
    
    beep_init();   
   beep_Set_Enable(1);
    printf("test on\r\n"); 
    
    system_init();    
    
    //lcd_start
    ST7789_Init();    
    //LVGL start
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    //beep tick 
    HAL_TIM_Base_Start_IT(&htim16);
    //encoder开始
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);  
    // ui
    // LVGL init
   // setup_ui(&guider_ui); 
    xTaskResumeAll();
		vTaskDelete(NULL); 
	}
}

