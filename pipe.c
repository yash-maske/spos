// simple_pipe.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main() {
    int fd[2];
    pid_t pid;
    int number = 10;
    int received;

    if (pipe(fd) == -1) {
        perror("pipe failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        close(fd[1]); // Close write end
        read(fd[0], &received, sizeof(received));
        printf("Child received number: %d\n", received);
        printf("Child: %d * 2 = %d\n", received, received * 2);
        close(fd[0]);
    } else {
        // Parent process
        close(fd[0]); // Close read end
        write(fd[1], &number, sizeof(number));
        close(fd[1]);
    }

    return 0;
}
