# map-coloring
 C program that solves the **[map coloring problem](https://en.wikipedia.org/wiki/Map_coloring)** [1].

### Install
```
git clone https://github.com/GeorgeSittas/map-coloring.git
```

### Input format
The input format is specified in [this](https://github.com/GeorgeSittas/map-coloring/blob/master/src/parse.c) file

### Random map generator
An additional map generator program (see genmap.c) is also provided. See the\
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

In order to activate the _optional_ arguments, one must provide them in the order seen above.

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

./genmap 100 | ./mapcol               // Colors a randomly generated map with 100 countries
./genmap 200 | ./mapcol | ./mapcol -c // Colors a randomly generated map with 200 countries and
                                      // checks if the coloring is valid
```
\
\
\
[1] see also: https://en.wikipedia.org/wiki/Graph_coloring
