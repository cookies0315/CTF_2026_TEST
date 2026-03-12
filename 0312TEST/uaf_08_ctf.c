#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct User {
    char username[32];
    char password[32];
    int is_admin;
};

struct User *current_user = NULL;

void menu() {
    printf("\n=== Menu ===\n");
    printf("1. Register new account\n");
    printf("2. Login\n");
    printf("3. View Profile\n");
    printf("4. Admin Panel\n");
    printf("5. Delete Account\n");
    printf("6. Secret Admin Upgrade\n");
    printf("7. Debug Info\n");
    printf("8. Exit\n");
    printf("Choice: ");
}

void register_account() {
    current_user = (struct User *)malloc(sizeof(struct User));
    printf("Username: ");
    scanf("%32s", current_user->username);
    printf("Password: ");
    scanf("%32s", current_user->password);
    current_user->is_admin = 0;
    printf("Account registered!\n");
}

void login() {
    if (current_user == NULL) {
        printf("No account registered!\n");
        return;
    }
    char username[32], password[32];
    printf("Username: ");
    scanf("%32s", username);
    printf("Password: ");
    scanf("%32s", password);
    
    if (strcmp(username, current_user->username) == 0 &&
        strcmp(password, current_user->password) == 0) {
        printf("Login successful!\n");
    } else {
        printf("Login failed!\n");
    }
}

void view_profile() {
    if (current_user == NULL) {
        printf("No account!\n");
        return;
    }
    printf("Username: %s\n", current_user->username);
    printf("Password: %s\n", current_user->password);
    printf("Admin: %s\n", current_user->is_admin ? "Yes" : "No");
}

void admin_panel() {
    if (current_user == NULL) {
        printf("No account!\n");
        return;
    }
    if (current_user->is_admin) {
        printf("=== ADMIN PANEL ===\n");
        printf("FLAG: FLAG{U4f_3xp10t_5ucc3ssful}\n");
        printf("====================\n");
    } else {
        printf("Access denied! Admin only.\n");
    }
}

void delete_account() {
    if (current_user == NULL) {
        printf("No account!\n");
        return;
    }
    free(current_user);
    current_user = NULL;
    printf("Account deleted!\n");
}

void admin_upgrade() {
    if (current_user == NULL) {
        printf("No account!\n");
        return;
    }
    current_user->is_admin = 1;
    printf("Upgraded to admin!\n");
}

void debug_info() {
    printf("Debug: current_user = %p\n", (void*)current_user);
    if (current_user != NULL) {
        printf("Debug: username = %s\n", current_user->username);
        printf("Debug: is_admin = %d\n", current_user->is_admin);
    }
}

int main() {
    int choice;
    
    printf("=== UAF CTF Challenge ===\n");
    
    while (1) {
        menu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: register_account(); break;
            case 2: login(); break;
            case 3: view_profile(); break;
            case 4: admin_panel(); break;
            case 5: delete_account(); break;
            case 6: admin_upgrade(); break;
            case 7: debug_info(); break;
            case 8: 
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}
