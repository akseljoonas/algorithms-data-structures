CC = gcc

CFLAGS = -O2 -std=c99 -pedantic -Wall -o -lm

recog: recognizeTest.c scanner.c recognizeEq.c
	$(CC) $(CFLAGS) $^ -o $@

eval: evalTest.c scanner.c recognizeEq.c evalEq.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean

clean:
	rm -f recog eval
