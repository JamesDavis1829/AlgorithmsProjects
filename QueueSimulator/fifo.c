/*
 * fifo.c
 *
 *  Created on: Sep 24, 2015
 *      Author: crims_000
 */
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#define MAXTERMS

struct fnode{
	struct person customer;
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

//Creates a new node to use with the fifo queue
fnodeP createNewNode(struct person customer)
{
	fnodeP new = malloc(sizeof(fnode));
	new->customer = customer;
	new->next = NULL;

	return new;
}

//Creates a new fifo queue
fheadP createFifo()
{
	fheadP l = malloc(sizeof(fhead));
	l->next = NULL;
	l->amount = 0;
	l->tail = NULL;
	l->head = NULL;

	return l;

}

//Adds the passed in person to the fifo queue
void addToFifo(fheadP list,struct person customer)
{
	if(list->next == NULL)
	{
		list->next = createNewNode(customer);
		list->tail = list->next;
		list->head = list->next;
		list->amount++;
		return;
	}
	list->tail->next = createNewNode(customer);
	list->tail = list->tail->next;
	list->amount++;
	return;
}

//Removes and returns the first person from the passed
//in fifo queue
struct person popFromFifo(fheadP list)
{
	person customer = list->head->customer;
	list->amount--;
	list->head = list->head->next;
	free(list->next);
	list->next = list->head;

	return customer;
}

//Getter for the amount of people in the FIFO queue
int amountInFifo(fheadP list)
{
	return list->amount;
}

//Frees the FIFO queue
void freeFifo(fheadP list)
{
	fnodeP current = list->next;
	fnodeP temp;

	int x;
	for(x = 0;x < list->amount; x++)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
	free(list);
}

//Getter for the first person departure time
double peekDFifo(fheadP list)
{
	return list->next->customer.dTime;
}

//Getter for the first persons PQ time
double peekPQFifo(fheadP list)
{
	return list->next->customer.pqTime;
}
 //Getter for the amount of people int the FIFO queue
int getFifoAmount(fheadP list)
{
	return list->amount;
}
