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
 * @file flash.h
 * \Author Jackie
 * @date 2024-01-05
 * @copyright COPYRIGHT (c) 2024
 */
#ifndef FLASH_H
#define FLASH_H

/* #include */

/* #define */
#define CONFIG_FLASH_ADDR ( ( uint32_t ) 0x0801F000 )
/* typedef */
typedef struct __attribute__( ( packed, aligned( 8 ) ) )
{
    /* data */
    float    thrs1; // method1
    float    thrs2; // method2
    uint16_t U7_R;  // 电位计 U2 的值
    uint16_t U1_R;  // 电位计 U1 的值
    uint8_t  crc8;
} LiquidDecte_TypeDef;

/* variables */
#undef GLOBAL
#ifdef FLASH_C
#define GLOBAL
#else
#define GLOBAL extern
#endif

/* constants */
GLOBAL uint32_t            noise;
GLOBAL uint16_t            calibrate_cnt;
GLOBAL LiquidDecte_TypeDef param;
/* function prototypes */
GLOBAL void              flash_init( void );
GLOBAL HAL_StatusTypeDef save_data( uint32_t address, uint32_t* data, uint32_t size );
GLOBAL void              read_data( uint32_t address, uint32_t* pBuff, uint32_t num );
#endif
