#include "./test.h"

START_TEST(test_dfs) {
  graph *g = graph_create();
  // 3x3 матрица: 1->2->3
  int matrix[3][3] = {{0, 1, 0}, {0, 0, 1}, {0, 0, 0}};
  g->size = 3;
  g->matrix = malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) {
    g->matrix[i] = malloc(3 * sizeof(int));
    memcpy(g->matrix[i], matrix[i], 3 * sizeof(int));
  }

  int *result = depth_first_search(g, 1);
  ck_assert_int_eq(result[0], 1);
  ck_assert_int_eq(result[1], 2);
  ck_assert_int_eq(result[2], 3);
  free(result);
  graph_free(g);
}
END_TEST

START_TEST(test_bfs) {
  graph *g = graph_create();
  // 4x4 матрица: 1->2->3->4
  //              1->4
  int matrix[4][4] = {{0, 1, 0, 1}, {0, 0, 1, 0}, {0, 0, 0, 1}, {0, 0, 0, 0}};
  g->size = 4;
  g->matrix = malloc(4 * sizeof(int *));
  for (int i = 0; i < 4; i++) {
    g->matrix[i] = malloc(4 * sizeof(int));
    memcpy(g->matrix[i], matrix[i], 4 * sizeof(int));
  }

  int *result = breadth_first_search(g, 1);
  ck_assert_int_eq(result[0], 1);
  ck_assert(result[1] == 2 || result[1] == 4);
  free(result);
  graph_free(g);
}
END_TEST

START_TEST(test_dijkstra) {
  graph *g = graph_create();
  // Граф с путями 1-2 (5), 1-3 (10), 2-3 (2)
  int matrix[3][3] = {{0, 5, 10}, {5, 0, 2}, {10, 2, 0}};
  g->size = 3;
  g->matrix = malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) {
    g->matrix[i] = malloc(3 * sizeof(int));
    memcpy(g->matrix[i], matrix[i], 3 * sizeof(int));
  }

  ck_assert_double_eq(get_shortest_path_between_vertices(g, 1, 3), 7);
  graph_free(g);
}
END_TEST

START_TEST(test_floyd_warshall) {
  graph *g = graph_create();
  int matrix[3][3] = {{0, 1, 0}, {0, 0, 1}, {0, 0, 0}};
  g->size = 3;
  g->matrix = malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) {
    g->matrix[i] = malloc(3 * sizeof(int));
    memcpy(g->matrix[i], matrix[i], 3 * sizeof(int));
  }

  double **dist = get_shortest_paths_between_all_vertices(g);
  ck_assert_double_eq(dist[1][3], 2);
  free_shortest_paths_matrix(dist, g->size);
  graph_free(g);
}
END_TEST

START_TEST(test_prim) {
  graph *g = graph_create();
  int matrix[3][3] = {{0, 2, 3}, {2, 0, 1}, {3, 1, 0}};
  g->size = 3;
  g->matrix = malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) {
    g->matrix[i] = malloc(3 * sizeof(int));
    memcpy(g->matrix[i], matrix[i], 3 * sizeof(int));
  }

  graph *mst = get_least_spanning_tree(g);
  ck_assert_int_eq(mst->matrix[0][1], 2);
  ck_assert_int_eq(mst->matrix[1][2], 1);
  graph_free(mst);
  graph_free(g);
}
END_TEST

START_TEST(test_prim_ne) {
  graph *g = graph_create();
  int matrix[5][5] = {{1, 1, 0, 1, 1},
                      {1, 1, 0, 1, 1},
                      {0, 0, 1, 0, 0},
                      {1, 1, 0, 1, 1},
                      {1, 1, 0, 1, 1}};

  g->size = 5;
  g->matrix = malloc(g->size * sizeof(int *));
  for (int i = 0; i < g->size; i++) {
    g->matrix[i] = malloc(g->size * sizeof(int));
    memcpy(g->matrix[i], matrix[i], g->size * sizeof(int));
  }

  ck_assert_ptr_null(get_least_spanning_tree(g));
  graph_free(g);
}
END_TEST

START_TEST(test_tsp_ant_colony_algoriht) {
  graph *g = graph_create();
  int matrix[4][4] = {
      {0, 10, 15, 20}, {10, 0, 35, 25}, {15, 35, 0, 30}, {20, 25, 30, 0}};
  g->size = 4;
  g->matrix = malloc(4 * sizeof(int *));
  for (int i = 0; i < 4; i++) {
    g->matrix[i] = malloc(4 * sizeof(int));
    memcpy(g->matrix[i], matrix[i], 4 * sizeof(int));
  }

  tsm_result *res = solve_traveling_salesman_problem(g);
  ck_assert(res->distance == 80);
  free_tsm_result(res);
  graph_free(g);
}
END_TEST

START_TEST(test_tsp_ant_colony_algoriht_ne) {
  graph *g = graph_create();
  int matrix[5][5] = {{1, 1, 0, 1, 1},
                      {1, 1, 0, 1, 1},
                      {0, 0, 1, 0, 0},
                      {1, 1, 0, 1, 1},
                      {1, 1, 0, 1, 1}};

  g->size = 5;
  g->matrix = malloc(g->size * sizeof(int *));
  for (int i = 0; i < g->size; i++) {
    g->matrix[i] = malloc(g->size * sizeof(int));
    memcpy(g->matrix[i], matrix[i], g->size * sizeof(int));
  }

  ck_assert_ptr_null(solve_traveling_salesman_problem(g));

  graph_free(g);
}
END_TEST

START_TEST(test_tsp_bf_algoriht) {
  graph *g = graph_create();
  int matrix[4][4] = {
      {0, 10, 15, 20}, {10, 0, 35, 25}, {15, 35, 0, 30}, {20, 25, 30, 0}};
  g->size = 4;
  g->matrix = malloc(4 * sizeof(int *));
  for (int i = 0; i < 4; i++) {
    g->matrix[i] = malloc(4 * sizeof(int));
    memcpy(g->matrix[i], matrix[i], 4 * sizeof(int));
  }

  tsm_result *res = bf_tsp(g);
  ck_assert(res->distance == 80);
  free_tsm_result(res);
  graph_free(g);
}
END_TEST

START_TEST(test_tsp_bf_algoriht_ne) {
  graph *g = graph_create();
  int matrix[5][5] = {{1, 1, 0, 1, 1},
                      {1, 1, 0, 1, 1},
                      {0, 0, 1, 0, 0},
                      {1, 1, 0, 1, 1},
                      {1, 1, 0, 1, 1}};

  g->size = 5;
  g->matrix = malloc(g->size * sizeof(int *));
  for (int i = 0; i < g->size; i++) {
    g->matrix[i] = malloc(g->size * sizeof(int));
    memcpy(g->matrix[i], matrix[i], g->size * sizeof(int));
  }

  ck_assert_ptr_null(bf_tsp(g));

  graph_free(g);
}
END_TEST

START_TEST(test_tsp_ant_greedy_algoriht) {
  graph *g = graph_create();
  int matrix[4][4] = {
      {0, 10, 15, 20}, {10, 0, 35, 25}, {15, 35, 0, 30}, {20, 25, 30, 0}};
  g->size = 4;
  g->matrix = malloc(4 * sizeof(int *));
  for (int i = 0; i < 4; i++) {
    g->matrix[i] = malloc(4 * sizeof(int));
    memcpy(g->matrix[i], matrix[i], 4 * sizeof(int));
  }

  tsm_result *res = greedy_tsp(g);
  ck_assert(res->distance == 80);
  free_tsm_result(res);
  graph_free(g);
}
END_TEST

START_TEST(test_tsp_ant_greedy_algoriht_2) {
  const char *filename = "./tests/graph_tests_files/graph_7.txt";
  graph *g = graph_create();
  ck_assert_int_eq(load_graph_from_file(g, filename), 0);
  ck_assert_ptr_null(greedy_tsp(g));
  graph_free(g);
}
END_TEST

START_TEST(test_tsp_ant_greedy_algoriht_ne) {
  graph *g = graph_create();
  int matrix[5][5] = {{1, 1, 0, 1, 1},
                      {1, 1, 0, 1, 1},
                      {0, 0, 1, 0, 0},
                      {1, 1, 0, 1, 1},
                      {1, 1, 0, 1, 1}};

  g->size = 5;
  g->matrix = malloc(g->size * sizeof(int *));
  for (int i = 0; i < g->size; i++) {
    g->matrix[i] = malloc(g->size * sizeof(int));
    memcpy(g->matrix[i], matrix[i], g->size * sizeof(int));
  }

  ck_assert_ptr_null(greedy_tsp(g));
  graph_free(g);
}
END_TEST

START_TEST(test_tsp_ant_nn_algoriht) {
  graph *g = graph_create();
  int matrix[4][4] = {
      {0, 10, 15, 20}, {10, 0, 35, 25}, {15, 35, 0, 30}, {20, 25, 30, 0}};
  g->size = 4;
  g->matrix = malloc(4 * sizeof(int *));
  for (int i = 0; i < 4; i++) {
    g->matrix[i] = malloc(4 * sizeof(int));
    memcpy(g->matrix[i], matrix[i], 4 * sizeof(int));
  }

  tsm_result *res = nearest_neighbor_tsp(g);
  ck_assert(res->distance == 80);
  free_tsm_result(res);
  graph_free(g);
}
END_TEST

START_TEST(test_tsp_ant_nn_algoriht_ne) {
  graph *g = graph_create();
  int matrix[5][5] = {{1, 1, 0, 1, 1},
                      {1, 1, 0, 1, 1},
                      {0, 0, 1, 0, 0},
                      {1, 1, 0, 1, 1},
                      {1, 1, 0, 1, 1}};

  g->size = 5;
  g->matrix = malloc(g->size * sizeof(int *));
  for (int i = 0; i < g->size; i++) {
    g->matrix[i] = malloc(g->size * sizeof(int));
    memcpy(g->matrix[i], matrix[i], g->size * sizeof(int));
  }

  ck_assert_ptr_null(nearest_neighbor_tsp(g));

  graph_free(g);
}
END_TEST

// для полного покрытия) контейнеров

START_TEST(test_containers_queue) {
  queue *q = queue_create();

  queue_push(q, 1);
  queue_push(q, 2);
  queue_push(q, 3);

  ck_assert_int_eq(queue_front(q), 1);
  ck_assert_int_eq(queue_back(q), 3);
  ck_assert_ptr_ne(q->front, q->rear);

  queue_free(q);
}
END_TEST

Suite *test_algorithms(void) {
  Suite *s = suite_create(
      "\n\033[37;1m==========| S21_GRAPH_ALGORITHMS |=========\033[0m");
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
  tcase_add_test(tc, test_tsp_bf_algoriht);
  tcase_add_test(tc, test_tsp_bf_algoriht_ne);

  tcase_add_test(tc, test_tsp_ant_greedy_algoriht);
  tcase_add_test(tc, test_tsp_ant_greedy_algoriht_2);
  tcase_add_test(tc, test_tsp_ant_greedy_algoriht_ne);
  tcase_add_test(tc, test_tsp_ant_nn_algoriht);
  tcase_add_test(tc, test_tsp_ant_nn_algoriht_ne);
  tcase_add_test(tc, test_containers_queue);

  return s;
}
