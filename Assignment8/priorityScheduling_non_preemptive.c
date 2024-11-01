#include <stdio.h>
struct process {
    int arrival, burst, priority, completion, turnaround, waiting;
};
void non_preemptive_priority(struct process p[], int n) {
    int time = 0, completed = 0, total_turnaround = 0, total_waiting = 0;
    while (completed < n) {
        int idx = -1, min_priority = 9999;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].burst > 0 && p[i].priority < min_priority) {
                min_priority = p[i].priority;
                idx = i;
            }
        }
        if (idx != -1) {
            time += p[idx].burst;
            p[idx].completion = time;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            total_turnaround += p[idx].turnaround;
            total_waiting += p[idx].waiting;
            p[idx].burst = 0; // Mark as completed
            completed++;
        } else {
            time++; // No process is ready, increment time
        }
    }
    printf("Process\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, p[i].arrival, p[i].burst + p[i].waiting, p[i].priority, p[i].completion, p[i].turnaround, p[i].waiting);
    printf("\nAverage Turnaround Time: %.2f\nAverage Waiting Time: %.2f\n", (float)total_turnaround / n, (float)total_waiting / n);
}
int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter arrival, burst time and priority for process %d: ", i + 1);
        scanf("%d %d %d", &p[i].arrival, &p[i].burst, &p[i].priority);
    }
    non_preemptive_priority(p, n);
    return 0;
}
