#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include "color.h"

#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)

sem_t mutex_A, mutex_B, empty_A, empty_B, full_A, full_B;
int a = 0, b = 0;

void *produceA()
{
    while (1)
    {
        sem_wait(&empty_A);
        sem_wait(&mutex_A);
        RED;
        printf("put an A into F1.There are %5d A in F1.\n", ++a);
        sem_post(&mutex_A);
        sem_post(&full_A);
    }
}

void *produceB()
{
    while (1)
    {
        sem_wait(&empty_B);
        sem_wait(&mutex_B);
        YELLOW;
        printf("put a  B into F2.There are %5d B in F2.\n", ++b);
        sem_post(&mutex_B);
        sem_post(&full_B);
    }
}

void *assemble()
{
    while (1)
    {
        sem_wait(&full_A);
        sem_wait(&mutex_A);
        BLUE;
        printf("get one A from F1.\n");
        a--;
        sem_post(&mutex_A);
        sem_post(&empty_A);
        sem_wait(&full_B);
        sem_wait(&mutex_B);
        BLUE;
        printf("get one B from F2.\n");
        b--;
        sem_post(&mutex_B);
        sem_post(&empty_B);
        BLUE;
        printf("assembling...\n");
    }
}

int main()
{
    pthread_t p1, p2, p3;
    sem_init(&mutex_A, 0, 1);
    sem_init(&mutex_B, 0, 1);
    sem_init(&empty_A, 0, 100);
    sem_init(&empty_B, 0, 100);
    sem_init(&full_A, 0, 0);
    sem_init(&full_B, 0, 0);
    pthread_create(&p1, NULL, produceA, NULL);
    pthread_create(&p2, NULL, produceB, NULL);
    pthread_create(&p3, NULL, assemble, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    CLOSE;
    return 0;
}