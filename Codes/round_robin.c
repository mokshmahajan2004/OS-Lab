#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

struct Process {
    int pid;        // Process ID
    int burstTime;  // Burst Time (time required by process)
    int remainingTime; // Remaining time for execution
    int waitingTime;   // Waiting time
    int turnaroundTime; // Turnaround time
};

void calculateWaitingTime(struct Process proc[], int n, int quantum) {
    int currentTime = 0;
    int done;
    
    do {
        done = 1; // Assume all processes are done
        for (int i = 0; i < n; i++) {
            if (proc[i].remainingTime > 0) {
                done = 0; // If at least one process is not done
                
                if (proc[i].remainingTime > quantum) {
                    currentTime += quantum;
                    proc[i].remainingTime -= quantum;
                } else {
                    currentTime += proc[i].remainingTime;
                    proc[i].waitingTime = currentTime - proc[i].burstTime;
                    proc[i].remainingTime = 0;
                }
            }
        }
    } while (!done); // Loop until all processes are done
}

void calculateTurnaroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaroundTime = proc[i].burstTime + proc[i].waitingTime;
    }
}

void printAverageTimes(struct Process proc[], int n) {
    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        totalWaitingTime += proc[i].waitingTime;
        totalTurnaroundTime += proc[i].turnaroundTime;
        printf("%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burstTime, proc[i].waitingTime, proc[i].turnaroundTime);
    }
    
    printf("\nAverage Waiting Time: %.2f", (float)totalWaitingTime / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);
}

int main() {
    int n, quantum;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process proc[n];
    
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &proc[i].burstTime);
        proc[i].remainingTime = proc[i].burstTime;
        proc[i].waitingTime = 0; // Initialize waiting time
    }
    
    printf("Enter time quantum: ");
    scanf("%d", &quantum);
    
    pid_t pid = fork(); // Create a child process
    
    if (pid == 0) {
        // Child process: run the round robin scheduling algorithm
        printf("\nChild process is running the Round Robin Scheduling...\n");
        calculateWaitingTime(proc, n, quantum);
        calculateTurnaroundTime(proc, n);
        printAverageTimes(proc, n); // Child process prints the results
        exit(0); // Terminate the child process after execution
    } else if (pid > 0) {
        // Parent process: wait for the child to complete
        wait(NULL); // Wait for the child process to finish
        printf("\nParent: Child process has completed scheduling.\n");
    } else {
        // Fork failed
        printf("Fork failed. Exiting...\n");
        return 1;
    }
    
    return 0;
}
