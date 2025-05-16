#include "grid.h"
#include "trie.h"
#include "game.h"

void printGrid(char grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if ((grid[i][j] >= 'A' && grid[i][j] <= 'Z') || (grid[i][j] >= 'a' && grid[i][j] <= 'z')) {
                setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                printf("%c ", grid[i][j]);
                resetColor();
            } else {
                printf("%c ", grid[i][j]);
            }
        }
        printf("\n");
    }
}

void CopyGrid(char grid[GRID_SIZE][GRID_SIZE], char grid2[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if ((grid[i][j] >= 'A' && grid[i][j] <= 'Z') || (grid[i][j] >= 'a' && grid[i][j] <= 'z')) {
                grid2[i][j] = '-';
            } else {
                grid2[i][j] = grid[i][j];
            }
        }
    }
}

bool CompareGrids(char grid[GRID_SIZE][GRID_SIZE], char grid2[GRID_SIZE][GRID_SIZE]) {
    bool flag = true;
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (grid[i][j] != grid2[i][j]) {
                flag = false;
            }
        }
    }
    return flag;
}

bool isValid(int row, int col) {
    return (row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE);
}

bool HorizontalUpdate(char grid[][GRID_SIZE], const char* str, char grid2[][GRID_SIZE], int row, int col, int index) {
    if (index == strlen(str) - 2) {
        if (grid2[row][col] == grid[row][col] && grid2[row][col + 1] == grid[row][col + 1]) {
            return false;
        }
        grid2[row][col] = grid[row][col];
        grid2[row][col + 1] = grid[row][col + 1];
        resetColor();
        return true;
    }
    if (isValid(row, col) && grid[row][col] == str[index]) {
        char temp = grid2[row][col];
        setColor(32);
        grid2[row][col] = grid[row][col];
        if (HorizontalUpdate(grid, str, grid2, row, col + 1, index + 1)) {
            return true;
        }
        resetColor();
        grid2[row][col] = temp;
    }
    return false;
}

bool VerticalUpdate(char grid[][GRID_SIZE], const char* str, char grid2[][GRID_SIZE], int row, int col, int index) {
    if (index == strlen(str) - 2) {
        if (grid2[row][col] == grid[row][col] && grid2[row + 1][col] == grid[row + 1][col]) {
            return false;
        }
        grid2[row][col] = grid[row][col];
        grid2[row + 1][col] = grid[row + 1][col];
        resetColor();
        return true;
    }
    if (isValid(row, col) && grid[row][col] == str[index]) {
        char temp = grid2[row][col];
        setColor(32);
        grid2[row][col] = grid[row][col];
        if (VerticalUpdate(grid, str, grid2, row + 1, col, index + 1)) {
            return true;
        }
        resetColor();
        grid2[row][col] = temp;
    }
    return false;
}

bool HorizontalVerticalUpdate(char grid[][GRID_SIZE], const char* str, char grid2[][GRID_SIZE], int row, int col, int index) {
    if (HorizontalUpdate(grid, str, grid2, row, col, index)) {
        return true;
    }
    if (VerticalUpdate(grid, str, grid2, row, col, index)) {
        return true;
    }
    return false;
}

void updateDisplayGrid(char grid[GRID_SIZE][GRID_SIZE], char grid2[GRID_SIZE][GRID_SIZE], const char* str) {
    bool found = false;
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (HorizontalVerticalUpdate(grid, str, grid2, i, j, 0)) {
                found = true;
                break;
            }
        }
        if (found) {
            break;
        }
    }
}

void EmptyHints(char hints2[][MAX_HINT_LENGTH], int n, int* index) {
    for (int i = 0; i < n; i++) {
        hints2[i][0] = '\0';
        index[i] = -1;
    }
    HintCounter = 0;
}

void HintsDisplayer(char hints2[][MAX_HINT_LENGTH], int* index) {
    setColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("HINTS : \n");
    resetColor();
    for (int i = 0; i < HintCounter; i++) {
        if (index[i] != -1) {
            setColor(FOREGROUND_BLACK | FOREGROUND_INTENSITY);
            printf("%d. %s\n", i + 1, hints2[i]);
            resetColor();
        } else {
            printf("%d. %s\n", i + 1, hints2[i]);
        }
    }
}

void EmptyGrid(char GRID[GRID_SIZE][GRID_SIZE], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            GRID[i][j] = ' ';
        }
    }
}