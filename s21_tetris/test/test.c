#include "test.h"

#include <check.h>

START_TEST(test_create_matrix) {
  figura f;
  f.figur = create(FSIZE, FSIZE);
  for (int x = 0; x < FSIZE; x++)
    for (int y = 0; y < FSIZE; y++) ck_assert_int_eq(f.figur[x][y], 0);
  tetFree(f.figur, FSIZE, FSIZE);
}
END_TEST

START_TEST(test_init_figura_I) {
  figura f;
  f.figur = create(FSIZE, FSIZE);
  initFigure(&f, 2);
  ck_assert_int_eq(f.n, 4);
  ck_assert_int_eq(f.m, 1);
  ck_assert_int_eq(f.figur[0][0], 1);
  ck_assert_int_eq(f.figur[1][0], 1);
  ck_assert_int_eq(f.figur[2][0], 1);
  ck_assert_int_eq(f.figur[3][0], 1);
  tetFree(f.figur, FSIZE, FSIZE);
}
END_TEST

START_TEST(test_init_figura_Q) {
  figura f;
  f.figur = create(FSIZE, FSIZE);
  initFigure(&f, 1);
  ck_assert_int_eq(f.n, 2);
  ck_assert_int_eq(f.m, 2);
  ck_assert_int_eq(f.figur[0][0], 1);
  ck_assert_int_eq(f.figur[0][1], 1);
  ck_assert_int_eq(f.figur[1][0], 1);
  ck_assert_int_eq(f.figur[1][1], 1);
  tetFree(f.figur, FSIZE, FSIZE);
}
END_TEST

START_TEST(test_init_figura_S) {
  figura f;
  f.figur = create(FSIZE, FSIZE);
  initFigure(&f, 3);
  ck_assert_int_eq(f.n, 2);
  ck_assert_int_eq(f.m, 3);
  ck_assert_int_eq(f.figur[0][0], 0);
  ck_assert_int_eq(f.figur[0][1], 1);
  ck_assert_int_eq(f.figur[0][2], 1);
  ck_assert_int_eq(f.figur[1][0], 1);
  ck_assert_int_eq(f.figur[1][1], 1);
  ck_assert_int_eq(f.figur[1][2], 0);
  tetFree(f.figur, FSIZE, FSIZE);
}
END_TEST

START_TEST(test_init_figura_Z) {
  figura f;
  f.figur = create(FSIZE, FSIZE);
  initFigure(&f, 4);
  ck_assert_int_eq(f.n, 2);
  ck_assert_int_eq(f.m, 3);
  ck_assert_int_eq(f.figur[0][0], 1);
  ck_assert_int_eq(f.figur[0][1], 1);
  ck_assert_int_eq(f.figur[0][2], 0);
  ck_assert_int_eq(f.figur[1][0], 0);
  ck_assert_int_eq(f.figur[1][1], 1);
  ck_assert_int_eq(f.figur[1][2], 1);
  tetFree(f.figur, FSIZE, FSIZE);
}
END_TEST
START_TEST(test_init_figura_L) {
  figura f;
  f.figur = create(FSIZE, FSIZE);
  initFigure(&f, 5);
  ck_assert_int_eq(f.n, 3);
  ck_assert_int_eq(f.m, 2);
  ck_assert_int_eq(f.figur[0][0], 1);
  ck_assert_int_eq(f.figur[1][0], 1);
  ck_assert_int_eq(f.figur[2][0], 1);
  ck_assert_int_eq(f.figur[0][1], 0);
  ck_assert_int_eq(f.figur[1][1], 0);
  ck_assert_int_eq(f.figur[2][1], 1);
  tetFree(f.figur, FSIZE, FSIZE);
}
END_TEST

START_TEST(test_init_figura_J) {
  figura f;
  f.figur = create(FSIZE, FSIZE);
  initFigure(&f, 6);
  ck_assert_int_eq(f.n, 3);
  ck_assert_int_eq(f.m, 2);
  ck_assert_int_eq(f.figur[0][1], 1);
  ck_assert_int_eq(f.figur[1][1], 1);
  ck_assert_int_eq(f.figur[2][1], 1);
  ck_assert_int_eq(f.figur[0][0], 0);
  ck_assert_int_eq(f.figur[1][0], 0);
  ck_assert_int_eq(f.figur[2][0], 1);
  tetFree(f.figur, FSIZE, FSIZE);
}
END_TEST

START_TEST(test_init_figura_T) {
  figura f;
  f.figur = create(FSIZE, FSIZE);
  initFigure(&f, 7);
  ck_assert_int_eq(f.n, 2);
  ck_assert_int_eq(f.m, 3);
  ck_assert_int_eq(f.figur[0][0], 0);
  ck_assert_int_eq(f.figur[1][0], 1);
  ck_assert_int_eq(f.figur[0][1], 1);
  ck_assert_int_eq(f.figur[1][1], 1);
  ck_assert_int_eq(f.figur[0][2], 0);
  ck_assert_int_eq(f.figur[1][2], 1);
  tetFree(f.figur, FSIZE, FSIZE);
}
END_TEST

START_TEST(test_initGame) {
  GameInfo_t game;
  figura fnow, fnext;
  fnow.figur = create(FSIZE, FSIZE);
  fnext.figur = create(FSIZE, FSIZE);
  game.fnow = &fnow;
  game.fnext = &fnext;
  initGame(&game);
  ck_assert_int_eq(game.level, 0);
  ck_assert_int_eq(game.score, 0);
  // ck_assert_int_eq(game.high_score , 0);
  ck_assert_int_eq(game.fnow->x, START_X);
  ck_assert_int_eq(game.fnow->y, START_Y);
  ck_assert_int_eq(game.fnext->x, R_NEXT_X);
  ck_assert_int_eq(game.fnext->y, R_NEXT_Y);
  ck_assert_int_eq(game.speed, SPEED);
  for (int x = 0; x < FIELD_N; x++)
    for (int y = 0; y < FIELD_M; y++) ck_assert_int_eq(game.field[x][y], 0);
  tetFree(game.field, FIELD_N, FIELD_M);
  tetFree(fnow.figur, FSIZE, FSIZE);
  tetFree(fnext.figur, FSIZE, FSIZE);
}
END_TEST

START_TEST(test_score0) {
  GameInfo_t game;
  figura fnow, fnext;
  fnow.figur = create(FSIZE, FSIZE);
  fnext.figur = create(FSIZE, FSIZE);
  game.fnow = &fnow;
  game.fnext = &fnext;
  initGame(&game);

  for (int j = 0; j < FIELD_M; j++) game.field[5][j] = 1;
  for (int j = 0; j < (FIELD_M - 1); j++) game.field[7][j] = 1;

  score(&game);

  ck_assert_int_eq(game.score, 100);

  tetFree(game.field, FIELD_N, FIELD_M);
  tetFree(fnow.figur, FSIZE, FSIZE);
  tetFree(fnext.figur, FSIZE, FSIZE);
}
END_TEST

START_TEST(test_score1) {
  GameInfo_t game;
  figura fnow, fnext;
  fnow.figur = create(FSIZE, FSIZE);
  fnext.figur = create(FSIZE, FSIZE);
  game.fnow = &fnow;
  game.fnext = &fnext;
  initGame(&game);

  for (int j = 0; j < FIELD_M; j++) game.field[5][j] = 1;
  for (int j = 0; j < (FIELD_M); j++) game.field[7][j] = 1;

  score(&game);

  ck_assert_int_eq(game.score, 300);

  tetFree(game.field, FIELD_N, FIELD_M);
  tetFree(fnow.figur, FSIZE, FSIZE);
  tetFree(fnext.figur, FSIZE, FSIZE);
}
END_TEST

START_TEST(test_score2) {
  GameInfo_t game;
  figura fnow, fnext;
  fnow.figur = create(FSIZE, FSIZE);
  fnext.figur = create(FSIZE, FSIZE);
  game.fnow = &fnow;
  game.fnext = &fnext;
  initGame(&game);

  for (int j = 0; j < FIELD_M; j++) {
    game.field[5][j] = 1;
    game.field[7][j] = 1;
    game.field[8][j] = 1;
  }

  score(&game);

  ck_assert_int_eq(game.score, 700);

  tetFree(game.field, FIELD_N, FIELD_M);
  tetFree(fnow.figur, FSIZE, FSIZE);
  tetFree(fnext.figur, FSIZE, FSIZE);
}
END_TEST

START_TEST(test_score3) {
  GameInfo_t game;
  figura fnow, fnext;
  fnow.figur = create(FSIZE, FSIZE);
  fnext.figur = create(FSIZE, FSIZE);
  game.fnow = &fnow;
  game.fnext = &fnext;
  initGame(&game);

  for (int j = 0; j < FIELD_M; j++) {
    game.field[5][j] = 1;
    game.field[7][j] = 1;
    game.field[8][j] = 1;
    game.field[1][j] = 1;
  }

  score(&game);

  ck_assert_int_eq(game.score, 1500);

  tetFree(game.field, FIELD_N, FIELD_M);
  tetFree(fnow.figur, FSIZE, FSIZE);
  tetFree(fnext.figur, FSIZE, FSIZE);
}
END_TEST

START_TEST(test_score4) {
  GameInfo_t game;
  figura fnow, fnext;
  fnow.figur = create(FSIZE, FSIZE);
  fnext.figur = create(FSIZE, FSIZE);
  game.fnow = &fnow;
  game.fnext = &fnext;
  initGame(&game);

  game.score = 310;
  writeScore(&game);
  ck_assert_int_eq(game.score, readScore());

  tetFree(game.field, FIELD_N, FIELD_M);
  tetFree(fnow.figur, FSIZE, FSIZE);
  tetFree(fnext.figur, FSIZE, FSIZE);
}
END_TEST

START_TEST(test_collisionDown1) {  // чистое поле фигура только появилась
  GameInfo_t game;
  figura fnow, fnext;
  fnow.figur = create(FSIZE, FSIZE);
  fnext.figur = create(FSIZE, FSIZE);
  game.fnow = &fnow;
  game.fnext = &fnext;
  initFigure(&fnow, 6);  // FIGUR_J
  initGame(&game);

  ck_assert_int_eq(collisionDown(game.fnow, &game), 0);

  tetFree(game.field, FIELD_N, FIELD_M);
  tetFree(fnow.figur, FSIZE, FSIZE);
  tetFree(fnext.figur, FSIZE, FSIZE);
}
END_TEST

START_TEST(test_collisionDown2) {  // чистое поле фигура внизу поля
  GameInfo_t game;
  figura fnow, fnext;
  fnow.figur = create(FSIZE, FSIZE);
  fnext.figur = create(FSIZE, FSIZE);
  game.fnow = &fnow;
  game.fnext = &fnext;
  initFigure(&fnow, 6);  // FIGUR_J
  initGame(&game);
  game.fnow->y = 17;
  ck_assert_int_eq(collisionDown(game.fnow, &game), 1);

  tetFree(game.field, FIELD_N, FIELD_M);
  tetFree(fnow.figur, FSIZE, FSIZE);
  tetFree(fnext.figur, FSIZE, FSIZE);
}
END_TEST
// 19 линии поля уже заполнен фигура около них
START_TEST(test_collisionDown3) {
  GameInfo_t game;
  figura fnow, fnext;
  fnow.figur = create(FSIZE, FSIZE);
  fnext.figur = create(FSIZE, FSIZE);
  game.fnow = &fnow;
  game.fnext = &fnext;
  initFigure(&fnow, 6);  // FIGUR_J
  initGame(&game);
  for (int j = 0; j < FIELD_M; j++) game.field[19][j] = 1;
  game.fnow->y = 16;
  ck_assert_int_eq(collisionDown(game.fnow, &game), 1);

  tetFree(game.field, FIELD_N, FIELD_M);
  tetFree(fnow.figur, FSIZE, FSIZE);
  tetFree(fnext.figur, FSIZE, FSIZE);
}
END_TEST
// фигура только появилась коллизии нет
START_TEST(test_collisionLeft1) {
  GameInfo_t game;
  figura fnow, fnext;
  fnow.figur = create(FSIZE, FSIZE);
  fnext.figur = create(FSIZE, FSIZE);
  game.fnow = &fnow;
  game.fnext = &fnext;
  initFigure(&fnow, 5);  // FIGUR_L
  initGame(&game);
  ck_assert_int_eq(collisionLeft(game.fnow, &game), 0);

  tetFree(game.field, FIELD_N, FIELD_M);
  tetFree(fnow.figur, FSIZE, FSIZE);
  tetFree(fnext.figur, FSIZE, FSIZE);
}
END_TEST

// фигура левую границу
START_TEST(test_collisionLeft2) {
  GameInfo_t game;
  figura fnow, fnext;
  fnow.figur = create(FSIZE, FSIZE);
  fnext.figur = create(FSIZE, FSIZE);
  game.fnow = &fnow;
  game.fnext = &fnext;
  initFigure(&fnow, 5);  // FIGUR_L
  initGame(&game);
  game.fnow->x = 0;
  ck_assert_int_eq(collisionLeft(game.fnow, &game), 1);

  tetFree(game.field, FIELD_N, FIELD_M);
  tetFree(fnow.figur, FSIZE, FSIZE);
  tetFree(fnext.figur, FSIZE, FSIZE);
}
END_TEST

// фигура левую границу поле слево заполенно
START_TEST(test_collisionLeft3) {
  GameInfo_t game;
  figura fnow, fnext;
  fnow.figur = create(FSIZE, FSIZE);
  fnext.figur = create(FSIZE, FSIZE);
  game.fnow = &fnow;
  game.fnext = &fnext;
  initFigure(&fnow, 5);  // FIGUR_L
  initGame(&game);
  game.fnow->x = 3;
  game.fnow->y = 5;
  game.field[5][2] = 1;

  ck_assert_int_eq(collisionLeft(game.fnow, &game), 1);

  tetFree(game.field, FIELD_N, FIELD_M);
  tetFree(fnow.figur, FSIZE, FSIZE);
  tetFree(fnext.figur, FSIZE, FSIZE);
}
END_TEST

// фигура только появилась коллизии нет
START_TEST(test_collisionRight1) {
  GameInfo_t game;
  figura fnow, fnext;
  fnow.figur = create(FSIZE, FSIZE);
  fnext.figur = create(FSIZE, FSIZE);
  game.fnow = &fnow;
  game.fnext = &fnext;
  initFigure(&fnow, 5);  // FIGUR_L
  initGame(&game);
  ck_assert_int_eq(collisionRight(game.fnow, &game), 0);

  tetFree(game.field, FIELD_N, FIELD_M);
  tetFree(fnow.figur, FSIZE, FSIZE);
  tetFree(fnext.figur, FSIZE, FSIZE);
}
END_TEST

// фигура левую границу
START_TEST(test_collisionRight2) {
  GameInfo_t game;
  figura fnow, fnext;
  fnow.figur = create(FSIZE, FSIZE);
  fnext.figur = create(FSIZE, FSIZE);
  game.fnow = &fnow;
  game.fnext = &fnext;
  initFigure(&fnow, 5);  // FIGUR_L
  initGame(&game);
  game.fnow->x = 9;
  ck_assert_int_eq(collisionRight(game.fnow, &game), 1);

  tetFree(game.field, FIELD_N, FIELD_M);
  tetFree(fnow.figur, FSIZE, FSIZE);
  tetFree(fnext.figur, FSIZE, FSIZE);
}
END_TEST

// фигура левую границу поле слево заполенно
START_TEST(test_collisionRight3) {
  GameInfo_t game;
  figura fnow, fnext;
  fnow.figur = create(FSIZE, FSIZE);
  fnext.figur = create(FSIZE, FSIZE);
  game.fnow = &fnow;
  game.fnext = &fnext;
  initFigure(&fnow, 5);  // FIGUR_L
  initGame(&game);
  game.fnow->x = 3;
  game.fnow->y = 5;
  game.field[5][4] = 1;

  ck_assert_int_eq(collisionRight(game.fnow, &game), 1);

  tetFree(game.field, FIELD_N, FIELD_M);
  tetFree(fnow.figur, FSIZE, FSIZE);
  tetFree(fnext.figur, FSIZE, FSIZE);
}
END_TEST

START_TEST(test_rotate) {
  GameInfo_t game;
  figura fnow, fnext;
  fnow.figur = create(FSIZE, FSIZE);
  fnext.figur = create(FSIZE, FSIZE);
  game.fnow = &fnow;
  game.fnext = &fnext;
  initFigure(&fnow, 5);  // FIGUR_L
  initGame(&game);

  int n = fnow.n;
  int m = fnow.m;

  rotateFigure(game.fnow, &game);
  ck_assert_int_eq(fnow.n, m);
  ck_assert_int_eq(fnow.m, n);

  tetFree(game.field, FIELD_N, FIELD_M);
  tetFree(fnow.figur, FSIZE, FSIZE);
  tetFree(fnext.figur, FSIZE, FSIZE);
}

Suite *test() {
  Suite *s = suite_create("\033[32m---TESTING TETRIS---\033[0m");
  TCase *test_case = tcase_create("test_equal_case");
  tcase_add_test(test_case, test_create_matrix);
  tcase_add_test(test_case, test_init_figura_Q);
  tcase_add_test(test_case, test_init_figura_I);
  tcase_add_test(test_case, test_init_figura_S);
  tcase_add_test(test_case, test_init_figura_Z);
  tcase_add_test(test_case, test_init_figura_L);
  tcase_add_test(test_case, test_init_figura_J);
  tcase_add_test(test_case, test_init_figura_T);
  tcase_add_test(test_case, test_initGame);
  tcase_add_test(test_case, test_score0);
  tcase_add_test(test_case, test_score1);
  tcase_add_test(test_case, test_score2);
  tcase_add_test(test_case, test_score3);
  tcase_add_test(test_case, test_score4);
  tcase_add_test(test_case, test_collisionDown1);
  tcase_add_test(test_case, test_collisionDown2);
  tcase_add_test(test_case, test_collisionDown3);
  tcase_add_test(test_case, test_collisionLeft1);
  tcase_add_test(test_case, test_collisionLeft2);
  tcase_add_test(test_case, test_collisionLeft3);
  tcase_add_test(test_case, test_collisionRight1);
  tcase_add_test(test_case, test_collisionRight2);
  tcase_add_test(test_case, test_collisionRight3);
  tcase_add_test(test_case, test_rotate);

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

int main() { s21_test(test()); }
