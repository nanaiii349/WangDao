#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include "color.h"

#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)

sem_t Close, start, stop, ready;

void *conductor()
{
    while (1)
    {
        sem_wait(&ready);
        sem_post(&Close);
        BLUE;
        printf("Close the door.\n");
        sem_wait(&start);
        BLUE;
        printf("Tickets.\n");
        sem_wait(&stop);
        BLUE;
        printf("open the door.\n\n");
        /* code */
    }
}

void *driver()
{
    while (1)
    {
        sem_wait(&Close);
        sem_post(&start);
        RED;
        printf("BUS start.\n");
        sleep(1);
        sem_post(&stop);
        RED;
        printf("BUS stop.\n");
        sem_post(&ready);
        /* code */
    }
}

int main()
{
    pthread_t p1, p2;
    sem_init(&stop, 0, 0); //信号量初始值为1
    sem_init(&start, 0, 0);
    sem_init(&Close, 0, 0);
    sem_init(&ready, 0, 1);
    pthread_create(&p1, NULL, conductor, NULL);
    pthread_create(&p2, NULL, driver, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    return 0;
}