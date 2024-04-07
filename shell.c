#include "shell.h"

void execute_command(char *command) {
    char *args[2];
    pid_t child_pid;
    int stat_loc;

    args[0] = command;
    args[1] = NULL;

    child_pid = fork();
    if (child_pid == -1) {
        perror("Fork failed");
        exit(1);
    } else if (child_pid == 0) {
        if (execve(args[0], args, NULL) == -1) {
            perror("Command not found");
            exit(1);
        }
    } else {
        waitpid(child_pid, &stat_loc, 0);
    }
}

int main() {
    char line[256];

    while (1) {
        printf("%s", PROMPT);
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\n");
            break;
        }

        line[strcspn(line, "\n")] = '\0';
        execute_command(line);
    }

    return 0;
}
