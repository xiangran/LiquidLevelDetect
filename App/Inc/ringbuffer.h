/**
 *****************************************************************************
 * @brief 	File containing example of doxygen usage for quick reference.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 * @file 	ringbuffer.h
 * @author	Jackie
 * @date 	24/Oct/2022
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

#ifndef RINGBUFFER_H
#define RINGBUFFER_H

/* #include */

/* #define */

/* typedef */
typedef struct
{
    uint32_t* buffer;
    uint16_t  buffer_size;
    uint16_t  read_index;
    uint16_t  save_index;
} ring_buffer;

/* variables */
#undef GLOBAL
#ifdef RINGBUFFER_C
#define GLOBAL
#else
#define GLOBAL extern
#endif

/* constants */

/* function prototypes */
GLOBAL void     ring_buffer_init( ring_buffer* ring, uint32_t* buff, uint16_t size );
GLOBAL void     ring_buffer_clear( ring_buffer* ring );
GLOBAL void     ring_buffer_save( ring_buffer* ring, uint32_t data );
GLOBAL int      ring_buffer_read( ring_buffer* ring, uint32_t* buffer, uint16_t size );
GLOBAL void     ring_buffer_save_isr( ring_buffer* ring, uint32_t dat );
GLOBAL void     ring_buffer_save_buffer_isr( ring_buffer* ring, uint32_t* data, uint16_t len );
GLOBAL int      ring_buffer_read_isr( ring_buffer* ring, uint32_t* buffer, uint16_t size );
GLOBAL uint16_t ring_buffer_data_num( ring_buffer* ring );
GLOBAL int      ring_buffer_isEmpty( ring_buffer* ring );

#endif
