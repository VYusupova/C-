#ifndef S21_GRAPH_C
#define S21_GRAPH_C

#include "s21_graph.h"


void print(s21_graph *g) {
    printf("size graph %02d\n ", g->row);
    printf("element graph\n");
    for (int i = 0; i < g->row; i++) {
        for (int j = 0; j < g->row; j++)
            printf(" %2d", g->matrix[i][j]);
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

static void read_graph_el(FILE *f, s21_graph *graph) {
  for (int i = 0; i < graph->row; i++)
    for (int j = 0; j < graph->row; j++)
      if (1 != fscanf(f, "%d", &graph->matrix[i][j])) {
        remove_graph(graph);
        perror(_ERR_READ_GRAPH);
        return;
      }
}

s21_graph *load_graph_from_file(char *filename) {
  s21_graph *graph = NULL;
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
  graph->row = size_graph;
  graph->matrix = create_matrix(size_graph);
   
  if (graph->matrix != NULL) {
    read_graph_el(f, graph);
  } else {
    perror(_ERR_CREATE_GRAPH);
    graph = NULL;
  }
  return graph;
  fclose(f);
}
/*
s21_graph export_graph_to_dot(char *filename) {

}
*/

#endif
