#include <stdio.h>
#include "stack/stack.h"

typedef struct graph {
    int ** matrix;
    int size;

}
s21_graph;

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
    return g -> size;
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
        stack * s = malloc(sizeof(stack));;
        s = stack_init(s);
        push(start_node+1, s);
        visited_add(start_node+1, visited, g -> size);
        int next_node = next(start_node, g);
        push(next_node+1, s);
     

        while (s -> size > 0) {
            int node = top(s);
                printf("top_%d\n", node);
            if (node_not_in_visited(node, visited, g -> size)) {

                visited_add(node, visited, g -> size);

                next_node = next(node-1, g);
                push(next_node+1, s);
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
    stack * s = malloc(sizeof(stack));
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
    g.matrix = calloc_matrix(5);
    g.matrix[0][0] = 0;
    g.matrix[0][1] = 1;
    g.matrix[0][2] = 1;
    g.matrix[0][3] = 0;
    g.matrix[0][4] = 1;

    g.matrix[1][0] = 0;
    g.matrix[1][1] = 0;
    g.matrix[1][2] = 1;
    g.matrix[1][3] = 1;
        g.matrix[1][4] = 1;

    g.matrix[2][0] = 1;
    g.matrix[2][1] = 0;
    g.matrix[2][2] = 0;
    g.matrix[2][3] = 1;
        g.matrix[2][4] = 1;
        
    g.matrix[3][0] = 0;
    g.matrix[3][1] = 1;
    g.matrix[3][2] = 0;
    g.matrix[3][3] = 0;
        g.matrix[3][4] = 1;
        
    g.matrix[4][0] = 0;
    g.matrix[4][1] = 1;
    g.matrix[4][2] = 0;
    g.matrix[4][3] = 0;
    g.matrix[4][4] = 1;
    g.size = 5;

    s = stack_init(s);
    printf("size stack %d\n", s -> size);
    int * vis = dfs_iterative( & g, 0);
            printf("visited = ");
    for (int i = 0; i < g.size; i++) {
            printf("%d ",vis[i]);


    }

    free(s);
    return 0;
}
