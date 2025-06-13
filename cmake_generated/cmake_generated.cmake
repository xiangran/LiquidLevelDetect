cmake_minimum_required(VERSION 3.22)

# Core MCU flags, CPU, instruction set and FPU setup
set(cpu_PARAMS ${cpu_PARAMS}
    -mthumb

    # -mcpu, -mfloat, -mfloat-abi config
    -mcpu=cortex-m4
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16
)

# Linker script
set(linker_script_SRC ${linker_script_SRC} ${CMAKE_CURRENT_SOURCE_DIR}/STM32G431XX_FLASH.ld)


# Sources
set(sources_SRCS ${sources_SRCS}
    ${CMAKE_SOURCE_DIR}/App/src/app.c
    ${CMAKE_SOURCE_DIR}/App/src/ad5160.c
    ${CMAKE_SOURCE_DIR}/App/src/app_queue.c
    ${CMAKE_SOURCE_DIR}/App/src/clist.c
    ${CMAKE_SOURCE_DIR}/App/src/cmd.c
    ${CMAKE_SOURCE_DIR}/App/src/exception.c
    ${CMAKE_SOURCE_DIR}/App/src/flash.c
    ${CMAKE_SOURCE_DIR}/App/src/public.c
    ${CMAKE_SOURCE_DIR}/App/src/ringbuffer.c
    ${CMAKE_SOURCE_DIR}/App/src/needle_temp_ctrl.c
    ${CMAKE_SOURCE_DIR}/Core/Src/adc.c
    ${CMAKE_SOURCE_DIR}/Core/Src/freertos.c
    ${CMAKE_SOURCE_DIR}/Core/Src/gpio.c
    ${CMAKE_SOURCE_DIR}/Core/Src/main.c
    ${CMAKE_SOURCE_DIR}/Core/Src/rtc.c
    ${CMAKE_SOURCE_DIR}/Core/Src/dma.c
    ${CMAKE_SOURCE_DIR}/Core/Src/stm32g4xx_hal_msp.c
    ${CMAKE_SOURCE_DIR}/Core/Src/stm32g4xx_hal_timebase_tim.c
    ${CMAKE_SOURCE_DIR}/Core/Src/stm32g4xx_it.c
    ${CMAKE_SOURCE_DIR}/Core/Src/usart.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Shell/Plugins/log/log.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Shell/shell_port.c
    ${CMAKE_SOURCE_DIR}/Core/Startup/startup_stm32g431xx.s
    D:/Proj/Proj_Components/shell/shell.c
    D:/Proj/Proj_Components/shell/shell_cmd_list.c
    D:/Proj/Proj_Components/shell/shell_companion.c
    D:/Proj/Proj_Components/shell/shell_ext.c
    ${CMAKE_SOURCE_DIR}/Middlewares/trace/cm_backtrace.c
)

# STM32 HAL/LL Drivers
set(STM32_Drivers_Src
    D:/Proj/STM32G4Driver/CMSIS/Device/ST/STM32G4xx/Source/Templates/system_stm32g4xx.c
    D:/Proj/STM32G4Driver/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal.c
    D:/Proj/STM32G4Driver/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_adc.c
    D:/Proj/STM32G4Driver/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_adc_ex.c
    D:/Proj/STM32G4Driver/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_cortex.c
    D:/Proj/STM32G4Driver/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dma.c
    D:/Proj/STM32G4Driver/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dma_ex.c
    D:/Proj/STM32G4Driver/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_exti.c
    D:/Proj/STM32G4Driver/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash.c
    D:/Proj/STM32G4Driver/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash_ex.c
    D:/Proj/STM32G4Driver/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash_ramfunc.c
    D:/Proj/STM32G4Driver/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_gpio.c
    D:/Proj/STM32G4Driver/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr.c
    D:/Proj/STM32G4Driver/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr_ex.c
    D:/Proj/STM32G4Driver/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc.c
    D:/Proj/STM32G4Driver/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc_ex.c
    D:/Proj/STM32G4Driver/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rtc.c
    D:/Proj/STM32G4Driver/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rtc_ex.c
    D:/Proj/STM32G4Driver/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_tim.c
    D:/Proj/STM32G4Driver/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_tim_ex.c
    D:/Proj/STM32G4Driver/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_uart.c
    D:/Proj/STM32G4Driver/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_uart_ex.c
    D:/Proj/STM32G4Driver/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_adc.c
)
# Drivers Midllewares

set(FreeRTOS_Src
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/croutine.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/list.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/queue.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/tasks.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/timers.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c
)

# Include directories
set(include_c_DIRS ${include_c_DIRS}
    D:/Proj/STM32G4Driver/STM32G4xx_HAL_Driver/Inc
    D:/Proj/STM32G4Driver/STM32G4xx_HAL_Driver/Inc/Legacy
    D:/Proj/STM32G4Driver/CMSIS/Device/ST/STM32G4xx/Include
    D:/Proj/STM32G4Driver/CMSIS/Include
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/include
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
    ${CMAKE_SOURCE_DIR}/App/inc
    ${CMAKE_SOURCE_DIR}/Core/Inc
    ${CMAKE_SOURCE_DIR}/Middlewares/Shell
    ${CMAKE_SOURCE_DIR}/Middlewares/Shell/Plugins/log
    ${CMAKE_SOURCE_DIR}/Middlewares/Trace/inc
    D:/Proj/Proj_Components/shell
)

set(include_cxx_DIRS ${include_cxx_DIRS})
set(include_asm_DIRS ${include_asm_DIRS})

# Symbols definition
set(symbols_c_SYMB ${symbols_c_SYMB}
    "HSE_VALUE=8000000"
    "HSI_VALUE=16000000"
    "USE_HAL_DRIVER"
	"STM32G431xx"
)
set(symbols_cxx_SYMB ${symbols_cxx_SYMB}
    "USE_HAL_DRIVER"
	"STM32G431xx"
)

set(symbols_asm_SYMB ${symbols_asm_SYMB}
    "STM32G431xx"
)

set(symbols_SYMB ${symbols_SYMB}
    "SMD_LIQUID_DETECT_BOARD_1=6"
    "PROJECT_HW_DEF=6"
    "MAJORVER=1"
    "MIDVER=0"
    "MINORVER=0"
    "INTVER=7"
)

# Link directories
set(link_DIRS ${link_DIRS})

# Link libraries
set(link_LIBS ${link_LIBS})

# Compiler options
set(compiler_OPTS ${compiler_OPTS})

# Linker options
set(linker_OPTS ${linker_OPTS})
