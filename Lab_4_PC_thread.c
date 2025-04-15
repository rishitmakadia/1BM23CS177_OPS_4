#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define max 5

int mutex = 1;
int full = 0;
int empty = max;
int buf[max];
int in = 0, out = 0;

void Wait(int *s) {
    while (*s <= 0)
        ;
    (*s)--;
}

void Signal(int *s) {
    (*s)++;
}

void* Producer(void* arg) {
    while (1) {
        int item = rand() % 100;
        Wait(&empty);
        Wait(&mutex);
        full++;
        printf("Item Produced %d\n", item);
        buf[in] = item;
        in = (in + 1) % max;
        Signal(&mutex);
        Signal(&full);
        sleep(1);
    }
    return NULL;
}

void* Consumer(void* arg) {
    while (1) {
        Wait(&full);
        Wait(&mutex);
        int item = buf[out];
        printf("Item Consumed %d\n", item);
        full--;
        out = (out + 1) % max;
        Signal(&mutex);
        Signal(&empty);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    pthread_create(&producer_thread, NULL, Producer, NULL);
    pthread_create(&consumer_thread, NULL, Consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}
