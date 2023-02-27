/* file   : recognizeEq.h */
/* author : Harmen de Weerd (harmen.de.weerd@rug.nl) */

/* Description:
 * Additional functionality for recognizing 
 * simple equations. Requires a token list 
 * as described by scanner.h
 */
#ifndef RECOGNIZEEQ_H
#define RECOGNIZEEQ_H

#include "scanner.h"

int isValidEquation(List *list);
	// go throught the list
		// check if have expression 
			// check if have term


	// Return 1 if and only if the TokenList list is a valid equation

int isSingleVariableEquation(List *list);
	// Return 1 if and only if the TokenList list 
	// represents a valid equation that includes exactly
	// one variable.

int getDegree(List *list);
	// Return the degree of the single variable equation list.


void calculateEq(List *list);
	// calculates the solution to the equation if its valid equation
#endif
