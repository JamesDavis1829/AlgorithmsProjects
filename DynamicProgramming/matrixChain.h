/*
 * matrixChain.h
 *
 *  Created on: Nov 26, 2015
 *      Author: crims_000
 */

#ifndef MATRIXCHAIN_H_
#define MATRIXCHAIN_H_

#include "inpstfix.h"

struct msArrays{
	int** m;
	int** s;
	int dimFlag;
	long int*** arrayData;
};

typedef struct msArrays msArrays;

msArrays* matrixChainOrder(int* dimensions, int length);

void printChainOrder(msArrays* ms,int length);

void freeChainOrder(msArrays* ms,int length,int* dims);

void printOptimalParens(msArrays* ms, int i, int j,char* string);

void printData(msArrays* ms, int* dims, int length);

void loadData(FILE* datafile, msArrays* ms,int* dims,int length);


#endif /* MATRIXCHAIN_H_ */
