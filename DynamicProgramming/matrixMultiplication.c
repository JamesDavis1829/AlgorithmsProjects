/*
 * matrixMultiplication.c
 *
 *  Created on: Nov 27, 2015
 *      Author: James Davis
 *
 *      Contains the code for all the functions pertaining to matrix multiplication.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrixChain.h"
#include "inpstfix.h"

struct finStack{
	int data[MAX];
	int dims[MAX][2];
	int top;
};

typedef struct finStack finStack;

finStack* createfinStack()
{
	finStack* new = malloc(sizeof(finStack));
	new->top = -1;
	return new;
}

void pushData(finStack* new, int j,int row, int col)
{
	new->top = new->top + 1;
	new->data[new->top] = j;
	new->dims[new->top][0] = row;
	new->dims[new->top][1] = col;
}

int getRow(finStack* new)
{
	return new->dims[new->top][0];
}

int getCol(finStack* new)
{
	return new->dims[new->top][1];
}

int popIndex(finStack* new)
{
	int x = new->data[new->top];
	new->top--;
	return x;
}

void freeFinStack(finStack* new)
{
	free(new);
}


void purgeString(char* string)
{
	int l = strlen(string);
	char* write = string;

	int x,y = 0;
	for(x = 0; x < l; x++)
	{
		if(string[x] == 'A')
		{
			write++;
		}
		else
		{
			string[y++] = *write;
			write++;
		}

	}
	string[y] = '\0';
}

long int dotProduct(long int* row, long int* column,int amount)
{
	int x;
	long int sum = 0;
	for(x = 0; x < amount; x++)
	{
		sum += row[x]*column[x];
	}
	return sum;
}

int findLargest(int* dims,int length)
{
	int x;
	int max = 0;
	for(x = 0; x < length+1; x++)
	{
		if(dims[x] > max)
			max = dims[x];
	}

	return max;
}

void mult(long int** a1, long int** a2, long int** final, int* a1d, int* a2d,int max)
{
	int a,b,x,y;
	long int finalCopy[max][max];

	long int row[a1d[1]];
	long int col[a2d[0]];

	for(x = 0; x < a1d[0]; x++)
	{
		//Put rows in a vector
		for(a = 0; a < a1d[1]; a++)
		{
			row[a] = a1[x][a];
		}
		//Put columns in a vector and multiplies
		for(y = 0; y < a2d[1]; y++)
		{
			for(b = 0; b < a2d[0]; b++)
			{
				col[b] = a2[b][y];
			}
			finalCopy[x][y] = dotProduct(row,col,a2d[0]);
		}
	}

	for(x = 0; x < a1d[0]; x++)
	{
		for(y = 0; y < a2d[1]; y++)
		{
			final[x][y] = finalCopy[x][y];
		}
	}
}

void matrixMult(msArrays* ms,char* equation,int* dims,int length)
{
	int max = findLargest(dims,length);

	finStack* fin = createfinStack();

	int l = strlen(equation);

	long int*** finalArray;
	finalArray = malloc(sizeof(long int*)*l);
	int a,b;
	for(a = 0; a < l; a++)
	{
		finalArray[a] = malloc(sizeof(long int*) * max);
		for(b = 0; b < max; b++)
		{
			finalArray[a][b] = malloc(sizeof(long int)*max);
		}
	}

	stackP equ = createStack();



	int x,y;
	int dim1[2],dim2[2];
	int finalArrayEntry;
	for(x = 0; x < l; x++)
	{
		if(equation[x] == '*')
		{
			int loc2 = pop(equ) - '0';
			int loc1 = pop(equ) - '0';

			if(loc2 != 78 && loc1 != 78)
			{
				dim1[0] = dims[loc1-1];
				dim1[1] = dims[loc1];
				dim2[0] = dims[loc2-1];
				dim2[1] = dims[loc2];
				mult(ms->arrayData[loc1 - 1],ms->arrayData[loc2-1],finalArray[x],dim1,dim2,max);
				pushData(fin,x,dim1[0],dim2[1]);
				finalArrayEntry = x;
			}
			else if(loc1 == 78 && loc2 != 78)
			{
				dim1[0] = getRow(fin);
				dim1[1] = getCol(fin);
				dim2[0] = dims[loc2-1];
				dim2[1] = dims[loc2];
				mult(finalArray[popIndex(fin)],ms->arrayData[loc2-1],finalArray[x],dim1,dim2,max);
				pushData(fin,x,dim1[0],dim2[1]);
				finalArrayEntry = x;
			}
			else if(loc2 == 78 && loc1 != 78)
			{
				dim2[0] = getRow(fin);
				dim2[1] = getCol(fin);
				dim1[0] = dims[loc1 - 1];
				dim1[1] = dims[loc1];
				mult(ms->arrayData[loc1-1],finalArray[popIndex(fin)],finalArray[x],dim1,dim2,max);
				pushData(fin,x,dim1[0],dim2[1]);
				finalArrayEntry = x;
			}
			else
			{
				int l1,l2;
				dim1[0] = getRow(fin);
				dim1[1] = getCol(fin);
				l1 = popIndex(fin);
				dim2[0] = getRow(fin);
				dim2[1] = getCol(fin);
				l2 = popIndex(fin);
				mult(finalArray[l1],finalArray[l2],finalArray[x],dim1,dim2,max);
				pushData(fin,x,dim1[0],dim2[1]);
				finalArrayEntry = x;
			}
			push(equ,'~');


		}
		else
		{
			push(equ,equation[x]);
		}
	}

	for(x = 0; x < dim1[0]; x++)
	{
		for(y = 0; y < dim2[1]; y++)
		{
			printf("%10ld ",finalArray[finalArrayEntry][x][y]);
		}
		printf("\n");
	}

	for(x = 0; x < l; x++)
	{
		for(y = 0; y < max; y++)
		{
			free(finalArray[x][y]);
		}
		free(finalArray[x]);
	}
	free(finalArray);
	freeFinStack(fin);
	freeStack(equ);
}


