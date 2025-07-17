/**
 *****************************************************************************
 * @brief 	File containing example of doxygen usage for quick reference.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 * @file 	shell_port.c
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

#define SHELL_PORT_C

/* #include */
#include "app_header.h"
#undef SHELL_PORT_C
/* #define */

/* typedef */

/* static variables */
char shellBuffer[512];
/** TX buffer for USB, RX buffer for UART */
#if ( SHELL_USING_LOCK == 1 )
osMutexId_t shellMutex;
#endif
#if ( LOG_USING_LOCK == 1 )
osMutexId_t logMutex;
#endif
osThreadId_t shellThread;

const osMutexAttr_t shellMutex_attr = { "shellMutex", osMutexRecursive, NULL, NULL };
const osMutexAttr_t logMutex_attr   = { "logMutex", osMutexRecursive, NULL, NULL };

static const osThreadAttr_t log_task_attr = {
    .name       = "SHELL_LOG",
    .priority   = ( osPriority_t ) osPriorityAboveNormal,
    .stack_size = 1200,
};

/* static constants */

/* static function prototypes */
/*!
 * \fn     userShellWrite
 * \brief
 *
 * \param  [in] char *data           #
 * \param  [in] unsigned short len   #
 *
 * \retval short
 *
 * \Author Jackie  2023-3-17
 */
short userShellWrite( char* data, unsigned short len )
{
    HAL_UART_Transmit( &huart3, ( const uint8_t* ) data, len, HAL_MAX_DELAY );
    return len;
}

/*!
 * \fn     userShellRead
 * \brief
 *
 * \param  [in] char *data           #
 * \param  [in] unsigned short len   #
 *
 * \retval short
 *
 * \Author Jackie  2023-3-17
 */
short userShellRead( char* data, unsigned short len )
{
    uint32_t uart_data = 0;

    if ( ring_buffer_data_num( &log_rx_ringbuffer ) > 0 && len == 1 )
    {
        ring_buffer_read( &log_rx_ringbuffer, &uart_data, len );
        *data = ( char ) uart_data;
        return len;
    }
    else
    {
        return 0;
    }
}

#if SHELL_USING_LOCK == 1
/*!
 * \fn     userShellLock
 * \brief
 *
 * \param  [in] Shell *shell   #
 *
 * \retval int
 *
 * \Author Jackie  2023-3-17
 */
int userShellLock( Shell* shell )
{
    osMutexAcquire( shellMutex, osWaitForever );
    return 0;
}

/*!
 * \fn     userShellUnlock
 * \brief
 *
 * \param  [in] Shell *shell   #
 *
 * \retval int
 *
 * \Author Jackie  2023-3-17
 */
int userShellUnlock( Shell* shell )
{
    osMutexRelease( shellMutex );
    return 0;
}
#endif

/*!
 * \fn     userShellInit
 * \brief
 *
 * \param  [in] void   #
 *
 * \retval void
 *
 * \Author Jackie  2023-3-17
 */
void log_shell_init( void )
{
    log_shell.write = userShellWrite;
    log_shell.read  = userShellRead;

#if SHELL_USING_LOCK == 1
    shellMutex       = osMutexNew( &shellMutex_attr );
    log_shell.lock   = userShellLock;
    log_shell.unlock = userShellUnlock;
#endif

    shellInit( &log_shell, shellBuffer, 512 );
    if ( ( shellThread = osThreadNew( shellTask, &log_shell, &log_task_attr ) ) == NULL )
    {
        printf( "shell task creat failed" );
        return;
    }

    uartLog.write = userShellLogWrite;
#if LOG_USING_LOCK == 1
    logMutex       = osMutexNew( &logMutex_attr );
    uartLog.lock   = userShellLogLock;
    uartLog.unlock = userShellLogUnlock;
#endif
    uartLog.active = true;
    uartLog.level  = LOG_ALL;
    logRegister( &uartLog, &log_shell );
}

/*!
 * \fn     userShellLogWrite
 * \brief
 *
 * \param  [in] char* data           #
 * \param  [in] unsigned short len   #
 *
 * \retval void
 *
 * \Author Jackie  2023-3-18
 */
void userShellLogWrite( char* data, short len )
{
    if ( uartLog.shell )
    {
        shellWriteEndLine( uartLog.shell, data, len );
    }
}

#if LOG_USING_LOCK == 1
/*!
 * \fn     userShellLogLock
 * \brief
 *
 * \param  [in] Log* log   #
 *
 * \retval int
 *
 * \Author Jackie  2023-3-22
 */
int userShellLogLock( Log* log )
{
    osMutexAcquire( logMutex, osWaitForever );
    // osKernelLock();
    return 0;
}

/*!
 * \fn     userShellLogUnlock
 * \brief
 *
 * \param  [in] Log* log   #
 *
 * \retval int
 *
 * \Author Jackie  2023-3-22
 */
int userShellLogUnlock( Log* log )
{
    osMutexRelease( logMutex );
    // osKernelUnlock();
    return 0;
}
#endif

/*!
 * \fn     get_shell_task_id
 * \brief
 *
 *
 * \retval osThreadId_t
 *
 * \Author Jackie  2023-4-27
 */
osThreadId_t get_shell_task_id() { return shellThread; }
