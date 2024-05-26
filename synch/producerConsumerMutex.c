#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;
int in = 0;    // Index for the producer to insert into the buffer
int out = 0;   // Index for the consumer to remove from the buffer

pthread_mutex_t mutex;

void insertItem(int item) {
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
    count++;
}
void *producer(void *param) {
    int item;
    while (1) {
        item = rand() % 100;

        pthread_mutex_lock(&mutex);
        if (count < BUFFER_SIZE) {
            insertItem(item);
            printf("Produced item: %d\n", item);
        }
        else {
            printf("Buffer is full. Cannot produce item %d\n" , item);
        }
        pthread_mutex_unlock(&mutex);

        sleep(2);
    }
}

int removeItem() {
    int item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    count--;
    return item;
}
void *consumer(void *param) {
    int item;
    while (1) {
        pthread_mutex_lock(&mutex);
        if (count > 0) {
            item = removeItem();
            printf("Consumed item: %d\n", item);
        }
        else {
            printf("Buffer is empty. Cannot consume item.\n");
        }
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
}

int main() {
    pthread_t tid_producer, tid_consumer;

    pthread_create(&tid_producer, NULL, producer, NULL);
    pthread_create(&tid_consumer, NULL, consumer, NULL);

    pthread_join(tid_producer, NULL);
    pthread_join(tid_consumer, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}