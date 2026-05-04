#include <stdio.h>
#include <math.h>

#define MAX 50

typedef struct {
    int pid;
    int burst;
    int period;
    int deadline;
    int weight;
    int completed;
} Process;

/* ---------- Utility ---------- */
void reset(Process p[], int n) {
    for (int i = 0; i < n; i++)
        p[i].completed = 0;
}

/* ---------- RATE MONOTONIC ---------- */
int findRM(Process p[], int n) {
    int min = -1;
    for (int i = 0; i < n; i++) {
        if (!p[i].completed) {
            if (min == -1 || p[i].period < p[min].period)
                min = i;
        }
    }
    return min;
}

void rateMonotonic(Process p[], int n) {
    printf("\n--- Rate Monotonic Scheduling ---\n");

    /* --- ADD: Utilization + RMS condition --- */
    float U = 0;
    for (int i = 0; i < n; i++) {
        U += (float)p[i].burst / p[i].period;
    }

    float bound = n * (pow(2, 1.0/n) - 1);

    printf("CPU Utilization = %.3f\n", U);
    printf("RMS Bound = %.3f\n", bound);

    if (U <= bound)
        printf("Schedulable under RMS\n");
    else
        printf("Not guaranteed schedulable under RMS\n");
    /* --- END ADD --- */

    reset(p, n);

    for (int i = 0; i < n; i++) {
        int idx = findRM(p, n);
        printf("P%d -> ", p[idx].pid);
        p[idx].completed = 1;
    }
    printf("END\n");
}

/* ---------- EDF ---------- */
int findEDF(Process p[], int n) {
    int min = -1;
    for (int i = 0; i < n; i++) {
        if (!p[i].completed) {
            if (min == -1 || p[i].deadline < p[min].deadline)
                min = i;
        }
    }
    return min;
}

void earliestDeadlineFirst(Process p[], int n) {
    printf("\n--- Earliest Deadline First ---\n");

    /* --- ADD: Utilization + EDF condition --- */
    float U = 0;
    for (int i = 0; i < n; i++) {
        U += (float)p[i].burst / p[i].period;
    }

    printf("CPU Utilization = %.3f\n", U);

    if (U <= 1)
        printf("Schedulable under EDF\n");
    else
        printf("Not schedulable under EDF\n");
    /* --- END ADD --- */

    reset(p, n);

    for (int i = 0; i < n; i++) {
        int idx = findEDF(p, n);
        printf("P%d -> ", p[idx].pid);
        p[idx].completed = 1;
    }
    printf("END\n");
}

/* ---------- PROPORTIONAL ---------- */
void proportionalScheduling(Process p[], int n) {
    printf("\n--- Proportional Scheduling ---\n");

    int totalWeight = 0;
    for (int i = 0; i < n; i++)
        totalWeight += p[i].weight;

    for (int i = 0; i < n; i++) {
        float share = (float)p[i].weight / totalWeight;
        printf("P%d gets %.2f CPU share\n", p[i].pid, share);
    }
}

/* ---------- MAIN ---------- */
int main() {
    Process p[MAX];
    int n, choice;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("\nProcess %d\n", i + 1);
        printf("Burst Time: ");
        scanf("%d", &p[i].burst);

        printf("Period (RM): ");
        scanf("%d", &p[i].period);

        printf("Deadline (EDF): ");
        scanf("%d", &p[i].deadline);

        printf("Weight (Proportional): ");
        scanf("%d", &p[i].weight);

        p[i].completed = 0;
    }

    printf("\nChoose Algorithm:\n");
    printf("1. Rate Monotonic\n");
    printf("2. Earliest Deadline First\n");
    printf("3. Proportional Scheduling\n");
    printf("Choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: rateMonotonic(p, n); break;
        case 2: earliestDeadlineFirst(p, n); break;
        case 3: proportionalScheduling(p, n); break;
        default: printf("Invalid choice\n");
    }

    return 0;