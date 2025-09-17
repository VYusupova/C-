#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct queue {
  int *arr;
  int front;
  int back;
  int capacity;
} queue;

queue *create_queue(int capacity);

void enqueue(queue *q, int value);

int dequeue(queue *q);
int is_empty(const queue *q);
void free_queue(queue *q);

#endif
