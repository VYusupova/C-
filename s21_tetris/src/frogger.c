#include "frogger.h"

#include <stdio.h>
#include <time.h>
#include <tetris.h>

int main(void) {
  WIN_INIT(250);
  setlocale(LC_ALL, "");
  initColors();  // инициализация цветов  
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
  // задаем начальные значения левел и количество очков
  gameBakend.fnow = &fnow;
  gameBakend.fnext = &fnext;
  initGame(&gameBakend);



  while (break_flag) {  
    if (userAct == Terminate) 
      break_flag = FALSE;

    //printGameField(&gameBakend); //?
    sigact(&userAct, &gameBakend, &fnow);  
       //if (state != Terminate) signal = GET_USER_INPUT; //state == MOVING || state == Start
    userAct = get_signal(GET_USER_INPUT);
    //movedown(&userAct, &fnow, &gameBakend);
    //napms(500);

    timeout(700); 
    // delay_output(200);
  }
  writeScore(&gameBakend);
}
