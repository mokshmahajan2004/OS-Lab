#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/wait.h> 
int main() { 
pid_t pid1, pid2; 
// First child process 
pid1 = fork(); 
if (pid1 < 0) { 
perror("Fork failed for child 1"); 
exit(1); 
} 
if (pid1 == 0) { 
// Inside first child process 
printf("Child 1 (PID: %d) running 'ls -l'\n", getpid()); 
execl("/bin/ls", "ls", "-l", NULL);  // Replace with 'ls -l' 
perror("execl failed for child 1");  // In case exec fails 
exit(1); 
} 
// Second child process 
pid2 = fork(); 

if (pid2 < 0) { 
perror("Fork failed for child 2"); 
exit(1); 
} 
if (pid2 == 0) { 
// Inside second child process 
printf("Child 2 (PID: %d) running 'ps -e'\n", getpid()); 
execl("/bin/ps", "ps", "-e", NULL);  // Replace with 'ps -e' 
perror("execl failed for child 2");  // In case exec fails 
exit(1); 
} 
// Parent process waits for both children to finish 
wait(NULL);  // Wait for the first child 
wait(NULL);  // Wait for the second child 
printf("Both child processes have completed.\n"); 
return 0; 
}