#include <iostream>


struct qNode {
	unsigned pageNumber;
	qNode *prev;
	qNode *next;
};


struct queue {
	unsigned size;
	unsigned filled;
	qNode *front, *rear;
};

struct Hash {
	unsigned capacity;
	qNode **array;
};

qNode *createNode (unsigned pageNumber) {
	qNode *newnode = new qNode();
	newnode->pageNumber = pageNumber;
	newnode->prev = newnode->next = NULL;

	return newnode;
}

queue *createQueue( int NumberofFrames ) {
	queue *nqueue = new queue();

	nqueue->size = NumberofFrames;
	nqueue->front = nqueue->rear = NULL;
	nqueue->filled = 0;

	return nqueue;
}


Hash *createHash(int capacity) {
	Hash *hash = new Hash();
	hash->capacity = capacity;

	hash->array = new qNode*[capacity];

	for (int i=0;i<capacity;i++) {
		hash->array[i] = NULL;
	}

	return hash;
}

bool allFramesAdded(queue *Queue) {
	return ( Queue->filled == Queue->size);
}

bool isQueueEmpty(queue *Queue) {
	return (Queue->rear == NULL);
}

void deQueue(queue *Queue) {
	if(isQueueEmpty(Queue))
		return;

	if(Queue->front == Queue->rear) {
		Queue->front = NULL;
	}

	qNode *temp = Queue->rear;
	Queue->rear = Queue->rear->prev;

	if (Queue->rear)
		Queue->rear->next = NULL;

	delete temp;

	Queue->filled--;
}

void Enqueue( queue *Queue, Hash *hash, unsigned pageNumber ) {

	if(allFramesAdded(Queue)) {
		hash->array[Queue->rear->pageNumber] = NULL;
		deQueue(Queue);
	}

	qNode *temp = createNode(pageNumber);
	temp->next = Queue->front;

	if(isQueueEmpty(Queue))
		Queue->front = Queue->rear = temp;
	else {
		Queue->front->prev = temp;
		Queue->front = temp;
	}

	hash->array[pageNumber] = temp;
	Queue->filled++;
}

void referencePage( queue *Queue, Hash *hash, unsigned pageNumber ) {

	qNode *reqPage = hash->array[pageNumber];

	if(!reqPage) {
		Enqueue(Queue,hash,pageNumber);
	}
	else if( reqPage != Queue->front) {

		reqPage->prev->next = reqPage->next;
		if(reqPage->next)
			reqPage->next->prev = reqPage->prev;

		if(reqPage == Queue->rear) {
			reqPage->prev->next = NULL;
			Queue->rear = reqPage->prev;
		}
		reqPage->next = Queue->front;
		reqPage->prev = NULL;

		reqPage->next->prev = reqPage;

		Queue->front = reqPage;
	}
}


int main () {
    queue *q = createQueue( 4 );

    Hash* hash = createHash( 10 );

    referencePage( q, hash, 1);
    referencePage( q, hash, 2);
    referencePage( q, hash, 3);
    referencePage( q, hash, 1);
    referencePage( q, hash, 4);
    referencePage( q, hash, 5);

    printf ("%d ", q->front->pageNumber);
    printf ("%d ", q->front->next->pageNumber);
    printf ("%d ", q->front->next->next->pageNumber);
    printf ("%d ", q->front->next->next->next->pageNumber);

	return 0;
}
