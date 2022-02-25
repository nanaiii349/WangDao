#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include "color.h"

#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)

int m = 10, n = 2;
int a = 0, b = 0;
sem_t mutex, M, N;

void *A()
{
    while (1)
    {
        sem_wait(&M);
        sem_wait(&mutex);
        BLUE;
        printf("put item A into buffer.There are %5d A ,%5d B in buffer.\t", ++a, b);
        RED;
        printf("M:%5d,N:%5d\n", a - b, b - a);
        sem_post(&mutex);
        sem_post(&N);
    }
}

void *B()
{
    while (1)
    {
        sem_wait(&N);
        sem_wait(&mutex);
        YELLOW;
        printf("put item B into buffer.There are %5d A ,%5d B in buffer.\t", a, ++b);
        RED;
        printf("M:%5d,N:%5d\n", a - b, b - a);
        sem_post(&mutex);
        sem_post(&M);
    }
}

int main()
{
    pthread_t p1, p2;
    sem_init(&mutex, 0, 1);
    sem_init(&M, 0, m);
    sem_init(&N, 0, n);
    pthread_create(&p1, NULL, A, NULL);
    pthread_create(&p2, NULL, B, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    CLOSE;
    return 0;
}