# LiquidLevelDetect

Embedded C firmware for an STM32G431-based liquid level detection board. The application runs on FreeRTOS through the CMSIS-RTOS v2 interface and uses ADC measurements to detect changes in the sensing signal.

## Features

- ADC sampling with DMA and ring-buffer processing.
- Liquid level detection using signal thresholds and changes between samples.
- Startup calibration and background noise checks.
- AD5160 digital potentiometer control for the sensing circuit.
- NTC resistance-to-temperature conversion using a lookup table.
- Detection parameter storage in internal Flash with CRC-8 validation.
- UART shell and logging integration, plus Cortex-M fault backtrace support.

## Hardware and software

The project targets the STM32G431 family (Arm Cortex-M4F). It depends on STM32G4 HAL and CMSIS headers, FreeRTOS, and board-specific analog circuitry and GPIO assignments.

The firmware is intended for its original sensing board. Review the pin definitions in `Core/Inc/main.h` and peripheral initialization in `Core/Src/` before adapting it to another board.

## Repository layout

| Path | Contents |
| --- | --- |
| `App/` | Detection logic, calibration, temperature conversion, parameter storage, and shell commands |
| `Core/` | MCU initialization, peripheral setup, interrupts, and RTOS task creation |
| `Middlewares/Third_Party/FreeRTOS/` | FreeRTOS kernel and CMSIS-RTOS integration |
| `Middlewares/Shell/` | Shell port and logging plugin |
| `Middlewares/Trace/` | Cortex-M backtrace support |
| `EWARM/` | IAR Embedded Workbench workspace, project, startup code, and linker configuration |
| `cmake/` | GNU Arm toolchain configuration |
| `cmake_generated/` | Generated source lists and compiler settings |
| `.vscode/` | Editor, build task, and ST-Link debug configuration |
| `STM32G431XX_FLASH.ld` | GNU linker script |

## Build setup

This checkout requires additional dependencies and local path configuration before it can be built. STM32 HAL/CMSIS driver files and the shell core are referenced from external directories and are not included in full.

### IAR Embedded Workbench

1. Install IAR Embedded Workbench for Arm with STM32G431 support.
2. Provide the STM32G4 HAL/CMSIS drivers and the shell core required by the project.
3. Open `EWARM/Project.eww`.
4. Update external source and include paths in the project settings, including the startup assembly reference.
5. Review `EWARM/buildconfig.cfg` and the configured post-build step, then build the project.

### GNU Arm / CMake

The repository includes a GNU Arm toolchain file, generated CMake configuration, and VS Code tasks. However, it does **not** currently include a top-level `CMakeLists.txt`, so a fresh checkout cannot be configured directly with CMake.

To complete this build setup:

1. Install the GNU Arm Embedded toolchain and CMake 3.22 or later.
2. Add a top-level CMake project that integrates the provided toolchain and generated source lists.
3. Replace external dependency paths with locations available on your machine.
4. Resolve missing startup/source references and directory capitalization differences in the generated configuration, especially on case-sensitive filesystems.

The VS Code build tasks require a successfully configured CMake project.

## Flashing and debugging

The VS Code configuration uses ST-Link over SWD. Install STM32CubeProgrammer and configure the local debugger, toolchain, and SVD paths in `.vscode/launch.json` before use.

Once a firmware image has been built and the target is connected, it can be programmed with:

```sh
STM32_Programmer_CLI --connect port=swd --download path/to/firmware.elf -hardRst
```

Replace `path/to/firmware.elf` with the actual build output. The command programs the connected target and resets it.

## Configuration

- `App/Inc/app.h`: default detection thresholds, potentiometer settings, and buffer sizes.
- `App/Src/app.c`: detection and calibration behavior.
- `App/Src/needle_temp_ctrl.c`: NTC measurement and temperature conversion.
- `App/Src/flash.c`: loading and saving detection parameters.
- `Core/Inc/FreeRTOSConfig.h`: RTOS configuration.
- `EWARM/buildconfig.cfg`: board selection, version definitions, and build flags.

Some peripheral and diagnostic code is retained even where initialization or task creation is disabled. Check the active startup path in `Core/Src/main.c` and `Core/Src/freertos.c` before relying on a particular interface.

## Licensing

No repository-wide license is currently provided. Third-party components retain their own copyright notices and license terms; see the relevant source headers and the FreeRTOS `LICENSE` file.
