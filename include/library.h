#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>

// Constants
#define FOREGROUND_BLACK       0x00
#define GRID_SIZE 22
#define numWords 6
#define MAX_WORD_LENGTH 20
#define MAX_HINT_LENGTH 100
#define MAX_NAME_LENGTH 50
#define MAX_USERS 101
#define ALPHABET_SIZE 26
#define MAX_WORDS 200
#define WORDS_FILE "crossword_words.txt"
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin"

// Color functions
void setColor(int colorCode);
void resetColor();
extern int HintCounter;

#endif