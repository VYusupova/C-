#ifndef S21_GRAPH_PRINT_C
#define S21_GRAPH_PRINT_C

#include "s21_graph.h"

void print_matrix(s21_graph *g) {
  printf("size graph %02d\n", g->size);
  if (g->matrix == NULL) {
    printf("ERROR\n");
  } else {
    for (int i = 0; i < g->size; i++) {
      for (int j = 0; j < g->size; j++) {
        printf(" %2d", g->matrix[i][j]);
      }
      printf("\n");
    }
  }
}

void print_dot(s21_graph *graph) {
  if (graph->size == 0) perror(_ERR_SIZE);
  int digraph = graph->is_digraph(graph);
  if (digraph == 0) {
    printf("graph {\n");
  } else {
    printf("digraph {\n");
  }
  for (int i = 0; i < graph->size; i++) {
    printf("%c;\n", 'A' + i);
  }
  for (int i = 0; i < graph->size; i++) {
    for (int j = i; j < graph->size; j++) {
      if (i != j && graph->matrix[i][j] != 0 && digraph == 0) {
        printf("%c -- %c;\n", 'A' + i, 'A' + j);
      } else if (graph->matrix[i][j] != 0 && graph->matrix[i][j] != -1 &&
                 digraph == 1) {
        printf("%c -> %c;\n", 'A' + i, 'A' + j);
      }
    }
  }
  printf("}\n");
}


#endif
