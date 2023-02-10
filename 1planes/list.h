/* file   : list.h */
/* author : Harmen de Weerd (harmen.de.weerd@rug.nl) */

/* Description:
 * An abstract data type implementation of lists.
 * Note how nearly all the implementation details 
 * are hidden from the user. 
 */

typedef struct listNode List;
	
List *newEmptyList();
	// Creates a new List with no content.
	
void freeList(List *li);
	// Frees a previously created List.
	
void addItem(int item, List *li);
	// Adds a value to a List.
	
int removeFirstItem(List *li);
	// Removes and returns the most recent value in the List.
	
int isEmptyList(List *li);
	// Determines whether a List is empty.

void addItemAtPos(int item, List *li, int position);
void removeItem(List *li, int value);



