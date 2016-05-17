/*
 * fifo.h
 *
 *  Created on: Sep 24, 2015
 *      Author: crims_000
 */

#ifndef FIFO_H_
#define FIFO_H_

typedef struct fnode fnode;
typedef fnode* fnodeP;

typedef struct fhead fhead;
typedef struct fhead* fheadP;

fnodeP createNewNode(struct person customer);

fheadP createFifo();

void addToFifo(fheadP list,struct person customer);

struct person popFromFifo(fheadP list);

int amountInFifo(fheadP list);

void freeFifo(fheadP list);

double peekDFifo(fheadP list);

double peekPQFifo(fheadP list);

int getFifoAmount(fheadP list);

#endif /* FIFO_H_ */
