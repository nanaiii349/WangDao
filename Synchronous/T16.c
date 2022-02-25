#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include "color.h"

#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)

sem_t mutex, empty, full;

void *P()
{
    while (1)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        RED;
        printf("P put something into buffer.\n");
        sem_post(&mutex);
        sem_post(&full);
        /* code */
    }
}

void *Q()
{
    while (1)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        YELLOW;
        printf("Q get something from buffer.\n");
        sem_post(&mutex);
        sem_post(&empty);
        /* code */
    }
}

void *R()
{
    while (1)
    {
        int FULL = 0, EMPTY = 0, d;
        d = sem_getvalue(&empty, &EMPTY);
        d = sem_getvalue(&full, &FULL);
        printf("full:%3d,empty:%3d\n", FULL, EMPTY);
        if (EMPTY >= 1)
        {
            sem_wait(&empty);
            sem_wait(&mutex);
            BLUE;
            printf("R put something into buffer.\n");
            sem_post(&mutex);
            sem_post(&full);
        }
        if (FULL >= 1)
        {
            sem_wait(&full);
            sem_wait(&mutex);
            GREEN;
            printf("R get something from buffer.\n");
            sem_post(&mutex);
            sem_post(&empty);
        }
        /* code */
    }
}

int main()
{
    pthread_t p1, p3, p2;
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, 3);
    sem_init(&full, 0, 0);
    pthread_create(&p1, NULL, P, NULL);
    pthread_create(&p2, NULL, Q, NULL);
    pthread_create(&p3, NULL, R, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    return 0;
}