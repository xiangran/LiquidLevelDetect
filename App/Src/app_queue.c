/**
 *****************************************************************************
 * @brief 	File containing example of doxygen usage for quick reference.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 * @file 	app_queue.c
 * @author	Jackie
 * @date 	21/Oct/2022
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

#define APP_QUEUE_C

/* #include */
#include "app_header.h"
#undef APP_QUEUE_C
/* #define */

/* typedef */

/* static variables */

/* static constants */

/* static function prototypes */
bool IsEmpty() { return ( data_list->len == 0 ); }

/*!
 * \fn     EnQueue
 * \brief
 *
 * \param  [in] void* pData         #
 * \param  [in] uint16_t length     #
 * \param  [in] bool highPriority   #
 *
 * \retval void
 *
 * \Author Jackie  2022-10-24
 */
void EnQueue( void* pData, uint16_t length, bool highPriority )
{
    payload_packet_t* data = ( payload_packet_t* ) trace_mem_malloc( __FUNCTION__, __LINE__, sizeof( payload_packet_t ) + length, true );

    if ( data )
    {
        data->size = length;
        memcpy( &( data->dataStream ), pData, length );
        Node* _node = ListNodeNew( ( void* ) data );
        if ( highPriority )
        {
            List_lPush( data_list, _node );
        }
        else
        {
            List_rPush( data_list, _node );
        }
        // printf( "can output queue,size: %d\r\n", data_list->len );
    }

    return;
}

/*!
 * \fn     TopQueue
 * \brief
 *
 *
 * \retval void*
 *
 * \Author Jackie  2022-10-24
 */
void* TopQueue()
{
    if ( IsEmpty() )
        return NULL;

    Node* item = List_AT( data_list, 0 );
    return item->val;
}

/*!
 * \fn     DeQueue
 * \brief
 *
 *
 * \retval void*
 *
 * \Author Jackie  2022-10-24
 */
void* DeQueue()
{
    if ( IsEmpty() )
        return NULL;

    Node* n = List_AT( data_list, 0 );
    List_Remove( data_list, n );
    // printf( "L DeQueue: size: %d\r\n", data_list->len );

    return NULL;
}
