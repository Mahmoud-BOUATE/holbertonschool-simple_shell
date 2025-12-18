#include "shell.h"

void print_prompt(int interactive)
{
    if (interactive)
        write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}

ssize_t read_input(char **line, size_t *len, int interactive)
{
    ssize_t nread = getline(line, len, stdin);

    if (nread == -1)
    {
        if (interactive)
            write(STDOUT_FILENO, "\n", 1);
        return -1;
    }

    if ((*line)[nread - 1] == '\n')
        (*line)[nread - 1] = '\0';

    return nread;
}

char *trim(char *str)
{
    char *end;

    while (*str == ' ' || *str == '\t')
        str++;

    if (*str == '\0')
        return str;

    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t'))
        end--;

    *(end + 1) = '\0';
    return str;
}

void split_line(char *line, char **argv)
{
    int i = 0;
    char *token = strtok(line, " \t");

    while (token && i < MAX_TOKENS - 1)
    {
        argv[i++] = token;
        token = strtok(NULL, " \t");
    }
    argv[i] = NULL;
}
