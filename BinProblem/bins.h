/*
 * bins.h
 *
 *  Created on: Oct 31, 2015
 *      Author: crims_000
 */

#ifndef BINS_H_
#define BINS_H_
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


typedef struct binEntry binEntry;
typedef struct bin bin;
typedef struct binHead binHead;

binHead* createBins(FILE* bins);

void addBin(binHead* head,FILE* bins);

void addEntry(binHead* head,int location,int size);

int FirstFitSearchBins(binHead* head, int size);

void freeBins(binHead* head);

int BestFitSearchBins(binHead* head, int size);

int FirstFitSearchBins(binHead* head, int size);

void printBins(binHead* OFF,binHead* ONF,binHead*OBF,binHead* XFF, binHead* XBF,int runNumber);

#endif /* BINS_H_ */
