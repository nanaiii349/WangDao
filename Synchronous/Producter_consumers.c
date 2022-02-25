/*************************************************************************
	> File Name: Pro_consumers.h
	> Author: NANAIII
	> Mail: luotianyou7056@163.com 
	> Created Time: Sat Sep 11 09:10:47 2021
 ************************************************************************/

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
int capacity = 0;
sem_t mutex, empty, full;

void *producer(void *arg)
{
	int i = 0;
	while (i < loop)
	{
		i++;
		sem_wait(&empty);
		sem_wait(&mutex);
		RED;
		printf("producer %ld add an item to buffer.There are %d items in buffer.\n", gettid(), ++capacity);
		sem_post(&mutex);
		sem_post(&full);
	}
}
void *consumer(void *arg)
{
	int i = 0;
	while (i < loop)
	{
		i++;
		sem_wait(&full);
		sem_wait(&mutex);
		BLUE;
		printf("consumer %ld remove an item from buffer.There are %d items in buffer.\n", gettid(), --capacity);
		sem_post(&mutex);
		sem_post(&empty);
	}
}

int main(int argc, char *argv[])
{
	pthread_t p1, p2, p3, p4;
	sem_init(&mutex, 0, 1);	   //信号量初始值为1
	sem_init(&empty, 0, size); //信号量初始值为1
	sem_init(&full, 0, 0);
	pthread_create(&p1, NULL, producer, NULL);
	pthread_create(&p2, NULL, consumer, NULL);
	pthread_create(&p3, NULL, consumer, NULL);
	pthread_create(&p4, NULL, consumer, NULL);
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	pthread_join(p3, NULL);
	pthread_join(p4, NULL);
	CLOSE;
	return 0;
}
