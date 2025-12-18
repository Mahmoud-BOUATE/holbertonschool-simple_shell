#include <stdlib.h>
#include <string.h>

/**
 * handle_exit - gère la commande exit
 * @argv: tableau d'arguments
 *
 * Si argv[0] est "exit", quitte le shell avec code 0.
 * Retourne 0 sinon.
 */
int handle_exit(char **argv)
{
    if (argv[0] && strcmp(argv[0], "exit") == 0)
        exit(0);  /* termine le shell proprement */
    return 0;
}