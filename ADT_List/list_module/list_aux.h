// Auxiliary methods for the ADT List module

#pragma once

#include "ADT_List.h"

// Creates and returns a new list node with given string and next fields
// (returns NIL_NODE if the memory cannot be allocated)

listNode list_aux_new_node(char *str, listNode next);

// Destroys a list node (memory deallocation)

void list_aux_destroy_node(listNode node);
