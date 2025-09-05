#include "../s21_graph_algorithms.h"

/**
 * @brief Решение задачи коммивояжера с помощью жадного алгоритма.
 * @note Алгоритм для быстрого поиска приближенного решения TSM =)).
 * * Начинает с фиксированной стартовой вершины (например, 1).
 * * На каждом шаге выбирает ближайшую непосещенную вершину.
 * * Формирует цикл, возвращаясь в стартовую вершину. Сложность O(n²)
 * @param graph Указатель на граф.
 * @return Результат решения задачи коммивояжера.
 */
tsm_result *greedy_tsp(graph *g) {
  if (!g || g->size < 2) return NULL;

  tsm_result *res = malloc(sizeof(tsm_result));
  res->vertices = malloc((g->size + 1) * sizeof(int));
  res->distance = 0;

  int *visited = calloc(g->size, sizeof(int));
  int current = 0;
  res->vertices[0] = 1;  // Стартовая вершина: Фиксирована (вершина 1 в коде).
  visited[0] = 1;

  for (int i = 1; i < g->size; i++) {
    int next = -1;
    int min_dist = INT_MAX;

    for (int j = 0; j < g->size; j++) {
      if (!visited[j] && g->matrix[current][j] > 0 &&
          g->matrix[current][j] < min_dist) {
        min_dist = g->matrix[current][j];
        next = j;
      }
    }

    if (next == -1) {
      free(res->vertices);
      free(res);
      res = NULL;
      break;
    }

    res->vertices[i] = next + 1;
    res->distance += min_dist;
    visited[next] = 1;
    current = next;
  }

  if (res) {
    // проверяем существует ли обратное ребро
    if (g->matrix[current][0] <= 0) {
      free(res->vertices);
      free(res);
      res = NULL;
    } else {
      res->vertices[g->size] = 1;
      res->distance += g->matrix[current][0];
    }
  }

  free(visited);
  return res;
}