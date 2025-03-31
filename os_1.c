#include<stdio.h>
#include<stdlib.h>

// Lab1: Write a C Program to store and retrieve the Process details such as pid, process name, process arrival time, process completion time, process execution time. 
// Using Dara structures Structure and arrays to demonstrate the above scenario.

// #define MAX 50;

typedef struct process{
    int id, arrivalT, completionT;
    char name[50];
    int turnAroundT;
}proc;

void insertProcess(proc* p){
    printf("Enter Process Name:");
    scanf(" %s", p->name);
    // fgets()
    printf("Enter Process ID:");
    scanf("%d", p->id);
    printf("Enter arrival Time:");
    scanf("%d", p->arrivalT);
    printf("Enter completion Time:");
    scanf("%d", p->completionT);
    p->turnAroundT = p->arrivalT-p->completionT;
}

void search(proc* p, int sId, int n){
    for(int k=0; k<n; k++){
        if (p[k].id == sId)
            displayProcess(p[k]);
    }
}

void displayProcess(proc p){
    printf("Process ID: %d", p.id);
    printf("Process Name: %s", p.name);
    printf("Process Turn Around Time: %d", p.turnAroundT);
}

int main(){
    int no;
    printf("Enter No. of processes:");
    scanf("%d", &no);
    proc arr[no];
    printf("Insert Processes\n");
    for(int i=0; i<no;i++){
        printf("Process %d\n", i+1);
        insertProcess(&arr[i]);
    }
    printf("Display Processes\n");
    for(int j=0; j<no;j++){
        displayProcess(arr[j]);
    }
}