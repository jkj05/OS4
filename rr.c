#include <stdio.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
};

int main() {
    int n, time_quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
        p[i].remaining_time = p[i].burst_time;
        p[i].waiting_time = 0;
        p[i].turnaround_time = 0;
    }

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    int time = 0, done;
    int completed = 0;

    while (completed < n) {
        done = 1;
        for (int i = 0; i < n; i++) {
            if (p[i].remaining_time > 0 && p[i].arrival_time <= time) {
                done = 0;
                if (p[i].remaining_time > time_quantum) {
                    time += time_quantum;
                    p[i].remaining_time -= time_quantum;
                } else {
                    time += p[i].remaining_time;
                    p[i].waiting_time = time - p[i].arrival_time - p[i].burst_time;
                    p[i].turnaround_time = time - p[i].arrival_time;
                    p[i].remaining_time = 0;
                    completed++;
                }
            }
        }
        if (done) {
            time++;
        }
    }

    double avg_waiting = 0, avg_turnaround = 0;
    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        avg_waiting += p[i].waiting_time;
        avg_turnaround += p[i].turnaround_time;
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].arrival_time,
               p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f", avg_waiting / n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround / n);
}