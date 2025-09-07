#include "../s21_graph_algorithms.h"

/**
 * @brief Решение задачи коммивояжера с помощью алгоритма ближайшего соседа.
 * @note Улучшение жадного алгоритма за счет перебора всех стартовых вершин.
 * * Запускает жадный алгоритм для каждой вершины как стартовой.
 * * Выбирает лучшее решение среди всех вариантов. Сложность: Остается O(n²)
 * Меньшая зависимость от выбора старта: Шанс найти более короткий путь.
 * @param graph Указатель на граф.
 * @return Результат решения задачи коммивояжера.
 */
tsm_result *nearest_neighbor_tsp(graph *g) {
  if (!g || g->size < 2) return NULL;

  tsm_result *best = NULL;

  for (int start = 0; start < g->size; start++) {
    tsm_result *res = malloc(sizeof(tsm_result));
    res->vertices = malloc((g->size + 1) * sizeof(int));
    res->distance = 0;

    int *visited = calloc(g->size, sizeof(int));
    int valid = 1;

    int current = start;
    res->vertices[0] = current + 1;
    visited[current] = 1;

    // Построение пути
    for (int i = 1; i < g->size; i++) {
      int next = -1;
      int min_dist = INT_MAX;

      // Поиск ближайшего непосещенного соседа
      for (int j = 0; j < g->size; j++) {
        if (!visited[j] && g->matrix[current][j] > 0 &&
            g->matrix[current][j] < min_dist) {
          min_dist = g->matrix[current][j];
          next = j;
        }
      }

      // Если следующий город не найден - путь невалиден
      if (next == -1) {
        valid = 0;
        break;
      }

      res->vertices[i] = next + 1;
      res->distance += min_dist;
      visited[next] = 1;
      current = next;
    }

    // Проверка условий:
    // 1. Все вершины посещены
    // 2. Существует обратное ребро в стартовую вершину
    if (valid) {
      // Проверка посещения всех вершин
      for (int i = 0; i < g->size; i++) {
        if (!visited[i]) {
          valid = 0;
          break;
        }
      }
      // Проверка существования последнего ребра
      if (valid && g->matrix[current][start] == 0) {
        valid = 0;
      }
      res->distance += valid ? g->matrix[current][start] : INFINITY;
    }

    res->vertices[g->size] = start + 1;  // Замыкание цикла

    // Обновление лучшего результата только для валидных путей
    if (valid && res->distance < INFINITY) {
      if (!best || res->distance < best->distance) {
        if (best) free_tsm_result(best);
        best = res;
      } else {
        free_tsm_result(res);
      }
    } else {
      free_tsm_result(res);
    }
    free(visited);
  }

  return best;
}
