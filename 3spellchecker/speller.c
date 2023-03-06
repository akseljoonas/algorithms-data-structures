// a SLOW spell checker

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

	// step 1: read in the dictionary
	Dictionary *dictionary = newEmptyDictionary();
	while (scanf("%45s", word) && word[0] != '!') {
		trimWord(word);
		addWord(word, dictionary);
	}

	// step 2: read in text
	int counter = 0; // number of unknown words
	int index = 0;
	int c = EOF;

	// BUG: This loop is wrong. It will read "one,twwo" as one word "onetwwo".
	while ((c = getchar()) && c != EOF) {
		// logic how to combine the char into word
		word[index] = c;
		index++;
		word[index] = '\0';
		if (!isalpha(c) && isalpha(word[index-2])){ // if scanned char is not alphabetical the end of word has been reached
			trimWord(word);
			if (!check(word, dictionary)) {
				counter++;
				printf("%s\n",word);
			}

			while (index != 0){ // set word back to 0
				word[index] = 0;
				index--;
			}
			
		}
		
	}
	// TODO: Replace the above while loop with a correct solution.
	// Hints:
	// - you should read one character at a time, using getchar()
	// - alphabetical characters should be appended to the current word
	// - any other symbol should terminate the word
	// this code might be useful:
	/*
	int index = 0;
	int c = EOF;
	while ((c = getchar()) && c != EOF) {
		// ...
	}
	*/

	// step 3: print number of unknown words
	printf("%d\n", counter);

	freeDictionary(dictionary);
	return 0;
}
