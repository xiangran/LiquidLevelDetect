/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    usart.c
 * @brief   This file provides code for the configuration
 *          of the USART instances.
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
/* Includes ------------------------------------------------------------------*/
#define USART_C
#include "app_header.h"
#undef USART_C

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;

/* USART1 init function */

void MX_USART1_UART_Init( void )
{

    /* USER CODE BEGIN USART1_Init 0 */

    /* USER CODE END USART1_Init 0 */

    /* USER CODE BEGIN USART1_Init 1 */

    /* USER CODE END USART1_Init 1 */
    huart1.Instance                    = USART1;
    huart1.Init.BaudRate               = 115200;
    huart1.Init.WordLength             = UART_WORDLENGTH_8B;
    huart1.Init.StopBits               = UART_STOPBITS_1;
    huart1.Init.Parity                 = UART_PARITY_NONE;
    huart1.Init.Mode                   = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl              = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling           = UART_OVERSAMPLING_16;
    huart1.Init.OneBitSampling         = UART_ONE_BIT_SAMPLE_DISABLE;
    huart1.Init.ClockPrescaler         = UART_PRESCALER_DIV1;
    huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if ( HAL_UART_Init( &huart1 ) != HAL_OK )
    {
        Error_Handler();
    }
    if ( HAL_UARTEx_SetTxFifoThreshold( &huart1, UART_TXFIFO_THRESHOLD_1_8 ) != HAL_OK )
    {
        Error_Handler();
    }
    if ( HAL_UARTEx_SetRxFifoThreshold( &huart1, UART_RXFIFO_THRESHOLD_1_8 ) != HAL_OK )
    {
        Error_Handler();
    }
    if ( HAL_UARTEx_DisableFifoMode( &huart1 ) != HAL_OK )
    {
        Error_Handler();
    }
    /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

void HAL_UART_MspInit( UART_HandleTypeDef* uartHandle )
{

    GPIO_InitTypeDef         GPIO_InitStruct = { 0 };
    RCC_PeriphCLKInitTypeDef PeriphClkInit   = { 0 };
    if ( uartHandle->Instance == USART1 )
    {
        /* USER CODE BEGIN USART1_MspInit 0 */

        /* USER CODE END USART1_MspInit 0 */

        /** Initializes the peripherals clocks
         */
        PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
        PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
        if ( HAL_RCCEx_PeriphCLKConfig( &PeriphClkInit ) != HAL_OK )
        {
            Error_Handler();
        }

        /* USART1 clock enable */
        __HAL_RCC_USART1_CLK_ENABLE();

        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**USART1 GPIO Configuration
        PA9     ------> USART1_TX
        PA10     ------> USART1_RX
        */
        GPIO_InitStruct.Pin       = LOG_UART_TX_Pin | LOG_UART_RX_Pin;
        GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull      = GPIO_NOPULL;
        GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
        HAL_GPIO_Init( GPIOA, &GPIO_InitStruct );

        /* USART1 interrupt Init */
        HAL_NVIC_SetPriority( USART1_IRQn, 5, 0 );
        HAL_NVIC_EnableIRQ( USART1_IRQn );
        /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit( UART_HandleTypeDef* uartHandle )
{

    if ( uartHandle->Instance == USART1 )
    {
        /* USER CODE BEGIN USART1_MspDeInit 0 */

        /* USER CODE END USART1_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_USART1_CLK_DISABLE();

        /**USART1 GPIO Configuration
        PA9     ------> USART1_TX
        PA10     ------> USART1_RX
        */
        HAL_GPIO_DeInit( GPIOA, LOG_UART_TX_Pin | LOG_UART_RX_Pin );

        /* USART1 interrupt Deinit */
        HAL_NVIC_DisableIRQ( USART1_IRQn );
        /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/* USER CODE BEGIN 1 */
/**
 * \brief
 * @date 2023-11-29
 * \Author Jackie
 */
void USART_Prepare()
{
    ring_buffer_init( &log_rx_ringbuffer, uart3_rx_buffer, UART3_RX_MAX_LEN );

    if ( HAL_OK != HAL_UART_Receive_IT( &huart3, &uart3_rx_char, 1 ) )
    {
        Error_Handler();
    }
}

/**
 * \brief
 * \param huart
 * @date 2024-01-04
 * \Author Jackie
 */
void HAL_UART_RxCpltCallback( UART_HandleTypeDef* huart )
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if ( huart->Instance == USART3 )
    {
        ring_buffer_save_isr( &log_rx_ringbuffer, uart3_rx_char );
        osThreadFlagsSet( get_shell_task_id(), SHELL_DATA_EVENT );
        HAL_UART_Receive_IT( &huart3, &uart3_rx_char, 1 );
    }

    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
/* USER CODE END 1 */

#if defined( __ICCARM__ )
/**
 * \brief
 * \param handle
 * \param buffer
 * \param size
 * \retval size_t
 * @date 2023-06-26
 * \Author Jackie
 */
size_t __write( int handle, const unsigned char* buffer, size_t size )
{
    if ( buffer == 0 )
    {
        /*
         * This means that we should flush internal buffers.  Since we
         * don't we just return.  (Remember, "handle" == -1 means that all
         * handles should be flushed.)
         */
        return 0;
    }

    /* This template only writes to "standard out" and "standard err",
     * for all other file handles it returns failure. */
    if ( handle != _LLIO_STDOUT && handle != _LLIO_STDERR )
    {
        return _LLIO_ERROR;
    }

    /* Sending in normal mode */
    HAL_UART_Transmit( LOG_SERIAL_PORT, ( uint8_t* ) buffer, size, 0xffffff );
    return size;
}
#elif defined( __GNUC__ )
int _write( int fd, char* ptr, int len )
{
    HAL_UART_Transmit( LOG_SERIAL_PORT, ( uint8_t* ) ptr, len, 0xFFFF );
    return len;
}
#endif