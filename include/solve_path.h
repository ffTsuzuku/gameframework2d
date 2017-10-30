#include "gf2d_vector.h"
//the maximum number of childeren a node can have is 4, since you can only move in the 4 cardinal directions
#define max_child 4

typedef struct Node
{
	struct Node *parent;
	Vector2D coordinate;
	struct Node  *child_nodes[max_child];
}Node;

typedef struct qNode
{
	struct Node *node;
	struct qNode *nxt_node;
}qNode;

typedef struct Path
{
	struct Path* prevCoordinate;
	Vector2D Coordinate;
	struct Path* nextCoordinate;
}path;


/**
* @brief Inserts A Node in queue, so you know to visit it
* @param node_queue is the queue to insert into 
* @param node is the node to insert into
* @return nothing
*/
void enqueue(struct qNode *node_queue, struct qNode *node);

/**
* @brief Inserts A Node's children. Makes Sure Vecotrs havent been visited/aren't walls
* @brief  Creates nodes for the children vectors, then gets their children
* @brief then queues them up
* @param node_queue is the queue to insert into
* @param node is the node whose children will be queued
* @return nothing
*/
void enqueueChildren(struct qNode *node_queue, struct qNode *visted, struct Node *node);

/**
* @brief Pulls A Node in queue, so you know to visit it
* @param node_queue is the queue to insert into
* @return pointer to the node that got popped
*/
Node *dequeue(struct qNode *node_queue);
/**
* @brief Gets the children of the current node, and adds it to the vectory array
* @param node_queue is the queue to insert into
* @return Pointer to node
*/
void get_children(Node *node);

/**
* @brief Does the actual finding of a path
* @param Start is the starting coordinate
* @param End the coordinate to end on
* @return dont know yet if need to return anything
*/
Vector2D* solve_path(Vector2D Start, Vector2D End);

/**
* @brief Check to see if we have reached the goal 
* @param node is the current node we are on
* @return either 1 or 0 based on if we reached the goal
*/
int checkDest(struct qNode *node);

/**
* @brief Get the childrenNodes, and queues them up
* @param node is the current node we are on
* @return Gets the children for a node
*/
void getChildren(struct Node *node);

/**
* @brief checks to see if you can walk on  the node or if its a wall
* @param node is the node to check
* @return Returns 0 if its a valid node, else returns 1.
*/
int validateNode(Vector2D coordinate);

/**
* @brief checks to see if the node has already been visted
* @param Visted is the list of visted nodes
* @param Node is the node needing to be checked
* @return Returns 1 if already visted else 0. 
*/
int searchVisited(struct qNode *Visted, struct Node *node);

/**
* @brief creates a qNode
* @param Node is the node to be associted with the qNode
* @return Pointer to qNode
*/
qNode* create_qNode(Node *node);

/**
* @brief creates a qNode
* @param Node is the node to be associted with the qNode
* @return Pointer to Node
*/
Node* create_Node(Node* parent, Vector2D coordinate);

/**
* @brief creates a queue for storing the correct path
* @param This will be the last nod in the queue, it will work bckwards using parents
* @return Pointer to Path queue
*/
path* construct_path(Node* pathNode);

void printQueue(qNode* queue);

qNode *copyQnode(qNode *queue);