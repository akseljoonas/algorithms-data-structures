// file        : planes.c
// version     : 2.1
// author(s)   : Mihkel Mariusz Jezierski (m.m.jezierski@student.rug.nl) & Aksel Joonas Reedi (a.j.reedi@student.rug.nl)
// date        : Fri Feb 11 2023
// compilation : gcc -std=c99 -Wall -pedantic -lm planes.c stack.c queue.c -o planes


/* description of the program: This program handles airport traffic, sorts the incoming planes to the hangar
   (with capacity of 5 planes) and waiting runway (with capacity of 7 planes) based on whether the plane needs
   repairs or not. In addition, this program controlls the departures that are explained below with the comments. */

#include <stdio.h>   // endables input/output commands
#include <stdlib.h>  // enables standard library of functions
#include <assert.h>  // enables the use of assertions
#include <math.h>    // math functions
#include <string.h>  // enables string library, e.g. strlen(str)
#include "stack.h"   // adds stack data structure
#include "queue.h"	 // adds queue data structure

// 0 for assertions on, 1 for assertions off
#if 0
#define NDEBUG
#endif

#define RUNWAY_CAPACITY 7
#define HANGAR_CAPACITY 5
char repairStatus[3];

int main(int argc, char *argv[]) {


	Queue *waitingRunway = newQueue(RUNWAY_CAPACITY);
	Stack *hangar = newStack(HANGAR_CAPACITY);

	//these variables track number of planes for both the hangar and the waiting runway, and the plane name indexes, accordingly.
	int numOfPlanesInHangar = 0;
	int numOfPlanesOnRunway = 0;
	int planeIndex = 0;

	while (1) {
		// getting plane index number (name) and checking if it needs repairStatus or not (goes to hangar or waiting runway)
		scanf("%d", &planeIndex);
		// "-1" plane index indicates the end of the input, hence it breaks from the loop
        if (planeIndex == -1) {
			break;
		}
		scanf("%s", repairStatus);

		if (!strcmp(repairStatus, "yes")) {
			push(planeIndex, hangar);
			numOfPlanesInHangar++;
		} else {
			enqueue(planeIndex, waitingRunway);
			numOfPlanesOnRunway++;
		}

		// if the runway is at full capacity, all planes on the waiting queue are let to depart
		if (numOfPlanesOnRunway == RUNWAY_CAPACITY) {
			for (int i = 0; i<RUNWAY_CAPACITY; i++) {
					printf("%d\n", dequeue(waitingRunway));
				}
			// since all planes have left the runway (dequeued and printed out) the numOfPlanesOnRunway is set to 0
			numOfPlanesOnRunway = 0;
		}

		// if the hangar stack is full, all planes from the runway are let to depart, and all planes from the hangar exit outside to the runway (therefore enqueued to the waiting queue)
		if (numOfPlanesInHangar == HANGAR_CAPACITY) {

			// waiting runway is cleared
			for (int i = 0; i<numOfPlanesOnRunway; i++) {
				printf("%d\n", dequeue(waitingRunway));
			}
			numOfPlanesOnRunway = 0;

			// all planes from the hangar are moved to the waiting runway queue
			for (int i = 0; i<HANGAR_CAPACITY; i++) {
				int checkVariable = pop(hangar);
				enqueue(checkVariable, waitingRunway);
				numOfPlanesOnRunway++;
			}
			numOfPlanesInHangar = 0;
		}
		
	}
	
	// last planes, if there are any, (before emptying the hangar) are let to depart
	if (numOfPlanesOnRunway > 0) {
		for (int i = 0; i<numOfPlanesOnRunway; i++) {
			printf("%d\n", dequeue(waitingRunway));
		}
		numOfPlanesOnRunway = 0;
	}

	// last planes from the hangar are moved to the waiting runway queue and then immidiately departed from the queue
	if (numOfPlanesInHangar > 0) {
		for (int i = 0; i<numOfPlanesInHangar; i++) {
			int checkVariable = pop(hangar);
			enqueue(checkVariable, waitingRunway);
			numOfPlanesOnRunway++;
		}
		numOfPlanesInHangar = 0;

		for (int i = 0; i<numOfPlanesOnRunway; i++) {
			printf("%d\n", dequeue(waitingRunway));
		}
		numOfPlanesOnRunway = 0;
	}

	// both waitingRunway queue's and hangar stack's memory are freed
	freeQueue(waitingRunway);
	freeStack(hangar);	

	return 0;
}
