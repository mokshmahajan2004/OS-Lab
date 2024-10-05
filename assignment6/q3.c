#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;

    // Create a new process using vfork
    pid = vfork();

    if (pid < 0) {
        // If vfork() fails, print an error and exit
        perror("vfork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        printf("Child process. PID = %d\n", getpid());
        printf("Child is running and will call _exit().\n");

        // Child process exits immediately without affecting the parent's memory
        _exit(0);  // Use _exit to avoid flushing I/O buffers in both processes
    } else {
        // Parent process
        printf("Parent process. PID = %d\n", getpid());
        printf("Parent is waiting for the child to exit.\n");

        // Wait for the child process to complete before continuing
        sleep(1);

        printf("Parent process resumes after child exits.\n");
    }

    return 0;
}
