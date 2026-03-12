#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_dangling_pointer() {
    char *ptr = (char *)malloc(100);
    strcpy(ptr, "Temporary data");
    return ptr;
}

int main() {
    char *ptr;
    
    printf("uaf_04: Dangling Pointer\n");
    
    ptr = create_dangling_pointer();
    printf("Before function returns: %s\n", ptr);
    
    printf("After function returns (dangling): %s\n", ptr);
    
    return 0;
}
