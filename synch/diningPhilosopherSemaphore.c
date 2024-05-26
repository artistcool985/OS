#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define NUM_PHIL 5

sem_t forks[NUM_PHIL];
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
        sem_wait(&forks[left_fork]);
        sem_wait(&forks[right_fork]);
        usleep((rand() % 100) * 100000);

        printf("Philosopher %d picked up forks and is eating.\n", id);
        usleep((rand() % 100) * 100000);
        printf("Philosopher %d finished eating one bite.\n", id);
        sem_post(&forks[left_fork]);
        sem_post(&forks[right_fork]);

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
        sem_init(&forks[i], 0, 1);
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
        sem_destroy(&forks[i]);
    }

    return 0;
}
