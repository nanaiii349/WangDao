#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include "color.h"

#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)
#define size 10

sem_t bowl, mutex, chopstick[size];

void *philosopher(void *data)
{
    int i = (int)data;
    printf("I:%d", i);
    sleep(34);
    while (1)
    {
        sem_wait(&bowl);
        sem_wait(&mutex);
        sem_wait(&chopstick[i]);
        sem_wait(&chopstick[(i + 1) % size]);
        sem_post(&mutex);
        BLUE;
        printf("philosopher is eating..\n");
        sem_post(&chopstick[i]);
        sem_post(&chopstick[(i + 1) % size]);
        sem_post(&bowl);
        RED;
        printf("philosopher is thinking...\n");
        /* code */
    }
}

int main(int argc, char *argv[])
{
    int m = 4;
    pthread_t p1, p2, p3, p4, p5;
    sem_init(&bowl, 0, m);
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