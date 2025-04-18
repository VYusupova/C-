//#include <check.h>

#include "s21_test.h"

START_TEST(test_init_tetris) {
  figura f;
  initFigureNow(&f);
  ck_assert_int_eq(f.x , START_X);
  ck_assert_int_eq(f.y , START_Y);
  // TO DO освободить ресурсы если будут выделяться
}
END_TEST

START_TEST(test_score0) {
  game_stats_t gb;
  initGame(&gb);
     score(&gb);
     ck_assert_int_eq(gb.score , 0);
}
END_TEST

START_TEST(test_score1) {
  game_stats_t gb;
  initGame(&gb);
        for (int j = 0; j < BOARD_M; j++)
            gb.gameField[5][j] = 1;
        //for (int j = 0; j < (BOARD_M-1); j++)
          //  gb.gameField[5][j] = 1;
     score(&gb);
     ck_assert_int_eq(gb.score , 100);
}
END_TEST

START_TEST(test_score2) {
  game_stats_t gb;
  initGame(&gb);
        for (int j = 0; j < BOARD_M; j++)
            gb.gameField[5][j] = 1;
        for (int j = 0; j < (BOARD_M-1); j++)
            gb.gameField[7][j] = 1;
     score(&gb);
     ck_assert_int_eq(gb.score , 100);
}
END_TEST

START_TEST(test_score3) {
  game_stats_t gb;
  initGame(&gb);
        for (int j = 0; j < BOARD_M; j++)
            gb.gameField[5][j] = 1;
        for (int j = 0; j < BOARD_M; j++)
            gb.gameField[7][j] = 1;
     score(&gb);
     ck_assert_int_eq(gb.score , 300);
}
END_TEST

START_TEST(test_score4) {
  game_stats_t gb;
  initGame(&gb);
        for (int j = 0; j < FIELD_M; j++){
            gb.gameField[5][j] = 1;
for (int j = 0; j < BOARD_M; j++)
            gb.gameField[7][j] = 1;
for (int j = 0; j < BOARD_M; j++)
            gb.gameField[8][j] = 1;
       }
     score(&gb);
     ck_assert_int_eq(gb.score , 700);
}
END_TEST


START_TEST(test_score5) {
  game_stats_t gb;
  initGame(&gb);
        for (int j = 0; j < BOARD_M; j++){
            gb.gameField[5][j] = 1;
            gb.gameField[6][j] = 1;
            gb.gameField[7][j] = 1;
            gb.gameField[8][j] = 1;
                                                }
     score(&gb);
     ck_assert_int_eq(gb.score , 1500);
}
END_TEST


Suite *test() {
  Suite *s = suite_create("\033[32m---TESTING TETRIS---\033[0m");
  TCase *test_case = tcase_create("test_equal_case");

  tcase_add_test(test_case, test_init_tetris);
  tcase_add_test(test_case, test_score0);
  tcase_add_test(test_case, test_score1);
    tcase_add_test(test_case, test_score2);
    tcase_add_test(test_case, test_score3);
    tcase_add_test(test_case, test_score4);
    tcase_add_test(test_case, test_score5);

  suite_add_tcase(s, test_case);

  return s;
}


int s21_test(Suite *s) {
  int faild;
  SRunner *run = srunner_create(s);

  srunner_run_all(run, CK_NORMAL);

  faild = srunner_ntests_failed(run);

  srunner_free(run);

  return (faild == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

int main() {
  s21_test(test());
}
