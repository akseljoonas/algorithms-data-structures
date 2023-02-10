/* file   : stack.c */
/* author : Harmen de Weerd (harmen.de.weerd@rug.nl) */

/* Description:
 * Implementation of the stack abstact data type.
 * In this implementation, stacks are arrays.
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "stack.h"

struct stack {
	int *array;
	int top;
	int size;
};

void stackMemoryFailure(int size) {
	printf("Failed to allocate a stack of size %i.\n", size);
	exit(EXIT_FAILURE); 
}

Stack *newStack(int initialSize) {
	Stack *output = malloc(sizeof(Stack));
	if (initialSize <= 0 || output == NULL) {
		stackMemoryFailure(initialSize);
	}
	output->top = 0;
	output->size = initialSize;
	output->array = malloc(initialSize * sizeof(int));
	return output;
}
		
void freeStack(Stack *st) {
	free(st->array);
	free(st);
}

int isEmptyStack(Stack *st) {
	return (st->top == 0);
}

void stackEmptyError() {
	printf("Stack empty: pop failed.\n");
	exit(EXIT_FAILURE);
}
	
int pop(Stack *st) {
	if (isEmptyStack(st)) {
		stackEmptyError();
	}
	(st->top)--;
	return (st->array)[st->top];
}
		
void doubleStackSize(Stack *st) {
	st->size *= 2;
	st->array = realloc(st->array, st->size * sizeof(int));
	if (st->array == NULL) {
		stackMemoryFailure(st->size);
	}
}

void push(int item, Stack *st) {
	if (st->top >= st->size) {
		doubleStackSize(st);
	}
	st->array[st->top] = item;
	st->top++;
}
