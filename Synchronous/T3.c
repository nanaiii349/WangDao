#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include "color.h"

#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)

#define size 100
const int loop = 1000;
sem_t mutex, empty, odd, even;
int buffer[1000] = {0};
int index = 0;

void *produce()
{
    int i = 0;
    while (i++ < loop)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        int a = rand() + 1;
        buffer[index++] = a;
        BLUE;
        printf("produce put %10d into buffer.There are %3d item in buffer.\n", a, index);
        if (a % 2 == 0)
            sem_post(&even);
        else
            sem_post(&odd);
        sem_post(&mutex);
    }
    exit(0);
}

void *getodd()
{
    int i = 0;
    while (i++ < loop)
    {
        sem_wait(&odd);
        sem_wait(&mutex);
        RED;
        int cnt = 0;
        for (int j = 0; j < index; j++)
        {
            if (buffer[j] % 2 == 1)
            {
                cnt = 1;
                printf("getodd %10d from buffer.", buffer[j]);
                while (++j < index)
                {
                    buffer[j - 1] = buffer[j];
                    if (buffer[j] % 1 == 0)
                        cnt++;
                }
                printf("There are %3d odds in buffer.\n", cnt);
                index--;
                break;
            }
        }
        if (cnt == 0) //没有消费数据，但是使用了信号量
            printf("There are no odds in buffer.\n");
        sem_post(&mutex);
        sem_post(&empty);
    }
}

void *geteven()
{
    int i = 0;
    while (i++ < loop)
    {
        sem_wait(&even);
        sem_wait(&mutex);
        YELLOW;
        int cnt = 0;
        for (int j = 0; j < index; j++)
        {
            if (buffer[j] % 2 == 0 && buffer[j] != 0)
            {
                cnt = 1;
                printf("geteven %10d from buffer.", buffer[j]);
                while (++j < index)
                {
                    buffer[j - 1] = buffer[j];
                    if (buffer[j] % 2 == 0 && buffer[j] != 0)
                        cnt++;
                }
                printf("There are %3d evens in buffer.\n", cnt);
                index--;
                break;
            }
        }
        if (cnt == 0)
            printf("There are no evens in buffer.\n");
        sem_post(&mutex);
        sem_post(&empty);
    }
}

int main()
{
    pthread_t p1, p2, p3;
    sem_init(&mutex, 0, 1); //信号量初始值为1
    sem_init(&empty, 0, 100);
    sem_init(&odd, 0, 0);
    sem_init(&even, 0, 0);
    pthread_create(&p1, NULL, produce, NULL);
    pthread_create(&p2, NULL, getodd, NULL);
    pthread_create(&p3, NULL, geteven, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    CLOSE;
    return 0;
}