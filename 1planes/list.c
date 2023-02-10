/* file   : list.c */
/* author : Harmen de Weerd (harmen.de.weerd@rug.nl) */

/* Description:
 * Implementation of the list abstact data type.
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "list.h"

struct listNode {
	int item;
	List *next;
};

void listMemoryFailure() {
	printf("Failed to allocate memory for list item.\n");
	exit(EXIT_FAILURE); 
}

List *newEmptyList() {
	List *output = malloc(sizeof(List));
	if (output == NULL) {
		listMemoryFailure();
	}
	output->next = NULL;
	return output;
}

void addItem(int item, List *li) {
	List *newNode = newEmptyList();
	newNode->item = item;
	newNode->next = li->next;
	li->next = newNode;
}

void listEmptyError() {
	printf("List empty: failed to remove item.\n");
	exit(EXIT_FAILURE);
}

int removeFirstItem(List *li) {
	if (li->next == NULL) {
		listEmptyError();
	}
	List *nodeToRemove = li->next;
	li->next = nodeToRemove->next;
	int returnValue = nodeToRemove->item;
	free(nodeToRemove);
	return returnValue;
}

void freeList(List *li) {
	if (li->next != NULL) {
		freeList(li->next);
	}
	free(li);
}

int isEmptyList(List *li) {
	return (li->next == NULL);
}

void listTooShort() {
	printf("List too short\n");
	exit(EXIT_FAILURE); 
}

int itemAtPos(List *li, int position) {
	if (li == NULL || li->next == NULL) {
		listTooShort();
	}
	if (position == 0) {
    	return (li->next)->item;
	} else {
    	return itemAtPos(li->next, position - 1);
	}
}

void addItemAtPos(int item, List *li, int position) {
	if (li == NULL || li->next == NULL) {
		listTooShort();
	}
	if (position == 0) {
		addItem(item, li);
	} else {
		addItemAtPos(item, li->next, position - 1);
	}
}

void removeItem(List *li, int value) {
	if (li != NULL && li->next != NULL) {
		if (itemAtPos(li, 0) == value) {
			removeFirstItem(li);
		} else {
			removeItem(li->next, value);
		}
	}
}

