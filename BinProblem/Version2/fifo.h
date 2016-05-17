/*
 * fifo.h
 *
 *  Created on: Sep 24, 2015
 *      Author: crims_000
 */

#ifndef FIFO_H_
#define FIFO_H_

struct fnode{
	int number;
	struct fnode *next;
};


struct fhead{
	int amount;
	struct fnode *next;
	struct fnode *tail;
	struct fnode *head;
};

typedef struct fnode fnode;
typedef fnode* fnodeP;

typedef struct fhead fhead;
typedef struct fhead* fheadP;

fnodeP createNewNode(int number);

fheadP createFifo();

void addToFifo(fheadP list,int number);

int popFromFifo(fheadP list);

int amountInFifo(fheadP list);

void freeFifo(fheadP list);

#endif /* FIFO_H_ */
