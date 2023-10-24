#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>

int buffer[5], in =0, out =0;
sem_t e, f, s;

void *producer(void* arg)
{
	sem_wait(&e);
	sem_wait(&s);
	int data = rand();
	data = data % 100;
	buffer[in] = data;
	printf("Production entered %d value. \tid = %lu \n", buffer[in], pthread_self());
	in = (in+1)%5; 
	sem_post(&s);
	sem_post(&f);
	sleep(3);
}

void *consumer(void * arg)
{
	int conti, data;
	do{
		sem_wait(&f);
		sem_wait(&s);
		data = buffer[out];
		out = (out+1)%5;
		printf("\tProduct out with data : %d \tid = %lu \n", data, pthread_self());
		sem_post(&s);
		sem_post(&e);
		sem_getvalue(&e, &conti);
	} while(conti != 5);
}

void main()
{
	pthread_t ptid[5], ctid;
	sem_init(&e, 0, 5);
	sem_init(&f, 0, 0);
	sem_init(&s, 0, 1);
	
	pthread_create(&ctid, NULL, consumer, NULL);
	for(int i=0; i<5; i++)
	{
		pthread_create(&ptid[i], NULL, producer, NULL);
	}
	
	for(int i=0; i<5; i++)
	{
		pthread_join(ptid[i], NULL);
	}
	pthread_join(ctid, NULL);
}
