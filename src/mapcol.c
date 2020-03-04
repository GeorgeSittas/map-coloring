#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "constants.h"
#include "utilities.h"
#include "ADT_List.h"
#include "color.h"
#include "parse.h"

struct options options; // See utilities.h for the "struct options" definition

int main(int argc, char **argv) {
  char *colors[] = {"red", "green", "blue", "yellow", "orange",
                    "violet", "cyan", "pink", "brown", "grey"};

  int max_colors = sizeof(colors) / sizeof(colors[0]);

  process_CLA(argc, argv);

  int n_colors = options.n_colors;
  if (n_colors <= 0 || n_colors > max_colors)
    terminate("Invalid number of colors");

  List *map = read_map(options.input_file);

  if (!is_map_valid(map)) {
    cleanup(map);
    terminate("Map is invalid (format rules weren't met)");
  }

  if (options.c_activated) {
    printf("Map is %scolored correctly\n",
          is_valid_coloring(map, colors, max_colors, n_colors) ? "" : "not ");
    goto exit_prog; // Go directly to memory clean up & file closing
  }

  // Keep a non-sorted version of the input map, so that we can
  // print the countries in the same order as they were entered

  List *non_sorted_map = map_copy(map);

  // Heuristic: high degree countries (vertices) will be colored first
  sort_map(map);

  // If map can be colored && the coloring is valid, print the result.
  // Otherwise notify the user that the map couldn't be colored

  if (color_map(map, colors, n_colors) == true) {
    if (is_valid_coloring(map, colors, max_colors, n_colors))
      map_print(non_sorted_map);
    else
      printf("If you can see this message, it's time for debugging\n");
  }
  else
    printf("The map cannot be colored with %d colors\n", n_colors);

exit_prog:

  cleanup(map);

  if (!options.c_activated)        free(non_sorted_map);
  if (options.input_file != stdin) fclose(options.input_file);

  return 0;
}
