#include "admin.h"

bool verifyAdminCredentials() {
    char username[MAX_WORD_LENGTH];
    char password[MAX_WORD_LENGTH];
    int attempts = 0;
    const int MAX_ATTEMPTS = 3;
    
    while (attempts < MAX_ATTEMPTS) {
        system("cls");
        printf("\nAdmin Authentication Required\n");
        printf("==========================\n");
        printf("Username: ");
        scanf("%s", username);
        
        printf("Password: ");
        scanf("%s", password);
        
        if (strcmp(username, ADMIN_USERNAME) == 0 && 
            strcmp(password, ADMIN_PASSWORD) == 0) {
            printf("\nAuthentication successful!\n");
            return true;
        } else {
            attempts++;
            printf("\nInvalid credentials. %d attempts remaining.\n", 
                   MAX_ATTEMPTS - attempts);
        }
        getch();
    }
    
    printf("\nToo many failed attempts. Access denied.\n");
    return false;
}