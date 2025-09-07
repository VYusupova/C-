#include "../s21_graph_algorithms.h"

/* Параметры алгоритма */
#define MAX_ANTS 50         ///< Количество агентов-муравьев в колонии
#define MAX_ITERATIONS 500  ///< Максимальное число итераций алгоритма
#define ALPHA 1.0           ///< Вес феромона при выборе пути (влияние опыта)
#define BETA 3.0            ///< Вес эвристики (приоритет коротких ребер)
#define RHO 0.4             ///< Коэффициент испарения феромонов (0-1)
#define Q 253.0             ///< Базовая величина для обновления феромонов

/**
 * @brief Структура, представляющая муравья-агента
 * @param path Массив с последовательностью посещенных городов
 * @param visited Массив меток посещения городов (0/1)
 * @param distance Общая длина пройденного маршрута
 */
typedef struct {
  int *path;        ///< Маршрут муравья (размер: graph_size + 1)
  int *visited;     ///< Посещенные города (размер: graph_size)
  double distance;  ///< Суммарная длина пути
} ant;

/**
 * @brief Инициализирует колонию муравьев
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
 * @brief Освобождает ресурсы, занятые колонией муравьев
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
 * @brief Выбирает следующий город в маршруте муравья
 * @param current Текущий город
 * @param g Указатель на граф
 * @param pheromone Матрица феромонов
 * @param visited Массив посещенных городов
 * @return Индекс следующего города или -1 при ошибке
 * @note Вероятность выбора рассчитывается по формуле:
 *       (pheromone^ALPHA) * (1/distance)^BETA
 */
int select_next_city(int current, graph *g, double **pheromone, int *visited) {
  double total = 0.0;
  double probabilities[g->size];

  // Рассчитываем общую сумму для нормализации
  for (int i = 0; i < g->size; i++) {
    if (!visited[i] && g->matrix[current][i] > 0) {
      probabilities[i] = pow(pheromone[current][i], ALPHA) *
                         pow(1.0 / g->matrix[current][i], BETA);
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

/**
 * @brief Решает задачу коммивояжера методом муравьиной колонии (ACO)
 * @note Алгоритм работает в 4 этапа:
 * * 1. Инициализация феромонов
 * * 2. Построение маршрутов муравьями
 * * 3. Испарение феромонов
 * * 4. Обновление феромонов на лучших путях
 * @param g Указатель на граф
 * @return Указатель на структуру с результатом (tsm_result)
 */
tsm_result *solve_traveling_salesman_problem(graph *g) {
  if (!g || g->size < 2) return NULL;

  srand(time(NULL));
  int num_ants = MAX_ANTS;
  int iterations = MAX_ITERATIONS;

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
  best->distance = INFINITY;

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
          ants[a].distance = INFINITY;
          break;
        }
        ants[a].path[step] = next;
        ants[a].visited[next] = 1;
        ants[a].distance += g->matrix[ants[a].path[step - 1]][next];
      }

      // Замыкание цикла (возврат в начальный город)
      if (ants[a].distance < INFINITY) {
        ants[a].distance +=
            g->matrix[ants[a].path[g->size - 1]][ants[a].path[0]];
        ants[a].path[g->size] = ants[a].path[0];
      }
      if (ants[a].distance < INFINITY) {
        // Проверка существования ребра возврата
        if (g->matrix[ants[a].path[g->size - 1]][ants[a].path[0]] == 0) {
          ants[a].distance = INFINITY;
        }
      }

      // Сброс посещенных городов
      memset(ants[a].visited, 0, g->size * sizeof(int));
    }

    // Испарение феромонов
    for (int i = 0; i < g->size; i++) {
      for (int j = 0; j < g->size; j++) {
        pheromone[i][j] *= (1.0 - RHO);
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

      if (ants[a].distance < INFINITY) {
        double deposit = Q / ants[a].distance;
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

  if (best->distance == INFINITY) {
    free(best->vertices);
    free(best);
    return NULL;
  }
  return best;
}