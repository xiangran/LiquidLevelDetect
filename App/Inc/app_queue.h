/**
 *****************************************************************************
 * @brief 	File containing example of doxygen usage for quick reference.
 * 
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 * 
 * @file 	app_queue.h
 * @author	Jackie
 * @date 	21/Oct/2022
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

#ifndef APP_QUEUE_H
#define APP_QUEUE_H

/* #include */

/* #define */

/* typedef */
typedef struct
{
    uint8_t size;
    uint8_t dataStream;
} payload_packet_t;

/* variables */
#undef GLOBAL
#ifdef APP_QUEUE_C
#define GLOBAL
#else
#define GLOBAL extern
#endif

/* constants */
GLOBAL List* data_list;

/* function prototypes */
GLOBAL bool IsEmpty( void );
GLOBAL void EnQueue( void* pData, uint16_t length, bool highPriority );
GLOBAL void* TopQueue( void );
GLOBAL void* DeQueue( void );

#endif


