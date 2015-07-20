#if 1

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

#define READERS 3
#define WRITERS 3

sem_t wrt, mutex;
int readCount = 0;

void *readers(void *arg);
void *writers(void *arg);

int main()
{

	sem_init(&wrt, 0, 2);
	sem_init(&mutex, 0, 2);

	pthread_t read[READERS];
	pthread_t write[WRITERS];

	for (int j = 0; j<READERS; j++)
		pthread_create(&read[j], NULL, readers, (void*)&j);

	for (int i = 0; i<WRITERS; i++)
		pthread_create(&write[i], NULL, writers, (void*)&i);

	for (int k = 0; k<READERS; k++)
		pthread_join(read[k], NULL);

	for (int i = 0; i<WRITERS; i++)
		pthread_join(write[i], NULL);

	return 0;
}

void *readers(void *arg)
{
	int x = *(int*)arg;

	printf("Reader %d is trying\n", x);
	sem_wait(&mutex);
	readCount++;
	if (readCount == 1)
	{
		printf("Reading %d \n", x);
		sem_wait(&wrt);
	}
	sem_post(&mutex);
	sem_wait(&mutex);
	readCount--;
	if (readCount == 0)
	{
		printf("Reader %d is leaving\n", x);
		sem_post(&wrt);
	}
	sem_post(&mutex);

	pthread_exit(NULL);
}

void *writers(void *arg)
{
	int x = *(int*)arg;
	printf("Writer %d is trying \n", x);
	sem_wait(&wrt);
	printf("Writing %d \n", x);
	printf("Writer %d is leaving \n", x);
	sem_post(&wrt);

	pthread_exit(NULL);
}

#endif
