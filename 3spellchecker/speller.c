// a SLOW spell checker

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
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


	while ((c = getchar()) && c != EOF) {
		// logic how to combine the char into word
		word[index] = c;
		index++;
		word[index] = '\0';
		// the if has to check if we reached a non alpha number and that we already scanned a word
		if (!isalpha(c) && isalpha(word[index-2])){ // if scanned char is not alphabetical the end of word has been reached
			trimWord(word);
			if (!check(word, dictionary)) {
				counter++;
				printf("%s\n",word);
			}
			//index = 0;
			while (index != 0){ // set word back to 0
				word[index] = 0;
				index--;
			}
			
		}
		
	}

	// step 3: print number of unknown words
	printf("%d\n", counter);
	freeDictionary(dictionary);
	return 0;
}
