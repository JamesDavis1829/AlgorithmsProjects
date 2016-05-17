/*
 * matrixChain.c
 *
 *  Created on: Nov 26, 2015
 *      Author: James Davis
 *
 *      Contains the functions for all the matrix chain problems
 */


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "inpstfix.h"

struct msArrays{
	int** m;
	int** s;
	int dimFlag;
	long int*** arrayData;
};

typedef struct msArrays msArrays;


msArrays* matrixChainOrder(int* dimensions, int length)
{
	length = length + 1;
	msArrays* ms = malloc(sizeof(msArrays));
	ms->m = malloc(sizeof(int*)* length);
	ms->s = malloc(sizeof(int*)* length);
	ms->dimFlag = 0;
	int x,y;
	for(x = 0; x < length; x++)
	{
		ms->m[x] = malloc(sizeof(int) * length);
		ms->s[x] = malloc(sizeof(int) * length);
	}

	int n = length - 1;

	//initialize matrices to zero
	for(x = 1; x <= n; x++)
	{
		for(y = 0; y < length; y++)
		{
			ms->m[x][y] = 0;
			ms->s[x][y] = 0;
		}
	}

	int l,i,j,k,q;
	for(l = 2; l <= n; l++)
	{
		for(i = 1; i < (n - l + 1); i++)
		{
			j = i + l - 1;
			ms->m[i][j] = 99999999; //infinity
			for(k = i; k <= (j-1); k++)
			{
				//Not sure about the dimensions additions here
				q = ms->m[i][k] + ms->m[k+1][j] + dimensions[i-1]*dimensions[k]*dimensions[j];

				if(q < ms->m[i][j])
				{
					ms->m[i][j] = q;
					ms->s[i][j] = k;
				}
			}

		}
	}

	return ms;

}

void printChainOrder(msArrays* ms,int length)
{
	printf("\nThe M array: \n");
	int x,y;
	for(x = 1; x < length; x++)
	{
		for(y = 1; y < length; y++)
		{
			printf("%10d ",ms->m[x][y]);
		}
		printf("\n");
	}

	printf("\nThe S array: \n");
	for(x = 1; x < length; x++)
	{
		for(y = 1; y < length; y++)
		{
			printf("%10d ",ms->s[x][y]);
		}
		printf("\n");
	}

	return;
}


void freeChainOrder(msArrays* ms,int length,int* dims)
{
	length = length + 1;
	int x;
	for(x = 0; x < length; x++)
	{
		free(ms->m[x]);
		free(ms->s[x]);
	}
	free(ms->m);
	free(ms->s);

	if(ms->dimFlag == 1)
	{
		int y,z;
		for(y = 0; y < length-2; y++)
		{
			for(z = 0; z < dims[y]; z++)
			{
				free(ms->arrayData[y][z]);
			}
			free(ms->arrayData[y]);
		}
		free(ms->arrayData);

	}

	free(ms);
	return;
}

void printOptimalParens(msArrays* ms, int i, int j,char* string)
{
	int sij;
	if(i == j)
	{
		printf("A%d",i);
		char str[3];
		str[0] = 'A';
		str[1] =  i + '0';
		str[2] = '\0';
		strcat(string,str);
	}
	else
	{
		printf("("); strcat(string,"(");
		sij = ms->s[i][j];
		printOptimalParens(ms,i,sij,string);
		printf("*");strcat(string,"*");
		printOptimalParens(ms,sij+1, j,string);
		printf(")");strcat(string,")");
	}

}

void loadData(FILE* datafile, msArrays* ms,int* dims,int length)
{
	int x,y,z;

	ms->arrayData = malloc(sizeof(long long int*)*length);
	ms->dimFlag = 1;



	for(x = 0; x < length; x++)
	{
		ms->arrayData[x] = malloc(sizeof(long long int*)*dims[x]);
		for(y = 0; y < dims[x]; y++)
		{
			ms->arrayData[x][y] = malloc(sizeof(long long int)*dims[x+1]);
			for(z = 0; z < dims[x+1]; z++)
			{
				fscanf(datafile,"%ld \n",&ms->arrayData[x][y][z]);
			}
		}
	}

}

void printData(msArrays* ms, int* dims, int length)
{
	int x,y,z;
	printf("The matrix contents: \n");
	for(x = 0; x < length; x++)
	{
		for(y = 0; y < dims[x]; y++)
		{
			for(z = 0; z < dims[x+1]; z++)
			{
				printf("%2ld ",ms->arrayData[x][y][z]);
			}
			printf("\n");
		}
		printf("\n");
	}
}


