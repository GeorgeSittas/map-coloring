#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "color.h"
#include "utilities.h"
#include "constants.h"

// Returns true if a map is valid, according to the format specified
// in parse.c (rules A and B)

bool is_map_valid(List *map) {

  // For each country, check if there exists a list in map for each of
  // its neighbours (rule A). If found, check if that list contains the
  // current country as a neighbour (neighbour of neighbour, rule B).

  for (int country = 0; country < options.n_countries; country++) {
    if (!has_neighbours(map, country)) continue;

    char *country_name = get_name(map, country);

    // First neighbouring country starts at the third position
    listNode curr = list_get_node(map[country], 2);

    char *curr_name;  // Current neighbouring country's name
    int neighb_index; // Current neighbouring country's index in map

    while (curr != list_end(map[country])) {
      curr_name = list_access(map[country], curr);
      neighb_index = find_country(map, curr_name);

      if (neighb_index == -1)
        return false; // Rule A is not met, so the map is invalid

      // temp traverses the neighbour list of country's current neighbour
      listNode temp = list_get_node(map[neighb_index], 1);

      while (true) {
        temp = list_next(map[neighb_index], temp);

        if (temp == list_end(map[neighb_index]))
          return false; // Rule B is not met, so the map is invalid

        if (!strcmp(list_access(map[neighb_index], temp), country_name))
          break; // Rules A and B are met for country and this neighbour
      }

      curr = list_next(map[country], curr);
    }
  }

  return true; // Input constraints have been met, so the map is valid
}

// Returns a copy of a map

List * map_copy(List *map) {
  List *copy = malloc(sizeof(List) * options.n_countries);
  if (copy == NULL) terminate("map_copy: out of memory");

  for (int i = 0; i < options.n_countries; i++)
    copy[i] = map[i];

  return copy;
}

// Does this really need any documentation? :P

void map_print(List *map) {
  for (int i = 0; i < options.n_countries; i++)
    list_print(map[i]);
}

// Replaces "nocolor" with a valid color for a country in the map

void paint_country(List *map, int country, char *color) {
  if (color != NULL && strlen(color) <= MAX_WORD
  && country >= 0 && country < options.n_countries)
    list_replace(map[country], list_begin(map[country]), color);
}

// Replaces a country's color with "nocolor"

void unpaint_country(List *map, int country) {
  paint_country(map, country, "nocolor");
}

// Returns the index of a country in the map (-1 in case of failure)

int find_country(List *map, char *country_name) {
  for (int i = 0; i < options.n_countries; i++)
    if (!strcmp(get_name(map, i), country_name))
      return i;

  return -1;
}

// Returns the number of neighbours of a country in the map

int neighbour_count(List *map, int country) {

  // Don't count the country's name and color!
  return list_size(map[country]) - 2;
}

// Returns true if a country in the map has neighbouring countries

bool has_neighbours(List *map, int country) {
  return (neighbour_count(map, country) > 0);
}

// Returns the color of a country, or NULL if it hasn't been colored yet

char * get_color(List *map, int country) {
  char *clr = list_get(map[country], 0);
  return !strcmp(clr, "nocolor") ? NULL : clr;
}

// Returns the name of a country, based on its index in map

char * get_name(List *map, int country) {
  return list_get(map[country], 1);
}

// Returns true if a country in the map hasn't been colored yet

bool uncolored(List *map, int country) {
  return (get_color(map, country) == NULL);
}

// Returns true if we can color a country with a specific color. If
// the checking_validity flag is set to true, then this method won't
// disregard already-colored countries as uncolorable (this is needed
// in order to cross check whether a country has been validly colored)

bool can_color(List *map, int country, char *color, bool checking_validity) {
  // Check if the country has already been colored, or if it's validly colored
  if (!checking_validity && !uncolored(map, country)) return false;

  // Check if the country (vertex) has degree 0 => is always colorable
  if (!has_neighbours(map, country)) return true;

  // First neighbouring country starts at the third position
  listNode curr = list_get_node(map[country], 2);

  char *curr_color;
  char *curr_name;

  // Check if there's a neighbouring country with the same color

  while (curr != list_end(map[country])) {
    curr_name = list_access(map[country], curr);
    curr_color = get_color(map, find_country(map, curr_name));

    if (curr_color != NULL && !strcmp(curr_color, color))
      return false; // Already colored a neighbour with this color

    curr = list_next(map[country], curr);
  }

  return true;
}

// [Auxiliary] Function that compares two countries, based on the
// number of their neighbours (needed for qsort)

int comparator(const void *p, const void *q) {
  int l = list_size(* ((List *) p)) - 2;
  int r = list_size(* ((List *) q)) - 2;

  return (r - l);
} 

// Sorts a list of countries based on how many neighboring countries they have

void sort_map(List *map) {
  qsort((void *) map, options.n_countries, sizeof(List), comparator);
}

// Colors a map with at most n colors so that two neighbouring countries
// have different colors. Returns true on success and false on failure

bool color_map(List *map, char **colors, int n_colors) {

  // The algorithm works as follows:
  //
  // for each country:
  //   1. If it hasn't already been colored, color it with the first
  //      available color in the colors array. Otherwise, continue to
  //      the next country.
  //
  //   2. If such a color has been found (meaning that the country can
  //      be colored), and if, after it's been colored, there are no more
  //      countries to color, we're done and the map has been completely
  //      colored. Otherwise (if not all countries have been colored),
  //      recursively color the rest of the map (i.e. jump to "for each
  //      country").
  //
  //   3. Otherwise, backtrack to the last country colored and choose a
  //      different color for it.

  for (int country = 0; country < options.n_countries; country++) {
    if (uncolored(map, country)) {
      for (int curr_clr = 0; curr_clr < n_colors; curr_clr++) {
        if (can_color(map, country, colors[curr_clr], false)) {
          paint_country(map, country, colors[curr_clr]);

          if (color_map(map, colors, n_colors) == false)
            unpaint_country(map, country); // Backtrack
          else
            return true; // Map can be colored
        }
      }

      return false; // Current country couldn't be colored
    }
  }

  return true; // All countries are colored
}

// Returns true if a map is colored with only the first n_clrs colors
// of the "clrs" array, in a way such that two neighbouring countries
// have different colors

bool is_valid_coloring(List *map, char *clrs[], int max_clrs, int n_clrs) {
  for (int i = 0; i < options.n_countries; i++) {
    char *curr_clr = get_color(map, i);
    if (curr_clr == NULL) continue; // This country hasn't been colored yet

    if (!can_color(map, i, curr_clr, true))
      return false; // invalid coloring: two neighbours have the same color

    if (n_clrs < max_clrs-1 && !strcmp(curr_clr, clrs[n_clrs])) {
      printf("More than %d colors used\n", n_clrs);
      return false; // invalid coloring: n_clrs+1 colors used instead of n_clrs
    }
  }

  return true;
}

