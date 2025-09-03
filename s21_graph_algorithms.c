#ifndef S21_GRAPH_ALGORITHMS_H
#define S21_GRAPH_ALGORITHMS_H

#include "s21_graph_algorithms.h"
#include "s21_graph.h"
#include "stack/stack.h"

static void visited_add(int node, int *visited, int len_visit) {
  for (int i = 0; i < len_visit; i++)
    if (0 == visited[i]) {
      visited[i] = node;
      return;
    }
}

/*
static int *list_next(int node, s21_graph *g) {
  int* list = calloc(sizeof(int));
  int l = 0;
  for (int i = 0; i < g->size; i++) {
    if (g->matrix[node][i] > 0){
      list[l] = i+1;
      l++;
      list = realloc(list, (l+1)*sizeof(int));
    }
  }
  if (list[0] == 0) return NULL;
  else return list;
}
*/
static int node_not_in_visited(int node, int *visit, int len_visit) {
  for (int i = 0; i <= len_visit; i++)
    if (node == visit[i])
      return 0;
  return 1;
}

void put_node_in_stack(stack *s, int node, s21_graph *g, int *visited) {
  for (int i = 0; i < g->size; i++) {
    if (g->matrix[node][i] > 0) {
      if (node_not_in_visited(i + 1, visited, g->size))
        push(i + 1, s);
    }
  }
}

/*
Алгоритм поиска в глубину работает следующим образом:

1. поместите любую вершину графа на вершину стека.
2. Возьмите верхний элемент стека и добавьте его в список “Пройденных”.
3. Создайте список смежных вершин для этой вершины. Добавьте те вершины, которых
нет в списке “Пройденных”, в верх стека.
4. Необходимо повторять шаги 2 и 3, пока стек не станет пустым.

*/
static int *dfs_iterative(s21_graph *g, int start_node) {
  int *visited = calloc(g->size, sizeof(int));
  if (g->size == 0)
    perror("_ERR_GRAPH_IS_EMPTY");
  else {
    stack *s = malloc(sizeof(stack));
    s = stack_init(s);
    push(start_node + 1, s);
    visited_add(start_node + 1, visited, g->size);
    put_node_in_stack(s, start_node, g, visited);
    int node = start_node;
    while (s->size > 0) {
      node = top(s);
      if (node_not_in_visited(node, visited, g->size)) {
        visited_add(node, visited, g->size);
        put_node_in_stack(s, node - 1, g, visited);
      } else {
        pop(s);
      }
    }
  }
  return visited;
}

// TO DO  добавить функцию вывода вершин которые были пройдены

int *depth_first_search(s21_graph *graph, int start_vertex) {
  int *visit = dfs_iterative(graph, start_vertex);
  return visit;
}

// int *  breadth_first_search(s21_graph *graph, int start_vertex) {

// }

#endif
