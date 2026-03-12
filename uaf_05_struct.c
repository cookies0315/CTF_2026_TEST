#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct User {
    char username[32];
    char password[32];
    int is_admin;
};

int main() {
    struct User *user = (struct User *)malloc(sizeof(struct User));
    
    printf("uaf_05: Struct UAF\n");
    
    strcpy(user->username, "admin");
    strcpy(user->password, "password123");
    user->is_admin = 0;
    
    printf("Before free: is_admin = %d\n", user->is_admin);
    
    free(user);
    
    printf("After free (UAF): is_admin = %d\n", user->is_admin);
    
    return 0;
}
