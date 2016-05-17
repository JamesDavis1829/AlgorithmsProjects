/*
 * online.h
 *
 *  Created on: Oct 31, 2015
 *      Author: crims_000
 */

#ifndef ONLINE_H_
#define ONLINE_H_
#include "bins.h"

binHead* onlineFirstFit(FILE* binItems);

binHead* onlineNextFit(FILE* binItems);

binHead* onlineBestFit(FILE* binItems);

int BestFitSearchBins(binHead* head, int size);

#endif /* ONLINE_H_ */
