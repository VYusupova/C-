#ifndef S21_GRAPH_ALGORITHMS_H
#define S21_GRAPH_ALGORITHMS_H

#include "s21_graph_algorithms.h"
#include "s21_graph.h"
#include "stack/stack.h"

#define S21_INF (2147483647 / 4) /* безопасная "бесконечность" */

static void visited_add(int node, int *visited, int len_visit) {
  for (int i = 0; i < len_visit; i++)
    if (0 == visited[i]) {
      visited[i] = node;
      return;  // exit if find first vertex not visited
    }
}

static int node_not_in_visited(int node, int *visit, int len_visit) {
  for (int i = 0; i <= len_visit; i++)
    if (node == visit[i])
      return 0;
  return 1;
}

void put_node_in_stack(stack *s, int node, s21_graph *g, int *visited) {
  for (int i = 0; i < g->size; i++) {
    if (g->matrix[node][i] > 0) {
      if (node_not_in_visited(i + 1, visited, g->size)){
        push(i + 1, s);
        return;
        }
    }
  }
}

/*
Алгоритм поиска в глубину работает следующим образом:

1. поместите любую вершину графа на вершину стека.
2. Возьмите верхний элемент стека и добавьте его в список “Пройденных”.
3. Создайте список смежных вершин для этой вершины. Добавьте те вершины, которых
нет в списке “Пройденных”, в верх стека.
4. Необходимо повторять шаги 2 и 3, пока стек не станет пустым.

*/
static int *dfs_iterative(s21_graph *g, int start_node) {
  int *visited = calloc(g->size, sizeof(int));
  if (g->size == 0)
    perror("_ERR_GRAPH_IS_EMPTY");
  else {
    stack *s = malloc(sizeof(stack));
    s = stack_init(s);
    push(start_node + 1, s);
    visited_add(start_node + 1, visited, g->size);
    put_node_in_stack(s, start_node, g, visited);
    int node = start_node;
    while (s->size > 0) {
      node = top(s);
      if (node_not_in_visited(node, visited, g->size)) {
        visited_add(node, visited, g->size);
        put_node_in_stack(s, node - 1, g, visited);
      } else {
        pop(s);
      }
    }
  }
  return visited;
}

// TO DO  добавить функцию вывода вершин которые были пройдены

int *depth_first_search(s21_graph *graph, int start_vertex) {
  int *visit = dfs_iterative(graph, start_vertex);
  return visit;
}

// int *  breadth_first_search(s21_graph *graph, int start_vertex) {

// }

/* Конструктор */
/*graph_algorithms *graph_algorithms_create(s21_graph *g) {
    if (!g) return NULL;
    graph_algorithms *alg = (graph_algorithms
*)malloc(sizeof(graph_algorithms)); if (!alg) return NULL; alg->g = g; return
alg;
}
*/
/* Деструктор  */
// void graph_algorithms_free(graph_algorithms *alg) {
//    if (alg) free(alg);
//}

/* Алгоритм Дейкстры: кратчайший путь между двумя вершинами в графе с
неотрицательными весами.
Данный алгоритм характеризуется тем, что позволяет находить
оптимальные маршруты и их длину между заданной исходной вершиной и
всеми остальными вершинами графа. Недостаток алгоритма заключается в том,
что при наличии в графе ребер с отрицательными весами, его работа будет
некорректной. Кроме того при работе данный алгоритм не предусматривает петель,
однако он не накладывает ограничения на вид графов для которых будет
использоваться. Сложность O(V²) */

int get_shortest_path_between_vertices(s21_graph *graph, int vertex1,
                                       int vertex2) {
  if (!graph || !graph->matrix || vertex1 >= graph->size ||
      vertex2 >= graph->size)
    return S21_INF;

  size_t n = graph->size;
  int *dist = malloc(n * sizeof(int));
  int *visited = calloc(n, sizeof(int));

  for (size_t i = 0; i < n; ++i)
    dist[i] = S21_INF;
  dist[vertex1] = 0;

  for (size_t i = 0; i < n; ++i) {
    int u = -1;
    for (size_t j = 0; j < n; ++j)
      if (!visited[j] && (u == -1 || dist[j] < dist[u]))
        u = j;

    if (dist[u] == S21_INF)
      break;
    visited[u] = 1;
    for (size_t v = 0; v < n; ++v) {
      int weight = graph->matrix[u][v];
      if (weight >= 0 && dist[u] + weight < dist[v])
        dist[v] = dist[u] + weight;
    }
  }

  int result = dist[vertex2];
  free(dist);
  free(visited);
  return result;
}

/* Алгоритм Флойда-Уоршелла: кратчайшие пути между всеми вершинами */
int **get_shortest_paths_between_all_vertices(s21_graph *graph) {
  if (!graph)
    return NULL;

  size_t n = graph->size;
  int **dist = malloc(n * sizeof(int *));
  for (size_t i = 0; i < n; ++i) {
    dist[i] = malloc(n * sizeof(int));
    for (size_t j = 0; j < n; ++j) {
      if (i == j)
        dist[i][j] = 0;
      else if (graph->matrix[i][j] >= 0)
        dist[i][j] = graph->matrix[i][j];
      else
        dist[i][j] = S21_INF;
    }
  }

  for (size_t k = 0; k < n; ++k)
    for (size_t i = 0; i < n; ++i)
      for (size_t j = 0; j < n; ++j)
        if (dist[i][k] < S21_INF && dist[k][j] < S21_INF &&
            dist[i][k] + dist[k][j] < dist[i][j])
          dist[i][j] = dist[i][k] + dist[k][j];

  return dist;
}


static int conditionsPRIM (s21_graph *g){
int result = 1;
  if (!g) result=0;
  else {
  for (int i = 0; i <= g->size; i++)
    for (int j = 0; j <= g->size; j++){
        // проверка что все ребра положительные
    if (g->matrix[i][j] < 0) result = 0;
      // проверка что граф не ориентированный
    if (g->matrix[i][j] != g->matrix[j][i]) result = 0;
   }
  }  
return result;
}

/* Поиск минимального остовного дерева в графе с помощью алгоритма Прима.
   Алгоритм строит MST, начиная с произвольной вершины и последовательно добавляя рёбра с минимальным весом.
   Алгоритм работает только с неориентированными графами.
   Веса рёбер должны быть положительными.
   Функция вернет NULL для несвязного графа.
 */


int **get_least_spanning_tree(s21_graph *g) 
{
  if (!conditionsPRIM(g)) return NULL;
  int size = g->size;
  int ** mst = malloc(size * sizeof(int *));

  // родительская вершина для i в MST.
  int *parent = malloc((size + 1) * sizeof(int));

  // минимальный вес ребра, соединяющего вершину i с текущим MST (изначально
  // INF).
  double *weight = malloc((size + 1) * sizeof(double));

  // флаг, указывающий, включена ли вершина i в MST
  int *in_mst = calloc((size + 1), sizeof(int));

  for (int i = 1; i <= size; i++) {
    weight[i] = S21_INF;
    mst[i - 1] = calloc(size, sizeof(int));
  }

  weight[1] = 0;      // Начинаем с вершины 1
  parent[1] = -1;  // У стартовой вершины нет родителя

  for (int count = 1; count <= size; count++) {
    // Выбор вершины u с минимальным весом
    int u = -1;
    for (int v = 1; v <= size; v++) {
      if (!in_mst[v] && (u == -1 || weight[v] < weight[u])) u = v;
    }
    // Проверка на несвязность графа
    if (weight[u] == S21_INF) {
      for (int i = 0; i <size; i++)
      	free(mst[i]);
      free(mst);
      free(parent);
      free(weight);
      free(in_mst);
      return NULL;
    }

    in_mst[u] = 1;

    // Если u не стартовая вершина, добавляется ребро parent[u] → u в mst
    if (parent[u] != -1) {
      mst[parent[u] - 1][u - 1] = g->matrix[parent[u] - 1][u - 1];
      mst[u - 1][parent[u] - 1] = g->matrix[u - 1][parent[u] - 1];
    }

    // Обновление ключей для соседей u. Если ребро u → v имеет меньший вес, чем
    // текущий weight[v], обновляется weight[v] и parent[v].
    for (int v = 1; v <= size; v++) {
      if (g->matrix[u - 1][v - 1] && !in_mst[v] &&
          g->matrix[u - 1][v - 1] < weight[v]) {
        parent[v] = u;
        weight[v] = g->matrix[u - 1][v - 1];
      }
    }
  }

  free(parent);
  free(weight);
  free(in_mst);
  return mst;
}
#endif
