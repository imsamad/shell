#include <stdio.h>
#include <unistd.h>

int main() {
    char *args[] = {"mkdir", "hello", NULL};  // Arguments to pass to ls
    if (execvp(args[0], args) == -1) {        // Execute ls with arguments
        perror("execvp failed");              // If execvp fails, print error
    }
    return 0;
}
