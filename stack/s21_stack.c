#ifndef S21_STACK_C
#define S21_STACK_C

#include "s21_stack.h"

stack *stack_init(stack *s) {
  s->head = NULL;
  s->size = 0;
  return s;
}

void push(int value, stack *s) {
  node *new_node = malloc(sizeof(node));
  new_node->tail = s->head;
  new_node->date = value;
  s->head = new_node;
  s->size++;
}

int pop(stack *s) {
  int el = s->head->date;
  node *del = s->head;
  if (del->tail == NULL)
    s->head = NULL;
  else
    s->head = del->tail;
  s->size--;
  free(del);
  return el;
}

int top(stack *s) { return s->head->date; }

void stack_free(stack *s) {
  while (s->head) pop(s);
  free(s);
}

#endif