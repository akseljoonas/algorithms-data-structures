/* file   : queue.c */
/* author : Harmen de Weerd (harmen.de.weerd@rug.nl) */

/* Description:
 * Implementation of the queue abstact data type.
 * In this implementation, queues are arrays.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"

struct queue {
	int *array;
	int back;
	int front;
	int size;
};

Queue *newQueue(int initialSize) {
	Queue *output = malloc(sizeof(Queue));
	assert(output != NULL);
	output->array = malloc(initialSize * sizeof(int));
	assert(output->array != NULL);
	output->back = 0;
	output->front = 0;
	output->size = initialSize;
	return output;
}

void freeQueue (Queue *q) {
	free(q->array);
	free(q);
}

void doubleQueueSize(Queue *q) {
	int originalSize = q->size;
	q->size *= 2;
	q->array = realloc(q->array, q->size * sizeof(int));
	assert(q->array != NULL);
	for (int i = 0; i < q->back; i++) {
		q->array[originalSize + i] = q->array[i];
	}
	q->back = q->back + originalSize;
}

void enqueue(int item, Queue *q) {
	q->array[q->back] = item;
	q->back = (q->back + 1) % q->size;
	if (q->back == q->front) {
		doubleQueueSize(q);
	}
}

int isEmptyQueue(Queue *q) {
	return (q->back == q->front);
}

void queueEmptyError() {
	printf("Queue empty: dequeue failed.\n");
	exit(EXIT_FAILURE);
}

int dequeue(Queue *q) {
	if (isEmptyQueue(q)) {
		queueEmptyError();
	}
	int item = q->array[q->front];
	q->front = (q->front + 1) % (q->size);
	return item;
}
