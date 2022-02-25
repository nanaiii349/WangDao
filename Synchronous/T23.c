#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include "color.h"

#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)

sem_t mutexX, mutexY, mutexZ;

typedef struct
{
    int a;
    int b;
} cnum;
cnum x, y, z;

cnum add(cnum p, cnum q)
{
    cnum s;
    s.a = p.a + q.a;
    s.b = p.b + q.b;
    return s;
}

void *P1()
{
    while (1)
    {
        cnum w;
        sem_wait(&mutexY);
        w = add(x, y);
        sem_post(&mutexY);
        BLUE;
        printf("P1 w.a:%5d\tw.b:%5d\n", w.a, w.b);
    }
}

void *P2()
{
    while (1)
    {
        cnum w;
        sem_wait(&mutexY);
        sem_wait(&mutexZ);
        w = add(z, y);
        sem_post(&mutexY);
        sem_post(&mutexZ);
        GREEN;
        printf("P2 w.a:%5d\tw.b:%5d\n", w.a, w.b);
    }
}

void *P3()
{
    while (1)
    {
        cnum w;
        w.a = 1;
        w.b = 1;
        sem_wait(&mutexZ);
        z = add(z, w);
        sem_post(&mutexZ);
        sem_wait(&mutexY);
        y = add(y, w);
        sem_post(&mutexY);
        RED;
        printf("P3 z.a:%5d\tz.b:%5d\ty.a:%5d\ty.b:%5d\n", z.a, z.b, y.a, y.b);
    }
}

int main()
{
    x.a = 1;
    x.b = 2;
    y.a = 2;
    y.b = -1;
    z.a = 4;
    z.b = 9;
    pthread_t p1, p2, p3;
    sem_init(&mutexX, 0, 1);
    sem_init(&mutexY, 0, 1);
    sem_init(&mutexZ, 0, 1);
    pthread_create(&p1, NULL, P1, NULL);
    pthread_create(&p2, NULL, P2, NULL);
    pthread_create(&p3, NULL, P3, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    return 0;
}
