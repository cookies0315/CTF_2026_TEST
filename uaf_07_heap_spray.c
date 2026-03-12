#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPRAY_SIZE 1000

int main() {
    char *ptrs[SPRAY_SIZE];
    
    printf("uaf_07: Heap Spray\n");
    
    for (int i = 0; i < SPRAY_SIZE; i++) {
        ptrs[i] = (char *)malloc(256);
        memset(ptrs[i], 'A', 256);
        ptrs[i][255] = '\0';
    }
    
    printf("Sprayed %d allocations\n", SPRAY_SIZE);
    
    for (int i = 0; i < SPRAY_SIZE; i++) {
        free(ptrs[i]);
    }
    
    char *target = (char *)malloc(256);
    printf("New allocation after spray: %p\n", (void*)target);
    printf("First few bytes: %.10s\n", target);
    
    return 0;
}
