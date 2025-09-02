#include "../s21_graph.h"
#include "../s21_graph_algorithms.h"
#include <stdio.h>

int main() {
  s21_graph g = graph_init();
  g.load_graph_from_file("test/file_test/t_2_load_export.txt", &g);
  printf("size graph %d\n", g.size);
  g.print_graph_matrix(&g);

  int *visit = depth_first_search(&g, 0);

  printf("visit grap node ");
  for (int i = 0; i < g.size; i++)
    printf("%d - ", visit[i]);
  printf(" \n");

  g.del_graph(&g);
  printf("size graph %d\n", g.size);
  return 0;
}
