#ifndef GAME_H
#define GAME_H

#include "library.h"
#include "database.h"
#include "user.h"
#include "trie.h"

// Game functions
void playGame(WordDatabase* db, User* u);
void generateCrossword(char grid[GRID_SIZE][GRID_SIZE], WordDatabase* db, TrieNode* mainTrie, TrieNode* gameTrie, char hints2[][MAX_HINT_LENGTH]);

#endif