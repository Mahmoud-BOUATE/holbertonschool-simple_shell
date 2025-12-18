#include "shell.h"

char *find_in_path(char *command)
{
    static char full_path[1024];
    int i;
    char *path_env;
    char *paths[256];
    char *token;
    char *path_copy;

    if (strchr(command, '/'))
    {
        if (access(command, X_OK) == 0)
            return command;
        return NULL;
    }

    path_env = NULL;
    for (i = 0; environ[i]; i++)
    {
        if (strncmp(environ[i], "PATH=", 5) == 0)
        {
            path_env = environ[i] + 5;
            break;
        }
    }

    if (!path_env || path_env[0] == '\0')
        return NULL;

    path_copy = strdup(path_env);
    if (!path_copy)
        return NULL;

    i = 0;
    token = strtok(path_copy, ":");
    while (token && i < 255)
    {
        paths[i++] = token;
        token = strtok(NULL, ":");
    }
    paths[i] = NULL;

    for (i = 0; paths[i]; i++)
    {
        snprintf(full_path, sizeof(full_path), "%s/%s", paths[i], command);
        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return full_path;
        }
    }

    free(path_copy);
    return NULL;
}
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
        /* on fixe le code de sortie à 127 si commande non trouvée */
        exit(127);
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
        if (WIFEXITED(status))
            exit(WEXITSTATUS(status));
    }
}