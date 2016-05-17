/*
 * heap.h
 *
 *  Created on: Sep 19, 2015
 *      Author: crims_000
 */

#ifndef HEAP_H_
#define HEAP_H_
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

heapP createHeap();

void swap(personP customer1,personP customer2);

void percolateDown(heapP q, int start);

void addToHeap(heapP q,double arrival,double *n);

void freeHeap(heapP q);

void printHeapUnordered(heapP q);

person popFromHeap(heapP q);

double peekDTimeHeap(heapP q);

double peekPQtime(heapP q);

double peekATimeHeap(heapP q);

void addCustomer(heapP q,person customer);

#endif /* HEAP_H_ */
