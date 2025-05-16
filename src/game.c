#include "game.h"
// Add this definition at file scope
int HintCounter = 0;

void playGame(WordDatabase* db, User* u) {
    system("cls");
    TrieNode* mainTrie = createNode();
    TrieNode* gameTrie = createNode();

    for (int i = 0; i < db->count; i++) {
        insertTrie(mainTrie, db->words[i], db->hints[i]);
    }

    char hints2[numWords][MAX_HINT_LENGTH] = {""};
    int index[numWords];
    char grid[GRID_SIZE][GRID_SIZE];
    char grid2[GRID_SIZE][GRID_SIZE];

    EmptyHints(hints2, numWords, index);
    EmptyGrid(grid, GRID_SIZE);
    EmptyGrid(grid2, GRID_SIZE);

    freeTrie(gameTrie);
    gameTrie = createNode();
    resetUsedFlags(mainTrie);

    char playerName[MAX_NAME_LENGTH];
    printf("\n\nEnter User Name: ");
    fflush(stdin);
    fgets(playerName, MAX_NAME_LENGTH, stdin);
    playerName[strcspn(playerName, "\n")] = 0;
    printf("\n\n");

    generateCrossword(grid, db, mainTrie, gameTrie, hints2);
    CopyGrid(grid, grid2);

    clock_t start_time = clock();

    while (1) {
        printGrid(grid2);
        HintsDisplayer(hints2, index);

        if (CompareGrids(grid, grid2)) {
            break;
        }

        char str[MAX_WORD_LENGTH];
        printf("\nEnter Word To Fill Crossword: ");
        scanf("%s", str);

        if (searchTrie(gameTrie, str)) {
            system("cls");
            int ind = searchTrieWithIndex(gameTrie, str);
            if (ind != -1) {
                index[ind] = ind;
            }
            updateDisplayGrid(grid, grid2, str);
        } else {
            system("cls");
            printf("\nIncorrect\n\n");
        }
    }

    clock_t end_time = clock();
    float duration_user = (float)(end_time - start_time) / CLOCKS_PER_SEC;

    insert_min_user(u, duration_user, playerName);
    int temp = u->size_u;

    for (int i = temp / 2; i > 0; i--) {
        heapify_min(u, i, temp);
    }
    user_min_sort(u, u->size_u);

    freeTrie(mainTrie);
    freeTrie(gameTrie);
}

void generateCrossword(char grid[GRID_SIZE][GRID_SIZE], WordDatabase* db, TrieNode* mainTrie, TrieNode* gameTrie, char hints2[][MAX_HINT_LENGTH]) {
    srand(time(NULL));

    bool isHorizontal = false;
    int randomIndex = rand() % db->count;

    char currentWord[MAX_WORD_LENGTH];
    strcpy(currentWord, db->words[randomIndex]);
    strcpy(hints2[HintCounter], db->hints[randomIndex]);

    insertTrieWithIndex(gameTrie, currentWord, db->hints[randomIndex], HintCounter);
    HintCounter++;

    int startRow = 0;
    int startCol = 0;
    int randomCharPos = (rand() % (strlen(currentWord) - 1)) + 1;
    char randomChar = currentWord[randomCharPos];
    int iIndex = 0;
    int jIndex = 0;

    for (int i = 0; i < strlen(currentWord); ++i) {
        if (currentWord[i] == randomChar) {
            iIndex = 0;
            jIndex = startCol + i;
        }
        grid[startRow][startCol + i] = currentWord[i];
    }

    for (int wordCount = 1; wordCount < numWords; ++wordCount) {
        char hint[MAX_HINT_LENGTH];
        int wordIndex = -1;

        if (!getRandomWord(mainTrie, randomChar, currentWord, hint, &wordIndex, true)) {
            char randomLetter = 'a' + (rand() % 26);
            if (!getRandomWord(mainTrie, randomLetter, currentWord, hint, &wordIndex, true)) {
                continue;
            }
        }

        strcpy(hints2[HintCounter], hint);
        insertTrieWithIndex(gameTrie, currentWord, hint, HintCounter);

        HintCounter++;

        startRow = iIndex;
        startCol = jIndex;
        randomCharPos = (rand() % (strlen(currentWord) - 1)) + 1;
        randomChar = currentWord[randomCharPos];

        for (int i = 0; i < strlen(currentWord); ++i) {
            if (isHorizontal) {
                if (i == 0) {
                    jIndex++;
                    continue;
                }
                if (currentWord[i] == randomChar) {
                    jIndex = startCol + i;
                }
                grid[startRow][startCol + i] = currentWord[i];
            } else {
                if (i == 0) {
                    iIndex++;
                    continue;
                }
                if (currentWord[i] == randomChar) {
                    iIndex = startRow + i;
                }
                grid[startRow + i][startCol] = currentWord[i];
            }
        }

        isHorizontal = !isHorizontal;
    }
}