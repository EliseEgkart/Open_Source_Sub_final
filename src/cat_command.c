#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "command.h"

void execute_cat(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "cat: missing argument\n");
        return;
    }

    for (int i = 1; args[i] != NULL; i++) {
        int fd = open(args[i], O_RDONLY);
        if (fd < 0) {
            perror("cat");
            continue;
        }

        char buffer[1024];
        int bytes_read;
        while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
            write(STDOUT_FILENO, buffer, bytes_read);
        }
        close(fd);
    }
}
