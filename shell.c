#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAX_CMD_LEN 1024

int main(void) {
    char command[MAX_CMD_LEN];
    int status;
    pid_t child_pid;

    while (1) {
        printf("#cisfun$ ");
        fflush(stdout);

        if (fgets(command, MAX_CMD_LEN, stdin) == NULL) {
            if (feof(stdin)) {
                printf("\n");  // Add a newline on Ctrl+D (EOF)
                break;         // Exit the loop
            }
            perror("Error reading input");
            exit(EXIT_FAILURE);
        }

        // Remove trailing newline character from the input
        command[strcspn(command, "\n")] = 0; 

        child_pid = fork();
        if (child_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (child_pid == 0) {
            // Child process
            char *argv[] = {command, NULL};
            if (execve(command, argv, NULL) == -1) {
                perror(command); // Use argv[0] (the command name) in the error message
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            wait(&status);
        }
    }
    return 0;
}
