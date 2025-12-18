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

/* Recherche la commande dans PATH via environ */
char *find_in_path(char *command)
{
    static char full_path[1024];
    char *path_env, *path_copy, *token;
    int i;

    if (strchr(command, '/'))
        return (access(command, X_OK) == 0) ? command : NULL;

    path_env = getenv("PATH");
    if (!path_env || path_env[0] == '\0')
        return NULL;

    path_copy = strdup(path_env);
    if (!path_copy)
        return NULL;

    token = strtok(path_copy, ":");
    while (token)
    {
        snprintf(full_path, sizeof(full_path), "%s/%s", token, command);
        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return full_path;
        }
        token = strtok(NULL, ":");
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
        fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
        return;
    }

    pid = fork();
    if (pid == -1)
        return;

    if (pid == 0)
    {
        execve(cmd_path, argv, environ);
        perror(argv[0]);
        _exit(127);
    }
    else
    {
        waitpid(pid, &status, 0);
    }
}
