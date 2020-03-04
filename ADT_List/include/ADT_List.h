// Interface file for the ADT List

#pragma once

#include <stdbool.h>

// The list is represented by the type List, whilst a list node
// is represented by the type listNode (incomplete structs)
//
// The user doesn't need to know the implementations of said types. He
// can use them directly, as well as the list_* methods seen below

typedef struct list *List;
typedef struct list_node *listNode;

// Special nil values for the list / node types

#define NIL_LIST (List) 0
#define NIL_NODE (listNode) 0

// Note 1: for all of the following methods that receive a List argument,
// the behaviour is undefined if the list is equal to NIL_LIST

// Note 2: make sure to call list_destroy() on every list that's used,
// when done using it

// Creates and returns an empty list (or NIL_LIST in case of error)

List list_create(void);

// Prints a list

void list_print(List list);

// Returns the list's size (number of nodes in the list)

unsigned list_size(List list);

// Returns true if the list is empty, false otherwise

bool list_is_empty(List list);

// Returns the first list node that contains the given string
// (or NIL_NODE, if said string can't be found in the list)

listNode list_search(List list, char *str);

// Returns the first node in a list (or NIL_NODE, if list is empty)

listNode list_begin(List list);

// Returns the succeeding node of a given node in a list (or NIL_NODE, if
// the given node is NIL_NODE). If the given node is the last node in the
// list, then list_end(list) is returned

listNode list_next(List list, listNode node);

// Returns the end of a list

listNode list_end(List list);

// Returns the i-th node in the list (or NIL_NODE, if index is out
// of bounds)

listNode list_get_node(List list, int index);

// Returns the i-th string in the list (indexing starts at 0).
// If index is out of bounds, NULL is returned

char * list_get(List list, int index);

// Returns the string contained in a given node in a list (or
// NULL if the given node is NIL_NODE)

char * list_access(List list, listNode node);

// Replaces a list node's string field with a new string

void list_replace(List list, listNode node, char *new_str);

// Inserts a new node at the tail of the list

void list_insert_last(List list, char *str);

// Inserts a new node in the list after the given node. If the given node
// is NIL_NODE, then the new node is inserted at the head of the list
//
// Assumption: the given node is either NIL_NODE or exists in the list
// (otherwise the behaviour of this method is undefined)

void list_insert_after(List list, char *str, listNode node);

// Removes the last node from the list

void list_delete_last(List list);

// Removes the given node from the list 
//
// Assumption: the given node exists in the list (otherwise the behaviour
// of this method is undefined)

void list_delete(List list, listNode node);

// Destroys a list (memory deallocation)
//
// Usage of said list after its deletion yields undefined behaviour

void list_destroy(List list);
