#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *ptr1 = (char *)malloc(100);
    char *ptr2 = (char *)malloc(100);
    
    printf("uaf_02: Double Free\n");
    printf("ptr1: %p\n", (void*)ptr1);
    printf("ptr2: %p\n", (void*)ptr2);
    
    strcpy(ptr1, "First allocation");
    strcpy(ptr2, "Second allocation");
    
    printf("Before double free:\n");
    printf("ptr1: %s\n", ptr1);
    printf("ptr2: %s\n", ptr2);
    
    free(ptr1);
    printf("After first free(ptr1)\n");
    
    free(ptr1);
    printf("After second free(ptr1) - DOUBLE FREE!\n");
    
    return 0;
}
