
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include "scanner.h"
#include "recognizeExp.h"
#include "evalExp.h"
#include "prefixExp.h"
#include "infixExp.h"


int valueNumber(List **list, double *value);

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
			} else {
				printf("the formula evaluates to %f\n", valueExpTree(tree)); // actual calculations
			}
		} else {
			printf("this is not a valid infix expression\n");
		}
		freeExpTree(tree);
		free(ar);
		freeTokenList(list);
		printf("\ngive an expression: "); // for next expression
		ar = readInput();
	}
	free(ar);
	printf("good bye\n");
}


