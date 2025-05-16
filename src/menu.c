#include "menu.h"

void displayMenu() {
    setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("\n\n\t\tCROSSWORD PUZZLE GAME\n");
    printf("\t\t=====================\n\n");
    resetColor();
    printf("1. Play Game\n");
    printf("2. Add New Word and Hint\n");
    printf("3. View Scores\n");
    printf("4. Exit\n\n");
    printf("Enter your choice: ");
}