/**
 *****************************************************************************
 * @brief 	File containing example of doxygen usage for quick reference.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 * @file 	app_command.h
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

#ifndef APP_COMMAND_H
#define APP_COMMAND_H

/* #include */

/* #define */
#define NTC_QUEUE_MAX_NO 20
#define CMD_RESPONSE_LEN ( 80u )
#define MSG_HDR 10 // header size
#define CMD_BODY_LEN 256
#define CMD_CTX_LEN ( CMD_BODY_LEN + MSG_HDR )
#define CMD_ITEM_NUM ( 126 )
#define BUFFER_SIZE 10
#define CAN_RX0_MAX_LEN 64

#define GROUP_CANID ( 0x1Fu )
#define CAN_BASE_ID 0x0
#define CAN_PROTOC_PC_DEVICE ( 0xC9u )
#define CAN_PROTOC_LOG_DEVICE ( 0x77 )
#define CAN_PROTOC_DEBUG_DEVICE ( 0xC0u )
#define GROUP_ADDR ( 0xFFu )
#define LOOK_UP_TABLE_ELEMENTS ( 166 )

/* typedef */
typedef enum // 错误码
{
    MERR0_NONEERR                         = 0,   // 没有错误
    MERR1_RESET_ERR1                      = 1,   // 复位错误1，第一次等待静止失败
    MERR2_RESET_ERR2                      = 2,   // 复位错误2，等待电机出光耦失败
    MERR3_RESET_ERR3                      = 3,   // 复位错误3，第二次等待静止失败
    MERR4_RESET_ERR4                      = 4,   // 复位错误4，第三次等待静止失败
    MERR5_STANDSTILL_OVERTIME             = 5,   // 电机静止超时
    MERR6_POSITION_REACHFAIL              = 6,   // 没到达目标位置
    MERR7_LEFTSWITCH_ACTIVE               = 7,   // 左参考开关误触发
    MERR8_RIGHTSWITCH_ACTIVE              = 8,   // 右参考开关误触发
    MERR9_CLEANTIMEOVER_FAIL              = 9,   // 清洗超时
    MERR10_MOTOR_STANDSTILL_FAIL          = 10,  // 电机静止失败
    MERR11_DRIVER_ERROR                   = 11,  // 驱动错误指示
    MERR12_MOTOR_STALLING                 = 12,  // 电机发生堵转
    MERR13_MOTORSTART_FAIL                = 13,  // 电机启动失败
    MERR14_MOTOR_RAMPMODESET_FAIL         = 14,  // 电机工作模式设置失败
    MERR15_RESET_FAIL                     = 15,  // 复位失败
    MERR16_MISSSETP                       = 16,  // 发生丢步
    MERR17_WAITSTANSTILL_FAIL             = 17,  // 电机启动时，等待静止失败
    MERR18_SPEEDRUNTOZERO_FAIL            = 18,  // 按照速度模式运动到零点超时
    MERR19_LEFTSWITCH_OPTFAILED           = 19,  // 左参考开关操作失败
    MERR20_CMDPARA_FAILED                 = 20,  // 指令携带参数异常
    MERR21_CMDADDR_FAILED                 = 21,  // 指令地址异常
    MERR22_MOTORSTATUSCHECK_FAILED        = 22,  // 电机运行检查失败
    MERR23_MOTORCURRENTSET_FAILED         = 23,  // 电机电流设置失败
    MERR24_MOTORCURRENTSET_OVER           = 24,  // 电机电流设置超出范围
    MERR25_MOTOROPT_HALERR                = 25,  // 操作电机时返回hal异常，通常是应为spi或者RS485通讯异常
    MERR26_SNEEDLEZ_SYNCFAIL              = 26,  // 样本针z轴同步失败
    MERR27_RNEEDLEZ_SYNCFAIL              = 27,  // 试剂针z轴同步失败
    MERR28_DNEEDLEZ_SYNCFAIL              = 28,  // 检测针z轴同步失败
    MERR29_MANIPULATOR_SYNCFAIL           = 29,  // 机械手同步失败
    MERR30_SRACKX_SYNCFAIL                = 30,  // 样本架X轴同步失败
    MERR31_SAMPLERACKQUERY_FAIL           = 31,  // 样本架状态查询失败
    MERR32_OPTERRORMOTOR_FAIL             = 32,  // 操作错误电机
    MERR33_RS485_NONEECHO                 = 33,  // RS485电机无响应
    MERR34_RS485_ECHOINVALID              = 34,  // RS485电机响应数据错误
    MERR35_FUNCTION_PARAERR               = 35,  // 函数形参参数错误
    MERR36_RGRIPMOTOR_GRIPFAIL            = 36,  // 开盖夹爪电机夹取失败
    MERR37_MAINDIRVER_COMMUNICATE_FASILED = 37,  // 主控板和驱动板通信错误
    MERR38_INVALID_PROTOCOL_TAIL          = 38,  // 接收到非法协议报尾
    MERR39_INVALID_PROTOCOL_CRC           = 39,  // 接收到非法CRC校验
    MERR40_INVALID_PROTOCOL_HEAD          = 40,  // 接收到非法协议头部
    MERR41_INVALID_PROTOCOL_LEN           = 41,  // 接收到非法协议长度
    MERR42_RGRIPMOTOR_RESETFAIL           = 42,  // 开盖夹爪电机复位失败
    MERR43_INTERNEL_ERROR                 = 43,  // 程序内部错误
    WARN256_SRACK_FULL                    = 256, // 样本架已满警告
    WARN257_NO_ACK                        = 257, // 此命令不需要在本驱动板上处理
} Command_ErrCode_TypeDef;

typedef enum
{
    CMD_RST = 0x01,
    CMD_INIT_SYNC,
    CMD_MAINBOARD_VERSION,
    CMD_DRV1_VERSION,
    CMD_DRV2_VERSION,
    CMD_DRV3_VERSION,
    CMD_DRV4_VERSION,
    CMD_DRV5_VERSION,
    CMD_LIUDETECT1_VERSION,
    CMD_LIUDETECT2_VERSION = 0x0a,
    CMD_TIMESTAMP_SYNC     = 0x0b,

    // 试剂盘模块操作
    CMD_RENT_SCANCODE = 0x0101,
    CMD_RENT_SINGLE_SCANCODE,
    CMD_RTRAY_REAGENT_POS,
    CMD_REAGENT_INFO_WRITE,
    CMD_REAGENT_INFO_READ,
    CMD_REAGENT_TRAY_FASTRST,
    CMD_REAGENT_TRAY_MIX,
    CMD_DILUENT_INFO_WRITE,
    CMD_DILUENT_INFO_READ,
    CMD_RTRAY_BUTTON_EVENT,

    // 孵育盘模块操作
    CMD_POWERON_GRAB_CUP = 0x0201,
    CMD_POWERON_ADD_CUP,
    CMD_POWERON_INCUADD_CUP,
    CMD_POWERON_THROW_CUP,
    CMD_POWERON_INCUTHROW_CUP,
    CMD_POWERON_DETECT_CUP,
    CMD_POWERON_INCUDETECT_CUP,
    CMD_INCU_CUP_TEST,
    CMD_INCU_CUP_TEST_POS,

    // 耗材区模块操作
    CMD_SUPPLY_CUP_TEST = 0x0301,
    CMD_SUPPLY_CUP_INFO_NOTICE,
    CMD_SUPPLY_AREA_EVALUE,
    CMD_TAKE_CUP_TO_SUPPLY_AREA,

    // 进样模块操作
    CMD_SCANCODE = 0x0401,
    CMD_PUT_SAMPLE,
    CMD_SAMPLE_COMPLETE,
    CMD_SAMPLE_RACK_STATUS_QUERY,

    // LED
    CMD_SRACK_STATUS_LED = 0x0501,
    CMD_WASTEBIN_STATUS_LED,
    CMD_FUNCTION_LED,
    CMD_WAITING_LED,
    CMD_STOP_LED,
    CMD_MICROSCOPE_LED,
    CMD_RTRAY_FUNCTION_LED,
    CMD_RTRAY_WAITING_LED,
    CMD_RTRAY_STOP_LED,

    // 周期任务模块
    CMD_SNEEDLE_PICKUP            = 0x0701,
    CMD_SNEEDLE_DISPENSE          = 0x0702,
    CMD_SNEEDLE_CLEAN             = 0x0703,
    CMD_SAMPLE_UNLOCKLID          = 0x0704,
    CMD_SAMPLE_CLOSELID           = 0x0705,
    CMD_INCU_SLOAD_POS            = 0x0706,
    CMD_RNEEDLE_PICKUP1           = 0x0707,
    CMD_RNEEDLE_DISPENSE1         = 0x0708,
    CMD_RNEEDLE_CLEAN1            = 0x0709,
    CMD_INCU_R1_POS               = 0x070A,
    CMD_RTRAY_R1_POS              = 0x070B,
    CMD_INCU_MIXR1                = 0x070C,
    CMD_RNEEDLE_PICKUP2           = 0x070D,
    CMD_RNEEDLE_DISPENSE2         = 0x070E,
    CMD_RNEEDLE_CLEAN2            = 0x070F,
    CMD_INCU_R2_POS               = 0x0710,
    CMD_RTRAY_R2_POS              = 0x0711,
    CMD_INCU_MIXR2                = 0x0712,
    CMD_INCU_DETECT_POS           = 0x0713,
    CMD_DNEEDLE_PICKUP            = 0x0714,
    CMD_DNEEDLE_DISPENSE          = 0x0715,
    CMD_DNEEDLE_CLEAN             = 0x0716,
    CMD_TAKE_PICTURE              = 0x0717,
    CMD_GRAB_CUP                  = 0x0718,
    CMD_INCU_ADDCUP_POS           = 0x0719,
    CMD_MANI_ADDCUP               = 0x071A,
    CMD_INCU_THROWCUP_POS         = 0x071B,
    CMD_MANI_THROWCUP             = 0x071C,
    CMD_TAKE_PICTURE_BG           = 0x071D,
    CMD_RNEEDLE_PICKUP_DILUENT1   = 0x071E,
    CMD_RNEEDLE_DISPENSE_DILUENT1 = 0x071F,
    CMD_RNEEDLE_CLEAN_DILUENT1    = 0x0720,
    CMD_RTRAY_DILUENT1_POS        = 0x0721,
    CMD_RNEEDLE_PICKUP_DILUENT2   = 0x0722,
    CMD_RNEEDLE_DISPENSE_DILUENT2 = 0x0723,
    CMD_RNEEDLE_CLEAN_DILUENT2    = 0x0724,
    CMD_RTRAY_DILUENT2_POS        = 0x0725,
    CMD_RTRAY_MIX_OPT             = 0x0726,
    CMD_SNEEDLE_WAITPICKDILUENT   = 0x0727,
    CMD_SNEEDLE_PICKDILUENT       = 0x0728,
    CMD_MICROSCOPE_HMOVE_POS_CMD  = 0x0729,

    // 测试
    CMD_MOTOR_TEST = 0x0801,

    // 温度
    CMD_TEMP_INFO = 0x0901,
    CMD_TEMP_CTRL,
    CMD_TEMP_CTRLINFO,
    CMD_TEMP_TEST,

    // 三针调试模块
    CMD_SNEEDLE_DCLEAN = 0x0a01,
    CMD_RNEEDLE_DCLEAN,
    CMD_DNEEDLE_DCLEAN,
    CMD_DNEEDLE_OUTLIQUID,
    CMD_SNEEDLE_LEAK_TEST,
    CMD_RNEEDLE_LEAK_TEST,
    CMD_DNEEDLE_LEAK_TEST,
    CMD_SLIQUID_DETECT_TEST,
    CMD_RLIQUID_DETECT_TEST,
    CMD_SNEEDLE_CIRCUIT_FILLING,
    CMD_RNEEDLE_CIRCUIT_FILLING,
    CMD_DNEEDLE_CIRCUIT_FILLING,

    // 流通室漂白/清洗
    CIRCUL_ROOM_BLEACH_CMD = 0x0b01,

    // 电机参数位置设置
    CMD_MOTOR_POS_SET = 0x0c01,
    CMD_MOTOR_POS_GOTO,
    CMD_MOTOR_POS_RELATIVE_MOVE,
    CMD_MOTOR_POS_GET,
    CMD_MOTOR_POS_CONFIG_QUERY,
    CMD_MOTOR_POS_CURRENT_QUERY,

    // 传感器状态
    CMD_WASTEBIN_DETECT = 0x0d01,
    CMD_CLEAN_FLUID_DETECT,
    CMD_WASTE_FLUID_DETECT,
    CMD_SENSOR_STATUS_REPORT,
    CMD_BARCODE_REPORT,

    // 气泡调整模块
    CMD_MICROSCOPE_BUBBLEVERIFY_PICK = 0x0e01,
    CMD_MICROSCOPE_BUBBLEVERIFY_CLEAN,

    CMD_CLEAN_FLUID_INFO_WRITE = 0x0f01,
    CMD_CLEAN_FLUID_INFO_READ,
    CMD_CLEAN_FLUID_CURRENT_QUERY,
    CMD_CLEAN_FLUID_CURRENT_CLEAR,

    // OTA
    CMD_BOARD_BOOT_UPDATE = 0x1001,

    CMD_NEEDLE_Z_ON_POSITION = 0x1101,
    CMD_CONFIG_PUMP_PWM      = 0x1102,
    CMD_POS_CONFIG_CMDLINE   = 0x1103,
} Uplink_Protoc_Function_TypeDef;

typedef struct
{
    Uplink_Protoc_Function_TypeDef cmd;
    uint8_t                        src_addr;
    uint8_t                        data[CMD_BODY_LEN];
} CmdCtx_TypeDef;

typedef struct
{
    Command_ErrCode_TypeDef   error;
    Error_Motor_OpterationDef error_opts;
    uint16_t                  motor_id;
    int                       resp_len;
    uint8_t                   resp[CMD_RESPONSE_LEN];
} CmdErrorOpts_TypeDef;

typedef struct
{
    // 协议中的命令
    uint32_t cmd;
    // 对应的驱动板
    uint16_t drv_id;
    // 对应的驱动板
    uint16_t src_id;
    intptr_t dynamic_cmd;
    bool     print_cmd_support;
    bool     dynamic_cmd_support;
} Protoc_TypeDef;

typedef struct
{
    int    temperature;
    double resistance;
} NTC10K_B3950_TypeDef;
/* variables */
#undef GLOBAL
#ifdef APP_COMMAND_C
#define GLOBAL
#else
#define GLOBAL extern
#endif

/* constants */
GLOBAL osMutexId_t         adc1_Semaphore;
GLOBAL const osMutexAttr_t adc1_Mutex_attr
#ifdef APP_COMMAND_C
    =
        {
            "myThreadMutex", osMutexPrioInherit | osMutexRecursive,
            // attr_bits
            NULL,
            // memory for control block
            0U
            // size for control block
}
#endif
;

GLOBAL NTC10K_B3950_TypeDef lookUpTable[LOOK_UP_TABLE_ELEMENTS]
#ifdef APP_COMMAND_C
    =
        {
            { 125, 332.07 }, { 124, 340.96 }, { 123, 350.12 }, { 122, 359.57 }, { 121, 369.32 }, { 120, 379.37 }, { 119, 389.77 }, { 118, 400.5 }, { 117, 411.58 }, { 116, 423.02 }, { 115, 434.84 }, { 114, 447.04 }, { 113, 459.65 }, { 112, 472.68 }, { 111, 486.14 }, { 110, 500.05 }, { 109, 514.38 }, { 108, 529.2 }, { 107, 544.5 }, { 106, 560.32 }, { 105, 576.67 }, { 104, 593.58 }, { 103, 611.06 }, { 102, 629.13 }, { 101, 647.83 }, { 100, 667.17 }, { 99, 687.22 }, { 98, 707.99 }, { 97, 729.49 }, { 96, 751.76 }, { 95, 774.82 }, { 94, 798.71 }, { 93, 823.47 }, { 92, 849.12 }, { 91, 875.7 },  { 90, 903.26 }, { 89, 931.76 },  { 88, 961.31 },  { 87, 991.94 },  { 86, 1023.7 },  { 84, 1090.8 },  { 85, 1056.6 },  { 83, 1126.2 },  { 82, 1163 },    { 81, 1201.2 },  { 80, 1240.8 },  { 79, 1282.1 },  { 78, 1325 },    { 77, 1369.5 },  { 76, 1415.9 },  { 75, 1464 },    { 74, 1514.1 },  { 73, 1566.1 },  { 72, 1620.3 },  { 71, 1676.6 }, { 70, 1735.2 },
            { 69, 1796.2 },  { 68, 1859.5 },  { 67, 1925.5 },  { 66, 1994.2 },  { 65, 2065.7 },  { 64, 2140.1 },  { 63, 2217.7 },  { 62, 2298.5 }, { 61, 2382.7 },  { 60, 2470.4 },  { 59, 2562.1 },  { 58, 2657.6 },  { 57, 2757.3 },  { 56, 2861.3 },  { 55, 2969.8 },  { 54, 3083 },    { 53, 3201.2 },  { 52, 3324.7 }, { 51, 3453.6 }, { 50, 3588.2 },  { 49, 3728.8 },  { 48, 3875.7 },  { 47, 4029.2 },  { 46, 4189.7 },  { 45, 4357.4 },  { 44, 4532.9 },  { 43, 4716.4 }, { 42, 4908.3 }, { 41, 5109.2 }, { 40, 5319.4 }, { 39, 5539.4 }, { 38, 5769.8 }, { 37, 6011.1 }, { 36, 6263.9 }, { 35, 6528.7 }, { 34, 6806.2 }, { 33, 7097 },    { 32, 7402 },    { 31, 7721.8 },  { 30, 8057.2 },  { 29, 8409.1 },  { 28, 8778.3 },  { 27, 9165.9 },  { 26, 9572.8 },  { 25, 10000 },   { 24, 10449 },   { 23, 10920 },   { 22, 11415 },   { 21, 11936 },   { 20, 12483 },   { 19, 13058 },   { 18, 13662 },   { 17, 14297 },   { 16, 14965 },   { 15, 15667 },  { 14, 16405 },
            { 13, 17181 },   { 12, 17997 },   { 11, 18856 },   { 10, 19760 },   { 9, 20716 },    { 8, 21724 },    { 7, 22788 },    { 6, 23910 },   { 5, 25095 },    { 4, 26346 },    { 3, 27669 },    { 2, 29066 },    { 1, 30544 },    { 0, 32108 },    { -1, 33738 },   { -2, 35456 },   { -3, 37267 },   { -4, 39175 },  { -5, 41185 },  { -6, 43303 },   { -7, 45535 },   { -8, 47885 },   { -9, 50360 },   { -10, 52966 },  { -11, 55736 },  { -12, 58659 },  { -13, 61745 }, { -14, 65003 }, { -15, 68443 }, { -16, 72075 }, { -17, 75910 }, { -18, 79961 }, { -19, 84239 }, { -20, 88758 }, { -21, 93644 }, { -22, 98839 }, { -23, 104370 }, { -24, 110250 }, { -25, 116530 }, { -26, 123210 }, { -27, 130350 }, { -28, 137960 }, { -29, 146100 }, { -30, 154800 }, { -31, 164000 }, { -32, 173810 }, { -33, 184290 }, { -34, 195490 }, { -35, 207460 }, { -36, 220260 }, { -37, 233950 }, { -38, 248610 }, { -39, 264320 }, { -40, 281160 },
}
#endif
;

GLOBAL uint32_t adc1_value_buffer[2];
GLOBAL double   needle_temperature;
/* function prototypes */
GLOBAL void needle_temp_ctrl_task( void* pvParameters );
GLOBAL void cmd_task_entry( void* parameter );
GLOBAL void cmd_process_task( CmdCtx_TypeDef* cmd );
GLOBAL void cmd_response( Uplink_Protoc_Function_TypeDef cmd, CmdErrorOpts_TypeDef* result );
GLOBAL void liquid_detect_ctrl( CmdCtx_TypeDef* cmd, CmdErrorOpts_TypeDef* ret );
GLOBAL void drv_version( CmdCtx_TypeDef* cmd, CmdErrorOpts_TypeDef* ret );
GLOBAL void timestamp_sync( CmdCtx_TypeDef* cmd, CmdErrorOpts_TypeDef* ret );

#endif
