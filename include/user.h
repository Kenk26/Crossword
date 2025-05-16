#ifndef USER_H
#define USER_H

#include "library.h"

typedef struct User {
    char name[MAX_USERS][MAX_NAME_LENGTH];
    float time_u[MAX_USERS];
    int points[MAX_USERS];
    int size_u;
} User;

// User functions
void initUser(User* u);
void insert_min_user(User* u, float value, const char* str);
void heapify_min(User* u, int index, int num);
void user_min_sort(User* u, int n);
void print_score(User* u);

#endif