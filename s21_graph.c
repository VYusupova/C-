#ifndef S21_GRAPH_C
#define S21_GRAPH_C

#include "s21_graph.h"

#include "../lib/s21_matrix.h"

static void read_graph_el(FILE *f, matrix_t *graph) {
  for (int i = 0; i < graph->rows; i++)
    for (int j = 0; j < graph->rows; j++)
      if (1 != fscanf(f, "%le", &graph->matrix[i][j])) {
        s21_remove_matrix(graph);
        perror(_ERR_READ_GRAPH);
        return;
      }
}

matrix_t *load_graph_from_file(char *filename) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    perror(_ERR_OPEN);
    return NULL;
  }
  int size_graph = 0;
  if (1 != fscanf(f, "%d", &size_graph)) {
    perror(_ERR_READ_SIZE);
    return NULL;
  }
  matrix_t *graph = NULL;
  if (OK_MATRIX == s21_create_matrix(size_graph, size_graph, graph)) {
    read_graph_el(f, graph);
  } else {
    perror(_ERR_CREATE_GRAPH);
  }

  return graph;
  fclose(f);
}
/*
s21_graph export_graph_to_dot(char *filename) {

}
*/

#endif
