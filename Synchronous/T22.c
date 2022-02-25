#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include "color.h"

#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)

sem_t emptyA, emptyB, fullA, fullB, mutexA, mutexB;

void *A()
{
    while (1)
    {
        sem_wait(&fullA);
        sem_wait(&mutexA);
        RED;
        printf("A answer a question from  B.\n");
        sem_post(&mutexA);
        sem_post(&emptyA);
        sem_wait(&emptyB);
        sem_wait(&mutexB);
        RED;
        printf("A put a new qusetion to B.\n");
        sem_post(&mutexB);
        sem_post(&fullB);
        /* code */
    }
}

void *B()
{
    while (1)
    {
        sem_wait(&fullB);
        sem_wait(&mutexB);
        BLUE;
        printf("B answer a question from  A.\n");
        sem_post(&mutexB);
        sem_post(&emptyB);
        sem_wait(&emptyA);
        sem_wait(&mutexA);
        BLUE;
        printf("B put a new qusetion to A.\n");
        sem_post(&mutexA);
        sem_post(&fullA);
        /* code */
    }
}

int main()
{
    int M = 10, N = 10;
    int x = 2, y = 7;
    pthread_t p1, p2;
    sem_init(&emptyA, 0, M - x);
    sem_init(&fullA, 0, x);
    sem_init(&emptyB, 0, N - y);
    sem_init(&fullB, 0, y);
    sem_init(&mutexA, 0, 1);
    sem_init(&mutexB, 0, 1);
    pthread_create(&p1, NULL, A, NULL);
    pthread_create(&p2, NULL, B, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    return 0;
}