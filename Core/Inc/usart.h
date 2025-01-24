/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    usart.h
 * @brief   This file contains all the function prototypes for
 *          the usart.c file
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
#ifndef __USART_H__
#define __USART_H__

#define UART3_RX_MAX_LEN 128

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#undef GLOBAL
#ifdef USART_C
#define GLOBAL
#else
#define GLOBAL extern
#endif

    /* USER CODE BEGIN Includes */

    /* USER CODE END Includes */

    GLOBAL UART_HandleTypeDef huart1;
    GLOBAL uint8_t            uart3_rx_char;
    GLOBAL ring_buffer        log_rx_ringbuffer;
    GLOBAL uint32_t           uart3_rx_buffer[UART3_RX_MAX_LEN];
    GLOBAL UART_HandleTypeDef huart3;
#define LOG_SERIAL_PORT &huart3

    /* USER CODE BEGIN Private defines */

    /* USER CODE END Private defines */

    void MX_USART1_UART_Init( void );
    void MX_USART3_UART_Init( void );

    /* USER CODE BEGIN Prototypes */

    /* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */
