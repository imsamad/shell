#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define INPUT_BUFFER 1 << 10
#define DELIMITER " \t\n\r\a"

char * read_cmd() {

    char *cmd = NULL;
    size_t buff_size = 0;

    if (getline(&cmd, &buff_size, stdin) == -1) {
        if (feof(stdin)) {
            exit(EXIT_SUCCESS);
        } else {
            perror("realine");
            exit(EXIT_FAILURE);
        }
    }
    return  cmd;
}

char **split_line(char *line) {

    if (strlen(line) == 0) {
        printf("empty commands \n");
        exit(EXIT_FAILURE);
    }

    unsigned int args_count = 100;
    char **args = malloc(args_count * sizeof(char*));

    if (!args) {
        printf("allocation error");
        exit(EXIT_FAILURE);
    }

    char *token = strtok(line, DELIMITER);
    int i = 0;

    while (token != NULL) {
        // printf("token: %s \n",token );
        args[i++] = token;
        token = strtok(NULL, DELIMITER);

        if (i >= args_count) {
            if (i > UINT_MAX - 100) {
                printf("overflow");
                exit(EXIT_FAILURE);
            }

            args_count += 100;
            args = realloc(args, args_count * sizeof(char*));

            if (!args) {
                printf("overflow");
                exit(EXIT_FAILURE);
            }
        }
    }

    args[i] = NULL;

    return args;
}

int run_cmd(char **args) {
    pid_t child_pid = fork();

    if (child_pid == 0) {

        // sleep(5);
        if (execvp(args[0], args) == -1) {
            perror("");
        }
        exit(EXIT_FAILURE);

    } else if (child_pid == -1) {
        perror("error forking");
    } else {
        int status;
        do {
            waitpid(child_pid, &status, WUNTRACED);
        } while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

int main() {
    while(1) {
        char *cmd = read_cmd();

        char **args = split_line(cmd);
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        run_cmd(args);
    }

    return EXIT_SUCCESS;
}
