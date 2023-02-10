// file        : planes.c
// version     : 0.2
// author(s)      : Mihkel Mariusz Jezierski (m.m.jezierski@student.rug.nl) & Aksel Joonas Reedi (a.j.reedi@student.rug.nl)
// date        : Fri Feb 10 2023
// compilation : gcc -std=c99 -Wall -pedantic -lm planes.c stack.c queue.c -o planes


/* description of the program: */

#include <stdio.h>   // endables input/output commands
#include <stdlib.h>  // enables standard library of functions
#include <assert.h>  // enables the use of assertions
#include <math.h>    // math functions
#include <string.h>  // enables string library, e.g. strlen(str)

#include "stack.h"
#include "queue.h"
#define RUNWAY_CAPACITY 7
#define HANGAR_CAPACITY 5



int main(int argc, char *argv[]) {
	Queue *waitingRunway = newQueue(RUNWAY_CAPACITY);
	Stack *hangar = newStack(HANGAR_CAPACITY);
	int planeIndex = 0;
	int numOfPlanesInHangar = 0;
	int numOfPlanesOnRunway = 0;
	char repairs[3];
	
	while (planeIndex != -1) {
		// getting plane index number (name) and checking if it needs repairs or not (goes to hangar or waiting runway)
		scanf("%d", &planeIndex);
        if (planeIndex == -1) {
			break;
		}
		scanf("%s", repairs);

		if (!strcmp(repairs, "yes")) {
			push(planeIndex, hangar);
			numOfPlanesInHangar++;
			printf("plane %d moved to hangar\n", hangar.array[hangar.top]);
		} else {
			enqueue(planeIndex, waitingRunway);
			numOfPlanesOnRunway++;
			printf("plane %d moved to the waiting runway\n", waitingRunway.array[waitingRunway.front]) ;
		}

		// if the runway is at full capacity, all planes are let to depart
		if (numOfPlanesOnRunway == RUNWAY_CAPACITY) {
			for (int i = 0; i<RUNWAY_CAPACITY; i++) {
					printf("%d\n", dequeue(waitingRunway));
				}
			// all planes have left the runway
			numOfPlanesOnRunway = 0;
		}

		// if the hangar is full, all planes from the runway depart, and all planes from the hangar exit outside to the runway
		if (numOfPlanesInHangar == HANGAR_CAPACITY) {

			for (int i = 0; i<numOfPlanesOnRunway; i++) {
					printf("%d\n", dequeue(waitingRunway));
				}
			numOfPlanesOnRunway = 0;

			for (int i = 0; i<HANGAR_CAPACITY; i++) {
				enqueue(pop(hangar), waitingRunway);
			}
			numOfPlanesInHangar = 0;
		}
	}
	

	if (numOfPlanesOnRunway > 0) {
		for (int i = 0; i<numOfPlanesOnRunway; i++) {
		printf("%d\n", dequeue(waitingRunway));
		}
		numOfPlanesOnRunway = 0;
	}

	if (numOfPlanesInHangar > 0) {
		for (int i = 0; i<numOfPlanesInHangar; i++) {
			enqueue(pop(hangar), waitingRunway);
			numOfPlanesOnRunway++;
		}
		numOfPlanesInHangar = 0;

		for (int i = 0; i<numOfPlanesOnRunway; i++) {
			printf("%d\n", dequeue(waitingRunway));
		}
		numOfPlanesOnRunway = 0;
	}
	

	return 0;
}

