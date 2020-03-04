//
// This file contains the implementation of some auxiliary
// functions used for parsing maps (graphs) from the input,
// according to the following format:
//
// A map is described by a set of lines. Each line comprises
// a sequence of words, which are separated by "white space"
// (1 or more space/tab characters). This sequence of words
// holds the info about a country's color and its neighbours.
//
// For each line:
// (1) first word      -> colour of the country (default: "nocolor")
// (2) second word     -> name of the country
// (3) remaining words -> names of neighbouring countries
//
// An input map must satisfy the following rules:
// (A) Each country which appears as a neighbour to another
//     country must have its own line (colour/neighbour info)
// (B) If K is neighbour of L, then L must be neighbour of K
// (C) Each line must end with a newline ('\n')

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "utilities.h"
#include "constants.h"
#include "parse.h"

// Returns true if token is either an alnum or '_' (valid characters for words)

bool is_valid(int token) {
  return (isalnum(token) || token == '_');
}

// Returns true if token is either ' ' or '\t' (whitespace)

bool is_whitespace(int ch) {
  return (ch == ' ' || ch == '\t');
}

// Returns the map description represented as an adjacency list

List * read_map(FILE *fp) {
  List *map = malloc(sizeof(List) * MAX_COUNTRIES);
  if (map == NULL) terminate("read_map: out of memory");

  for (int i = 0; i < MAX_COUNTRIES; i++)
    if ((map[i] = list_create()) == NIL_LIST)
      terminate("read_map: out of memory");

  char buf[1024]; // Line buffer
  char *word;

  int n_countries = 0;

  // Read from input stream until there are no more lines
  for ( ; fgets(buf, sizeof(buf), fp); n_countries++) {
    if (n_countries >= MAX_COUNTRIES)
      terminate("read_map: too many lines");

    // Parse every word for each line and save it in its corresponding list
    for (int i = 0; buf[i] != '\0'; i++) {
      for ( ; is_whitespace(buf[i]); i++); // Skip whitespace

      if (!is_valid(buf[i]))
        terminate("read_map: invalid input"); // Unknown token found

      word = malloc(sizeof(char) * (MAX_WORD+1)); // +1 for '\0'
      if (word == NULL) terminate("read_map: out of memory");

      for (int j = 0; is_valid(buf[i]); i++, j++) {
        if (j >= MAX_WORD) terminate("read_map: word too big");
        word[j] = buf[i];

        if (!is_valid(buf[i+1])) word[++j] = '\0';
      }

      list_insert_last(map[n_countries], word);
    }
  }

  options.n_countries = n_countries;
  return map;
}
