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
  if (g->size == 0) {
    printf("граф пустой! загрузите граф, потом может построю обход =)\n");
  } else {
    printf("введите чило от 0 до %d вершину с которой надо начать обход :",
           g->size);
    int vertex = 0;
    if (1 != scanf("%d", &vertex))
      ERR_INPUT_DOT
    else {
      if (vertex > g->size)
        ERR_INPUT_DOT
      else {
        visit = depth_first_search(g, vertex);
      }
    }
    printf("обход графа { ");
    for (int i = 0; i < g->size; i++)
      printf("%d  ", visit[i]);
    printf(" }\n");
  }
}

void console(s21_graph *g) {
  int user_input;
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
    break;
  case 5:
    break;
  case 6:
    break;
  case 7:
    break;
  default:
    ERR_INPUT;
    break;
  }
}

int main() {
  s21_graph g = graph_init();

  int break_flag = 0; // TO DO переделать
  while (break_flag != 3) {
    console(&g);
    break_flag++;
  }

  return 0;
}
