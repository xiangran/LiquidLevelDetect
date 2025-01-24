/**
 *****************************************************************************
 * @brief 	File containing example of doxygen usage for quick reference.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 * @file 	public.h
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

#ifndef PUBLIC_H
#define PUBLIC_H

/* #include */

/* #define */
// Static Array length
#define _ARRAY_SIZE( ARRAY ) ( sizeof( ARRAY ) / sizeof( ( ARRAY )[0] ) )
#define ARRAY_SIZE( ARRAY ) ( ( _ARRAY_SIZE( ARRAY ) == 1 || sizeof( ARRAY ) != sizeof( &( ( ARRAY )[0] ) ) ) ? _ARRAY_SIZE( ARRAY ) : 0 )

#define BITSET( x, y ) ( x |= ( 1 << y ) )  // set Y bit of X
#define BITCLR( x, y ) ( x &= ~( 1 << y ) ) // clear Y bit of X
#define BITCHK( X, Y ) ( ( X >> Y ) & 1 )
#define BYTE( value, n ) ( ( ( value ) >> ( ( n ) << 3 ) ) & 0xFF )

#ifndef MIN
#define MIN( a, b ) ( ( ( a ) < ( b ) ) ? ( a ) : ( b ) )
#endif

#ifndef MAX
#define MAX( a, b ) ( ( ( a ) > ( b ) ) ? ( a ) : ( b ) )
#endif

__STATIC_INLINE void DWT_Delay_us( volatile uint32_t microseconds )
{
    uint32_t clk_cycle_start = DWT->CYCCNT;

    /* Go to number of cycles for system */
    microseconds *= ( HAL_RCC_GetHCLKFreq() / 1000000 );

    /* Delay till end */
    while ( ( DWT->CYCCNT - clk_cycle_start ) < microseconds )
        ;
}

#define PRINT_RAW_DATA( BUFF, LEN )                    \
    for ( int i = 0; i < LEN; i++ )                    \
    {                                                  \
        printf( "0x%x ", *( ( uint8_t* ) BUFF + i ) ); \
    }                                                  \
    printf( "\n" );

/* typedef */
typedef struct
{
    uint32_t      millisec;
    osTimerType_t type;
    osTimerFunc_t def;
    uint8_t       Send_ID;
} t_TimerStruct;

typedef enum
{
    E_TIMER_PID_PERIOD, // 0
    E_MAX_TIMER,
} eTimerName;
/* variables */
#undef GLOBAL
#ifdef PUBLIC_C
#define GLOBAL
#else
#define GLOBAL extern
#endif

/* constants */
GLOBAL osTimerId_t g_TimerController[E_MAX_TIMER];
/* function prototypes */
GLOBAL uint32_t DWT_Delay_Init( void );
GLOBAL void     rtk_set_event( uint8_t evt_id, intptr_t evt_p1, intptr_t evt_p2, intptr_t evt_p3, osMessageQueueId_t thread_index );
GLOBAL void     start_timer( uint8_t timer_id );
GLOBAL void     timeout_callback( void* argument );
GLOBAL uint8_t  crc8( uint8_t* data, uint16_t len );

GLOBAL const t_TimerStruct g_TimerList[E_MAX_TIMER]
#ifdef PUBLIC_C
    =
        {
            [E_TIMER_PID_PERIOD] =
                {
                    1000,
                    osTimerOnce,
                    ( osTimerFunc_t ) timeout_callback,
                    EVT_PID_PERIOD_TIMEOUT,
                }, // 0
}
#endif
;
#endif
