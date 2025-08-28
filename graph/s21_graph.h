#ifndef SRC_GRAPH_S21_GRAPH_H
#define SRC_GRAPH_S21_GRAPH_H

#include <stdio.h>
#include <stdlib.h>

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/**
 * @brief Структура для представления графа
 */
typedef struct {
  int **matrix; /**< Матрица смежности графа */
  int size;     /**< Размер графа */
} graph;

graph *graph_create();
void graph_free(graph *g);
int load_graph_from_file(graph *g, const char *filename);
int export_graph_to_dot(const graph *g, const char *filename);
int graph_get_vertex_count(const graph *g);
int graph_get_edge_weight(const graph *g, int from, int to);
int is_undirected(const graph *g);

#endif  // SRC_GRAPH_S21_GRAPH_H