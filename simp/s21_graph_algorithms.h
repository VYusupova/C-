#ifndef SRC_GRAPH_ALGORITHMS_S21_GRAPH_ALGORITHMS_H
#define SRC_GRAPH_ALGORITHMS_S21_GRAPH_ALGORITHMS_H

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../graph/s21_graph.h"
#include "containers/s21_queue.h"
#include "containers/s21_stack.h"

#define INF (1.0 / 0.0)
#define NO_EDGE 0

/**
 * @struct tsm_result
 * @brief Структура для хранения результата решения задачи коммивояжера.
 */
typedef struct {
  int* vertices;   /**< Массив вершин. */
  double distance; /**< Расстояние. */
} tsm_result;

int* depth_first_search(graph* g, int start_vertex);
int* breadth_first_search(graph* g, int start_vertex);

// Поиск кратчайших путей в графе:

// алгоритм Дейкстры.
double get_shortest_path_between_vertices(graph* graph, int start, int end);
// алгоритм Флойда-Уоршелла.
double** get_shortest_paths_between_all_vertices(graph* graph);

// поиск наименьшего остовного дерева в графе с помощью алгоритма Прима.
graph* get_least_spanning_tree(graph* graph);

// Решение задачи коммивояжера с помощью:
//  муравьиного алгоритма.
tsm_result* solve_traveling_salesman_problem(graph* graph);

// жадного алгоритма.
tsm_result* greedy_tsp(graph* graph);

// с помощью алгоритма лижайшего соседа.
tsm_result* nearest_neighbor_tsp(graph* graph);

// для проверки верного решения =)) Сделал для сверки и сравнения
tsm_result* bf_tsp(graph* graph);

void free_shortest_paths_matrix(double** matrix, int size);
void free_tsm_result(tsm_result* result);

#endif  // SRC_GRAPH_ALGORITHMS_S21_GRAPH_ALGORITHMS_H