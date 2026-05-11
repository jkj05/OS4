#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5

sem_t forkS[N];

void* phil(void *arg) {

    int i = *(int*)arg;
    int l = i;
    int r = (i + 1) % N;

    printf("Philosopher %d is thinking\n", i);

    sem_wait(&forkS[l]);
    sem_wait(&forkS[r]);

    printf("Philosopher %d is eating\n", i);

    sem_post(&forkS[r]);
    sem_post(&forkS[l]);

    printf("Philosopher %d finished eating\n", i);

    return NULL;
}

int main() {

    pthread_t t[N];
    int id[N];

    for (int i = 0; i < N; i++)
        sem_init(&forkS[i], 0, 1);

    for (int i = 0; i < N; i++) {
        id[i] = i;
        pthread_create(&t[i], NULL, phil, &id[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(t[i], NULL);

    for (int i = 0; i < N; i++)
        sem_destroy(&forkS[i]);

    return 0;
}