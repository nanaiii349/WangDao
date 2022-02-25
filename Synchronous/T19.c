#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include "color.h"

#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)

sem_t A, B, m1, m2;

void *nankai()
{
    while (1)
    {
        sem_wait(&m1);
        sem_wait(&A);
        BLUE;
        printf("A car %ld from Nankai University come in.\n", gettid());
        sem_post(&A);
        BLUE;
        printf("A car %ld from Nankai University arrvie M.\n", gettid());
        sem_wait(&B);
        BLUE;
        printf("A car %ld from Nankai University arrvie Tianjin University.\n", gettid());
        sem_post(&B);
        sem_post(&m1);
        /* code */
    }
}

void *tianjin()
{
    while (1)
    {
        sem_wait(&m2);
        sem_wait(&B);
        RED;
        printf("A car %ld from Tianjin University come in.\n", gettid());
        sem_post(&B);
        RED;
        printf("A car %ld from Tianjin University arrvie M.\n", gettid());
        sem_wait(&A);
        RED;
        printf("A car %ld from Tianjin University arrvie Nankai University.\n", gettid());
        sem_post(&A);
        sem_post(&m2);
    }
}

int main()
{
    pthread_t p1, p21, p22, p23, p24;
    sem_init(&m1, 0, 1);
    sem_init(&m2, 0, 1);
    sem_init(&A, 0, 1);
    sem_init(&B, 0, 1);
    pthread_create(&p1, NULL, nankai, NULL);
    pthread_create(&p21, NULL, nankai, NULL);
    pthread_create(&p22, NULL, tianjin, NULL);
    pthread_create(&p23, NULL, tianjin, NULL);
    pthread_create(&p24, NULL, tianjin, NULL);
    pthread_join(p1, NULL);
    pthread_join(p21, NULL);
    pthread_join(p22, NULL);
    pthread_join(p23, NULL);
    pthread_join(p24, NULL);
    return 0;
}