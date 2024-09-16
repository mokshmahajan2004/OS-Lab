#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
void create_child(const char *cmd, const char *arg1, const char *arg2) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
        printf("Child (PID: %d) running '%s %s'\n", getpid(), arg1, arg2);
        execl(cmd, arg1, arg2, NULL);
        perror("execl");
        exit(1);
    }
}
int main() {
    create_child("/bin/ls", "ls", "-l");  // First child
    create_child("/bin/ps", "ps", "-e");  // Second child
    // Parent waits for both children
    while (wait(NULL) > 0);  // Wait for all children
    printf("Both child processes have completed.\n");
    return 0;
}
