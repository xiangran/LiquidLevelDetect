/**
 *****************************************************************************
 * @brief 	File containing example of doxygen usage for quick reference.
 * 
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 * 
 * @file 	clist.h
 * @author	Jackie
 * @date 	13/Sep/2022
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

#ifndef CLIST_H
#define CLIST_H

/* #include */

/* #define */

/* typedef */
typedef enum
{
    LIST_HEAD,
    LIST_TAIL
} Direction_t;

typedef struct node
{
    struct node* prev;
    struct node* next;
    void*        val;
    bool         pararrel;
} Node;

typedef void ( *listFree )( void* val );
typedef int ( *itemCompare )( void* a, void* b );

typedef struct
{
    Node*        head;
    Node*        tail;
    unsigned int len;
    listFree     free;
    itemCompare  match;
} List;

typedef struct
{
    Node*       next;
    Direction_t direction;
} List_iterator_t;

/* variables */
#undef GLOBAL
#ifdef CLIST_C
#define GLOBAL
#else
#define GLOBAL extern
#endif

/* constants */

/* function prototypes */
GLOBAL List* ListNew( listFree func1, itemCompare func2 );
GLOBAL Node* ListNodeNew( void* val );
GLOBAL void ListDestroy( List* self );
GLOBAL Node* List_rPush( List* self, Node* node );
GLOBAL Node* List_rPop( List* self );
GLOBAL Node* List_lPop( List* self );
GLOBAL Node* List_lPush( List* self, Node* node );
GLOBAL Node* List_Find( List* self, void* val );
GLOBAL Node* List_AT( List* self, int index );
GLOBAL void List_Remove( List* self, Node* node );
GLOBAL List_iterator_t* List_iterator_new( List* list, Direction_t direction );
GLOBAL List_iterator_t* List_iterator_new_from_node( Node* node, Direction_t direction );
GLOBAL Node* List_iterator_next( List_iterator_t* self );
GLOBAL void List_iterator_destroy( List_iterator_t* self );

#endif


