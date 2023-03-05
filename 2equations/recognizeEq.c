/* file   : recognizeEq.c */
/* author : Aksel Joonas Reedi (s4790820) Mihkel Mariuz Jezierski (S4787730) */

/* Description:
 * Implementation of recognition of simple 
 * calculation expressions and solving them. 
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

int acceptTerm(List **list) { 
	if (acceptNumber(list)) {  // checks if the current input is a number
		if (acceptIdentifier(list)) { // after finding an number check if there is an identifier
			if(acceptSymbol('^', list)) { // check for degree and if found check if its a number
				return acceptNumber(list);
			}
		}
	} else if (acceptIdentifier(list)) { // if not a number checks if the current input is a identifier
		if(acceptSymbol('^', list)) { // check for degree and if found check if its a number
			return acceptNumber(list);
		}	
	} else if (acceptSymbol('=', list) || acceptSymbol('+', list)|| acceptSymbol('-', list)){ // checks for double signs ex. x = = 4
		return 0;
	} else if ((*list) == NULL){ // if there is not anything after = sign
		return 0;
	}
	
	return 1;
}

int acceptExpression(List **list) { 
	(acceptSymbol('-', list)); // if expression starts with '-' go forward
			
	if (!acceptTerm(list)) { // if you cant find a term after starting to find an experssion, quit
		return 0;
	} 
	
	while (acceptSymbol('+', list) || acceptSymbol('-', list)){ // if an experssion has multiple terms loop forward
		if (!acceptTerm(list)){
			return 0; 
		}
	}

	return 1;
}

int isValidEquation(List *list) {
	if (acceptExpression(&list)) { // try to find the first expression
		if (acceptSymbol('=', &list)) { // after finding the first expression try to find = 
			return acceptExpression(&list) && list == NULL; // after finding = try to find second expression and if there is something more return 0
		}
	}

	return 0; // if cant find expressions
}
	

int isSingleVariableEquation(List *list) { // checks if the equation has two or more variables
	// two character arrays are made to compare potentially >1 found identifiers,
	// counter to track the amount of identifiers (whether it is more than 1), and a variable to check if any identifiers are found at all.
	char *arr1 = NULL;
	char *arr2 = NULL;
	int counter = 0;
	int identifierFound = 0;

	while(list != NULL) { // this while loop checks every node of the list

		// if an identifier is found, it is saved into the array
		if (list->type == IDENTIFIER) {
			identifierFound = 1;
			arr1 = (list->token).identifier;

			// if there are more than two identifiers and they are not the same, return 0 (not a single variable eq)
			if (counter > 0 && strcmp(arr1, arr2) != 0) {
				return 0;
			}

			arr2 = arr1;
			counter++;
		}
		list = list->next;
	}
	// if none identifiers found, return 0
	if (identifierFound == 0) {
		return 0;
	}

	return 1;
}
	

int getDegree(List *list) {
	
	// initialised to 1 since this function is ran only on equations with found identifiers (which is at least degree 1)
	int maxDegreeFound = 1;
	while(list->next != NULL) {
		// this if statement checks every degree indicated after '^'. If it is larger than previous maxDegreeFound, then it is saved
		if ((list->token).symbol == '^') {
			if((list->next)->type == NUMBER && ((list->next)->token).number > maxDegreeFound) {
				maxDegreeFound = ((list->next)->token).number;
			}
		}
		list = list->next;
	}

	return maxDegreeFound;
}

// calculating linear equations
void calculateEq(List *list){


	int identifier = 0, number = 0;

	while( !acceptSymbol('=', &list)){ // run first loop until = sign is found

		if (acceptSymbol('-', &list)){ // if found a term that starts with - sign
			
			if (list->type == NUMBER){ // if term starts with number
				if((list->next)->type == IDENTIFIER){ // case example 5x=0
					if (((list->next)->next)->type == SYMBOL &&((list->next)->next)->token.symbol == '^') { // if identifier is to the power of something
						
						if ((((list->next)->next)->next)->token.number == 0) { // if power is 0 it is just a number
							
							number += (list->token).number; 
							list = (list)->next; // move to account for identifier
							list = (list)->next; // move to account for power symbol
							list = (list)->next; // move to account for power number

						} else if ((((list->next)->next)->next)->token.number == 1) {// if power is 1 it acts as a normal identifier
							
							identifier -= (list->token).number;
							list = (list)->next; // move to account for identifier
							list = (list)->next; // move to account for power symbol
							list = (list)->next; // move to account for power number
						}
					} else { // if no power is found
						
						identifier -= (list->token).number;
						list = (list)->next; // to move forward to count for the identifier
					}
				} else{ // if its just a number without an identifier
					number += (list->token).number;
				}
			} else if (list->type == IDENTIFIER){ // if indentifier without any number
				if (list->next != NULL && (list->next)->type == SYMBOL && (list->next)->token.symbol == '^') { // if identifier is to the power of something
						
					if (((list->next)->next)->token.number == 0) { 	// if power is 0 it is just a number	
						number++; 
						list = (list)->next; // move to account for identifier
						list = (list)->next; // move to account for power symbol
						
					} else if (((list->next)->next)->token.number == 1) { // if power is 0 it is just a number
						
						identifier--;
						list = (list)->next; // move to account for identifier
						list = (list)->next; // move to account for power symbol
						
					}
				} else { // if not to the pwr
					
					identifier--;
					
				}
			}
		} else { // normal term

			if (list->type == NUMBER){ // if term starts with number

				if((list->next)->type == IDENTIFIER){ // if number + identifier case example 5x=0
					if (((list->next)->next)->type == SYMBOL &&((list->next)->next)->token.symbol == '^') { // if identifier is to the power of something
						
						if ((((list->next)->next)->next)->token.number == 0) { // if power is 0 it is just a number
							
							number -= (list->token).number; 
							list = (list)->next; // move to account for identifier
							list = (list)->next; // move to account for power symbol
							list = (list)->next; // move to account for power number

						} else if ((((list->next)->next)->next)->token.number == 1) { // if power is 1 it acts as a normal identifier
							
							
							identifier += (list->token).number;
							list = (list)->next; // move to account for identifier
							list = (list)->next; // move to account for power symbol
							list = (list)->next; // move to account for power number
						}
					} else { // if no power symbol
						
						identifier += (list->token).number;
						list = (list)->next; // to move forward to count for the identifier
					}
				} else{ // if a normal number
					number -= (list->token).number;
				}
			} else if (list->type == IDENTIFIER){ // if identifier without number
				if (list->next != NULL && (list->next)->type == SYMBOL && (list->next)->token.symbol == '^') { // if identifier is to the power of something
						
						if (((list->next)->next)->token.number == 0) {// if power is 0 it is just a number	
							
							number--; 
							list = (list)->next; // move to account for identifier
							list = (list)->next; // move to account for power symbol
							

						} else if (((list->next)->next)->token.number == 1) {// if power is 1 it acts as a normal identifier
							
							identifier++;
							list = (list)->next; // move to account for identifier
							list = (list)->next; // move to account for power symbol
							
						}
					} else {// if no power symbol
						
						identifier++;

					}
			}
		}
		
		

		list = (list)->next; // move to the next item

	}
	
	
	while (list != NULL){ //check second expression after =

		
		if (acceptSymbol('-', &list)){ //account for negative expressions
			if (list->type == NUMBER){  
				if(list->next != NULL && (list->next)->type == IDENTIFIER){ // check for identifier after the number
					if ((list->next)->next != NULL && ((list->next)->next)->type == SYMBOL &&((list->next)->next)->token.symbol == '^') { // check if there is a power
						
						if (((list->next)->next)->next != NULL && (((list->next)->next)->next)->token.number == 0) { // if the power is 0, add to the constant number
							
							number -= (list->token).number; 
							list = (list)->next; // move to account for identifier
							list = (list)->next; // move to account for power symbol
							list = (list)->next; // move to account for power number

						} else if ((((list->next)->next)->next)->token.number == 1) { //if power is 1, add one to the identifier counter
							
							identifier += (list->token).number;
							list = (list)->next; // move to account for identifier
							list = (list)->next; // move to account for power symbol
							list = (list)->next; // move to account for power number
						}
					} else { // if there is no power, simply add the number to identifier counter
						
						identifier += (list->token).number;
						list = (list)->next; // to move forward to count for the identifier
					}
				} else{ // if there is simply a number without an identifier
					number -= (list->token).number;
				}
			} else if (list->type == IDENTIFIER){ // if there is an identifier without a constant number before it
				if (list->next != NULL && (list->next)->type == SYMBOL && (list->next)->token.symbol == '^') { // everything else follows the same logic as above.
						
						if (((list->next)->next)->token.number == 0) {
							
							number--; 
							list = (list)->next; // move to account for identifier
							list = (list)->next; // move to account for power symbol
							

						} else if (((list->next)->next)->token.number == 1) {
							
							identifier++;
							list = (list)->next; // move to account for identifier
							list = (list)->next; // move to account for power symbol
						
						}
					} else {
						
						identifier++;
						 // to move forward to count for the identifier
					}
			}
		} else { // if the term is positive (+), everything else is the same

			if (list->type == NUMBER){ 
				if(list->next != NULL && (list->next)->type == IDENTIFIER){ //if 5x=0
					if ((list->next)->next != NULL && ((list->next)->next)->type == SYMBOL &&((list->next)->next)->token.symbol == '^') { 
						
						if (((list->next)->next)->next != NULL && (((list->next)->next)->next)->token.number == 0) {
							
							number += (list->token).number; 
							list = (list)->next; // move to account for identifier
							list = (list)->next; // move to account for power symbol
							list = (list)->next; // move to account for power number

						} else if ((((list->next)->next)->next)->token.number == 1) {
							
							identifier -= (list->token).number;
							list = (list)->next; // move to account for identifier
							list = (list)->next; // move to account for power symbol
							list = (list)->next; // move to account for power number
						}
					} else {	
						identifier -= (list->token).number;
						list = (list)->next; // to move forward to count for the identifier
					}
				} else{
					number += (list->token).number;
				}
			} else if (list->type == IDENTIFIER){
				if (list->next != NULL && (list->next)->type == SYMBOL && (list->next)->token.symbol == '^') { 

					if (((list->next)->next)->token.number == 0) {

						number++; 
						list = (list)->next; // move to account for identifier
						list = (list)->next; // move to account for power symbol
							
					} else if (((list->next)->next)->token.number == 1) {

						identifier--;
						list = (list)->next; // move to account for identifier
						list = (list)->next; // move to account for power symbol
							
					}
				} else {
					identifier--;
				}
			}
		}
			list = (list)->next;
	}

	// calculate the answer and print it
	double answer = (double)number/(double)identifier;
	if (answer < 0 && answer > -0.0005) {
		answer = 0;
	}
	if (identifier == 0) {
		printf("not solvable\n");
	} else {
		printf("solution: %.3lf\n", answer);
	}
}
