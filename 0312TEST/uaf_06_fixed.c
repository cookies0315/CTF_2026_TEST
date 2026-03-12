#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *ptr = (char *)malloc(100);
    
    printf("uaf_06: Fixed (Safe Example)\n");
    
    strcpy(ptr, "Hello World");
    printf("Before free: %s\n", ptr);
    
    free(ptr);
    ptr = NULL;
    
    if (ptr != NULL) {
        printf("After free: %s\n", ptr);
    } else {
        printf("Pointer is NULL, safe!\n");
    }
    
    return 0;
}
