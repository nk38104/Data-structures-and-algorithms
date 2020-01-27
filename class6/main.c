#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CAPACITY 10000

typedef struct _Node{
	int priority;
	void* fnc;
}Node;

typedef struct _Queue{
	int top;
	Node* nodeArray;
}Queue;

void print_queue(Queue*);
Queue* initQueue();
Node* create_node(int);
void insert_node(Queue*, Node*);
void swap_nodes(int*, int*);
void fix_bottom_to_top(Queue*, int);
void fix_top_to_bottom(Queue*, int);
void delete_queue(Queue*);

int main()
{
	srand(time(NULL));
	Queue* queue = initQueue();

	for (int i = 1; i < 20; i++) {
		Node* node = create_node(i); 
		insert_node(queue, node);
	}
	print_queue(queue);
	while (queue->top > 0){
		delete_queue(queue);
	}
	print_queue(queue);

	free(queue->nodeArray);
	free(queue);
	return 0;
}

void print_queue(Queue* que) {
	for (int i = 0; i < que->top; i++)
		printf("%d  ", que->nodeArray[i].priority);
	putchar('\n');
	if (que->top == 0)
		printf("Queue empty!\n");
}

Queue* initQueue() {
	Queue* que = (Queue*)malloc(sizeof(Queue));
	if (!que) return 0;

	que->top = 0;
	que->nodeArray = (Node*)malloc(CAPACITY * sizeof(Node));

	return que;
}

Node* create_node(int priority) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (!newNode) return 0;

	newNode->priority = priority;

	return newNode;
}

void insert_node(Queue* que, Node* nodePriority) {
	if (que->top == CAPACITY) {
		printf("Queue is full!\n");
		return;
	}	
	que->nodeArray[que->top].priority = nodePriority->priority;
	fix_bottom_to_top(que, que->top);
	(que->top)++;
}

void swap_nodes(int* parent, int* child) {
	int temp = *parent;
	*parent = *child;
	*child = temp;
}

void fix_bottom_to_top(Queue* que, int child) {
	if (child == 0) return;

	int parent = (child - 1) / 2;

	if (que->nodeArray[parent].priority < que->nodeArray[child].priority) {
		swap_nodes(&que->nodeArray[parent].priority, &que->nodeArray[child].priority);
	}
	fix_bottom_to_top(que, parent);
}

void fix_top_to_bottom(Queue* que, int parent) {
	if ((parent + 1) >= que->top) return;

	int leftChild = (2 * parent) + 1, rightChild = leftChild + 1;

	if (leftChild > que->top) { leftChild = parent; }
	if (rightChild > que->top) { rightChild = parent; }

	if (que->nodeArray[leftChild].priority > que->nodeArray[rightChild].priority && leftChild != parent) {
		swap_nodes(&que->nodeArray[parent].priority, &que->nodeArray[leftChild].priority);
		fix_top_to_bottom(que, leftChild);
	}
	else if (rightChild != parent) {
		swap_nodes(&que->nodeArray[parent].priority, &que->nodeArray[rightChild].priority);
		fix_top_to_bottom(que, rightChild);
	}
}

void delete_queue(Queue* que) {
	swap_nodes(&que->nodeArray[0].priority, &que->nodeArray[que->top - 1].priority);
	que->top--;
	que->nodeArray[que->top].priority = 0;
	fix_top_to_bottom(que, 0);
}
