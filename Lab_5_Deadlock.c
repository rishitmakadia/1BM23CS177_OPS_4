#include <stdio.h>
#include <stdlib.h>

#define N 4    // Number of processes
#define M 3    // Number of resources

int deadlock_detection(int alloc[N][M], int max[N][M], int avail[M]) {
    int finish[N] = {0};
    int work[M];
    int need[N][M];
    int deadlocked = 0;

    // Calculate Need Matrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Initialize Work array
    for (int i = 0; i < M; i++) {
        work[i] = avail[i];
    }

    int count = 0;
    while (count < N) {
        int found = 0;
        for (int i = 0; i < N; i++) {
            if (finish[i] == 0) { // Process not finished
                int j;
                for (j = 0; j < M; j++) {
                    if (need[i][j] > work[j])
                        break;
                }
                if (j == M) { // If all needs can be satisfied
                    for (int k = 0; k < M; k++) {
                        work[k] += alloc[i][k];
                    }
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }
        if (found == 0) {
            break; // No process could be finished
        }
    }

    // Check for deadlocked processes
    for (int i = 0; i < N; i++) {
        if (finish[i] == 0) {
            deadlocked = 1;
            break;
        }
    }

    if (deadlocked) {
        printf("Deadlock Detected!!!\nDeadlocked processes are: ");
        for (int i = 0; i < N; i++)
            if (finish[i] == 0)
                printf("P%d ", i);
        printf("\n");
        return 1; // Return 1 to indicate deadlock
    } else {
        printf("Deadlock Not Detected!!!!\n");
        return 0; // Return 0 to indicate no deadlock
    }
}

int main() {
    int alloc[N][M], max[N][M], avail[M];

    printf("Enter Allocation Matrix (%dx%d):\n", N, M);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Max Matrix (%dx%d):\n", N, M);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources (%d):\n", M);
    for (int i = 0; i < M; i++)
        scanf("%d", &avail[i]);

    deadlock_detection(alloc, max, avail);

    return 0;
}

// Alternate Method
// 2)DEADLOCK DETECTION
// #include <stdio.h>
// #include <stdbool.h>

// #define MAX_P 10
// #define MAX_R 10

// int n, m;
// int Allocation[MAX_P][MAX_R];
// int Request[MAX_P][MAX_R];
// int Available[MAX_R];
// bool Finish[MAX_P];

// int main() {
//     input();
//     detectDeadlock();
//     return 0;
// }

// void input() {
//     printf("Enter number of processes: ");
//     scanf("%d", &n);
//     printf("Enter number of resources: ");
//     scanf("%d", &m);

//     printf("Enter Allocation Matrix (%d x %d):\n", n, m);
//     for (int i = 0; i < n; i++)
//         for (int j = 0; j < m; j++)
//             scanf("%d", &Allocation[i][j]);

//     printf("Enter Request Matrix (%d x %d):\n", n, m);
//     for (int i = 0; i < n; i++)
//         for (int j = 0; j < m; j++)
//             scanf("%d", &Request[i][j]);

//     printf("Enter Available Resources (%d):\n", m);
//     for (int i = 0; i < m; i++)
//         scanf("%d", &Available[i]);

//     for (int i = 0; i < n; i++)
//         Finish[i] = false;
// }

// bool canExecute(int process) {
//     for (int j = 0; j < m; j++) {
//         if (Request[process][j] > Available[j])
//             return false;
//     }
//     return true;
// }

// void detectDeadlock() {
//     int count = 0;

//     while (count < n) {
//         bool found = false;

//         for (int i = 0; i < n; i++) {
//             if (!Finish[i] && canExecute(i)) {
//                 for (int j = 0; j < m; j++)
//                     Available[j] += Allocation[i][j];

//                 Finish[i] = true;
//                 found = true;
//                 count++;
//             }
//         }

//         if (!found)
//             break;
//     }

//     printDeadlockProcesses();
// }

// void printDeadlockProcesses() {
//     bool deadlock = false;
//     for (int i = 0; i < n; i++) {
//         if (!Finish[i]) {
//             deadlock = true;
//             printf("Process %d is in deadlock.\n", i);
//         }
//     }

//     if (!deadlock)
//         printf("No deadlock detected. All processes can complete.\n");
// }
