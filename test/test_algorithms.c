#include "test.h"

START_TEST(test_dfs) {
  graph g = graph_init();
  g = g.load_graph_from_file("file_test/t_dfs.txt");

  int *result = depth_first_search(&g, 1);
  ck_assert_int_eq(result[0], 2);
  ck_assert_int_eq(result[1], 3);
  ck_assert_int_eq(result[2], 0);
  free(result);
  g.del_graph(&g);
}
END_TEST

START_TEST(test_bfs) {
  graph g = graph_init();
  g = g.load_graph_from_file("file_test/t_bfs.txt");

  int *result = breadth_first_search(&g, 0);
  ck_assert_int_eq(result[0], 1);
  ck_assert(result[1] == 2);
  free(result);
  g.del_graph(&g);
}
END_TEST

START_TEST(test_dijkstra) {
  graph g = graph_init();
  g = g.load_graph_from_file("file_test/t_dijkstra.txt");
  ck_assert_double_eq(get_shortest_path_between_vertices(&g, 0, 2), 7);
  g.del_graph(&g);
}
END_TEST

START_TEST(test_floyd_warshall) {
  graph g = graph_init();
  g = g.load_graph_from_file("file_test/t_dfs.txt");

  int **dist = get_shortest_paths_between_all_vertices(&g);
  if (dist) {
    ck_assert_double_eq(dist[1][2], 1);
    for (int i = 0; i < g.size; i++)
      if (dist[i]) free(dist[i]);
    free(dist);
  }
  g.del_graph(&g);
}
END_TEST

START_TEST(test_prim) {
  graph g = graph_init();
  g = g.load_graph_from_file("file_test/t_prim.txt");

  int **mst = get_least_spanning_tree(&g);
  ck_assert_int_eq(mst[0][1], 2);
  ck_assert_int_eq(mst[1][2], 1);
  for (int i = 0; i < g.size; i++) free(mst[i]);
  free(mst);

  g.del_graph(&g);
}
END_TEST

START_TEST(test_prim_ne) {
  graph g = graph_init();
  g = g.load_graph_from_file("file_test/t_prim_ne.txt");

  ck_assert_ptr_null(get_least_spanning_tree(&g));
  g.del_graph(&g);
}
END_TEST

START_TEST(test_tsp_ant_colony_algoriht) {
  graph g = graph_init();
  g = g.load_graph_from_file("file_test/test_sole_trev.txt");

  tsm_result *res = solve_traveling_salesman_problem(&g);
  ck_assert(res->distance != 0);
  free(res->vertices);
  free(res);
  g.del_graph(&g);
}
END_TEST

START_TEST(test_tsp_ant_colony_algoriht_ne) {
  graph g = graph_init();
  g = g.load_graph_from_file("file_test/test_sole_trev_ne.txt");

  tsm_result *res = solve_traveling_salesman_problem(&g);
  ck_assert_ptr_null(res);

  g.del_graph(&g);
}
END_TEST

START_TEST(test_greedy_algoriht) {
  graph g = graph_init();
  const int matrix[4][4] = {
      {0, 10, 15, 20}, {10, 0, 35, 25}, {15, 35, 0, 30}, {20, 25, 30, 0}};
  g.size = 4;
  g.matrix = malloc(4 * sizeof(int *));
  for (int i = 0; i < 4; i++) {
    g.matrix[i] = malloc(4 * sizeof(int));
    memcpy(g.matrix[i], matrix[i], 4 * sizeof(int));
  }

  tsm_result *res = greedy_tsp(&g);
  ck_assert(res->distance == 80);
  free(res->vertices);
  free(res);
  g.del_graph(&g);
}
END_TEST

START_TEST(test_tsp_ant_greedy_algoriht_ne) {
  graph g = graph_init();
  g = g.load_graph_from_file("file_test/test_sole_trev_ne.txt");

  ck_assert_ptr_null(greedy_tsp(&g));
  g.del_graph(&g);
}
END_TEST

START_TEST(test_nearest_neighbor) {
  graph g = graph_init();
  g = g.load_graph_from_file("file_test/t_dijkstra.txt");
  tsm_result *res = nearest_neighbor_tsp(&g);
  
  if (res) {
    ck_assert(res->distance == 17);
    if (res->vertices) free(res->vertices);
    free(res);
  }
  g.del_graph(&g);
}
END_TEST

Suite *test_algorithms(void) {
  Suite *s =
      suite_create("\n\033[35;107m  TESTING S21_GRAPH_ALGORITHMS \033[0m");
  TCase *tc = tcase_create("test_algorithms");

  suite_add_tcase(s, tc);

  tcase_add_test(tc, test_dfs);
  tcase_add_test(tc, test_bfs);
  tcase_add_test(tc, test_dijkstra);
  tcase_add_test(tc, test_floyd_warshall);
  tcase_add_test(tc, test_prim);
  tcase_add_test(tc, test_prim_ne);
  tcase_add_test(tc, test_tsp_ant_colony_algoriht);
  tcase_add_test(tc, test_tsp_ant_colony_algoriht_ne);
  tcase_add_test(tc, test_greedy_algoriht);
  tcase_add_test(tc, test_tsp_ant_greedy_algoriht_ne);
  tcase_add_test(tc, test_nearest_neighbor);

  return s;
}