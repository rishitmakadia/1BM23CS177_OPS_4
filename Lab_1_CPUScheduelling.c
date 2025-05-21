#include <stdio.h>
#include <stdlib.h>
#define QUANTUM 4

typedef struct process {
    int pID, aT, bT, cT, tT, wT, priority, remainingB;
} proc;

void sortByArrival(proc p[], int n) {
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

void sortByPriority(proc p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].aT > p[j].aT || (p[i].aT == p[j].aT && p[i].priority > p[j].priority)) {
                proc temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void calculateTAT(proc p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].tT = p[i].cT - p[i].aT;
    }
}

void calculateWT(proc p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].wT = p[i].tT - p[i].bT;
    }
}

void printResults(proc p[], int n, const char* algorithm) {
    double avgTAT = 0, avgWT = 0;
    
    printf("\n%s Scheduling Results:\n", algorithm);
    printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               p[i].pID, p[i].aT, p[i].bT, p[i].cT, p[i].tT, p[i].wT);
        avgTAT += p[i].tT;
        avgWT += p[i].wT;
    }
    
    printf("\nAverage Turnaround Time: %.2f\n", avgTAT / n);
    printf("Average Waiting Time: %.2f\n\n", avgWT / n);
}

void FCFS(proc p[], int n) {
    proc temp[n];
    for (int i = 0; i < n; i++) temp[i] = p[i];
    
    sortByArrival(temp, n);
    
    temp[0].cT = temp[0].aT + temp[0].bT;
    for (int i = 1; i < n; i++) {
        if (temp[i].aT > temp[i-1].cT) {
            temp[i].cT = temp[i].aT + temp[i].bT;
        } else {
            temp[i].cT = temp[i-1].cT + temp[i].bT;
        }
    }
    
    calculateTAT(temp, n);
    calculateWT(temp, n);
    printResults(temp, n, "FCFS");
}

void SJF(proc p[], int n) {
    proc temp[n];
    for (int i = 0; i < n; i++) temp[i] = p[i];
    
    sortByArrival(temp, n);
    
    int completed = 0, currentTime = 0;
    int isCompleted[n];
    for (int i = 0; i < n; i++) isCompleted[i] = 0;
    
    while (completed < n) {
        int idx = -1;
        int minBT = 9999;
        
        for (int i = 0; i < n; i++) {
            if (temp[i].aT <= currentTime && !isCompleted[i]) {
                if (temp[i].bT < minBT) {
                    minBT = temp[i].bT;
                    idx = i;
                }
            }
        }
        
        if (idx == -1) {
            currentTime++;
        } else {
            temp[idx].cT = currentTime + temp[idx].bT;
            currentTime = temp[idx].cT;
            isCompleted[idx] = 1;
            completed++;
        }
    }
    
    calculateTAT(temp, n);
    calculateWT(temp, n);
    printResults(temp, n, "SJF");
}

void PriorityScheduling(proc p[], int n) {
    proc temp[n];
    for (int i = 0; i < n; i++) temp[i] = p[i];
    
    sortByPriority(temp, n);
    
    int completed = 0, currentTime = 0;
    int isCompleted[n];
    for (int i = 0; i < n; i++) isCompleted[i] = 0;
    
    while (completed < n) {
        int idx = -1;
        int minPri = 9999;
        
        for (int i = 0; i < n; i++) {
            if (temp[i].aT <= currentTime && !isCompleted[i]) {
                if (temp[i].priority < minPri) {
                    minPri = temp[i].priority;
                    idx = i;
                }
            }
        }
        
        if (idx == -1) {
            currentTime++;
        } else {
            temp[idx].cT = currentTime + temp[idx].bT;
            currentTime = temp[idx].cT;
            isCompleted[idx] = 1;
            completed++;
        }
    }
    
    calculateTAT(temp, n);
    calculateWT(temp, n);
    printResults(temp, n, "Priority");
}

void RoundRobin(proc p[], int n) {
    proc temp[n];
    for (int i = 0; i < n; i++) {
        temp[i] = p[i];
        temp[i].remainingB = temp[i].bT;
    }
    
    sortByArrival(temp, n);
    
    int completed = 0, currentTime = 0;
    int isCompleted[n];
    for (int i = 0; i < n; i++) isCompleted[i] = 0;
    
    while (completed < n) {
        int idx = -1;
        
        for (int i = 0; i < n; i++) {
            if (temp[i].aT <= currentTime && !isCompleted[i] && temp[i].remainingB > 0) {
                idx = i;
                break;
            }
        }
        
        if (idx == -1) {
            currentTime++;
        } else {
            int timeSlice = (temp[idx].remainingB > QUANTUM) ? QUANTUM : temp[idx].remainingB;
            temp[idx].remainingB -= timeSlice;
            currentTime += timeSlice;
            
            if (temp[idx].remainingB == 0) {
                temp[idx].cT = currentTime;
                isCompleted[idx] = 1;
                completed++;
            }
        }
    }
    
    calculateTAT(temp, n);
    calculateWT(temp, n);
    printResults(temp, n, "Round Robin");
}

int main() {
    int n;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    proc processes[n];
    
    for (int i = 0; i < n; i++) {
        processes[i].pID = i + 1;
        printf("\nProcess %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].aT);
        printf("Burst Time: ");
        scanf("%d", &processes[i].bT);
        printf("Priority: ");
        scanf("%d", &processes[i].priority);
    }
    
    // Call all scheduling algorithms directly
    FCFS(processes, n);
    SJF(processes, n);
    PriorityScheduling(processes, n);
    RoundRobin(processes, n);
    
    return 0;
}