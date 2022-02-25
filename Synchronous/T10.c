#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include "color.h"

#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)

sem_t vat, well, empty, pail, full;
int a = 0, b = 0;

void *oldmonk()
{
    while (1)
    {
        sem_wait(&full);
        sem_wait(&pail);
        sem_wait(&vat); //要先占水桶再占水缸，不然会死锁
        BLUE;
        printf("old monk %ld drink water from vat.There are %d water in vat.\n", gettid(), --a);
        sem_post(&vat);
        sem_post(&pail);
        sem_post(&empty);
    }
}

void *youngmonk()
{
    while (1)
    {
        sem_wait(&empty);
        sem_wait(&pail);
        sem_wait(&well);
        RED;
        printf("young monk %ld take some water from well.\n", gettid());
        sem_post(&well);
        sem_wait(&vat);
        RED;
        printf("young monk %ld put water into vat.There are %d water in vat.\n", gettid(), ++a);
        sem_post(&vat);
        sem_post(&pail);
        sem_post(&full);
    }
}

int main()
{
    pthread_t p1, p2, p3, p4, p5, p6;
    sem_init(&vat, 0, 1);
    sem_init(&well, 0, 1);
    sem_init(&empty, 0, 10);
    sem_init(&pail, 0, 3);
    sem_init(&full, 0, 0);
    pthread_create(&p1, NULL, oldmonk, NULL);
    pthread_create(&p2, NULL, oldmonk, NULL);
    pthread_create(&p3, NULL, youngmonk, NULL);
    pthread_create(&p4, NULL, youngmonk, NULL);
    pthread_create(&p5, NULL, youngmonk, NULL);
    pthread_create(&p6, NULL, youngmonk, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);
    pthread_join(p5, NULL);
    pthread_join(p6, NULL);
    CLOSE;
    return 0;
}