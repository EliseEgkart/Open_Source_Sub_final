#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

void execute_exec(char **args) {
    if (args[0] == NULL) {
        fprintf(stderr, "exec: command missing\n");
        return;
    }

    pid_t pid = fork(); // 자식 프로세스 생성
    if (pid == -1) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        // 자식 프로세스: 명령 실행
        if (execvp(args[0], args) == -1) {
            // 명령어가 PATH에 없으면 현재 디렉토리에서 실행 시도
            char path[BUFFER_SIZE];
            snprintf(path, sizeof(path), "./%s", args[0]);
            execvp(path, args);

            // 여전히 실패하면 에러 출력
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        // 부모 프로세스: 자식 프로세스 대기
        int status;
        waitpid(pid, &status, 0);
    }
}