#ifndef S21_QUEUE_C
#define S21_QUEUE_C

#include <stdio.h>
#include <stdlib.h>

typedef struct {	
	int *arr;	
	int front;
	int back;
	int capacity;
} queue;

typedef struct node {
  struct node *tail;
  int date;
} node;

queue* create_queue() {
	queue *q = (queue)malloc(sizeof(queue));
	q->arr = (int*)malloc(capacity * sizeof(queue));
	q->front = 0;
	q->back = -1;
	q->capacity = capacity;
	return q;
}

void enqueue(queue *q, int value) {
	if(q->back == q->capacity - 1) {
		return;
	}
	q->data[++q->back] = value;
}

int dequeue(queue *q) {
	if(q->front > q->back) {
		return -1;
	}
	return q->arr[q->front++];
}

int is_empty(queue *q) {
	return q->front > q->back;
}

void free_queue(queue *q) {
	free(q->arr);
	free(q);
}

#endif
