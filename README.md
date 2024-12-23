## Linked list in C

Basic implementation of a universal doubly-linked list in C. Uses `void*` to store any data type in node data field.

## Functions

1) Initialization
- `Linkedlist* CreateLinkedlist(size_t data_size)`
2) Utility
- `void Linkedlist_insert(Linkedlist* list, size_t index, void* value)`
- `void* Linkedlist_delete(Linkedlist* list, size_t index)`
- `void* Linkedlist_get(Linkedlist* list, size_t index)`
3) Destructor
- `void Linkedlist_destroy(Linkedlist* list)`

## Macros

Some macros are provided to simply insertion / deletion of nodes at either the head or tail. Macros have similar names to array operations.
- `Linkedlist_append(list, value_ptr)`
- `Linkedlist_append_head(list, value_ptr)`
- `Linkedlist_pop(list)`
- `Linkedlist_pop_head(list)`

## Usage

### 1) Initialize linked list

Initialize a linked list struct with the data field size.
```c
/* Example */
Linkedlist* list = CreateLinkedlist(sizeof(int));
```

### 2) Append / delete / get
```c
/* Inserting nodes */
int data = 65;
Linkedlist_append(list, (void*)&data);
data = 75;
Linkedlist_insert(list, 1, (void*)&data);

/* Deleting nodes */
Linkedlist_pop(list);
void* deleted_value_ptr = Linkedlist_delete(list, 1);
int deleted_value = *((int*)deleted_value_ptr);

/* Accessing node data */
void* value_ptr = Linkedlist_get(list, 1);
int value = *((int*)value_ptr);
```
### 3) Destroy

Deleted and frees all nodes in linked list structure. Only to be called at end of `main` function
```c
Linkedlist_destroy(list);
```
