#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }
    
    if (pid == 0) {
        // Child process
        execlp("ps", "ps", "-e", NULL);
        perror("execlp");  // Print error if exec fails
        return 1;
    }

    // Parent process
    wait(NULL);
    printf("Parent process: Child completed.\n");

    return 0;
}
