/*
 * fifo.c
 *
 *  Created on: Sep 24, 2015
 *      Author: crims_000
 */
#include <stdio.h>
#include <stdlib.h>
#define MAXTERMS

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

fnodeP createNewNode(int number)
{
	fnodeP new = malloc(sizeof(fnode));
	new->number = number;
	new->next = NULL;

	return new;
}

fheadP createFifo()
{
	fheadP l = malloc(sizeof(fhead));
	l->next = NULL;
	l->amount = 0;
	l->tail = NULL;
	l->head = NULL;

	return l;

}


void addToFifo(fheadP list,int number)
{
	if(list->next == NULL)
	{
		list->next = createNewNode(number);
		list->tail = list->next;
		list->head = list->next;
		list->amount++;
		return;
	}
	list->tail->next = createNewNode(number);
	list->tail = list->tail->next;
	list->amount++;
	return;
}

int popFromFifo(fheadP list)
{
	int number = list->head->number;
	list->amount--;
	list->head = list->head->next;
	free(list->next);
	list->next = list->head;

	return number;
}

int amountInFifo(fheadP list)
{
	return list->amount;
}


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
