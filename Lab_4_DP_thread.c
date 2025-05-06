#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// b) Dining-Philosopher’s problem

#define MAX 5

int chopstick[MAX] = {1, 1, 1, 1, 1};  // 1 = free, 0 = taken
int mutex = 1;
int philosopher_id = 0;

void Wait(int *s) {
    while (*s <= 0);
    (*s)--;
}

void Signal(int *s) {
    (*s)++;
}

void* philosopher(void* arg) {
    int id;

    // Assign philosopher ID inside thread
    Wait(&mutex);
    id = philosopher_id++;
    Signal(&mutex);

    int left = id;
    int right = (id + 1) % MAX;

    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);

        Wait(&mutex);
        if (chopstick[left] && chopstick[right]) {
            chopstick[left] = chopstick[right] = 0;
            printf("Philosopher %d picked up chopsticks %d and %d and is eating.\n", id, left, right);
            Signal(&mutex);

            sleep(2); // Eating

            Wait(&mutex);
            chopstick[left] = chopstick[right] = 1;
            printf("Philosopher %d put down chopsticks %d and %d.\n", id, left, right);
            Signal(&mutex);
        } else {
            Signal(&mutex);
        }
    }
}

void main() {
    pthread_t philosophers[5];

    for (int i = 0; i < 5; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, NULL);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(philosophers[i], NULL);
    } 
}