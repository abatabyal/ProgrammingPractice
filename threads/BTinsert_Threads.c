#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
//#include <

#define THREADS 10

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

struct tree {
    long data;
    struct tree *left;
	struct tree *right;
};

struct tree *root = NULL;



struct tree *newnode(long data) {
	struct tree *newnode = (struct tree*)malloc(sizeof(struct tree));
	newnode->data = data;
	newnode->left = NULL;
	newnode->right = NULL;

	return newnode;
}

void* insert(void *dat) {

	long data = (long)dat;
	printf("thread %ld is inserting a node in BST with value %ld\n",pthread_self(),data);
	struct tree *newn = newnode(data);

	if(!(root)) {
		pthread_mutex_lock(&mtx);
		root = newn;
		pthread_mutex_unlock(&mtx);
		pthread_exit( (void*)1);
	}

	struct tree *temp = root;
	while(temp) {
		if (temp->data > data)  {
			if(!temp->left) {
				pthread_mutex_lock(&mtx);
				temp->left = newn;
				pthread_mutex_unlock(&mtx);
				pthread_exit( (void*)1);
			}
			printf("%ld is traversing\n",pthread_self());
			temp = temp->left;
		}
		else if ( temp->data < data ) {
			if(!temp->right) {
				pthread_mutex_lock(&mtx);
				temp->right = newn;
				pthread_mutex_unlock(&mtx);
				pthread_exit( (void*)1);
			}
			printf("%ld is traversing\n",pthread_self());
			temp = temp->right;
		}
		else {
			pthread_exit( (void*)0);
		}
	}
    pthread_exit( (void*)0);
}

void inorder(struct tree *root) {
	if(!root)
		return;

	if(root) {
		inorder(root->left);
		printf("%ld ",root->data);
		inorder(root->right);
	}
}

int main () {
	pthread_t thread[THREADS];

	long r,t;
	void *status;


	for ( t = 0; t<THREADS;t++) {
		//srand(time(NULL));
		r = pthread_create(&thread[t],NULL,insert,(void*)(rand()%10));
		if(r) {
			printf("thread not created\n");
			exit(EXIT_FAILURE);
		}
	}

	for(t=0;t<THREADS;t++) {
		pthread_join(thread[t],&status);
		printf("%ld thread exited with status %ld\n",t,(long)status);
	}

	printf("inorder of BST :\n");
	struct tree *temp = root;
	inorder(temp);

	pthread_exit(EXIT_SUCCESS);
}
