#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#define PROMPT "#cisfun$ "
#define MAX_INPUT 1024

int main(void) {
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while (1) {
        // Afficher le prompt
        printf("%s", PROMPT);
        fflush(stdout);

        // Lire la ligne de commande
        nread = getline(&line, &len, stdin);
        if (nread == -1) { // Ctrl+D ou erreur
            printf("\n");
            break;
        }

        // Supprimer le \n final
        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        // Ignorer les lignes vides
        if (strlen(line) == 0)
            continue;

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            continue;
        } else if (pid == 0) { // Processus enfant
            char *argv[] = {line, NULL};
            if (execve(line, argv, environ) == -1) {
                fprintf(stderr, "%s: No such file or directory\n", line);
                exit(EXIT_FAILURE);
            }
        } else { // Processus parent
            int status;
            waitpid(pid, &status, 0);
        }
    }

    free(line);
    return 0;
}
