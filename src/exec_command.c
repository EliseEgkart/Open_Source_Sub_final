#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void execute_exec(char **args) {
    if (args[0] == NULL) {
        fprintf(stderr, "exec: command missing\n");
        return;
    }

    pid_t pid = fork(); // 프로세스를 복제합니다.
    if (pid == -1) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        // 자식 프로세스: execvp를 사용해 명령 실행
        if (execvp(args[0], args) == -1) {
            perror("execvp");
        }
        exit(EXIT_FAILURE); // execvp 실패 시 종료
    } else {
        // 부모 프로세스: 자식 프로세스가 종료될 때까지 대기
        int status;
        waitpid(pid, &status, 0);
    }
}
