//#include <check.h>

#include "s21_test.h"

START_TEST(test_create_matrix) {
 // figura f;
 // f.figur = create(FSIZE,FSIZE);  
 // for (int x = 0; x<FSIZE; x++)
 // for (int y = 0; y <FSIZE; y++)
 // ck_assert_int_eq(f.figur[x][y] , 0);
 // tetFree(f.figur, FSIZE,FSIZE);
}
END_TEST

START_TEST(test_init_tetris) {
  figura f;
  initFigure(&f);
  ck_assert_int_eq(f.x , START_X);
  ck_assert_int_eq(f.y , START_Y);
  // TO DO освободить ресурсы если будут выделяться
}
END_TEST

START_TEST(test_score0) {
  GameInfo_t game;
  initGame(&game);
     score(&game);
     ck_assert_int_eq(game.score , 0);
}
END_TEST

START_TEST(test_score1) {
  GameInfo_t game;
  initGame(&game);
        for (int j = 0; j < FIELD_M; j++)
            game.field[5][j] = 1;
        //for (int j = 0; j < (BOARD_M-1); j++)
          //  gb.field[5][j] = 1;
     score(&game);
     ck_assert_int_eq(game.score , 100);
}
END_TEST

START_TEST(test_score2) {
  GameInfo_t game;
  initGame(&game);
        for (int j = 0; j < FIELD_M; j++)
            game.field[5][j] = 1;
        for (int j = 0; j < (FIELD_M-1); j++)
            game.field[7][j] = 1;
     score(&game);
     ck_assert_int_eq(game.score , 100);
}
END_TEST

START_TEST(test_score3) {
GameInfo_t gb;
  initGame(&gb);
        for (int j = 0; j < BOARD_M; j++)
            gb.field[5][j] = 1;
        for (int j = 0; j < BOARD_M; j++)
            gb.field[7][j] = 1;
     score(&gb);
     ck_assert_int_eq(gb.score , 300);
}
END_TEST

START_TEST(test_score4) {
GameInfo_t gb;
  initGame(&gb);
        for (int j = 0; j < FIELD_M; j++){
            gb.field[5][j] = 1;
for (int j = 0; j < BOARD_M; j++)
            gb.field[7][j] = 1;
for (int j = 0; j < BOARD_M; j++)
            gb.field[8][j] = 1;
       }
     score(&gb);
     ck_assert_int_eq(gb.score , 700);
}
END_TEST


START_TEST(test_score5) {
GameInfo_t gb;
  initGame(&gb);
        for (int j = 0; j < BOARD_M; j++){
            gb.field[5][j] = 1;
            gb.field[6][j] = 1;
            gb.field[7][j] = 1;
            gb.field[8][j] = 1;
                                                }
     score(&gb);
     ck_assert_int_eq(gb.score , 1500);
}
END_TEST


Suite *test() {
  Suite *s = suite_create("\033[32m---TESTING TETRIS---\033[0m");
  TCase *test_case = tcase_create("test_equal_case");
    tcase_add_test(test_case, test_create_matrix);
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
