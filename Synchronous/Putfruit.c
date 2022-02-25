#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include "color.h"

#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)

const int size = 10;
const int loop = 100;
sem_t mutex, apple, orange, empty;

void *dad()
{
    int i = 0;
    while (i++ < loop)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        RED;
        printf("DAD put an apple into plate.\n");
        sem_post(&mutex);
        sem_post(&apple);
        /* code */
    }
}

void *mom()
{
    int i = 0;
    while (i++ < loop)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        BLUE;
        printf("MOM put an orange into plate.\n");
        sem_post(&mutex);
        sem_post(&orange);
        /* code */
    }
}

void *son()
{
    int i = 0;
    while (i++ < loop)
    {
        sem_wait(&orange);
        sem_wait(&mutex);
        YELLOW;
        printf("SON get an orange from plate.\n");
        sem_post(&mutex);
        sem_post(&empty);
        /* code */
    }
}

void *daughter()
{
    int i = 0;
    while (i++ < loop)
    {
        sem_wait(&apple);
        sem_wait(&mutex);
        GREEN;
        printf("DAUGHTER get an apple from plate.\n");
        sem_post(&mutex);
        sem_post(&empty);
        /* code */
    }
}

int main()
{
    pthread_t p1, p2, p3, p4;
    sem_init(&mutex, 0, 1); //信号量初始值为1
    sem_init(&empty, 0, 1); //信号量初始值为1
    sem_init(&apple, 0, 0);
    sem_init(&orange, 0, 0);
    pthread_create(&p1, NULL, dad, NULL);
    pthread_create(&p2, NULL, mom, NULL);
    pthread_create(&p3, NULL, son, NULL);
    pthread_create(&p4, NULL, daughter, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);
    CLOSE;
    return 0;
}