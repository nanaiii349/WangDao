#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include "color.h"

#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)

sem_t a, b, c, d, e;

void *A()
{
    while (1)
    {
        printf("A\t");
        sem_post(&a);
        /* code */
    }
}

void *B()
{
    printf("B\t");
    sem_post(&b);
    /* code */
}

void *C()
{
    sem_wait(&a);
    sem_wait(&b);
    printf("C\t");
    sem_post(&c);
}

void *D()
{
    printf("D\t");
    sem_post(&d);
}

void *E()
{
    sem_wait(&c);
    sem_wait(&d);
    printf("E\n");
}
