/* file   : recognizeExp.c */
/* author : Harmen de Weerd (harmen.de.weerd@rug.nl) */

/* Description:
 * Implementation of recognition of simple 
 * calculation expressions.
 */

#include <stdlib.h>
#include "scanner.h"
#include "scannerStructs.h"
#include "recognizeExp.h"

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

int acceptTerm(List **list)  { // pass down a tree
	if (!acceptFactor(list)) { // build a factor
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

int acceptExpression(List **list) {
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
