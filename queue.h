#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdlib.h>

typedef struct node {
	int data;
	struct node *next;
}Node;

typedef struct queue {
	Node *head, *tail;
	int size;
}*Queue;

Queue initQueue(int data);
Node *initNode(int data);
Queue enqueue(Queue queue, int data);
Queue dequeue(Queue queue);
int first(Queue queue);
int isEmptyQueue(Queue queue);
Node *freeNode(Node *node);
Queue freeQueue(Queue queue);

#endif /* QUEUE_H */