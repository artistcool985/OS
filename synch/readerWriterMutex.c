#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

pthread_mutex_t mutex;
int readers_reading = 0;
bool writer_writing = false;

void *reader(void *arg) {
    int id = *((int *)arg);
    while (true) {
        pthread_mutex_lock(&mutex);
        while (writer_writing) {
            pthread_mutex_unlock(&mutex);
            usleep(1000000);
            pthread_mutex_lock(&mutex);
        }
        readers_reading++;
        printf("Reader %d is reading...\n", id);
        pthread_mutex_unlock(&mutex);

        usleep(1000000);

        pthread_mutex_lock(&mutex);
        readers_reading--;
        if (readers_reading == 0) {
            pthread_mutex_unlock(&mutex);
            usleep(1000000);
        } else {
            pthread_mutex_unlock(&mutex);
        }

        usleep(1000000);
    }
    return NULL;
}

void *writer(void *arg) {
    int id = *((int *)arg);
    while (true) {
        printf("\n");
        printf("Writer %d is trying to enter\n", id);
        pthread_mutex_lock(&mutex);
        while (readers_reading > 0 || writer_writing) {
            pthread_mutex_unlock(&mutex);
            usleep(1000000);
            pthread_mutex_lock(&mutex);
        }
        writer_writing = true;
        printf("Writer %d is writing...\n", id);
        pthread_mutex_unlock(&mutex);
        printf("Writer %d is leaving\n", id);
        printf("\n");
        usleep(2000000);

        pthread_mutex_lock(&mutex);
        writer_writing = false;
        pthread_mutex_unlock(&mutex);

        usleep(2000000);
    }
    return NULL;
}

int main() {
    int num_readers, num_writers;

    printf("Enter the number of readers:");
    scanf("%d", &num_readers);

    printf("Enter the number of writers:");
    scanf("%d", &num_writers);

    pthread_t readers[num_readers];
    pthread_t writers[num_writers];
    int reader_ids[num_readers];
    int writer_ids[num_writers];

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < num_readers; i++) {
        reader_ids[i] = i;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    for (int i = 0; i < num_writers; i++) {
        writer_ids[i] = i;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    for (int i = 0; i < num_readers; i++)
        pthread_join(readers[i], NULL);
    for (int i = 0; i < num_writers; i++)
        pthread_join(writers[i], NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
