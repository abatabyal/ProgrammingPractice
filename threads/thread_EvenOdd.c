#include <stdio.h>
#include <pthread.h>

#define MAX 50

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int count=0;
int flag=0;

void* even(void *arg) {
    while(count < MAX) {
    	pthread_mutex_lock(&mutex);
		if(flag == 1)
			pthread_cond_wait(&cond,&mutex);
		printf("%d ",count);
		flag=1;
		count++;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}

void *odd(void *arg) {
	while(count < MAX) {
		pthread_mutex_lock(&mutex);
		if(flag == 0)
			pthread_cond_wait(&cond,&mutex);
		printf("%d ",count);
		flag=0;
		count++;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}

int main() {
	pthread_t th1;
	pthread_t th2;

	int r;

	r = pthread_create(&th1,NULL,even,NULL);
	r = pthread_create(&th2,NULL,odd,NULL);

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);

	pthread_exit(NULL);
//	exit(0);
}
