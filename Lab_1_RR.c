#include <stdio.h>
#include <stdlib.h>

#define quantum 4  // Fixed quantum time

typedef struct process {
    int aT, bT, pID, cT, tT, wT, remainingB;
} proc;

void completionT(proc p[], int n) {
    int completed = 0, currentTime = 0;
    int isCompleted[n];
    for (int i = 0; i < n; i++) {
        isCompleted[i] = 0;
        p[i].remainingB = p[i].bT;  // Initialize remaining burst time
    }

    // Process execution loop
    while (completed < n) {
        int idx = -1;

        // Check for processes that have arrived and are not completed
        for (int i = 0; i < n; i++) {
            if (p[i].aT <= currentTime && !isCompleted[i] && p[i].remainingB > 0) {
                idx = i;
                break;
            }
        }

        if (idx == -1) {
            currentTime++;  // No process is ready, so increment time
        } else {
            // Execute the process for a time slice of 'quantum'
            int timeSlice = (p[idx].remainingB > quantum) ? quantum : p[idx].remainingB;
            p[idx].remainingB -= timeSlice;
            currentTime += timeSlice;

            // If the process is completed
            if (p[idx].remainingB == 0) {
                p[idx].cT = currentTime;  // Set the completion time
                isCompleted[idx] = 1;     // Mark this process as completed
                completed++;
            }
        }
    }
}

void tatT(proc p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].tT = p[i].cT - p[i].aT;  // Turnaround time = Completion Time - Arrival Time
    }
}

void waitingT(proc p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].wT = p[i].tT - p[i].bT;  // Waiting time = Turnaround Time - Burst Time
    }
}

void RoundRobin(proc arr[], int n) {
    double TATavg = 0;
    double WTavg = 0;
    sort(arr, n);  // Sort processes by arrival time
    completionT(arr, n);
    tatT(arr, n);
    waitingT(arr, n);

    // Display results
    printf("\nProcess ID\t Arrival Time\t Burst Time\t Completion Time\t Turn Around Time\t Waiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t\t%d\t\t\t%d\n", arr[i].pID, arr[i].aT, arr[i].bT, arr[i].cT, arr[i].tT, arr[i].wT);
    }

    // Average Turnaround Time and Waiting Time
    for (int i = 0; i < n; i++) {
        TATavg += arr[i].tT;
        WTavg += arr[i].wT;
    }
    printf("\nAverage Turn Around Time: %f\n", (TATavg / n));
    printf("Average Waiting Time: %f\n", (WTavg / n));
}

void sort(proc p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].aT > p[j].aT) {
                proc temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int main() {
    int no;
    printf("Enter No. of Processes: ");
    scanf("%d", &no);
    proc process[no];
    for (int i = 0; i < no; i++) {
        process[i].pID = i + 1;
        printf("\nProcess %d \n", (i + 1));
        printf("Arrival Time: ");
        scanf("%d", &process[i].aT);
        printf("Burst Length: ");
        scanf("%d", &process[i].bT);
    }
    RoundRobin(process, no);
    return 0;
}
