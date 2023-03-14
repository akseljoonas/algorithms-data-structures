
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include "scanner.h"
#include "recognizeExp.h"
#include "evalExp.h"
#include "infixExp.h"

int valueNumber(List **list, double *value);

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

int treePrefixExpression(List **listNode, ExpTree **treeNode) {
	if (listNode == NULL || *listNode == NULL) {
		return 0;
	}
	Token token;
	double value;
	if (valueNumber(listNode, &value)) {
		token.number = (int)value;
		*treeNode = newExpTreeNode(NUMBER, token);
	} else if (valueIdentifier(listNode, &(token.identifier))) {
		*treeNode = newExpTreeNode(IDENTIFIER, token);
	} else if (valueOperator(listNode, &(token.symbol))) {
		*treeNode = newExpTreeNode(SYMBOL, token);
		// (if going with ) linking nodes together should be done here
		if (!treePrefixExpression(listNode, &((*treeNode)->left)) ||
		!treePrefixExpression(listNode, &((*treeNode)->right))) { // what exatly is this checking??
			return 0;
		}
	}
	return 1;
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

/* precondition: isNumerical(tr)) */
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


void prefExpTrees() {
	char *ar;
	List *list;
	printf("give an expression: ");
	ar = readInput();
	while (ar[0] != '!') {
		list = tokenList(ar); // ?? 
		printList(list);
		List *listPosition = list;
		ExpTree *tree = NULL;
		if (treePrefixExpression(&listPosition, &tree) && listPosition == NULL) { // if can create tree
			printf("the formula is ");
			printExpTreeInfix(tree); // print tree in infix notation
			printf("\n");
			if (!isNumerical(tree)) { // look though tree and check that does not have x y z 
				printf("this is not a numerical prefix expression\n");
			} else {
				printf("the formula evaluates to %f\n", valueExpTree(tree)); // actual calculations
			}
		} else {
			printf("this is not a valid prefix expression\n");
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
