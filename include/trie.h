#ifndef TRIE_H
#define TRIE_H

#include "library.h"

typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
    char hint[MAX_HINT_LENGTH];
    int index;
    bool used;
} TrieNode;

// Trie functions
TrieNode* createNode();
void insertTrie(TrieNode* root, const char* word, const char* hint);
void insertTrieWithIndex(TrieNode* root, const char* word, const char* hint, int index);
bool searchTrie(TrieNode* root, const char* word);
int searchTrieWithIndex(TrieNode* root, const char* word);
int countWordsWithPrefix(TrieNode* root, char prefix);
int countWords(TrieNode* node);
bool getRandomWordHelper(TrieNode* node, char* word, int depth, char* hint, int* index, int target, bool markUsed);
bool getRandomWord(TrieNode* root, char prefix, char* word, char* hint, int* index, bool markUsed);
void freeTrie(TrieNode* root);
void resetUsedFlags(TrieNode* root);

#endif