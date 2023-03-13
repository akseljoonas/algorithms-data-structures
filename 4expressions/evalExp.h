/* file   : evalExp.h */
/* author : Harmen de Weerd (harmen.de.weerd@rug.nl) */

/* Description:
 * Additional functionality for recognizing 
 * simple calculations expressions. Requires a 
 * token list as described by scanner.h
 */

#ifndef EVALEXP_H
#define EVALEXP_H
#include "scanner.h"
#include "scannerStructs.h"

int valueExpression(List **list, double *value);

#endif