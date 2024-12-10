#include <stdio.h>
#include <unistd.h>
#include "command.h"

void execute_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "cd: missing argument\n");
    } else if (chdir(args[1]) != 0) {
        perror("cd");
    }
}
