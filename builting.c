#include "shell.h"

/* Implémentation du built-in exit */
int handle_exit(char **argv)
{
    if (argv[0] && strcmp(argv[0], "exit") == 0)
        return 1;  /* retourne 1 pour signaler la sortie */
    return 0;
}

/* Implémentation du built-in env */
int handle_env(char **argv)
{
    int i;

    if (argv[0] && strcmp(argv[0], "env") == 0)
    {
        for (i = 0; environ[i]; i++)
            printf("%s\n", environ[i]);
        return 1;  /* commande traitée */
    }
    return 0;
}
