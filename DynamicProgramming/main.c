/*
 * main.c
 *
 *  Created on: Nov 25, 2015
 *      Author: James Davis
 *
 *      Contains the main code for the dynamic programming problems
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "matrixChain.h"
#include "inpstfix.h"
#include "matrixMultiplication.h"

#define EXP 100

int main()
{
	//Opens the file and makes sure its valid
	FILE* matrixDims = fopen("MatrixDimensions.txt","r");
	if(matrixDims == NULL)
	{
		printf("There is no file with the name MatrixDimentions found. Unable to run program");
		return -1;
	}

	//Reads the first part of the file to see how many dimensions to read
	int dimensionNumber;
	fscanf(matrixDims,"%d\n",&dimensionNumber);

	//the matrix to store the dimensions
	int dimensions[dimensionNumber+1];

	//Loop to read all the dimensions
	int x;
	for(x = 0; x < dimensionNumber+1; x++ )
	{
		fscanf(matrixDims,"%d\n",&dimensions[x]);
	}
	fclose(matrixDims);


	//Matrix Chain Order Functions
	msArrays* ms = matrixChainOrder(dimensions,dimensionNumber+1);
	char expressionString[EXP];
	strcpy(expressionString,"");

	printf("1. Computing Optimal Parenthesization:\n");
	printOptimalParens(ms,1,dimensionNumber,expressionString);

	infixToPostfix(expressionString);
	printf("\n\n2. Infix to Postfix: \n");
	printf("%s\n",expressionString);

	FILE* data = fopen("matrixData.txt","r");
	if(!data)
	{
		printf("Was not able to open matrixData.txt. Program Closing");
		freeChainOrder(ms,dimensionNumber+1,dimensions);
		return -1;
	}

	loadData(data,ms,dimensions,dimensionNumber);
	fclose(data);

	printf("\n3. Loaded Array Data\n");

	purgeString(expressionString);

	printf("\n4.Final Result: \n");
	matrixMult(ms,expressionString,dimensions,dimensionNumber);
	printf("Number of scalar multiplications: %ld\n",ms->m[1][dimensionNumber]);


	freeChainOrder(ms,dimensionNumber+1,dimensions);
	return 0;
}

