#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include "color.h"

#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)

sem_t m1, m2, m3, watch;
int a = 0, b = 0, c = 0;

void *A()
{
    while (1)
    {
        sem_wait(&m1);
        if (a == 0)
            sem_wait(&watch);
        a++;
        sem_post(&m1);
        BLUE;
        printf("%ld is watching movie A...There are %d \n", gettid(), a);
        sem_wait(&m1);
        if (--a == 0)
            sem_post(&watch);
        sem_post(&m1);
        /* code */
    }
}

void *B()
{
    while (1)
    {
        sem_wait(&m2);
        if (b == 0)
            sem_wait(&watch);
        b++;
        sem_post(&m2);
        RED;
        printf("%ld is watching movie B...\n", gettid());
        sem_wait(&m2);
        if (--b == 0)
            sem_post(&watch);
        sem_post(&m2);
        /* code */
    }
}

void *C()
{
    while (1)
    {
        sem_wait(&m3);
        if (c == 0)
            sem_wait(&watch);
        c++;
        sem_post(&m3);
        YELLOW;
        printf("%ld is watching movie C...\n", gettid());
        sem_wait(&m3);
        if (--c == 0)
            sem_post(&watch);
        sem_post(&m3);
        /* code */
    }
}

int main()
{
    pthread_t p11, p12, p13, p21, p22, p31, p32, p33, p34;
    sem_init(&m1, 0, 1);
    sem_init(&m2, 0, 1);
    sem_init(&m3, 0, 1);
    sem_init(&watch, 0, 1);
    pthread_create(&p11, NULL, A, NULL);
    pthread_create(&p12, NULL, B, NULL);
    pthread_create(&p13, NULL, B, NULL);
    pthread_create(&p21, NULL, B, NULL);
    pthread_create(&p22, NULL, B, NULL);
    pthread_create(&p31, NULL, C, NULL);
    pthread_create(&p32, NULL, C, NULL);
    pthread_create(&p33, NULL, C, NULL);
    pthread_create(&p34, NULL, C, NULL);
    pthread_join(p11, NULL);
    pthread_join(p12, NULL);
    pthread_join(p13, NULL);
    pthread_join(p21, NULL);
    pthread_join(p22, NULL);
    pthread_join(p31, NULL);
    pthread_join(p32, NULL);
    pthread_join(p33, NULL);
    pthread_join(p34, NULL);
    return 0;
}