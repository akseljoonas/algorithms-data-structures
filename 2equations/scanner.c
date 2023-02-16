/* file   : scanner.c */
/* author : Harmen de Weerd (harmen.de.weerd@rug.nl) */

/* Description:
 * An implementation for a token list scanner 
 * for expressions. The token list scanner separates 
 * a string of characters into numbers, identifiers,
 * and symbols.
 */
#ifndef SCANNER_C
#define SCANNER_C

#include <stdio.h>  /* getchar, printf */
#include <stdlib.h> /* NULL, malloc, free */
#include <string.h> /* strcpy */
#include <ctype.h>  /* isspace, isdigit, isalpha, isalnum */
#include <assert.h> /* assert */
#include "scanner.h"
#include "scannerStructs.h"

char *readInput() {
	int strLen = MAXINPUT;
	int c = getchar();
	int i = 0;
	char *s = malloc((strLen+1)*sizeof(char));
	assert(s != NULL);
	while (c != '\n') {
		s[i] = c;
		i++;
		if (i >= strLen) {
			/* s is not large enough, double its length */
			strLen = 2*strLen;
			s = realloc(s,(strLen+1)*sizeof(char));
			assert(s != NULL);
		}
		c = getchar();
	}
	s[i] = '\0';
	return s;
}

int matchNumber(const char *input, int *position) {
	int n = 0;
	while (isdigit(input[*position])) {
		n = 10*n + (input[*position] - '0');
		(*position)++;
	}
	return n;
}

char matchSymbol(const char *input, int *position) {
	char symbol = input[*position];
	(*position)++;
	return symbol;
}

char *matchIdentifier(const char *input, int *position) {
	int n = 0;
	while (isalnum(input[*position+n])) {
		n++;
	}
	char *s = malloc((n + 1)*sizeof(char));
	assert(s != NULL);
	strncpy(s, input + *position, n);
	s[n] = '\0'; // to guarantee a null-terminated string
	(*position) += n;
	return s;
}

List *createListNode() {
	List *output = malloc(sizeof(List));
	if (output == NULL) {
		printf("Failed to allocate memory for list node,\n");
		exit(EXIT_FAILURE);
	}
	output->next = NULL;
	return output;
}

List *newNode(const char *input, int *position) {
	List *output = createListNode();
	if (isdigit(input[*position])) {
		/* we see a digit, so a number starts here */
		(output->token).number = matchNumber(input, position);
		output->type = NUMBER;
		return output;
	}
	if (isalpha(input[*position])) {
		/* we see a letter, so an identifier starts here */
		(output->token).identifier = matchIdentifier(input, position);
		output->type = IDENTIFIER;
		return output;
	}
	/* no space, no number, no identifier: we call it a symbol */
	(output->token).symbol = matchSymbol(input, position);
	output->type = SYMBOL;
	return output;
}

List *tokenList(const char *input) {
	List *lastNode = NULL;
	List *currentNode = NULL;
	List *headNode = NULL;
	int inputLength = strlen(input);
	int position = 0;
	while (position < inputLength) {
		if (isspace(input[position])) {
			position++;
		} else {
			currentNode = newNode(input, &position);
			if (lastNode == NULL) {
				/* there is no list yet; start it with node */
				headNode = currentNode;
			} else {
				/* there is already a list; add node at the end */
				(lastNode)->next = currentNode;
			}
			lastNode = currentNode;
		}
	}
	return headNode;
}

void printList(const List *list) {
	while (list != NULL) {
		switch (list->type) {
			case NUMBER:
				printf("%i ",(list->token).number);
				break;
			case IDENTIFIER:
				printf("%s ",(list->token).identifier);
				break;
			case SYMBOL:
				printf("%c ",(list->token).symbol);
				break;
		}
		list = list->next;
	}
	printf("\n");
}

void freeTokenList(List *list) {
	if (list == NULL) {
		return;
	}
	if (list->type == IDENTIFIER) {
		free((list->token).identifier);
	}
	freeTokenList(list->next);
	free(list);
}

#endif
