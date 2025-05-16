#include "trie.h"

TrieNode* createNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    node->isEndOfWord = false;
    node->hint[0] = '\0';
    node->index = -1;
    node->used = false;
    return node;
}

void insertTrie(TrieNode* root, const char* word, const char* hint) {
    TrieNode* current = root;

    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!current->children[index]) {
            current->children[index] = createNode();
        }
        current = current->children[index];
    }

    current->isEndOfWord = true;
    strcpy(current->hint, hint);
}

void insertTrieWithIndex(TrieNode* root, const char* word, const char* hint, int index) {
    TrieNode* current = root;

    for (int i = 0; i < strlen(word); i++) {
        int idx = word[i] - 'a';
        if (!current->children[idx]) {
            current->children[idx] = createNode();
        }
        current = current->children[idx];
    }

    current->isEndOfWord = true;
    strcpy(current->hint, hint);
    current->index = index;
}

bool searchTrie(TrieNode* root, const char* word) {
    TrieNode* current = root;

    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!current->children[index]) {
            return false;
        }
        current = current->children[index];
    }

    return (current != NULL && current->isEndOfWord);
}

int searchTrieWithIndex(TrieNode* root, const char* word) {
    TrieNode* current = root;

    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!current->children[index]) {
            return -1;
        }
        current = current->children[index];
    }

    if (current != NULL && current->isEndOfWord) {
        return current->index;
    }
    return -1;
}

int countWordsWithPrefix(TrieNode* root, char prefix) {
    TrieNode* current = root;
    int index = prefix - 'a';

    if (!current->children[index]) {
        return 0;
    }

    current = current->children[index];
    return countWords(current);
}

int countWords(TrieNode* node) {
    int count = 0;

    if (node->isEndOfWord) {
        count++;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            count += countWords(node->children[i]);
        }
    }

    return count;
}

bool getRandomWordHelper(TrieNode* node, char* word, int depth, char* hint, int* index, int target, bool markUsed) {
    static int count = 0;

    if (target == 0) {
        count = 0;
    }

    if (node->isEndOfWord && !node->used) {
        if (count == target) {
            word[depth] = '\0';
            strcpy(hint, node->hint);
            *index = node->index;
            if (markUsed) {
                node->used = true;
            }
            count = 0;
            return true;
        }
        count++;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            word[depth] = 'a' + i;
            if (getRandomWordHelper(node->children[i], word, depth + 1, hint, index, target, markUsed)) {
                return true;
            }
        }
    }

    return false;
}

bool getRandomWord(TrieNode* root, char prefix, char* word, char* hint, int* index, bool markUsed) {
    TrieNode* current = root;
    int prefixIndex = prefix - 'a';

    if (!current->children[prefixIndex]) {
        return false;
    }

    current = current->children[prefixIndex];
    int wordCount = countWords(current);
    if (wordCount == 0) {
        return false;
    }

    int randomIndex = rand() % wordCount;
    char tempWord[MAX_WORD_LENGTH] = {0};
    tempWord[0] = prefix;

    if (getRandomWordHelper(current, tempWord, 1, hint, index, randomIndex, markUsed)) {
        strcpy(word, tempWord);
        return true;
    }
    return false;
}

void freeTrie(TrieNode* root) {
    if (root == NULL) {
        return;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            freeTrie(root->children[i]);
        }
    }

    free(root);
}

void resetUsedFlags(TrieNode* root) {
    if (root == NULL) {
        return;
    }

    root->used = false;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            resetUsedFlags(root->children[i]);
        }
    }
}