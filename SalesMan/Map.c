/*
 * Map.c
 *
 *  Created on: Oct 7, 2015
 *      Author: James Davis
 *      Contains: The code to generate and interact with a map of cities
 */
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "bruteSales.h"
#define NUMBEROFCITIES 20

struct map{
	int numOfCities;
	double distances[NUMBEROFCITIES][NUMBEROFCITIES];
	int numberOfTours;
	int numOfGenerations;
	int percentMutations;
	int percentElites;
	int best[NUMBEROFCITIES + 1];
	int* generation;

};

//Assumes that there are two files names theCities.txt and thePresets.txt
//and reads those files to find out all the info it needs to create the
//map and store the data.
struct map* createMap()
{
	FILE* cities = fopen("theCities.txt","r");
	FILE* presets = fopen("thePresets.txt","r");
	if(!presets || !cities)
	{
		printf("\n\nEither theCities.txt or thePresets.txt is missing. Program exiting.\n\n");
		exit(1);
	}

	struct map *newMap = malloc(sizeof(struct map));
	double tempMutations,tempElites;

	//Grab the numbers from the presets
	fscanf(presets,"%d\n",&newMap->numberOfTours);
	fscanf(presets,"%d\n",&newMap->numOfGenerations);
	fscanf(presets,"%lf\n",&tempMutations);
	fscanf(presets,"%lf\n",&tempElites);
	fscanf(presets,"%d\n",&newMap->numOfCities);

	
	if(tempMutations < 1)
		newMap->percentMutations = tempMutations*100;
	else
		newMap->percentMutations = tempMutations;
	if(tempElites < 1)
		newMap->percentElites = tempElites*100;
	else
		newMap->percentElites = tempElites;

	//Sets the percentages to useful numbers
	newMap->percentElites = (newMap->numberOfTours*newMap->percentElites)/100;
	newMap->percentMutations = (newMap->numberOfTours*newMap->percentMutations)/100;

	int x,y;
	for(x = 0; x < NUMBEROFCITIES; x++)
	{
		for(y = 0; y < NUMBEROFCITIES; y++)
		{
			if(x != y)
				fscanf(cities,"%lf\n",&newMap->distances[x][y]);
			else
				newMap->distances[x][y] = 0;
		}
	}
	for(x = 0; x < newMap->numOfCities; x++)
	{
		newMap->best[x] = x;
	}
	newMap->best[newMap->numOfCities] = 0;
	fclose(presets);
	fclose(cities);

	//Create the first generation
	newMap->generation = malloc(sizeof(int) * (newMap->numberOfTours * (newMap->numOfCities - 1)));

	return newMap;
}

//Gets the distance between the two passed cities
double getDistance(struct map* myMap,int source, int destination)
{
	return myMap->distances[source][destination];
}

//Calculates the total distance and returns
double getDistanceOfTrail(struct map* myMap,int* trail)
{
	int x;
	double sum = 0;
	for(x = 0; x < myMap->numOfCities-2;x++)
	{
		sum += getDistance(myMap,trail[x],trail[x+1]);
	}

	sum += getDistance(myMap,0,trail[0]);
	sum += getDistance(myMap,trail[myMap->numOfCities-2],0);
	return sum;
}

double getDistanceOfBestTrail(struct map* myMap)
{
	int x;
	double sum = 0;
	for(x = 0; x < myMap->numOfCities-1;x++)
	{
		sum += getDistance(myMap,myMap->best[x],myMap->best[x+1]);
	}
	sum += getDistance(myMap,myMap->best[myMap->numOfCities-1],0);
	return sum;
}

void printPresets(struct map* newMap)
{
	printf("\nTours: %d\nGenerations: %d\nMutations: %d\nElites: %d\nCities: %d",newMap->numberOfTours,newMap->numOfGenerations,newMap->percentMutations,newMap->percentElites,newMap->numOfCities);
}

int getNumCities(struct map* newMap)
{
	return newMap->numOfCities;
}

void setBest(struct map* newMap,int* newBest)
{
	int x;
	for(x = 0; x < newMap->numOfCities-1; x++)
	{
		newMap->best[x+1] = newBest[x];
	}
	return;
}

int getBestEntry(struct map* newMap, int location)
{
	return newMap->best[location];
}

double printBestTrail(struct map* newMap)
{
	printf("\nThe best trail is: 	 ");
	int x;
	double distance;
	for(x = 0; x < newMap->numOfCities+1; x++)
	{
		printf("%d ",newMap->best[x]);
	}
	printf("\n");

	distance = getDistanceOfBestTrail(newMap);
	printf("With distance:	 	 %0.2lf",distance);
	return distance;
}

/***************Generation algorithms*****************/

double getDistanceOfTrailGeneration(struct map* myMap,int start)
{
	int x;
	double sum = 0;
	for(x = 0; x < myMap->numOfCities-1;x++)
	{
		sum += getDistance(myMap,myMap->generation[start+x],myMap->generation[start+x+1]);
	}
	sum += getDistance(myMap,0,myMap->generation[start]);
	sum += getDistance(myMap,myMap->generation[myMap->numOfCities-1 + start],0);
	return sum;
}

int calcArrayIndex(struct map* nMap,int x,int y)
{
	if(x == 0 && y == 0)
		return 0;
	else if(x <= nMap->numberOfTours)
		return (nMap->numOfCities-1)*x + y;
	else
		return 0;

}

void printGeneration(struct map* nMap)
{
	int x,y;
	printf("\n");
	for(x = 0; x < nMap->numberOfTours; x++)
	{
		for(y = 0; y < nMap->numOfCities - 1; y++)
		{
			printf("%d ",nMap->generation[calcArrayIndex(nMap,x,y)]);
		}
		printf("\n");
	}
}

void printArrayLocation(struct map* nMap,int start)
{
	start = calcArrayIndex(nMap,start,0);
	printf("\nThe simulated trail is:	 0 ");
	int x;
	for(x = 0; x < nMap->numOfCities-1; x++)
	{
		printf("%d ",nMap->generation[start + x]);
	}
	printf("0");
	printf("\n");
}


void swapArray(int* a1, int* a2, int length)
{
	int x;
	for(x = 0; x < length; x++)
	{
		int temp = a1[x];
		a1[x] = a2[x];
		a2[x] = temp;
	}

}

double findBest(struct map* nMap,int start)
{
	int x,ret;
	double best = DBL_MAX;
	for(x = start; x < nMap->numberOfTours-1; x++)
	{
		double check = getDistanceOfTrailGeneration(nMap,calcArrayIndex(nMap,x,0));
		if(check < best)
		{
			best = check;
			ret = x;
		}
	}
	return ret;
}

int getRandomBetweenNumber(int n)
{
	return rand()%(n);
}

void permuteOnce(struct map* nMap,int start)
{
	start = calcArrayIndex(nMap,start,0);

	int m,k,p,q,i,n = nMap->numOfCities-1;
	//Set s equal to the passed array
	int s[getNumCities(nMap)-1];
	for(i = 0; i < getNumCities(nMap); i++ )
	{
		s[i] = nMap->generation[start + i];
	}
	m = n - 2;
	while(s[m] > s[m+1])
		m = m -1;
	k = n - 1;
	while(s[m] > s[k])
		k = k - 1;
	swap(s,m,k);
	p = m + 1;
	q = n - 1;
	while(p < q)
	{
		swap(s,p,q);
		p++;
		q--;
	}
	for(i = 0; i < nMap->numOfCities; i++)
		nMap->generation[start+i] = s[i];
	return;
}


void permuteGenerations(struct map* nMap,int start)
{
	int x = start;
	for(; x < nMap->numberOfTours; x++)
	{
		permuteOnce(nMap,x);
	}


}


void primeGeneration(struct map* nMap)
{
	//Prime all the generations with 1 through numberOfCities-2
	int x,y;
	for(x = 0; x < nMap->numberOfTours; x++)
	{
		for(y = 0; y < nMap->numOfCities - 1; y++)
		{
			nMap->generation[calcArrayIndex(nMap,x,y)] = y+1;
		}
	}


}

void mutateArray(struct map* nMap, int start)
{
	int j,k;
	j = nMap->numOfCities/2 - 2;
	k = nMap->numOfCities/2 + 2;
	start = calcArrayIndex(nMap,start,0);
	int temp = nMap->generation[start + j];
	nMap->generation[start + j] = nMap->generation[start + k];
	nMap->generation[start + k] = temp;

	j = 1;
	k = nMap->numOfCities-2;
	temp = nMap->generation[start + j];
	nMap->generation[start + j] = nMap->generation[start + k];
	nMap->generation[start + k] = temp;

	/*int temp;
	start = calcArrayIndex(nMap,start,0);
	for(i = 0; i < nMap->numOfCities/2 - 1; i++)
	{
		j = nMap->numOfCities/2 + i;
		k = nMap->numOfCities - 2 - i;
		temp = nMap->generation[start + j];
		nMap->generation[start + j] = nMap->generation[start + k];
		nMap->generation[start + k] = temp;
	}*/
	return;
}

double runMutation(struct map* nMap)
{
	primeGeneration(nMap);

	int best = findBest(nMap,0);
	swapArray(&nMap->generation[calcArrayIndex(nMap,0,0)],&nMap->generation[calcArrayIndex(nMap,best,0)],nMap->numOfCities-1);
	//Run generations first one is already done
	int x,y;
	for(x = 0; x < nMap->numOfGenerations-1; x++)
	{

		permuteGenerations(nMap,/*nMap->percentMutations +*/ nMap->percentElites);
		for(y = 0; y < nMap->percentElites; y++)
		{
			best = findBest(nMap,y);
			swapArray(&nMap->generation[calcArrayIndex(nMap,y,0)],&nMap->generation[calcArrayIndex(nMap,best,0)],nMap->numOfCities-1);
		}
		for(y = 1; y < nMap->percentMutations; y++)
			mutateArray(nMap,y);

	}


	return best;
}


void freeMap(struct map* myMap)
{
	free(myMap->generation);
	free(myMap);
	return;
}

