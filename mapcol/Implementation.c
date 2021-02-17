#include "Interface.h"

#include <stdio.h>
#include <stdlib.h>

void insert (char * line ,Map * m ,int firstCountry) // Inserts the data for the specific country by creating a struct country
{
	int   j = 0 ,word = 1 ,firstNeigb = 0 ,createFirstNieghbCountry = 0 ,createNieghbCountry = 0 ,firstNextCountry = 0 ; // If its 1 we have already create the struct
	NeighbCountry * lastNeighbC = NULL ;
	NeighbCountry * nextNeighbC = NULL ;
	Map * lastMap = NULL ; 
	Map * nextMap = NULL ;

	if (firstCountry == 0) // It's the first Country
	{
		m->country = malloc (sizeof(Country)) ; // Creating the struct for the first country
		if (m->country == NULL) 
		{
	    	printf("!! ERROR MALLOC IN FUCNTION INSERT !!") ;
		}
		m->country->neighbList = NULL ;
		for (int i = 0 ; i < 10 ; i++) // Initializing the array with '+' so we know where the line ends
	    	m->country->colour [i] = '+' ;

	    for (int i = 0 ; i < 33 ; i++) // Initializing the array with '+' so we know where the line ends
	    	m->country->name [i] = '+' ;

		int i = 0 ;
		while (line [i] != '+')
		{
			if (line [i] != ' ' && line [i] != '\t' && word  == 1) // Inserting the colour for the first country
			{
				m->country->colour [j] = line [i] ;
				j++ ;
				i++ ;
			}
			else if ((line [i] == ' ' || line [i] == '\t') && word  == 1) // We have inserted the colour so we are going to the next word which is the name of the country
			{
				m->country->colour [j] = '\0' ;
				j = 0 ;
				word = 2 ;
				do
				{
					i++ ;
				}while (line [i] == ' ' || line [i] == '\t') ;
			}
			else if (line [i] != ' ' && line [i] != '\t' && word  == 2) // Inserting the name for the first country
			{
				m->country->name [j] = line [i] ;
				i++ ;
				j++ ;
			}
			else if ((line [i] == ' ' || line [i] == '\t') && word  == 2) // We have inserted the name for the first country so we are going to the next word (if we have one) which is the first neighbor
			{
				m->country->name [j] = '\0' ;
				j = 0 ;
				word = 3 ;
				do
				{
					i++ ;
				}while (line [i] == ' ' || line [i] == '\t') ;
			}
			else if (word  == 3) // Inserting the neighbors for the first country
			{	
				if (firstNeigb == 1) // It's not the first neighbor of the first Country
				{
					if (createNieghbCountry == 0) // If its 0 we have to create the struct
					{
						lastNeighbC = m->country->neighbList ; 
						nextNeighbC = m->country->neighbList->nextNeighbCountry ;

						while (nextNeighbC != NULL) // Going to the last node of the list
						{
							lastNeighbC = nextNeighbC ;
							nextNeighbC = nextNeighbC->nextNeighbCountry ;
						}
						lastNeighbC->nextNeighbCountry = malloc ( sizeof(NeighbCountry)) ;

						if (lastNeighbC->nextNeighbCountry == NULL) 
						{
					    	printf("!! ERROR MALLOC IN FUCNTION INSERT !!") ;
						}
						lastNeighbC->nextNeighbCountry->nextNeighbCountry = NULL ;

						for (int i = 0 ; i < 33 ; i++) // Initializing the array with '+' so we know where the line ends
			    			lastNeighbC->nextNeighbCountry->countryName[i] = '+' ;	
			    		createNieghbCountry = 1 ;				
					}
					if (line [i] != ' ' && line [i] != '\t') // Inserting the name of the neighbor country
					{
						lastNeighbC->nextNeighbCountry->countryName [j] = line [i] ;
						j++ ;
						i++ ;
					}
					else if ((line [i] == ' ' || line [i] == '\t')) // The name of the neighbor country ended so now we are going to the next name (if there is one)
					{
						lastNeighbC->nextNeighbCountry->countryName [j] = '\0' ;
						j = 0 ;
						do
						{
							i++ ;
						}while (line [i] == ' ' || line [i] == '\t') ;
						createNieghbCountry = 0 ; // Now we finished this neighbCountry's name so we need the next time to create a NieghbCountry struct for the next neighbor country (if there is one)
					}					
				}
				else // It's the first neighbor of the first country
				{
					if (createFirstNieghbCountry == 0) // If its 0 we create the struct for the neighbor country otherwise we have already created
					{
						m->country->neighbList = malloc (sizeof (NeighbCountry)) ;

						if (m->country->neighbList == NULL) 
						{
					    	printf("!! ERROR MALLOC IN FUCNTION INSERT !!") ;
						}
						m->country->neighbList->nextNeighbCountry = NULL ;

						for (int i = 0 ; i < 33 ; i++) // Initializing the array with '+' so we know where the line ends
			    			m->country->neighbList->countryName [i] = '+' ;
			    		createFirstNieghbCountry = 1 ;
					}					
					if (line [i] != ' ' && line [i] != '\t') // Inserting the name of the first neighbor of the first country
					{
						m->country->neighbList->countryName [j] = line [i] ;
						j++ ;
						i++ ;
					}
					else if ((line [i] == ' ' || line [i] == '\t')) // The name of the first neighbor of the first country finished so we are going to the next word which is the name of the second neighbor of the first country (if there is one)
					{
						m->country->neighbList->countryName [j] = '\0' ;
						j = 0 ;
						do
						{
							i++ ;
						}while (line [i] == ' ' || line [i] == '\t') ;
						firstNeigb = 1 ;
					}
				}
			}
		}
	}
	else // Not the first Country
	{ 
		if (firstNextCountry == 0) // If its 0 we have to create the struct otherwise we already have created
		{
			lastMap = m ; 
			nextMap = m->nextCountry ;
			while (nextMap != NULL) // Going to the last node of the list
			{
				firstNextCountry = 1 ;
				lastMap = lastMap->nextCountry ;
				nextMap = nextMap->nextCountry ;
			}
			lastMap->nextCountry = malloc (sizeof (Map)) ;
			if (lastMap->nextCountry == NULL) 
			{
		    	printf("!! ERROR MALLOC IN FUCNTION INSERT !!") ;
			}
			lastMap->nextCountry->country = NULL ;
			lastMap->nextCountry->nextCountry = NULL ;

			lastMap->nextCountry->country = malloc( sizeof (Country)) ;
			if (lastMap->nextCountry->country == NULL) 
			{
		    	printf("!! ERROR MALLOC IN FUCNTION INSERT !!") ;
			}
			lastMap->nextCountry->country->neighbList = NULL ;
			for (int i = 0 ; i < 10 ; i++) // Initializing the array with '+' so we know where the line ends
		    	lastMap->nextCountry->country->colour [i] = '+' ;

		    for (int i = 0 ; i < 33 ; i++) // Initializing the array with '+' so we know where the line ends
		    	lastMap->nextCountry->country->name [i] = '+' ;
		    firstNextCountry == 1 ;
		}

		int i = 0 ;
		while (line [i] != '+')
		{
			if (line [i] != ' ' && line [i] != '\t' && word  == 1) // Inserting the colour of the specific country
			{
				lastMap->nextCountry->country->colour [j] = line [i] ;
				j++ ;
				i++ ;
			}
			else if ((line [i] == ' ' || line [i] == '\t') && word  == 1) // The colour of the specific country ended so now we are going to the next word which is the name of the country
			{
				lastMap->nextCountry->country->colour [j] = '\0' ;
				j = 0 ;
				word = 2 ;
				do
				{
					i++ ;
				}while (line [i] == ' ' || line [i] == '\t') ;
			}
			else if (line [i] != ' ' && line [i] != '\t' && word  == 2) // Inserting the name of the specific country
			{
				lastMap->nextCountry->country->name [j] = line [i] ;
				i++ ;
				j++ ;
			}
			else if ((line [i] == ' ' || line [i] == '\t') && word  == 2) // The name of the specific country ended so now we are going to the next word (if there is one) which is the first neighbor of the country
			{
				lastMap->nextCountry->country->name [j] = '\0' ;
				j = 0 ;
				word = 3 ;
				do
				{
					i++ ;
				}while (line [i] == ' ' || line [i] == '\t') ;
			}
			else if (word  == 3) // It's a neighbor
			{
				if (firstNeigb == 1) // It's not the first neighbor
				{
					if (createNieghbCountry == 0) // If its 0 we have to create the struct for the next neighbor otherwise we have already created the struct
					{
						lastNeighbC = lastMap->nextCountry->country->neighbList ; 
						nextNeighbC = lastMap->nextCountry->country->neighbList->nextNeighbCountry ;

						while (nextNeighbC != NULL) // Going to the last node of the list
						{
							lastNeighbC = nextNeighbC ;
							nextNeighbC = nextNeighbC->nextNeighbCountry ;
						}
						lastNeighbC->nextNeighbCountry = malloc (sizeof (NeighbCountry)) ;

						if (lastNeighbC->nextNeighbCountry == NULL) 
						{
					    	printf("!! ERROR MALLOC IN FUCNTION INSERT !!") ;
						}
						lastNeighbC->nextNeighbCountry->nextNeighbCountry = NULL ;

						for (int i = 0 ; i < 33 ; i++) // Initializing the array with '+' so we know where the line ends
			    			lastNeighbC->nextNeighbCountry->countryName [i] = '+' ;	
			    		createNieghbCountry = 1 ;				
					}
					if (line [i] != ' ' && line [i] != '\t') // Inserting the name of the specific neighbor
					{
						lastNeighbC->nextNeighbCountry->countryName [j] = line [i] ;
						j++ ;
						i++ ;
					}
					else if ((line [i] == ' ' || line [i] == '\t')) // The name of the specific neighbor ended so now we are going to the next word (if there is one) which is the next neighbor's name
					{
						lastNeighbC->nextNeighbCountry->countryName [j] = '\0' ;
						j = 0 ;
						do
						{
							i++ ;
						}while (line [i] == ' ' || line [i] == '\t') ;
						createNieghbCountry = 0 ; // Now we finished this neighbCountry's name so we need the next time to create a NieghbCountry struct if there is another neighbor
					}					
				}
				else // Its the first neighbor
				{
					if (createFirstNieghbCountry == 0) // If its 0 we have to create the struct otherwise we have already create it
					{
						lastMap->nextCountry->country->neighbList = malloc (sizeof (NeighbCountry)) ;

						if (lastMap->nextCountry->country->neighbList == NULL) 
						{
					    	printf("!! ERROR MALLOC IN FUCNTION INSERT !!") ;
						}
						lastMap->nextCountry->country->neighbList->nextNeighbCountry = NULL ;

						for (int i = 0 ; i < 33 ; i++) // Initializing the array with '+' so we know where the line ends
			    			lastMap->nextCountry->country->neighbList->countryName [i] = '+' ;
			    		createFirstNieghbCountry = 1 ;
					}					
					if (line [i] != ' ' && line [i] != '\t') // Inserting the name of the first neighbor of the specific country
					{
						lastMap->nextCountry->country->neighbList->countryName [j] = line [i] ;
						j++ ;
						i++ ;
					}
					else if ((line [i] == ' ' || line [i] == '\t')) // The name of the first neighbor of the specific country ended so now we are going to the next word (if there is one) which is the name of the second neighbor of the specific country
					{
						lastMap->nextCountry->country->neighbList->countryName [j] = '\0' ;
						j = 0 ;
						do
						{
							i++ ;
						}while (line [i] == ' ' || line [i] == '\t') ;
						firstNeigb = 1 ;
					}
				}
			}
		}
	}
}

void printMap (Map * map) // Prints the map
{
	printCountry (map->country) ; // Prints the first country
	while (map->nextCountry != NULL) // Prints the other countries if there are any
	{
		map = map->nextCountry ;
		printCountry (map->country) ;
	}
}

void printCountry (Country * country) // Prints a Country 
{
	printf("\n The country = %s has colour = %s and for neighbors : \n" ,country->name ,country->colour) ;
	printNeighbors (country->neighbList) ; // Prints the neighbors of a country
}

void printNeighbors (NeighbCountry * neighbCountry) // Prints the neighbors of a Country
{ 
	if (neighbCountry != NULL) // If the country has neighbors
	{
		printf (" %s\n", neighbCountry->countryName) ; // Prints the first neighbor
		while (neighbCountry->nextNeighbCountry != NULL) // Prints the other neighbors if there are any
		{
			neighbCountry = neighbCountry->nextNeighbCountry ;
			printf (" %s\n" ,neighbCountry->countryName) ;
		}
	}
	else
	{
		printf(" No neighbors\n");
	}
}

void free_map (Map * map) // Free's the allocated memory of the map
{
	Map * m = map ; // We dont want to chanege where the map pointer points so we are going to use the m pointer
	Map * lastMap = map ;
	Map * prevMap = map ; // So we can make the pointer of the previous Map of the Map we freeing point to NULL
	free_country (m->country) ; // Free's the allocated memory for the first country
	m->country = NULL ;
	while (m->nextCountry != NULL) // Freeing the allocated memory for all the countries
	{
		m = m->nextCountry ;
		free_country (m->country) ; // Free's the allocated memory for a country
		m->country = NULL ;
	}
	// Freeing the allocated memory for all the map structs
	while (map != NULL) // Freeing memory until the map is empty
	{
		while (lastMap->nextCountry != NULL) // Finding the last Map and freeing the allocated memory
		{
			prevMap = lastMap ;
			lastMap = lastMap->nextCountry ;
		}
		prevMap->nextCountry = NULL ;
		free (lastMap) ; // Freeing the memory for the last map
		if (prevMap == lastMap) // we have only one map remaining and now we will free its memory so the function must stop
			map = NULL ;
		lastMap = map ;
		prevMap = map ;
	}
}

void free_country (Country * country) // Free's the allocated memory for a country
{
	if (country->neighbList != NULL) // If the country has neighbors we freeing the allocated memory for the neighbors
	{
		free_neigbor (country->neighbList) ; // Free's the allocated memory for the neighbors of a country
	}
	free(country) ;
}

void free_neigbor (NeighbCountry * neighbor) // Free's the allocated memory for the neighbors of a country
{
	NeighbCountry * lastNeighbor = neighbor ;
	NeighbCountry * prevNeighbor = neighbor ; // So we can make the pointer of the previous neighbor of the country we freeing point to NULL
	while (neighbor != NULL) // Freeing memory until the neighblist is empty
	{
		while (lastNeighbor->nextNeighbCountry != NULL) // Finding the last neighbor and freeing the allocated memory
		{
			prevNeighbor = lastNeighbor ;
			lastNeighbor = lastNeighbor->nextNeighbCountry ;
		} 
		if (prevNeighbor == lastNeighbor) // we have only one neighbor remaining and now we will free its memory so the function must stop
			neighbor = NULL ;
		prevNeighbor->nextNeighbCountry = NULL ;
		free (lastNeighbor) ; // Freeing the memory for the last neighbor
		lastNeighbor = neighbor ;
		prevNeighbor = neighbor ;
	}
}