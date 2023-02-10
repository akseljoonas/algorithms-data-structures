/* file   : stack.h */
/* author : Harmen de Weerd (harmen.de.weerd@rug.nl) */

/* Description:
 * An abstract data type implementation of stacks.
 * Note how nearly all the implementation details 
 * are hidden from the user. The user still needs
 * to create and free a stack manually.
 */

typedef struct stack Stack;

int pop(Stack *st);
	// Removes and returns the most recently added item from the stack
void push(int item, Stack *st);
	// Adds an item onto the stack
Stack *newStack(int initialSize);
	// Creates a new stack with a given initial size
void freeStack(Stack *st);
	// Frees the memory associated with a given stack
int isEmptyStack(Stack *st);
	// Determines whether there are no items on the stack
