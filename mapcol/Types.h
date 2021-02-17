#ifndef __Types__
#define __Types__

typedef struct map Map ;
typedef struct country Country ;
typedef struct neighbCountry NeighbCountry ; 

struct map // Every country has a struct map
{
    Country * country ;
    Map * nextCountry ;
} ;

struct country 
{
  char colour [10] ;
  char name [33] ;
  NeighbCountry * neighbList ;
} ;

struct neighbCountry
{
	char countryName [33] ;
	 NeighbCountry * nextNeighbCountry ;
};

#endif