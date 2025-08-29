typedef struct node {
    int * tail;
    int date;
}
node;

typedef struct stack {
    node * head;
    int size;

}
stack;

stack * stack_init(stack * s) {
    s = malloc(sizeof(stack));
    s -> head = NULL;
    s -> size = 0;
    return s;
}

stack * push(int value, stack * s) //  — добавление элемента в стек/очередь;
{
    node * new_node = malloc(sizeof(node));
    new_node -> tail = s -> head;
    new_node -> date = value;
    s -> head = new_node;
    s -> size++;
    //printf("size %d\n", s->size); 
    return s;
}
int pop(stack * s) // — получение элемента из стека/очереди с его последующим удалением из стека/очереди;
{
    int el = s -> head -> date;
    node * del = s -> head;
    if (del -> tail == NULL) s -> head = NULL;
    else s -> head = del -> tail;
    s -> size--;
    free(del);
    return el;
}
int top(stack * s) // — получение элемента из стека без его удаления из стека;
{
    return s -> head -> date;
}
