#include "Interface.h"

#include <stdio.h>
#include <stdlib.h>

int main (void) 
{
	int firstCountry = 0 ; // Calling the insert for the first country if it is 0 
	int bufNum = 128 ;
    char buf [bufNum] ; // Support for lines at most bufNum characters long 

    for (int i = 0 ; i < bufNum ; i++) // Initializing the array with '+' so we know where the line ends
    	buf [i] = '+' ;

	Map * m = NULL ; // Creating a pointer to our map
    
    m = malloc (sizeof(Map)) ; // Creating the struct for the first country
	if (m == NULL) 
	{
    	return 1 ;
	}

	m->country = NULL ;
	m->nextCountry = NULL ;

    while (fgets (buf, sizeof(buf), stdin)) // For every line we call the function insert
    {
        printf ("Read line: %s" ,buf) ;
        insert (buf ,m ,firstCountry) ;
        for (int i = 0 ; i < bufNum ; i++) // Initializing the array with '+' so we know where the line ends and we don't get thrush from the previous lines
    		buf [i] = '+' ;
        firstCountry = 1 ; 
    }
    printMap (m) ; // Printing the map
    free_map (m) ; // Free's the allocated memory for the map
    return 0 ;
} 