/* file   : recognizeTest.c */
/* author : Harmen de Weerd (harmen.de.weerd@rug.nl) */

/* Description:
 * Dialog for entering equations
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include "scanner.h"
#include "recognizeEq.h"

void recognizeEquations() {
	char *input;
	List *list;
	printf("give an equation: ");
	input = readInput();
	while (input[0] != '!') {
		list = tokenList(input);
		printList(list);
		if (isValidEquation(list)) {
			if (isSingleVariableEquation(list)) {
				printf("this is an equation in 1 variable of degree %i\n", getDegree(list));
			} else {
				printf("this is an equation, but not in 1 variable\n");
			}
		} else {
			printf("this is not an equation\n");
		}
		free(input);
		freeTokenList(list);
		printf("\ngive an equation: ");
		input = readInput();
	}
	free(input);
	printf("good bye\n");
}

int main(int argc, char *argv[]) {
	recognizeEquations();
}
