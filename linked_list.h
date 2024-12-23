#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <stdint.h>

/*
 * Some macros with similar names to operations on arrays.
 *
 * Macros to:
 * Append new node to end of list (append),
 * Append to start of list (append_head),
 * Delete last node (pop),
 * Delete first node (pop_head)
 */
#define Linkedlist_append(list, value_ptr) Linkedlist_insert(list, list->size, value_ptr)
#define Linkedlist_append_head(list, value_ptr) Linkedlist_insert(list, 0, value_ptr)
#define Linkedlist_pop(list) Linkedlist_delete(list, list->size - 1)
#define Linkedlist_pop_head(list) Linkedlist_delete(list, 0)

/*
 * Structures for linked list and nodes
 */
typedef struct Node
{
    void* data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct 
{
    Node* head;
    Node* tail;
    uint8_t data_size;
    size_t size;
} Linkedlist;

/*
 * Functions
 */
Linkedlist* CreateLinkedlist(size_t data_size);
void Linkedlist_insert(Linkedlist* list, size_t index, void* value);
void* Linkedlist_delete(Linkedlist* list, size_t index);
void* Linkedlist_get(Linkedlist* list, size_t index);
void Linkedlist_destroy(Linkedlist* list);

/* Debug function (only for integer linked lists) */
void Linkedlist_debug(Linkedlist* list);

#endif