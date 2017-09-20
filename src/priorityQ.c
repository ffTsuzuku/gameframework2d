/*
This contains all the functions required for a priority queue. You can create, delete, delete max, delete min and insert.
*/
#include "priorityQ.h"

//Creates our Priority Queue, data will contain head of linked list.When one is inserted. NUll for now.
PriorityQueue *pq_new(size_t elementSize)
{
	PriorityQueue *pqueue = malloc(sizeof(pqueue));
	pqueue->data = NULL;
	pqueue->elementSize = elementSize;

	return pqueue;
}

void pq_insert(PriorityQueue *pq, void *data, int priority)
{
	//depth needed to know if inserting head node or subsequent node
	int depth = 0;
	Node* tmpHead = (Node*)pq->data;

	Node *newNode = malloc(sizeof(Node));
	newNode->data = data;
	newNode->priority = priority;
	newNode->previous = NULL;
	newNode->next = NULL;

	while (tmpHead->next != NULL){
		tmpHead = tmpHead->next;
		depth++;
	}
	//If you're creating head node, your depth inside a linked list will be 0, so previous node wont exist.
	if (depth != 0)
		newNode->previous = tmpHead;
	if (depth == 0)
		newNode->previous = NULL;
	tmpHead->next = newNode;
}

void pq_delete(PriorityQueue *pq)
{

	if (pq->data != NULL){
		Node *delNode = pq->data;
		pq->data = delNode->next;

		//Need to free both Data and Node since both were mallocd
		free(delNode->data);
		free(delNode);
	}
	else{
		printf("Your Priority Queue has not been Malloced");
	}
}

/*
Find the biggest priority, return its value. And delete it. 
*/
void *pq_delete_max(PriorityQueue *pq)
{
	Node *maxP = pq->data;
	Node* tmpHead = ((Node*)pq->data)->next;

	while (tmpHead->next){
		if (maxP->priority < tmpHead->priority){
			maxP = tmpHead;
			tmpHead = tmpHead->next;
		}
	}
	//Set the previous Node's Next equal to the Max node's next. Since we're deleting. 
	(maxP->previous)->next = maxP->next;
	//should we do this in main. or store value in a new int * and then free
	//free(maxP);
	return &(maxP->data);
}

void *pq_delete_min(PriorityQueue *pq){
	Node *minP = pq->data;
	Node* tmpHead = ((Node*)pq->data)->next;

	while (tmpHead->next){
		if (minP->priority > tmpHead->priority){
			minP = tmpHead;
			tmpHead = tmpHead->next;
		}
	}
	//Set the previous Node's Next equal to the Max node's next. Since we're deleting. 
	(minP->previous)->next = minP->next;

	//should we do this in main. or store value in a new int * and then free
	//free(minP);
	return &(minP->data);
}
