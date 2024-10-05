#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        // If fork() fails, exit with error
        perror("fork failed");
        exit(1);
    }

    if (pid > 0) {
        // Parent process: This block is executed by the parent
        printf("Parent process. PID = %d\n", getpid());
        printf("Child process forked. PID = %d\n", pid);

        // Sleep for some time to allow the child to exit and become a zombie
        sleep(10);

        // Now the parent waits for the child to reap it and remove the zombie
        wait(NULL);

        printf("Child process reaped. Parent is exiting.\n");
    } else {
        // Child process: This block is executed by the child
        printf("Child process. PID = %d\n", getpid());
        printf("Child is exiting now.\n");

        // The child process exits immediately, becoming a zombie until the parent reaps it
        exit(0);
    }

    return 0;
}
