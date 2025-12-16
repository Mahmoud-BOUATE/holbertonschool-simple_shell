#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

extern char **environ;

#define PROMPT "#cisfun$ "
#define MAX_INPUT 1024

/* Fonction pour enlever les espaces en début et fin */
char *trim(char *str)
{
    char *end;

    /* Supprimer les espaces de début */
    while (*str == ' ' || *str == '\t')
        str++;

    if (*str == 0) /* chaîne vide */
        return str;

    /* Supprimer les espaces de fin */
    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t'))
        end--;

    *(end + 1) = '\0';
    return str;
}

int main(void)
{
    char *line = NULL;
    char *line_trimmed;
    size_t len = 0;
    ssize_t nread;
    int status;
    pid_t pid;
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
        if (nread == -1) /* Ctrl+D ou erreur */
        {
            if (interactive)
                printf("\n");
            break;
        }

        /* Supprimer le \n final */
        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        /* Trim des espaces */
        line_trimmed = trim(line);

        /* Ignorer les lignes vides */
        if (strlen(line_trimmed) == 0)
            continue;

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            continue;
        }
        else if (pid == 0)
        {
            char *argv[2];
            argv[0] = line_trimmed;
            argv[1] = NULL;

            if (execve(line_trimmed, argv, environ) == -1)
            {
                fprintf(stderr, "%s: No such file or directory\n", line_trimmed);
                exit(EXIT_FAILURE);
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
