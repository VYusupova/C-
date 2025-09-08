#include "../s21_graph_algorithms.h"

/**
 * @brief Поиск в ширину в графе от заданной вершины.
 * @note  алгоритм обхода графа, где Очередь (FIFO) используется для хранения
 * вершин, которые предстоит посетить. Систематически обходит все вершины графа.
 * В чем его отличие от обхода в глубину? Обход в глубину "перепрыгивает" между
 * строками списка смежности по 1 вершине за раз, а обход в ширину сразу по всем
 * возможным. Сложность O(V+E) - линейная.
 * @param g Указатель на граф.
 * @param start_vertex Начальная вершина.
 * @return Массив, содержащий результат поиска.
 */
int *breadth_first_search(graph *g, int start_vertex) {
  if (!g || start_vertex < 1 || start_vertex > g->size) return NULL;

  int size = g->size;

  // Посещенные вершины помечаются в массиве visited, чтобы избежать повторного
  // посещения.
  int *visited = calloc(size + 1, sizeof(int));
  int *result = malloc((size + 1) * sizeof(int));

  // Очередь (FIFO) используется для хранения вершин, которые предстоит посетить
  queue *q = queue_create();
  int idx = 0;

  queue_push(q, start_vertex);
  visited[start_vertex] = 1;
  result[idx++] = start_vertex;

  while (q->front) {
    // Извлекается вершина из начала очереди
    int current = queue_pop(q);

    for (int i = 1; i <= size; i++) {
      // Вершины обрабатываются уровень за уровнем (ближайшие соседи → соседи
      // соседей)
      if (g->matrix[current - 1][i - 1] > 0 && !visited[i]) {
        // Все её непосещенные соседи добавляются в конец очереди
        queue_push(q, i);
        visited[i] = 1;
        result[idx++] = i;
      }
    }
  }
  free(visited);
  queue_free(q);
  result[idx] = -1;
  return result;
}
