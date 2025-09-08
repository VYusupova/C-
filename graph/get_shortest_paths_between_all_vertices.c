#include "../s21_graph_algorithms.h"

/**
 * @brief Поиск кратчайших путей между всеми парами вершин в графе с
 * использованием алгоритма Флойда-Уоршелла.
 * @note  алгоритм может использоваться только на
взвешенных графах, с положительными и отрицательными весами ребер. При
этом в графах должны отсутствовать отрицательные циклы. Сложности O(V³)
 * @param graph Указатель на граф.
 * @return Матрица кратчайших путей.
 */
double **get_shortest_paths_between_all_vertices(graph *g) {
  if (!g) return NULL;

  int size = g->size;

  // Создается матрица dist, где dist[i][j] — расстояние от i до j
  double **dist = malloc((size + 1) * sizeof(double *));

  for (int i = 1; i <= size; i++) {
    dist[i] = malloc((size + 1) * sizeof(double));
    for (int j = 1; j <= size; j++) {
      // Значения dist инициализируются: 0, если i == j, Вес ребра i→j, если оно
      // существует INF в остальных случаях.
      dist[i][j] =
          (i == j) ? 0
                   : (g->matrix[i - 1][j - 1] ? g->matrix[i - 1][j - 1] : INF);
    }
  }

  // Три вложенных цикла:
  for (int k = 1; k <= size; k++)  // Промежуточная вершина
  {
    for (int i = 1; i <= size; i++)  // Исходная вершина
    {
      for (int j = 1; j <= size; j++)  // Целевая вершина
      {
        // На каждой итерации проверяется, улучшает ли путь через вершину k
        // текущее расстояние i→j.
        if (dist[i][k] + dist[k][j] < dist[i][j])
          dist[i][j] = dist[i][k] + dist[k][j];
      }
    }
  }

  return dist;
}