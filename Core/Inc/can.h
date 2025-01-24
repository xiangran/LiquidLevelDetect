/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.h
  * @brief   This file contains all the function prototypes for
  *          the can.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAN_H__
#define __CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#define BUFFER_SIZE 10
#define CAN_RX0_MAX_LEN 64

#define GROUP_CANID ( 0x1Fu )
#define CAN_BASE_ID 	0x0
#define CAN_PROTOC_PC_DEVICE ( 0xC9u )
#define CAN_PROTOC_LOG_DEVICE ( 0x77 )
#define CAN_PROTOC_DEBUG_DEVICE ( 0xC0u )
#define GROUP_ADDR ( 0xFFu )

#define CAN_FILTER_MODE_MASK_ENABLE 1
#define CAN_ID_TYPE_STD_ENABLE      1 // 1 - 标准ID, 0 - 扩展ID

#define GET_SRC_CANID( StdCanId ) BYTE( StdCanId, 1 )
#define GET_DST_CANID( StdCanId ) BYTE( StdCanId, 0 )
// 组合来源和目标CAN ID
#define ASSEMBLE_CANID( SrcStdId, TargetStdId ) ( ( SrcStdId << 8 ) | TargetStdId )

typedef union
{
    __IO uint32_t value;
    struct
    {
        uint8_t REV : 1;			//< [0]    
        uint8_t RTR : 1;			//< [1]     
        uint8_t IDE : 1;			//< [2]    
        uint32_t EXID : 18;			//< [21:3] 
        uint16_t STID : 11;			//< [31:22] 
    } Sub;
} CAN_FilterRegTypeDef;

typedef struct
{
    uint8_t    data[8];
    uint8_t    size;
    FlagStatus rxFlag;
} CAN_RecvMsg_TypeDef;

typedef struct
{
    uint8_t    data[8];
    uint8_t    size;
    FlagStatus txFlag;
} CAN_TxMsg_TypeDef;

typedef struct
{
    CAN_TxHeaderTypeDef txHandle;
    CAN_RxHeaderTypeDef rxHandle;
    CAN_RecvMsg_TypeDef rxMsg;
    CAN_TxMsg_TypeDef   txMsg;
} CAN_CommTypeDef;

#undef GLOBAL
#ifdef CAN_C
#define GLOBAL
#else
#define GLOBAL extern
#endif

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

GLOBAL CAN_HandleTypeDef hcan;
GLOBAL uint8_t           can_rx0_buffer_array_index;
GLOBAL uint8_t           can_rx0_buffer[BUFFER_SIZE][CAN_RX0_MAX_LEN];

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

GLOBAL void MX_CAN_Init(void);
GLOBAL HAL_StatusTypeDef CAN_Transmit( uint32_t tx_StdId, uint8_t* tx_data_buff, uint8_t data_size );

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __CAN_H__ */

