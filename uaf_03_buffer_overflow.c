#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char buffer[32];
    
    printf("uaf_03: Buffer Overflow\n");
    printf("Enter input (no bounds check): ");
    
    fgets(buffer, sizeof(buffer), stdin);
    
    printf("You entered: %s\n", buffer);
    
    return 0;
}
