/**
 *****************************************************************************
 * @brief 	File containing example of doxygen usage for quick reference.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 * @file 	log.c
 * @author	Jackie
 * @date 	26/Apr/2023
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

#define LOG_C
#include "app_header.h"
#undef LOG_C

Log*        logList[LOG_MAX_NUMBER] = { 0 };
static char logBuffer[LOG_BUFFER_SIZE];

/*!
 * \fn     Log_Init
 * \brief
 *
 * \param  [in] void   #
 *
 * \retval void
 *
 * \Author Jackie  2022-8-07
 */
void Log_Init( void )
{
#ifdef DEBUG
    log_shell_init();
#endif
}

/*!
 * \fn     trace_mem_malloc
 * \brief
 *
 * \param  [in] char const* func   #
 * \param  [in] int line           #
 * \param  [in] size_t size        #
 * \param  [in] bool printLog      #
 *
 * \retval void*
 *
 * \Author Jackie  2022-8-07
 */
void* trace_mem_malloc( char const* func, int line, size_t size, bool printLog )
{
    void* addr = pvPortMalloc( size );

#ifdef DEBUG
    if ( false )
        logVerbose( true, "%s %d malloc %d, %x", func, line, size, addr );
#endif

    return addr;
}

/*!
 * \fn     trace_mem_free
 * \brief
 *
 * \param  [in] char const* func   #
 * \param  [in] int line           #
 * \param  [in] void* ptr          #
 * \param  [in] bool printLog      #
 *
 * \retval void
 *
 * \Author Jackie  2022-8-07
 */
void trace_mem_free( char const* func, int line, void* ptr, bool printLog )
{
#ifdef DEBUG
    if ( false )
        logVerbose( true, "%s %d free %x", func, line, ptr );
#endif

    vPortFree( ptr );
}

/*!
 * \fn     cplusplus_new
 * \brief
 *
 * \param  [in] size_t size   #
 *
 * \retval void*
 *
 * \Author Jackie  2022-10-14
 */
void* cplusplus_new( size_t size ) { return pvPortMalloc( size ); }

/*!
 * \fn     cplusplus_free
 * \brief
 *
 * \param  [in] void* ptr   #
 *
 * \retval void
 *
 * \Author Jackie  2022-10-14
 */
void cplusplus_free( void* ptr ) { vPortFree( ptr ); }

/*!
 * \fn     Log_TrimNewLine
 * \brief
 *
 * \param  [in] char* str   #
 *
 * \retval char*
 *
 * \Author Jackie  2022-8-07
 */
char* Log_TrimNewLine( char* str )
{
    char* orignal = str;

    // Trim leading space
    while ( ( unsigned char ) *str == '\r' || ( unsigned char ) *str == '\n' )
        str++;

    if ( *str == 0 ) // only newline
        return orignal;

    // Trim trailing space
    /*end = str + strlen(str) - 1;
    while(end > str && ((unsigned char)*end == '\r' || (unsigned char)*end == '\n'))) end--;

    // Write new null terminator character
    end[1] = '\0';*/

    return str;
}

#if LOG_USING_LOCK == 1
/**
 * @brief   上锁log对象
 * @param   log log对象
 */
static void logLock( Log* log )
{
    if ( log == LOG_ALL_OBJ )
    {
        for ( short i = 0; i < LOG_MAX_NUMBER; i++ )
        {
            if ( logList[i] && logList[i]->active )
            {
                if ( logList[i]->lock )
                {
                    LOG_LOCK( logList[i] );
                }
            }
        }
    }
    else if ( log->lock )
    {
        LOG_LOCK( log );
    }
}

/*!
 * \fn     logUnlock
 * \brief  解锁log对象
 *
 * \param  [in] Log* log   #
 *
 * \retval static void
 *
 * \Author Jackie  2023-3-20
 */
static void logUnlock( Log* log )
{
    if ( log == LOG_ALL_OBJ )
    {
        for ( short i = 0; i < LOG_MAX_NUMBER; i++ )
        {
            if ( logList[i] && logList[i]->active )
            {
                if ( logList[i]->unlock )
                {
                    LOG_UNLOCK( logList[i] );
                }
            }
        }
    }
    else if ( log->unlock )
    {
        LOG_UNLOCK( log );
    }
}
#endif /* LOG_USING_LOCK == 1 */

/*!
 * \fn     logRegister
 * \brief  注册log对象
 *
 * \param  [in] Log* log       #
 * \param  [in] Shell* shell   #
 *
 * \retval void
 *
 * \Author Jackie  2023-3-20
 */
void logRegister( Log* log, Shell* shell )
{
    if ( shell )
    {
        log->shell = shell;
#if SHELL_USING_COMPANION == 1
        shellCompanionAdd( shell, SHELL_COMPANION_ID_LOG, log );
#endif
    }
    for ( short i = 0; i < LOG_MAX_NUMBER; i++ )
    {
        if ( logList[i] == 0 )
        {
            logList[i] = log;
            return;
        }
    }
}

/*!
 * \fn     logUnRegister
 * \brief  注销log对象
 *
 * \param  [in] Log* log   #
 *
 * \retval void
 *
 * \Author Jackie  2023-3-20
 */
void logUnRegister( Log* log )
{
    for ( short i = 0; i < LOG_MAX_NUMBER; i++ )
    {
        if ( logList[i] == log )
        {
            logList[i] = 0;
            return;
        }
    }
}

/*!
 * \fn     logSetLevel
 * \brief  设置log日志级别
 *
 * \param  [in] Log* log         #
 * \param  [in] LogLevel level   #
 *
 * \retval void
 *
 * \Author Jackie  2023-3-20
 */
void logSetLevel( Log* log, LogLevel level )
{
    logAssert( log, return );
    log->level = level;
}
#if SHELL_USING_COMPANION == 1
SHELL_EXPORT_CMD_AGENCY( SHELL_CMD_PERMISSION( 0 ) | SHELL_CMD_TYPE( SHELL_TYPE_CMD_FUNC ) | SHELL_CMD_DISABLE_RETURN, logSetLevel, logSetLevel, set log level\r\n logSetLevel[level], ( void* ) shellCompanionGet( shellGetCurrent(), SHELL_COMPANION_ID_LOG ), p1 );
#else
SHELL_EXPORT_CMD( SHELL_CMD_PERMISSION( 0 ) | SHELL_CMD_TYPE( SHELL_TYPE_CMD_FUNC ), logSetLevel, logSetLevel, set log level\r\n logSetLevel[log][level] );
#endif /** SHELL_USING_COMPANION == 1 */

/*!
 * \fn     logWriteBuffer
 * \brief  log写buffer
 *
 * \param  [in] Log* log         #
 * \param  [in] LogLevel level   #
 * \param  [in] char* buffer     #
 * \param  [in] short len        #
 *
 * \retval static void
 *
 * \Author Jackie  2023-3-20
 */
static void logWriteBuffer( Log* log, LogLevel level, char* buffer, short len )
{
#if LOG_USING_LOCK == 1
    logLock( log );
#endif /* LOG_USING_LOCK == 1 */
    if ( log == LOG_ALL_OBJ )
    {
        for ( short i = 0; i < LOG_MAX_NUMBER; i++ )
        {
            if ( logList[i] && logList[i]->active && logList[i]->level >= level )
            {
                logList[i]->write( logBuffer, len );
            }
        }
    }
    else if ( log && log->active && log->level >= level )
    {
        log->write( logBuffer, len );
    }
#if LOG_USING_LOCK == 1
    logUnlock( log );
#endif /* LOG_USING_LOCK == 1 */
}

/*!
 * \fn     logWrite
 * \brief  格式化写入数据
 *
 * \param  [in] Log* log          #
 * \param  [in] LogLevel level    log级别#
 * \param  [in] const char* fmt   #
 * \param  [in] ...               #
 *
 * \retval void
 *
 * \Author Jackie  2023-3-20
 */
void logWrite( Log* log, LogLevel level, bool local_output, const char* fmt, ... )
{
    // char  p_out[9] = { 0 };
    short len;

#if LOG_USING_LOCK == 1
    logLock( log );
#endif /* LOG_USING_LOCK == 1 */

    va_list ap;
    va_start( ap, fmt );

    memset( logBuffer, 0, LOG_BUFFER_SIZE );
    // rtc_printCurrentTime( p_out, 9 );
    if ( osKernelGetTickCount() < 10000000 )
    {
        len = snprintf( logBuffer, LOG_BUFFER_SIZE, "[%5lu.%3u][%s] ", osKernelGetTickCount() / 1000, osKernelGetTickCount() % 1000, vTaskName() );
    }
    else
    {
        len = snprintf( logBuffer, LOG_BUFFER_SIZE, "[%9lu][%s] ", osKernelGetTickCount(), vTaskName() );
    }
    len += vsnprintf( logBuffer + len, LOG_BUFFER_SIZE - len, fmt, ap );
    va_end( ap );

    logWriteBuffer( log, level, logBuffer, len );
#if LOG_USING_LOCK == 1
    logUnlock( log );
#endif /* LOG_USING_LOCK == 1 */
}

/**
 * @brief 16进制输出
 *
 * @param log log对象
 * @param level 日志级别
 * @param base 内存基址
 * @param length 长度
 */
void logHexDump( Log* log, LogLevel level, void* base, unsigned int length )
{
    unsigned char* address;
    unsigned int   len;
    unsigned int   printLen = 0;

    if ( length == 0 || ( log != LOG_ALL_OBJ && log->level < level ) )
    {
        return;
    }
#if LOG_USING_LOCK == 1
    logLock( log );
#endif /* LOG_USING_LOCK == 1 */
    len = snprintf( logBuffer, LOG_BUFFER_SIZE - 1, "addr 0x%08x, size: %d:\r\n%s", ( unsigned int ) base, length, memPrintHead );
    logWriteBuffer( log, level, logBuffer, len );

    len = length;

    address = ( unsigned char* ) ( ( unsigned int ) base & ( ~0x0000000F ) );
    length += ( unsigned int ) base - ( unsigned int ) address;
    length = ( length + 15 ) & ( ~0x0000000F );

    while ( length )
    {
        printLen += sprintf( logBuffer + printLen, memPrintAddr, ( unsigned int ) address );
        for ( int i = 0; i < 16; i++ )
        {
            if ( ( unsigned int ) ( address + i ) < ( unsigned int ) base || ( unsigned int ) ( address + i ) >= ( unsigned int ) base + len )
            {
                logBuffer[printLen++] = ' ';
                logBuffer[printLen++] = ' ';
                logBuffer[printLen++] = ' ';
            }
            else
            {
                printLen += sprintf( logBuffer + printLen, "%02x ", *( address + i ) );
            }
        }
        logBuffer[printLen++] = '|';
        logBuffer[printLen++] = ' ';
        for ( int i = 0; i < 16; i++ )
        {
            if ( ( unsigned int ) ( address + i ) < ( unsigned int ) base || ( unsigned int ) ( address + i ) >= ( unsigned int ) base + len )
            {
                logBuffer[printLen++] = ' ';
            }
            else
            {
                if ( *( address + i ) >= 32 && *( address + i ) <= 126 )
                {
                    printLen += sprintf( logBuffer + printLen, "%c", *( address + i ) );
                }
                else
                {
                    logBuffer[printLen++] = '.';
                }
            }
        }
        logBuffer[printLen++] = ' ';
        logBuffer[printLen++] = '|';
        logBuffer[printLen++] = '\r';
        logBuffer[printLen++] = '\n';
        logWriteBuffer( log, level, logBuffer, printLen );
        address += 16;
        length -= 16;
        printLen = 0;
    }
#if LOG_USING_LOCK == 1
    logUnlock( log );
#endif /* LOG_USING_LOCK == 1 */
}

#if SHELL_USING_COMPANION == 1
SHELL_EXPORT_CMD_AGENCY( SHELL_CMD_PERMISSION( 0 ) | SHELL_CMD_TYPE( SHELL_TYPE_CMD_FUNC ) | SHELL_CMD_DISABLE_RETURN, hexdump, logHexDump, hex dump\r\n hexdump[base][len], ( void* ) shellCompanionGet( shellGetCurrent(), SHELL_COMPANION_ID_LOG ), LOG_NONE, ( void* ) p1, ( unsigned int ) p2 );
#else
SHELL_EXPORT_CMD( SHELL_CMD_PERMISSION( 0 ) | SHELL_CMD_TYPE( SHELL_TYPE_CMD_FUNC ) | SHELL_CMD_DISABLE_RETURN, hexdump, logHexDump, hex dump\r\n hexdump[log][level][base][len] );
#endif /** SHELL_USING_COMPANION == 1 */

#if SHELL_USING_COMPANION == 1
/*!
 * \fn     logSwitchLevel
 * \brief
 *
 * \param  [in] Shell* shell   #
 *
 * \retval void
 *
 * \Author Jackie  2023-3-20
 */
void logSwitchLevel( Shell* shell )
{
    Log* log = shellCompanionGet( shell, SHELL_COMPANION_ID_LOG );
    SHELL_ASSERT( log, return );
    log->level = ( LogLevel ) ( log->level >= LOG_ALL ? LOG_NONE : ( log->level + 1 ) );
    logPrintln( "set log level: %d", log->level );
}
SHELL_EXPORT_KEY( SHELL_CMD_PERMISSION( 0 ), 0x04000000, logSwitchLevel, switch log level );
#endif /** SHELL_USING_COMPANION == 1 */
