/**
 *****************************************************************************
 * @brief 	File containing example of doxygen usage for quick reference.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 * @file 	app_command.c
 * @author	Jackie
 * @date 	3/Apr/2023
 *****************************************************************************
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <b>&copy; COPYRIGHT 2023 </b>
 *
 *****************************************************************************
 */

#define APP_COMMAND_C

/* #include */
#include "app_header.h"
#undef APP_COMMAND_C
/* #define */

/* typedef */

/* static variables */

/* static constants */

/* static function prototypes */
/*!
 * \fn     cli_task
 * \brief
 *
 * \param  [in] void* pvParameters   #
 *
 * \retval void
 *
 * \Author Jackie  2023-4-03
 */
void needle_temp_ctrl_task( void* pvParameters )
{
    double   v_adc_ntc = 0.0, ntc_curr_resistance = 0.0;
    uint32_t adc_value = 0;
    // GPIO_PinState flt       = GPIO_PIN_RESET;
    const double R18     = 5100.0f; // 分压电阻 5.1K
    const double VCC     = 3.3f;    // 参考电压
    const double ADC_MAX = 4096.0f; // 12位ADC
    const double GAIN    = 2.0;     // 运放增益 = 1 + (R8/R11) = 2

    // LOG( CAN_MODULE, "ntc task init complete" );

    while ( true )
    {
        adc_value = get_adc1_value( ADC_CHANNEL_15 );
        v_adc_ntc = ( double ) adc_value * VCC / ADC_MAX;
        // 同相放大2倍
        double v_AOUT = v_adc_ntc / GAIN;

        // KCL: V_N1 / R_A + (V_N1 - V_out) / R_B + (V_N1 - 3.3V) / R_C = 0
        // V_N1 / 1kΩ + (V_N1 - V_out) / 1.5kΩ + (V_N1 - 3.3V) / 1kΩ = 0
        // V_N1 = (9.9 + 2 * V_out) / 8
        double v            = ( 9.9 + 2 * v_AOUT ) / 8; // V_out为负, v为反相输入端电压
        ntc_curr_resistance = R18 * ( VCC - v ) / v;

        for ( int i = 0; i < LOOK_UP_TABLE_ELEMENTS; i++ )
        {
            if ( lookUpTable[i].resistance >= ntc_curr_resistance )
            {
                if ( i > 0 )
                {
                    // 得出下区间电阻值
                    double min_resistance = lookUpTable[( i > 0 ) ? i - 1 : 0].resistance;
                    // 得出上区间电阻值
                    double max_resistance = lookUpTable[i].resistance;
                    // 将该区间的阻值分为10等分
                    double d1 = ( max_resistance - min_resistance ) / 10;
                    // 得出n份*0.1°C
                    double d2 = ( ( ( ntc_curr_resistance - min_resistance ) / d1 ) * ( 1 / 10 ) );
                    // 以上四步是求小数点温度
                    needle_temperature = lookUpTable[i].temperature + d2;
                    break;
                }
                else
                {
                    needle_temperature = lookUpTable[0].temperature;
                }
            }
        }
        LOG( CAN_MODULE, "ntc volt:%f, R:%f, temp:%f", v_adc_ntc, ntc_curr_resistance, needle_temperature );
        // flt = HAL_GPIO_ReadPin( HEAT_FAULT_GPIO_Port, HEAT_FAULT_Pin );

        osDelay( 1000 );
    }
}

/*!
 * \fn     cmd_task_entry
 * \brief
 *
 * \param  [in] void* parameter   #
 *
 * \retval void
 *
 * \Author Jackie  2023-4-03
 */
void cmd_task_entry( void* parameter )
{
    CmdErrorOpts_TypeDef* ret = ( CmdErrorOpts_TypeDef* ) pvPortMalloc( sizeof( CmdErrorOpts_TypeDef ) );
    CmdCtx_TypeDef*       cmd = ( CmdCtx_TypeDef* ) parameter;

    if ( ret )
    {
        memset( ret, 0, sizeof( CmdErrorOpts_TypeDef ) );
        ret->resp_len = 4;

        LOG( APP_MODULE, "exec: 0x%x", cmd->cmd );

        switch ( cmd->cmd )
        {
            /*case CMD_SNEEDLE_DETECT_LIQUID:
            case CMD_RNEEDLE_DETECT_LIQUID:
            {
                liquid_detect_ctrl( cmd, ret );
            }
            break;*/
            case CMD_LIUDETECT1_VERSION:
            case CMD_LIUDETECT2_VERSION:
            {
                drv_version( cmd, ret );
            }
            break;
            case CMD_TIMESTAMP_SYNC:
            {
                timestamp_sync( cmd, ret );
            }
            break;
            default:
            {
                ret->error = WARN257_NO_ACK;
            }
            break;
        }

        cmd_response( cmd->cmd, ret );
        vPortFree( ( void* ) ret );
    }
    trace_mem_free( __FUNCTION__, __LINE__, ( void* ) parameter, true );
    vTaskDelete( NULL );
}

/*!
 * \fn     cmd_process_task
 * \brief
 *
 * \param  [in] CmdCtx_TypeDef* cmd   #
 *
 * \retval void
 *
 * \Author Jackie  2023-4-03
 */
void cmd_process_task( CmdCtx_TypeDef* cmd ) {}

void cmd_response( Uplink_Protoc_Function_TypeDef cmd, CmdErrorOpts_TypeDef* result )
{
    /*----------------------------------------------------------------*/
    /*----        Local Varible       ----*/
    /*----------------------------------------------------------------*/
    /*----------------------------------------------------------------*/
    /*----         Code body          ----*/
    /*----------------------------------------------------------------*/

    printf( "cmd process result: %d", result->error );
}

/*!
 * \fn     liquid_detect_ctrl
 * \brief
 *
 * \param  [in] CmdCtx_TypeDef* cmd         #
 * \param  [in] CmdErrorOpts_TypeDef* ret   #
 *
 * \retval void
 *
 * \Author Jackie  2023-4-03
 */
/*void liquid_detect_ctrl( CmdCtx_TypeDef* cmd, CmdErrorOpts_TypeDef* ret )
{
    liquid_scan = cmd->data[0];

    if ( liquid_scan == 1 )
    {
        HAL_GPIO_WritePin( CPU_STATUS_GPIO_Port, CPU_STATUS_Pin, GPIO_PIN_SET );
    }
    else
    {
        HAL_GPIO_WritePin( CPU_STATUS_GPIO_Port, CPU_STATUS_Pin, GPIO_PIN_RESET );
    }
}*/

/*!
 * \fn     drv_version
 * \brief
 *
 * \param  [in] CmdCtx_TypeDef* cmd         #
 * \param  [in] CmdErrorOpts_TypeDef* ret   #
 *
 * \retval void
 *
 * \Author Jackie  2023-4-03
 */
void drv_version( CmdCtx_TypeDef* cmd, CmdErrorOpts_TypeDef* ret )
{
    int baseVer = MAJORVER, mVer = MIDVER, cVer = MINORVER, iVer = INTVER;

    snprintf( ( char* ) ret->resp, CMD_RESPONSE_LEN, "V%d.%d.%d.%d", baseVer, mVer, cVer, iVer );
    ret->resp_len = 30;
}

/*!
 * \fn     timestamp_sync
 * \brief
 *
 * \param  [in] CmdCtx_TypeDef* cmd         #
 * \param  [in] CmdErrorOpts_TypeDef* ret   #
 *
 * \retval void
 *
 * \Author Jackie  2023-4-03
 */
void timestamp_sync( CmdCtx_TypeDef* cmd, CmdErrorOpts_TypeDef* ret )
{
    uint32_t   ts = *( uint32_t* ) &cmd->data[0];
    struct tm* vl_tm;

    RTC_DateTypeDef sdate;
    RTC_TimeTypeDef stime;

    time_t count = ts;

    vl_tm         = localtime( &count );
    sdate.Year    = vl_tm->tm_year - 100;
    sdate.Month   = vl_tm->tm_mon + 1;
    sdate.Date    = vl_tm->tm_mday;
    stime.Hours   = vl_tm->tm_hour;
    stime.Minutes = vl_tm->tm_min;
    stime.Seconds = vl_tm->tm_sec;

    LOG( APP_MODULE, "sync ts: %d-%d-%d %d:%d:%d", sdate.Year, sdate.Month, sdate.Date, stime.Hours, stime.Minutes, stime.Seconds );
    HAL_RTC_SetDate( &hrtc, &sdate, RTC_FORMAT_BIN );
    HAL_RTC_SetTime( &hrtc, &stime, RTC_FORMAT_BIN );
}
