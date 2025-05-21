#include <stdio.h>

void worst_fit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[processes];
    for (int i = 0; i < processes; i++) {
        int worstIdx = -1;
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        } else {
            allocation[i] = -1;
        }
    }

    printf("Worst Fit Allocation:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process %d of size %d -> ", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("Block %d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void best_fit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[processes];
    for (int i = 0; i < processes; i++) {
        int bestIdx = -1;
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        } else {
            allocation[i] = -1;
        }
    }

    printf("Best Fit Allocation:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process %d of size %d -> ", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("Block %d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void first_fit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[processes];
    for (int i = 0; i < processes; i++) {
        allocation[i] = -1;
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    printf("First Fit Allocation:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process %d of size %d -> ", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("Block %d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int blockSize[] = {100, 500, 200, 300, 600};
    int processSize[] = {212, 417, 112, 426};
    int n = sizeof(blockSize) / sizeof(blockSize[0]);
    int m = sizeof(processSize) / sizeof(processSize[0]);

    int blockSize1[5] = {100, 500, 200, 300, 600};
    int blockSize2[5] = {100, 500, 200, 300, 600};
    int blockSize3[5] = {100, 500, 200, 300, 600};

    first_fit(blockSize1, n, processSize, m);
    printf("\n");
    best_fit(blockSize2, n, processSize, m);
    printf("\n");
    worst_fit(blockSize3, n, processSize, m);

    return 0;
}
