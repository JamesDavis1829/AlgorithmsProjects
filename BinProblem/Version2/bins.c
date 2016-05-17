/*
 * bins.c
 *
 *  Created on: Oct 31, 2015
 *      Author: James Davis
 *      Purpose: Contains all the functinos for the bins
 */
#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"

struct bin{
	int max;
	int holding;
	fheadP contents;
	struct bin *next;
};

struct binHead{
	int amountBins;
	struct bin *next;
};

typedef struct bin bin;
typedef struct binHead binHead;

/***********Functions to handle bins***************/

binHead* createBins(FILE* bins)
{
	binHead* make = malloc(sizeof(binHead));
	make->next = malloc(sizeof(bin));
	make->amountBins = 1;

	make->next->holding = 0;
	fscanf(bins,"%d\n",&make->next->max);
	make->next->next = NULL;
	make->next->contents = NULL;
	return make;
}

void addBin(binHead* head,FILE* bins)
{
	head->amountBins++;
	bin* current = head->next;
	while(current->next != NULL)
		current = current->next;
	current->next = malloc(sizeof(bin));
	fscanf(bins,"%d\n",&current->next->max);
	current->next->holding = 0;
	current->next->contents = NULL;
	current->next->next = NULL;

}

void addEntry(binHead* head,int location,int size)
{
	int x;
	bin* current = head->next;
	for(x = 0; x < location; x++)
	{
		current = current->next;
	}
	if(current->contents == NULL)
	{
		current->holding += size;
		current->contents = createFifo();
		addToFifo(current->contents,size);
	}
	else
	{
		current->holding += size;
		addToFifo(current->contents,size);
	}
}

int FirstFitSearchBins(binHead* head, int size)
{
	int location = 0;
	bin* current = head->next;
	if((current->holding + size) < current->max)
	{
		return 0;
	}
	else
	{
		while(current != NULL)
		{
			if((current->holding + size) < current->max)
			{
				return location;
			}
			else
			{
				location++;
				current = current->next;
			}

		}
	}
	return -1;
}

int BestFitSearchBins(binHead* head, int size)
{
	int curLocation = 0, retLocation = -1, minLeft = 99999999, calc;
	bin* current = head->next;

	calc = current->max - (current->holding + size);
	if(calc > 0 && calc < minLeft)
	{
		minLeft = calc;
		retLocation = curLocation;
	}
	else
	{
		while(current->next != NULL)
		{
			calc = current->max - (current->holding + size);
			if(calc > 0 && calc < minLeft)
			{
				minLeft = calc;
				retLocation = curLocation;
			}
			current = current->next;
			curLocation++;
		}
		calc = current->max - (current->holding + size);
		if(calc > 0 && calc < minLeft)
		{
			minLeft = calc;
			retLocation = curLocation;
		}
	}
	return retLocation;
}


void freeBins(binHead* head)
{
	bin* current = head->next;
	bin* previous = current;

	while(current->next != NULL)
	{
		if(current->contents != NULL)
			freeFifo(current->contents);
		previous = current;
		free(current);
		current = previous->next;
	}
	if(current->contents != NULL)
		freeFifo(current->contents);
	free(current);
	free(head);

}

void printBinContents(binHead* theBins)
{
	bin* current = theBins->next;
	int binNumber = 1;
	while(current->next != NULL)
	{
		printf("Bin Number: %d has - ",binNumber);
		if(current->contents != NULL)
		{
			while(current->contents->amount > 0)
			{
				printf("%d ",popFromFifo(current->contents));
			}
		}
		printf("\n");
		binNumber++;
		current = current->next;
	}
	printf("Bin Number: %d has - ",binNumber);
	if(current->contents != NULL)
	{
		while(current->contents->amount > 0)
		{
			printf("%d ",popFromFifo(current->contents));
		}
	}
	printf("\n");
}

void printBins(binHead* OFF,binHead* ONF,binHead*OBF,binHead* XFF, binHead* XBF,int runNumber)
{
	printf("\nRun Number: %d\n",runNumber);
	printf("Online\n");
	printf("Policy      |  Bins\n");
	printf("First Fit   |  %d\n",OFF->amountBins);
	printf("Next Fit    |  %d\n",ONF->amountBins);
	printf("Best Fit    |  %d\n",OBF->amountBins);
	printf("Offline\n");
	printf("First Fit   |  %d\n",XFF->amountBins);
	printf("Best Fit    |  %d\n",XBF->amountBins);
	printf("\n");
	printf("The contents of the Online First Fit Bins: \n");
	printBinContents(OFF);
	printf("\nThe contents of the Online Next Fit Bins: \n");
	printBinContents(ONF);
	printf("\nThe contents of the Online Best Fit Bins: \n");
	printBinContents(OBF);
	printf("\nThe contents of the Offline First Fit Bins: \n");
	printBinContents(XFF);
	printf("\nThe contents of the Offline Best Fit Bins: \n");
	printBinContents(XBF);

}





