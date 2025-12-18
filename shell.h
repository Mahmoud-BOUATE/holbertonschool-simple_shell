#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define PROMPT "$ "
#define MAX_TOKENS 64

extern char **environ;

/* helpers.c */
char *trim(char *str);
void split_line(char *line, char **argv);
ssize_t read_input(char **line, size_t *len, int interactive);
void print_prompt(int interactive);

/* execute.c */
int execute_command(char **argv);
char *find_in_path(char *command);

/* builtins.c */
int handle_exit(char **argv);
int handle_env(char **argv);

#endif
