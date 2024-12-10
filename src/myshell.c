#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"

#define BUFFER_SIZE 1024

void parse_and_execute(char *input) {
    char *args[BUFFER_SIZE];
    int i = 0;

    char *token = strtok(input, " \t\n");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;

    if (args[0] == NULL) {
        return;
    }

    if (strcmp(args[0], "cd") == 0) {
        execute_cd(args);
    } else if (strcmp(args[0], "pwd") == 0) {
        execute_pwd();
    } else if (strcmp(args[0], "ls") == 0) {
        execute_ls(args);
    } else if (strcmp(args[0], "cat") == 0) {
        execute_cat(args);
    } else if (strcmp(args[0], "exit") == 0) {
        printf("Exiting myshell.\n");
        exit(0);
    } else {
        fprintf(stderr, "%s: command not found\n", args[0]);
    }
}

int main() {
    char input[BUFFER_SIZE];

    while (1) {
        printf("myshell> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        parse_and_execute(input);
    }

    return 0;
}
