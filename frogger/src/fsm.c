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

  switch (user_input) {
    case KEY_DOWN:
      rc = MOVE_DOWN;
      break;
    case KEY_LEFT:
      rc = MOVE_LEFT;
      break;
    case KEY_RIGHT:
      rc = MOVE_RIGHT;
      break;
    case ESCAPE:
      rc = ESCAPE_BTN;
      break;
    case ENTER_KEY:
      rc = ENTER_BTN;
      break;
    case ' ':
      rc = ROTOR;
      break;
    default:
      break;
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

void moveleft(figura *f, game_stats_t *gb) {
  if (!collisionLeft(f, gb)) refreshFigure(f, -1, 0);
}
void moveright(figura *f, game_stats_t *gb) {
  if (!collisionRight(f, gb)) refreshFigure(f, 1, 0);
}
// void movedown(figura *f, game_stats_t *gb) {
//   if (!collisionDown(f, gb))
//     refreshFigure(f, 0, 1);
//   else {
//     figuraGamefield(gb, f);
//     initFigure(f);
//   }
// }

void movedown(frog_state *state, figura *f, game_stats_t *gb) {
  timeout(1200);
  if (!collisionDown(f, gb))
    refreshFigure(f, 0, 1);
  else {
    figuraGamefield(gb, f);
    if (!collisionUp(f, gb))
      initFigure(f);
    else
      *state = GAMEOVER;
  }
}

void rotate(figura *f, game_stats_t *gb) {
  hideFigure(f);
  rotateFigure(f, gb);
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
      *state = START;  // а мне это надо?
      break;
  }
}
// отрисовка начало игры
void on_spawn_state(frog_state *state, game_stats_t *stats, board_t *map,
                    player_pos *frog_pos, figura *posStart) {
  // if (stats->level > LEVEL_CNT) *state = GAMEOVER;
  // else if (!lvlproc(map, stats)) {
  // fill_finish(map->finish);
  //   print_finished(map);
  //   frogpos_init(frog_pos);
  hideIntro();
  initFigure(posStart);  // инициализируем фигуру
  showFigure(posStart);
  *state = MOVING;
  //} else
  //  *state = FILE_ERROR_STATE;
}

void on_moving_state(signals sig, frog_state *state, board_t *map,
                     player_pos *frog_pos, figura *f, game_stats_t *gamestats) {
  switch (sig) {
      // case MOVE_UP:
      //   moveup(frog_pos); // не используется т.е. убрать
      //   break;

    case MOVE_DOWN:
      movedown(state, f, gamestats);
      break;
    case MOVE_RIGHT:
      moveright(f, gamestats);  // сдвинуть фигуру вправо
      break;
    case MOVE_LEFT:
      moveleft(f, gamestats);
      break;
    case ROTOR:
      rotate(f, gamestats);
      break;
    case ESCAPE_BTN:
      *state = EXIT_STATE;
      break;
    default:
      // movedown(state, f, gamestats);
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
    // print_finished(map);
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

void sigact(signals sig, frog_state *state, game_stats_t *gamestats,
            board_t *map, player_pos *frog_pos, figura *posStart) {
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
