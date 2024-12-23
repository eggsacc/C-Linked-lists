#include<stdio.h>
#include<stdlib.h>
#include"linked_list.h"

int main(void)
{
    /* Create & initialize linked list struct */
    Linkedlist* int_list = CreateLinkedlist(sizeof(int));

    /* Populate list with 10 nodes */
    int data;
    for(int i = 0; i < 5; i++)
    {
        data = i;
        /* Using append macro */
        Linkedlist_append(int_list, (void*)&data);
    }
    printf("---------------------------- Linked list with 5 nodes ----------------------------\n");
    Linkedlist_debug(int_list);

    /* Delete last node */
    Linkedlist_pop(int_list);
    printf("---------------------------- After deleting last node ----------------------------\n");
    Linkedlist_debug(int_list);

    /* Insert new node at start of list */
    data = 69;
    Linkedlist_append_head(int_list, (void*)&data);
    printf("---------------------------- After appending 69 to start ----------------------------\n");
    Linkedlist_debug(int_list);

    /* Destroy linked list after use */
    Linkedlist_destroy(int_list);
    return 0;
}