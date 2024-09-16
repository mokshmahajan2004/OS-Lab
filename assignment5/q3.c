#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
void and_logic() {
    printf("\n--- AND Logic ---\n");
    if (fork() == 0) exit(0);  // First child exits successfully
    wait(NULL);
    if (fork() == 0) exit(0);  // Second child exits successfully
    wait(NULL);
    printf("AND logic is TRUE.\n");  // Both succeeded
}
void or_logic() {
    printf("\n--- OR Logic ---\n");
    if (fork() == 0) exit(1);  // First child fails
    int status;
    wait(&status);
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        printf("OR logic is TRUE.\n");  // First child succeeded
    } else if (fork() == 0) exit(0);  // Second child succeeds
    wait(NULL);
    printf("OR logic is TRUE.\n");  // One of the children succeeded
}
int main() {
    and_logic();
    or_logic();
    return 0;
}
