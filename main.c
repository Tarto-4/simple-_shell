#include "shell.h"
/**
 * main - the main function of the shell
 *
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
    char line[256];

    while (1)
    {
        printf("%s", PROMPT);
        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            printf("\n");
            break;
        }

        line[strcspn(line, "\n")] = '\0';
        execute_command(line);
    }

    return 0;
}
