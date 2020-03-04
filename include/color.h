#pragma once

#include <stdbool.h>

#include "ADT_List.h"

// Returns true if a map is valid, according to the format specified
// in parse.c (rules A and B)

bool is_map_valid(List *map);

// Returns a copy of a map

List * map_copy(List *map);

// Does this really need any documentation? :P

void map_print(List *map);

// Replaces "nocolor" with a valid color for a country in the map

void paint_country(List *map, int country, char *color);

// Replaces a country's color with "nocolor"

void unpaint_country(List *map, int country);

// Returns the index of a country in the map (-1 in case of failure)

int find_country(List *map, char *country_name);

// Returns the number of neighbours of a country in the map

int neighbour_count(List *map, int country);

// Returns true if a country in the map has neighbouring countries

bool has_neighbours(List *map, int country);

// Returns the color of a country, or NULL if it hasn't been colored yet

char * get_color(List *map, int country);

// Returns the name of a country, based on its index in map

char * get_name(List *map, int country);

// Returns true if a country in the map hasn't been colored yet

bool uncolored(List *map, int country);

// Returns true if we can color a country with a specific color. If
// the checking_validity flag is set to true, then this method won't
// disregard already-colored countries as uncolorable (this is needed
// in order to cross check whether a country has been validly colored)

bool can_color(List *map, int country, char *color, bool checking_validity);

// Sorts a list of countries based on how many neighboring countries they have

void sort_map(List *map);

// Colors a map with at most n colors so that two neighbouring countries
// have different colors. Returns true on success and false on failure

bool color_map(List *map, char **colors, int n_colors);

// Returns true if a map is colored with only the first n_clrs colors
// of the "clrs" array, in a way such that two neighbouring countries
// have different colors

bool is_valid_coloring(List *map, char *clrs[], int max_clrs, int n_clrs);
