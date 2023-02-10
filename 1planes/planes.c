// file        : planes.c
// version     : 0.2
// author(s)      : Mihkel Mariusz Jezierski (m.m.jezierski@student.rug.nl) & Aksel Joonas Reedi (a.j.reedi@student.rug.nl)
// date        : Fri Feb 10 2023
// compilation : gcc -std=c99 -Wall -pedantic -lm planes.c -o planes


/* description of the program: */

#include <stdio.h>   // endables input/output commands
#include <stdlib.h>  // enables standard library of functions
#include <assert.h>  // enables the use of assertions
#include <math.h>    // math functions
#include <string.h>  // enables string library, e.g. strlen(str)

#include "stack.h"
#include "queue.h"
#define RUNWAY_CAPACITY 7
#define GARAGE_CAPACITY 5



int main(int argc, char *argv[]) {
	Queue *waitingRunway = newQueue(RUNWAY_CAPACITY);
	Stack *hangar = newStack(GARAGE_CAPACITY);
	int planeIndex = 0;
	int currentHangarOc = 0;
	int currentRunwayOc = 0;
	char *repairs; 
	char no[] = "No";
	while (planeIndex != -1) {
		scanf("%d %s", &planeIndex, repairs);

		if (strcmp(repairs, no)) { // if repairs str is longer than 'no' then push into hangar
			push(planeIndex, hangar);
			currentHangarOc++;
		} else {
			enqueue(planeIndex, waitingRunway);
			currentRunwayOc++;
		}

		if (currentRunwayOc == RUNWAY_CAPACITY) {
			//for // every plane in the queue, dequeue

		}

		if (currentHangarOc == GARAGE_CAPACITY) {
			//for // every plane in the queue, dequeue
			//for // every plane in the hangar, add to queue
			// kas sa näed seda v?
			// 2
		}
	}

	if (currentHangarOc > 0) {
		//for // every plane in the hangar, add to queue
		//for // very plane in the queue, dequeue
	}

	return 0;
}
