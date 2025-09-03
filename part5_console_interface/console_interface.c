#include "console_define.h"

static void question_print(s21_graph *g) {
  PRINT_QUESTION;
  int user_input;
  scanf("%d", &user_input);
  switch (user_input) {
  case 1:
    g->print_graph_matrix(g);
    break;
  case 2:
    // g->print_graph_dot(g);
    break;
  default:
    ERR_INPUT;
    break;
  }
}

static void load_grap(s21_graph *g) {
  PRINT_LOAD_GRAP;
  char filename[100];
  int c = scanf("%s", filename);
  printf("\n");
  if (1 == c) {
    g->load_graph_from_file(filename, g);
    if (g->size == 0)
      ERR_PRINT_LOAD_GRAP;
    else
      question_print(g);
  } else
    ERR;
}

static void print_DFS(s21_graph *g) {
  int *visit;
  if (g->size == 0)
    ERR_GRAF_EMPTY;
  else {
    printf("введите чиcло от 0 до %d вершину с которой надо начать обход :",
           g->size);
    int vertex = 0;
    if (1 != scanf("%d", &vertex))
      ERR_INPUT_DOT;
    else {
      if (vertex > g->size || vertex < 0)
        ERR_INPUT_DOT;
      else 
        visit = depth_first_search(g, vertex);
      
    }
    printf("обход графа { ");
    for (int i = 0; i < g->size; i++)
      printf("%d  ", visit[i]);
    printf(" }\n");
  }
}

static void print_Dejkstra(s21_graph *g) {
  int short_path = 0;
  if (g->size == 0)
    ERR_GRAF_EMPTY;
  else {
    printf(
        "введите pair vertex от 0 до %d вершину с которой надо начать обход :",
        g->size);
    int start = 0;
    int end = g->size;
    if (2 != scanf("%d %d", &start, &end))
      ERR_INPUT_DOT;
    else {
      if (start > g->size || start < 0 || end > g->size || end < 0 )
        ERR_INPUT_DOT;
      else {
        short_path =
            graph_algorithms_get_shortest_path_between_vertices(g, start, end);
      }
    }
    printf("shortest way is %d", short_path);
  }
}

static void print_Floyd(s21_graph *g) {
  int** short_dist = 0;
  if (g->size == 0)
    ERR_GRAF_EMPTY;
  else {
        short_dist =
            graph_algorithms_get_shortest_paths_between_all_vertices(g);
      }
      printf("\t\tshortest dist \n");
    for (int i = 0; i < g->size; i++) {
      for (int j = 0; j < g->size; j++) {
        printf(" %2d", short_dist[i][j]);
      }
      printf("\n");
  }
    }
    

int main() {
  s21_graph g1 = graph_init();
    s21_graph *g = &g1;
  int user_input;

  int break_flag = 0; 
  
  while (!break_flag) {
  PRINT_CHOOSE;
  scanf("%d", &user_input);
  switch (user_input) {
  case 1:
    load_grap(g);
    break;
  case 2:

    break;
  case 3:
    print_DFS(g);
    break;
  case 4:
    print_Dejkstra(g);
    break;

  case 5:
    print_Floyd(g);
    break;
  case 6:
    break;
  case 7:
    break;
  case 8:
    break_flag = 1;
    break;  
  default:
    ERR_INPUT;
    break;
  }
  }

  return 0;
}
