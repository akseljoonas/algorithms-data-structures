
#ifndef PREFIXEXP_H
#define PREFIXEXP_H
#include "scannerStructs.h"

typedef struct expTreeNode ExpTree;

struct expTreeNode {
	TokenType type;
	Token token;
	ExpTree *left;
	ExpTree *right;
};

ExpTree *newExpTreeNode(TokenType type, Token token);
int valueIdentifier(List **list, char **pString);
int valueOperator(List **list, char *operator);
int isNumerical(ExpTree *tree);
double valueExpTree(ExpTree *tree);
int treePrefixExpression(List **listNode, ExpTree **treeNode);
void printExpTreeInfix(ExpTree *tree);
void prefExpTrees();
void freeExpTree(ExpTree *treeNode);
int isOperator(char c);

#endif
