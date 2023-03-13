// file        : speller.c
// author      : Mihkel Mariusz Jezierski (s4787730) && Aksel Joonas Reedi (s4790820)
// date        : Tue Mar 07 2023


/* description of the program: This program checks whether words are present in a dictionary*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

// remove non-alphabetic characters and convert to lower case
void trimWord(char *word) {
  int k = 0;
  for (int i = 0; i < (int) strlen(word); i++) {
    if (isalpha(word[i])) {
      word[k] = tolower(word[i]);
      k++;
    }
  }
  word[k] = '\0';
}


int main(int argc, char *argv[]) {
	char word[LENGTH + 1] = "";

	// step 1: read in the trie
	Trie *trie = newTrieNode();
	while (scanf("%45s", word) && word[0] != '!') {
		trimWord(word);
		addWord(word, trie);
	}

	// step 2: read in text
	int counter = 0; // number of unknown words
	int index = 0;
	int c = EOF;

	// scanning in the words, letter by letter into word array
	while ((c = getchar()) && c != EOF) {
		// logic how to combine the char into word
		word[index] = c;
		index++;
		word[index] = '\0';
		if (!isalpha(c) && isalpha(word[index-2])){ // if scanned char is not alphabetical the end of word has been reached
			trimWord(word);
			//printing words, that were not in the dictionary
			if (!check(word, trie)) {
				counter++;
				printf("%s\n",word);
			}

			while (index != 0){ // set word back to 0
				word[index] = 0;
				index--;
			}
			
		}
		
	}

	// step 3: print number of unknown words and free the memory in the trie
	printf("%d\n", counter);
	freeTrie(trie);
	return 0;
}
