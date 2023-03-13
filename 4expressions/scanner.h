/* file   : scanner.h */
/* author : Harmen de Weerd (harmen.de.weerd@rug.nl) */

/* Description:
 * An abstract data type for a token list scanner 
 * for expressions. The token list scanner separates 
 * a string of characters into numbers, identifiers,
 * and symbols.
 */

#ifndef SCANNER_H
#define SCANNER_H
#define MAXINPUT 100  /* maximal length of the input */

typedef struct listNode List;

char *readInput();
List *tokenList(const char *input);
void printList(const List *list);
void freeTokenList(List *list);

#endif