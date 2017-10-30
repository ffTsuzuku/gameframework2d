#include <stdlib.h>
#include <stdio.h>
#include "solve_path.h"
#include "tilemap.h"
#include <string.h>

struct Node* create_Node(struct Node* parent, Vector2D coordinate)
{
	struct Node* node = (struct Node*) malloc(sizeof(struct Node));
	node->parent = parent;
	node->coordinate = coordinate;
	memset(node->child_nodes, '\0', sizeof(node->child_nodes));

	return node;
}

qNode* create_qNode(struct Node *node)
{
	struct qNode *qnode = (qNode*) malloc(sizeof(qNode));
	if (!qnode){ printf("Create_qNode failed to malloc qNode\n"); }
	qnode->node = node;
	qnode->nxt_node = NULL;

	return qnode;
}

void enqueue(qNode **node_queue, qNode *node){
	if (!node){ printf("Failed to allocate node\n"); }
	if (!node_queue){ printf("Failed to allocate node_queue\n"); }

	struct qNode *tmpHead = *node_queue;
	struct qNode *prevHead = tmpHead;
	
	if (tmpHead == NULL){
		*node_queue = node;
	}
	else{
		while (tmpHead){
			prevHead = tmpHead;
			tmpHead = tmpHead->nxt_node;
		}
		prevHead->nxt_node = node;
	}
}

void enqueueChildren(struct qNode **node_queue,struct qNode **visited,  struct Node *node)
{
	int i, valid, visitedVal;
	i = valid = 0;

	while (i < max_child){
		valid = validateNode(node->child_nodes[i]->coordinate);
		visitedVal = searchVisited(*visited, node->child_nodes[i]);

		if (valid ==0 && !visitedVal){
			struct Node *enqueueNode = create_Node(node, node->child_nodes[i]->coordinate);
			struct qNode *enqueueQNode = create_qNode(enqueueNode);
			enqueue(&(*node_queue), enqueueQNode);
		}
		i++;
	}
}

Node* dequeue(qNode** visited, qNode **qnode)
{
	if ((*qnode) == NULL){ return NULL; }

	qNode *returnNode;
	returnNode = copyQnode (*qnode); 
	enqueue(&(*visited), returnNode);
	
	if (!(*qnode)->nxt_node){
		*qnode = NULL;
	}
	else{
		*qnode = (*qnode)->nxt_node;
	}
	return returnNode->node;
}

void getChildren(Node *node)
{
	float x, y;
	x = node->coordinate.x;
	y = node->coordinate.y;
	
	//Child 1
	node->child_nodes[0] = malloc(sizeof(Node));
	node->child_nodes[0]->coordinate.x = x - 1;
	node->child_nodes[0]->coordinate.y = y;
	node->child_nodes[0]->parent = node;

	//Child 2
	node->child_nodes[1] = malloc(sizeof(Node));
	node->child_nodes[1]->coordinate.x = x + 1;
	node->child_nodes[1]->coordinate.y = y;
	node->child_nodes[1]->parent = node;
	//Child 3
	node->child_nodes[2] = malloc(sizeof(Node));
	node->child_nodes[2]->coordinate.x = x;
	node->child_nodes[2]->coordinate.y = y - 1;
	node->child_nodes[2]->parent = node;
	//Child 4
	node->child_nodes[3] = malloc(sizeof(Node));
	node->child_nodes[3]->coordinate.x = x;
	node->child_nodes[3]->coordinate.y = y + 1;
	node->child_nodes[3]->parent = node;
}

int validateNode(Vector2D coordinate)
{
	//Do Stuff
	int i, x, y, row;
	char valid;
	char *file = "levels/tilemap.map";
	TileMap *mapObj;
	mapObj = tilemap_load(file);
	
	x = coordinate.x;
	y = coordinate.y;
	row = mapObj->width * y;

	valid =  *((mapObj->map) + row + x);
	
	//printf("Valid Value: %d", valid - '0');
	
	return valid - '0';
}
    
int searchVisited(qNode *Visited, Node *node)
{
	if (!Visited->node){ return 0; }

	int nodeX, nodeY;
	qNode *tmpNode = Visited;
	nodeX = node->coordinate.x;
	nodeY = node->coordinate.y;

	while (tmpNode->nxt_node != NULL){
		if (tmpNode->node->coordinate.x == nodeX &&
			tmpNode->node->coordinate.y == nodeY)
			return 1;
		else
			tmpNode = tmpNode->nxt_node;
	} 
	return 0;
}

int checkDest(Node *node, Vector2D End)
{
	if (node->coordinate.x == End.x &&
		node->coordinate.y == End.y)
		{return 1;}

	else
		{return 0;}
	
}

path* construct_path(Node* pathNode)
{
	int i = 0;
	path *Path;
	Path = (path *) malloc(sizeof(path));

	Path->Coordinate = pathNode->coordinate;
	Path->nextCoordinate = NULL;
	
	path *tmpHead = Path;
	Node *tmpNode = pathNode;

	while(tmpNode->parent){
		//Get the next Vector2D
		tmpNode = tmpNode->parent;
		//Malloc space for  preCoord path
		tmpHead->prevCoordinate = (path *)malloc(sizeof(path));
		//Set the prevCoordinates Vector2D
		tmpHead->prevCoordinate->Coordinate = tmpNode->coordinate;
		tmpHead->prevCoordinate->nextCoordinate = tmpHead;
		tmpHead = tmpHead->prevCoordinate;
	}

	return tmpHead;
}

void printQueue(qNode* queue)
{
	if (!queue){ return; }

	qNode *tmpHead = queue;
	printf("{");
	while (tmpHead){
		printf("{");
		printf("%f:%f}", tmpHead->node->coordinate.x, tmpHead->node->coordinate.y);
		tmpHead = tmpHead->nxt_node;
	}
	printf("}\n");
}

qNode *copyQnode(qNode *queue)
{
	qNode *newNode = (qNode *) malloc(sizeof(qNode));
	newNode->node = queue->node;
	newNode->nxt_node = NULL;

	return newNode;
}

Vector2D* solve_path(Vector2D Start, Vector2D End)
{
	int solved = 0, i=0;
	
	struct Node *Origin, *testNode;
	qNode *node_queue, *visited_queue;
	path *Path; 

	Vector2D finalPath[200];
	visited_queue = NULL;
	//Set up the Root Node of the Tree
	Origin = create_Node(NULL, Start);
	if (!Origin){ printf("Failed to allocate Origin\n");}

	//	getChildren(Origin);

	//Set up the queue of nodes to be visted
	node_queue = create_qNode(Origin);
	if (!node_queue){ printf("Failed to allocate nodeQueue\n"); } 
	
	//Node *test = dequeue(&node_queue);
	//printf("Dequeue Test. X: %f Y: %f\n", test->coordinate.x, test->coordinate.y);

	//printf("X: %f Y: %f\n", node_queue->node->coordinate.x, node_queue->node->coordinate.y);
	//printf("Visted Result: %d\n", searchVisited(node_queue,Origin));
	//printf("Validate Node Result: %d\n", validateNode(Start));	

	//Set up a queue that tracks visted nodes 
	//visited_queue = (qNode*) malloc(sizeof(qNode));
	//visited_queue->node = NULL;
	//visited_queue->nxt_node = NULL;

	//enqueueChildren(node_queue, visited_queue, Origin);
	//Node *test = dequeue(&node_queue);
	//printf("Dequeue Test. X: %f Y: %f\n", test->coordinate.x, test->coordinate.y);

	while (node_queue && !solved){
		//printQueue(node_queue);
		testNode = dequeue(&visited_queue,&node_queue);
		//printf("X: %f Y: %f\n", testNode->coordinate.x, testNode->coordinate.y);
		solved = checkDest(testNode,End);

		if (solved){
			printf("Got it\n");
			Path = construct_path(testNode);
			
			i = 0;
			while (Path){
				//printf("{%f,%f}\n",Path->Coordinate.x,Path->Coordinate.y);
				finalPath[i] = Path->Coordinate;
				Path = Path->nextCoordinate;
				i++;
			}

		}
		else{
			//Queue up the childeren of the current node
			getChildren(testNode);
			enqueueChildren(&node_queue, &visited_queue, testNode);
		}
	}
	return finalPath;
}