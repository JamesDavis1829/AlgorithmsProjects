/*
 * tester.c
 *
 *  Created on: Sep 19, 2015
 *      Author: crims_000
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include "queuemath.h"
#include "heap.h"
#include "fifo.h"


//Prints the person for debugging purposes
void printPerson(person customer)
{
	printf("\nThe aTime: %0.4lf,dTime: %0.4lf, pqTime: %0.4lf, ssTime: %0.4lf",customer.aTime,customer.dTime,customer.pqTime,customer.ssTime);
}

//Fills up the queue when called with the next arrival times
void fillQ(heapP q, double* n,double lambda, double* time)
{
	double x;
	for(x = *n;x > 0; x--)
	{
		if(q->heapSize >= MAXHEAPSIZE)
		{
			break;
		}
		addToHeap(q,getNextRandomInterval(lambda,time),n);


	}

}

//Creates the departure times when there is a service person available
void createDepartureSAvailable(heapP q,double mu,person customer)
{
	customer.ssTime = customer.aTime;
	customer.dTime = getNextRandomService(mu,customer.ssTime);
	customer.pqTime = customer.dTime;
	addCustomer(q,customer);
}

//Removes a person from the fifo queue when there is a server available
void removeFromFifo(heapP q,fheadP fifo,double time,double mu)
{
	person customer = popFromFifo(fifo);
	customer.ssTime = time;
	customer.dTime = getNextRandomService(mu,customer.ssTime);
	customer.pqTime = customer.dTime;
	addCustomer(q,customer);
}

//Processes the next event. If it is an arrival then check if server is available
//or put in fifo line. If its a departure calculate stats and remove from people
//if there is another person in the fifo queue then set them to departure
void processNextEvent(heapP q,fheadP fifo,double M ,int *servers,double mu,double *totalWTime,double *totalSTime,double *expP0,double *customersWaiting)
{
	person customer = popFromHeap(q);
	if(customer.dTime == -1)
	{
		if(*servers > 0)
		{
			*servers = *servers - 1;
			createDepartureSAvailable(q,mu,customer);
		}
		else
		{
			addToFifo(fifo,customer);
		}
	}
	else
	{
		*servers = *servers + 1;
		*totalSTime = *totalSTime + (customer.dTime - customer.ssTime);
		*totalWTime = *totalWTime + (customer.ssTime - customer.aTime);
		if(*servers == M)
			*expP0 = *expP0 + peekPQtime(q) - customer.pqTime;
		if(getFifoAmount(fifo) > 0)
		{
			*customersWaiting = *customersWaiting + 1;
			removeFromFifo(q,fifo,customer.pqTime,mu);
			*servers = *servers - 1;
		}
	}

}

int main()
{
	//Sets the random seed for the times
	srand((unsigned int)time(NULL));
	double time = 0,lastTime=0,totalWTime=0,totalSTime=0,expP0=0,customersWaiting = 0;
	double n,lambda,mu,M;

	//Opens the file simulation.txt and reads the contents for the given variables
	FILE* file = fopen("runSimulation.txt","r");
	fscanf(file,"%lf\n",&lambda);
	fscanf(file,"%lf\n",&mu);
	fscanf(file,"%lf\n",&M);
	fscanf(file,"%lf\n",&n);
	fclose(file);

	//Saves the amount of  customers for math later
	double totalCustomers = n;
	//Prints out the given values from the file
	printf("The given lambda is: %lf\nThe given mu is: %lf\nThe given M is: %lf\nThe given n is: %lf\n",lambda,mu,M,n);

	//loop variable
	int x = 0;

	//creates heap and fills it up
	heapP q = createHeap();
	fillQ(q,&n,lambda,&time);

	//Create the servers
	int serversAvailable = 2;

	//create Fifo
	fheadP fifo = createFifo();
	//prime the q
	for(x = 1; x < M; x++)
	{
		createDepartureSAvailable(q,mu,popFromHeap(q));
	}



	//goes through the events until no more are available
	while(q->heapSize > 0)
	{
		processNextEvent(q,fifo,M,&serversAvailable,mu,&totalWTime,&totalSTime,&expP0,&customersWaiting);
		if(q->heapSize == 1)
			lastTime = peekPQtime(q);
		if(n > 0 && q->heapSize <= M+1)
		{
			fillQ(q,&n,lambda,&time);
		}
	}

	//Finish all the experimental variable calculations
	double cexpP0 = expP0/lastTime;
	double expW = (totalSTime - totalWTime)/totalCustomers;
	double expWq = totalWTime/totalCustomers;
	double expRho = totalSTime/(M*lastTime);

	//Print out results
	printf("\np0: %lf",p0(M,mu,lambda));
	printf("\nL: %lf",L(M,mu,lambda));
	printf("\nW: %lf",W(M,mu,lambda));
	printf("\nLq: %lf",Lq(M,mu,lambda));
	printf("\nWq: %lf",Wq(M,mu,lambda));
	printf("\nrho: %lf",rho(M,mu,lambda));
	printf("\nExperimental p0: %lf",cexpP0);
	printf("\nExperimental W: %lf",expW);
	printf("\nExperimental Wq: %lf",expWq);
	printf("\nExperimental rho: %lf",expRho);
	printf("\nWait for Service: %lf",customersWaiting/totalCustomers);
	freeHeap(q);
	freeFifo(fifo);
	return 0;
}

