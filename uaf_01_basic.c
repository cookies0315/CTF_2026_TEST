#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void winner() {
    printf("Congratulations! You triggered the UAF vulnerability!\n");
}

int main() {
    char *ptr = (char *)malloc(100);
    
    printf("uaf_01: Basic UAF\n");
    printf("Address of ptr: %p\n", (void*)&ptr);
    printf("Address of allocated memory: %p\n", (void*)ptr);
    
    strcpy(ptr, "Hello World");
    printf("Before free: %s\n", ptr);
    
    free(ptr);
    
    printf("After free (UAF): %s\n", ptr);
    
    return 0;
}
