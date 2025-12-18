#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int handle_exit(char **argv)
{
    if (argv[0])
    {
        // Supprimer le '\n' si présent à la fin
        size_t len = strlen(argv[0]);
        if (len > 0 && argv[0][len - 1] == '\n')
            argv[0][len - 1] = '\0';

        if (strcmp(argv[0], "exit") == 0)
            exit(0);
    }
    return 0;
}