/*
 * main.c
 *
 *  Created on: Oct 31, 2015
 *      Author: James Davis
 *      Purpose: Contains the main function
 */

#include <stdio.h>
#include <stdlib.h>
#include "online.h"
#include "offline.h"
#include "bins.h"
#include "fifo.h"

void resetFilePointer(FILE* file)
{
	fseek(file,0,SEEK_SET);
	int temp;
	fscanf(file,"%d\n",&temp);
	return;
}

int main(int argc, char* argv[])
{
	FILE* binItems = fopen("binItems.txt","r");
	int runs;
	fscanf(binItems,"%d\n",&runs);
	binHead* OnlineFirstFit[runs];
	binHead* OnlineNextFit[runs];
	binHead* OnlineBestFit[runs];
	binHead* OfflineFirstFit[runs];
	binHead* OfflineBestFit[runs];

	//Loop to run the Online First Fit [n] times
	int x;
	for(x = 0; x < runs; x++)
		OnlineFirstFit[x] = onlineFirstFit(binItems);

	//Reset file pointer and run OnlineNextFit
	resetFilePointer(binItems);
	for(x = 0; x < runs; x++)
		OnlineNextFit[x] = onlineNextFit(binItems);

	//Reset file pointer and run onlineBestFit
	resetFilePointer(binItems);
	for(x = 0; x < runs; x++)
		OnlineBestFit[x] = onlineBestFit(binItems);

	//Reset file pointer and run OfflineFirstFit
	resetFilePointer(binItems);
	for(x = 0; x < runs; x++)
		OfflineFirstFit[x] = offlineFirstFit(binItems);

	//Reset file pointer and run OfflineBestFir
	resetFilePointer(binItems);
	for(x = 0; x < runs; x++)
		OfflineBestFit[x] = offlineBestFit(binItems);

	//Prints out results
	printf("\n\nThe number of runs is: %d",runs);
	for(x = 0; x < runs; x++)
	{
		printBins(OnlineFirstFit[x],OnlineNextFit[x],OnlineBestFit[x],OfflineFirstFit[x],OfflineBestFit[x],x+1);
	}

	//Frees all the memory
	for(x = 0; x < runs; x++)
	{
		freeBins(OnlineFirstFit[x]);
		freeBins(OnlineNextFit[x]);
		freeBins(OnlineBestFit[x]);
		freeBins(OfflineFirstFit[x]);
		freeBins(OfflineBestFit[x]);
	}
	fclose(binItems);
	return 0;

}

