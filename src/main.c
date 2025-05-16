#include "library.h"
#include "trie.h"
#include "user.h"
#include "grid.h"
#include "database.h"
#include "menu.h"
#include "game.h"
#include "admin.h"

int main() {
    WordDatabase db;
    loadWordDatabase(&db);
    
    User u;
    initUser(&u);

    int choice;
    srand(time(NULL));

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                playGame(&db, &u);
                break;
            case 2:
                if(verifyAdminCredentials())
                    addNewWord(&db);
                break;
            case 3:
                print_score(&u);
                break;
            case 4:
                printf("\nThank you for playing!\n");
                exit(0);
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }

    return 0;
}