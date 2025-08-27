#ifndef S21_GRAPH_C
#define S21_GRAPH_C

#include "s21_graph.h"


void print(s21_graph g) {
    printf("size graph %02d\n ", g.row);
    printf("element graph\n");
    for (int i = 0; i < g.row; i++) {
        for (int j = 0; j < g.row; j++)
            printf(" %2d", g.matrix[i][j]);
        printf("\n");
    }
}

int ** create_matrix(int row) {
    int ** result;
    if (row < 1) {
        perror(_ERR_SIZE);
        return NULL;
    }

    result = (int ** ) calloc(row, sizeof(int * ));

    if (!result) {
        perror(_ERR_CALLOC);
        return NULL;
    }
    for (int i = 0; i < row; i++) {
        result[i] = (int * ) calloc(row, sizeof(int));

        if (!result[i]) {
            while (i--) free(result[i]);
            free(result);
            perror(_ERR_CALLOC);
            return NULL;
        }
    }

    return result;
}

void remove_graph(s21_graph *g) {
  if (g->matrix != NULL) {
    for (int i = 0; i < g->row; i++) free(g->matrix[i]);
    free(g->matrix);
    g->matrix = NULL;
    g->row = 0;
  }
}

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
