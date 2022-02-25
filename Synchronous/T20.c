#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include "color.h"

#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)

sem_t mutex, empty, full, work;

void *porduce()
{
    while (1)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        BLUE;
        printf("porduce  %ld put an item into buffer.\n", gettid());
        sem_post(&mutex);
        sem_post(&full);
        /* code */
    }
}

void *consumer()
{
    while (1)
    {
        sem_wait(&work);
        for (int i = 0; i < 10; i++)
        {
            sem_wait(&full);
            sem_wait(&mutex);
            RED;
            printf("consumer %ld get an item from buffer.(i:%2d)\n", gettid(), i + 1);
            sem_post(&mutex);
            sem_post(&empty);
        }
        sem_post(&work);
    }

    sem_wait(&full);
}

int main()
{
    pthread_t p1, p3, p2, p4, p5;
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, 100);
    sem_init(&full, 0, 0);
    sem_init(&work, 0, 1);
    pthread_create(&p1, NULL, porduce, NULL);
    pthread_create(&p2, NULL, porduce, NULL);
    pthread_create(&p4, NULL, porduce, NULL);
    pthread_create(&p3, NULL, consumer, NULL);
    pthread_create(&p5, NULL, consumer, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);
    pthread_join(p5, NULL);
    return 0;
}