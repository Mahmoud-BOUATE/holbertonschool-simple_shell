#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    pid_t pid;
    int status;

    while (1)
    {
        printf("($) ");               // Affiche le prompt
        if (getline(&line, &len, stdin) == -1) // Ctrl+D ou erreur
            break;

        line[strcspn(line, "\n")] = '\0'; // Supprime le \n

        pid = fork();                  // Crée un processus enfant
        if (pid == 0)                  // Enfant
        {
            execve(line, NULL, environ);
            fprintf(stderr, "%s: not found\n", line); // Si execve échoue
            exit(1);
        }
        else if (pid > 0)              // Parent
        {
            wait(&status);             // Attend que l’enfant termine
        }
        else
        {
            perror("fork");
            exit(1);
        }
    }

    free(line);
    return 0;
}
