/**
 *****************************************************************************
 * @brief 	File containing example of doxygen usage for quick reference.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 * @file 	public.c
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

#define PUBLIC_C

/* #include */
#include "app_header.h"
#undef PUBLIC_C
/* #define */

/* typedef */

/* static variables */

/* static constants */

/* static function prototypes */
/*!
 * \fn     DWT_Delay_Init
 * \brief
 *
 * \param  [in] void   #
 *
 * \retval uint32_t
 *
 * \Author Jackie  2022-11-01
 */
uint32_t DWT_Delay_Init( void )
{
    /* Disable TRC */
    CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk; // ~0x01000000;
    /* Enable TRC */
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // 0x01000000;

    /* Disable clock cycle counter */
    DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk; //~0x00000001;
    /* Enable  clock cycle counter */
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk; // 0x00000001;

    /* Reset the clock cycle counter value */
    DWT->CYCCNT = 0;

    /* 3 NO OPERATION instructions */
    __ASM volatile( "NOP" );
    __ASM volatile( "NOP" );
    __ASM volatile( "NOP" );

    /* Check if clock cycle counter has started */
    if ( DWT->CYCCNT )
    {
        return 0; /*clock cycle counter started*/
    }
    else
    {
        return 1; /*clock cycle counter not started*/
    }
}

/*!
 * \fn     rtk_set_event
 * \brief
 *
 * \param  [in] uint8_t evt_id                    #
 * \param  [in] intptr_t evt_p1                   #
 * \param  [in] intptr_t evt_p2                   #
 * \param  [in] intptr_t evt_p3                   #
 * \param  [in] osMessageQueueId_t thread_index   #
 *
 * \retval void
 *
 * \Author Jackie  2023-4-03
 */
void rtk_set_event( uint8_t evt_id, intptr_t evt_p1, intptr_t evt_p2, intptr_t evt_p3, osMessageQueueId_t thread_index )
{
    osStatus_t      state;
    evt_info_s_type vl_TaskSync   = { 0 };
    bool            high_priority = false;

    vl_TaskSync.evt_id     = evt_id;
    vl_TaskSync.evt_param1 = evt_p1;
    vl_TaskSync.evt_param2 = evt_p2;
    vl_TaskSync.evt_param3 = evt_p3;
    vl_TaskSync.src_task   = ( intptr_t ) osThreadGetId();

    if ( ( state = osMessageQueuePut( thread_index, &vl_TaskSync, high_priority, 0 ) ) != osOK )
    {
        printf( "set evt %d to 0x%x fail = %d", evt_id, thread_index, state );
    }
    /*else
    {
        printf( "dst q %x size: %d\r\n", thread_index, osMessageQueueGetCount( thread_index ) );
    }*/
}

/*!
 * \fn     start_timer
 * \brief
 *
 * \param  [in] uint8_t timer_id   #
 *
 * \retval void
 *
 * \Author Jackie  2022-8-16
 */
void start_timer( uint8_t timer_id )
{
    osStatus_t ret;

    // LOG( APP_MODULE, "start timer %d, d:%d", timer_id, g_TimerList[timer_id].millisec / 1000 );
    if ( ( ret = osTimerStart( g_TimerController[timer_id], g_TimerList[timer_id].millisec ) ) != osOK )
    {
        ALERT( APP_MODULE, "start timer %d fail: %d\r\n", timer_id, ret );
    }
}

/*!
 * \fn     start_timer_with_duration
 * \brief
 *
 * \param  [in] uint8_t time_id     #
 * \param  [in] uint32_t duration   #
 *
 * \retval void
 *
 * \Author Jackie  2022-11-09
 */
void start_timer_with_duration( uint8_t timer_id, uint32_t duration )
{
    osStatus_t ret;

    // LOG( APP_MODULE, "start timer %d, d:%d", timer_id, duration / 1000 );
    if ( ( ret = osTimerStart( g_TimerController[timer_id], duration ) ) != osOK )
    {
        ALERT( APP_MODULE, "start timer %d fail: %d\r\n", timer_id, ret );
    }
}

/*!
 * \fn     stop_timer
 * \brief
 *
 * \param  [in] uint8_t timer_id   #
 *
 * \retval void
 *
 * \Author Jackie  2022-11-07
 */
void stop_timer( uint8_t timer_id )
{
    osStatus_t ret;

    // LOG( APP_MODULE, "stop timer %d, d:%d", timer_id, g_TimerList[timer_id].millisec / 1000 );
    if ( ( ret = osTimerStop( g_TimerController[timer_id] ) ) != osOK )
    {
        ALERT( APP_MODULE, "stop timer %d fail: %d\r\n", timer_id, ret );
    }
}

/*!
 * \fn     timeout_callback
 * \brief
 *
 * \param  [in] void* arg   #
 *
 * \retval void
 *
 * \Author Jackie  2022-8-16
 */
void timeout_callback( void* arg )
{
    uint32_t vl_TimerID = ( uint32_t ) arg;

    if ( vl_TimerID == E_TIMER_PID_PERIOD )
    {
        //rtk_set_event( g_TimerList[vl_TimerID].Send_ID, vl_TimerID, 0, 0, ntc_queue_handle );
    }
}

/*!
 * \fn     crc8
 * \brief
 *
 * \param  [in] uint8_t* data   #
 * \param  [in] uint16_t len    #
 *
 * \retval uint8_t
 *
 * \Author Jackie  2023-4-03
 */
uint8_t crc8( uint8_t* data, uint16_t len )
{
    uint8_t crc = 0;

    for ( int i = 0; i < len; i++ )
    {
        crc ^= data[i];
    }

    return crc;
}
