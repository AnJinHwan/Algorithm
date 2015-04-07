#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE (!TRUE)

#define SIZE_QUEUE	100

typedef int EType;
typedef struct queue Queue;

struct queue
{
	int front;
	int rear;
	EType elems[SIZE_QUEUE];
};

void initQueue(Queue* queue);
int isEempty(Queue* queue);
int isFull(Queue* queue);
int enequeue(Queue* queue, EType data);
int dequeue(Queue* queue, EType *data);
void printQueue(Queue* queue);

int main(int argc, char *argv[])
{
	EType val;
	Queue queue;
	initQueue(&queue);

	enequeue(&queue, 10);
	enequeue(&queue, 20);
	enequeue(&queue, 30);
	dequeue(&queue, &val);
	

	return 0;
}

void initQueue(Queue* queue)
{
	queue->front = queue->rear = -1;
	memset(queue->elems, 0, sizeof(EType) * SIZE_QUEUE);
}

int isEempty(Queue* queue)
{
	return (queue->front == -1);
}

int isFull(Queue* queue)
{
	return (queue->rear + 1) % SIZE_QUEUE == queue->front;
}

int enequeue(Queue* queue, EType data)
{	
	int newRear = 0;
	if (isFull(queue)) return -1;
	newRear = (queue->rear + 1) % SIZE_QUEUE;

	queue->elems[queue->rear = newRear] = data;
	if (queue->front == -1)
		queue->front = 0;
	return data;
}

int dequeue(Queue* queue, EType *data)
{
	if (isEempty(queue)) return -1;

	*data = queue->elems[queue->front];
	if (queue->front != queue->rear)
	{
		queue->front = (queue->front + 1) % SIZE_QUEUE;
	}
	else
	{
		queue->front = queue->rear = -1;
	}
	return *data;
}

void printQueue(Queue* queue)
{
	int pos = queue->front;
	if (isEempty(queue)) return;

	while (pos <= queue->rear)
	{
		printf("%d ", queue->elems[pos++]);
	}
	printf("\n");
}