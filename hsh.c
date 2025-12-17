#include "shell.h"

int main(void)
{
    char *line = NULL;
    char *line_trimmed;
    char *argv[MAX_TOKENS];
    size_t len = 0;
    int interactive;

    interactive = isatty(STDIN_FILENO);

    while (1)
    {
        print_prompt(interactive);

        if (read_input(&line, &len, interactive) == -1)
            break;

        line_trimmed = trim(line);
        if (*line_trimmed == '\0')
            continue;

        split_line(line_trimmed, argv);
        execute_command(argv);
    }

    free(line);
    return 0;
}
