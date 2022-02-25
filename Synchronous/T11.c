#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include "color.h"

#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)

sem_t m1, m2, m3, rb, ry, rz;
int x, y, z;
int a = 2, b = 3, c = 4;

void *P1()
{
    while (1)
    {
        sem_wait(&m1);
        a = rand() % 50;
        BLUE;
        printf("P1 input A:%5d.\n", a);
        sem_post(&m2);
        sem_wait(&rb);
        x = a + b;
        BLUE;
        printf("P1 get   x:%5d.\n", x);
        sem_wait(&ry);
        sem_wait(&rz);
        GREEN;
        printf("x:%5d,y:%5d,z:%5d.\n\n", x, y, z);
    }
}

void *P2()
{
    while (1)
    {
        sem_wait(&m2);
        b = rand() % 50;
        YELLOW;
        printf("P2 input B:%5d.\n", b);
        sem_post(&rb);
        sem_post(&m3);
        y = a * b;
        YELLOW;
        printf("P2 get   y:%5d.\n", y);
        sem_post(&ry);
        sem_post(&ry); //P1、P3都需要使用ry
    }
}

void *P3()
{
    while (1)
    {
        sem_wait(&m3);
        c = rand() % 50;
        RED;
        printf("P3 input C:%5d.\n", c);
        sem_wait(&ry);
        RED;
        z = y + c - a;
        printf("P3 get   z:%5d.\n", z);
        sem_post(&rz);
        sem_post(&m1);
    }
}

int main()
{
    pthread_t p1, p2, p3;
    sem_init(&m1, 0, 1);
    sem_init(&m2, 0, 0);
    sem_init(&m3, 0, 0);
    sem_init(&rb, 0, 0);
    sem_init(&ry, 0, 0);
    sem_init(&rz, 0, 0);
    pthread_create(&p1, NULL, P1, NULL);
    pthread_create(&p2, NULL, P2, NULL);
    pthread_create(&p3, NULL, P3, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    CLOSE;
    return 0;
}