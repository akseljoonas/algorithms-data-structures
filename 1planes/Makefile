
a.out: planes.c stack.c queue.c list.c
	gcc -g -O2 -std=c99 -pedantic -Wall -Wno-unused-result *.c -lm

.PHONY: run example debug clean

run: a.out
	./a.out

example: a.out
	cat exampleInput.txt | ./a.out

debug: a.out
	cat exampleInput.txt | valgrind ./a.out

clean:
	rm a.out
