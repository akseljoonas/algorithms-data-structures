/* file   : scannerStructs.h */
/* author : Harmen de Weerd (harmen.de.weerd@rug.nl) */

/* Description:
 * The internal structure of the data types used in
 * scanner.c. Programs extending the functionality
 * probably need these declarations.
 *
 */
#ifndef SCANNERSTRUCTS_H
#define SCANNERSTRUCTS_H

typedef enum tokenType {
	NUMBER,
	IDENTIFIER,
	SYMBOL
} TokenType;

typedef union token {
	int number;
	char *identifier;
	char symbol;
} Token;

struct listNode {
	TokenType type;
	Token token;
	List *next;
};

#endif
