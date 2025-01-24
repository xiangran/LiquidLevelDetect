/**
 *****************************************************************************
 * @brief 	File containing example of doxygen usage for quick reference.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 * @file 	ringbuffer.c
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

#define RINGBUFFER_C

/* #include */
#include "app_header.h"
#undef RINGBUFFER_C
/* #define */

/* typedef */

/* static variables */

/* static constants */

/* static function prototypes */
/*!
 * \fn     Ring_buffer_init
 * \brief
 *
 * \param  [in] ring_buffer* ring   #
 * \param  [in] uint8_t* buff       #
 * \param  [in] uint16_t size       #
 *
 * \retval void
 *
 * \Author Jackie  2022-10-24
 */
void ring_buffer_init( ring_buffer* ring, uint32_t* buff, uint16_t size )
{
    ring->buffer      = buff;
    ring->buffer_size = size;
    ring->read_index  = 0;
    ring->save_index  = 0;
}

/*!
 * \fn     ring_buffer_clear
 * \brief
 *
 * \param  [in] ring_buffer* ring   #
 *
 * \retval void
 *
 * \Author Jackie  2023-1-06
 */
void ring_buffer_clear( ring_buffer* ring )
{
    ring->read_index = 0;
    ring->save_index = 0;
}

/*!
 * \fn     Ring_buffer_save
 * \brief
 *
 * \param  [in] ring_buffer* ring   #
 * \param  [in] uint8_t data        #
 *
 * \retval void
 *
 * \Author Jackie  2022-10-24
 */
void ring_buffer_save( ring_buffer* ring, uint32_t data )
{
    /* save character */
    ring->buffer[ring->save_index] = data;
    ring->save_index++;

    if ( ring->save_index >= ring->buffer_size )
        ring->save_index = 0;

    /* if the next position is read index, discard this 'read char' */
    if ( ring->save_index == ring->read_index )
    {
        ring->read_index++;

        if ( ring->read_index >= ring->buffer_size )
            ring->read_index = 0;
    }
}

/*!
 * \fn     Ring_buffer_read
 * \brief
 *
 * \param  [in] ring_buffer* ring   #
 * \param  [in] uint8_t* buffer     #
 * \param  [in] uint16_t size       #
 *
 * \retval int
 *
 * \Author Jackie  2022-10-24
 */
int ring_buffer_read( ring_buffer* ring, uint32_t* buffer, uint16_t size )
{
    uint32_t* ptr = buffer;

    while ( size-- )
    {
        if ( ring->read_index != ring->save_index )
        {
            /* read a character */
            *( ptr++ ) = ring->buffer[ring->read_index];

            /* move to next position */
            ring->read_index++;
            if ( ring->read_index >= ring->buffer_size )
                ring->read_index = 0;
        }
        else
        {
            break;
        }
    }

    return ( ptr - buffer );
}

/*!
 * \fn     Ring_buffer_save_buffer_isr
 * \brief
 *
 * \param  [in] ring_buffer * ring   #
 * \param  [in] uint8_t* data        #
 * \param  [in] uint16_t len         #
 *
 * \retval void
 *
 * \Author Jackie  2022-10-24
 */
void ring_buffer_save_buffer_isr( ring_buffer* ring, uint32_t* data, uint16_t len )
{
    uint32_t* ptr = data;

    while ( len-- )
    {
        ring_buffer_save_isr( ring, *ptr );
        ptr++;
    }
}

/*!
 * \fn     Ring_buffer_save_isr
 * \brief
 *
 * \param  [in] ring_buffer* ring   #
 * \param  [in] uint8_t data        #
 *
 * \retval void
 *
 * \Author Jackie  2022-10-24
 */
void ring_buffer_save_isr( ring_buffer* ring, uint32_t data )
{
    /* save character */
    ring->buffer[ring->save_index] = data;
    ring->save_index++;

    if ( ring->save_index >= ring->buffer_size )
        ring->save_index = 0;

    /* if the next position is read index, discard this 'read char' */
    if ( ring->save_index == ring->read_index )
    {
        ring->read_index++;

        if ( ring->read_index >= ring->buffer_size )
            ring->read_index = 0;
    }
}

/*!
 * \fn     Ring_buffer_read_isr
 * \brief
 *
 * \param  [in] ring_buffer* ring   #
 * \param  [in] uint8_t* buffer     #
 * \param  [in] uint16_t size       #
 *
 * \retval int
 *
 * \Author Jackie  2022-10-24
 */
int ring_buffer_read_isr( ring_buffer* ring, uint32_t* buffer, uint16_t size )
{
    uint32_t* ptr = buffer;

    while ( size-- )
    {
        if ( ring->read_index != ring->save_index )
        {
            /* read a character */
            *( ptr++ ) = ring->buffer[ring->read_index];

            /* move to next position */
            ring->read_index++;

            if ( ring->read_index >= ring->buffer_size )
                ring->read_index = 0;
        }
        else
        {
            break;
        }
    }

    return ( ptr - buffer );
}

/*!
 * \fn     Ring_buffer_data_num
 * \brief
 *
 * \param  [in] ring_buffer* ring   #
 *
 * \retval uint16_t
 *
 * \Author Jackie  2022-10-24
 */
uint16_t ring_buffer_data_num( ring_buffer* ring )
{
    if ( ring->save_index >= ring->read_index )
    {
        return ( ring->save_index - ring->read_index );
    }
    else
    {
        return ( ring->save_index + ring->buffer_size - ring->read_index );
    }
}

/*!
 * \fn     Ring_buffer_isEmpty
 * \brief
 *
 * \param  [in] ring_buffer* ring   #
 *
 * \retval int
 *
 * \Author Jackie  2022-10-24
 */
int ring_buffer_isEmpty( ring_buffer* ring )
{
    if ( ring->save_index == ring->read_index )
        return true;
    else
        return false;
}
