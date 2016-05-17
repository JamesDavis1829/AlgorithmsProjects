/*
 * offline.c
 *
 *  Created on: Oct 31, 2015
 *      Author: James Davis
 *      Purpose: Contains all the offline algorithms
 */

#include <stdio.h>
#include <stdlib.h>
#include "bins.h"
#include "fifo.h"


//Global file pointer for all the functions
FILE* bins;

/************General Arrays************************/
void fillArray(int* array, int length,FILE* file)
{
	int x;
	for(x = 0; x < length; x++)
	{
		fscanf(file,"%d\n",&array[x]);
	}
}

void swap(int* x, int* y)
{
	int temp = *y;
	*y = *x;
	*x = temp;
	return;

}

void sortArray(int* array, int length)
{
	int x,y;
	for(x = 0; x < length; x++)
	{
		for(y = 0; y < length; y++)
		{
			if(array[x] > array[y])
			{
				swap(&array[x],&array[y]);
			}
		}
	}
}

/******Functions to call Offline Algorithms**************/
binHead* offlineFirstFit(FILE* binItems)
{
	bins = fopen("bins.txt","r");

	int numOfItems;
	fscanf(binItems,"%d\n",&numOfItems);

	int array[numOfItems];
	fillArray(array,numOfItems,binItems);
	sortArray(array,numOfItems);

	binHead* theBins = createBins(bins);

	int x;
	for(x = 0; x < numOfItems; x++)
	{

		if(array[x] > 100 || array[x] < 0)
		{
			printf("\nThe item: %d was thrown out: Offline FF",array[x]);
		}
		else
		{
			//The maximum number of bins is 1000
			int y,throw = 0,numThrow = 0;
			for(y = theBins->amountBins; y < 1000; y++)
			{
				int location = FirstFitSearchBins(theBins,array[x]);
				if(location == -1)
				{
					if(throw == 0)
					{
						throw = 1;
						addBin(theBins,bins);
					}
					else
					{
						printf("\nThe item: %d was thrown out: Offline FF",array[x]);
						numThrow += 1;
						break;
					}
				}
				else
				{
					addEntry(theBins,location,array[x]);
					break;
				}
			}
		}

	}

	fclose(bins);
	return theBins;
}

binHead* offlineBestFit(FILE* binItems)
{
	bins = fopen("bins.txt", "r");

	int numOfItems;
	fscanf(binItems,"%d\n",&numOfItems);

	int array[numOfItems];
	fillArray(array,numOfItems,binItems);
	sortArray(array,numOfItems);

	binHead* theBins = createBins(bins);

	int x,numThrow = 0;
	for(x = 0; x < numOfItems; x++)
	{

		if(array[x] > 100 || array[x] < 0)
		{
			printf("\nThe item: %d was thrown out: Offline BF",array[x]);
		}
		else
		{
			//The maximum number of bins is 1000
			int y,throw = 0;
			for(y = theBins->amountBins; y < 1000; y++)
			{
				int location = BestFitSearchBins(theBins,array[x]);
				if(location == -1)
				{
					if(throw == 0)
					{
						throw = 1;
						addBin(theBins,bins);
					}
					else
					{
						printf("\nThe item: %d was thrown out: Offline BF",array[x]);
						numThrow += 1;
						break;
					}
				}
				else
				{
					addEntry(theBins,location,array[x]);
					break;
				}
			}
		}

	}

	fclose(bins);
	return theBins;
}

