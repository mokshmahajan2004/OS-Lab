#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        // If fork() fails, print an error and exit
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        printf("Child process. PID = %d\n", getpid());
        printf("Child is performing its task.\n");

        // Simulate some work with sleep
        sleep(2);

        printf("Child process is exiting.\n");
        exit(42);  // Exit with a specific status code
    } else {
        // Parent process
        printf("Parent process. PID = %d\n", getpid());
        printf("Parent is waiting for the child to complete.\n");

        // Wait for the child to finish and retrieve its status
        pid_t child_pid = wait(&status);

        // Check if the child terminated normally
        if (WIFEXITED(status)) {
            printf("Child process %d exited with status %d.\n", child_pid, WEXITSTATUS(status));
        } else {
            printf("Child process %d did not terminate normally.\n", child_pid);
        }

        printf("Parent process is done.\n");
    }

    return 0;
}
