#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>


#define NTHREADS 10

int counter=0;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void *functionC(void *arg) {

    pthread_mutex_lock(&mutex1);
	counter++;
	printf("thread id : %ld and counter %d\n",pthread_self(), counter);
	pthread_mutex_unlock(&mutex1);
    return NULL;
}


int main() {
	pthread_t th[NTHREADS];
	int r;

	for(int i=0;i<NTHREADS;i++) {
		if((r = pthread_create(&th[i], NULL, functionC, NULL))) {
			printf("th%d create fail : %d\n",i,r);
			exit(EXIT_FAILURE);
		}
	}

	for(int i=0;i<NTHREADS;i++) {
		pthread_join(th[i],NULL);
	}

	printf("final value of counter : %d\n",counter);

    return 0;
}
