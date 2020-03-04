# map-coloring
 C program that solves the **[map coloring problem](https://en.wikipedia.org/wiki/Map_coloring)** [1].

### Install
```
git clone https://github.com/GeorgeSittas/map-coloring.git
```

### Input format
The input format is specified [here](https://github.com/GeorgeSittas/map-coloring/blob/b7a8202f630aaae24cd155c7556905c39ec7b3a2/src/parse.c#L1-L20).

### Random map generator
An additional map generator program (see [genmap.c](https://github.com/GeorgeSittas/map-coloring/blob/master/src/genmap.c)) is also provided. See the\
"Usage" section below for instructions on how to use it.

### Compilation
```
cd map-coloring

make        // Produces the executable "mapcol" (same as "make mapcol")
make genmap // Produces the executable "genmap"
make all    // Produces both "mapcol" and "genmap" executables
```

### File cleanup
```
cd map-coloring

make clean // Deletes ALL object & executable files inside map-coloring
```

### Usage
#### mapcol options
The following command line options are available for mapcol:

- \-i \<file\> : \<file\> becomes the input stream (i.e. map is read from \<file\>
- \-c : program **only checks** if input map is colored correctly
- \-n \<num\> : \<num\> colors **can be used** to color the input map (1 ≤ \<num\> ≤ 10)

By default, the program colors a map (i.e. -c is not activated) with at most 4 colors\
(i.e. \<num\> is equal to 4) and input is read from stdin (i.e. \<file\> is stdin).

#### genmap arguments
The genmap program receives at least one command line argument: the number\
of countries in the map that it will generate. Additionally, it can receive four more\
_optional_ arguments.

The command syntax is as follows:

```
./genmap <n_countries> [<uncolperc> [<density> [<seed> [colornum]]]]
```

In order to pass the _optional_ arguments, one must provide them in the order seen above.

- \<n_countries\> : number of countries in the map
- \<uncolperc\> : percentage (0 to 100) of uncolored countries in the map (default: 100)
- \<density\> : percentage (0 to 100) which determines the map density (default: 30)
- \<seed\> : RNG seed used in srand (default: time(NULL))
- \<colornum\> : number of colors for which the generated map can definitely be colored with (default: 4)

#### Examples
```
./mapcol -i input_maps/Europe.txt               // Colors Europe.txt
./mapcol -i input_maps/Balkans_solved.txt -c    // Checks if Balkans_solved.txt is colored validly
./mapcol -i input_maps/Europe10Uncolored.txt -c // Checks if Europe10Uncolored.txt is (partially) colored validly
./mapcol -i input_maps/no4colors.txt -n 5       // Colors no4colors.txt using 5 colors
./mapcol -i input_maps/triv4.txt -c -n 3        // Checks if triv4.txt can be colored, using only 3 colors

./genmap 100 | ./mapcol               // Colors a randomly generated map with 100 countries
./genmap 200 | ./mapcol | ./mapcol -c // Colors a randomly generated map with 200 countries and
                                      // checks if the coloring is valid
```

### Notes
- The program can currently color maps consisting of 200 countries (generated with ./genmap 200)\
in under 10 seconds (on average), but it becomes significantly slower as we increase \<n_countries\>.

- An important part of the coloring algorithm is that countries (i.e. vertices, if map is seen as a graph)\
with bigger degrees are colored first (this is [well known heuristic approach in graph coloring](https://en.wikipedia.org/wiki/Greedy_coloring)).

### Possible optimizations

- Make a **1-1 mapping between integers and countries** in the map, in order to avoid dealing with\
strings (as maps become bigger and/or more dense, the string methods can cause the program to\
slow down significantly).

- **Create a lookup table**, in order to [avoid searching the whole adjacency list to find a country's\
index](https://github.com/GeorgeSittas/map-coloring/blob/b7a8202f630aaae24cd155c7556905c39ec7b3a2/src/color.c#L89-L97).

- **Keep track of the available colors** for each country, as the coloring process progresses, so that no\
time is wasted in [searching for the next available color linearly](https://github.com/GeorgeSittas/map-coloring/blob/b7a8202f630aaae24cd155c7556905c39ec7b3a2/src/color.c#L132-L163). Deciding how to encode this information\
for a country is crucial, since having a list of "available colors" becomes memory-heavy as map size grows.\
One simple approach that can solve this problem, is to encode the available colors as a binary string (int)\
that has as many bits as the total number of colors, and then process this string using bitwise operators.

- **Try a different heuristic approach**, such as prioritizing countries that have less available colors.\

\
[1] see also: https://en.wikipedia.org/wiki/Graph_coloring
