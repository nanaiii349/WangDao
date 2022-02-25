/*************************************************************************
	> File Name: Writer_readersII.c
	> Author: NANAIII
	> Mail: luotianyou7056@163.com 
	> Created Time: Sun Sep 12 10:03:34 2021
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
sem_t mutex, rw, tag;

void *writer(void *arg)
{
	int i = 0;
	while (i++ < loop)
	{
		sem_wait(&tag);
		sem_wait(&rw);
		RED;
		printf("WRITER %ld start to write something in buffer.\n", gettid());
		printf("WRITER %ld Done.\n", gettid());
		sem_post(&rw);
		sem_post(&tag);
	}
}
void *reader(void *arg)
{
	int i = 0;
	while (i++ < loop)
	{
		sem_wait(&tag);
		sem_wait(&mutex);
		if (capacity++ == 0)
			sem_wait(&rw);
		sem_post(&mutex);
		sem_post(&tag);
		BLUE;
		printf("READER %ld start to read something in buffer.There are %5d readers are reading.\n", gettid(), capacity);
		sem_wait(&mutex);
		if (--capacity == 0)
			sem_post(&rw);
		printf("READER %ld Done.\n", gettid());
		sem_post(&mutex);
	}
}

int main(int argc, char *argv[])
{
	pthread_t p1, p2, p3, p4, p5;
	sem_init(&tag, 0, 1);
	sem_init(&mutex, 0, 1); //信号量初始值为1
	sem_init(&rw, 0, 1);	//信号量初始值为1
	pthread_create(&p1, NULL, writer, NULL);
	pthread_create(&p2, NULL, writer, NULL);
	pthread_create(&p3, NULL, writer, NULL);
	pthread_create(&p4, NULL, reader, NULL);
	pthread_create(&p5, NULL, reader, NULL);
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	pthread_join(p3, NULL);
	pthread_join(p4, NULL);
	pthread_join(p5, NULL);
	CLOSE;
	return 0;
}
