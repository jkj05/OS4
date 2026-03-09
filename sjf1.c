#include <stdio.h>

struct Process {
    int pid;        // Process ID
    int bt;         // Burst Time
    int at;         // Arrival Time
    int wt;         // Waiting Time
    int tat;        // Turnaround Time
    int rt;         // Remaining Time 
};

// ---------- NON-PREEMPTIVE SJF ----------
void sjf_non_preemptive(struct Process p[], int n) {
    // Sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].bt > p[j].bt) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Waiting time
    p[0].wt = 0;
    for (int i = 1; i < n; i++) {
        p[i].wt = p[i - 1].wt + p[i - 1].bt;
    }

    // Turnaround time
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].wt + p[i].bt;
    }

    printf("\n--- Non-Preemptive SJF ---\n");
    printf("PID\tBT\tWT\tTAT\n");
    float avg_wt = 0, avg_tat = 0;
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\n", p[i].pid, p[i].bt, p[i].wt, p[i].tat);
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }
    printf("Average WT: %.2f\n", avg_wt/n);
    printf("Average TAT: %.2f\n", avg_tat/n);
}

// ---------- PREEMPTIVE SJF (SRTF) ----------
void sjf_preemptive(struct Process p[], int n) {
    int complete = 0, t = 0, minm = 9999;
    int shortest = -1, finish_time;
    int check = 0;
    for (int i = 0; i < n; i++)
        p[i].rt = p[i].bt;

    while (complete != n) {
        shortest = -1;
        minm = 9999;
        for (int j = 0; j < n; j++) {
            if ((p[j].at <= t) && (p[j].rt < minm) && p[j].rt > 0) {
                minm = p[j].rt;
                shortest = j;
                check = 1;
            }
        }

        if (check == 0) {
            t++;
            continue;
        }

        p[shortest].rt--;
        minm = p[shortest].rt;

        if (p[shortest].rt == 0) {
            complete++;
            check = 0;
            finish_time = t + 1;
            p[shortest].tat = finish_time - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;
            if (p[shortest].wt < 0) p[shortest].wt = 0;
        }
        t++;
    }

    printf("\n--- Preemptive SJF (SRTF) ---\n");
    printf("PID\tAT\tBT\tWT\tTAT\n");
    float avg_wt = 0, avg_tat = 0;
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].wt, p[i].tat);
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }
    printf("Average WT: %.2f\n", avg_wt/n);
    printf("Average TAT: %.2f\n", avg_tat/n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n], q[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter burst time for process %d: ", p[i].pid);
        scanf("%d", &p[i].bt);
        printf("Enter arrival time for process %d: ", p[i].pid);
        scanf("%d", &p[i].at);
        q[i] = p[i]; // copy for preemptive
    }

    sjf_non_preemptive(p, n);
    sjf_preemptive(q, n);

    return 0;
}

  