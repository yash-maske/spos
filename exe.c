// fork_exec_example.c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process replaces its image with /bin/ls
        execl("/bin/ls", "ls", "-l", NULL);
        perror("execl failed"); // Only prints if execl fails
    } else {
        // Parent waits for the child
  
        printf("Parent: Child has finished executing.\n");
    }

    return 0;
}
