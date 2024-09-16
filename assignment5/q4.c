#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
void run_execl() {
    printf("Using execl:\n");
    execl("/bin/ls", "ls", "-l", NULL);
    perror("execl failed");
}
void run_execlp() {
    printf("Using execlp:\n");
    execlp("ls", "ls", "-l", NULL);
    perror("execlp failed");
}
void run_execv() {
    printf("Using execv:\n");
    char *args[] = {"ls", "-l", NULL};
    execv("/bin/ls", args);
    perror("execv failed");
}
void run_execvp() {
    printf("Using execvp:\n");
    char *args[] = {"ls", "-l", NULL};
    execvp("ls", args);
    perror("execvp failed");
}
void run_execle() {
    printf("Using execle:\n");
    char *env[] = {"HOME=/usr/home", "LOGNAME=guest", NULL};
    execle("/bin/ls", "ls", "-l", NULL, env);
    perror("execle failed");
}
void run_execve() {
    printf("Using execve:\n");
    char *args[] = {"ls", "-l", NULL};
    char *env[] = {"HOME=/usr/home", "LOGNAME=guest", NULL};
    execve("/bin/ls", args, env);
    perror("execve failed");
}
int main() {
    pid_t pid;
    // execl
    if ((pid = fork()) == 0) {
        run_execl();
    } else {
        wait(NULL);
    }
    // execlp
    if ((pid = fork()) == 0) {
        run_execlp();
    } else {
        wait(NULL);
    }
    // execv
    if ((pid = fork()) == 0) {
        run_execv();
    } else {
        wait(NULL);
    }
    // execvp
    if ((pid = fork()) == 0) {
        run_execvp();
    } else {
        wait(NULL);
    }
    // execle
    if ((pid = fork()) == 0) {
        run_execle();
    } else {
        wait(NULL);
    }
    // execve
    if ((pid = fork()) == 0) {
        run_execve();
    } else {
        wait(NULL);
    }
    return 0;
}
