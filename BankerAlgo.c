#include <stdio.h>

#define P 10
#define R 10

int n, m;
int av[R], mx[P][R], al[P][R], nd[P][R];

void calc_need() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            nd[i][j] = mx[i][j] - al[i][j];
}

void banker() {
    int wk[R], fin[P] = {0}, seq[P], cnt = 0;

    for (int i = 0; i < m; i++)
        wk[i] = av[i];

    while (cnt < n) {
        int f = 0;

        for (int i = 0; i < n; i++) {
            if (!fin[i]) {
                int ok = 1;

                for (int j = 0; j < m; j++) {
                    if (nd[i][j] > wk[j]) {
                        ok = 0;
                        break;
                    }
                }

                if (ok) {
                    for (int j = 0; j < m; j++)
                        wk[j] += al[i][j];

                    seq[cnt++] = i;
                    fin[i] = 1;
                    f = 1;
                }
            }
        }

        if (!f)
            break;
    }

    if (cnt == n) {
        printf("\nSafe State\nSafe Sequence: ");
        for (int i = 0; i < n; i++)
            printf("P%d ", seq[i]);
    } else {
        printf("\nUnsafe State\n");
    }
}

void detect() {
    int wk[R], fin[P], dead = 0;

    for (int i = 0; i < m; i++)
        wk[i] = av[i];

    for (int i = 0; i < n; i++) {
        int emp = 1;

        for (int j = 0; j < m; j++) {
            if (al[i][j] != 0) {
                emp = 0;
                break;
            }
        }

        fin[i] = emp;
    }

    while (1) {
        int f = 0;

        for (int i = 0; i < n; i++) {
            if (!fin[i]) {
                int ok = 1;

                for (int j = 0; j < m; j++) {
                    if (nd[i][j] > wk[j]) {
                        ok = 0;
                        break;
                    }
                }

                if (ok) {
                    for (int j = 0; j < m; j++)
                        wk[j] += al[i][j];

                    fin[i] = 1;
                    f = 1;
                }
            }
        }

        if (!f)
            break;
    }

    printf("\nDeadlocked Processes: ");
    for (int i = 0; i < n; i++) {
        if (!fin[i]) {
            printf("P%d ", i);
            dead = 1;
        }
    }

    if (!dead)
        printf("None");
}

int main() {
    printf("Enter number of processes and resources: ");
    scanf("%d%d", &n, &m);

    printf("\nEnter Available matrix:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &av[i]);

    printf("\nEnter Max matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &mx[i][j]);

    printf("\nEnter Allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &al[i][j]);

    calc_need();

    banker();
    detect();

    return 0;
}