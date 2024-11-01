#include <stdio.h>
struct process {
    int arrival, burst, remaining, completion, turnaround, waiting;
};
void rr(struct process p[], int n, int quantum) {
    int time = 0, completed = 0, total_turnaround = 0, total_waiting = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                time += (p[i].remaining > quantum) ? quantum : p[i].remaining;
                p[i].remaining -= (p[i].remaining > quantum) ? quantum : p[i].remaining;

                if (p[i].remaining == 0) {
                    p[i].completion = time;
                    p[i].turnaround = time - p[i].arrival;
                    p[i].waiting = p[i].turnaround - p[i].burst;
                    total_turnaround += p[i].turnaround;
                    total_waiting += p[i].waiting;
                    completed++;
                }
            }
        }
    }
    printf("Process\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", i + 1, p[i].arrival, p[i].burst, p[i].completion, p[i].turnaround, p[i].waiting);
    printf("\nAverage Turnaround Time: %.2f\nAverage Waiting Time: %.2f\n", (float)total_turnaround / n, (float)total_waiting / n);
}
int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    struct process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter arrival and burst time for process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].remaining = p[i].burst; // Initialize remaining time
    }
    rr(p, n, quantum);
    return 0;
}
