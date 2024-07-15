/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32c0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

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
#define ADC_NO_OF_CHANNELS 4
#define Onboard_LED_Pin GPIO_PIN_9
#define Onboard_LED_GPIO_Port GPIOB
#define B1_Pin GPIO_PIN_2
#define B1_GPIO_Port GPIOA
#define B1_EXTI_IRQn EXTI2_3_IRQn
#define B2_Pin GPIO_PIN_3
#define B2_GPIO_Port GPIOA
#define B2_EXTI_IRQn EXTI2_3_IRQn
#define B3_Pin GPIO_PIN_4
#define B3_GPIO_Port GPIOA
#define B3_EXTI_IRQn EXTI4_15_IRQn
#define B4_Pin GPIO_PIN_5
#define B4_GPIO_Port GPIOA
#define B4_EXTI_IRQn EXTI4_15_IRQn
#define IncA_Pin GPIO_PIN_6
#define IncA_GPIO_Port GPIOA
#define IncA_EXTI_IRQn EXTI4_15_IRQn
#define IncB_Pin GPIO_PIN_7
#define IncB_GPIO_Port GPIOA
#define Out1_Pin GPIO_PIN_2
#define Out1_GPIO_Port GPIOB
#define Out2_Pin GPIO_PIN_8
#define Out2_GPIO_Port GPIOA
#define Out3_Pin GPIO_PIN_9
#define Out3_GPIO_Port GPIOA
#define Out4_Pin GPIO_PIN_6
#define Out4_GPIO_Port GPIOC
#define Out5_Pin GPIO_PIN_10
#define Out5_GPIO_Port GPIOA
#define Out6_Pin GPIO_PIN_11
#define Out6_GPIO_Port GPIOA
#define Poti1_Pin GPIO_PIN_12
#define Poti1_GPIO_Port GPIOA
#define Out8_Pin GPIO_PIN_3
#define Out8_GPIO_Port GPIOB
#define Out7_Pin GPIO_PIN_4
#define Out7_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
