#ifndef __Interface__
#define __Interface__

#include "Types.h"

void insert (char * line ,Map * m ,int firstCountry) ; // Inserts the data for the countries 

void printMap (Map * map) ; // Prints the map 

void printCountry (Country * country) ; // Prints a Country 

void printNeighbors (NeighbCountry * neighbCountry) ; // Prints the neighbors of a Country

void free_map (Map * map) ; // Free's the allocated memory of the map

void free_country (Country * country) ; // Free's the allocated memory for a country

void free_neigbor (NeighbCountry * neighbor) ; // Free's the allocated memory for the neighbors of a country

#endif