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
			
			if(acceptSymbol('^', list)) {
				return acceptNumber(list);
			}
		}
	} else if (acceptIdentifier(list)) {
			
			
		if(acceptSymbol('^', list)) {
			return acceptNumber(list);
		}

	} else if (acceptSymbol('=', list)){
		return 0;
	}

	//printf("!\n");
	return 1;
}

int acceptExpression(List **list) { // needs change according to excercise
	if (!acceptTerm(list)) {
		if (acceptSymbol('-', list)) {
			goto label_1;
		}
		//printf("returnin 0\n");
		return 0;
	} 

	//printf("esimene term sisse võetud\n");
	
	while (acceptSymbol('+', list) || acceptSymbol('-', list)){
		label_1:
		if (!acceptTerm(list)){
			return 0; 
		}
	}
	
	

	return 1;
}

int isValidEquation(List *list) {
	//printf("alustan esimese expressioniga\n");
	if (acceptExpression(&list)) {
		printf("Esimene expression done!\n");
		if (acceptSymbol('=', &list)) {
			//printf("Jõudsin peale esimest võrdus märki!\n");
			//check if = again
			return acceptExpression(&list) && !acceptSymbol('=', &list);
		}
	}
	return 0;
}
	

int isSingleVariableEquation(List *list);
	// Return 1 if and only if the TokenList list 
	// represents a valid equation that includes exactly
	// one variable.

int getDegree(List *list);
	// Return the degree of the single variable equation list.