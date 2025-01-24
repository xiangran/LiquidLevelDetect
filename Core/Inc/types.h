/**
 *****************************************************************************
 * @brief 	File containing example of doxygen usage for quick reference.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 * @file 	types.h
 * @author	Jackie
 * @date 	1/Nov/2022
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

#ifndef TYPES_H
#define TYPES_H

/* #include */

/* #define */

/* typedef */
typedef struct
{
    uint8_t  evt_id;
    intptr_t evt_param1;
    intptr_t evt_param2;
    intptr_t evt_param3;
    intptr_t src_task;
} evt_info_s_type;

enum
{
    // can rx task
    EVT_CAN_RX_DATA,
    // can tx task
    EVT_PID_PERIOD_TIMEOUT,
    // diagnosis task
    // cmd process task
    EVT_CMD_RECEIVED,
    // usart task
    EVT_UI_CMD,
    // app task
    EVT_ADC_DATA,
    EVT_ADC_TEST,
    EVT_ADC_NOISE,
    EVT_REBOOT,
};

typedef enum
{
    ERROROPT_NONE             = 0, // 没有动作
    ERROROPT_STOP_SINGLEMOTOR = 1, // 停止单个电机
    ERROROPT_STOP_ALLMOTOR    = 2, // 停止所有电机
} Error_Motor_OpterationDef;

typedef enum
{
    RESET_CAUSE_UNKNOWN = 0,
    RESET_CAUSE_LOW_POWER_RESET,      // 低功耗复位
    RESET_CAUSE_WINDOW_WATCHDOG,      // 窗口看门狗复位
    RESET_CAUSE_INDEPENDENT_WATCHDOG, // 独立看门狗复位
    RESET_CAUSE_SOFTWARE,             // 软件复位
    RESET_CAUSE_POWER_ON_POWER_DOWN,  // 上电/掉电复位
    RESET_CAUSE_EXTERNAL_PIN_RESET,   // 外部引脚复位
    RESET_CAUSE_BROWNOUT_RESET,       // 欠压复位
} reset_cause_t;
/* variables */

/* constants */

/* function prototypes */

#endif
