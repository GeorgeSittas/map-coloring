#pragma once

#include <stdbool.h>

#include "ADT_List.h"

struct options {
  FILE *input_file; // This is stdin by default, and is changed if -i is given
  bool c_activated; // Program only checks if input map is colored correctly
  int n_colors;     // This is 4 by default, and is changed if -n is given
  int n_countries;  // Additional info: how many countries the map contains
};

extern struct options options;

// Processes Command Line Arguments
//
// Valid options:
// -i <file> : <file> becomes the input stream
// -c : program only checks if input map is colored correctly
// -n <num> : specifies how many colors can be used to color input map

void process_CLA(int argc, char **argv);

// [Auxiliary] Function that compares two countries, based on the
// number of their neighbours (needed for qsort)

int comparator(const void *p, const void *q);

// Prints msg and terminates the program

void terminate(char *msg);

// Deallocates the map description list

void cleanup(List *map);
