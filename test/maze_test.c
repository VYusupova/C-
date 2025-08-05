#include <check.h>
#include "../inc/maze.h"

START_TEST(test_way_DFS) {
    // Загрузим лабиринт из файла тестов
    maze_t* m = read_file_maze("test/test01.txt");

    ck_assert_ptr_nonnull(m);
    ck_assert_int_eq(m->rows,10);
    ck_assert_int_eq(m->columns,10);

    // задаем точки
    Point start = {0,0};
    Point end = {0,0};

    for (; start.x < m->rows; start.x++)
    for (; start.y < m->columns; start.y++)
    for (; end.y < m->columns; end.y++)
      {
        bool visited[MAX][MAX] = {false};  // Массив пути
        Point path[m->rows * m->columns];  // Максимальная длина пути = rows * cols
        int path_length = 0;
        ck_assert_int_eq (dfs(m, visited, start, end, path, &path_length), 1); 
      }
        

    remove_maze(m);
}
END_TEST

Suite *maze_suite(void) {
    Suite *s;
    TCase *tc_core;
    
    s = suite_create("MAZE");
    tc_core = tcase_create("dfs");
    
    tcase_add_test(tc_core, test_way_DFS);
    suite_add_tcase(s, tc_core);
    
    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;
    
    s = maze_suite();
    sr = srunner_create(s);
    
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
