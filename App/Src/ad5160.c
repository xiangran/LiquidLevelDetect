/**
 *****************************************************************************
 * @brief 	File containing example of doxygen usage for quick reference.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 * @file 	ad5160.c
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

#define AD5160_C

/* #include */
#include "app_header.h"
#undef AD5160_C
/* #define */

/* typedef */

/* static variables */

/* static constants */

/* static function prototypes */
/*!
 * \fn     liquid_ad_value_calibration
 * \brief 设置中心频率
 *
 *
 * \retval void
 *
 * \Author Jackie  2022-11-01
 */
int8_t liquid_ad_value_calibration()
{
    int8_t ret = 0;
#if 0
    uint8_t  potentioData = 127, calibrate_cnt = 0, read_cnt = 0;
    double   volt = 0.0, volt2 = 0.0;
    uint32_t adc_value = 0, curr_tick = osKernelGetTickCount();
    uint32_t sum = 0, buffer[10] = { 0 }, max_val = 0, min_val = 0xffffffff;

    do
    {
        osDelay( 5 );
        // 读取锁相环SF_OUT输出电压
        adc_value          = get_adc1_value( ADC_CHANNEL_12 );
        buffer[read_cnt++] = adc_value;
        if ( read_cnt < 10 )
            continue;
        else
        {
            max_val  = 0;
            min_val  = 0xffffffff;
            read_cnt = 0;
            sum      = 0;

            for ( int i = 0; i < 10; i++ )
            {
                if ( buffer[i] > max_val )
                    max_val = buffer[i];
                if ( buffer[i] < min_val )
                    min_val = buffer[i];
                sum += buffer[i];
            }
            adc_value = ( sum - max_val - min_val ) / 8;
        }

        volt = ( double ) adc_value * 3.3 / 4096;
        LOG( LIQUID_MODULE, "adc_value = %d, volt = %f, potentioData = %d", adc_value, volt, potentioData );
        adc_value = adc_chn_average_value( LIQUID_DET_ADC_Pin, 10 );
        volt2     = ( double ) adc_value * 3.3 / 4096;
        LOG( LIQUID_MODULE, "adc_value2 = %d, volt2 = %f", adc_value, volt2 );

        if ( volt > 1.8 )
        {
            if ( potentioData > 0 )
            {
                potentioData--;                     // 增大电位计R_aw端电阻
                ad5160_1_writeByte( potentioData ); // 设置采样数字电位计U1,Rp2
            }
            else // 数字电位计到下极限
            {
                potentioData = 127;
            }
            calibrate_cnt = 0;
        }
        else if ( volt < 1.5 )
        {
            if ( potentioData < 255 )
            {
                potentioData++;                     // 减小电位计R_aw端电阻
                ad5160_1_writeByte( potentioData ); // 设置采样数字电位计U1
            }
            else // 数字电位计到上极限
            {
                potentioData = 127;
            }
            calibrate_cnt = 0;
        }
        else
        {
            calibrate_cnt++;
            LOG( LIQUID_MODULE, "potentioData: %d", potentioData );
        }

        // 20s timeout
        if ( osKernelGetTickCount() - curr_tick > 20000 )
        {
            LOG( LIQUID_MODULE, "calibrate fail" );
            ret = -1;
            break;
        }
    } while ( calibrate_cnt < 5 );

    // 此时液位探测不应该读到电压
    if ( volt2 > 1.0 )
    {
        ret = -2;
    }
#else
    ad5160_1_writeByte( param.U1_R );
#endif
    return ret;
}

void ad5160_gpio_init( void )
{
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin( GPIOA, AD5160_1_CS, GPIO_PIN_RESET );
    HAL_GPIO_WritePin( GPIOB, AD5160_1_WCLK | AD5160_1_SDI, GPIO_PIN_RESET );
    HAL_GPIO_WritePin( GPIOB, AD5160_2_CS | AD5160_2_WCLK | AD5160_2_SDI, GPIO_PIN_RESET );

    /*Configure GPIO pins : PBPin PBPin */
    GPIO_InitStruct.Pin   = AD5160_1_CS;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull  = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init( GPIOA, &GPIO_InitStruct );

    GPIO_InitStruct.Pin   = AD5160_1_WCLK | AD5160_1_SDI;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init( GPIOB, &GPIO_InitStruct );

    GPIO_InitStruct.Pin   = AD5160_2_CS;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init( GPIOB, &GPIO_InitStruct );

    GPIO_InitStruct.Pin   = AD5160_2_WCLK | AD5160_2_SDI;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init( GPIOB, &GPIO_InitStruct );
}

/**
 * \brief
 * \param num
 * @date 2023-12-29
 * \Author Jackie
 */
void ad5160_init()
{
    ad5160_gpio_init();

    AD5160_1_CS_SET;
    AD5160_1_WCLK_CLR;

    AD5160_2_CS_SET;
    AD5160_2_WCLK_CLR;
}

/**
 * \brief
 * \param z
 * @date 2023-12-29
 * \Author Jackie
 */
void ad5160_delay( unsigned int z )
{
    for ( ; z > 0; z-- )
    {
        ;
    }
}

/**
 * \brief 设置采样数字电位计U1,Rp2
 * \param data_resistance
 * @date 2023-12-29
 * \Author Jackie
 */
void ad5160_1_writeByte( uint8_t data_resistance )
{
    uint8_t i;
    AD5160_1_CS_CLR;

    for ( i = 0; i < 8; i++ )
    {
        AD5160_1_WCLK_CLR;
        ad5160_delay( 0x0FFF );
        if ( data_resistance & 0x80 )
            AD5160_1_SDI_Write_1;
        else
            AD5160_1_SDI_Write_0;
        ad5160_delay( 0x0FFF );
        AD5160_1_WCLK_SET;
        ad5160_delay( 0x0FFF );
        data_resistance <<= 1;
    }
    AD5160_1_CS_SET;
    AD5160_1_WCLK_CLR;
}

/**
 * \brief 设置采样数字电位计U2,Rp1
 * \param data_resistance
 * @date 2023-12-29
 * \Author Jackie
 */
void ad5160_2_writeByte( uint8_t data_resistance )
{
    uint8_t i;
    AD5160_2_CS_CLR;

    for ( i = 0; i < 8; i++ )
    {
        AD5160_2_WCLK_CLR;
        ad5160_delay( 0x0FFF );
        if ( data_resistance & 0x80 )
            AD5160_2_SDI_Write_1;
        else
            AD5160_2_SDI_Write_0;
        ad5160_delay( 0x0FFF );
        AD5160_2_WCLK_SET;
        ad5160_delay( 0x0FFF );
        data_resistance <<= 1;
    }
    AD5160_2_CS_SET;
    AD5160_2_WCLK_CLR;
}
