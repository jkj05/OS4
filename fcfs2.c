#include <stdio.h>

int main() {
    int n;
    printf("Enter number of Processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], ct[n], tat[n], wt[n];
    float total_tat = 0, total_wt = 0;

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("\nProcess %d\n", pid[i]);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
    }


    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1] || (at[j] == at[j + 1] && pid[j] > pid[j + 1])) {

                int temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;

                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                temp = pid[j];
                pid[j] = pid[j + 1];
                pid[j + 1] = temp;
            }
        }
    }

    int cur_t = 0;

    for (int i = 0; i < n; i++) {
        if (cur_t < at[i]) {
            cur_t = at[i];
        }

        ct[i] = cur_t + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        cur_t = ct[i];

        total_tat += tat[i];
        total_wt += wt[i];
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("Avg TAT time: %.2f\n", total_tat / n);
    printf("Avg WT time: %.2f\n", total_wt / n);

    return 0;
}
