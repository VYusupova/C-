#include "frogger.h"

#include <stdio.h>
#include <time.h>
#include <tetris.h>

int main(void) {
  WIN_INIT(250);
  setlocale(LC_ALL, "");
  print_overlay();  // отрисовка поля игры
  game_loop();
  endwin();

  return SUCCESS;
}

void game_loop() {
  //board_t map;
  game_stats_t gameBakend;  // здесь лежит массив с описанием игрового поля
  player_pos frog;
  figura fnow;
  figura fnext;

  bool break_flag = TRUE;

  UserAction_t state = Pause;
  // задаем начальные значения левел и количество очков
  gameBakend.fnow = &fnow;
  gameBakend.fnext = &fnext;
  initGame(&gameBakend);

  initColors();  // инициализация цветов

  while (break_flag) {  // GAMEOVER  - не должен заканчивать цикл???
    if (state == Terminate) //state == GAMEOVER || state == EXIT_STATE || state == FILE_ERROR_STATE
      break_flag = FALSE;

    printGameField(&gameBakend);
    sigact(&state, &gameBakend, &frog, &fnow); // &map, 
    state = get_signal(GET_USER_INPUT);
    movedown(&state, &fnow, &gameBakend);
    napms(600);

    //timeout(1200); // THIS need go to sigact function
    //movedown(&state, &fnow, &gameBakend); // THIS need go to sigact function
	    // delay_output(200);
	    
    //if (state != Terminate) signal = GET_USER_INPUT; //state == MOVING || state == Start
  }
}
