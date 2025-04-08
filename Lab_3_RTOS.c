#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int id;
    int bT;
    int period;
    int deadline;
    int remT;
    int priority;
    int next_arrival;
    int next_deadline;
} Task;

// GCD and LCM functions
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int calculate_lcm(Task *tasks, int n) {
    int result = tasks[0].period;
    for (int i = 1; i < n; i++) {
        result = lcm(result, tasks[i].period);
    }
    return result;
}

void insert(Task *tasks, int n) {
    for (int i = 0; i < n; i++) {
        printf("Enter Process %d - Burst Time, Period, Deadline, priority: ", i + 1);
        scanf("%d %d %d %d", &tasks[i].bT, &tasks[i].period, &tasks[i].deadline, &tasks[i].priority);
        tasks[i].id = i + 1;
        tasks[i].remT = 0;
        tasks[i].next_arrival = 0;
        tasks[i].next_deadline = 0;
    }
}

void rate_monotonic(Task *tasks, int n, int hyper_period) {
    printf("\nRate-Monotonic Scheduling:\n");
    for (int t = 0; t < hyper_period; t++) {
        int current = -1;
        for (int i = 0; i < n; i++) {
            if (t == tasks[i].next_arrival) {
                tasks[i].remT = tasks[i].bT;
                tasks[i].next_arrival += tasks[i].period;
                tasks[i].next_deadline = t + tasks[i].period;
            }
            if (tasks[i].remT > 0 && (current == -1 || tasks[i].period < tasks[current].period)) {
                current = i;
            }
        }
        if (current != -1) {
            printf("Time %d: P%d\n", t, tasks[current].id);
            tasks[current].remT--;
        } else {
            printf("Time %d: Idle\n", t);
        }
    }
}

void earliest_deadline_first(Task *tasks, int n, int hyper_period) {
    printf("\nEarliest-Deadline First Scheduling:\n");
    for (int t = 0; t < hyper_period; t++) {
        int current = -1;
        for (int i = 0; i < n; i++) {
            if (t == tasks[i].next_arrival) {
                tasks[i].remT = tasks[i].bT;
                tasks[i].next_arrival += tasks[i].period;
                tasks[i].next_deadline = t + tasks[i].deadline;
            }
            if (tasks[i].remT > 0 && (current == -1 || tasks[i].next_deadline < tasks[current].next_deadline)) {
                current = i;
            }
        }
        if (current != -1) {
            printf("Time %d: P%d\n", t, tasks[current].id);
            tasks[current].remT--;
        } else {
            printf("Time %d: Idle\n", t);
        }
    }
}

void proportional_scheduling(Task *tasks, int n, int total_time) {
    printf("\nProportional Scheduling (priorityed Round Robin Approx.):\n");
    int time = 0;
    while (time < total_time) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < tasks[i].priority && time < total_time; j++) {
                printf("Time %d: P%d\n", time, tasks[i].id);
                time++;
            }
        }
    }
}

int main() {
    int n;
    Task *tasks;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    tasks = (Task *)malloc(n * sizeof(Task));
    if (!tasks) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    insert(tasks, n);
    int hyper_period = calculate_lcm(tasks, n);

    printf("\nCalculated total simulation time (LCM of periods): %d\n", hyper_period);

    rate_monotonic(tasks, n, hyper_period);

    for (int i = 0; i < n; i++) {
        tasks[i].remT = 0;
        tasks[i].next_arrival = 0;
        tasks[i].next_deadline = 0;
    }

    earliest_deadline_first(tasks, n, hyper_period);

    proportional_scheduling(tasks, n, hyper_period);

    free(tasks);
    return 0;
}