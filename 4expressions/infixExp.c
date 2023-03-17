
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include "scanner.h"
#include "recognizeExp.h"
#include "evalExp.h"
#include "infixExp.h"

int valueNumber(List **list, double *value);
/*
ExpTree *newExpTreeNode(TokenType type, Token token) {
	ExpTree *newNode = malloc(sizeof(ExpTree));
	assert(newNode != NULL);
	newNode->type = type;
	newNode->token = token;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

int valueIdentifier(List **list, char **pString) {
	if (*list != NULL && (*list)->type == IDENTIFIER) {
		*pString = ((*list)->token).identifier;
		*list = (*list)->next;
		return 1;
	}
	return 0;
}

int isOperator(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

int valueOperator(List **list, char *operator) {
	if (*list != NULL && (*list)->type == SYMBOL
	                  && isOperator(((*list)->token).symbol) ) {
		*operator = ((*list)->token).symbol;
		*list = (*list)->next;
		return 1;
	}
	return 0;
}

void freeExpTree(ExpTree *treeNode) {
	if (treeNode == NULL) {
		return;
	}
	freeExpTree(treeNode->left);
	freeExpTree(treeNode->right);
	free(treeNode);
}


void printExpTreeInfix(ExpTree *tree) {
	if (tree == NULL) {
		return;
	}
	switch (tree->type) {
		case NUMBER:
			printf("%i",(tree->token).number);
			break;
		case IDENTIFIER:
			printf("%s",(tree->token).identifier);
			break;	
		case SYMBOL:
			printf("(");
			printExpTreeInfix(tree->left);
			printf(" %c ",(tree->token).symbol);
			printExpTreeInfix(tree->right);
			printf(")");
			break;
	}
}

int isNumerical(ExpTree *tree) {
	assert(tree != NULL);
	if (tree->type == NUMBER) {
		return 1;
	}
	if (tree->type == IDENTIFIER) {
		return 0;
	}
	return (isNumerical(tree->left) && isNumerical(tree->right));
}

/* precondition: isNumerical(tr)) 
double valueExpTree(ExpTree *treeNode) {
	assert(treeNode != NULL);
	if (treeNode->type == NUMBER) {
		return (treeNode->token).number;
	}
	double leftValue = valueExpTree(treeNode->left);
	double rightValue = valueExpTree(treeNode->right);
	switch ((treeNode->token).symbol) {
		case '+':
		return (leftValue + rightValue);
		case '-':
		return (leftValue - rightValue);
		case '*':
		return (leftValue * rightValue);
		case '/':
		assert(rightValue != 0);
		return (leftValue / rightValue);
		default:
		printf("Unrecognized operator '%c'.\n", (treeNode->token).symbol);
		exit(EXIT_FAILURE);
	}
}
*/



/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

int acceptBracket(char symbol, List **list, ExpTree **tree){
	if (*list != NULL && (*list)->type == SYMBOL && ((*list)->token).symbol == '(' || *list != NULL && (*list)->type == SYMBOL && ((*list)->token).symbol == ')') {
		
		
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


