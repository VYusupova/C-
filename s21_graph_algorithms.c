#ifndef S21_GRAPH_ALGORITHMS_C
#define S21_GRAPH_ALGORITHMS_C

#include "s21_graph_algorithms.h"

#include <math.h>
#include <time.h>

#define S21_INF (2147483647 / 4) /* безопасная "бесконечность" */

/*Структура, представляющая муравья-агента */
typedef struct {
  int *path;
  int *visited;
  double distance;
} ant;

/*Поиск в ширину использует очередь
1. Выбирается произвольная вершина в графе и помещается в очередь.
2. В очередь помещаются все вершины графа смежные с уже находящейся в очереди
вершиной, после чего эта вершина выталкивается из очереди.
3. Выполняется пункт 2 для всех вершин, находящихся в очереди.*/

int *breadth_first_search(graph *graph, int start_vertex) {
  int *visited = calloc(graph->size, sizeof(int));
  int *visit = calloc(graph->size, sizeof(int));

  if (graph->size == 0) {
    perror("_ERR_GRAPH_IS_EMPTY");
    free(visit);
  } else {
    int j = 0;
    visited[start_vertex] = 1;
    visit[j] = start_vertex + 1;
    j++;
    queue *q = create_queue(graph->size);
    enqueue(q, start_vertex);

    while (!is_empty(q)) {
      int current_vertex = dequeue(q);
      const int *temp = graph->matrix[current_vertex];
      int i = 0;
      while (i < graph->size) {
        if (temp[i] != 0) {
          int adj_vertex = i;
          if (visited[adj_vertex] == 0) {
            visited[adj_vertex] = 1;
            visit[j] = adj_vertex + 1;
            j++;
            enqueue(q, adj_vertex);
          }
        }
        i++;
      }
    }
    free_queue(q);
  }
  free(visited);
  return visit;
}

static void visited_add(int node, int *visited, int len_visit) {
  for (int i = 0; i < len_visit; i++)
    // кладем в первую пустую ячейку
    if (0 == visited[i]) {
      visited[i] = node;
      i = len_visit;
    }
}

static int node_not_in_visited(int node, const int *visit, int len_visit) {
  for (int i = 0; i < len_visit; i++)
    if (node == visit[i]) return 0;
  return 1;
}

void put_node_in_stack(stack *s, int node, const graph *g, const int *visited) {
  for (int i = 0; i < g->size; i++) {
    if (g->matrix[node][i] > 0) {
      if (node_not_in_visited(i + 1, visited, g->size)) {
        push(i + 1, s);
        i = g->size;
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

int *depth_first_search(const graph *graph, int start_vertex) {
  int *visited = calloc(graph->size, sizeof(int));
  if (graph->size == 0) {
    perror("_ERR_GRAPH_IS_EMPTY");
    free(visited);
  } else {
    stack *s = malloc(sizeof(stack));
    s = stack_init(s);
    int node = start_vertex;
    push(node + 1, s);
    visited_add(node + 1, visited, graph->size);
    put_node_in_stack(s, start_vertex, graph, visited);

    while (s->size > 0) {
      node = top(s);
      if (node_not_in_visited(node, visited, graph->size)) {
        visited_add(node, visited, graph->size);
        put_node_in_stack(s, node - 1, graph, visited);
      } else {
        pop(s);
      }
    }
    stack_free(s);
  }
  return visited;
}

/* Алгоритм Дейкстры: кратчайший путь между двумя вершинами в графе с
неотрицательными весами.
Данный алгоритм характеризуется тем, что позволяет находить
оптимальные маршруты и их длину между заданной исходной вершиной и
всеми остальными вершинами графа. Недостаток алгоритма заключается в том,
что при наличии в графе ребер с отрицательными весами, его работа будет
некорректной. Кроме того при работе данный алгоритм не предусматривает петель,
однако он не накладывает ограничения на вид графов для которых будет
использоваться. Сложность O(V²) */

int get_shortest_path_between_vertices(graph *graph, int vertex1, int vertex2) {
  if (!graph || !graph->matrix || vertex1 >= graph->size ||
      vertex2 >= graph->size)
    return S21_INF;

  size_t n = graph->size;
  int *dist = malloc(n * sizeof(int));
  int *visited = calloc(n, sizeof(int));

  for (size_t i = 0; i < n; ++i) dist[i] = S21_INF;
  dist[vertex1] = 0;

  for (size_t i = 0; i < n; ++i) {
    int u = -1;
    for (size_t j = 0; j < n; ++j)
      if (!visited[j] && (u == -1 || dist[j] < dist[u])) u = j;

    if (dist[u] == S21_INF) break;
    visited[u] = 1;
    for (size_t v = 0; v < n; ++v) {
      int weight = graph->matrix[u][v];
      if (weight >= 0 && dist[u] + weight < dist[v]) dist[v] = dist[u] + weight;
    }
  }

  int result = dist[vertex2];
  free(dist);
  free(visited);
  return result;
}

/* Алгоритм Флойда-Уоршелла: кратчайшие пути между всеми вершинами */
int **get_shortest_paths_between_all_vertices(graph *graph) {
  if (graph->size <= 0) {
    perror("_ERR_GRAPH_IS_EMPTY");
    return NULL;
  } else {
    int n = graph->size;
    int **dist = (int **)calloc(n, sizeof(int *));
    if (dist)
      for (size_t i = 0; i < n; ++i) {
        dist[i] = (int *)calloc(n, sizeof(int));
        if (!dist[i]) {
          while (i > 0) {
            free(dist[i]);
            i--;
          }
          free(dist);
          break;
        }
      }
    else
      free(dist);

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (i == j)
          dist[i][j] = 0;
        else if (graph->matrix[i][j] != 0)
          dist[i][j] = graph->matrix[i][j];
        else
          dist[i][j] = S21_INF;
      }
    }

    for (size_t k = 0; k < n; ++k) {
      for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
          if (dist[i][k] != S21_INF && dist[k][j] != S21_INF &&
              dist[i][k] + dist[k][j] < dist[i][j]) {
            dist[i][j] = dist[i][k] + dist[k][j];
          }
        }
      }
    }

    return dist;
  }
}

/* Поиск минимального остовного дерева в графе с помощью алгоритма Прима.
   Алгоритм строит MST, начиная с произвольной вершины и последовательно
   добавляя рёбра с минимальным весом. Алгоритм работает только с
   неориентированными графами. Веса рёбер должны быть положительными. Функция
   вернет NULL для несвязного графа.
 */

static int conditionsPRIM(const graph *g) {
  int result = 1;
  if (!g)
    result = 0;
  else {
    for (int i = 0; i < g->size; i++)
      for (int j = 0; j < g->size; j++) {
        // проверка что все ребра положительные
        if (g->matrix[i][j] < 0) {
          result = 0;
        }
        // проверка что граф не ориентированный
        if (g->matrix[i][j] != g->matrix[j][i]) result = 0;
      }
  }
  return result;
}

static void free_pw(int *p, double *w, int *v) {
  free(p);
  free(w);
  free(v);
}

int **get_least_spanning_tree(graph *g) {
  if (conditionsPRIM(g) != 1) return NULL;
  int size = g->size;
  int **mst = malloc(size * sizeof(int *));

  int *parent = malloc((size + 1) * sizeof(int));
  double *weight = malloc((size + 1) * sizeof(double));
  int *in_mst = calloc((size + 1), sizeof(int));

  for (int i = 1; i <= size; i++) {
    weight[i] = S21_INF;
    mst[i - 1] = calloc(size, sizeof(int));
  }

  weight[1] = 0;  // Начинаем с вершины 1
  parent[1] = -1;  // У стартовой вершины нет родителя

  for (int count = 1; count <= size; count++) {
    // Выбор вершины u с минимальным весом
    int u = -1;
    for (int v = 1; v <= size; v++) {
      if (!in_mst[v] && (u == -1 || weight[v] < weight[u])) u = v;
    }
    // Проверка на несвязность графа
    if (weight[u] == S21_INF) {
      for (int i = 0; i < size; i++) free(mst[i]);
      free(mst);
      free_pw(parent, weight, in_mst);
      return NULL;
    }

    in_mst[u] = 1;

    // Если u не стартовая вершина, добавляется ребро parent[u] → u в mst
    if (parent[u] != -1) {
      mst[parent[u] - 1][u - 1] = g->matrix[parent[u] - 1][u - 1];
      mst[u - 1][parent[u] - 1] = g->matrix[u - 1][parent[u] - 1];
    }

    // Обновление ключей для соседей. Если ребро  имеет меньший вес, чем
    // текущий, обновляется вес и роидтель.
    for (int v = 1; v <= size; v++) {
      if (g->matrix[u - 1][v - 1] && !in_mst[v] &&
          g->matrix[u - 1][v - 1] < weight[v]) {
        parent[v] = u;
        weight[v] = g->matrix[u - 1][v - 1];
      }
    }
  }

  free_pw(parent, weight, in_mst);
  return mst;
}

/**
  Инициализирует колонию муравьев
 * @param num_ants Количество муравьев
 * @param graph_size Число вершин графа
 * @return Указатель на массив структур ant
 * @note Выделяет память под пути и метки посещения для каждого муравья
 */
ant *init_ants(int num_ants, int graph_size) {
  ant *ants = malloc(num_ants * sizeof(ant));
  for (int i = 0; i < num_ants; i++) {
    ants[i].path = malloc((graph_size + 1) * sizeof(int));
    ants[i].visited = calloc(graph_size, sizeof(int));
    ants[i].distance = 0.0;
  }
  return ants;
}

/**
  Освобождает ресурсы, занятые колонией муравьев
 * @param ants Указатель на массив муравьев
 * @param num_ants Количество муравьев
 */
void free_ants(ant *ants, int num_ants) {
  for (int i = 0; i < num_ants; i++) {
    free(ants[i].path);
    free(ants[i].visited);
  }
  free(ants);
}

/**
  Выбирает следующий город в маршруте муравья
 * @param current Текущий город
 * @param g Указатель на граф
 * @param pheromone Матрица феромонов
 * @param visited Массив посещенных городов
 * @return Индекс следующего города или -1 при ошибке
 * @note Вероятность выбора рассчитывается по формуле:
 *       (pheromone^ALPHA) * (1/distance)^BETA
 */
int select_next_city(int current, const graph *g, double **pheromone,
                     const int *visited) {
  double total = 0.0;
  double probabilities[g->size];

  // Рассчитываем общую сумму для нормализации
  for (int i = 0; i < g->size; i++) {
    if (!visited[i] && g->matrix[current][i] > 0) {
      probabilities[i] =
          pow(pheromone[current][i], 1) * pow(1.0 / g->matrix[current][i], 3);
      total += probabilities[i];
    } else {
      probabilities[i] = 0.0;
    }
  }

  if (total == 0.0) return -1;

  // Рулеточный выбор
  double r = (double)rand() / RAND_MAX * total;
  double sum = 0.0;
  for (int i = 0; i < g->size; i++) {
    if (!visited[i] && g->matrix[current][i] > 0) {
      sum += probabilities[i];
      if (sum >= r) return i;
    }
  }
  return -1;
}

/*
Решение задачи коммивояжера методом муравьиной колонии (ACO)
 Алгоритм работает в 4 этапа:
 1. Инициализация феромонов
 2. Построение маршрутов муравьями
 3. Испарение феромонов
 4. Обновление феромонов на лучших путях
 */
tsm_result *solve_traveling_salesman_problem(graph *g) {
  if (!g || g->size < 2) return NULL;

  srand(time(NULL));
  int num_ants = 50;  // Количество агентов-муравьев в колонии
  int iterations = 500;

  // Инициализация феромонов
  double **pheromone = malloc(g->size * sizeof(double *));
  for (int i = 0; i < g->size; i++) {
    pheromone[i] = malloc(g->size * sizeof(double));
    for (int j = 0; j < g->size; j++) {
      pheromone[i][j] = (g->matrix[i][j] > 0) ? 0.1 : 0.0;
    }
  }

  ant *ants = init_ants(num_ants, g->size);
  tsm_result *best = malloc(sizeof(tsm_result));
  best->vertices = malloc((g->size + 1) * sizeof(int));
  best->distance = S21_INF;

  // Основной цикл оптимизации
  for (int iter = 0; iter < iterations; iter++) {
    // Построение путей муравьями
    for (int a = 0; a < num_ants; a++) {
      // Случайный стартовый город
      int start = rand() % g->size;
      ants[a].path[0] = start;
      ants[a].visited[start] = 1;

      // Пошаговое построение маршрута
      for (int step = 1; step < g->size; step++) {
        int next = select_next_city(ants[a].path[step - 1], g, pheromone,
                                    ants[a].visited);
        if (next == -1) {
          ants[a].distance = S21_INF;
          break;
        }
        ants[a].path[step] = next;
        ants[a].visited[next] = 1;
        ants[a].distance += g->matrix[ants[a].path[step - 1]][next];
      }

      // Замыкание цикла (возврат в начальный город)
      if (ants[a].distance < S21_INF) {
        ants[a].distance +=
            g->matrix[ants[a].path[g->size - 1]][ants[a].path[0]];
        ants[a].path[g->size] = ants[a].path[0];
      }
      if (ants[a].distance < S21_INF) {
        // Проверка существования ребра возврата
        if (g->matrix[ants[a].path[g->size - 1]][ants[a].path[0]] == 0) {
          ants[a].distance = S21_INF;
        }
      }

      // Сброс посещенных городов
      memset(ants[a].visited, 0, g->size * sizeof(int));
    }

    // Испарение феромонов
    for (int i = 0; i < g->size; i++) {
      for (int j = 0; j < g->size; j++) {
        pheromone[i][j] *= (1.0 - 0.4);
      }
    }

    // Обновление феромонов на найденных путях
    for (int a = 0; a < num_ants; a++) {
      if (ants[a].distance < best->distance) {
        best->distance = ants[a].distance;
        for (int i = 0; i <= g->size; i++) {
          best->vertices[i] = ants[a].path[i] + 1;
        }
      }

      if (ants[a].distance < S21_INF) {
        double deposit = 253 / ants[a].distance;
        for (int i = 0; i < g->size; i++) {
          int from = ants[a].path[i];
          int to = ants[a].path[i + 1];

          // Обновление для неориентированного графа
          pheromone[from][to] += deposit;
          pheromone[to][from] += deposit;
        }
      }
    }
  }

  // Освобождение ресурсов
  for (int i = 0; i < g->size; i++) free(pheromone[i]);
  free(pheromone);
  free_ants(ants, num_ants);

  if (best->distance == S21_INF) {
    free(best->vertices);
    free(best);
    return NULL;
  }
  return best;
}

/*
 Решение задачи коммивояжера с помощью жадного алгоритма.
 Алгоритм для быстрого поиска приближенного решения TSM =)).
 Начинает с фиксированной стартовой вершины (например, 1).
 На каждом шаге выбирает ближайшую непосещенную вершину.
 Формирует цикл, возвращаясь в стартовую вершину. Сложность O(n²)
 */

static int next_min_node(int current, const int *visited, graph *g,
                         int *min_dist) {
  int next = -1;
  for (int j = 0; j < g->size; j++) {
    int edge = g->matrix[current][j];
    if (!visited[j] && edge > 0 && edge < *min_dist) {
      *min_dist = edge;
      next = j;
    }
  }
  return next;
}

static void free_tsm(tsm_result *t) {
  if (t) {
    free(t->vertices);
    free(t);
  }
}

tsm_result *greedy_tsp(graph *g) {
  tsm_result *tsm = NULL;
  if (g->size == 0)
    perror("_ERR_GRAPH_IS_EMPTY");
  else {
    tsm = malloc(sizeof(tsm_result));
    tsm->vertices = malloc((g->size + 1) * sizeof(int));
    tsm->distance = 0;

    int *visited = calloc(g->size, sizeof(int));
    int current = 0;
    tsm->vertices[0] = 1;
    visited[0] = 1;
    for (int i = 1; i < g->size; i++) {
      int next = -1;
      int min_dist = INT_MAX;
      next = next_min_node(current, visited, g, &min_dist);
      if (next == -1) {
        free(tsm->vertices);
        free(tsm);
        tsm = NULL;
        break;
      }
      tsm->vertices[i] = next + 1;
      tsm->distance += min_dist;
      visited[next] = 1;
      current = next;
    }
    if (tsm) {
      // проверяем существует ли обратное ребро
      if (g->matrix[current][0] <= 0) {
        free_tsm(tsm);
      } else {
        tsm->vertices[g->size] = 1;
        tsm->distance += g->matrix[current][0];
      }
    }
    free(visited);
  }
  return tsm;
}

/*
 Решение задачи коммивояжера с помощью алгоритма ближайшего соседа.
 Улучшение жадного алгоритма за счет перебора всех стартовых вершин.
Запускает жадный алгоритм для каждой вершины как стартовой.
Выбирает лучшее решение среди всех вариантов. Сложность: Остается O(n²)
Меньшая зависимость от выбора старта: Шанс найти более короткий путь.
 */

tsm_result *nearest_neighbor_tsp(graph *g) {
  tsm_result *best = NULL;

  if (g->size < 2)
    perror("_ERR_GRAPH_IS_EMPTY");
  else {
    for (int start = 0; start < g->size; start++) {
      tsm_result *res = malloc(sizeof(tsm_result));
      res->vertices = (int *)calloc((g->size + 1), sizeof(int));
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
        next = next_min_node(current, visited, g, &min_dist);

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
          if (0 == visited[i]) {
            valid = 0;
            break;
          }
        }
        // Проверка существования последнего ребра
        if (valid && g->matrix[current][start] == 0) {
          valid = 0;
        }
        res->distance += valid ? g->matrix[current][start] : S21_INF;
        res->vertices[g->size] = start + 1;  // Замыкание цикла
      }
      // // Обновление лучшего результата только для валидных путей
      if (valid && res->distance < S21_INF) {
        if (!best || res->distance < best->distance) {
          if (best) {
            if (best->vertices) free(best->vertices);
            free(best);
          }
          best = res;
        } else {
          if (res) {
            if (res->vertices) free(res->vertices);
            free(res);
          }
        }
      } else {
        { free_tsm(best); }
      }
      free(visited);
    }
  }

  return best;
}

#endif
