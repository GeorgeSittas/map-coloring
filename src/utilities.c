#include <stdlib.h>
#include <stdio.h>

#include "constants.h"
#include "ADT_List.h"
#include "utilities.h"

// Processes Command Line Arguments
//
// Valid options:
// -i <file> : <file> becomes the input stream
// -c : program only checks if input map is colored correctly
// -n <num> : specifies how many colors can be used to color input map

void process_CLA(int argc, char **argv) {
  options.input_file  = stdin;
  options.c_activated = false;
  options.n_colors    = 4;

  int argind; // current program argument index

  for (argind = 1; argind < argc && argv[argind][0] == '-'; argind++) {
    switch (argv[argind][1]) {
      case 'i':
        if (argv[++argind] == NULL)
          terminate("Invalid program arguments");

        if ((options.input_file = fopen(argv[argind], "r")) == NULL)
          terminate("Cannot open input file");

        break;

      case 'c':
        options.c_activated = true;
        break;

      case 'n':
        if (argv[++argind] == NULL)
          terminate("Invalid program arguments");

        for (int i = 0; argv[argind][i] != '\0'; i++)
          if (!isdigit(argv[argind][i]))
            terminate("Invalid program arguments");

        options.n_colors = atoi(argv[argind]);
        break;

      default:
        terminate("Invalid program arguments");
    }
  }

  // Takes care of option arguments not starting with a dash ('-')
  if (argind < argc) terminate("Invalid program arguments");
}

// Prints msg and terminates the program

void terminate(char *msg) {
  fprintf(stderr, "%s\n", msg);
  exit(EXIT_FAILURE);
}

// Deallocates the map description list

void cleanup(List *map) {
  for (int i = 0; i < MAX_COUNTRIES; i++) {
    listNode curr = list_begin(map[i]);

    // Deallocate memory for all the words in the current list
    while (curr != list_end(map[i])) {
      free(list_access(map[i], curr));
      curr = list_next(map[i], curr);
    }

    list_destroy(map[i]);
  }

  free(map);
}
