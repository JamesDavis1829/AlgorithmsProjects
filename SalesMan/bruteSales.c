/*
 * bruteSales.c
 *
 *  Created on: Oct 9, 2015
 *      Author: James Davis
 *      Contains: The brute force algorithm for the traveling salesman problem
 */

#include <stdio.h>
#include <stdlib.h>
#include "Map.h"

void permute(mapP,int,int);

void swap(int* a, int b,int c)
{
	int temp = a[b];
	a[b] = a[c];
	a[c] = temp;
	return;
}

//Sets the permutation numbers
void permuteIter(mapP map)
{
	int i;
	int n = getNumCities(map)-1;
	int nfact = 1;
	for(i = 1; i <= n; i++)
	{
		nfact *= i;
	}
	permute(map,nfact-1,n);


}

//Permutes through the permutation algorithm
void permute(mapP map,int nfact,int n)
{
	int m,k,p,q,i;
	//Set s equal to the default array
	int s[getNumCities(map)-1];
	for(i = 0; i < getNumCities(map) - 1; i++ )
	{
		s[i] = getBestEntry(map,i+1);
	}

	for(i = 0; i < nfact; i++)
	{
		m = n - 2;
		while(s[m] > s[m+1])
			m = m -1;
		k = n - 1;
		while(s[m] > s[k])
			k = k - 1;
		swap(s,m,k);
		p = m + 1;
		q = n - 1;
		while(p < q)
		{
			swap(s,p,q);
			p++;
			q--;
		}
		if(getDistanceOfTrail(map,s) < getDistanceOfBestTrail(map))
		{
			setBest(map,s);
		}
	}
}


//Takes in the first cities in order then brute force guesses the most optimal path
void findBrutePath(mapP map)
{
	permuteIter(map);
}

