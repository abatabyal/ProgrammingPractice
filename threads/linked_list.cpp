#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>

using namespace std;

struct node {
	int data;
	node *next;
	pthread_mutex_t lock;
};

pthread_rwlock_t _rwlock;


node *nnode(int data) {
	node *nnode = new node();
	nnode->data = data;
	nnode->next = NULL;
	pthread_mutex_t temp = PTHREAD_MUTEX_INITIALIZER;
	nnode->lock = temp;
	return nnode;
}

/*
void insertHead(node **head, int data) {
	node *newnode = newnode(data);

	if(!(*head)) {
		*head = newnode;
		return;
	}
	newnode->next = *head;
	*head = newnode;
}
*/


void sortedInsert(node **head, int data) {
	node *newnode = nnode(data);

	pthread_rwlock_rdlock(&_rwlock);			//two level of locking : one for read-write lock
	if(!*head || (*head)->data >= data ) {
		if(*head) {
			pthread_mutex_lock(&(*head)->lock);			//per-node lock
		}
		newnode->next = *head;
		if(*head) {
			pthread_mutex_unlock(&(*head)->lock);
		}
		*head = newnode;
		return;
	}
	else {
		node *temp = *head;
		while( temp->next && temp->next->data > data) {
			temp = temp->next;
		}

		pthread_mutex_lock(&temp->lock);
		newnode->next = temp->next;
		temp->next = newnode;
		pthread_mutex_unlock(&temp->lock);
	}
	pthread_rwlock_unlock(&_rwlock);
}


int main() {

	pthread_rwlock_init(&_rwlock,NULL);

	bool lock(false);
	bool old = __sync_val_compare_and_swap(&lock, false, true);			//CAS implementation in GCC
	cout <<"new :"<< lock << endl;
	cout <<"old :" << old<<endl;

	pthread_rwlock_destroy(&_rwlock);
}
