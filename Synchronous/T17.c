#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include "color.h"

#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)

sem_t mutex, wait, ready;
int site = 2;

void *customer()
{
    while (1)
    {
        int flag = 0;
        sem_wait(&mutex);
        if (site > 0)
        {
            BLUE;
            printf("customer %ld is waiting...\n", gettid());
            flag = 1;
            site--;
        }
        sem_post(&mutex);
        if (flag == 1)
        {
            sem_post(&wait);
            sem_wait(&ready);
            BLUE;
            printf("customer %ld leave with a new hairstyle.\n", gettid());
        }
        else
        {
            RED;
            printf("customer %ld leave because no sites.\n", gettid());
        }
        /* code */
    }
}

void *countsite()
{
    while (1)
    {
        sleep(1);
        GREEN;
        printf("There are %d empty site.\n", site);
    }
}

void *barber()
{
    while (1)
    {
        sem_wait(&wait);
        sem_post(&ready);
        YELLOW;
        printf("barber is working...\n");
        sem_wait(&mutex);
        site++;
        sem_post(&mutex);
        /* code */
    }
}

int main()
{
    pthread_t p1, p3, p2, p4, p5;
    sem_init(&mutex, 0, 1);
    sem_init(&wait, 0, 0);
    sem_init(&ready, 0, 0);
    pthread_create(&p1, NULL, customer, NULL);
    pthread_create(&p2, NULL, customer, NULL);
    pthread_create(&p4, NULL, customer, NULL);
    pthread_create(&p3, NULL, barber, NULL);
    pthread_create(&p5, NULL, countsite, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);
    pthread_join(p5, NULL);
    return 0;
}