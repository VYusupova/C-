
#include <stdio.h>
#include <tetris.h>
#include <time.h>

#include "fsm.h"

int main(void) {
  WIN_INIT(250);
  setlocale(LC_ALL, "");
  initColors();     // инициализация цветов
  print_overlay();  // отрисовка поля игры
  srand(time(NULL)); // for true random
  game_loop();
  endwin();

  return SUCCESS;
}

void game_loop() {
  GameInfo_t game;  

  figura fnow;
  figura fnext;
  
  fnow.figur = create(FSIZE, FSIZE);
  fnext.figur = create(FSIZE, FSIZE);
  

  bool break_flag = TRUE;

  UserAction_t userAct = Pause;
  tetris_state state = START;
  // задаем начальные значения левел и количество очков
  game.fnow = &fnow;
  game.fnext = &fnext;
  initGame(&game);
  game.speed = 700;

  while (break_flag) {
    if (state == GAMEOVER) {
      break_flag = FALSE;
      // gameOver();
    }
  
    sigact(&userAct, &state, &game, &fnow);

    if (state == MOVING || state == START) userAct = get_signal(GET_USER_INPUT);
    // else userAct = Terminate;
    timeout(game.speed); //  timeout(700);
    // napms(500);
    // delay_output(200);
  }
  writeScore(&game);
  
  tetFree(fnow.figur, FSIZE, FSIZE);
  tetFree(fnext.figur, FSIZE, FSIZE);
  tetFree(game.field, FIELD_N, FIELD_M);
}
