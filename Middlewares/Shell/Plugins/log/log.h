/**
 *****************************************************************************
 * @brief 	File containing example of doxygen usage for quick reference.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 * @file 	log.h
 * @author	Jackie
 * @date 	27/Apr/2023
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

#ifndef LOG_H
#define LOG_H

/* #include */

#ifdef __cplusplus
extern "C"
{
#endif /**< defined __cplusplus */

#include "shell.h"

#ifdef DEBUG
#define LOG_ENABLE 1
#else
#define LOG_ENABLE 0
#endif

#define ACK_MAX_LEN 800
#define DEBUG_MAX_LENGTH ( ACK_MAX_LEN + 50 )
#define CMD_LEN ACK_MAX_LEN

#define LOG_VERSION "1.0.1"

#define SHELL_COMPANION_ID_LOG -2

#define LOG_USING_LOCK 1
// log输出缓冲大小
#define LOG_BUFFER_SIZE DEBUG_MAX_LENGTH
// 是否使用颜色
#define LOG_USING_COLOR 1
// 允许注册的最大log对象数量
#define LOG_MAX_NUMBER 5
// 是否自动添加TAG
#define LOG_AUTO_TAG 1
// log信息结尾
#define LOG_END "\r\n"
// 设置获取系统时间戳
#define LOG_TIME_STAMP 0

#ifndef LOG_TAG
// 自定添加的TAG
#define LOG_TAG __FUNCTION__
#endif

#if LOG_USING_LOCK == 1
#define LOG_LOCK( log ) log->lock( log )
#define LOG_UNLOCK( log ) log->unlock( log )
#else
#define LOG_LOCK( log )
#define LOG_UNLOCK( log )
#endif /* LOG_USING_LOCK == 1 */

// 所有已注册的log对象
#define LOG_ALL_OBJ ( ( Log* ) -1 )

/**
 * 终端字体颜色代码
 */
#define CSI_BLACK 30
#define CSI_RED 31
#define CSI_GREEN 32
#define CSI_YELLOW 33
#define CSI_BLUE 34
// 品红
#define CSI_FUCHSIN 35
// 青色
#define CSI_CYAN 36
#define CSI_WHITE 37
// 亮黑
#define CSI_BLACK_L 90
// 亮红
#define CSI_RED_L 91
// 亮绿
#define CSI_GREEN_L 92
// 亮黄
#define CSI_YELLOW_L 93
// 亮蓝
#define CSI_BLUE_L 94
// 亮品红
#define CSI_FUCHSIN_L 95
// 亮青
#define CSI_CYAN_L 96
// 亮白
#define CSI_WHITE_L 97
// 默认
#define CSI_DEFAULT 39
// ANSI CSI指令
#define CSI( code ) "\033[" #code "m"

/**
 * log级别字符(包含颜色)
 */
#if LOG_USING_COLOR == 1
#define ERROR_TEXT CSI( 31 ) "E(%d) %s:" CSI( 39 )   /**< 错误标签 */
#define WARNING_TEXT CSI( 33 ) "W(%d) %s:" CSI( 39 ) /**< 警告标签 */
#define INFO_TEXT CSI( 32 ) "I(%d) %s:" CSI( 39 )    /**< 信息标签 */
#define DEBUG_TEXT CSI( 34 ) "D(%d) %s:" CSI( 39 )   /**< 调试标签 */
#define VERBOSE_TEXT CSI( 36 ) "V(%d) %s:" CSI( 39 ) /**< 冗余信息标签 */
#define CMD_DIAG_STRING "[%x-%d]:%s"
#else
#define ERROR_TEXT "E(%d) %s:"
#define WARNING_TEXT "W(%d) %s:"
#define INFO_TEXT "I(%d) %s:"
#define DEBUG_TEXT "D(%d) %s:"
#define VERBOSE_TEXT "V(%d) %s:"
#define CMD_DIAG_STRING "[%x-%d]:%s"
#endif

#if LOG_USING_COLOR == 1
#define memPrintHead \
    CSI( 31 )        \
    "    Offset: 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F" CSI( 39 ) "\r\n"
#define memPrintAddr CSI( 31 ) "0x%08x: " CSI( 39 )
#else
#define memPrintHead "    Offset: 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\r\n"
#define memPrintAddr "0x%08x: "
#endif

#define LOG( M, args... ) logInfo( false, args )
#define ALERT( M, args... ) logError( false, args )
#define LOG_LOCAL( M, args... ) logInfo( true, args )
#define CMD_DIAG( args... ) logDebug( true, CMD_DIAG_STRING, args )

    /**
     * @brief 日志级别定义
     *
     */
    typedef enum
    {
        LOG_NONE    = 0, // 无级别
        LOG_ERROR   = 1, // 错误
        LOG_WRANING = 2, // 警告
        LOG_INFO    = 3, // 消息
        LOG_DEBUG   = 4, // 调试
        LOG_VERBOSE = 5, // 冗余
        LOG_ALL     = 6, // 所有日志
    } LogLevel;

    typedef enum
    {
        APP_MODULE,
        QUEUE_MODULE,
        DEBUG_MODULE,
        FLASH_MODULE,
        LIQUID_MODULE,
        MEMORY_MODULE,
        SENSOR_MODULE,
        USART_MODULE,
        CMD_MODULE,
    } e_sys_module;

    /**
     * @brief log对象定义
     *
     */
    typedef struct log_def
    {
        void ( *write )( char*, short ); // 写buffer
        char     active;                 // 是否激活
        LogLevel level;                  // 日志级别
#if LOG_USING_LOCK == 1
        int ( *lock )( struct log_def* );   // log 加锁
        int ( *unlock )( struct log_def* ); // log 解锁
#endif                                      // LOG_USING_LOCK == 1
        Shell* shell;                       // 关联shell对象
    } Log;

/**
 * @brief log打印(自动换行)
 *
 * @param fmt 格式
 * @param ... 参数
 */
#define logPrintln( format, ... ) logWrite( LOG_ALL_OBJ, LOG_NONE, true, format "\r\n", ##__VA_ARGS__ )

/**
 * @brief 日志格式化输出
 *
 * @param text 消息文本
 * @param level 日志级别
 * @param fmt 格式
 * @param ... 参数
 */
#define logFormat( text, level, local, fmt, ... )                                                               \
    if ( LOG_ENABLE )                                                                                           \
    {                                                                                                           \
        logWrite( LOG_ALL_OBJ, level, local, text " " fmt "" LOG_END, PROJECT_HW_DEF, LOG_TAG, ##__VA_ARGS__ ); \
    }

/**
 * @brief 错误log输出
 *
 * @param fmt 格式
 * @param ... 参数
 */
#define logError( local, fmt, ... ) logFormat( ERROR_TEXT, LOG_ERROR, local, fmt, ##__VA_ARGS__ )

/**
 * @brief 警告log输出
 *
 * @param fmt 格式
 * @param ... 参数
 */
#define logWarning( local, fmt, ... ) logFormat( WARNING_TEXT, LOG_WRANING, local, fmt, ##__VA_ARGS__ )

/**
 * @brief 信息log输出
 *
 * @param fmt 格式
 * @param ... 参数
 */
#define logInfo( local, fmt, ... ) logFormat( INFO_TEXT, LOG_INFO, local, fmt, ##__VA_ARGS__ )

/**
 * @brief 调试log输出
 *
 * @param fmt 格式
 * @param ... 参数
 */
#define logDebug( local, fmt, ... ) logFormat( DEBUG_TEXT, LOG_DEBUG, local, fmt, ##__VA_ARGS__ )

/**
 * @brief 冗余log输出
 *
 * @param fmt 格式
 * @param ... 参数
 */
#define logVerbose( local, fmt, ... ) logFormat( VERBOSE_TEXT, LOG_VERBOSE, local, fmt, ##__VA_ARGS__ )

/**
 * @brief 断言
 *
 * @param expr 表达式
 * @param action 断言失败操作
 */
#define logAssert( expr, action )                                                            \
    if ( !( expr ) )                                                                         \
    {                                                                                        \
        logError( "\"" #expr "\" assert failed at file: %s, line: %d", __FILE__, __LINE__ ); \
        action;                                                                              \
    }
/**
 * @brief 16进制输出到所有终端
 *
 * @param base 内存基址
 * @param length 长度
 */
#define log_hex_dump_all( base, length ) logHexDump( LOG_ALL_OBJ, LOG_ALL, base, length )

/* variables */
#undef GLOBAL
#ifdef LOG_C
#define GLOBAL
#else
#define GLOBAL extern
#endif

    /* constants */

    /* function prototypes */
    GLOBAL void  Log_Init( void );
    GLOBAL void* trace_mem_malloc( char const* func, int line, size_t size, bool printLog );
    GLOBAL void  trace_mem_free( char const* func, int line, void* ptr, bool printLog );
    GLOBAL void* cplusplus_new( size_t size );
    GLOBAL void  cplusplus_free( void* ptr );
    GLOBAL void  Log_Disable( void );
    GLOBAL void  Log_Enable( void );
    GLOBAL void  Log_Print_Setting( e_sys_module vl_module, char is_output );
    GLOBAL char  Log_Need_Print( e_sys_module vl_module );
    GLOBAL void  USART_Prepare( void );
    GLOBAL char* Log_TrimNewLine( char* str );
    GLOBAL void  logRegister( Log* log, Shell* shell );
    GLOBAL void  logUnRegister( Log* log );
    GLOBAL void  logSetLevel( Log* log, LogLevel level );
    GLOBAL void  logWrite( Log* log, LogLevel level, bool local_output, const char* fmt, ... );
    GLOBAL void  logHexDump( Log* log, LogLevel level, void* base, unsigned int length );

#ifdef __cplusplus
}
#endif /**< defined __cplusplus */

#endif
