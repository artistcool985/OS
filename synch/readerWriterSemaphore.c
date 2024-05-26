#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <unistd.h>

pthread_mutex_t mutex;
sem_t can_read;
sem_t can_write;

int readers_reading = 0;
bool writer_writing = false;

void *reader(void *arg) {
    int id = *((int *)arg);
    while (true) {
        sem_wait(&can_read);
        pthread_mutex_lock(&mutex);
        readers_reading++;
        if (readers_reading == 1) {
            sem_wait(&can_write);
        }
        pthread_mutex_unlock(&mutex);
        sem_post(&can_read);

        printf("Reader %d is reading...\n", id);
        usleep(1000000);

        sem_wait(&can_read);
        pthread_mutex_lock(&mutex);
        readers_reading--;
        if (readers_reading == 0) {
            sem_post(&can_write);
        }
        pthread_mutex_unlock(&mutex);
        sem_post(&can_read);

        usleep(1000000);
    }
    return NULL;
}

void *writer(void *arg) {
    int id = *((int *)arg);
    while (true) {
        printf("\n");
        printf("Writer %d is trying to enter\n", id);
        sem_wait(&can_write);
        writer_writing = true;
        printf("Writer %d is writing...\n", id);
        sem_post(&can_write);
        printf("Writer %d is leaving\n", id);
        printf("\n");

        usleep(2000000);

        writer_writing = false;
        sem_post(&can_read);

        usleep(2000000);
    }
    return NULL;
}

int main() {
    int num_readers, num_writers;

    printf("Enter the number of readers: ");
    scanf("%d", &num_readers);

    printf("Enter the number of writers: ");
    scanf("%d", &num_writers);

    pthread_t readers[num_readers];
    pthread_t writers[num_writers];
    int reader_ids[num_readers];
    int writer_ids[num_writers];

    sem_init(&can_read, 0, num_readers);
    sem_init(&can_write, 0, 1);

    for (int i = 0; i < num_readers; i++) {
        reader_ids[i] = i;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    for (int i = 0; i < num_writers; i++) {
        writer_ids[i] = i;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    for (int i = 0; i < num_readers; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < num_writers; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&can_read);
    sem_destroy(&can_write);

    return 0;
}
