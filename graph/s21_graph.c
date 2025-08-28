#include "s21_graph.h"

/**
 * @brief Создает новый граф
 *
 * @return Указатель на созданный граф или NULL в случае ошибки
 */
graph *graph_create() {
  graph *g = (graph *)malloc(sizeof(graph));
  if (g) {
    g->matrix = NULL;
    g->size = 0;
  }
  return g;
}

/**
 * @brief Освобождает память, занятую графом
 *
 * @param g Указатель на граф
 */
void graph_free(graph *g) {
  if (g) {
    if (g->matrix) {
      for (int i = 0; i < g->size; i++) {
        free(g->matrix[i]);
      }
      free(g->matrix);
    }
    free(g);
  }
}

/**
 * @brief Загружает граф из файла
 *
 * @param g Указатель на граф
 * @param filename Имя файла
 * @return 0 в случае успеха, -1 в случае ошибки
 */
int load_graph_from_file(graph *g, const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) return -1;

  if (fscanf(file, "%d", &g->size) != 1 || g->size <= 0) {
    fclose(file);
    return -1;
  }

  g->matrix = (int **)malloc(g->size * sizeof(int *));

  for (int i = 0; i < g->size; i++) {
    g->matrix[i] = (int *)malloc(g->size * sizeof(int));

    for (int j = 0; j < g->size; j++) {
      if (fscanf(file, "%d", &g->matrix[i][j]) != 1) {
        for (int k = 0; k <= i; k++) {
          free(g->matrix[k]);
          g->matrix[k] = NULL;
        }
        free(g->matrix);
        g->matrix = NULL;
        fclose(file);
        return -1;
      }
    }
  }
  fclose(file);
  return 0;
}

/**
 * @brief Экспортирует граф в формате DOT
 *
 * @param g Указатель на граф
 * @param filename Имя файла
 * @return 0 в случае успеха, -1 в случае ошибки
 */
int export_graph_to_dot(const graph *g, const char *filename) {
  FILE *file = fopen(filename, "w");
  if (!file) return -1;

  int is_undirected_value = is_undirected(g);

  if (is_undirected_value) {
    fprintf(file, "graph G {\n");
    for (int i = 0; i < g->size; i++) {
      for (int j = i; j < g->size; j++) {
        // Пропускаем петли (i == j) и нулевые веса
        if (i != j && g->matrix[i][j] != 0) {
          fprintf(file, "    %d -- %d [weight=%d];\n", i + 1, j + 1,
                  g->matrix[i][j]);
        }
      }
    }
  } else {
    fprintf(file, "digraph G {\n");
    for (int i = 0; i < g->size; i++) {
      for (int j = 0; j < g->size; j++) {
        if (/*i != j && */ g->matrix[i][j] != 0) {
          fprintf(file, "    %d -> %d [weight=%d];\n", i + 1, j + 1,
                  g->matrix[i][j]);
        }
      }
    }
  }

  fprintf(file, "}\n");
  fclose(file);
  return 0;
}

/**
 * @brief Проверяет, является ли граф неориентированным
 *
 * @param g Указатель на граф
 * @return TRUE, если граф неориентированный, FALSE в противном случае
 */
int is_undirected(const graph *g) {
  for (int i = 0; i < g->size; i++) {
    for (int j = 0; j < i; j++) {
      if (g->matrix[i][j] != g->matrix[j][i]) {
        return FALSE;
      }
    }
  }
  return TRUE;
}

/**
 * @brief Возвращает количество вершин в графе
 *
 * @param g Указатель на граф
 * @return Количество вершин
 */
int graph_get_vertex_count(const graph *g) { return g->size; }

/**
 * @brief Возвращает вес ребра между двумя вершинами
 *
 * @param g Указатель на граф
 * @param from Номер первой вершины
 * @param to Номер второй вершины
 * @return Вес ребра или -1 в случае ошибки
 */
int graph_get_edge_weight(const graph *g, int from, int to) {
  if (from < 1 || to < 1 || from > g->size || to > g->size) return -1;
  return g->matrix[from - 1][to - 1];
}