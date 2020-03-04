// This file contains the implementation of the ADT List,
// as described in the ADT_List.h interface file

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list_aux.h" // Auxiliary methods
#include "ADT_List.h" // interface file for the ADT List

// In this implementation of the ADT List, the empty list is
// represented by a dummy list node
//
// The List is implemented as a structure that contains the list's dummy
// head node, an auxiliary pointer to the list's last node and an integer
// representing the list's size. On the other hand, the list's node is
// represented simply as a structure with a string field (i.e. the node's)
// string value) and a pointer to the next node

struct list {
  listNode dummy;
  listNode last;
  size_t size;
};

struct list_node {
  char *str;
  listNode next;
};

// Creates and returns a new list node with given string and next fields
// (returns NIL_NODE if the memory cannot be allocated)

listNode list_aux_new_node(char *str, listNode next) {
  listNode new_node;

  if ((new_node = malloc(sizeof(*new_node))) == NULL)
    return NIL_NODE;

  new_node->str = str; // We don't use additional memory for str!
  new_node->next = next;

  return new_node;
}

// Destroys a list node (memory deallocation)

void list_aux_destroy_node(listNode node) {
  free(node);
}

// Creates and returns an empty list (or NIL_LIST in case of error)

List list_create(void) {
  List list = malloc(sizeof(*list));
  if (list == NULL) return NIL_LIST;

  list->dummy = list_aux_new_node(NULL, NIL_NODE);

  if (list->dummy == NIL_NODE) {
    free(list);
    return NIL_LIST;
  }

  list->last = list->dummy;
  list->size = 0;

  return list;
}

// Prints a list

void list_print(List list) {
  listNode curr = list->dummy->next; // first non-dummy node

  while (curr != NIL_NODE) {
    printf("%s%s", curr->str, (curr->next == NIL_NODE) ? "" : " ");
    curr = curr->next;
  }

  printf("\n");
}

// Returns the list's size (number of nodes in the list)

size_t list_size(List list) {
  return list->size;
}

// Returns true if the list is empty, false otherwise

bool list_is_empty(List list) {
  return (list->size == 0) ? true : false;
}

// Returns the first list node that contains the given string
// (or NIL_NODE, if said string can't be found in the list)

listNode list_search(List list, char *str) {
  if (str == NULL) return NIL_NODE;

  listNode curr = list->dummy->next; // First non-dummy node

  while (curr != NIL_NODE) {
    if (!strcmp(curr->str, str))
      return curr;

    curr = curr->next;
  }

  return NIL_NODE;
}

// Returns the first node in a list (or NIL_NODE, if list is empty)

listNode list_begin(List list) {
  return list_is_empty(list) ? NIL_NODE : list->dummy->next;
}

// Returns the succeeding node of a given node in a list (or NIL_NODE, if
// the given node is NIL_NODE). If the given node is the last node in the
// list, then list_end(list) is returned

listNode list_next(List list, listNode node) {
  return (node == NIL_NODE) ? NIL_NODE : node->next;
}

// Returns the end-signalling node of a list

listNode list_end(List list) {
  return NIL_NODE;
}

// Returns the i-th node in the list (or NIL_NODE, if index is out
// of bounds)

listNode list_get_node(List list, int index) {
  if (index < 0 || index >= list->size) return NIL_NODE;

  listNode curr = list->dummy->next; // First non-dummy node
  for (int i = 0; i < index; i++)
    curr = curr->next;

  return curr;
}

// Returns the ith string in the list (indexing starts at 0).
// If index is out of bounds, NULL is returned

char * list_get(List list, int index) {
  if (index < 0 || index >= list->size) return NULL;

  listNode curr = list->dummy->next; // First non-dummy node
  for (int i = 0; i < index; i++)
    curr = curr->next;

  return curr->str;
}

// Returns the string contained in a given node in a list (or
// NULL if the given node is NIL_NODE)

char * list_access(List list, listNode node) {
  return (node == NIL_NODE) ? NULL : node->str;
}

// Replaces a list node's string field with a new string

void list_replace(List list, listNode node, char *new_str) {
  if (node != NIL_NODE && new_str != NULL)
    strcpy(node->str, new_str);
}

// Inserts a new node at the tail of the list

void list_insert_last(List list, char *str) {
  list_insert_after(list, str, list->last);
}

// Inserts a new node in the list after the given node. If the given node
// is NIL_NODE, then the new node is inserted at the head of the list
//
// Assumption: the given node is either NIL_NODE or exists in the list
// (otherwise the behaviour of this method is undefined)

void list_insert_after(List list, char *str, listNode node) {
  if (str == NULL) return;
  if (node == NIL_NODE) node = list->dummy;

  listNode new_node = list_aux_new_node(str, node->next);
  if (new_node == NIL_NODE) return;

  node->next = new_node;
  list->size++;

  if (node == list->last) list->last = node->next;
}

// Removes the last node from the list

void list_delete_last(List list) {
  list_delete(list, list->last);
}

// Removes the given node from the list 
//
// Assumption: the given node exists in the list (otherwise the behaviour
// of this method is undefined)

void list_delete(List list, listNode node) {
  if (node == NIL_NODE) return;

  listNode curr = list->dummy;

  // Find the node before the to-be-deleted node
  while (curr->next != node)
    curr = curr->next;

  if (node == list->last) list->last = curr;

  listNode temp = node->next;
  list_aux_destroy_node(node);
  curr->next = temp;

  list->size--;
}

// Destroys a list (memory deallocation)
//
// Usage of said list after its deletion yields undefined behaviour

void list_destroy(List list) {
  listNode curr = list->dummy;
  listNode temp;

  while (curr != NIL_NODE) {
    temp = curr;
    curr = curr->next;
    list_aux_destroy_node(temp);
  }

  free(list);
}
