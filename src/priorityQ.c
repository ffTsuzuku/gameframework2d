/*
This contains all the functions required for a priority queue. You can create, delete, delete max, delete min and insert.
*/
#include "priorityQ.h"
#include<stdlib.h>
#include<stdio.h>

//Creates our Priority Queue, data will contain head of linked list.When one is inserted. NUll for now.
PriorityQueue *pq_new(size_t elementSize)
{
  PriorityQueue *pqueue = malloc(sizeof(pqueue));
  pqueue->data = NULL;
  //pqueue->elementSize = elementSize;
  
  return pqueue;
}

void pq_insert(PriorityQueue *pq, void *data, int priority)
{
  //depth needed to know if inserting head node or subsequent node
  int depth = 0;
  Node* tmpHead = (Node*)pq->data;
  Node* tail = (Node*)pq->data;
  
  if(!pq){
    printf("ERROR:Your priority Queue was never mallocd\n");
    return;
  }
  
  //create the node to be inserted
  Node *newNode = malloc(sizeof(Node));
  newNode->data = data;
  newNode->priority = priority;
  newNode->previous = NULL;
  newNode->next = NULL;
  
  //printf("%d\n",*(int*)newNode->data);
  
  while(tmpHead){
    tail = tmpHead;
    tmpHead = tmpHead->next;
    depth++;  
  }

//If you're creating head node, your depth inside a linked list will be 0, so previous node wont exist.
  if (depth){
    newNode->previous = tail;
    tail->next = newNode;
  }
  else{
    newNode->previous = NULL;
    pq->data = newNode;
  }
}

void pq_delete(PriorityQueue *pq)
{
  
  if (pq->data){
    Node *delNode = pq->data;
    pq->data = delNode->next;
    
    //Need to free both Data and Node since both were mallocd
    free(delNode);
  }
  else{
    printf("ERROR:Attempting to Delete from an Empty Queue\n");
    printf("The program will now gracefully terminate\n");
    exit(-1);
  }
}

/*
  Find the biggest priority, return its value. And delete it. 
*/
void *pq_delete_max(PriorityQueue *pq)
{
  void *value;
  Node *maxP = NULL;
  Node *currNode;
  
  if(pq->data){
    maxP = pq->data;
    currNode=maxP->next;
    
    //need to check both, incase there is only 1 node in the list
    while(currNode){
      if(maxP->priority < currNode->priority){
	maxP = currNode;
	currNode=currNode->next;
      }
      else{
	currNode = currNode->next;
      }
    }
  }
  
  else{
    printf("ERROR:Attempting to get Max From Empty Queue\n");
    printf("The program will now gracefully terminate\n");
    exit(-1);
  }

  //Delete the node
  //Check if this is the head node. 
  if ((Node *)(maxP->previous)){
	  if (maxP->next){
		  ((Node *)(maxP->previous))->next = maxP->next;
		  ((Node *)(maxP->next))->previous = maxP->previous;
		  return maxP->data;
	  }
	  else{
		  // printf("New End Node: %d\n", (int*)((Node *)(minP->previous))->data);
		  ((Node *)(maxP->previous))->next = NULL;
		  return maxP->data;
	  }
  }
  //since its the head node, we need to set a new head
  else{
    if(maxP->next){
      pq->data = maxP->next;
      ((Node*)(pq->data))->previous = NULL;
      value = maxP->data;
      free(maxP);
      return value;
    }
    else{
      pq->data = NULL;
      value = maxP->data;
      free(maxP);
      return value;
    }
  }
}

void *pq_delete_min(PriorityQueue *pq){
  Node *minP = NULL;
  Node *currNode;
  
  if(pq->data){
    minP = pq->data;
    currNode=minP->next;
    
    while(currNode){
      if(minP->priority > currNode->priority){
		minP = currNode;
		currNode=currNode->next;
      }
      else{
		currNode = currNode->next;
      }
    }
  }
  
  else{
    printf("ERROR:Attempting to get Min From Empty Queue\n");
    printf("The program will now gracefully terminate\n");
    exit(-1);
  }

  //Delete the node
  //Check if this is the head or subnode. 
  if((Node *)(minP->previous)){
	  if (minP->next){
		  ((Node *)(minP->previous))->next = minP->next;
		  ((Node *)(minP->next))->previous = minP->previous;
		  return minP->data;
	  }
	  else{
		 // printf("New End Node: %d\n", (int*)((Node *)(minP->previous))->data);
		  ((Node *)(minP->previous))->next = NULL;
		  return minP->data;
	  }
  }
  //since its the head node, we need to set a new head
  else{
    if(minP->next){
      pq->data = minP->next;
      ((Node*)(pq->data))->previous = NULL;
      return minP->data;
    }
    else{
      pq->data = NULL;
      return minP->data;
    }
  }
}

