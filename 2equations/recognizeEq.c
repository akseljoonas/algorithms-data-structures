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
#include <string.h>
#include <math.h>


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
	}
		//printf("!\n");
		return 1;
}

int acceptExpression(List **list) { // needs change according to excercise
	if (!acceptTerm(list)) {
		if (acceptSymbol('-', list)) {
			goto label_1;
		}
		return 0;
	} 

	//printf("First term checked!\n");
	
	while (acceptSymbol('+', list) || acceptSymbol('-', list)){
		label_1:
		if (!acceptTerm(list)){
			return 0; 
		}
	}
	
	return 1;
}

int isValidEquation(List *list) {
	//printf("Starting first expression check\n");
	if (acceptExpression(&list)) {
		//printf("First expression done!\n");
		if (acceptSymbol('=', &list)) {
			//printf("Starting second expression check!\n");
			return acceptExpression(&list);
		}
	}
	return 0;
}
	

int isSingleVariableEquation(List *list) {

	char *arr1 = NULL;
		char *arr2 = NULL;
		int counter = 0;

	while(list->next != NULL) {
		
		if (list->type == IDENTIFIER) {
			arr1 = (list->token).identifier;

			if (counter > 0 && strcmp(arr1, arr2) != 0) {
				
				return 0;
			}

			arr2 = arr1;
			counter++;
		}
		list = list->next;
	}

	return 1;
	
	
	
	
}
	

int getDegree(List *list) {
	
	int maxDegree = 1;
	while(list->next != NULL) {
	
		if ((list->token).symbol == '^') {
			if((list->token).number > maxDegree) {
				maxDegree = ((list->next)->token).number;
			}
		}
		list = list->next;
	}
	return maxDegree;
	
	//return 1;
	
}
	// Return the degree of the single variable equation list.