/* file   : recognizeExp.h */
/* author : Harmen de Weerd (harmen.de.weerd@rug.nl) */

/* Description:
 * Additional functionality for recognizing 
 * simple calculations expressions. Requires a 
 * token list as described by scanner.h
 */
#ifndef RECOGEXP_H
#define RECOGEXP_H
#include "scanner.h"

int acceptExpression(List **list);

#endif