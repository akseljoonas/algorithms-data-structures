
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <string.h> // strings
#include "scanner.h"
#include "recognizeExp.h"
#include "evalExp.h"
#include "prefixExp.h"
#include "infixExp.h"


int valueNumber(List **list, double *value);


void makeTreeCopy (ExpTree **currentTreeNode, ExpTree **copyTreeNode) {
	if ((*currentTreeNode) == NULL){
		return; 
	}
	
	if ((*currentTreeNode)->type == IDENTIFIER) {
		*copyTreeNode = newExpTreeNode(IDENTIFIER, (*currentTreeNode)->token);
	}
	if ((*currentTreeNode)->type == SYMBOL) {
		*copyTreeNode = newExpTreeNode(SYMBOL, (*currentTreeNode)->token);
	}
	if ((*currentTreeNode)->type == NUMBER) {
		*copyTreeNode = newExpTreeNode(NUMBER, (*currentTreeNode)->token);
	}
	
	makeTreeCopy(&(*currentTreeNode)->left, &(*copyTreeNode)->left);
	makeTreeCopy(&(*currentTreeNode)->right, &(*copyTreeNode)->right);
	
}

int deriveNode(ExpTree **treeNode) {
 /*
	dn/dx = 0
	dy/dx = 0 if y is an identifier different from x 
	dx/dx = 1
*/

	if ((*treeNode)->type == IDENTIFIER){
		(*treeNode)->type = NUMBER;

		if (!strcmp(((*treeNode)->token).identifier, "x")) { // loodame et on õige
			return 1;
		}
	}
	return 0;
	


	// switch ((*treeNode)->type) {
	// 	case IDENTIFIER :
	// 		if (!strcmp(((*treeNode)->token).identifier,'x')) { // loodame et on õige
	// 			return 1;
	// 		} else {
	// 			return 0;
	// 		}
	// 		break;
	// 	case NUMBER :
	// 		return 0;
	// 		break;
	// }

}



void differentiate(ExpTree **treeNode){


	/*
	// base check
	if ((*treeNode) == NULL){
		return; 
	}
	
	// simple derivative check
	if (treeNode == Identifier || treeNode == Number) {
		deriveNode(treeNode);
		return;
	}

	if (((*treeNode)->token).symbol == '+ või -'){ 
		currentLeft = differentiate(currentLeft);
		currentRight = differentiate(currentRight);
	}


	if (((*treeNode)->token).symbol == '*'){ 
		A = currentLeft
		B = currentRight

		uus tree
		createNode +
		createLeft *
			createLeftLeft differentiate(A)
			createLeftRight B
		createRight *
			createRightLeft differentiate(B)
			createRightRight A

		(*treeNode) = uus tree

	}

	if (((*treeNode)->token).symbol == '/'){ 
		A = currentLeft;
		B = currentRight;
		Aprime = A;
		Bprime = B;
		differentiate(Aprime);
		differentiate(Bprime);
		uus tree
		createNode /
			createNodeLeft -
				createNodeLeftLeft *
					createNodeLeftLeftLeft Aprime;
					createNodeLeftLeftRight B
				createNodeLeftRight *
					createNodeLeftRightLeft Bprime;
					createNodeLeftRightRight A
			createNodeRight *
				createNodeRightLeft A
				createNodeRightRight A
	}

	kõige lõpus simplifyWholeWAdeva
	
	*/


	// recursion base case
	if ((*treeNode) == NULL){
		return; 
	}

	// simple derivative check
	if ((*treeNode)->type == IDENTIFIER || (*treeNode)->type == NUMBER) {
		((*treeNode)->token).number = deriveNode(treeNode);
		return;
	}


	if (((*treeNode)->token).symbol == '+' || ((*treeNode)->token).symbol == '-' ){ 
		differentiate(&(*treeNode)->left); // currentLeft = differentiate((*treeNode)->left);
		differentiate(&(*treeNode)->right); //currentRight = differentiate((*treeNode)->right);
	}
	
	
	if (((*treeNode)->token).symbol == '*'){
	
		
		// A = currentLeft;
		ExpTree *a = NULL;
		makeTreeCopy(&(*treeNode)->left, &a);


		// B = currentRight;
		ExpTree *b = NULL; 
		makeTreeCopy(&(*treeNode)->right, &b);
		// Aprime = A;
		ExpTree *aPrime = NULL;


		makeTreeCopy(&a, &aPrime);

	
		differentiate(&aPrime);


		// Bprime = B;
		ExpTree *bPrime = NULL;
		makeTreeCopy(&b, &bPrime);


		differentiate(&bPrime);

		
		// new tree
		ExpTree *tempTree = NULL;

		// createNode +
		Token temp;
		temp.symbol = '+';
		tempTree = newExpTreeNode(SYMBOL,temp );
		
		
		//printf("SEGMENTATION FOULT HERE LOL\n");

		// createLeft *
		temp.symbol = '*';

		//((tempTree->left)->token).symbol = '*';

			// 	createLeftLeft differentiate(A)
			(tempTree->left) = newExpTreeNode(SYMBOL, temp);
			((tempTree->left)->left) = aPrime;

			// 	createLeftRight B
			((tempTree->left)->right) = b;
		
		// createRight *

			// 	createRightLeft differentiate(B)
			(tempTree->right) = newExpTreeNode(SYMBOL, temp);
			((tempTree->right)->left) = bPrime;

			// 	createRightRight A
			((tempTree->right)->right) = a;
		
		// (*treeNode) = uus tree
		*treeNode = tempTree;
	}

	if (((*treeNode)->token).symbol == '/'){
	
		// A = currentLeft;
		ExpTree *a = NULL;
		makeTreeCopy(&(*treeNode)->left, &a);


		// B = currentRight;
		ExpTree *b = NULL; 
		makeTreeCopy(&(*treeNode)->right, &b);
		// Aprime = A;
		ExpTree *aPrime = NULL;


		makeTreeCopy(&a, &aPrime);

	
		differentiate(&aPrime);


		// Bprime = B;
		ExpTree *bPrime = NULL;
		makeTreeCopy(&b, &bPrime);


		differentiate(&bPrime);


		// printf("\nprint a: ");
		// printExpTreeInfix(a);
		// printf("type: %d\n", a->type);
		// printf("\nprint aPrime: ");
		// printExpTreeInfix(aPrime);
		// printf("\nprint b: ");
		// printExpTreeInfix(b);
		// printf("type: %d\n", b->type);
		// printf("\nprint bPrime: ");
		// printExpTreeInfix(bPrime);
		// printf("\n");

		// new tree
		ExpTree *tempTree = NULL;
	
		// createNode +
		Token temp;
		temp.symbol = '/';
		tempTree = newExpTreeNode(SYMBOL,temp );
		
		temp.symbol = '-';


			(tempTree->left) = newExpTreeNode(SYMBOL, temp);
			temp.symbol = '*';
			((tempTree->left)->left) = newExpTreeNode(SYMBOL,temp );
			(((tempTree->left)->left)->left) = aPrime;
			(((tempTree->left)->left)->right) = b;
			((tempTree->left)->right) = newExpTreeNode(SYMBOL,temp );
			(((tempTree->left)->right)->left) = bPrime;
			(((tempTree->left)->right)->right) = a;
			(tempTree->right) = newExpTreeNode(SYMBOL, temp);
			((tempTree->right)->left) = b;
			((tempTree->right)->right) = b;
			*treeNode = tempTree;
	}
	/*
	if (((*treeNode)->token).symbol == '/'){ 
		A = currentLeft;
		B = currentRight;
		Aprime = A;
		Bprime = B;
		differentiate(Aprime);
		differentiate(Bprime);
		uus tree
		createNode /
			createNodeLeft -
				createNodeLeftLeft *
					createNodeLeftLeftLeft Aprime;
					createNodeLeftLeftRight B
				createNodeLeftRight *
					createNodeLeftRightLeft Bprime;
					createNodeLeftRightRight A
			createNodeRight *
				createNodeRightLeft A
				createNodeRightRight A
	}
	

	if (((*treeNode)->token).symbol == '/'){ 

		// A = currentLeft;
		ExpTree *a = (*treeNode)->left;


		// B = currentRight;
		ExpTree *b = (*treeNode)->right;
		// Aprime = A;
		ExpTree *aPrime = NULL;


		makeTreeCopy(&a, &aPrime);

	
		differentiate(&aPrime);


		// Bprime = B;
		ExpTree *bPrime = NULL;
		makeTreeCopy(&b, &bPrime);


		differentiate(&bPrime);
		

	}*/
}





void simplify(ExpTree **treeNode){
	// recursion base case
	if ((*treeNode) == NULL){
		return; 
	}

	// go to bottom logic
	simplify (&(*treeNode)->left);
	simplify (&(*treeNode)->right);

	// do simplification logic

	// if *
	if (((*treeNode)->token).symbol == '*'){
		//if e*0 or 0*e
		if ((((*treeNode)->left)->token).number == 0){
			
			*treeNode = (*treeNode)->left;
			return;
			
			/*ExpTree *tempNode = (*treeNode)->left;
			free((*treeNode)->left);
			free((*treeNode)->right);
			*treeNode = tempNode;
			free(tempNode);
			return;*/
		}
		if ((((*treeNode)->right)->token).number == 0){
			*treeNode = (*treeNode)->right;
			return;
		}
		// if e*1 or 1*e
		if ((((*treeNode)->left)->token).number == 1){
			*treeNode = (*treeNode)->right;
			return;
		}
		if ((((*treeNode)->right)->token).number == 1){
			*treeNode = (*treeNode)->left;
			return;
		}
	}

	// if /
	if (((*treeNode)->token).symbol == '/'){
		//if e/1
		if ((((*treeNode)->right)->token).number == 1){
			*treeNode = (*treeNode)->left;
			return;
		}
	}

	// if + 
	if (((*treeNode)->token).symbol == '+'){
		//if e+0 or 0+e
		if ((((*treeNode)->left)->token).number == 0){
			*treeNode = (*treeNode)->right;
			return;

		}
		if ((((*treeNode)->right)->token).number == 0){
			*treeNode = (*treeNode)->left;
			return;

		}
	}

	// if -
	if (((*treeNode)->token).symbol == '-'){
		//if e-0
		if ((((*treeNode)->right)->token).number == 0){
			*treeNode = (*treeNode)->left;
			return;

		}
	}


	// free node
	//free(treeNode);

}


int acceptBracket(char symbol, List **list, ExpTree **tree){
	if ((*list != NULL && (*list)->type == SYMBOL && ((*list)->token).symbol == '(') || (*list != NULL && (*list)->type == SYMBOL && ((*list)->token).symbol == ')')) {
		if ((*list)->next != NULL) {
			*list = (*list)->next;
		}

		return 1;
	}
	return 0;
}

int acceptTreeSymbol(char symbol, List **list, ExpTree **tree) {
	

	if (*list != NULL && (*list)->type == SYMBOL && ((*list)->token).symbol == symbol) {
		*tree = newExpTreeNode(SYMBOL, (*list)->token);

		*list = (*list)->next;
		return 1;
	}
	return 0;
}

int acceptTreeIdentifier(List **list, ExpTree **tree) {
	if (*list != NULL && (*list)->type == IDENTIFIER) {
		*tree = newExpTreeNode(IDENTIFIER, (*list)->token);
		*list = (*list)->next;
		return 1;
	}
	return 0;
}

int acceptTreeNumber(List **list, ExpTree **tree) {


	if (*list != NULL && (*list)->type == NUMBER) {


		*tree = newExpTreeNode(NUMBER, (*list)->token);
		*list = (*list)->next;
		return 1;
	}


	return 0;
}

int treeFactor(List **list, ExpTree **tree ) {
	if (acceptTreeNumber(list, tree)) {


		return 1;
	}
	if (acceptTreeIdentifier(list, tree)) {
		return 1;
	}
	if (acceptBracket('(', list, tree)) {


		ExpTree *expression = NULL;
		treeExpression(list, &expression);

		*tree = expression;
		acceptBracket(')', list, tree);
		return 1;
	}
	return 0;
}

int treeTerm(List **list, ExpTree **tree)  { // pass down a tree


	if (!treeFactor(list, tree)) { // build a factor
		return 0;
	}
	ExpTree *leftBranchTree = NULL; 
	while (acceptTreeSymbol('*', list, &leftBranchTree) || acceptTreeSymbol('/', list, &leftBranchTree)) { 
		// If we encounter a * or /, 
		leftBranchTree->left = *tree;

		// it must be followed by another term


		if (!treeFactor(list, &(leftBranchTree)->right)) {
			return 0;
		}
		*tree = leftBranchTree;
	}
	return 1;
}

int treeExpression(List **list, ExpTree **tree) {

	
	if (!treeTerm(list, tree)) {
		return 0;
	}
	ExpTree *leftBranchTree = NULL; 

	
	while (acceptTreeSymbol('+' ,list , &leftBranchTree) || acceptTreeSymbol('-',list ,&leftBranchTree)) {
		// If we encounter a + or -,
		leftBranchTree->left = *tree;
		// it must be followed by another term


		if (!treeTerm(list, &(leftBranchTree)->right)) {
			return 0;
		}



		*tree = leftBranchTree;
	}

	return 1;
}


void doExpTrees() {
	char *ar;
	List *list;
	printf("give an expression: ");
	ar = readInput();
	while (ar[0] != '!') {
		list = tokenList(ar); // ?? 
		printList(list);
		List *listPosition = list;
		ExpTree *tree = NULL;
		if (acceptExpression(&listPosition) && listPosition == NULL && treeExpression(&list, &tree) /* create the tree*/ ) {

			printf("the formula is ");
			printExpTreeInfix(tree); // print tree in infix notation
			printf("\n");
			if (!isNumerical(tree)) { // look though tree and check that does not have x y z 
				printf("this is not a numerical infix expression\n");
				printf("simplified: ");
				simplify(&tree); //simplify tree
				printExpTreeInfix(tree); // print tree in infix notation
				printf("\n");
				printf("derivative to x: ");
				// derive
				differentiate(&tree);
				// simplify
				simplify(&tree); //simplify tree
				// print derive tree
				printExpTreeInfix(tree); // print tree in infix notation
				printf("\n");
			} else {
				printf("the formula evaluates to %f\n", valueExpTree(tree)); // actual calculations
			}
		} else {
			printf("this is not a valid infix expression\n");
		}
		//freeExpTree(tree);
		free(ar);
		freeTokenList(list);
		printf("\ngive an expression: "); // for next expression
		ar = readInput();
	}
	free(ar);
	printf("good bye\n");
}