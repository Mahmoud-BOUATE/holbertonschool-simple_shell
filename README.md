<h1 align="center"># Simple Shell Project</h1>

## Table of contents
- Description
- Features
- Files description
- Usage
- Compilation
- Allowed Functions
- Author

## Description
`simple_shell` is a simple Unix command line interpreter (shell) written in C.
It replicates the behavior of the standard Unix shell (`/bin/sh`) and allows users to execute commands, handle simple shell features, and work in both interactive and non-interactive modes.

## Features
- Executes commands with absolute and relative paths.
- Supports basic shell features: PATH resolution, built-in commands like `exit`.
- Works in interactive and non-interactive modes.
- Error handling similar to `/bin/sh`.

## Files description



## Usage
### Interactive mode
```bash
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($) exit
```

### Non-Interactive mode
```bash
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
```

## Complilation
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

## Allowed Functions
access, chdir, close, closedir, execve, exit, _exit, fflush, fork, free, getcwd, getline, getpid, isatty, kill, malloc, open, opendir, perror, printf, fprintf, vfprintf, sprintf, putchar, read, readdir, signal, stat, lstat, fstat, strtok, wait, waitpid, wait3, wait4, write.

# Author
BOUATE Mahmoud

