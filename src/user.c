#include "user.h"

void initUser(User* u) {
    u->size_u = 0;
    u->time_u[0] = -1;
    u->points[0] = 1000;
}

void insert_min_user(User* u, float value, const char* str) {
    u->size_u = u->size_u + 1;
    int i = u->size_u;
    strcpy(u->name[i], str);
    u->time_u[i] = value;
    
    u->points[i] = 1000;
    if (value > 60) {
        u->points[i] -= 2 * (int)(value - 60);
        if (u->points[i] < 0) u->points[i] = 0;
    }

    while (i > 1) {
        int temp = i / 2;
        if (u->time_u[temp] > u->time_u[i]) {
            // Swap time
            float tempFloat = u->time_u[temp];
            u->time_u[temp] = u->time_u[i];
            u->time_u[i] = tempFloat;
            
            // Swap name
            char tempName[MAX_NAME_LENGTH];
            strcpy(tempName, u->name[temp]);
            strcpy(u->name[temp], u->name[i]);
            strcpy(u->name[i], tempName);
            
            // Swap points
            int tempPoints = u->points[temp];
            u->points[temp] = u->points[i];
            u->points[i] = tempPoints;

            i = temp;
        } else {
            return;
        }
    }
}

void heapify_min(User* u, int index, int num) {
    int large = index;
    int left = 2 * index;
    int right = 2 * index + 1;

    if (left <= num && u->time_u[large] < u->time_u[left]) {
        large = left;
    }
    if (right <= num && u->time_u[large] < u->time_u[right]) {
        large = right;
    }

    if (large != index) {
        // Swap time
        float tempFloat = u->time_u[large];
        u->time_u[large] = u->time_u[index];
        u->time_u[index] = tempFloat;

        // Swap name
        char tempName[MAX_NAME_LENGTH];
        strcpy(tempName, u->name[large]);
        strcpy(u->name[large], u->name[index]);
        strcpy(u->name[index], tempName);
        
        // Swap points
        int tempPoints = u->points[large];
        u->points[large] = u->points[index];
        u->points[index] = tempPoints;

        heapify_min(u, large, num);
    }
}

void user_min_sort(User* u, int n) {
    while (n > 1) {
        // Swap time
        float tempFloat = u->time_u[1];
        u->time_u[1] = u->time_u[n];
        u->time_u[n] = tempFloat;

        // Swap name
        char tempName[MAX_NAME_LENGTH];
        strcpy(tempName, u->name[1]);
        strcpy(u->name[1], u->name[n]);
        strcpy(u->name[n], tempName);
        
        // Swap points
        int tempPoints = u->points[1];
        u->points[1] = u->points[n];
        u->points[n] = tempPoints;

        n--;
        heapify_min(u, 1, n);
    }
}

void print_score(User* u) {
    system("cls");
    setColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\n\n\t\t*SCORE CARD\t\t\n\n");
    resetColor();
    printf("Names\t\tTime\t\tPoints\n\n");

    for (int i = 1; i <= u->size_u; i++) {
        printf("%s\t\t%.2f sec\t%d\n", u->name[i], u->time_u[i], u->points[i]);
    }
    printf("\n");
}