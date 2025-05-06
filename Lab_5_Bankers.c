#include <stdio.h>
#define MAX 10

// Write a C program to simulate: (Any one)
// a) Bankers’ algorithm for the purpose of deadlock
// avoidance.
// b) Deadlock Detection

void in(int arr[][MAX], int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }
}

void bankers(int processes, int res, int alloc[][MAX], int max[][MAX], int instances[])
{
    int finish[MAX] = {0}, safeSeq[MAX], need[MAX][MAX], work[MAX];

    for (int i = 0; i < res; i++)
        work[i] = instances[i];

 
    for (int i = 0; i < processes; i++)
    {
        for (int j = 0; j < res; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];  // Calculate Need
        }
    }
    for (int i = 0; i < processes; i++)  
    {
        for (int j = 0; j < res; j++)
        {
            work[j] -= alloc[i][j];  
        }
    }

    int count = 0;
    while (count < processes)
    {
        int found = 0;
        for (int p = 0; p < processes; p++)
        {
            if (finish[p] == 0)
            {
                int j;
                for (j = 0; j < res; j++)
                    if (need[p][j] > work[j]) 
                        break;

                if (j == res) 
                {
                    for (int k = 0; k < res; k++)
                        work[k] += alloc[p][k]; 

                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = 1;
                }
            }
        }

        if (found == 0) 
        {
            printf("System is not in a safe state.\n");
            return;  
        }
    }

    // Print the safe sequence
    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < processes; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");
}

int main()
{
    int res, proce;
    printf("Enter No of processes: ");
    scanf("%d", &proce);
    printf("Enter No of Resource: ");
    scanf("%d", &res);
    
    int instances[MAX], allocated[MAX][MAX], max[MAX][MAX];
    
    printf("Enter No of Instances of each Resource: \n");
    for (int i = 0; i < res; i++)
    {
        printf("Instance of %d: ", (i + 1));
        scanf("%d", &instances[i]);
    }
    
    printf("Enter Maximum Resource Matrix:\n");
    in(max, proce, res);
    
    printf("Enter Allocation Matrix:\n");
    in(allocated, proce, res);

    bankers(proce, res, allocated, max, instances);

    return 0;
}
