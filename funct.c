#include "shell.h"

/* Affiche le prompt */
void print_prompt(int interactive)
{
    if (interactive)
        write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}

/* Lecture de l'entrée utilisateur */
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

/* Supprime espaces début et fin */
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

/* Découpe la ligne en arguments */
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

/* Recherche la commande dans le PATH */
char *find_in_path(char *command)
{
    char *path, *path_copy, *dir;
    static char full_path[1024];

    if (strchr(command, '/'))
    {
        if (access(command, X_OK) == 0)
            return command;
        return NULL;
    }

    path = getenv("PATH");
    if (!path)
        return NULL;

    path_copy = strdup(path);
    if (!path_copy)
        return NULL;

    dir = strtok(path_copy, ":");
    while (dir)
    {
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return full_path;
        }
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}

/* Exécution de la commande */
void execute_command(char **argv)
{
    pid_t pid;
    int status;
    char *cmd_path;

    if (!argv[0])
        return;

    cmd_path = find_in_path(argv[0]);
    if (!cmd_path)
    {
        fprintf(stderr, "%s: not found\n", argv[0]);
        return; /* PAS DE fork si commande introuvable */
    }

    pid = fork();
    if (pid == -1)
        return;

    if (pid == 0)
    {
        execve(cmd_path, argv, environ);
        perror(argv[0]);
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(pid, &status, 0);
    }
}
