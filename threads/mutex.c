#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>


int counter=0;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void *functionC() {
	pthread_mutex_lock(&mutex1);
	counter++;
	printf("%d\n",counter);
	pthread_mutex_unlock(&mutex1);
}


int main() {
	pthread_t th1, th2;
	int r;

	if(r = pthread_create(&th1, NULL, functionC, NULL)) {
		printf("th1 create fail : %d\n",r);
		exit(EXIT_FAILURE);
	}

	if(r = pthread_create(&th2, NULL, functionC, NULL)) {
		printf("th2 create fail : %d\n",r);
		exit(EXIT_FAILURE);
	}

	pthread_join(th1,NULL);
	pthread_join(th2,NULL);

	exit(EXIT_SUCCESS);

	return 0;
}
