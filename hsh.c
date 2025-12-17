#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

// Supprime les espaces en début et fin de chaîne
char *trim(char *str) {
    while(*str == ' ' || *str == '\t') str++;
    if(*str == 0) return str;
    char *end = str + strlen(str) - 1;
    while(end > str && (*end == ' ' || *end == '\t' || *end == '\n')) end--;
    *(end+1) = 0;
    return str;
}

// Découpe la ligne en arguments
int parse_line(char *line, char **args) {
    int count = 0;
    char *token = strtok(line, " \t\n");
    while(token != NULL && count < MAX_ARGS - 1) {
        args[count++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[count] = NULL;
    return count;
}

int main() {
    char line[MAX_LINE];
    char *args[MAX_ARGS];
    char *path_env = getenv("PATH");
    if(!path_env) path_env = "/bin:/usr/bin";

    while(fgets(line, sizeof(line), stdin)) {
        char *cmd = trim(line);
        if(strlen(cmd) == 0) continue;
        int argc = parse_line(cmd, args);
        if(argc == 0) continue;

        pid_t pid = fork();
        if(pid == 0) {
            execvp(args[0], args);
            perror("execvp");
            exit(1);
        } else if(pid > 0) {
            int status;
            waitpid(pid, &status, 0);
        } else {
            perror("fork");
        }
    }
    return 0;
}
