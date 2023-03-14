// file        : dictionary.h
// author      : Mihkel Mariusz Jezierski (s4787730) && Aksel Joonas Reedi (s4790820)
// date        : Tue Mar 07 2023

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word
#define LENGTH 45

<<<<<<< HEAD
// a dictionary is a trie
=======
// standard implementation for a trie
typedef struct trieNode Trie;

// a dictionary is an array
typedef struct dictonary Dictionary;
>>>>>>> 05ae4af2bb9fa69be9126e3ddf1a11a0dc5a3121

typedef struct trieNode Trie;
Trie *newTrieNode();
void addWord(const char *word, Trie *trie);
bool check(const char *word, Trie *trie);
void freeTrie(Trie *n);

#endif // DICTIONARY_H
