#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include "color.h"

#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)

sem_t mutex, empty, full, finish, ready;

void *customer()
{
    while (1)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        BLUE;
        printf("customer %ld take the number.\n", gettid());
        sem_post(&mutex);
        sem_post(&full);
        sem_wait(&ready);
        BLUE;
        printf("customer %ld accept services.\n", gettid());
        sem_post(&empty);
    }
}

void *teller()
{
    while (1)
    {
        sem_wait(&full);
        sem_post(&ready);
        RED;
        printf("The teller serves a customer.\n");
        /* code */
    }
}

int main()
{
    pthread_t p1, p21, p22, p23, p24;
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, 3);
    sem_init(&full, 0, 0);
    sem_init(&ready, 0, 0);
    pthread_create(&p1, NULL, teller, NULL);
    pthread_create(&p21, NULL, customer, NULL);
    pthread_create(&p22, NULL, customer, NULL);
    pthread_create(&p23, NULL, customer, NULL);
    pthread_create(&p24, NULL, customer, NULL);
    pthread_join(p1, NULL);
    pthread_join(p21, NULL);
    pthread_join(p22, NULL);
    pthread_join(p23, NULL);
    pthread_join(p24, NULL);
    return 0;
}