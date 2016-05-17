/*
 * heap.c
 *
 *  Created on: Sep 19, 2015
 *      Author: crims_000
 */
#include <stdio.h>
#include <stdlib.h>
#include "queuemath.h"
#define MAXHEAPSIZE 100

struct person{
	double pqTime;
	double aTime;
	double ssTime;
	double dTime;
};

struct heap{
	struct person customers[MAXHEAPSIZE + 1];
	int heapSize;

};

typedef struct person person;
typedef struct person *personP;

typedef struct heap heap;
typedef struct heap *heapP;

//Creates a heap and then returns the address of that heap
heapP createHeap()
{
	heapP newHeap = malloc(sizeof(heap));
	newHeap->heapSize = 0;
	return newHeap;
}

//Swaps the two people passed into the function. Must be passed as pointers
void swap(personP customer1,personP customer2)
{
	person temp = *customer1;
	*customer1 = *customer2;
	*customer2 = temp;
	return;
}

//Organizes the list from the specified entry up until everything is in the
//correct place/
void bubbleUp(heapP q,person x)
{
	q->customers[0] = x;
	int slot = q->heapSize;
	while(x.pqTime < q->customers[slot/2].pqTime)
	{
		q->customers[slot] = q->customers[slot/2];
		slot = slot / 2;
	}
	q->customers[slot] = x;
	return;
}

//Organizes the list from the specified enty down until everything is in its
//proper place.
void percolateDown(heapP q, int slot)
{
	int child;
	person temp = q->customers[slot];

	while(slot*2 <= q->heapSize)
	{
		child = slot*2;
		if(child != q->heapSize && q->customers[child+1].pqTime < q->customers[child].pqTime)
			child++;
		if(q->customers[child].pqTime < temp.pqTime)
			q->customers[slot] = q->customers[child];
		else
			break;
		slot = child;
	}
	q->customers[slot] = temp;
	return;
}

//Adds a person to the heap and cumulatively lowers the count of the amount
//of people left to be simulated
void addToHeap(heapP q,double arrival,double *n)
{
	q->heapSize++;
	*n = *n - 1;
	person new;
	new.aTime = arrival;
	new.pqTime = arrival;
	new.ssTime = -1;
	new.dTime = -1;
	bubbleUp(q,new);
}

//Adds a customer to the heap and then sorts it
void addCustomer(heapP q,person customer)
{
	q->heapSize++;
	q->customers[q->heapSize].aTime = customer.aTime;
	q->customers[q->heapSize].dTime = customer.dTime;
	q->customers[q->heapSize].pqTime = customer.pqTime;
	q->customers[q->heapSize].ssTime = customer.ssTime;
	bubbleUp(q,q->customers[q->heapSize]);
}

//Prints out the heap in the order that it appears in the array
//Used for debuggin purposes to check to see that the smallest
//Amount is on top
void printHeapUnordered(heapP q)
{
	printf("\nThe heap: ");
	int x;
	for(x = 1; x <= q->heapSize; x++)
	{
		printf("\nPerson has comparison time of: %lf",q->customers[x].pqTime);
	}
	return;
}

//Removes a person from the heap and then returns them
person popFromHeap(heapP q)
{
	person customer = q->customers[1];
	q->customers[1] = q->customers[q->heapSize];
	q->heapSize--;
	percolateDown(q,1);
	return customer;
}

//Getter for the first persons departure time
double peekDTimeHeap(heapP q)
{
	return q->customers[1].dTime;
}

//Getter for the first persons pq time
double peekPQtime(heapP q)
{
	return q->customers[1].pqTime;
}

//Getter for the first persons A time
double peekATimeHeap(heapP q)
{
	return q->customers[1].aTime;
}

//Frees the memory associated with the heap
void freeHeap(heapP q)
{
	free(q);
	return;
}
