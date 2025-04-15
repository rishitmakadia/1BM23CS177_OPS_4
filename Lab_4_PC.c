#include <stdio.h>

/*Write a C program to simulate: (Any one)
a) Producer-Consumer problem using semaphores.*/

int mutex = 1;
int full = 0;
int empty = 2;
int item = 0;

void wait(int *s)
{
    while (*s <= 0)
        ;
    (*s)--;
}
void signal(int *s)
{
    (*s)++;
}

void Producer()
{
    wait(&mutex);
    wait(&empty);
    full++;
    printf("Item Produced %d", ++item);
    signal(&mutex);
    signal(&full);
}

void Consumer()
{
    wait(&full);
    wait(&mutex);
    printf("Item Consumed %d", item--);
    full--;
    signal(&empty);
    signal(&mutex);
}

int main()
{
    int option;
    printf("1. Producer\t2. Consumer\t3. Exit\n");
    while (1)
    {
        printf("\nEnter Option: ");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            if ((mutex == 1) && (empty != 0))
                Producer();
            else
                printf("Stock is full, can't produce more");
            break;
        case 2:
            if ((mutex == 1) && (full != 0))
                Consumer();
            else
                printf("Stock is empty, can't consume");
            break;
        case 3:
            return 0;
            break;
        default:
            printf("Enter Correct Option");
            break;
        }
    }
}