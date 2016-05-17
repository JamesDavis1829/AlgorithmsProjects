/*
 * inpstfix.c
 *
 *  Created on: Nov 27, 2015
 *      Author: James Davis
 *
 *      This file is based on the code and algorithm on the following websites
 *      http://www.c4learn.com/data-structure/c-program-convert-infix-expression-to-postfix-using-stack/
 *      http://geeksquiz.com/stack-set-2-infix-to-postfix/
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 100

struct stack{
	int data[MAX];
	int top;

};

typedef struct stack stack;
typedef stack* stackP;

int getPrio(char letter)
{
	if (letter == '(')
		return 0;
	if (letter == '+' || letter == '-')
		return 1;
	if (letter == '*' || letter == '/' || letter == '%')
		return 2;
	return 3;
}

stackP createStack()
{
	stackP newStack = malloc(sizeof(stack));
	newStack->top = -1;
	return newStack;
}

int isEmpty(stackP exp)
{
	if(exp->top == -1)
		return 1;
	else
		return 0;
}

int isFull(stackP exp)
{
	if(exp->top == MAX-1)
		return 1;
	else
		return 0;
}

void push(stackP exp, char letter)
{
	exp->top = exp->top + 1;
	exp->data[exp->top] = letter;
}

char pop(stackP exp)
{
	char x;
	x = exp->data[exp->top];
	exp->top = exp->top-1;
	return x;
}

char top(stackP exp)
{
	return exp->data[exp->top];
}

void freeStack(stackP exp)
{
	free(exp);
}

void printStack(stackP exp)
{
	printf("\n");
	int top = exp->top;
	while(isEmpty(exp) != 1)
	{
		printf("%c",pop(exp));
	}
	exp->top = top;
	return;
}

void printStackRev(stackP exp)
{
	printf("\n");
	stackP temp = createStack();
	int top = exp->top;
	while(isEmpty(exp) != 1)
	{
		push(temp,pop(exp));
	}
	exp->top = top;

	while(isEmpty(temp) != 1)
	{
		printf("%c",pop(temp));
	}
	freeStack(temp);
}

int isOperand(char letter)
{
	return (((letter >= '0') && (letter <= 'z')) || ((letter >= 'A') && (letter <= 'Z')));
}


void loadStack(stackP exp, char* string)
{
	int x = strlen(string);
	int z;
	for(z = x - 1; z >= 0; z--)
	{
		if(isFull(exp) != 1)
		{
			push(exp,string[z]);
		}
	}
	return;
}

void infixToPostfix(char* exp)
{
	int i, k;

	// Create a stack of capacity equal to expression size
	stackP temp = createStack();
	if(!temp) // See if stack was created successfully
		return;

	for (i = 0, k = -1; exp[i]; ++i)
	{
		 // If the scanned character is an operand, add it to output.
		if (isOperand(exp[i]))
			exp[++k] = exp[i];

		// If the scanned character is an ‘(‘, push it to the stack.
		else if (exp[i] == '(')
			push(temp, exp[i]);

		//  If the scanned character is an ‘)’, pop and output from the stack
		// until an ‘(‘ is encountered.
		else if (exp[i] == ')')
		{
			while (!isEmpty(temp) && top(temp) != '(')
				exp[++k] = pop(temp);
			if (!isEmpty(temp) && top(temp) != '(')
				return; // invalid expression
			else
				pop(temp);
		}
		else // an operator is encountered
		{
			while (!isEmpty(temp) && getPrio(exp[i]) <= getPrio(top(temp)))
				exp[++k] = pop(temp);
			push(temp, exp[i]);
		}

	}

	// pop all the operators from the stack
	while (!isEmpty(temp))
		exp[++k] = pop(temp );
	exp[++k] = '\0';
	freeStack(temp);
	return;
}
