#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        // If fork() fails, print an error and exit
        perror("fork failed");
        exit(1);
    }

    if (pid > 0) {
        // Parent process
        printf("Parent process. PID = %d\n", getpid());
        printf("Child process forked. PID = %d\n", pid);

        // Parent process sleeps for 2 seconds and then exits
        sleep(2);
        printf("Parent process is exiting.\n");
        exit(0);
    } else {
        // Child process
        printf("Child process. PID = %d\n", getpid());

        // Sleep for a longer time to ensure the parent exits before the child
        sleep(10);

        printf("Child process is still running, and now it's an orphan.\n");
        printf("Child process is exiting.\n");
    }

    return 0;
}
