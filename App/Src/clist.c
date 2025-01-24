/**
 *****************************************************************************
 * @brief 	File containing example of doxygen usage for quick reference.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 * @file 	clist.c
 * @author	Jackie
 * @date 	12/Sep/2022
 *****************************************************************************
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <b>&copy; COPYRIGHT 2022</b>
 *
 *****************************************************************************
 */

#define CLIST_C

/* #include */
#include "app_header.h"
#undef CLIST_C
/* #define */

/* typedef */

/* static variables */

/* static constants */

/* static function prototypes */
/*!
 * \fn     ListNew
 * \brief  Allocate a new list_t. NULL on failure.
 *
 * \param  [in] void   #
 *
 * \retval List *
 *
 * \Author Jackie  2022-2-02
 */
List* ListNew( listFree func1, itemCompare func2 )
{
    List* self = trace_mem_malloc( __FUNCTION__, __LINE__, sizeof( List ), true );

    if ( self == NULL )
    {
        return NULL;
    }

    self->head  = NULL;
    self->tail  = NULL;
    self->free  = func1;
    self->match = func2;
    self->len   = 0;
    return self;
}

/*!
 * \fn     ListNodeNew
 * \brief   Allocates a new list_node_t. NULL on failure.
 *
 * \param  [in] void *val   #
 *
 * \retval
 *
 * \Author Jackie  2022-2-02
 */
Node* ListNodeNew( void* val )
{
    Node* self = trace_mem_malloc( __FUNCTION__, __LINE__, sizeof( Node ), true );

    if ( self == NULL )
    {
        return NULL;
    }

    self->prev = NULL;
    self->next = NULL;
    self->val  = val;
    return self;
}

/*!
 * \fn     ListDestroy
 * \brief   Free the list.
 *
 * \param  [in] List *self   #
 *
 * \retval void
 *
 * \Author Jackie  2022-2-02
 */
void ListDestroy( List* self )
{
    unsigned int len = self->len;
    Node*        next;
    Node*        curr = self->head;

    while ( len-- )
    {
        next = curr->next;
        if ( self->free )
            self->free( curr->val );
        trace_mem_free( __FUNCTION__, __LINE__, curr, true );
        curr = next;
    }

    trace_mem_free( __FUNCTION__, __LINE__, self, true );
}

/*!
 * \fn     List_rPush
 * \brief   Append the given node to the list and return the node, NULL on failure.
 *
 * \param  [in] List *self   #
 * \param  [in] Node *node   #
 *
 * \retval Node *
 *
 * \Author Jackie  2022-2-02
 */
Node* List_rPush( List* self, Node* node )
{
    if ( !node )
        return NULL;

    if ( self->len )
    {
        node->prev       = self->tail;
        node->next       = NULL;
        self->tail->next = node;
        self->tail       = node;
    }
    else
    {
        self->head = self->tail = node;
        node->prev = node->next = NULL;
    }

    ++self->len;
    return node;
}

/*!
 * \fn     List_rPop
 * \brief   Return / detach the last node in the list, or NULL.
 *
 * \param  [in] List *self   #
 *
 * \retval
 *
 * \Author Jackie  2022-2-02
 */
Node* List_rPop( List* self )
{
    if ( !self->len )
        return NULL;

    Node* node = self->tail;

    if ( --self->len )
    {
        ( self->tail = node->prev )->next = NULL;
    }
    else
    {
        self->tail = self->head = NULL;
    }

    node->next = node->prev = NULL;
    return node;
}

/*!
 * \fn     List_lPop
 * \brief  Return / detach the first node in the list, or NULL.
 *
 * \param  [in] list_t *self   #
 *
 * \retval
 *
 * \Author Jackie  2022-2-02
 */
Node* List_lPop( List* self )
{
    if ( !self->len )
        return NULL;

    Node* node = self->head;

    if ( --self->len )
    {
        ( self->head = node->next )->prev = NULL;
    }
    else
    {
        self->head = self->tail = NULL;
    }

    node->next = node->prev = NULL;
    return node;
}

/*!
 * \fn     List_lPush
 * \brief    Prepend the given node to the list Sand return the node, NULL on failure.
 *
 * \param  [in] List *self   #
 * \param  [in] Node *node   #
 *
 * \retval
 *
 * \Author Jackie  2022-2-02
 */
Node* List_lPush( List* self, Node* node )
{
    if ( !node )
        return NULL;

    if ( self->len )
    {
        node->next       = self->head;
        node->prev       = NULL;
        self->head->prev = node;
        self->head       = node;
    }
    else
    {
        self->head = self->tail = node;
        node->prev = node->next = NULL;
    }

    ++self->len;
    return node;
}

/*!
 * \fn     List_Insert
 * \brief
 *
 * \param  [in] List* self   #
 * \param  [in] Node* node   #
 *
 * \retval Node*
 *
 * \Author Jackie  2022-7-20
 */
void List_InsertAfterPosition( List* self, Node* postion, Node* insert_node )
{
    if ( !postion || !insert_node )
        return;

    postion->next     = insert_node;
    insert_node->next = postion->next;
    ++self->len;
}

/*!
 * \fn     List_Find
 * \brief   Return the node associated to val or NULL.
 *
 * \param  [in] List *self   #
 * \param  [in] void *val    #
 *
 * \retval Node *
 *
 * \Author Jackie  2022-2-02
 */
Node* List_Find( List* self, void* val )
{
    List_iterator_t* it = List_iterator_new( self, LIST_HEAD );
    Node*            node;

    while ( ( node = List_iterator_next( it ) ) )
    {
        if ( self->match )
        {
            if ( self->match( val, node->val ) )
            {
                List_iterator_destroy( it );
                return node;
            }
        }
        else
        {
            if ( val == node->val )
            {
                List_iterator_destroy( it );
                return node;
            }
        }
    }

    List_iterator_destroy( it );
    return NULL;
}

/*!
 * \fn     List_AT
 * \brief  Return the node at the given index or NULL.
 *
 * \param  [in] List *self   #
 * \param  [in] int index    #
 *
 * \retval
 *
 * \Author Jackie  2022-2-02
 */
Node* List_AT( List* self, int index )
{
    Direction_t direction = LIST_HEAD;

    if ( index < 0 )
    {
        direction = LIST_TAIL;
        index     = ~index;
    }

    if ( ( unsigned ) index < self->len )
    {
        List_iterator_t* it   = List_iterator_new( self, direction );
        Node*            node = List_iterator_next( it );

        while ( index-- )
            node = List_iterator_next( it );

        List_iterator_destroy( it );
        return node;
    }

    return NULL;
}

/*!
 * \fn     List_Remove
 * \brief  Remove the given node from the list, freeing it and it's value.
 *
 * \param  [in] List *self   #
 * \param  [in] Node *node   #
 *
 * \retval
 *
 * \Author Jackie  2022-2-02
 */
void List_Remove( List* self, Node* node )
{
    node->prev ? ( node->prev->next = node->next ) : ( self->head = node->next );

    node->next ? ( node->next->prev = node->prev ) : ( self->tail = node->prev );

    if ( self->free )
        self->free( node->val );

    trace_mem_free( __FUNCTION__, __LINE__, node, true );
    --self->len;
}

/*!
 * \fn     list_iterator_new
 * \brief   Allocate a new list_iterator_t. NULL on failure. Accepts a direction, which may be LIST_HEAD or LIST_TAIL.
 *
 * \param  [in] List *list              #
 * \param  [in] Direction_t direction   #
 *
 * \retval
 *
 * \Author Jackie  2022-2-02
 */
List_iterator_t* List_iterator_new( List* list, Direction_t direction )
{
    Node* node = direction == LIST_HEAD ? list->head : list->tail;
    return List_iterator_new_from_node( node, direction );
}

/*!
 * \fn     list_iterator_new_from_node
 * \brief    Allocate a new list_iterator_t with the given start node. NULL on failure.
 *
 * \param  [in] Node *node              #
 * \param  [in] Direction_t direction   #
 *
 * \retval
 *
 * \Author Jackie  2022-2-02
 */
List_iterator_t* List_iterator_new_from_node( Node* node, Direction_t direction )
{
    List_iterator_t* self = trace_mem_malloc( __FUNCTION__, __LINE__, sizeof( List_iterator_t ), true );
    if ( self == NULL )
        return NULL;
    self->next      = node;
    self->direction = direction;
    return self;
}

/*!
 * \fn     list_iterator_next
 * \brief   Return the next list_node_t or NULL when no more nodes remain in the list.
 *
 * \param  [in] List_iterator_t *self   #
 *
 * \retval
 *
 * \Author Jackie  2022-2-02
 */
Node* List_iterator_next( List_iterator_t* self )
{
    Node* curr = self->next;
    if ( curr )
    {
        self->next = self->direction == LIST_HEAD ? curr->next : curr->prev;
    }
    return curr;
}

/*!
 * \fn     list_iterator_destroy
 * \brief  Free the list iterator.
 *
 * \param  [in] List_iterator_t *self   #
 *
 * \retval
 *
 * \Author Jackie  2022-2-02
 */
void List_iterator_destroy( List_iterator_t* self )
{
    trace_mem_free( __FUNCTION__, __LINE__, self, true );
    self = NULL;
}
