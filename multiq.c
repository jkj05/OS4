#include <stdio.h>

#define MAX 50

typedef struct {
    int pid;
    int burst_time;
    int waiting_time;                                                                                
    int turnaround_time;
} Process;


void calculateFCFS(Process queue[], int n) {
    int i;

    queue[0].waiting_time = 0;

    // Waiting Time
    for (i = 1; i < n; i++) {
        queue[i].waiting_time = queue[i - 1].waiting_time + queue[i - 1].burst_time;
    }

    // Turnaround Time
    for (i = 0; i < n; i++) {
        queue[i].turnaround_time = queue[i].waiting_time + queue[i].burst_time;
    }
}

// Function to print results
void printQueue(Process queue[], int n, char *name) {
    int i;
    float total_wt = 0, total_tat = 0;

    printf("\n--- %s Queue ---\n", name);
    printf("PID\tBT\tWT\tTAT\n");

    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\n",
               queue[i].pid,
               queue[i].burst_time,
               queue[i].waiting_time,
               queue[i].turnaround_time);

        total_wt += queue[i].waiting_time;
        total_tat += queue[i].turnaround_time;
    }

    printf("Average WT: %.2f\n", total_wt / n);
    printf("Average TAT: %.2f\n", total_tat / n);
}

int main() {
    Process systemQ[MAX], userQ[MAX];
    int n, i, sysCount = 0, userCount = 0;
    int type;

    printf("Enter total number of processes: ");
    scanf("%d", &n);

    // Input
    for (i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        printf("Enter Burst Time: ");
        int bt;
        scanf("%d", &bt);

        printf("Enter Type (1 = System, 2 = User): ");
        scanf("%d", &type);

        if (type == 1) {
            systemQ[sysCount].pid = i + 1;
            systemQ[sysCount].burst_time = bt;
            sysCount++;
        } else {
            userQ[userCount].pid = i + 1;
            userQ[userCount].burst_time = bt;
            userCount++;
        }
    }

    // Scheduling
    if (sysCount > 0)
        calculateFCFS(systemQ, sysCount);

    if (userCount > 0)
        calculateFCFS(userQ, userCount);

    // Output
    if (sysCount > 0)
        printQueue(systemQ, sysCount, "System");

    if (userCount > 0)
        printQueue(userQ, userCount, "User");

    return 0;
}