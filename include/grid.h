#ifndef GRID_H
#define GRID_H

#include "library.h"

// Grid functions
void printGrid(char grid[GRID_SIZE][GRID_SIZE]);
void CopyGrid(char grid[GRID_SIZE][GRID_SIZE], char grid2[GRID_SIZE][GRID_SIZE]);
bool CompareGrids(char grid[GRID_SIZE][GRID_SIZE], char grid2[GRID_SIZE][GRID_SIZE]);
bool isValid(int row, int col);
bool HorizontalUpdate(char grid[][GRID_SIZE], const char* str, char grid2[][GRID_SIZE], int row, int col, int index);
bool VerticalUpdate(char grid[][GRID_SIZE], const char* str, char grid2[][GRID_SIZE], int row, int col, int index);
bool HorizontalVerticalUpdate(char grid[][GRID_SIZE], const char* str, char grid2[][GRID_SIZE], int row, int col, int index);
void updateDisplayGrid(char grid[GRID_SIZE][GRID_SIZE], char grid2[GRID_SIZE][GRID_SIZE], const char* str);
void EmptyHints(char hints2[][MAX_HINT_LENGTH], int n, int* index);
void HintsDisplayer(char hints2[][MAX_HINT_LENGTH], int* index);
void EmptyGrid(char GRID[GRID_SIZE][GRID_SIZE], int n);

#endif