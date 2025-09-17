#ifndef S21_QUEUE_C
#define S21_QUEUE_C
#include "s21_queue.h"

queue *create_queue(int capacity) {
  queue *q = malloc(sizeof(queue));
  q->arr = (int *)malloc(capacity * sizeof(queue));
  q->front = 1;
  q->back = 0;
  q->capacity = capacity;
  return q;
}

void enqueue(queue *q, int value) {
  if (q->back < q->capacity) {
    q->back++;
    q->arr[q->back] = value;
  }
}

int dequeue(queue *q) {
  if (q->capacity <= 0) {
    return -1;
  }
  q->capacity--;
  return q->arr[q->front++];
}

int is_empty(const queue *q) { return q->front > q->back; }

void free_queue(queue *q) {
  free(q->arr);
  free(q);
}

#endif
