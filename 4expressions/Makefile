CC     = gcc
CFLAGS = -std=c99 -pedantic -Wall

prefix: scanner.c recognizeExp.c evalExp.c prefixExp.c prefix_test.c
	$(CC) $(CFLAGS) $^ -o $@


infix: scanner.c recognizeExp.c evalExp.c prefixExp.c infixExp.c infix_test.c
	$(CC) $(CFLAGS) $^ -o $@

part1-test: infix
	cat example_part1_input.txt | ./infix

part1-debug: infix
	cat example_part1_input.txt | valgrind --leak-check=full ./infix


part2-test: infix
	cat example_part2_input.txt | ./diff

part2-debug: infix
	cat example_part2_input.txt | valgrind --leak-check=full ./diff


clean:
	rm -f pref infix
