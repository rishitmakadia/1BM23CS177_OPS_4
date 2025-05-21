#include <stdio.h>
#define MAX 100

void printFrames(int frame[], int capacity) {
    for (int j = 0; j < capacity; j++) {
        if (frame[j] != -1) 
            printf("%d ", frame[j]);
    }
    printf("\n");
}

void fifo(int pages[], int n, int f) {
    int frames[f], i, j, k = 0, faults = 0, hit;

    for (i = 0; i < f; i++) frames[i] = -1;

    printf("\nFIFO Page Replacement:\n");

    for (i = 0; i < n; i++) {
        hit = 0;
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                hit = 1;
                break;
            }
        }
        if (!hit) {
            frames[k % f] = pages[i];
            k++;
            faults++;
        }

        printf("Frames after inserting %d: ", pages[i]);
        printFrames(frames, f); 
    }
    printf("FIFO - Total Page Faults: %d\n", faults);
}

void lru(int pages[], int n, int f) {
    int frames[f], time[f], i, j, t = 0, faults = 0, hit, pos;

    for (i = 0; i < f; i++) frames[i] = -1;

    printf("\nLRU Page Replacement:\n");

    for (i = 0; i < n; i++) {
        hit = 0;
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                hit = 1;
                time[j] = t++;
                break;
            }
        }
        if (!hit) {
            pos = -1;
            for (j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }
            if (pos == -1) {
                pos = 0;
                for (j = 1; j < f; j++) {
                    if (time[j] < time[pos])
                        pos = j;
                }
            }
            frames[pos] = pages[i];
            time[pos] = t++;
            faults++;
        }

        printf("Frames after inserting %d: ", pages[i]);
        printFrames(frames, f);  
    }
    printf("LRU - Total Page Faults: %d\n", faults);
}

void optimal(int pages[], int n, int f) {
    int frames[f], i, j, k, faults = 0, hit, farthest, index;

    for (i = 0; i < f; i++) frames[i] = -1;

    printf("\nOptimal Page Replacement:\n");

    for (i = 0; i < n; i++) {
        hit = 0;
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                hit = 1;
                break;
            }
        }
        if (!hit) {
            int found = 0;
            for (j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    frames[j] = pages[i];
                    found = 1;
                    break;
                }
            }
            if (!found) {
                farthest = -1;
                index = -1;
                for (j = 0; j < f; j++) {
                    int pos;
                    for (pos = i + 1; pos < n; pos++) {
                        if (frames[j] == pages[pos])
                            break;
                    }
                    if (pos > farthest) {
                        farthest = pos;
                        index = j;
                    }
                }
                frames[index] = pages[i];
            }
            faults++;
        }

        printf("Frames after inserting %d: ", pages[i]);
        printFrames(frames, f); 
    }
    printf("Optimal - Total Page Faults: %d\n", faults);
}

int main() {
    int choice, n, f, i;
    int pages[MAX];
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &f);
    fifo(pages, n, f);
    optimal(pages, n, f);
    lru(pages, n, f); 
    return 0;
}
