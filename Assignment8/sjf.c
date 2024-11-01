#include <stdio.h>
struct process {
    int arrival, burst, completion, turnaround, waiting, done;
};
void sjf(struct process p[], int n) {
    int time = 0, completed = 0, total_turnaround = 0, total_waiting = 0;
    while (completed < n) {
        int min_index = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && !p[i].done && (min_index == -1 || p[i].burst < p[min_index].burst))
                min_index = i;
        }
        if (min_index == -1) time++;  // No process has arrived, increment time
        else {
            time += p[min_index].burst;
            p[min_index].completion = time;
            p[min_index].turnaround = time - p[min_index].arrival;
            p[min_index].waiting = p[min_index].turnaround - p[min_index].burst;
            p[min_index].done = 1;

            total_turnaround += p[min_index].turnaround;
            total_waiting += p[min_index].waiting;
            completed++;
        }
    }
    printf("Process\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", i+1, p[i].arrival, p[i].burst, p[i].completion, p[i].turnaround, p[i].waiting);
    printf("\nAverage Turnaround Time: %.2f\nAverage Waiting Time: %.2f\n", (float)total_turnaround / n, (float)total_waiting / n);
}
int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct process p[n];
    
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].done = 0;  // Mark process as not completed
    }
    
    sjf(p, n);
    return 0;
}
