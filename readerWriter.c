#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>

sem_t r, w;
int rdcnt=0;
FILE *fptr;

void *writer(void* arg)
{
	sem_wait(&w);
	printf("\nWriter. \tid = %lu \n", pthread_self());
	fptr = fopen("f9.txt", "a+");
	fprintf(fptr, "Hi, This is Writer : %lu \n", pthread_self());
	fclose(fptr);
	sem_post(&w);
	sleep(3);
}

void *reader(void* arg)
{
	sem_wait(&r);
	rdcnt ++;
	if(rdcnt == 1)
		sem_wait(&w);
	sem_post(&r);
	
	printf("\n\tReader. \tid = %lu \n", pthread_self());
	fptr = fopen("f9.txt", "r");
	char myString[100];
	while(fgets(myString, sizeof(myString), fptr) != NULL)
		printf("%s", myString);
	fclose(fptr);
	sem_wait(&r);
	rdcnt --;
	if(rdcnt == 0)
		sem_post(&w);
	sem_post(&r);
	//sleep(3);
}

void main()
{
	pthread_t wrt[4], rdr[4];
	sem_init(&r, 0, 1);
	sem_init(&w, 0, 1);
	fptr = fopen("f9.txt", "w");
	fclose(fptr);
	
	for(int i=0; i<4; i++)
		pthread_create(&wrt[i], NULL, writer, NULL);
	for(int i=0; i<4; i++)
		pthread_create(&rdr[i], NULL, reader, NULL);
	
	for(int i=0; i<4; i++)
		pthread_join(wrt[i], NULL);
	for(int i=0; i<4; i++)
		pthread_join(rdr[i], NULL);
}


//gcc readerWriter.c -lpthread








