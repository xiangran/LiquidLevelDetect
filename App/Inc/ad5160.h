/**
 *****************************************************************************
 * @brief 	File containing example of doxygen usage for quick reference.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 * @file 	ad5160.h
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

#ifndef AD5160_H
#define AD5160_H

/* #include */

/* #define */
#define AD5160_1_SDI_Write_1 HAL_GPIO_WritePin( GPIOB, AD5160_1_SDI, GPIO_PIN_SET )
#define AD5160_1_SDI_Write_0 HAL_GPIO_WritePin( GPIOB, AD5160_1_SDI, GPIO_PIN_RESET )

#define AD5160_1_WCLK_SET HAL_GPIO_WritePin( GPIOB, AD5160_1_WCLK, GPIO_PIN_SET )
#define AD5160_1_WCLK_CLR HAL_GPIO_WritePin( GPIOB, AD5160_1_WCLK, GPIO_PIN_RESET )
#define AD5160_1_CS_SET HAL_GPIO_WritePin( GPIOA, AD5160_1_CS, GPIO_PIN_SET )
#define AD5160_1_CS_CLR HAL_GPIO_WritePin( GPIOA, AD5160_1_CS, GPIO_PIN_RESET )

#define AD5160_2_SDI_Write_1 HAL_GPIO_WritePin( GPIOB, AD5160_2_SDI, GPIO_PIN_SET )
#define AD5160_2_SDI_Write_0 HAL_GPIO_WritePin( GPIOB, AD5160_2_SDI, GPIO_PIN_RESET )

#define AD5160_2_WCLK_SET HAL_GPIO_WritePin( GPIOB, AD5160_2_WCLK, GPIO_PIN_SET )
#define AD5160_2_WCLK_CLR HAL_GPIO_WritePin( GPIOB, AD5160_2_WCLK, GPIO_PIN_RESET )
#define AD5160_2_CS_SET HAL_GPIO_WritePin( GPIOB, AD5160_2_CS, GPIO_PIN_SET )
#define AD5160_2_CS_CLR HAL_GPIO_WritePin( GPIOB, AD5160_2_CS, GPIO_PIN_RESET )
/* typedef */

/* variables */
#undef GLOBAL
#ifdef AD5160_C
#define GLOBAL
#else
#define GLOBAL extern
#endif

/* constants */

/* function prototypes */
GLOBAL int8_t liquid_ad_value_calibration( void );
GLOBAL void   ad5160_1_writeByte( uint8_t data_resistance );
GLOBAL void   ad5160_2_writeByte( uint8_t data_resistance );
GLOBAL void   ad5160_gpio_init( void );
GLOBAL void   ad5160_init( void );
#endif
