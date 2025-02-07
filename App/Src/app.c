/**
 *****************************************************************************
 * @brief 	File containing example of doxygen usage for quick reference.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 * @file 	app.c
 * @author	Jackie
 * @date 	1/Nov/2022
 *****************************************************************************
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <b>&copy; COPYRIGHT 2022 </b>
 *
 *****************************************************************************
 */

#define APP_C

/* #include */
#include "app_header.h"
#undef APP_C
/* #define */

/* typedef */

/* static variables */

/* static constants */

/* static function prototypes */
/*!
 * \fn     app_task
 * \brief
 *
 * \param  [in] void* pvParameters   #
 *
 * \retval void
 *
 * \Author Jackie  2022-11-01
 */
void detect_liquid_level_task( void* pvParameters )
{
    uint32_t adc_value = 0, k_cnt = 0, thrs_cnt = 0;
    double   voltage = 0.0, k_step_value = 0.0;
    bool     liquid_detected = false;

    ring_buffer_init( &liquid_ad_val, adc_value_buffer, SINE_WAVE_PERIOD );
    // 设置采样数字电位计U2
    ad5160_2_writeByte( 255 ); // param.U7_R

    if ( liquid_ad_value_calibration() == 0 )
    {
        read_noise = true;
        ring_buffer_clear( &liquid_ad_val );
    }
    else
    {
        while ( true )
        {
            HAL_GPIO_TogglePin( LED_RED_GPIO_Port, LED_RED_Pin );
            osDelay( 300 );
        }
    }

    start_check_liquid_level();

    // 检测噪声信号
    while ( noise > 100 )
    {
        read_noise = true;
        while ( read_noise )
            __NOP();

        if ( noise > 100 )
        {
            // 干扰过大
            HAL_GPIO_WritePin( LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET );
        }
        else
        {
            HAL_GPIO_WritePin( LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET );
            break;
        }
    }

    // param.thrs1 = METHOD1_THRS;
    HAL_GPIO_WritePin( CPU_STATUS_GPIO_Port, CPU_STATUS_Pin, GPIO_PIN_RESET );
    osDelay( 500 );
    HAL_GPIO_WritePin( CPU_STATUS_GPIO_Port, CPU_STATUS_Pin, GPIO_PIN_SET );
    // LOG( APP_MODULE, "init complete, noise: %d", noise );

    while ( true )
    {
        // analyse 3 data
        if ( ring_buffer_data_num( &liquid_ad_val ) )
        {
            ring_buffer_read( &liquid_ad_val, &adc_value, 1 );

            if ( liquid_level_detect_flag )
            {
                voltage = ( double ) adc_value * 3.3 / 4096;
                // if ( voltage > 0.1 )
                //     printf( "%f\r\n", voltage );

                // 阈值法
                if ( voltage > ( double ) param.thrs1 )
                {
                    // 3 AD values greater than high thresholds
                    thrs_cnt++;
                }
                else
                {
                    thrs_cnt = 0;
                }

                // 斜率法
                if ( voltage > ( double ) param.thrs2 )
                {
                    if ( k_cnt )
                    {
                        float k = voltage - k_step_value;
                        if ( k > param.thrs2 )
                        {
                            k_step_value = voltage;
                            k_cnt++;
                        }
                    }
                    else
                    {
                        // first value
                        k_step_value = voltage;
                        k_cnt++;
                    }
                }
            }
        }

        // 阈值
        if ( thrs_cnt )
        {
            HAL_ADC_Stop_IT( &hadc2 );
            liquid_detected = true;
        }
        else if ( k_cnt > 2 ) // 斜率
        {
            HAL_ADC_Stop_IT( &hadc2 );
            liquid_detected = true;
        }

        if ( liquid_detected )
        {
            thrs_cnt        = 0;
            k_cnt           = 0;
            liquid_detected = false;
            HAL_GPIO_WritePin( LEVEL_GPIO_Port, LEVEL_Pin, GPIO_PIN_SET );
            HAL_GPIO_WritePin( CPU_STATUS_GPIO_Port, CPU_STATUS_Pin, GPIO_PIN_RESET );
            osDelay( 1000 );
            HAL_GPIO_WritePin( LEVEL_GPIO_Port, LEVEL_Pin, GPIO_PIN_RESET );
            HAL_GPIO_WritePin( CPU_STATUS_GPIO_Port, CPU_STATUS_Pin, GPIO_PIN_SET );
            ring_buffer_clear( &liquid_ad_val );
            start_check_liquid_level();
        }
    }
}

/**
 * \brief
 * \param pvParameters
 * @date 2025-01-22
 * \Author Jackie
 */
void adc_task( void* pvParameters )
{
    HAL_ADCEx_Calibration_Start( &hadc1, ADC_SINGLE_ENDED );

    while ( true )
    {
        start_adc1_conv();
        osDelay( 10 );
    }
}

/**
 * \brief 获取重启原因并清除状态位
 * \retval reset_cause_t
 * @date 2025-01-21
 * \Author Jackie
 */
reset_cause_t get_Reset_Cause( void )
{
    reset_cause_t reset_cause;

    if ( __HAL_RCC_GET_FLAG( RCC_FLAG_LPWRRST ) )
    {
        reset_cause = RESET_CAUSE_LOW_POWER_RESET;
    }
    else if ( __HAL_RCC_GET_FLAG( RCC_FLAG_WWDGRST ) )
    {
        reset_cause = RESET_CAUSE_WINDOW_WATCHDOG;
    }
    else if ( __HAL_RCC_GET_FLAG( RCC_FLAG_IWDGRST ) )
    {
        reset_cause = RESET_CAUSE_INDEPENDENT_WATCHDOG;
    }
    else if ( __HAL_RCC_GET_FLAG( RCC_FLAG_SFTRST ) )
    {
        reset_cause = RESET_CAUSE_SOFTWARE;
    }
    else if ( __HAL_RCC_GET_FLAG( RCC_FLAG_PINRST ) )
    {
        reset_cause = RESET_CAUSE_EXTERNAL_PIN_RESET;
    }
    else if ( __HAL_RCC_GET_FLAG( RCC_FLAG_BORRST ) )
    {
        reset_cause = RESET_CAUSE_BROWNOUT_RESET;
    }
    else
    {
        reset_cause = RESET_CAUSE_UNKNOWN;
    }

    // 清除所有复位标志
    __HAL_RCC_CLEAR_RESET_FLAGS();

    return reset_cause;
}

/**
 * \brief 将复位原因转换为字符串
 * \param reset_cause
 * \retval const char*
 * @date 2025-01-21
 * \Author Jackie
 */
const char* reset_Cause_ToString( reset_cause_t reset_cause )
{
    switch ( reset_cause )
    {
        case RESET_CAUSE_LOW_POWER_RESET:
            return "LOW POWER RESET";
        case RESET_CAUSE_WINDOW_WATCHDOG:
            return "WINDOW WATCHDOG";
        case RESET_CAUSE_INDEPENDENT_WATCHDOG:
            return "INDEPENDENT WATCHDOG";
        case RESET_CAUSE_SOFTWARE:
            return "SOFTWARE RESET";
        case RESET_CAUSE_POWER_ON_POWER_DOWN:
            return "POWER-ON/POWER-DOWN";
        case RESET_CAUSE_EXTERNAL_PIN_RESET:
            return "EXTERNAL PIN RESET";
        case RESET_CAUSE_BROWNOUT_RESET:
            return "BROWNOUT";
        default:
            return "UNKNOWN";
    }
}