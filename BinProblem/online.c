/*
 * online.c
 *
 *  Created on: Oct 31, 2015
 *      Author: James Davis
 *      Purpose: Contains all the online algorithms
 */

#include <stdio.h>
#include <stdlib.h>
#include "bins.h"
#include "fifo.h"


//Global File pointers to point to the place to read the bin size from
FILE* bins;


/**********Functions for algorithms***************/

binHead* onlineFirstFit(FILE* binItems)
{
	//open both of the files
	bins = fopen("bins.txt","r");

	//get the number of items in the run
	int numOfItems;
	fscanf(binItems,"%d\n",&numOfItems);

	//Set up the bin head
	binHead* theBins = createBins(bins);

	int x = 0,numThrow = 0;
	for(x = 0; x < numOfItems; x++)
	{
		//Get the time that goes in the bins
		int item;
		fscanf(binItems,"%d\n",&item);

		if(item > 100 || item < 0)
		{
			printf("\nThe item: %d was thrown out: Online FF",item);
		}
		else
		{
			int throw = 0;
			//The maximum number of bins is 1000
			while(theBins->amountBins < 1000)
			{
				int location = FirstFitSearchBins(theBins,item);
				if(location == -1)
				{
					if(throw == 0)
					{
						throw = 1;
						addBin(theBins,bins);
					}
					else
					{
						printf("\nThe item: %d was thrown out: Online FF",item);
						numThrow += 1;
						break;
					}
				}
				else
				{
					addEntry(theBins,location,item);
					break;
				}
			}
		}

	}
	fclose(bins);
	return theBins;

}

binHead* onlineNextFit(FILE* binItems)
{
	bins = fopen("bins.txt","r");

	int numOfItems;
	fscanf(binItems,"%d\n",&numOfItems);

	binHead* theBins = createBins(bins);
	bin* current = theBins->next;
	int location = 0;

	int x,numThrown = 0;
	for(x = 0; x < numOfItems; x++)
	{
		int item;
		fscanf(binItems,"%d\n",&item);

		if(item > 100 || item < 0)
		{
			printf("\nThe item: %d was thrown out: Online NF",item);
		}
		else
		{
			int y,throw = 0;
			for(y = theBins->amountBins; y < 1000; y++)
			{

				if(current->holding + item < current->max)
				{
					addEntry(theBins,location,item);
					break;
				}
				else
				{
					if(throw == 0)
					{
						throw = 1;
						addBin(theBins,bins);
						current = current->next;
						location++;
					}
					else
					{
						printf("\nThe item: %d was thrown out: Online NF",item);
						numThrown += 1;
						break;
					}
				}
			}

		}
	}
	fclose(bins);
	return theBins;

}

binHead* onlineBestFit(FILE* binItems)
{
	//open both of the files
	bins = fopen("bins.txt","r");

	//get the number of items in the run
	int numOfItems;
	fscanf(binItems,"%d\n",&numOfItems);

	//Set up the bin head
	binHead* theBins = createBins(bins);

	int x = 0,numThrow = 0;
	for(x = 0; x < numOfItems; x++)
	{
		//Get the time that goes in the bins
		int item;
		fscanf(binItems,"%d\n",&item);

		if(item > 100 || item < 0)
		{
			printf("\nThe item: %d was thrown out: Online BF",item);
		}
		else
		{
			//The maximum number of bins is 1000
			int y, throw = 0;
			for(y = theBins->amountBins; y < 1000; y++)
			{
				int location = BestFitSearchBins(theBins,item);
				if(location == -1)
				{
					if(throw == 0)
					{
						throw  = 1;
						addBin(theBins,bins);
					}
					else
					{
						printf("\nThe item: %d was thrown out: Online BF",item);
						numThrow += 1;
						break;
					}
				}
				else
				{
					addEntry(theBins,location,item);
					break;
				}
			}
		}

	}

	fclose(bins);
	return theBins;

}

