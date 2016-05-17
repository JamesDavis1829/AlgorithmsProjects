/*
 * queuemath.c
 *
 *  Created on: Sep 19, 2015
 *      Author: James Davis
 *      About: Contains all the necessary math funtions for the queue simulator project
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//returns the factorial of the number specified
int fact(int number)
{
	if(number == 0)
	{
		return 1;
	}
	return (number * fact(number - 1));

}

//returns the result of a 'number' to the power of 'power'
double powerTo(double number, int power)
{
	if(power == 0)
	{
		return 1;
	}
	else if(power == 1)
	{
		return number;
	}
	int x;
	double result = 1;
	for(x = 0; x < power; x++)
	{
		result = result * number;
	}
	return result;

}

//Calculates the value of p0 and returnrs it
double p0(double M,double mu, double lambda)
{
	int x;
	double result = 0,test;
	for(x = 0; x < M; x++)
	{
		test = fact(x)*powerTo((lambda/mu) , x);
		result += test;
	}


	double temp = (1.0/fact(M)) * powerTo((lambda/mu) , M) * ((M*mu)/(M*mu - lambda));
	result = 1/(result +temp);
	return result;
}

//Returns the value of L
double L(double M, double mu, double lambda)
{
	double result;
	result = lambda * mu * powerTo((lambda/mu) , (int)M);
	result /= fact(M - 1) * powerTo((M*mu - lambda), 2);
	result *= p0(M,mu,lambda);
	result += (lambda/mu);

	return result;
}

//Returns the value of L using P0
double LWithP0(double M, double mu, double lambda, double P0)
{
	double result;
	result = lambda * mu * powerTo((lambda/mu) , (int)M);
	result /= fact(M - 1) * powerTo((M*mu - lambda), 2);
	result *= P0;
	result += (lambda/mu);

	return result;
}

//Returns the value of W
double W(double M, double mu, double lambda)
{
	double result;
	result = mu*powerTo((lambda / mu), M);
	result /= fact(M - 1) * powerTo((M*mu - lambda) , 2);
	result *= p0(M,mu,lambda);
	result += 1.0/mu;

	return result;
}

//Returns the value of Lq using the value of L
double LqWithL(double L, double mu, double lambda)
{
	return L - (lambda/mu);
}

//Returns the value of Lq without using the value of L
double Lq(double M, double mu, double lambda)
{
	return L(M,mu,lambda) - (lambda/mu);
}

//Returns the value of Wq
double Wq(double M, double mu, double lambda)
{
	return Lq(M , mu, lambda)/lambda;
}

//Returns the value of Rho
double rho(double M,double mu, double lambda)
{
	return lambda/(M * mu);
}

//Gets the next random intervale and cumulatively increments time
//with the new value. This keeps track of the current time of the
//simulation
double getNextRandomInterval(double average,double *time)
{
	double r = (double)rand()/(double)(RAND_MAX);
	while(r == 1 || r == 0)
		r = (double)rand()/(double)(RAND_MAX);
	*time = *time  + (-1 * (1.0/average) * log(r));
	return *time;

}

//Get the next interval without cumulatively updating time
double getNextRandomService(double average, double time)
{
	double r = (double)rand() / (double)(RAND_MAX);
	while(r == 1 || r == 0)
		r = (double)rand() / (double)(RAND_MAX);
	return time + (-1 * (1.0/average) * log(r));
}
