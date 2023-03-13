// file        : dictionary.c
// author      : Mihkel Mariusz Jezierski (s4787730) && Aksel Joonas Reedi (s4790820)
// date        : Tue Mar 07 2023

/* description of the program: This part of the code implements the word
addition to the dictionary, checks if certain words are in the dictionary and the creation of trie nodes*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dictionary.h"

// a trie node, which has a child node for each letter in alphabet
struct trieNode {	
	bool isEndNode;
	Trie *children[26];
};

// creating a new trie node and setting all child nodes to NULL
Trie *newTrieNode() {
	Trie *trie = malloc(sizeof(Trie));
	assert(trie != NULL);
	trie->isEndNode = 0;
	for (int i = 0; i < 26; i++) {
		trie->children[i] = NULL;
	}
	return trie;
}

// add a word to the dictionary trie.
void addWord(const char *word, Trie *trie) {
	/* Temporary trie pointer is made, so it can be moved to add words, 
	and be resetted when next word is going to be added */
	Trie *tempTrie = trie; 
	int index = 0;
	// for each letter equivalent node children is assigned to next letters node pointer
	while (word[index] != '\0'){
		int letter = (int)(word[index] - 'a');
		if (tempTrie->children[letter] == NULL){
			tempTrie->children[letter] = newTrieNode();
		}
		tempTrie = tempTrie->children[letter];
		index++;
	}
	// isEndNode indicates if the node is a leaf ndoe
	tempTrie->isEndNode = 1;
}

// check whether word is in dictionary trie, by checking each chars node children, and every next chars equivalent children
bool check(const char *word, Trie *trie) {
	Trie *tempTrie = trie;
	for(int i = 0; i < strlen(word); i++) {
		int letter = (int)(word[i] - 'a');
		if (tempTrie->children[letter] != NULL) {
			tempTrie = tempTrie->children[letter];
		} else {
			return 0;
		}
	}
	// the word is in a dictionary if the checker arrives to EndNode, thus recognizing each char in a word
	if (tempTrie->isEndNode == 1) {
		return 1;
	}

	return 0;
}

void freeTrie(Trie *n) {
	
	for (int i = 0; i < 26; i++) {
		if (n->children[i] != NULL) {
			freeTrie(n->children[i]);
		}
	}
	free(n);
}
