#include <stdio.h>
#include <string.h>

int main() {
    char line[255] = "Hello World";
    size_t size = sizeof(line);
    size_t len = strlen(line); // length of string (not including the null terminator character) -> returns 11 but is really 12
    // '\0'
    printf("Line size: %zu\n", size);
    printf("Line length: %zu\n", len);
    return 0;
}
