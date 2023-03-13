// declares a dictionary

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word
#define LENGTH 45

// standard implementation for a trie
typedef struct trieNode Trie;

// a dictionary is an array
typedef struct dictonary Dictionary;

Dictionary *newEmptyDictionary();
void addWord(const char *word, Dictionary *dictionary);
bool check(const char *word, Dictionary *dictionary);
void freeDictionary(Dictionary *n);

#endif // DICTIONARY_H
