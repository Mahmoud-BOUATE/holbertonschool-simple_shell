/* task_5.c */
/* Implémente le built-in exit pour Simple Shell 0.4 */

#include <stdlib.h>
#include <string.h>

/**
 * handle_exit - gère la commande exit
 * @argv: tableau d'arguments
 *
 * Si argv[0] est "exit", quitte le shell.
 */
int handle_exit(char **argv)
{
    if (argv[0] && strcmp(argv[0], "exit") == 0)
        exit(0);
    return 0;
}
