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
sem_t tobacco, glue, paper, finish;

void *provider()
{
    int i = 0;
    while (i++ < loop)
    {

        sem_wait(&finish);
        int a = rand() % 3;
        BLUE;
        if (a == 0)
        {
            sem_post(&tobacco);
            printf("PROVIDER offer tobacco.\n");
        }
        if (a == 1)
        {
            sem_post(&glue);
            printf("PROVIDER offer glue.\n");
        }
        if (a == 2)
        {
            sem_post(&paper);
            printf("PROVIDER offer paper.\n");
        }
        /* code */
    }
    exit(0);
}

void *smoker_tobacco()
{
    int i = 0;
    while (i++ < loop)
    {
        sem_wait(&tobacco);
        RED;
        printf("smoker %ld with tobacco is smoking.\n", gettid());
        sem_post(&finish);
        /* code */
    }
}

void *smoker_glue()
{
    int i = 0;
    while (i++ < loop)
    {
        sem_wait(&glue);
        RED;
        printf("smoker %ld with glue is smoking.\n", gettid());
        sem_post(&finish);
        /* code */
    }
}

void *smoker_paper()
{
    int i = 0;
    while (i++ < loop)
    {
        sem_wait(&paper);
        RED;
        printf("smoker %ld with paper is smoking.\n", gettid());
        sem_post(&finish);
        /* code */
    }
}

int main()
{
    pthread_t p1, p2, p3, p4;
    sem_init(&finish, 0, 1); //信号量初始值为1
    sem_init(&tobacco, 0, 0);
    sem_init(&glue, 0, 0);
    sem_init(&paper, 0, 0);
    pthread_create(&p1, NULL, provider, NULL);
    pthread_create(&p2, NULL, smoker_tobacco, NULL);
    pthread_create(&p3, NULL, smoker_glue, NULL);
    pthread_create(&p4, NULL, smoker_paper, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);
    CLOSE;
    return 0;
}