#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include "color.h"

#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)

#define size 3
sem_t mutex, empty;
int a = 0;

void *visitor()
{
    while (1)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        RED;
        printf("visitor %ld enter the door.\n", gettid());
        a++;
        sem_post(&mutex);
        YELLOW;
        printf("visitor %ld is visiting.There are %1d vistors.\n", gettid(), a);
        for (int i = 0; i < 100; i++)
            a = a;
        sem_wait(&mutex);
        GREEN;
        printf("visitor %ld out the door.\n", gettid());
        a--;
        sem_post(&mutex);
        sem_post(&empty);
    }
}

int main()
{
    pthread_t p1, p2, p3, p4;
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, size);
    pthread_create(&p1, NULL, visitor, NULL);
    pthread_create(&p2, NULL, visitor, NULL);
    pthread_create(&p3, NULL, visitor, NULL);
    pthread_create(&p4, NULL, visitor, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);
    CLOSE;
    return 0;
}