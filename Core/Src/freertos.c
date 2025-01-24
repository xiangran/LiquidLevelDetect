/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "app_header.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t         detect_liquid_level_task_handle;
osThreadId_t         needle_temp_ctrl_task_handle;
osThreadId_t         adc_task_handle;
const osThreadAttr_t detect_liquid_level_task_attributes = {
    .name       = "DETECT",
    .stack_size = 1200,
    .priority   = ( osPriority_t ) osPriorityNormal,
};

const osThreadAttr_t needle_temp_ctrl_task_attributes = {
    .name       = "PID",
    .priority   = ( osPriority_t ) osPriorityNormal,
    .stack_size = 1200,
};

const osThreadAttr_t adc_task_attributes = {
    .name       = "ADC",
    .priority   = ( osPriority_t ) osPriorityAboveNormal,
    .stack_size = 512,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */
void vApplicationStackOverflowHook( xTaskHandle xTask, signed char* pcTaskName );

/* USER CODE BEGIN 4 */
void vApplicationStackOverflowHook( xTaskHandle xTask, signed char* pcTaskName )
{
    /* Run time stack overflow checking is performed if
    configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
    called if a stack overflow is detected. */

    while ( true )
    {
        ALERT( DEBUG_MODULE, "%s overflow", vTaskName() );
    }
}
/* USER CODE END 4 */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void init_task( void )
{
    /* USER CODE BEGIN Init */
    flash_init();
    /* USER CODE END Init */

    /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
    /* USER CODE END RTOS_MUTEX */

    /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
    /* USER CODE END RTOS_SEMAPHORES */

    /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
    /* USER CODE END RTOS_TIMERS */

    /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
    /* USER CODE END RTOS_QUEUES */

    /* Create the thread(s) */
    log_shell_init();
    /* creation of defaultTask */
    detect_liquid_level_task_handle = osThreadNew( detect_liquid_level_task, NULL, &detect_liquid_level_task_attributes );
    needle_temp_ctrl_task_handle    = osThreadNew( needle_temp_ctrl_task, NULL, &needle_temp_ctrl_task_attributes );
    adc_task_handle                 = osThreadNew( adc_task, NULL, &adc_task_attributes );

    /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
    /* USER CODE END RTOS_THREADS */

    /* USER CODE BEGIN RTOS_EVENTS */
    /* add events, ... */
    /* USER CODE END RTOS_EVENTS */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
