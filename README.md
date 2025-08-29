# Часть 1. Обход графа в глубину и в ширину
- [ ] Библиотека должна быть написана на языке C    
- [ ] Код библиотеки должен находиться в папке `src` в ветке `develop`  
## Реализуйте библиотеку s21_graph:
- [ ] При написании программы используйте стандартный для выбранного языка стиль написания кода 
- [ ]  Оформите решение как статическую библиотеку (`s21_graph`)
      
- [ ] Библиотека должна быть представлена в виде класса graph, который хранит информацию о графе с помощью матрицы смежности. Размерность матрицы смежности должна задаваться динамически при инициализации графа (при его загрузке из файла).
- [x] Сборка программы должна быть настроена с помощью `Makefile` со стандартным набором целей для программ `GNU: all, clean, test, s21_graph`.
- [ ] Обеспечьте полное покрытие модульными тестами методов класса graph.
- [ ] Класс graph должен содержать как минимум следующие общедоступные методы:  
> `load_graph_from_file(char *filename)` — загрузка графа из файла в формате матрицы смежности  
> `export_graph_to_dot(char *filename)` — выгрузка графа в файл в формате dot (см. материалы)  

## Реализуйте библиотеку s21_graph_algorithms:

- [ ] Оформите решение как статическую библиотеку (`s21_graph_algorithms`).
- [ ] Библиотека должна быть представлена в виде класса `graph_algorithms`, который будет содержать реализацию алгоритмов на графах. При этом сам класс `graph_algorithms` не должен ничего знать о внутреннем представлении графа в классе `graph`. Для взаимодействия с данными графа класс `graph_algorithms` может использовать только общедоступные методы и свойства, предоставляемые классом `graph`.
- [ ] Добавьте в `Makefile` цель `s21_graph_algorithms`  
- [ ] Обеспечьте полное покрытие модульными тестами методов класса graph_algorithms.
- [ ] Класс graph_algorithms должен содержать как минимум следующие общедоступные методы:
> `depth_first_search(graph *graph, int start_vertex)` — нерекурсивный поиск в глубину в графе от заданной вершины. Функция должна возвращать массив, содержащий пройденные вершины в порядке их обхода. При реализации этой функции обязательно используйте самописную структуру данных стек, которую предварительно стоит оформить в виде отдельной статической библиотеки  
> `breadth_first_search(graph *graph, int start_vertex)` — поиск в ширину в графе, начинающийся с заданной вершины. Функция должна возвращать массив, содержащий пройденные вершины в порядке их обхода. При реализации этой функции обязательно используйте самописную структуру данных очередь, которую предварительно стоит оформить в виде отдельной статической библиотеки  
- [ ] Необходимо адаптировать ранее созданные самописные вспомогательные классы stack и queue (для этого можно использовать своё решение из проекта CPP2) и реализовать для них интерфейсы на C. Эти классы должны содержать следующие методы:
> `stack()` — создание пустого стека  
> `queue()` — создание пустой очереди  
> `push(value)` — добавление элемента в стек/очередь  
> `pop()` — получение элемента из стека/очереди с последующим удалением из стека/очереди  
> `top()` — получение элемента из стека без его удаления из стека  
> `front()` — получение первого элемента из очереди без его удаления из очереди  
> `back()` — получение последнего элемента из очереди без его удаления из очереди  
- [ ] В этом и последующих заданиях считайте, что нумерация вершин начинается с 1.

 ```make
.PHONY: 

NAME := SimpleNavigator
DIR_LIB := lib\
LIB_GRAPH = $(DIR_LIB)s21_graph
LIB_GRAPH_ALG = $(DIR_LIB)s21_graph_algorithms

all: clean s21_graph s21_graph_algorithms

clean:
  $(RM) $(LIB_GRAPH)  $(LIB_GRAPH_ALG)

test: 
  $(CC) $(CFLAGS) $(GCOV_FLAGS) -c test/$(LIB_GRAPH).c -o  test/$(LIB_GRAPH).gcov.o
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -o $(TEST) test/$(LIB_GRAPH).gcov.o   $(CHECK_LIBS)
	@printf "\e[1;35;107m RUN FILE TESTING  \e[31;0m \n"
	./$(TEST)
	@printf "\n\e[1;35;107m END FILE TESTING    \e[31;0m \n"
	@printf "\e[1;35;107m  Отчет покрытия кода в 'gcov/index.html' ┃\e[31;0m   📊 \n"
	lcov -t "gcov_report" -o $(NAME)_coverage.info -c -d .
	genhtml -o gcov $(NAME)_coverage.info
	$(RM) test/*.gcov.*


LIB_GRAPH:
ifdef DIR_LIB
	@if [ -d $(DIR_LIB) ]; then ;\
	  else mkdir -p $(DIR_LIB) ; \
	        $(CC) $(CFLAGS) $(LIB_GRAPH).c -o $(LIB_GRAPH).o ; 	\
          ar rcs  $(LIB_GRAPH).a *.o; 	\
	        rm *.o # Использованные объектные файлы можно удалены; 	\
          printf " \n ✅ $(LIB_GRAPH).a created in catalog [$(DIR_LIB)]" ; \
	fi
else
	$(error DIR_LIB must be set!)
endif
  
  

LIB_GRAPH_ALG:
ifdef DIR_LIB
	@if [ -d $(DIR_LIB) ]; then ;\
	  else mkdir -p $(DIR_LIB) ; \
	  $(CC) $(CFLAGS) $(LIB_GRAPH_ALG).c -o $(LIB_GRAPH_ALG).o; \
     ar rcs  $(LIB_GRAPH_ALG).a *.o; \
	    rm *.o ; \
          printf " \n ✅ LIB_GRAPH_ALG.a created in catalog [$(DIR_LIB)]" ; \
	fi
else
	$(error DIR_LIB must be set!)
endif


```
```bash
mkdir -p inc/
touch inc/s21_graph.h
touch s21_graph.c
touch inc/s21_graph_algorithms.h
touch s21_graph_algorithms.c
```

```c
#include <stdio.h>

typedef struct graph {
    int ** matrix;
    int size;

}
s21_graph;

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

int node_not_in_visited(int node, int * visit, int len_visit) {
    for (int i = 0; i <= len_visit; i++)
        if (node == visit[i]) return 0;
    return 1;
}
void visited_add(int node, int * visited, int len_visit) {
    for (int i = 0; i < len_visit; i++)
        if (0 == visited[i])
        {
            visited[i] = node;
            return;
        }

}

int next(int node, s21_graph * g) {
    for (int i = node; i < g -> size; i++) {
        if (g -> matrix[node][i] != 0) return i;
    }
}

void print_graph(s21_graph *g){
   for (int i = 0; i < g -> size; i++) {
            for (int j = 0; j < g -> size; j++) {
                printf("%d ", g -> matrix[i][j]);
            }
            printf("\n");
        }
}

int * dfs_iterative(s21_graph * g, int start_node) {
    int * visited = calloc(g -> size, sizeof(int));
    if (g -> size == 0) {
        perror("_ERR_GRAPH_IS_EMPTY");
    }
    else {
        print_graph(g);
        stack * s = stack_init(s);
        push(start_node, s);
        visited_add(start_node, visited, g -> size);
        int next_node = next(start_node, g);
        push(next_node, s);
     

        while (s -> size > 0) {
            int node = top(s);

            if (node_not_in_visited(node, visited, g -> size)) {
                printf("node_%d\n", node);
                visited_add(node, visited, g -> size);

                next_node = next(node, g);
                push(next_node, s);
            }
            else {
                pop(s);
            }
        }
    }
    return visited;
}

static int ** calloc_matrix(int size) {
    int ** result;
    if (size < 1)
        perror("_ERR_SIZE");
    else {
        result = (int ** ) calloc(size, sizeof(int * ));
        if (!result) {
            perror("_ERR_CALLOC");
        }
        else {
            for (int i = 0; i < size; i++) {
                result[i] = (int * ) calloc(size, sizeof(int));
                if (!result[i]) {
                    while (i--) free(result[i]);
                    free(result);
                    perror("_ERR_CALLOC");
                }
            }
        }
    }
    return result;
}

int main() {
    stack * s;
    // if (s == NULL) printf("GOOD stack is null \n");
    // else printf("BAD stack is not null \n");

    // if (s == NULL) printf("BAD stack is null \n");
    // else printf("GOOD  stack is not null \n");
    // s = push(13, s);
    // if (s == NULL) printf("BAD stack is null \n");
    // else printf("GOOD  stack is not null \n");
    // printf("TOP  stack is - %d \n", top(s));
    // s = push(18, s);
    // printf("TOP  stack is - %d \n", top(s));
    // printf("POP  stack is - %d & size is = %d \n", pop(s), s->size);
    // printf("TOP  stack is - %d & size is = %d \n", top(s), s->size);
    s21_graph g;
    g.matrix = calloc_matrix(4);
    g.matrix[0][0] = 0;
    g.matrix[0][1] = 1;
    g.matrix[0][2] = 0;
    g.matrix[0][3] = 0;

    g.matrix[1][0] = 1;
    g.matrix[1][1] = 0;
    g.matrix[1][2] = 1;
    g.matrix[1][3] = 1;

    g.matrix[2][0] = 1;
    g.matrix[2][1] = 0;
    g.matrix[2][2] = 0;
    g.matrix[2][3] = 1;
    
    g.matrix[3][0] = 0;
    g.matrix[3][1] = 1;
    g.matrix[3][2] = 0;
    g.matrix[3][3] = 1;
    g.size = 4;

    s = stack_init(s);
    printf("size stack %d\n", s -> size);
    int * vis = dfs_iterative( & g, 2);
            printf("visited = ");
    for (int i = 0; i < g.size; i++) {
            printf("%d ",vis[i]);


    }

    free(s);
}
```
