/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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
#define MCU_LED_Pin GPIO_PIN_1
#define MCU_LED_GPIO_Port GPIOA
#define TEST_LED_Pin GPIO_PIN_2
#define TEST_LED_GPIO_Port GPIOA
#define U2_SPI1_SCN_Pin GPIO_PIN_0
#define U2_SPI1_SCN_GPIO_Port GPIOB
#define U2_DRV_ENN_Pin GPIO_PIN_1
#define U2_DRV_ENN_GPIO_Port GPIOB
#define U2_SWP_DIAG1_Pin GPIO_PIN_11
#define U2_SWP_DIAG1_GPIO_Port GPIOF
#define U2_SWN_DIAG0_Pin GPIO_PIN_12
#define U2_SWN_DIAG0_GPIO_Port GPIOF
#define U2_REFL_DIR_Pin GPIO_PIN_13
#define U2_REFL_DIR_GPIO_Port GPIOF
#define U2_SD_MODE_Pin GPIO_PIN_12
#define U2_SD_MODE_GPIO_Port GPIOB
#define U2_SPI_MODE_Pin GPIO_PIN_13
#define U2_SPI_MODE_GPIO_Port GPIOB
#define SW1_Pin GPIO_PIN_1
#define SW1_GPIO_Port GPIOD
#define U1_SPI_MODE_Pin GPIO_PIN_2
#define U1_SPI_MODE_GPIO_Port GPIOD
#define U1_SD_MODE_Pin GPIO_PIN_3
#define U1_SD_MODE_GPIO_Port GPIOD
#define U1_REFL_DIR_Pin GPIO_PIN_4
#define U1_REFL_DIR_GPIO_Port GPIOD
#define U1_SPI1_SCN_Pin GPIO_PIN_5
#define U1_SPI1_SCN_GPIO_Port GPIOD
#define U1_SWN_DIAG0_Pin GPIO_PIN_11
#define U1_SWN_DIAG0_GPIO_Port GPIOG
#define U1_SWP_DIAG1_Pin GPIO_PIN_12
#define U1_SWP_DIAG1_GPIO_Port GPIOG
#define U1_DRV_ENN_Pin GPIO_PIN_13
#define U1_DRV_ENN_GPIO_Port GPIOG
#define TMC_CLK_Pin GPIO_PIN_6
#define TMC_CLK_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
