/* file   : evalExp.c */
/* author : Harmen de Weerd (harmen.de.weerd@rug.nl) */

/* Description:
 * Implementation of evaluation of simple 
 * calculation expressions.
 *
 * Note that this implementation explicitly depends 
 * on the implementation of recognition of expressions.
 */

#include <stdlib.h>
#include "recognizeExp.h"
#include "evalExp.h"

int acceptSymbol(char symbol, List **list); // Implemented in expression recognition

int valueNumber(List **list, double *value) {
	if (*list != NULL && (*list)->type == NUMBER) {
		*value = ((*list)->token).number;
		*list = (*list)->next;
		return 1;
	}
	return 0;
}

int valueFactor(List **list, double *value) {
	if (valueNumber(list, value)) {
		return 1;
	}
	if (acceptSymbol('(', list)) {
		return valueExpression(list, value) && acceptSymbol(')', list);
	}
	return 0;
}

int valueTerm(List **list, double *value) {
	double operandValue;
	if (!valueFactor(list, value)) {
		return 0;
	}
	while (*list != NULL) {
		if (acceptSymbol('*', list)) {
			if (valueFactor(list, &operandValue)) {
				*value *= operandValue;
			} else {
				return 0;
			}
		} else if (acceptSymbol('/', list)) {
			if (valueFactor(list, &operandValue)) {
				*value /= operandValue;
			} else {
				return 0;
			}
		} else {
			return 1;
		}
	}
	return 1;
}

int valueExpression(List **list, double *value) {
	double operandValue;
	if (!valueTerm(list, value)) {
		return 0;
	}
	while (*list != NULL) {
		if (acceptSymbol('+', list)) {
			if (valueTerm(list, &operandValue)) {
				*value += operandValue;
			} else {
				return 0;
			}
		} else if (acceptSymbol('-', list)) {
			if (valueTerm(list, &operandValue)) {
				*value -= operandValue;
			} else {
				return 0;
			}
		} else {
			return 1;
		}
	}
	return 1;
}
