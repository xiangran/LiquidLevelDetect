/**
 *****************************************************************************
 * @brief 	File containing example of doxygen usage for quick reference.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 * @file 	app.h
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

#ifndef APP_H
#define APP_H

/* #include */

/* #define */
#define APP_QUEUE_MAX_NO 20
#define METHOD1_THRS ( 0.2 )
#define METHOD2_THRS ( 0.2 )
#define U7R ( 240u ) // ( 256 - U7R ) / 256 * 50000 Ω + 60 = 9420
#define SINE_WAVE_PERIOD ( 300u )
#define TEST_BUFFER_SIZE ( 1000u )
// 1 阈值/斜率
#define DETECT_METHOD ( 1 )

/* typedef */
// 液面探测ADC采样数据集合
typedef struct
{
    uint16_t write_index;
    uint16_t read_index;
} Liquid_AD_TypeDef;

/* variables */
#undef GLOBAL
#ifdef APP_C
#define GLOBAL
#else
#define GLOBAL extern
#endif

/* constants */
GLOBAL osMessageQueueId_t app_queue_handle;
GLOBAL ring_buffer        liquid_ad_val;
GLOBAL uint32_t           adc_value_buffer[SINE_WAVE_PERIOD];
GLOBAL __IO bool          read_noise;
GLOBAL bool               liquid_level_detect_flag;

/* function prototypes */
GLOBAL void          detect_liquid_level_task( void* pvParameters );
GLOBAL void          adc_task( void* pvParameters );
GLOBAL void          app_variable_init( void );
GLOBAL reset_cause_t get_Reset_Cause( void );
GLOBAL const char*   reset_Cause_ToString( reset_cause_t reset_cause );
#endif
