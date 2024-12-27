#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Hello, world! Welcome to C programming.";
    const char delim[] = " ,!.";

    char *token = strtok(str, delim);
    printf("Delim: %s\n", delim);

    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok(NULL, delim); // Continue tokenizing
    }

    return 0;
}
