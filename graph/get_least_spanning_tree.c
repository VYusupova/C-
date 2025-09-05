#include "../s21_graph_algorithms.h"

/**
 * @brief Поиск минимального остовного дерева в графе с помощью алгоритма Прима.
 * @note Алгоритм строит MST, начиная с произвольной вершины и последовательно
 * добавляя рёбра с минимальным весом.
 * ОграниченияЖ:
 * * Неориентированные графы: Алгоритм работает только с неориентированными
 * графами.
 * * Веса рёбер должны быть ≥ 0.
 * * Функция вернет NULL для несвязного графа.
 * @param graph Указатель на граф.
 * @return Указатель на мимальное остовное дерево.
 */
graph *get_least_spanning_tree(graph *g) {
  if (!g) return NULL;

  int size = g->size;
  graph *mst = graph_create();
  mst->size = size;
  mst->matrix = malloc(size * sizeof(int *));

  // родительская вершина для i в MST.
  int *parent = malloc((size + 1) * sizeof(int));

  // минимальный вес ребра, соединяющего вершину i с текущим MST (изначально
  // INF).
  double *key = malloc((size + 1) * sizeof(double));

  // флаг, указывающий, включена ли вершина i в MST
  int *in_mst = calloc((size + 1), sizeof(int));

  for (int i = 1; i <= size; i++) {
    key[i] = INF;
    mst->matrix[i - 1] = calloc(size, sizeof(int));
  }

  key[1] = 0;      // Начинаем с вершины 1
  parent[1] = -1;  // У стартовой вершины нет родителя

  for (int count = 1; count <= size; count++) {
    // Выбор вершины u с минимальным key
    int u = -1;
    for (int v = 1; v <= size; v++) {
      if (!in_mst[v] && (u == -1 || key[v] < key[u])) u = v;
    }
    // Проверка на несвязность графа
    if (key[u] == INF) {
      graph_free(mst);
      free(parent);
      free(key);
      free(in_mst);
      return NULL;
    }

    in_mst[u] = 1;

    // Если u не стартовая вершина, добавляется ребро parent[u] → u в mst
    if (parent[u] != -1) {
      mst->matrix[parent[u] - 1][u - 1] = g->matrix[parent[u] - 1][u - 1];
      mst->matrix[u - 1][parent[u] - 1] = g->matrix[u - 1][parent[u] - 1];
    }

    // Обновление ключей для соседей u. Если ребро u → v имеет меньший вес, чем
    // текущий key[v], обновляется key[v] и parent[v].
    for (int v = 1; v <= size; v++) {
      if (g->matrix[u - 1][v - 1] && !in_mst[v] &&
          g->matrix[u - 1][v - 1] < key[v]) {
        parent[v] = u;
        key[v] = g->matrix[u - 1][v - 1];
      }
    }
  }

  free(parent);
  free(key);
  free(in_mst);
  return mst;
}