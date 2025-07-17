/**
 * *****************************************************************************
 * *
 * * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 * *
 * \brief
 * @file cmd.c
 * \Author Jackie
 * @date 2023-11-29
 * @copyright COPYRIGHT (c) 2023
 */
#define CMD_C

/* #include */
#include "app_header.h"
#undef CMD_C
/* #define */

/* typedef */

/* static variables */

/* static constants */

/* static function prototypes */
/*void print_ad( int argc, char* argv[] )
{
    for ( int j = 0; j < TEST_BUFFER_SIZE; j++ )
    {
        printf( "%d ", test_buffer[j] );

        if ( j % 20 == 0 )
        {
            printf( "\r\n" );
        }
    }
}
SHELL_EXPORT_CMD( SHELL_CMD_PERMISSION( 0 ) | SHELL_CMD_TYPE( SHELL_TYPE_CMD_MAIN ) | SHELL_CMD_DISABLE_RETURN, print, print_ad, print debug info\n );
*/
/**
 * \brief
 * \param argc
 * \param argv
 * @date 2024-01-05
 * \Author Jackie
 */
void thrs1( int argc, char* argv[] )
{
    if ( argc == 2 )
    {
        float thrs  = atof( argv[1] );
        param.thrs1 = thrs;
        param.crc8  = crc8( ( uint8_t* ) &param, offsetof( LiquidDecte_TypeDef, crc8 ) );
        save_data( CONFIG_FLASH_ADDR, ( uint32_t* ) &param, sizeof( param ) / 4 );
    }
}
SHELL_EXPORT_CMD( SHELL_CMD_PERMISSION( 0 ) | SHELL_CMD_TYPE( SHELL_TYPE_CMD_MAIN ) | SHELL_CMD_DISABLE_RETURN, thrs1, thrs1, config threshold 1\n );

/**
 * \brief
 * \param argc
 * \param argv
 * @date 2024-01-05
 * \Author Jackie
 */
void thrs2( int argc, char* argv[] )
{
    if ( argc == 2 )
    {
        float thrs  = atof( argv[1] );
        param.thrs2 = thrs;
        param.crc8  = crc8( ( uint8_t* ) &param, offsetof( LiquidDecte_TypeDef, crc8 ) );
        save_data( CONFIG_FLASH_ADDR, ( uint32_t* ) &param, sizeof( param ) / 4 );
    }
}
SHELL_EXPORT_CMD( SHELL_CMD_PERMISSION( 0 ) | SHELL_CMD_TYPE( SHELL_TYPE_CMD_MAIN ) | SHELL_CMD_DISABLE_RETURN, thrs2, thrs2, config threshold 2\n );

/**
 * \brief
 * \param argc
 * \param argv
 * @date 2024-01-11
 * \Author Jackie
 */
void reset( int argc, char* argv[] )
{
    __set_FAULTMASK( 1 );
    NVIC_SystemReset();
}
SHELL_EXPORT_CMD( SHELL_CMD_PERMISSION( 0 ) | SHELL_CMD_TYPE( SHELL_TYPE_CMD_MAIN ) | SHELL_CMD_DISABLE_RETURN, reset, reset, reset board\n );

/**
 * \brief
 * \param argc
 * \param argv
 * @date 2024-01-11
 * \Author Jackie
 */
void u7_r( int argc, char* argv[] )
{
    if ( argc == 2 )
    {
        int r      = atoi( argv[1] );
        param.U7_R = r;
        ad5160_2_writeByte( r );
        param.crc8 = crc8( ( uint8_t* ) &param, offsetof( LiquidDecte_TypeDef, crc8 ) );
        save_data( CONFIG_FLASH_ADDR, ( uint32_t* ) &param, sizeof( param ) / 8 );
    }
}
SHELL_EXPORT_CMD( SHELL_CMD_PERMISSION( 0 ) | SHELL_CMD_TYPE( SHELL_TYPE_CMD_MAIN ) | SHELL_CMD_DISABLE_RETURN, u7_r, u7_r, config U7 R value\n );

/**
 * \brief
 * \param argc
 * \param argv
 * @date 2025-05-22
 * \Author Jackie
 */
void u1_r( int argc, char* argv[] )
{
    if ( argc == 2 )
    {
        int r = atoi( argv[1] );
        ad5160_1_writeByte( r );
        param.U1_R = r;
        param.crc8 = crc8( ( uint8_t* ) &param, offsetof( LiquidDecte_TypeDef, crc8 ) );
        save_data( CONFIG_FLASH_ADDR, ( uint32_t* ) &param, sizeof( param ) / 8 );
    }
}
SHELL_EXPORT_CMD( SHELL_CMD_PERMISSION( 0 ) | SHELL_CMD_TYPE( SHELL_TYPE_CMD_MAIN ) | SHELL_CMD_DISABLE_RETURN, u1_r, u1_r, config U1 R value\n );

/**
 * \brief
 * \param argc
 * \param argv
 * @date 2025-05-22
 * \Author Jackie
 */
void adc_sf( int argc, char* argv[] )
{
    if ( argc == 1 )
    {
        uint32_t adc_value = adc_chn_average_value( STABLE_POINT_Pin, 10 );
        double   volt      = ( double ) adc_value * 3.3 / 4096;
        LOG( LIQUID_MODULE, "adc_sf = %f", volt );
    }
}
SHELL_EXPORT_CMD( SHELL_CMD_PERMISSION( 0 ) | SHELL_CMD_TYPE( SHELL_TYPE_CMD_MAIN ) | SHELL_CMD_DISABLE_RETURN, adc_sf, adc_sf, adc sf\n );

/**
 * \brief
 * \param argc
 * \param argv
 * @date 2025-05-22
 * \Author Jackie
 */
void adc_pll( int argc, char* argv[] )
{
    if ( argc == 1 )
    {
        uint32_t adc_value = adc_chn_average_value( LIQUID_DET_ADC_Pin, 10 );
        double   volt2     = ( double ) adc_value * 3.3 / 4096;
        LOG( LIQUID_MODULE, "adc_pll = %f", volt2 );
    }
}
SHELL_EXPORT_CMD( SHELL_CMD_PERMISSION( 0 ) | SHELL_CMD_TYPE( SHELL_TYPE_CMD_MAIN ) | SHELL_CMD_DISABLE_RETURN, adc_pll, adc_pll, adc pll\n );

/**
 * \brief
 * \param argc
 * \param argv
 * @date 2024-01-18
 * \Author Jackie
 */
void debug_info( int argc, char* argv[] )
{
    if ( argc == 1 )
    {
        LOG( CMD_MODULE, "thrs1: %f, thrs2: %f, u7_r: %d, u1_r: %d", ( double ) param.thrs1, ( double ) param.thrs2, param.U7_R, param.U1_R );
    }
}
SHELL_EXPORT_CMD( SHELL_CMD_PERMISSION( 0 ) | SHELL_CMD_TYPE( SHELL_TYPE_CMD_MAIN ) | SHELL_CMD_DISABLE_RETURN, params, debug_info, display params\n );

/**
 * \brief
 * \param argc
 * \param argv
 * @date 2025-01-23
 * \Author Jackie
 */
void heat_cmd( int argc, char* argv[] )
{
    if ( argc == 2 )
    {
        int ctrl = atoi( argv[1] );
        // debug_mode = atoi( argv[1] );

        if ( ctrl == 1 )
        {
            heat_ctrl( true );
            LOG( CAN_MODULE, "heating is on" );
        }
        else
        {
            heat_ctrl( false );
            LOG( CAN_MODULE, "heating is off" );
        }
    }
}
SHELL_EXPORT_CMD( SHELL_CMD_PERMISSION( 0 ) | SHELL_CMD_TYPE( SHELL_TYPE_CMD_MAIN ) | SHELL_CMD_DISABLE_RETURN, heat, heat_cmd, heat ctrl\n );

/**
 * \brief
 * \param argc
 * \param argv
 * @date 2025-01-23
 * \Author Jackie
 */
void liquid_level_ctrl( int argc, char* argv[] )
{
    if ( argc == 2 )
    {
        liquid_level_detect_flag = atoi( argv[1] );
    }
}
SHELL_EXPORT_CMD( SHELL_CMD_PERMISSION( 0 ) | SHELL_CMD_TYPE( SHELL_TYPE_CMD_MAIN ) | SHELL_CMD_DISABLE_RETURN, detect_start, liquid_level_ctrl, liquid level ctrl\n );

/**
 * \brief
 * \param argc
 * \param argv
 * @date 2025-02-07
 * \Author Jackie
 */
void needle_temp( int argc, char* argv[] )
{
    if ( argc == 1 )
    {
        LOG( CAN_MODULE, "needle temperature: %f", needle_temperature );
    }
}
SHELL_EXPORT_CMD( SHELL_CMD_PERMISSION( 0 ) | SHELL_CMD_TYPE( SHELL_TYPE_CMD_MAIN ) | SHELL_CMD_DISABLE_RETURN, temp, needle_temp, needle temp ctrl\n );
