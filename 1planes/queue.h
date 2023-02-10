/* file   : queue.h */
/* author : Harmen de Weerd (harmen.de.weerd@rug.nl) */

/* Description:
 * An abstract data type implementation of queues.
 * Note how nearly all the implementation details 
 * are hidden from the user. In particular, the
 * user does not know whether queues are implemented
 * as stacks, arrays, or something else.
 *
 * The user still needs to create and free a queue 
 * manually.
 */

typedef struct queue Queue;
	
Queue *newQueue(int initialSize);
	// Creates a new Queue of a given initial size.
	
void freeQueue(Queue *q);
	// Frees a previously created Queue.
	
void enqueue(int value, Queue *q);
	// Adds a value to a Queue.
	
int dequeue(Queue *q);
	// Removes and returns the oldest value on the Queue.
	
int isEmptyQueue(Queue *q);
	// Determines whether a Queue is empty.
