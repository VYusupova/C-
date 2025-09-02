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

static int next(int node, s21_graph *g) {
  for (int i = node; i < g->size; i++) {
    if (g->matrix[node][i] != 0)
      return i;
  }
  return g->size;
}

static int node_not_in_visited(int node, int *visit, int len_visit) {
  for (int i = 0; i <= len_visit; i++)
    if (node == visit[i])
      return 0;
  return 1;
}

static int *dfs_iterative(s21_graph *g, int start_node) {
  int *visited = calloc(g->size, sizeof(int));
  if (g->size == 0)
    perror("_ERR_GRAPH_IS_EMPTY");
  else {
    stack *s = malloc(sizeof(stack));
    ;
    s = stack_init(s);
    push(start_node + 1, s);
    visited_add(start_node + 1, visited, g->size);
    int next_node = next(start_node, g);
    push(next_node + 1, s);
    while (s->size > 0) {
      int node = top(s);
      if (node_not_in_visited(node, visited, g->size)) {
        visited_add(node, visited, g->size);
        next_node = next(node - 1, g);
        push(next_node + 1, s);
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
