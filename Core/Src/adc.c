/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    adc.c
 * @brief   This file provides code for the configuration
 *          of the ADC instances.
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
#define ADC_C
#include "app_header.h"
#undef ADC_C

/* USER CODE BEGIN 0 */
static uint16_t adc1_dma_buffer[ADC1_CHANNEL_NUM];

/* USER CODE END 0 */

/* ADC1 init function */
void MX_ADC1_Init()
{

    /* USER CODE BEGIN ADC1_Init 0 */

    /* USER CODE END ADC1_Init 0 */

    ADC_MultiModeTypeDef   multimode = { 0 };
    ADC_ChannelConfTypeDef sConfig   = { 0 };

    /* USER CODE BEGIN ADC1_Init 1 */

    /* USER CODE END ADC1_Init 1 */

    /** Common config
     */
    hadc1.Instance                   = ADC1;
    hadc1.Init.ClockPrescaler        = ADC_CLOCK_ASYNC_DIV1;
    hadc1.Init.Resolution            = ADC_RESOLUTION_12B;
    hadc1.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    hadc1.Init.GainCompensation      = 0;
    hadc1.Init.ScanConvMode          = ADC_SCAN_ENABLE;
    hadc1.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;
    hadc1.Init.LowPowerAutoWait      = DISABLE;
    hadc1.Init.ContinuousConvMode    = DISABLE;
    hadc1.Init.NbrOfConversion       = 2;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConv      = ADC_SOFTWARE_START;
    hadc1.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.Overrun               = ADC_OVR_DATA_PRESERVED;
    hadc1.Init.OversamplingMode      = DISABLE;
    if ( HAL_ADC_Init( &hadc1 ) != HAL_OK )
    {
        Error_Handler();
    }

    /** Configure the ADC multi-mode
     */
    multimode.Mode = ADC_MODE_INDEPENDENT;
    if ( HAL_ADCEx_MultiModeConfigChannel( &hadc1, &multimode ) != HAL_OK )
    {
        Error_Handler();
    }

    /** Configure Regular Channel
     */
    sConfig.Channel      = ADC_CHANNEL_12;
    sConfig.Rank         = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_47CYCLES_5;
    sConfig.SingleDiff   = ADC_SINGLE_ENDED;
    sConfig.OffsetNumber = ADC_OFFSET_NONE;
    sConfig.Offset       = 0;
    if ( HAL_ADC_ConfigChannel( &hadc1, &sConfig ) != HAL_OK )
    {
        Error_Handler();
    }

    /** Configure Regular Channel
     */
    sConfig.Channel = ADC_CHANNEL_15;
    sConfig.Rank    = ADC_REGULAR_RANK_2;
    if ( HAL_ADC_ConfigChannel( &hadc1, &sConfig ) != HAL_OK )
    {
        Error_Handler();
    }
    /* USER CODE BEGIN ADC1_Init 2 */

    /* USER CODE END ADC1_Init 2 */
}
/* ADC2 init function */
void MX_ADC2_Init( void )
{

    /* USER CODE BEGIN ADC2_Init 0 */

    /* USER CODE END ADC2_Init 0 */

    ADC_ChannelConfTypeDef sConfig = { 0 };

    /* USER CODE BEGIN ADC2_Init 1 */

    /* USER CODE END ADC2_Init 1 */

    /** Common config
     */
    hadc2.Instance                   = ADC2;
    hadc2.Init.ClockPrescaler        = ADC_CLOCK_ASYNC_DIV1;
    hadc2.Init.Resolution            = ADC_RESOLUTION_12B;
    hadc2.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    hadc2.Init.GainCompensation      = 0;
    hadc2.Init.ScanConvMode          = ADC_SCAN_DISABLE;
    hadc2.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;
    hadc2.Init.LowPowerAutoWait      = DISABLE;
    hadc2.Init.ContinuousConvMode    = ENABLE;
    hadc2.Init.NbrOfConversion       = 1;
    hadc2.Init.DiscontinuousConvMode = DISABLE;
    hadc2.Init.ExternalTrigConv      = ADC_SOFTWARE_START;
    hadc2.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc2.Init.DMAContinuousRequests = DISABLE;
    hadc2.Init.Overrun               = ADC_OVR_DATA_PRESERVED;
    hadc2.Init.OversamplingMode      = DISABLE;
    if ( HAL_ADC_Init( &hadc2 ) != HAL_OK )
    {
        Error_Handler();
    }

    /** Configure Regular Channel
     */
    sConfig.Channel      = ADC_CHANNEL_12;
    sConfig.Rank         = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_640CYCLES_5;
    sConfig.SingleDiff   = ADC_SINGLE_ENDED;
    sConfig.OffsetNumber = ADC_OFFSET_NONE;
    sConfig.Offset       = 0;
    if ( HAL_ADC_ConfigChannel( &hadc2, &sConfig ) != HAL_OK )
    {
        Error_Handler();
    }
    /* USER CODE BEGIN ADC2_Init 2 */

    /* USER CODE END ADC2_Init 2 */
}

static uint32_t HAL_RCC_ADC12_CLK_ENABLED = 0;

void HAL_ADC_MspInit( ADC_HandleTypeDef* adcHandle )
{

    GPIO_InitTypeDef         GPIO_InitStruct = { 0 };
    RCC_PeriphCLKInitTypeDef PeriphClkInit   = { 0 };
    if ( adcHandle->Instance == ADC1 )
    {
        /* USER CODE BEGIN ADC1_MspInit 0 */

        /* USER CODE END ADC1_MspInit 0 */

        /** Initializes the peripherals clocks
         */
        PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC12;
        PeriphClkInit.Adc12ClockSelection  = RCC_ADC12CLKSOURCE_PLL;
        if ( HAL_RCCEx_PeriphCLKConfig( &PeriphClkInit ) != HAL_OK )
        {
            Error_Handler();
        }

        /* ADC1 clock enable */
        HAL_RCC_ADC12_CLK_ENABLED++;
        if ( HAL_RCC_ADC12_CLK_ENABLED == 1 )
        {
            __HAL_RCC_ADC12_CLK_ENABLE();
        }

        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**ADC1 GPIO Configuration
        PB0     ------> ADC1_IN15
        PB1     ------> ADC1_IN12
        */
        GPIO_InitStruct.Pin  = MCU_NTC_Pin | STABLE_POINT_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        HAL_GPIO_Init( GPIOB, &GPIO_InitStruct );

        /* ADC1 DMA Init */
        /* ADC1 Init */
        hdma_adc1.Instance                 = DMA1_Channel1;
        hdma_adc1.Init.Request             = DMA_REQUEST_ADC1;
        hdma_adc1.Init.Direction           = DMA_PERIPH_TO_MEMORY;
        hdma_adc1.Init.PeriphInc           = DMA_PINC_DISABLE;
        hdma_adc1.Init.MemInc              = DMA_MINC_ENABLE;
        hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
        hdma_adc1.Init.MemDataAlignment    = DMA_MDATAALIGN_HALFWORD;
        hdma_adc1.Init.Mode                = DMA_NORMAL;
        hdma_adc1.Init.Priority            = DMA_PRIORITY_LOW;
        if ( HAL_DMA_Init( &hdma_adc1 ) != HAL_OK )
        {
            Error_Handler();
        }

        __HAL_LINKDMA( adcHandle, DMA_Handle, hdma_adc1 );

        /* ADC1 interrupt Init */
        HAL_NVIC_SetPriority( ADC1_2_IRQn, 5, 0 );
        HAL_NVIC_EnableIRQ( ADC1_2_IRQn );
        /* USER CODE BEGIN ADC1_MspInit 1 */

        /* USER CODE END ADC1_MspInit 1 */
    }
    else if ( adcHandle->Instance == ADC2 )
    {
        /* USER CODE BEGIN ADC2_MspInit 0 */

        /* USER CODE END ADC2_MspInit 0 */

        /** Initializes the peripherals clocks
         */
        PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC12;
        PeriphClkInit.Adc12ClockSelection  = RCC_ADC12CLKSOURCE_PLL;
        if ( HAL_RCCEx_PeriphCLKConfig( &PeriphClkInit ) != HAL_OK )
        {
            Error_Handler();
        }

        /* ADC2 clock enable */
        HAL_RCC_ADC12_CLK_ENABLED++;
        if ( HAL_RCC_ADC12_CLK_ENABLED == 1 )
        {
            __HAL_RCC_ADC12_CLK_ENABLE();
        }

        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**ADC2 GPIO Configuration
        PB2     ------> ADC2_IN12
        */
        GPIO_InitStruct.Pin  = LIQUID_DET_ADC_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        HAL_GPIO_Init( LIQUID_DET_ADC_GPIO_Port, &GPIO_InitStruct );

        /* ADC2 interrupt Init */
        HAL_NVIC_SetPriority( ADC1_2_IRQn, 5, 0 );
        HAL_NVIC_EnableIRQ( ADC1_2_IRQn );
        /* USER CODE BEGIN ADC2_MspInit 1 */

        /* USER CODE END ADC2_MspInit 1 */
    }
}

void HAL_ADC_MspDeInit( ADC_HandleTypeDef* adcHandle )
{

    if ( adcHandle->Instance == ADC1 )
    {
        /* USER CODE BEGIN ADC1_MspDeInit 0 */

        /* USER CODE END ADC1_MspDeInit 0 */
        /* Peripheral clock disable */
        HAL_RCC_ADC12_CLK_ENABLED--;
        if ( HAL_RCC_ADC12_CLK_ENABLED == 0 )
        {
            __HAL_RCC_ADC12_CLK_DISABLE();
        }

        /**ADC1 GPIO Configuration
        PB0     ------> ADC1_IN15
        PB1     ------> ADC1_IN12
        */
        HAL_GPIO_DeInit( GPIOB, MCU_NTC_Pin | STABLE_POINT_Pin );

        /* ADC1 DMA DeInit */
        HAL_DMA_DeInit( adcHandle->DMA_Handle );

        /* ADC1 interrupt Deinit */
        /* USER CODE BEGIN ADC1:ADC1_2_IRQn disable */
        /**
         * Uncomment the line below to disable the "ADC1_2_IRQn" interrupt
         * Be aware, disabling shared interrupt may affect other IPs
         */
        /* HAL_NVIC_DisableIRQ(ADC1_2_IRQn); */
        /* USER CODE END ADC1:ADC1_2_IRQn disable */

        /* USER CODE BEGIN ADC1_MspDeInit 1 */

        /* USER CODE END ADC1_MspDeInit 1 */
    }
    else if ( adcHandle->Instance == ADC2 )
    {
        /* USER CODE BEGIN ADC2_MspDeInit 0 */

        /* USER CODE END ADC2_MspDeInit 0 */
        /* Peripheral clock disable */
        HAL_RCC_ADC12_CLK_ENABLED--;
        if ( HAL_RCC_ADC12_CLK_ENABLED == 0 )
        {
            __HAL_RCC_ADC12_CLK_DISABLE();
        }

        /**ADC2 GPIO Configuration
        PB2     ------> ADC2_IN12
        */
        HAL_GPIO_DeInit( LIQUID_DET_ADC_GPIO_Port, LIQUID_DET_ADC_Pin );

        /* USER CODE BEGIN ADC2_MspDeInit 1 */

        /* USER CODE END ADC2_MspDeInit 1 */
    }
}

/* USER CODE BEGIN 1 */
uint32_t adc_chn_average_value( uint16_t chn, uint8_t times )
{
    uint32_t           sum    = 0;
    ADC_HandleTypeDef* handle = NULL;

    if ( chn == STABLE_POINT_Pin || MCU_NTC_Pin )
    {
        return 0;
    }
    else
    {
        handle = &hadc2;
    }

    for ( int i = 0; i < times; i++ )
    {
        HAL_ADC_Start( handle );
        HAL_ADC_PollForConversion( handle, 100 );

        if ( ( HAL_ADC_GetState( handle ) & HAL_ADC_STATE_REG_EOC ) == HAL_ADC_STATE_REG_EOC )
        {
            sum += HAL_ADC_GetValue( handle );
        }
        HAL_ADC_Stop( handle );
        osDelay( 2 );
    }

    return ( uint16_t ) ( sum / times );
}

/**
 * \brief
 * @date 2023-11-30
 * \Author Jackie
 */
void start_check_liquid_level() { HAL_ADC_Start_IT( &hadc2 ); }

/**
 * \brief
 * @date 2025-01-21
 * \Author Jackie
 */
void start_adc1_conv() { HAL_ADC_Start_DMA( &hadc1, ( uint32_t* ) &adc1_dma_buffer, ADC1_CHANNEL_NUM ); }

/**
 * \brief
 * \param channel
 * \retval uint32_t
 * @date 2025-01-22
 * \Author Jackie
 */
uint16_t get_adc1_value( int channel )
{
    uint16_t value = 0;

    vPortEnterCritical();
    if ( channel == ADC_CHANNEL_12 )
    {
        value = adc1_dma_buffer[0];
    }
    else if ( channel == ADC_CHANNEL_15 )
    {
        value = adc1_dma_buffer[1];
    }

    vPortExitCritical();
    return value;
}

/**
 * \brief
 * \param hadc
 * @date 2023-11-30
 * \Author Jackie
 */
void HAL_ADC_ConvCpltCallback( ADC_HandleTypeDef* hadc )
{
    uint32_t val = 0;

    if ( hadc->Instance == ADC2 )
    {
        val = HAL_ADC_GetValue( hadc );

        if ( read_noise )
        {
            noise = MAX( val, noise );

            if ( calibrate_cnt++ > 1000 )
            {
                read_noise = false;
            }
        }
        else
        {
            if ( val > noise )
            {
                ring_buffer_save_isr( &liquid_ad_val, val );
            }
        }
    }
}
/* USER CODE END 1 */
