/* file   : recognizeEq.c */
/* author : ??? */

/* Description:
 * Implementation of recognition of simple 
 * calculation expressions.
 *
 * Note that this implementation explicitly depends 
 * on the implementation of the scanner, and therefore
 * includes "scannerStructs.h" in addition to "scanner.h". 
 */

#include "scanner.h"
#include "scannerStructs.h"
#include "recognizeEq.h"
#include <stdlib.h>
#include <stdio.h>


// start of recognizeExp.c
int acceptSymbol(char symbol, List **list) {
	if (*list != NULL && (*list)->type == SYMBOL && ((*list)->token).symbol == symbol) {
		*list = (*list)->next;
		return 1;
	}
	return 0;
}

int acceptIdentifier(List **list) {
	if (*list != NULL && (*list)->type == IDENTIFIER) {
		*list = (*list)->next;
		return 1;
	}
	return 0;
}

int acceptNumber(List **list) {
	if (*list != NULL && (*list)->type == NUMBER) {
		*list = (*list)->next;
		return 1;
	}
	return 0;
}

int acceptTerm(List **list) { // needs change according to excercise
	if (acceptNumber(list)) { // putsis gray area
		if (acceptIdentifier(list)) {
			if (acceptSymbol("+", list)){
				return 1;
			}
			 else if(acceptSymbol("⌃", list)) {
				return acceptNumber(list);
			}
		} else if (acceptSymbol("+", list)) {
			return 1;
		}
	} else if (acceptIdentifier(list)) {
		if (acceptSymbol("+", list)){
				return 1;
		} else if(acceptSymbol("⌃", list)) {
				return acceptNumber(list);
		}
	} else {
		printf("!");
		return 0;
	} 
}

int acceptExpression(List **list) { // needs change according to excercise
	// expression 1
	while (acceptSymbol("=", list)) {
		if (acceptTerm(list) == 0) {
			return 0;
		}
	}
	// expression 2
	while (acceptSymbol("\n", list)) {
		if (acceptTerm(list) == 0) {
			return 0;
		}
	}
	
	return 1;
}

int isValidEquation(List *list) {
	return acceptExpression(&list);
}
	

int isSingleVariableEquation(List *list);
	// Return 1 if and only if the TokenList list 
	// represents a valid equation that includes exactly
	// one variable.

int getDegree(List *list);
	// Return the degree of the single variable equation list.