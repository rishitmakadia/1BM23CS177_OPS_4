#include <stdio.h>
#include <stdlib.h>

// Write a C program to simulate multi-level queue scheduling
// algorithm considering the following scenario. All the
// processes in the system are divided into two categories –
// system processes and user processes. System processes are
// to be given higher priority than user processes. Use FCFS
// scheduling for the processes in each queue.

typedef struct process {
    int aT, bT, pID, cT, tT, wT, priority, remainingB;
} proc;

void completionT(proc p[], int n) {
    int completed = 0, currentTime = 0;
    int isCompleted[n];
    for (int i = 0; i < n; i++) {
        isCompleted[i] = 0;
        p[i].remainingB = p[i].bT;  // Initialize remaining burst time
    }

    while (completed < n) {
        int idx = -1;
        int minPri = 9999;

        for (int i = 0; i < n; i++) {
            // Check for arrival time and completion status
            if (p[i].aT <= currentTime && !isCompleted[i] && p[i].remainingB > 0) {
                // Choose the highest priority process (lower number means higher priority)
                if (p[i].priority < minPri) {
                    minPri = p[i].priority;
                    idx = i;
                }
                // If same priority, choose the one with the earlier arrival time
                else if (p[i].priority == minPri && p[i].aT < p[idx].aT) {
                    idx = i;
                }
            }
        }

        // If no process is found, increment the current time
        if (idx == -1) {
            currentTime++;
        } else {
            // Process the selected job for one unit of time
            p[idx].remainingB--;
            currentTime++;

            // If process has completed
            if (p[idx].remainingB == 0) {
                p[idx].cT = currentTime;
                isCompleted[idx] = 1;
                completed++;
            }
        }
    }
}

void tatT(proc p[], int n) {
    for (int k = 0; k < n; k++) {
        p[k].tT = p[k].cT - p[k].aT;  // Turnaround Time
    }
}

void waitingT(proc p[], int n) {
    for (int l = 0; l < n; l++) {
        p[l].wT = p[l].tT - p[l].bT;  // Waiting Time
    }
}

void MultiQueue(proc arr[], int n) {
    double TATavg = 0;
    double WTavg = 0;
    completionT(arr, n);
    tatT(arr, n);
    waitingT(arr, n);

    printf("\nProcess ID\tArrival Time\tBurst Time\tQueue\tCompletion Time\tTurn Around Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        TATavg += arr[i].tT;
        WTavg += arr[i].wT;
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\t\t\t%d\n", arr[i].pID, arr[i].aT, arr[i].bT, arr[i].priority, arr[i].cT, arr[i].tT, arr[i].wT);
    }

    printf("\nAverage Turn Around Time: %.2f\n", (TATavg / n));
    printf("Average Waiting Time: %.2f\n", (WTavg / n));
}

int main() {
    int no;
    printf("Enter No. of Processes: ");
    scanf("%d", &no);
    proc process[no];

    for (int i = 0; i < no; i++) {
        process[i].pID = i + 1;
        printf("Process %d\n", (i + 1));
        printf("Arrival Time: ");
        scanf("%d", &process[i].aT);
        printf("Burst Length: ");
        scanf("%d", &process[i].bT);
        printf("1 = System Process\t2 = User Process: ");
        scanf("%d", &process[i].priority);
    }
    MultiQueue(process, no);
    return 0;
}
