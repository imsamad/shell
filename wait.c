#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child process: %d is running. \n",getpid());
        sleep(2);
        printf("Child process exited \n");
        exit(2);
    } else {
        while(1) {
            int status = 0;
            pid_t child_pid = waitpid(pid, &status, WNOHANG);

            if (child_pid == 0){
                // printf("waiting for child");
            } else if (child_pid == -1) {
                perror("waitpid");
                printf("waiting for child but error");
                break;
                } else {
                int tmp = status >> 8;

                printf("tmp: %d \n",tmp);
                printf("status: %d \n",status);
                printf("wifexited(status): %d \n", WIFEXITED(status));
                break;

            }
        }

    }
    return  0;
}
