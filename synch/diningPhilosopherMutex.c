#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHIL 5

pthread_mutex_t forks[NUM_PHIL];
pthread_t philosophers[NUM_PHIL];
int bites[NUM_PHIL] = {0};
int total_bites = 0;

void *philosopher(void *arg) {
    int id = *((int *) arg);
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHIL;

    while (bites[id] < 1) {
        printf("Philosopher %d is thinking.\n", id);
        usleep((rand() % 100) * 100000);

        printf("Philosopher %d is hungry and trying to pick up forks.\n", id);
        pthread_mutex_lock(&forks[left_fork]);
        pthread_mutex_lock(&forks[right_fork]);
        usleep((rand() % 100) * 100000);

        printf("Philosopher %d picked up forks and is eating.\n", id);
        usleep((rand() % 100) * 100000);
        printf("Philosopher %d finished eating one bite.\n", id);
        pthread_mutex_unlock(&forks[left_fork]);
        pthread_mutex_unlock(&forks[right_fork]);

        bites[id]++;
        total_bites++;

        usleep((rand() % 100) * 100000);
    }

    if (total_bites == NUM_PHIL) {
        printf("All philosophers have had one bite. Exiting...\n");
        exit(0);
    }

    return NULL;
}

int main() {
    srand(time(NULL));

    for (int i = 0; i < NUM_PHIL; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    for (int i = 0; i < NUM_PHIL; i++) {
        int *arg = malloc(sizeof(*arg));
        *arg = i;
        pthread_create(&philosophers[i], NULL, philosopher, arg);
    }

    for (int i = 0; i < NUM_PHIL; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < NUM_PHIL; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
