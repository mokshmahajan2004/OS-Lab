#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    for (int i = 0; i < 3; i++) {
        if (fork() == 0) {
            printf("Child process: PID = %d, PPID = %d\n", getpid(), getppid());
        } else {
            wait(NULL);
            break;
        }
    }
    return 0;
}
