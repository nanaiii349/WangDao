#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include "color.h"

#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)

#define size 5
const int loop = 100;
int capacity = 0;
sem_t chopstick[size];
sem_t mutex;

void *philosopher(void *data)
{
    int index = (int)data;
    while (1)
    {
        sem_wait(&mutex);
        sem_wait(&chopstick[index]);
        YELLOW;
        printf("I:%d    philosopher %ld get chopstick%d.\n", index, gettid(), index);
        sem_wait(&chopstick[(index + 1) % size]);
        YELLOW;
        printf("I:%d    philosopher %ld get chopstick%d.\n", index, gettid(), (index + 1) % size);
        sem_post(&mutex);
        BLUE;
        printf("I:%d    philosopher %ld is eating.\n", index, gettid());
        sem_wait(&mutex);
        sem_post(&chopstick[index]);
        sem_post(&chopstick[(index + 1) % size]);
        RED;
        printf("I:%d    philosopher %ld is thinking.\n", index, gettid());
        sem_post(&mutex);
    }
}

int main(int argc, char *argv[])
{
    pthread_t p1, p2, p3, p4, p5;
    sem_init(&mutex, 0, 1);
    for (int i = 0; i < size; i++)
        sem_init(&chopstick[i], 0, 1); //信号量初始值为1
    pthread_create(&p1, NULL, philosopher, (void *)0);
    pthread_create(&p2, NULL, philosopher, (void *)1);
    pthread_create(&p3, NULL, philosopher, (void *)2);
    pthread_create(&p4, NULL, philosopher, (void *)3);
    pthread_create(&p5, NULL, philosopher, (void *)4);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);
    pthread_join(p5, NULL);
    CLOSE;
    return 0;
}
