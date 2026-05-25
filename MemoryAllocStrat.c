#include <stdio.h>

#define MAX 20

void first_fit(int m[], int ms, int p[], int ps) {
    int al[MAX];

    for (int i = 0; i < ps; i++)
        al[i] = -1;

    for (int i = 0; i < ps; i++) {
        for (int j = 0; j < ms; j++) {
            if (m[j] >= p[i]) {
                al[i] = j;
                m[j] -= p[i];
                break;
            }
        }
    }

    printf("\nFirst Fit:\n");
    for (int i = 0; i < ps; i++) {
        if (al[i] != -1)
            printf("P%d -> M%d\n", i + 1, al[i] + 1);
        else
            printf("P%d -> Not Allocated\n", i + 1);
    }
}

void best_fit(int m[], int ms, int p[], int ps) {
    int al[MAX];

    for (int i = 0; i < ps; i++)
        al[i] = -1;

    for (int i = 0; i < ps; i++) {
        int bi = -1;

        for (int j = 0; j < ms; j++) {
            if (m[j] >= p[i]) {
                if (bi == -1 || m[j] < m[bi])
                    bi = j;
            }
        }

        if (bi != -1) {
            al[i] = bi;
            m[bi] -= p[i];
        }
    }

    printf("\nBest Fit:\n");
    for (int i = 0; i < ps; i++) {
        if (al[i] != -1)
            printf("P%d -> M%d\n", i + 1, al[i] + 1);
        else
            printf("P%d -> Not Allocated\n", i + 1);
    }
}

void worst_fit(int m[], int ms, int p[], int ps) {
    int al[MAX];

    for (int i = 0; i < ps; i++)
        al[i] = -1;

    for (int i = 0; i < ps; i++) {
        int wi = -1;

        for (int j = 0; j < ms; j++) {
            if (m[j] >= p[i]) {
                if (wi == -1 || m[j] > m[wi])
                    wi = j;
            }
        }

        if (wi != -1) {
            al[i] = wi;
            m[wi] -= p[i];
        }
    }

    printf("\nWorst Fit:\n");
    for (int i = 0; i < ps; i++) {
        if (al[i] != -1)
            printf("P%d -> M%d\n", i + 1, al[i] + 1);
        else
            printf("P%d -> Not Allocated\n", i + 1);
    }
}

int main() {
    int ms, ps;
    int m1[MAX], m2[MAX], m3[MAX], p[MAX];

    printf("Enter number of memory partitions: ");
    scanf("%d", &ms);

    printf("Enter memory partition sizes:\n");
    for (int i = 0; i < ms; i++) {
        scanf("%d", &m1[i]);
        m2[i] = m1[i];
        m3[i] = m1[i];
    }

    printf("Enter number of processes: ");
    scanf("%d", &ps);

    printf("Enter process sizes:\n");
    for (int i = 0; i < ps; i++)
        scanf("%d", &p[i]);

    first_fit(m1, ms, p, ps);
    best_fit(m2, ms, p, ps);
    worst_fit(m3, ms, p, ps);

    return 0;
}