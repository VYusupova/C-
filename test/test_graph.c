#include "test.h"

START_TEST(test_graph_init) {
  s21_graph g;
  ck_assert_ptr_nonnull(&g);

  g = graph_init();
  ck_assert_int_eq(g.size, 0);
  ck_assert_ptr_null(g.matrix);
  g.del_graph(&g);
}
END_TEST

START_TEST(test_load_valid_file_1) {
  s21_graph g = graph_init();
  char *filename = "test_valid.txt";

  FILE *f = fopen(filename, "w");
  fprintf(f, "3\n0 1 0\n1 0 1\n0 1 0");
  fclose(f);

  g.load_graph_from_file(filename, &g);
  ck_assert_int_eq(g.size, 3);
  ck_assert_int_eq(g.matrix[0][0], 0);
  ck_assert_int_eq(g.matrix[0][1], 1);
  ck_assert_int_eq(g.matrix[0][2], 0);
  ck_assert_int_eq(g.matrix[1][0], 1);
  ck_assert_int_eq(g.matrix[1][1], 0);
  ck_assert_int_eq(g.matrix[1][2], 1);
  ck_assert_int_eq(g.matrix[2][0], 0);
  ck_assert_int_eq(g.matrix[2][1], 1);
  ck_assert_int_eq(g.matrix[2][2], 0);

  g.del_graph(&g);
  remove(filename);
}
END_TEST

START_TEST(test_load_valid_file_2) {
  s21_graph g = graph_init();
  char *filename = "test/file_test/t_1_load.txt";

  g.load_graph_from_file(filename, &g);
  ck_assert_int_eq(g.size, 11);
  ck_assert_int_eq(g.matrix[0][0], 0);
  ck_assert_int_eq(g.matrix[0][1], 29);
  ck_assert_int_eq(g.matrix[0][2], 20);
  ck_assert_int_eq(g.matrix[1][0], 29);
  ck_assert_int_eq(g.matrix[1][1], 0);
  ck_assert_int_eq(g.matrix[1][2], 15);
  ck_assert_int_eq(g.matrix[2][0], 20);
  ck_assert_int_eq(g.matrix[2][1], 15);
  ck_assert_int_eq(g.matrix[2][2], 0);

  g.del_graph(&g);
}
END_TEST

START_TEST(test_load_nonexistent_file) {
  s21_graph g = graph_init();
  g.load_graph_from_file("nonexistent.txt", &g);
  ck_assert_int_eq(g.size, 0);
  ck_assert_ptr_null(g.matrix);

  g.del_graph(&g);
}
END_TEST

START_TEST(test_invalid_size_format) {
  char *filename = "invalid_size.txt";
  FILE *tmp = fopen(filename, "w");
  fprintf(tmp, "not_a_number\n");
  fclose(tmp);

  s21_graph g = graph_init();
  g.load_graph_from_file(filename, &g);

  ck_assert_int_eq(g.size, 0);
  ck_assert_ptr_null(g.matrix);

  g.del_graph(&g);
  remove(filename);
}
END_TEST

START_TEST(test_incomplete_size_read) {
  char *filename = "empty_size.txt";
  FILE *tmp = fopen(filename, "w");
  fclose(tmp);

  s21_graph g = graph_init();
  g.load_graph_from_file(filename, &g);
  ck_assert_int_eq(g.size, 0);
  ck_assert_ptr_null(g.matrix);

  g.del_graph(&g);
  remove(filename);
}
END_TEST

START_TEST(test_negative_size) {
  char *filename = "negative_size.txt";
  FILE *tmp = fopen(filename, "w");
  fprintf(tmp, "-5\n");
  fclose(tmp);

  s21_graph g = graph_init();
  g.load_graph_from_file(filename, &g);

  ck_assert_int_eq(g.size, 0);
  ck_assert_ptr_null(g.matrix);

  g.del_graph(&g);
  remove(filename);
}
END_TEST

START_TEST(test_partially_corrupted) {
  char *filename = "partial.txt";

  FILE *tmp = fopen(filename, "w");
  fprintf(tmp, "3\n");
  fprintf(tmp, "1 aa 3\n");
  fclose(tmp);

  s21_graph g = graph_init();
  g.load_graph_from_file(filename, &g);

  ck_assert_int_eq(g.size, 0);
  ck_assert_ptr_null(g.matrix);

  g.del_graph(&g);
  remove(filename);
}
END_TEST

// START_TEST(test_export_directed_graph) {
//   s21_graph g = graph_init();
//   char *filename = "test_export_directed.dot";

//   FILE *f = fopen("temp.txt", "w");
//   fprintf(f, "2\n0 5\n0 0");
//   fclose(f);
//   g.load_graph_from_file("temp.txt", &g);

//   ck_assert_int_eq(g.export_graph_to_dot(filename, &g), 0);

//   f = fopen(filename, "r");
//   char line[256];
//   ck_assert(fgets(line, sizeof(line), f));
//   ck_assert_str_eq(line, "digraph G {\n");
//   ck_assert(fgets(line, sizeof(line), f));
//   ck_assert_str_eq(line, "    1 -> 2 [weight=5];\n");
//   ck_assert(fgets(line, sizeof(line), f));
//   ck_assert_str_eq(line, "}\n");
//   fclose(f);

//   g.del_graph(&g);
//   remove("temp.txt");
//   remove(filename);
// }
// END_TEST

// START_TEST(test_export_undirected_graph) {
//   s21_graph g = graph_init();
//   char *filename = "test_export_undirected.dot";
//   const char *expected_edges[] = {"1 -- 2 [weight=1];", "1 -- 3 [weight=1];",
//                                   "1 -- 5 [weight=1];", "2 -- 3 [weight=1];",
//                                   "2 -- 4 [weight=1];", "3 -- 4 [weight=1];",
//                                   "4 -- 5 [weight=1];", NULL};

//   // Создаем тестовый файл с матрицей смежности
//   FILE *f = fopen("temp.txt", "w");
//   fprintf(f,
//           "5\n"
//           "0 1 1 0 1\n"
//           "1 0 1 1 0\n"
//           "1 1 0 1 0\n"
//           "0 1 1 0 1\n"
//           "1 0 0 1 0");
//   fclose(f);

//   g.load_graph_from_file("temp.txt", &g);
//   ck_assert_int_eq(g.export_graph_to_dot(filename, &g), 0);

//   // Проверяем содержимое DOT-файла
//   f = fopen(filename, "r");
//   ck_assert_ptr_nonnull(f);

//   char line[256];
//   int edge_count = 0;
//   int header_found = 0;
//   int footer_found = 0;

//   while (fgets(line, sizeof(line), f)) {
//     line[strcspn(line, "\n")] = '\0';

//     if (strcmp(line, "graph G {") == 0) {
//       header_found = 1;
//       continue;
//     }

//     if (strcmp(line, "}") == 0) {
//       footer_found = 1;
//       continue;
//     }
//     int found = 0;
//     for (int i = 0; expected_edges[i]; i++) {
//       if (strstr(line, expected_edges[i]) != NULL) {
//         found = 1;
//         edge_count++;
//         break;
//       }
//     }
//     ck_assert(found == 1);
//   }

//   ck_assert_int_eq(header_found, 1);
//   ck_assert_int_eq(footer_found, 1);
//   ck_assert_int_eq(edge_count, 7);

//   fclose(f);
//   g.del_graph(&g);
//   remove("temp.txt");
//   remove(filename);
// }
// END_TEST

Suite *test_graph(void) {
  Suite *s =
      suite_create("\n\033[37;1m==========| S21_GRAPH |=========\033[0m");
  TCase *tc = tcase_create("test_graph");

  suite_add_tcase(s, tc);

  tcase_add_test(tc, test_graph_init);
  tcase_add_test(tc, test_load_valid_file_1);
  tcase_add_test(tc, test_load_valid_file_2);
  tcase_add_test(tc, test_load_nonexistent_file);
  tcase_add_test(tc, test_invalid_size_format);
  tcase_add_test(tc, test_incomplete_size_read);
  tcase_add_test(tc, test_negative_size);
  tcase_add_test(tc, test_partially_corrupted);
  // tcase_add_test(tc, test_export_directed_graph);
  // tcase_add_test(tc, test_export_undirected_graph);

  return s;
}
