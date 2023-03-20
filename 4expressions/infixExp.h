
#ifndef INFIXEXP_H
#define INFIXEXP_H
#include "scannerStructs.h"

typedef struct expTreeNode ExpTree;

ExpTree *newExpTreeNode(TokenType type, Token token);
int acceptTreeSymbol(char symbol, List **list, ExpTree **tree);
int acceptTreeIdentifier(List **list, ExpTree **tree);
int acceptTreeNumber(List **list, ExpTree **tree);
int treeFactor(List **list, ExpTree **tree );
int treeTerm(List **list, ExpTree **tree);
int treeExpression(List **list, ExpTree **tree);
void doExpTrees();

#endif