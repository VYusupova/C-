#include <stdlib.h>

typedef struct node {
    struct node * tail;
    int date;
}
node;

typedef struct stack {
    node * head;
    int size;

}
stack;

stack * stack_init(stack * s);
stack * push(int value, stack * s) ;
int pop(stack * s) ;
int top(stack * s) ;
void stack_free(stack *s) ;
