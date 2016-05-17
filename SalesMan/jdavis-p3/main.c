/*
 * main.c
 *
 *  Created on: Oct 7, 2015
 *      Author: James Davis
 *      Contians: All the code for using and running the program
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Map.h"
#include "bruteSales.h"

int main(int argc,char* argv[])
{
	clock_t begin, end;
	//Creates a map based on the two input files theCities.txt and thePresets.txt
	mapP cityMap = createMap();
	//Prints out the brute force method:
	begin = clock();
	findBrutePath(cityMap);
	end = clock();
	double best = printBestTrail(cityMap);
	printf("\nThe time spent in seconds: %0.3lf",(double)(end - begin)/CLOCKS_PER_SEC);

	//Seeds the random generator
	srand(time(NULL));
	begin = clock();
	//Runs the mutation algorithm
	int bLocation = runMutation(cityMap);
	end = clock();
	double cBest = getDistanceOfTrailGeneration(cityMap,bLocation);
	printArrayLocation(cityMap,bLocation);
	printf("With Distance: 		 %0.2lf",cBest);
	printf("\nPercent of best: 	 %0.2lf",(cBest/best)*100);
	printf("\nThe time spent in seconds: %0.3lf",(double)(end - begin)/CLOCKS_PER_SEC);

	freeMap(cityMap);

	return 0;
}
