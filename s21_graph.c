#ifndef S21_GRAPH_C
#define S21_GRAPH_C

#include "s21_graph.h"

static int is_digraph(const graph *graph) {
  int result = 0;
  for (int i = 0; i < graph->size; i++) {
    for (int j = 0; j < graph->size; j++) {
      if (graph->matrix[i][j] != graph->matrix[j][i]) {
        result = 1;
      }
    }
  }
  return result;
}

/*функция не проверят что ей передано отрицательное число
это надо делать до вызова функции */
static int **calloc_matrix(unsigned int size) {
  int **result;
  result = (int **)calloc(size, sizeof(int *));
  if (!result) {
    perror(_ERR_CALLOC);
  } else {
    for (int i = 0; i < size; i++) {
      result[i] = (int *)calloc(size, sizeof(int));
      if (!result[i]) {
        while (i--) free(result[i]);
        free(result);
        perror(_ERR_CALLOC);
      }
    }
  }
  return result;
}

static void remove_graph(graph *g) {
  if (g->matrix != NULL) {
    for (int i = 0; i < g->size; i++) free(g->matrix[i]);
    free(g->matrix);
    g->matrix = NULL;
    g->size = 0;
  }
}

static void read_graph_el(FILE *f, graph *graph) {
  if (graph->matrix != NULL) {
    for (int i = 0; i < graph->size; i++) {
      for (int j = 0; j < graph->size; j++) {
        int el = 0;
        if (1 != fscanf(f, "%d", &el)) {
          remove_graph(graph);
          perror(_ERR_READ_GRAPH);
        } else {
          graph->matrix[i][j] = el;
        }
      }
    }
  } else {
    perror(_ERR_CREATE_GRAPH);
  }
}

static void load_graph(const char *filename, graph *graph) {
  FILE *f = fopen(filename, "r");
  if (f == NULL)
    perror(_ERR_OPEN);
  else {
    int size_graph = 0;
    if (1 != fscanf(f, "%d", &size_graph))
      perror(_ERR_READ_SIZE);
    else {
      if (size_graph <= 0)
        perror(_ERR_SIZE);
      else {
        graph->size = size_graph;

        graph->matrix = calloc_matrix(size_graph);

        read_graph_el(f, graph);
      }
    }
    fclose(f);
  }
}

graph load_graph_from_file(const char *filename) {
  graph graph = graph_init();
  load_graph(filename, &graph);
  return graph;
}

int export_graph(const char *filename, const graph *g) {
  if (g->size == 0) {
    perror(_ERR_SIZE);
    return -1;
  }
  FILE *file = fopen(filename, "w");
  if (!file) return -1;

  int digraph = is_digraph(g);

  if (!digraph) {
    fprintf(file, "graph G {\n");
  } else {
    fprintf(file, "digraph G {\n");
  }
  for (int i = 0; i < g->size; i++) {
    for (int j = 0; j < g->size; j++) {
      if (g->matrix[i][j] != 0) {
        if (!digraph) {
          if (j >= i) {
            fprintf(file, "    %d -- %d [weight=%d];\n", i + 1, j + 1,
                    g->matrix[i][j]);
          }
        } else {
          fprintf(file, "    %d -> %d [weight=%d];\n", i + 1, j + 1,
                  g->matrix[i][j]);
        }
      }
    }
  }

  fprintf(file, "}\n");
  fclose(file);
  return 0;
}

graph graph_init() {
  graph g;  //= graph_create();
  g.load_graph_from_file = &load_graph_from_file;
  g.export_graph_to_dot = &export_graph;
  g.del_graph = &remove_graph;
  g.is_digraph = &is_digraph;
  g.size = 0;
  g.matrix = NULL;
  return g;
}

#endif
