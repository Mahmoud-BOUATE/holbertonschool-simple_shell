
#include <stdlib.h>
#include <string.h>

/* built-in exit */
int handle_exit(char **argv)
{
    if (argv[0] && strcmp(argv[0], "exit") == 0)
        exit(0);  /* quitte immédiatement le shell avec status 0 */
    return 0;     /* sinon rien */
}
