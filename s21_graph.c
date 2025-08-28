#ifndef S21_GRAPH_C
#define S21_GRAPH_C

#include "s21_graph.h"


static void print(s21_graph * g) {
    printf("size graph %02d\n", g -> size);
    if (g -> matrix == NULL) {
        printf("ERROR\n");
    }
    else {
        for (int i = 0; i < g -> size; i++) {
            for (int j = 0; j < g -> size; j++)
            {
                printf(" %2d", g -> matrix[i][j]);
            }
            printf("\n");
        }
    }
}

static int ** calloc_matrix(int size) {
    int ** result;
    if (size < 1)
        perror(_ERR_SIZE);
    else {
        result = (int ** ) calloc(size, sizeof(int * ));
        if (!result) {
            perror(_ERR_CALLOC);
        }
        else {
            for (int i = 0; i < size; i++) {
                result[i] = (int * ) calloc(size, sizeof(int));
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

static void remove_graph(s21_graph * g) {
    if (g -> matrix != NULL) {
        for (int i = 0; i < g -> size; i++) free(g -> matrix[i]);
        free(g -> matrix);
        g -> matrix = NULL;
        g -> size = 0;
    }
}

static void read_graph_el(FILE * f, s21_graph * graph) {
    if (graph->matrix != NULL) {

        for (int i = 0; i < graph -> size; i++) {
            for (int j = 0; j < graph -> size; j++) {
                int el = 0;
                if (1 != fscanf(f, "%d", & el)) {
                    remove_graph( graph);
                    perror(_ERR_READ_GRAPH);
                }
                else {
                    graph->matrix[i][j] = el;
                }
            }
        }
    }
    else {
        perror(_ERR_CREATE_GRAPH);
    }

}

static void load_graph(char * filename, s21_graph * graph) {
    printf("load graph\n");
    FILE * f = fopen(filename, "r");
    if (f == NULL) {
        perror(_ERR_OPEN);
    }
    else {

        int size_graph = 0;
        if (1 != fscanf(f, "%d", & size_graph)) {
            perror(_ERR_READ_SIZE);
        }
        else {

            graph->size = size_graph;

            graph->matrix = calloc_matrix(size_graph);

            read_graph_el(f, graph);

        }
    }
    fclose(f);
        printf("load graph end \n");
 
}

static int is_directed(const graph *g) {
  for (int i = 0; i < g->size; i++) {
    for (int j = 1; j < i; j++) {
      if (g->matrix[i][j] != g->matrix[j][i]) {
        return FALSE;
      }
    }
  }
  return TRUE;
}


int export_graph(char *filename, s21_graph * g) {
FILE *file = fopen(filename, "w");
if (!file) return -1;

  int isdirected = is_directed(g);

  if (!isdirected) {
    fprintf(file, "graph G {\n");
    for (int i = 0; i < g->size; i++) {
      for (int j = i; j < g->size; j++) {
        if (i != j && g->matrix[i][j] != 0) {
          fprintf(file, "\t%d -- %d [weight=%d];\n", i + 1, j + 1,
                  g->matrix[i][j]);
        }
      }
    }
  } else {
    fprintf(file, "digraph G {\n");
    for (int i = 0; i < g->size; i++) {
      for (int j = 0; j < g->size; j++) {
        if ( g->matrix[i][j] != 0) {
          fprintf(file, "\t%d -> %d [weight=%d];\n", i + 1, j + 1,
                  g->matrix[i][j]);
        }
      }
    }
  }

  fprintf(file, "}\n");
  fclose(file);
  return 0;
}



s21_graph graph_init(){
s21_graph g ;
g.print_graph = &print;
g.load_graph_from_file = &load_graph;
g.export_graph_to_dot =&export_graph;
g.del_graph = &remove_graph;
g.size = 0;
return g;
}


#endif
