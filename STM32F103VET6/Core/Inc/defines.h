/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    defines.h
  * @brief   This file contains all the function prototypes for the gpio.c file
  ******************************************************************************
  * @attention Hoo
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DEFINES_H__
#define __DEFINES_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f1xx_hal_gpio.h"
/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
// GPIO
#define LED_ON	GPIO_PIN_RESET
#define LED_OFF	GPIO_PIN_SET
/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ DEFINES_H__ */
