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

int acceptFactor(List **list) {
	if (acceptNumber(list)) {
		return 1;
	}
	if (acceptIdentifier(list)) {
		return 1;
	}
	if (acceptSymbol('(', list)) {
		return acceptExpression(list) && acceptSymbol(')', list);
	}
	return 0;
}

int acceptTerm(List **list) { // needs change according to excercise
	if (!acceptFactor(list)) {
		return 0;
	}
	while (acceptSymbol('*', list) || acceptSymbol('/', list)) {
		// If we encounter a * or /, 
		// it must be followed by another term
		if (!acceptFactor(list)) {
			return 0;
		}
	}
	return 1;
}

int acceptExpression(List **list) { // needs change according to excercise
	if (!acceptTerm(list)) {
		return 0;
	}
	while (acceptSymbol('+', list) || acceptSymbol('-', list)) {
		// If we encounter a + or -, 
		// it must be followed by another term
		if (!acceptTerm(list)) {
			return 0;
		}
	}
	return 1;
}
// end of recognizeExp.c

