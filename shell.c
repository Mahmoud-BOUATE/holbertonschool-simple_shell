#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

#define PROMPT "#cisfun$ "
#define MAX_TOKENS 64

/* Trim espaces début et fin */
char *trim(char *str)
{
    char *end;

    while (*str == ' ' || *str == '\t')
        str++;

    if (*str == 0)
        return str;

    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t'))
        end--;

    *(end + 1) = '\0';
    return str;
}

/* Découpe la ligne en arguments */
void split_line(char *line, char **argv)
{
    int i = 0;
    char *token;

    token = strtok(line, " \t");
    while (token != NULL && i < MAX_TOKENS - 1)
    {
        argv[i++] = token;
        token = strtok(NULL, " \t");
    }
    argv[i] = NULL;
}

int main(void)
{
    char *line = NULL;
    char *line_trimmed;
    char *argv[MAX_TOKENS];
    size_t len = 0;
    ssize_t nread;
    pid_t pid;
    int status;
    int interactive;

    interactive = isatty(STDIN_FILENO);

    while (1)
    {
        if (interactive)
        {
            printf("%s", PROMPT);
            fflush(stdout);
        }

        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            if (interactive)
                printf("\n");
            break;
        }

        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        line_trimmed = trim(line);
        if (*line_trimmed == '\0')
            continue;

        split_line(line_trimmed, argv);

        pid = fork();
        if (pid == -1)
            continue;

        if (pid == 0)
        {
            if (execve(argv[0], argv, environ) == -1)
            {
                fprintf(stderr, "%s: No such file or directory\n", argv[0]);
                exit(1);
            }
        }
        else
        {
            waitpid(pid, &status, 0);
        }
    }

    free(line);
    return 0;
}
