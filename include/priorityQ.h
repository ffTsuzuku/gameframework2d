#ifndef __priorityQ_H__
#include<stdio.h>
#include<stdlib.h>
typedef struct Node Node;

typedef struct{
	void *data;
	size_t numElements;
	size_t elementSize;
}PriorityQueue;

struct Node{
	void* data;
	int priority;
	Node *previous;
	Node *next;
};


PriorityQueue *pq_new(size_t elementSize);
//Delete oldest member of the list
void pq_delete(PriorityQueue *pq);
//Delete Index with biggest priority
void *pq_delete_max(PriorityQueue *pq);
//Delete index with lowest priorty
void *pq_delete_min(PriorityQueue *pq);
//Insert into the queue
void pq_insert(PriorityQueue *pq, void *data, int priority);

#endif
