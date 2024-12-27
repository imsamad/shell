#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define MAX_ARGS 100

#define DELIMITER " \t\n\r\a"

int main() {


    while (1) {
        char *input = NULL;
        size_t len = 0;

        printf("shell> "); // Shell prompt
        if (getline(&input, &len, stdin) == -1) {
            perror("getline failed");
            free(input);
            break;
        }

        // Remove trailing newline
        if (input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        }

        // Exit shell on empty input or "exit"
        if (strlen(input) == 0 || strcmp(input, "exit") == 0) {
            free(input);
            break;
        }

        // Tokenize input
        char *args[MAX_ARGS];
        int i = 0;
        args[i] = strtok(input, DELIMITER);

        while (args[i] != NULL && i < MAX_ARGS - 1) {
            args[++i] = strtok(NULL, DELIMITER);
        }
        args[i] = NULL; // Null-terminate arguments array

        // Debugging: Print tokens
        for (int j = 0; args[j] != NULL; j++) {
            printf("args[%d]: '%s'\n", j, args[j]);
        }

        // Fork and execute command
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            if (execvp(args[0], args) == -1) {
                perror("Error executing command");
            }
            exit(EXIT_SUCCESS);
        } else if (pid < 0) {
            // Fork failed
            perror("Error forking process");
        } else {
            // Parent process: wait for child
            int status;
            do {
                waitpid(pid, &status, WUNTRACED);
                printf("WIFSIGNALED(status): %d \n", WIFSIGNALED(status));
                printf("WIFEXITED(status): %d \n", WIFEXITED(status));
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));

            printf("WIFSIGNALED(status): %d \n", WIFSIGNALED(status));
            printf("WIFEXITED(status): %d \n", WIFEXITED(status));
        }

        free(input); // Free allocated input
    }

    return 0;
}
