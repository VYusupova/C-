#include "../s21_graph_algorithms.h"

/**
 * @brief Поиск кратчайшего пути от вершины start до end  в графе с
неотрицательными весами с использованием алгоритма Дейкстры.
 * @note Данный алгоритм характеризуется тем, что позволяет находить
оптимальные маршруты и их длину между заданной исходной вершиной и
всеми остальными вершинами графа. Недостаток алгоритма заключается в том,
что при наличии в графе ребер с отрицательными весами, его работа будет
некорректной. Кроме того при работе данный алгоритм не предусматривает петель,
однако он не накладывает ограничения на вид графов для которых будет
использоваться. Сложность O(V²)
 * @param graph Указатель на граф.
 * @param start Начальная вершина.
 * @param end Конечная вершина.
 * @return Расстояние между вершинами.
 */
double get_shortest_path_between_vertices(graph *g, int start, int end) {
  if (!g || start < 1 || end < 1 || start > g->size || end > g->size) return -1;

  int size = g->size;

  // хранит текущее кратчайшее расстояние от start до вершины i

  double *dist = malloc((size + 1) * sizeof(double));
  int *visited = calloc(size + 1, sizeof(int));

  // Инициализируется значением INF (бесконечность) для всех вершин, кроме
  // стартовой (dist[start] = 0)
  for (int i = 1; i <= size; i++) dist[i] = INF;

  // Длина пути для вершины, которая является стартовой, будет равной 0;
  dist[start] = 0;

  for (int i = 1; i <= size; i++) {
    int min_idx = -1;
    for (int j = 1; j <= size; j++) {
      // На каждой итерации выбирается вершина min_idx с минимальным расстоянием
      // из непосещенных (жадный выбор)
      if (!visited[j] && (min_idx == -1 || dist[j] < dist[min_idx]))
        min_idx = j;
    }

    if (dist[min_idx] == INF) break;
    // Вершина помечается как посещенная.
    visited[min_idx] = 1;

    for (int j = 1; j <= size; j++) {
      int weight = g->matrix[min_idx - 1][j - 1];

      // Для выбранной вершины обновляются расстояния до всех её соседей:
      if (weight > 0 && dist[j] > dist[min_idx] + weight)
        dist[j] = dist[min_idx] + weight;
    }
  }

  // Возвращается dist[end] (или -1, если путь не существует).
  double result = dist[end] == INF ? -1 : dist[end];

  free(dist);
  free(visited);

  return result;
}
