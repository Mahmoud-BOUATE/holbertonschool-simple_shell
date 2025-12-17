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

/* Recherche la commande dans un PATH fixe (sans getenv) */
char *find_in_path(char *command)
{
    static char full_path[1024];
    char *paths[] = {"/bin", "/usr/bin", NULL};
    int i;

    /* Si la commande contient un /, tester directement */
    if (strchr(command, '/'))
    {
        if (access(command, X_OK) == 0)
            return command;
        return NULL;
    }

    /* Parcours des dossiers standards */
    for (i = 0; paths[i]; i++)
    {
        snprintf(full_path, sizeof(full_path), "%s/%s", paths[i], command);
        if (access(full_path, X_OK) == 0)
            return full_path;
    }

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
