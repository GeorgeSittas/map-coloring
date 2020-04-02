// Credits: Panagiotis Stamatopoulos (http://cgi.di.uoa.gr/~takis/)

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

char *colors[] = {"red", "green", "blue", "yellow", "orange",
                  "violet", "cyan", "pink", "brown", "grey"};

int main(int argc, char **argv) {
  int n_countries;     // Number of countries in the graph
  int uncolperc = 100; // Uncolored country percentage (0 to 100)
  int density = 30;    // Graph density (0 to 100)
  int colornum = 4;    // Number of colors with which graph can be colored

  long seed = time(NULL);
  char *color, **neighb;

  if (argc == 1) {
    fprintf(stderr, "%s: Wrong usage\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  n_countries = atoi(argv[1]);

  if (argc > 2) uncolperc = atoi(argv[2]);
  if (argc > 3) density = atoi(argv[3]);
  if (argc > 4) seed = atoi(argv[4]);
  if (argc > 5) colornum = atoi(argv[5]);

  if (colornum > (int) sizeof(colors)) {
    fprintf(stderr, "%s: Too many colors\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  srand((unsigned) seed);

  // Color matrix for the countries
  color = malloc(n_countries * sizeof(char));

  // Reserve space for the 2-D triangular matrix to hold countries' borders
  neighb = malloc(n_countries * sizeof(char *));

  for (int i = 0; i < n_countries - 1; i++)
    neighb[i] = malloc((n_countries-i-1) * sizeof(char));

  // Select random color for each country
  for (int i = 0; i < n_countries; i++)
    color[i] = rand() % colornum + 1;

  // Decide randomly about borders
  for (int i = 0; i < n_countries - 1; i++) {
    for (int j = i+1; j < n_countries; j++) {
      neighb[i][j-i-1] = 0;

      if (color[i] != color[j]
       && (100.0 * rand()) / (RAND_MAX + 1.0) < (double) density)
        neighb[i][j-i-1] = 1;
    }
  }

  // Uncolor some countries (randomly), according to the given percentage
  for (int i = 0; i < (uncolperc * n_countries) / 100.0; i++) {
    int j = rand() % n_countries;

    while (color[j] == 0)
      j = (j+1) % n_countries;

    color[j] = 0;
  }

  // Finally, print out the map
  for (int i = 0; i < n_countries; i++) {
    printf("%s C%05d", (color[i] == 0 ? "nocolor" : colors[color[i]-1]), i+1);

    for (int j = 0; j < n_countries; j++) {
      // Express borders in both directions

      if (i < j)
        if (neighb[i][j-i-1] == 1)
          printf(" C%05d", j+1);

      if (i > j)
        if (neighb[j][i-j-1] == 1)
          printf(" C%05d", j+1);
    }

    printf("\n");
  }

  // Memory cleanup
  for (int i = 0; i < n_countries - 1; i++)
    free(neighb[i]);

  free(neighb);
  free(color);

  return 0;
}
