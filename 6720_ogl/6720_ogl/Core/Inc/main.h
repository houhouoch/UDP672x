/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ROM_SDA_Pin GPIO_PIN_13
#define ROM_SDA_GPIO_Port GPIOC
#define ROM_SCL_Pin GPIO_PIN_14
#define ROM_SCL_GPIO_Port GPIOC
#define MCU_Noise2_Pin GPIO_PIN_0
#define MCU_Noise2_GPIO_Port GPIOC
#define BEEP_Pin GPIO_PIN_3
#define BEEP_GPIO_Port GPIOC
#define CODER_B_Pin_Pin GPIO_PIN_0
#define CODER_B_Pin_GPIO_Port GPIOA
#define CODER_A_Pin_Pin GPIO_PIN_1
#define CODER_A_Pin_GPIO_Port GPIOA
#define LED_M1_Pin GPIO_PIN_4
#define LED_M1_GPIO_Port GPIOA
#define LCD_SCK_Pin GPIO_PIN_5
#define LCD_SCK_GPIO_Port GPIOA
#define LCD_SDO_Pin GPIO_PIN_6
#define LCD_SDO_GPIO_Port GPIOA
#define LCD_SDA_Pin GPIO_PIN_7
#define LCD_SDA_GPIO_Port GPIOA
#define LCD_RS_Pin GPIO_PIN_4
#define LCD_RS_GPIO_Port GPIOC
#define LCD_CS_Pin GPIO_PIN_5
#define LCD_CS_GPIO_Port GPIOC
#define LCD_RST_Pin GPIO_PIN_0
#define LCD_RST_GPIO_Port GPIOB
#define OUT_ONOFF_Pin GPIO_PIN_1
#define OUT_ONOFF_GPIO_Port GPIOB
#define LED_CC_Pin GPIO_PIN_10
#define LED_CC_GPIO_Port GPIOB
#define LED_CV_Pin GPIO_PIN_11
#define LED_CV_GPIO_Port GPIOB
#define ADC_SCL_Pin GPIO_PIN_12
#define ADC_SCL_GPIO_Port GPIOB
#define LED_M2_Pin GPIO_PIN_13
#define LED_M2_GPIO_Port GPIOB
#define LED_M3_Pin GPIO_PIN_14
#define LED_M3_GPIO_Port GPIOB
#define LED_LOCK_Pin GPIO_PIN_15
#define LED_LOCK_GPIO_Port GPIOB
#define SENSE_Pin GPIO_PIN_6
#define SENSE_GPIO_Port GPIOC
#define VREF_PWM_Pin GPIO_PIN_9
#define VREF_PWM_GPIO_Port GPIOA
#define BACKLIGHT_PWM_Pin GPIO_PIN_10
#define BACKLIGHT_PWM_GPIO_Port GPIOA
#define TEST_OTP_Pin GPIO_PIN_12
#define TEST_OTP_GPIO_Port GPIOA
#define KEY_out1_Pin GPIO_PIN_15
#define KEY_out1_GPIO_Port GPIOA
#define KEY_out2_Pin GPIO_PIN_10
#define KEY_out2_GPIO_Port GPIOC
#define KEY_out3_Pin GPIO_PIN_11
#define KEY_out3_GPIO_Port GPIOC
#define KEY_in1_Pin GPIO_PIN_2
#define KEY_in1_GPIO_Port GPIOD
#define KEY_in2_Pin GPIO_PIN_3
#define KEY_in2_GPIO_Port GPIOB
#define KEY_in3_Pin GPIO_PIN_4
#define KEY_in3_GPIO_Port GPIOB
#define CODER_OK_Pin GPIO_PIN_5
#define CODER_OK_GPIO_Port GPIOB
#define TEST_CC_Pin GPIO_PIN_6
#define TEST_CC_GPIO_Port GPIOB
#define KEY_out4_Pin GPIO_PIN_3
#define KEY_out4_GPIO_Port GPIOH
#define ADC_SDA_Pin GPIO_PIN_8
#define ADC_SDA_GPIO_Port GPIOB
#define LED_ONOFF_Pin GPIO_PIN_9
#define LED_ONOFF_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
