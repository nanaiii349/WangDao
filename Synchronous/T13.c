#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include "color.h"

#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)

sem_t bridge, m1, m2;
int north = 0, south = 0;

void *South()
{
    while (1)
    {
        sem_wait(&m1);
        if (south == 0)
            sem_wait(&bridge);
        south++;
        sem_post(&m1);
        RED;
        printf("A car %ld drive from south to north.\n", gettid());
        sem_wait(&m1);
        if (--south == 0)
            sem_post(&bridge);
        sem_post(&m1);
        /* code */
    }
}

void *North()
{
    while (1)
    {
        sem_wait(&m2);
        if (north == 0)
            sem_wait(&bridge);
        north++;
        sem_post(&m2);
        BLUE;
        printf("A car %ld drive from north to south.\n", gettid());
        sem_wait(&m2);
        if (--north == 0)
            sem_post(&bridge);
        sem_post(&m2);
    }
}

int main()
{
    pthread_t p1, p2, p3, p4, p5, p6;
    sem_init(&bridge, 0, 1);
    sem_init(&m1, 0, 1);
    sem_init(&m2, 0, 1);
    pthread_create(&p1, NULL, North, NULL);
    pthread_create(&p2, NULL, North, NULL);
    pthread_create(&p3, NULL, South, NULL);
    pthread_create(&p4, NULL, North, NULL);
    pthread_create(&p5, NULL, North, NULL);
    pthread_create(&p6, NULL, North, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);
    pthread_join(p5, NULL);
    pthread_join(p6, NULL);
    CLOSE;
    return 0;
}