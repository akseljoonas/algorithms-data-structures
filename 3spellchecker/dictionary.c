// implements a dictionary

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "dictionary.h"

// standard implementation for a trie
struct trieNode {
	bool endNode ;
	Trie * children [26];
};


// A dictionary is an array
struct dictonary {
	int numWords;
	int maxWords;
	char **words;
};

Dictionary *newEmptyDictionary() {
	Dictionary *dictionary = malloc(sizeof(Dictionary));
	assert(dictionary != NULL);
	dictionary->numWords = 0;
	dictionary->maxWords = 1;
	dictionary->words = malloc(dictionary->maxWords * sizeof(char *));
	return dictionary;
}

// add word to the dictionary if it is is not already known
void addWord(const char *word, Dictionary *dictionary) {
	if (!check(word, dictionary)) {
		// if we need more space before adding the word, double the size
		if (dictionary->numWords == dictionary->maxWords) {
			dictionary->maxWords *= 2;
			dictionary->words = realloc(dictionary->words,dictionary->maxWords * (sizeof(char *)));
			assert(dictionary->words != NULL);
		}
		
		// now we actually add the word
		dictionary->words[dictionary->numWords] = malloc((LENGTH + 1) * sizeof(char));
		strcpy(dictionary->words[dictionary->numWords], word);
		dictionary->numWords++;
	}
}

// check whether word is in dictionary
bool check(const char *word, Dictionary *dictionary) {
	for (int i = 0; i < dictionary->numWords; i++) {
		if (strcmp(dictionary->words[i], word) == 0) {
			return true;
		}
	}
	return false;
}

void freeDictionary(Dictionary *dictionary) {
	for (int i = 0; i < dictionary->numWords; i++) {
		free(dictionary->words[i]);
	}
	free(dictionary->words);
	free(dictionary);
}
