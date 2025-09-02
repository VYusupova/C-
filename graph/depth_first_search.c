#include "../s21_graph_algorithms.h"

/**
 * @brief Нерекурентный поиск в глубину в графе от заданной вершины.
 * @note алгоритм обхода графа, где стек определяет порядок обхода: на каждом
шаге исследуется последняя добавленная вершина, что обеспечивает
углубление в граф, а массив visited гарантирует, что каждая вершина
обрабатывается один раз". Сложность O(V+E) - линейная.
 * @param g Указатель на граф.
 * @param start_vertex Начальная вершина.
 * @return Массив, содержащий результат поиска.
 */
int *depth_first_search(graph *g, int start_vertex) {
  if (!g || start_vertex < 1 || start_vertex > g->size)
    return NULL;

  int size = g->size;

  int *visited = calloc(size + 1, sizeof(int));
  int *result = malloc((size + 1) * sizeof(int));

  // Стек используется для хранения вершин, которые предстоит посетить.
  stack *s = stack_create();
  int idx = 0;

  stack_push(s, start_vertex);

  // Посещенные вершины помечаются отдельно, чтобы избежать повторного
  // посещения.
  visited[start_vertex] = 1;

  result[idx++] = start_vertex;

  while (s->top) {
    // Берется вершина с вершины стека
    int current = stack_top(s);
    int found = 0;

    // Проверяются ее непосещенные соседи
    for (int i = 1; i <= size; i++) {
      if (g->matrix[current - 1][i - 1] > 0 && !visited[i]) {
        // Первый найденный непосещенный сосед добавляется в стек
        stack_push(s, i);

        // и помечается как посещенный
        visited[i] = 1;
        result[idx++] = i;
        found = 1;
        break;
      }
    }
    // Если непосещенных соседей нет — вершина удаляется из стека.
    if (!found)
      stack_pop(s);
  }

  free(visited);
  stack_free(s);
  result[idx] = -1; // Маркер конца результата
  return result;
}