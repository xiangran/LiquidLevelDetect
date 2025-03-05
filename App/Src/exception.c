/**
 *****************************************************************************
 * @brief 	File containing example of doxygen usage for quick reference.
 * 
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 * 
 * @file 	exception.c
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

#define EXCEPTION_C

/* #include */
#include "app_header.h"
#undef EXCEPTION_C

/* #define */

/* typedef */

/* static variables */

/* static constants */

/* static function prototypes */
uint8_t protoc_error( uint16_t MotorSelect, Command_ErrCode_TypeDef ErrorID, uint8_t TargetAddr, uint16_t Function, Error_Motor_OpterationDef MotorStopOpt ) { return 0; }

