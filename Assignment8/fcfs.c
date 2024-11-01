#include <stdio.h>

struct process {
    int arrival_time, burst_time, completion_time, turnaround_time, waiting_time;
};

void fcfs(struct process p[], int n) {
    int time = 0, total_turnaround = 0, total_waiting = 0;
    
    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival_time) time = p[i].arrival_time;
        p[i].completion_time = time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        
        time += p[i].burst_time;
        total_turnaround += p[i].turnaround_time;
        total_waiting += p[i].waiting_time;
    }

    printf("Process\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", i+1, p[i].arrival_time, p[i].burst_time, 
               p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
    
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_turnaround / n);
    printf("Average Waiting Time: %.2f\n", (float)total_waiting / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct process p[n];
    
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
    }
    
    fcfs(p, n);
    return 0;
}
