#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include "color.h"

#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)

sem_t mutex_i, mutex_j;
int i = 0, j = 0;

void *sales()
{
    while (1)
    {
        sem_wait(&mutex_j);
        BLUE;
        if (j <= i)
        {
            printf("Sell a piece of bread to customer %5d.\n", j++);
        }
        else
            printf("sales do nothing.\n");
        sem_post(&mutex_j);
    }
}

void *customer()
{
    while (1)
    {
        sem_wait(&mutex_i);
        YELLOW;
        printf("customer %5d come to buy bread.\n", i++);
        sem_post(&mutex_i);
    }
}

int main()
{
    pthread_t p1, p2;
    sem_init(&mutex_i, 0, 1);
    sem_init(&mutex_j, 0, 1);
    pthread_create(&p1, NULL, sales, NULL);
    pthread_create(&p2, NULL, customer, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    CLOSE;
    return 0;
}