#include "fsm.h"

// This is a finite state machine realisation based on switch-case statement.
/*

Функция sigact() описывает логику переключения состояний.
    States are checked in order specified in function sigact().
    It enters a state-case which it corresponds to, where begins another
switch-case statement. Inner switch-case statement is looking for a signal given
by get_signal(). After finding it makes some action and switches state to the
next one.

    Pros:
        1) Less memory usage.
    Cons:
        1) A lot of codelines.
*/

signals get_signal(int user_input) {
  signals rc = NOSIG;

  switch (user_input){
case KEY_DOWN : rc = MOVE_DOWN; break;
case KEY_LEFT : rc = MOVE_LEFT; break;
case  KEY_RIGHT : rc = MOVE_RIGHT; break;
case ESCAPE : rc = ESCAPE_BTN; break;
case ENTER_KEY : rc = ENTER_BTN; break;
case ' ' : rc = ROTOR; break;
default : break;
  }
  return rc;
}




/*фигура задана массивом 4 на 4 из 0 и 1, 1 это часть фигуры
нам надо найти где в массиве крайний левый угол область фигуры
что бы слева фигура пристыковалась к левому краю игровой области
не выходя за него или не доходя до него 
перебор матрицы делаем по столбцам, зтем по строкам, 
как только найдена позиция стобика запоминаем его и циклы прекращаются
потому что переменная pos перестает равняться -1 */
int leftExtremPos(figura *f){
  int positon = -1;
  for (int j = 0 ; j < 4 && positon == -1; j++)
    for (int i = 0 ; i < 4 && positon == -1; i++)
      if (f->figur[i][j]) positon = j;
  return positon;
}
int rigtExtremPos(figura *posStart){
   int pos = -1;
 for (int j = 3 ; j >= 0 && pos == -1; j--)
    for (int i = 0 ; i < 4 && pos == -1; i++)
      if (posStart->figur[i][j]) pos = j;
  return pos;
}
int downExtremPos(figura *posStart){
 int pos = -1;
 for (int i = 3 ; i >= 0 && pos == -1; i--)
    for (int j = 0 ; j < 4 && pos == -1; j++)
      if (posStart->figur[i][j]) pos = i;
  return pos;
}

void moveleft(player_pos *frog_pos, figura *f) {
  if (f->x + leftExtremPos(f) != 1){
    refreshFigure(f, -1, 0);
  }
}
void moveright(player_pos *frog_pos, figura *posStart) {
  if (posStart->x + rigtExtremPos(posStart) != BOARD_M)
    refreshFigure(posStart, 1, 0);
}

int check(figura *f,  game_stats_t *gb){
  int result = 0;
  for (int i = f->y+1, k = 0; i < BOARD_N && k <  FSIZE; i++, k++)
     for(int j = f->x, l = 0; j < BOARD_M && l <  FSIZE; j++, l++)
     if(gb->gameField[i][j] != 0 && f->figur[k][l] == 1 )
     result = 1;
  return result;

}
void movedown(player_pos *frog_pos,  figura *f,  game_stats_t *gb) {
  if (f->y + downExtremPos(f) < BOARD_N  &&  !check(f,gb))
    refreshFigure(f, 0, 1);
  else {
    figuraGamefield(gb, f);
    initFigure(f);   
  }
}
void rotate(player_pos *frog_pos, figura *f) {
    hideFigure(f);
    rotateFigure(f);
    showFigure(f);
}

void on_start_state(signals sig, frog_state *state) {
  switch (sig) {
    case ENTER_BTN:
      *state = SPAWN;
      break;
    case ESCAPE_BTN:
      *state = EXIT_STATE;
      break;
    default:
      *state = START; // а мне это надо? 
      break;
  }
}
//отрисовка начало игры 
void on_spawn_state(frog_state *state, game_stats_t *stats, board_t *map,
                    player_pos *frog_pos, figura *posStart) {
  //if (stats->level > LEVEL_CNT) *state = GAMEOVER;
  //else if (!lvlproc(map, stats)) {
  //fill_finish(map->finish);
  //  print_finished(map);
  //  frogpos_init(frog_pos);
    hideIntro();
    initFigure(posStart); // инициализируем фигуру
    showFigure(posStart);
    *state = MOVING;
  //} else
  //  *state = FILE_ERROR_STATE;
}

void on_moving_state(signals sig, frog_state *state, board_t *map,
                     player_pos *frog_pos, figura *posStart,  game_stats_t *gamestats) {

  switch (sig) {
    // case MOVE_UP:
    //   moveup(frog_pos); // не используется т.е. убрать
    //   break;
    case MOVE_DOWN:
      movedown(frog_pos, posStart, gamestats);
      break;
    case MOVE_RIGHT:
      moveright(frog_pos, posStart); // сдвинуть фигуру вправо
      break;
    case MOVE_LEFT:
      moveleft(frog_pos, posStart);
      break;
    case ROTOR:
      rotate(frog_pos, posStart);
      break;      
    case ESCAPE_BTN:
      *state = EXIT_STATE;
      break;
    default:
    //printFigure(posStart); // фигура опускается ниже по игровому полю
      break;
  }

  if (*state != EXIT_STATE) {
    if (check_collide(frog_pos, map))
      *state = COLLIDE;
    else if (check_finish_state(frog_pos, map))
      *state = REACH;
    else
      *state = SHIFTING;
  }
}

void on_shifting_state(frog_state *state, game_stats_t *stats, board_t *map,
                       player_pos *frog_pos) {
  // shift_map(map);

  if (check_collide(frog_pos, map))
    *state = COLLIDE;
  else {
    *state = MOVING;
    print_board(map, frog_pos);
    print_stats(stats);
  }
}

void on_reach_state(frog_state *state, game_stats_t *stats, board_t *map,
                    player_pos *frog_pos) {
  stats->score += 1;
  add_proggress(map);

  if (check_level_compl(map)) {
    stats->level++;
    stats->speed++;
    *state = SPAWN;
  } else {
    frogpos_init(frog_pos);
    //print_finished(map);
    *state = MOVING;
  }
}

void on_collide_state(frog_state *state, game_stats_t *stats,
                      player_pos *frog_pos) {
  if (stats->lives) {
    stats->lives--;
    frogpos_init(frog_pos);
    *state = MOVING;
  } else
    *state = GAMEOVER;
}


void sigact(signals sig, frog_state *state, game_stats_t *gamestats, board_t *map,
            player_pos *frog_pos, figura *posStart) {
  switch (*state) {
    case START:
      on_start_state(sig, state);
      break;
    case SPAWN:
      on_spawn_state(state, gamestats, map, frog_pos, posStart);
      break;
    case MOVING:
      on_moving_state(sig, state, map, frog_pos, posStart, gamestats);
      break;
    case SHIFTING:  // сдвиг карты
      on_shifting_state(state, gamestats, map, frog_pos);
      break;
    case REACH:
      on_reach_state(state, gamestats, map, frog_pos);
      break;
    case COLLIDE:
      on_collide_state(state, gamestats, frog_pos);
      break;
    case GAMEOVER:
      print_banner(gamestats);
      break;
    default:
          
      break;
  }
}

// сдвиг вверх мне не нужен 
/*
void moveup(player_pos *frog_pos ) { 
  if (frog_pos->y != 1)

  {
    sleep(10);
    CLEAR_BACKPOS(frog_pos->y, frog_pos->x);
    frog_pos->y -= 2;
  }
}
*/
