/*
 * inpstfix.h
 *
 *  Created on: Nov 27, 2015
 *      Author: crims_000
 */

#ifndef INPSTFIX_H_
#define INPSTFIX_H_
#define MAX 50

struct stack{
	int data[MAX];
	int top;

};


typedef struct stack stack;
typedef stack* stackP;

int getPrio(char letter);

stackP createStack();

int isEmpty(stackP exp);

int isFull(stackP exp);

void push(stackP exp, char letter);

char pop(stackP exp);

char top(stackP exp);

void freeStack(stackP exp);

void printStack(stackP exp);

void loadStack(stackP exp, char* string);

void infixToPostfix(char* exp);

void printStackRev(stackP exp);

#endif /* INPSTFIX_H_ */
