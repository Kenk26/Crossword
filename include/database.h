#ifndef DATABASE_H
#define DATABASE_H

#include "library.h"

typedef struct WordDatabase {
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    char hints[MAX_WORDS][MAX_HINT_LENGTH];
    int count;
} WordDatabase;

// Database functions
void saveWordDatabase(WordDatabase* db);
bool loadWordDatabase(WordDatabase* db);
void initializeDefaultWordDatabase(WordDatabase* db);
void addWordToDatabase(WordDatabase* db, const char* word, const char* hint);
void addNewWord(WordDatabase* db);

#endif