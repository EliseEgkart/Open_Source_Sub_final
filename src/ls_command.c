#include <stdio.h>
#include <dirent.h>
#include "command.h"

void execute_ls(char **args) {
    char *path = args[1] ? args[1] : ".";
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("ls");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
}
