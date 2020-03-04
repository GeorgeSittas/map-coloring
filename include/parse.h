#pragma once

#include <stdbool.h>

#include "ADT_List.h"

// Returns true if token is either an alnum or '_' (valid characters for words)

bool is_valid(int token);

// Returns true if token is either ' ' or '\t' (whitespace)

bool is_whitespace(int token);

// Returns the map description represented as an adjacency list

List * read_map(FILE *fp);
