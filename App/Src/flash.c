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
 * @file flash.c
 * \Author Jackie
 * @date 2024-01-05
 * @copyright COPYRIGHT (c) 2024
 */
#define FLASH_C

/* #include */
#include "app_header.h"
#undef FLASH_C
/* #define */

/* typedef */

/* static variables */

/* static constants */

/* static function prototypes */
void flash_init()
{
    uint8_t crc;
    read_data( CONFIG_FLASH_ADDR, ( uint32_t* ) &param, sizeof( LiquidDecte_TypeDef ) / 4 );
    crc = crc8( ( uint8_t* ) &param, offsetof( LiquidDecte_TypeDef, crc8 ) );

    if ( crc == param.crc8 )
    {
        LOG( APP_MODULE, "read param success, thrs1:%f, thrs2:%f", ( double ) param.thrs1, ( double ) param.thrs2 );
    }
    else
    {
        param.thrs1 = METHOD1_THRS;
        param.thrs2 = METHOD2_THRS;
        param.U7_R  = U7R;
        LOG( APP_MODULE, "read param fail, reset thrs: %f, %f", ( double ) param.thrs1, ( double ) param.thrs2 );
    }
}

/**
 * \brief Get the Page object
 * \param Addr
 * \retval uint32_t
 * @date 2025-01-17
 * \Author Jackie
 */
static uint32_t GetPage( uint32_t Addr )
{
    return ( Addr - FLASH_BASE ) / FLASH_PAGE_SIZE;
    ;
}

/**
 * \brief
 * \param address
 * \param data
 * @date 2024-01-05
 * \Author Jackie
 */
HAL_StatusTypeDef save_data( uint32_t address, uint32_t* data, uint32_t size )
{
    HAL_FLASH_Unlock();

    FLASH_EraseInitTypeDef EraseInitStruct;
    EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.Page      = GetPage( address );
    EraseInitStruct.NbPages   = GetPage( address + size ) - EraseInitStruct.Page + 1;

    uint32_t PageError;
    if ( HAL_FLASHEx_Erase( &EraseInitStruct, &PageError ) != HAL_OK ) // Erase the Page Before a Write Operation
    {
        HAL_FLASH_Lock();
        return HAL_ERROR;
    }

    for ( int i = 0; i < size; i++ )
    {
        HAL_FLASH_Program( FLASH_TYPEPROGRAM_DOUBLEWORD, address + 8 * i, ( uint64_t ) data[i] );
    }

    HAL_FLASH_Lock();
    return HAL_OK;
}

/**
 * \brief
 * \param Address
 * \retval uint32_t
 * @date 2024-01-05
 * \Author Jackie
 */
void read_data( uint32_t address, uint32_t* pBuff, uint32_t num )
{
    for ( uint32_t i = 0; i < num; i++ )
    {
        *pBuff++ = *( __IO uint32_t* ) ( address + i * 4 );
    }
}