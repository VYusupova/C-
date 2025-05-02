
#include <stdio.h>
#include <tetris.h>
#include <time.h>

#include "fsm.h"

int main(void) {
  WIN_INIT(250);
  setlocale(LC_ALL, "");
  initColors();     // инициализация цветов
  print_overlay();  // отрисовка поля игры
  game_loop();
  endwin();

  return SUCCESS;
}

void game_loop() {
  game_stats_t gameBakend;  // здесь лежит массив с описанием игрового поля

  figura fnow;
  figura fnext;

  bool break_flag = TRUE;

  UserAction_t userAct = Pause;
  tetris_state state = GAME;
  // задаем начальные значения левел и количество очков
  gameBakend.fnow = &fnow;
  gameBakend.fnext = &fnext;
  initGame(&gameBakend);

  while (break_flag) {
    if (state == GAMEOVER) {
      break_flag = FALSE;
      // gameOver();
    }

   printGameField(&gameBakend);
   
    sigact(&userAct, &state, &gameBakend, &fnow);

    if (state == MOVING || state == GAME) userAct = get_signal(GET_USER_INPUT);
    // else userAct = Terminate;
    timeout(700);
    // movedown(&userAct, &fnow, &gameBakend);
    // napms(500);

    // delay_output(200);
  }
  writeScore(&gameBakend);
}
