#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>


#define BUFF_SIZE   5    	/* total number of slots */
#define NP          3		/* total number of producers */
#define NC          3		/* total number of consumers */
#define NITERS      4		/* number of items produced/consumed */

typedef struct {
    int buf[BUFF_SIZE];   /* shared var */
    int in;         	  /* buf[in%BUFF_SIZE] is the first empty slot */
    int out;        	  /* buf[out%BUFF_SIZE] is the first full slot */
    sem_t full;     	  /* keep track of the number of full spots */
    sem_t empty;    	  /* keep track of the number of empty spots */
    sem_t mutex;    	  /* enforce mutual exclusion to shared data */
} sbuf_t;

sbuf_t shared;

void *Producer(void *arg)
{
    int i, item;
    long index;

    index = (long)arg;

    for (i=0; i < NITERS; i++) {

        item = i;

        sem_wait(&shared.empty);
        sem_wait(&shared.mutex);
        shared.buf[shared.in] = item;
        shared.in = (shared.in+1)%BUFF_SIZE;
        printf("[P%ld] Producing %d ...\n", index, item); fflush(stdout);
        sem_post(&shared.mutex);
        sem_post(&shared.full);

        if (i % 2 == 1) sleep(1);
    }
    return NULL;
}

void *Consumer(void *arg)
{
 	int i, index, item;

	index = (long)arg;

	for(i = 0; i < NITERS; i++) {
		sem_wait(&shared.full);
		sem_wait(&shared.mutex);
		item = shared.buf[shared.out];
		shared.out = (shared.out+1)%BUFF_SIZE;
		printf("------> [C%ld] consumed %d\n",index,item); fflush(stdout);
		sem_post(&shared.mutex);
		sem_post(&shared.empty);
		if (i % 2 == 0) sleep(1);
	}
	return NULL;
}

int main()
{
    pthread_t idP, idC;
    long index;

    sem_init(&shared.full, 0, 0);
    sem_init(&shared.empty, 0, BUFF_SIZE);

    sem_init(&shared.mutex, 0, 1);

    for (index = 0; index < NP; index++) {
       pthread_create(&idP, NULL, Producer, (void*)index);
    }

    for (index = 0; index < NC; index++) {
       pthread_create(&idC, NULL, Consumer, (void*)index);
    }

    pthread_exit(NULL);
}
