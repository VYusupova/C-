#include "console_define.h"

static int valid_scanf(int *input) {
  int result = 1;
  if (1 != scanf("%d", input)) {
    ERR;
    /* После неудачной попытки считывания scanf(),
      введенные данные (которые не являются числом)
      остаются в буфере ввода. Если их не очистить,
      они могут помешать последующим операциям считывания. */
    while (getchar() != '\n');
    /* читает символы до конца строки (\n), эффективно очищая буфер.*/
    result = 0;
  }
  return result;
}

static void print_matrix(const graph *g) {
  printf("size graph %02d\n", g->size);
  if (g->matrix == NULL) {
    printf("ERROR\n");
  } else {
    for (int i = 0; i < g->size; i++) {
      for (int j = 0; j < g->size; j++) {
        printf(" %2d", g->matrix[i][j]);
      }
      printf("\n");
    }
  }
}

static void print_dot(const graph *graph) {
  if (graph->size == 0) perror(_ERR_SIZE);
  int digraph = graph->is_digraph(graph);
  if (digraph == 0) {
    printf("graph {\n");
  } else {
    printf("digraph {\n");
  }
  for (int i = 0; i < graph->size; i++) {
    printf("%c;\n", 'A' + i);
  }
  for (int i = 0; i < graph->size; i++) {
    for (int j = i; j < graph->size; j++) {
      if (i != j && graph->matrix[i][j] != 0 && digraph == 0) {
        printf("%c -- %c;\n", 'A' + i, 'A' + j);
      } else if (graph->matrix[i][j] != 0 && graph->matrix[i][j] != -1 &&
                 digraph == 1) {
        printf("%c -> %c;\n", 'A' + i, 'A' + j);
      }
    }
  }
  printf("}\n");
}

static void question_print(const graph *g) {
  PRINT_QUESTION;
  int user_input;
  if (!valid_scanf(&user_input)) user_input = 0;
  switch (user_input) {
    case 1:
      print_matrix(g);
      break;
    case 2:
      print_dot(g);
      break;
    default:
      break;
  }
}

static graph load_grap() {
  PRINT_LOAD_GRAP;
  graph g = graph_init();
  char filename[256];
  if (1 == scanf("%255s", filename)) {
    printf("\n");
    g = g.load_graph_from_file(filename);
    if (g.size == 0) {
      ERR_PRINT_LOAD_GRAP;
    } else {
      question_print(&g);
    }
  } else {
    ERR;
  }
  return g;
}

static void export_infile_dot(graph *g) {
  PRINT_OUT_GRAP;
  char filename[256];
  int c = scanf("%255s", filename);
  printf("\n");
  if (1 == c) {
    if (g->size == 0)
      ERR_PRINT_LOAD_GRAP;
    else
      g->export_graph_to_dot(filename, g);
  } else
    ERR;
}

static void print_DFS_BFS(graph *g, int b) {
  if (g->size == 0)
    ERR_GRAF_EMPTY;
  else {
    const int *visit = NULL;
    printf(START_VERTEX, g->size - 1);
    int vertex = 0;
    if (!valid_scanf(&vertex)) {
      ERR_INPUT_DOT;
      vertex = 0;
    }
    if (vertex > g->size || vertex < 0)
      ERR_INPUT_DOT;
    else if (b == 1)
      visit = depth_first_search(g, vertex);
    else
      visit = breadth_first_search(g, vertex);
    if (visit) {
      printf("обход графа { ");
      for (int i = 0; i < g->size; i++) printf("%d  ", visit[i]);
      printf(" }\n");
    }
  }
}

static void print_Dijkstra(graph *g) {
  if (g->size == 0)
    ERR_GRAF_EMPTY;
  else {
    printf(
        "введите пару вершин от 0 до %d между которыми надо вычилить "
        "расстояние :",
        g->size - 1);
    int start = 0;
    int end = g->size;
    if (!valid_scanf(&start) || !valid_scanf(&end)) {
      ERR_INPUT_DOT;
      start = 0;
      end = g->size;
    }
    if (start > g->size || start < 0 || end > g->size || end < 0)
      ERR_INPUT_DOT;
    else {
      int short_path = 0;
      short_path = get_shortest_path_between_vertices(g, start, end);
      printf("расстояние = %d \n", short_path);
    }
  }
}

#define S21_INF (2147483647 / 4) /* безопасная "бесконечность" */

static void out_matrix(int size, int **m) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (m[i][j] == S21_INF)
        printf(" INF");
      else
        printf(" %3d", m[i][j]);
    }
    printf("\n");
  }
}

static void print_Floyd(graph *g) {
  int **short_dist = 0;
  if (g->size == 0)
    ERR_GRAF_EMPTY;
  else {
    short_dist = get_shortest_paths_between_all_vertices(g);
  }
  printf("\t\tкратчайшие путь = \n");
  out_matrix(g->size, short_dist);
}

static void print_least_spanning_tree(graph *g) {
  int **mst = get_least_spanning_tree(g);
  if (mst != NULL) {
    printf("минимальное остовное дерево :\n");
    out_matrix(g->size, mst);
    for (int i = 0; i < g->size; i++) free(mst[i]);
    free(mst);
  } else
    ERR_GRAF_NOT_VALID;
}

static int question_N() {
  int ui = 1;
  PRINT_QUESTION_N;
  if (!valid_scanf(&ui)) ui = 0;
  while (ui < 1 || ui > 1000) {
    ui = 1;
    ERR_RANGE;
    PRINT_QUESTION_N;
    if (!valid_scanf(&ui)) ui = 0;
  }
  return ui;
}

void func_time(int n, graph *g, tsm_result *(*func_ptr)(graph *g),
               const char *str) {
  clock_t start = clock();
  int count = 0;
  tsm_result *t = NULL;
  while (count < n) {
    t = (*func_ptr)(g);
    count++;
    if (t == NULL) break;
  }
  if (t == NULL) {
    ERR_GRAF_NOT_VALID;
  } else {
    clock_t end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\t %s алгоритм = { ", str);
    for (int i = 0; i < g->size; i++) printf("%d ", t->vertices[i]);
    printf(" } distance = %f ", t->distance);
    printf(" время выполнения %f sec\n", cpu_time_used);
    free(t);
  }
}

static void analitic_solve_traviling(graph *g) {
  int n = question_N();
  if (g->size > 1) {
    printf(
        "сравнительное исследование скорости работы трёх алгоритмов при N = "
        "%d:\n",
        n);
    tsm_result *(*func_solve)(graph *g);
    func_solve = solve_traveling_salesman_problem;
    func_time(n, g, func_solve, "     муравьиный ");
    func_solve = greedy_tsp;
    func_time(n, g, func_solve, "         жадный ");
    func_solve = nearest_neighbor_tsp;
    func_time(n, g, func_solve, "ближнего соседа ");
  } else {
    ERR_GRAF_NOT_VALID;
  }
}

static void solve_traviling(graph *g) {
  if (g->size > 1) {
    tsm_result *(*func_solve)(graph *g);
    func_solve = solve_traveling_salesman_problem;
    func_time(1, g, func_solve, "муравьиный ");
  } else {
    ERR_GRAF_NOT_VALID;
  }
}

int main() {
  printf("start\n");
  graph g;
  int user_input;

  int break_flag = 0;

  while (!break_flag) {
    PRINT_CHOOSE;
    if (!valid_scanf(&user_input)) user_input = 10;
    switch (user_input) {
      case 0:
        break_flag = 1;
        break;
      case 1:
        g = load_grap();
        break;
      case 2:
        print_DFS_BFS(&g, 0);
        break;
      case 3:
        print_DFS_BFS(&g, 1);
        break;
      case 4:
        print_Dijkstra(&g);
        break;
      case 5:
        print_Floyd(&g);
        break;
      case 6:
        print_least_spanning_tree(&g);
        break;
      case 7:
        solve_traviling(&g);
        break;
      case 8:
        export_infile_dot(&g);
        break;
      case 9:
        analitic_solve_traviling(&g);
        break;
      default:
        ERR_INPUT;
        break;
    }
  }

  return 0;
}
