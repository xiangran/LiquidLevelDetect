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
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

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
    void Error_Handler( void );
    void init_task( void );

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LEVEL_Pin GPIO_PIN_13
#define LEVEL_GPIO_Port GPIOC
#define CPU_STATUS_Pin GPIO_PIN_14
#define CPU_STATUS_GPIO_Port GPIOC
#define LED_RED_Pin GPIO_PIN_15
#define LED_RED_GPIO_Port GPIOC
#define HEAT_EN_Pin GPIO_PIN_0
#define HEAT_EN_GPIO_Port GPIOA
#define HEAT_FAULT_Pin GPIO_PIN_1
#define HEAT_FAULT_GPIO_Port GPIOA
#define MCU_NTC_Pin GPIO_PIN_0
#define MCU_NTC_GPIO_Port GPIOB
#define STABLE_POINT_Pin GPIO_PIN_1
#define STABLE_POINT_GPIO_Port GPIOB
#define LIQUID_DET_ADC_Pin GPIO_PIN_2
#define LIQUID_DET_ADC_GPIO_Port GPIOB
#define HOST_LVL_DET_CTRL_Pin GPIO_PIN_10
#define HOST_LVL_DET_CTRL_GPIO_Port GPIOB
#define HOST_HEAT_CTRL_Pin GPIO_PIN_11
#define HOST_HEAT_CTRL_GPIO_Port GPIOB
#define AD5160_2_CS GPIO_PIN_12
#define AD5160_2_CS_GPIO_Port GPIOB
#define AD5160_2_WCLK GPIO_PIN_13
#define AD5160_2_WCLK_GPIO_Port GPIOB
#define AD5160_2_SDI GPIO_PIN_15
#define AD5160_2_SDI_GPIO_Port GPIOB
#define LOG_UART_TX_Pin GPIO_PIN_9
#define LOG_UART_TX_GPIO_Port GPIOA
#define LOG_UART_RX_Pin GPIO_PIN_10
#define LOG_UART_RX_GPIO_Port GPIOA
#define AD5160_1_CS GPIO_PIN_15
#define AD5160_1_CS_GPIO_Port GPIOA
#define AD5160_1_WCLK GPIO_PIN_3
#define AD5160_1_WCLK_GPIO_Port GPIOB
#define AD5160_1_SDI GPIO_PIN_5
#define AD5160_1_SDI_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define USE_FULL_ASSERT 1U

    /* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
