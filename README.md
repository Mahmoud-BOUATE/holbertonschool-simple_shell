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

The shell reads user commands, checks for built-in commands (`exit`, `env`), searches for executables in the PATH environment variable, creates a child process using `fork()`, executes the command with `execve()`, and waits for the process to finish with `waitpid()`.

It also handles end-of-file (Ctrl+D) and basic error reporting like the standard shell.

## Features
- Executes commands with absolute and relative paths.
- Supports basic shell features: PATH resolution, built-in commands like `exit` and `env`.
- Works in interactive and non-interactive modes.
- Handles end-of-file (Ctrl+D) gracefully.
- Error handling similar to `/bin/sh`.
- Uses system calls efficiently (`fork`, `execve`, `waitpid`).

## Files description

| File | Description |
|------|-------------|
| `main.c` | Main loop of the shell: reads input, handles built-ins, executes commands, and manages the program flow. |
| `helpers.c` | Utility functions: print prompt, read input, trim spaces, split input line into arguments. |
| `executes.c` | Handles finding commands in PATH and executing them using `fork` + `execve`. Waits for the process to finish. |
| `builtins.c` | Implements the built-in commands `exit` and `env`. |
| `shell.h` | Header file: function prototypes, macros, and declaration of the global `environ` variable. |
| `README.md` | Project documentation and instructions. |
| `man_1_simple_shell` | Manual page describing usage, built-ins, and exit status. |

## Usage
### Interactive mode
```bash
$ ./hsh
($) /bin/ls
hsh main.c shell.c helpers.c executes.c builtins.c shell.h
($) exit
```

### Non-Interactive mode
```bash
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c helpers.c executes.c builtins.c shell.h
```
## Compilation
```bash
$ gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

# holbertonschool-chatgpt-introduction
