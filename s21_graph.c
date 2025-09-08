#ifndef S21_GRAPH_C
#define S21_GRAPH_C

#include "s21_graph.h"

graph *graph_create() {
	graph *graph = malloc(sizeof(graph));
	if(graph) {
		graph->matrix = NULL;
		graph->size = 0;
    graph.load_graph_from_file = &load_graph;
    graph.export_graph_to_dot = &export_graph;
    graph.del_graph = &remove_graph;
    graph.is_digraph = &is_digraph;
	}
	return graph;
}

/*
static void graph_free(graph *graph) {
	if(graph) {
		if(graph->matrix) {
			for(int i = 0; i < graph->size; i++) {
				free(graph->matrix[i]);
			}
			free(graph->matrix);
		}
	free(graph);
	}
}
*/

graph *load_graph_from_file(char *filename) {
	FILE *file = fopen(filename, "r");
	if(!file) return NULL;

	graph *graph = graph_create();
  load_graph(filename, graph);

	
	return graph;
}

static int is_digraph(const s21_graph *graph) {
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

static int **calloc_matrix(int size) {
  int **result;
  if (size < 1)
    perror(_ERR_SIZE);
  else {
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
  }
  return result;
}

static void remove_graph(s21_graph *g) {
  if (g->matrix != NULL) {
    for (int i = 0; i < g->size; i++) free(g->matrix[i]);
    free(g->matrix);
    g->matrix = NULL;
    g->size = 0;
  }
}

static void read_graph_el(FILE *f, s21_graph *graph) {
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

static void load_graph(char *filename, s21_graph *graph) {
  printf("load graph\n");
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

  printf("load graph end \n");
}



int export_graph(char *filename, s21_graph *g) {
  if (g->size == 0) return -1;
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
    fprintf(file, "    %d -- %d [weight=%d];\n", i + 1, j + 1,
                g->matrix[i][j]);
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
/*
s21_graph graph_init() {
  s21_graph g = graph_create();
  g.load_graph_from_file = &load_graph;
  g.export_graph_to_dot = &export_graph;
  g.del_graph = &remove_graph;
  g.is_digraph = &is_digraph;
  //g.size = 0;
  //g.matrix = NULL;
  return g;
}
*/
#endif
