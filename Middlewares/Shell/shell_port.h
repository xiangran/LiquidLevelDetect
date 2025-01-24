/**
 *****************************************************************************
 * @brief 	File containing example of doxygen usage for quick reference.
 * 
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 * 
 * @file 	shell_port.h
 * @author	Jackie
 * @date 	17/Mar/2023
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

#ifndef SHELL_PORT_H
#define SHELL_PORT_H

/* #include */
#include "shell.h"
/* #define */

/* typedef */

/* variables */
#undef GLOBAL
#ifdef SHELL_PORT_C
#define GLOBAL
#else
#define GLOBAL extern
#endif

/* constants */
GLOBAL Shell log_shell;
GLOBAL Log  uartLog;

/* function prototypes */
#if SHELL_USING_LOCK == 1
GLOBAL int userShellLock( Shell* shell );
GLOBAL int userShellUnlock( Shell* shell );
#endif
GLOBAL void log_shell_init(void);
GLOBAL void userShellLogWrite( char* data, short len );
#if LOG_USING_LOCK == 1
GLOBAL int userShellLogLock( Log* log );
GLOBAL int userShellLogUnlock( Log* log );
#endif
GLOBAL osThreadId_t get_shell_task_id( void );

#endif
