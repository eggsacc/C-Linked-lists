#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "linked_list.h"

/*
 * @brief Creates and initializes linked list struct.
 * @param[in] int data_size Size of input data
 * @return Linkedlist* pointer to new linked list struct.
 */
Linkedlist* CreateLinkedlist(size_t data_size)
{
    Linkedlist* list = (Linkedlist*)malloc(sizeof(Linkedlist));
    if(list == NULL)
    {
        free(list);
        printf("Initialization fail: linked list struct malloc fail\n");
    }
    list->head = NULL;
    list->tail = NULL;
    list->data_size = (uint8_t)data_size;
    list->size = 0;
    return list;
}

/* 
 * @scope Static
 * @brief Creates new node
 * @return Node* to node created
 * @note Initializes all members to NULL
 * @warning Frees node and returns NULL if malloc fails
 */
static Node* createNode()
{
    /* Create node & check if malloc successful */
    Node* temp = (Node*)malloc(sizeof(Node));
    if(temp == NULL)
    {
        free(temp);
        printf("Node malloc fail\n");
        return NULL;
    }
    /* Initialize node pointers */
    temp->data = NULL;
    temp->next = NULL;
    temp->prev = NULL;

    return temp;
}

/* 
 * @scope Static
 * @brief Allocates memory for node datafield
 * @param[in, out] Node* node to create datafield for
 * @param[in] uint8_t data_size Size of data
 * @return void
 * @note Modifies node->data pointer to point to malloced datafield
 * @warning Returns NULL if allocation fails, and frees datafield.
 */
static void createNodeDatafield(Node* node, uint8_t data_size)
{
    node->data = malloc(data_size);
    if(node->data == NULL)
    {
        free(node->data);
        printf("Node datafield creation fail\n");
        return;
    }
    return;
}

/* 
 * @brief Create and insert new node at index.
 * @param[in] Linkedlist* list Pointer to linked list struct
 * @param[in] size_t index Index to insert at. 
 * @param[in] void* value Void pointer to input data
 * @note list is taken to be 0-indexed.
 */
void Linkedlist_insert(Linkedlist* list, size_t index, void* value)
{
    /* Check if insertion index is within linked list size */
    if(index > list->size)
    {
        printf("Insert fail: index out of linked list range\n");
        return;
    }

    Node* temp = createNode();
    if(temp == NULL)
    {
        printf("Insert fail: Node malloc fail\n");
    }

    createNodeDatafield(temp, list->data_size);
    if(temp->data == NULL)
    {
        printf("Insert fail: Node datafield malloc fail\n");
        free(temp);
        return;
    }
    
    /* Copy data to node datafield */
    memcpy(temp->data, value, list->data_size);

    /*************** Insertion at beginning ***************/
    if(index == 0)
    {
        temp->next = list->head;
        /* Check if list is empty */
        if(list->size > 0)
        {
            list->head->prev = temp;
        }
        else
        {
            list->tail = temp;
        }
        /* Update new head address */
        list->head = temp;
    }

    /****************** Insertion at end ******************/
    else if(index == list->size)
    {
        if(list->tail != NULL)
        {
            list->tail->next = temp;
        }
        else
        {
            list->head = temp;
        }
        temp->prev = list->tail;
        list->tail = temp;
    }

    /***************** Insertion at index *****************/
    else
    {
        Node* temp_n = NULL;
        /* Index over halfway: traverse from tail */
        if(index >= list->size / 2)
        {
            temp_n = list->tail;
            for(int i = 0; i < list->size - index - 1; i++)
            {
                temp_n = temp_n->prev;
            }
        }
        else
        {
            temp_n = list->head;
            for(int i = 0; i < index; i++)
            {
                temp_n = temp_n->next;
            }
        }
        /* Update links */
        temp->prev = temp_n->prev;
        temp_n->prev->next = temp;
        temp->next = temp_n;
        temp_n->prev = temp;
    }
    list->size++;
    return;
}

/* 
 * @brief Deletes node at position and returns associated data
 * @param[in] Linkedlist* list Pointer to linked list struct
 * @param[in] size_t index Index to remove from
 * @note Returns NULL if list empty or invalid index
 * @warning Free returned data pointer after use 
 */
void* Linkedlist_delete(Linkedlist* list, size_t index)
{
    /* Check if index out of range */
    if(index >= list->size)
    {
        printf("Linkedlist_delete: Index out of range\n");
        return NULL;
    }

    else
    {
        void* data = NULL;
        /* Case: index = last node */
        if(index == list->size - 1)
        {
            Node* temp = list->tail;
            data = list->tail->data;
            list->tail = list->tail->prev;
            list->tail->next = NULL;
            free(temp);
        }
        /* Case: index = first node (0) */
        else if(index == 0)
        {
            Node* temp = list->head;
            data = list->head->data;
            list->head = list->head->next;
            list->head->prev = NULL;
            free(temp);
        }
        /* Case: arbitrary index */
        else
        {
            Node* temp = NULL;
            /* Index over halfway: traverse from tail */
            if(index >= list->size / 2)
            {
                temp = list->tail;
                /* Traverse to node */
                for(int i = 0; i < list->size - index - 1; i++)
                {
                    temp = temp->prev;
                }
            }
            /* Otherwise travrse from head */
            else
            {
                temp = list->head;
                /* Traverse to node */
                for(int i = 0; i < index; i++)
                {
                    temp = temp->next;
                }
            }

            data = temp->data;
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            free(temp);
        }

        list->size--;
        return data;
    }
}

/*
 * @brief Get data stored in a node.
 * @param[in] Linkedlist* list Pointer to list struct
 * @param[in] size_t index Node to retrieve data from
 * @return void* to data
 * @note Returns NULL if index is invalid
 * @warning Do not free returned pointer after use
 */
void* Linkedlist_get(Linkedlist* list, size_t index)
{
    /* Check if index out of bounds */
    if(index >= list->size)
    {
        printf("Linkedlist_get: Index out of range\n");
        return NULL;
    }
    else
    {
        Node* temp = NULL;
        /* Index over halfway: traverse from tail */
        if(index >= list->size / 2)
        {
            temp = list->tail;
            /* Traverse list to node at index */
            for(int i = 0; i < list->size - index - 1; i++)
            {
                temp = temp->prev;
            }        
        }
        /* Otherwise traverse from head */
        else
        {
            temp = list->head;
            /* Traverse list to node at index */
            for(int i = 0; i < index; i++)
            {
                temp = temp->next;
            }
        }

        /* Get data */
        return temp->data;
    }
}

/*
 * @brief Destroys linked list.
 * @param[in] Linkedlist* list Pointer to linked list
 * @return void 
 * @warning To be called only at end of main loop / function 
 */
void Linkedlist_destroy(Linkedlist* list)
{
    /* Check if list is empty */
    if(list->head == NULL)
    {
        free(list);
        return;
    }

    /* Iterate through list and free all nodes & associated data */
    Node* temp = list->head;
    Node* next = NULL;
    while(temp != NULL)
    {
        next = temp->next;
        free(temp->data);
        free(temp);
        temp = next;
    }

    /* Free linked list struct */
    free(list);
}

/*
 * @brief Print all node addresses and functions in a integer linked list.
 * Utility function to debug integer linked lists only. Used for testing
 * @param[in] Linkedlist* list Pointer to linked list
 * @return void
 */
void Linkedlist_debug(Linkedlist* list)
{
    if(list->head == NULL)
    {
        printf("Empty");
        return;
    }

    printf("Number of nodes: %d\n", list->size);

    int i = 0;
    Node* temp = list->head;

    while(temp != NULL)
    {
        printf("Node[%-2d] add: %p | Prev add: %p | Next add: %p | Data: %d\n", 
        i, temp, temp->prev, temp->next, *((int*)temp->data));
        temp = temp->next;
        i++;
    }
    printf("\n");
}