#ifndef S21_GRAPH_C
#define S21_GRAPH_C

#include "s21_graph.h"


void print_m(int row, int **matrix) {
    printf("size graph %02d\n ", row);
    if (matrix == NULL) {printf("ERROR\n");return;}
   // printf("element graph %d\n", matrix[0][0]);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3	; j++)
        {
        int el = matrix[i][j];
           printf(" %2d", el);
        }
        printf("\n");
    }
}

void create_matrix(int row, int ** result) {

           printf("func create matrix\n");
    if (row < 1) {
        perror(_ERR_SIZE);
        return ;
    }

    result = (int ** ) calloc(row,sizeof(int * ));

    if (!result) {
        perror(_ERR_CALLOC);
        return ;
    }
    for (int i = 0; i < row; i++) {
        result[i] = (int * ) calloc(row, sizeof(int));

        if (!result[i]) {
            while (i--) free(result[i]);
            free(result);
            perror(_ERR_CALLOC);
            return ;
        }
    }
print_m(row, result);
           printf("func create matrix off\n");
           
}

void remove_graph(s21_graph *g) {
  if (g->matrix != NULL) {
    for (int i = 0; i < g->row; i++) free(g->matrix[i]);
    free(g->matrix);
    g->matrix = NULL;
    g->row = 0;
  }
}

void read_graph_el(FILE *f, s21_graph *graph) {
  for (int i = 0; i < graph->row; i++)
    for (int j = 0; j < graph->row; j++)
      if (1 != fscanf(f, "%d", &graph->matrix[i][j])) {
        remove_graph(graph);
        perror(_ERR_READ_GRAPH);
        return;
      }
}

s21_graph load_graph_from_file(char *filename) {
  s21_graph graph;
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    perror(_ERR_OPEN);

  }
  printf("size read\n");
  int size_graph = 0;
  if (1 != fscanf(f, "%d", &size_graph)) {
    perror(_ERR_READ_SIZE);

  }
    printf("size read norm\n");
  graph.row = size_graph;
  int **m = NULL	;
  create_matrix(size_graph,   m);
  print_m(5,m);
  graph.matrix = m;
       printf("matrix size\n");
       print_m(graph.row, graph.matrix);
  if (graph.matrix != NULL) {
    //read_graph_el(f, graph);
    for (int i = 0; i < graph.row; i++)
    for (int j = 0; j < graph.row; j++){
    int el = 0;

      if (1 != fscanf(f, "%d", &el)) {
        remove_graph(&graph);
        perror(_ERR_READ_GRAPH);

      }
      else {//graph.matrix[i][j] = el;
             printf("read element %d\n", el);}
      }
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
