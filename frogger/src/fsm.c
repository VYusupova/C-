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
 //   case 'p':
 //     rc = PAUSE_BTN;
 //     break;
    default:
      rc = Action ; //NOSIG;
      break;
  }
  return rc;
}

void moveleft(figura *f, game_stats_t *gb) {
  if (!collisionLeft(f, gb)) refreshFigure(f, -1, 0);
}

// void moveleft(game_stats_t *gb) {
//  if (!collisionLeft(gb->fnow, gb)) refreshFigure(gb->fnow, -1, 0);
//}

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
  if (!collisionDown(f, gb))
    refreshFigure(f, 0, 1);
  else {
    figuraGamefield(gb, f);
    if (!collisionUp(f, gb)) {
      swapFigure(gb->fnow, gb->fnext);
      // f = gb->fnow;
      hideFigure(gb->fnext);
      initFigure(gb->fnext);

      refreshFigure(gb->fnext, 0, 0);
      // TO DO maybe  used showFigure();
    } else
      *state = GAMEOVER;
  }
}

void rotate(figura *f, game_stats_t *gb) {
  hideFigure(f);
  rotateFigure(f, gb);
  showFigure(f);
}

void on_start_state(signals sig, frog_state *state, game_stats_t *game) {
  switch (sig) {
    //case ENTER_BTN:
    //  *state = SPAWN;
    //  break;
    case ESCAPE_BTN:
      *state = Terminate; // EXIT_STATE;
      break;
    default:
      //*state = Start;  // а мне это надо?
        hideIntro();
  initFigure(game->fnow);  // инициализируем фигуру
  initFigure(game->fnext);
  showFigure(game->fnow);

  game->fnext->x = R_NEXT_X;
  game->fnext->y = R_NEXT_Y;

  showFigure(game->fnext);
  *state = Action; //MOVING;

      break;
  }
}
// отрисовка начало игры
void on_spawn_state(frog_state *state, game_stats_t *game, board_t *map,
                    player_pos *frog_pos, figura *now) {
  // if (stats->level > LEVEL_CNT) *state = GAMEOVER;
  // else if (!lvlproc(map, stats)) {
  // fill_finish(map->finish);
  //   print_finished(map);
  //   frogpos_init(frog_pos);

  // figura next;
  //   initFigure(&next);
  //   next.x = 0;
  //   next.y = 0;
  //   showFigure(&next);
  // initFigure(stats->fnext);
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
      *state = Terminate; //EXIT_STATE;
      break;
    //case PAUSE_BTN:
    //  while (GET_USER_INPUT <> 'p') {}
    //  break;
    default:
      // movedown(state, f, gamestats);
      break;
  }

  if (*state != Terminate) { //EXIT_STATE
    if (check_collide(frog_pos, map))
      *state = COLLIDE;
    else if (check_finish_state(frog_pos, map))
      *state = REACH;
    else
      *state = SHIFTING;
  }
}

//void on_shifting_state(frog_state *state, game_stats_t *stats, board_t *map,
                    //   player_pos *frog_pos) {
  // shift_map(map);

  //if (check_collide(frog_pos, map))
 //   *state = COLLIDE;
 // else {
  //  *state = MOVING;
  //  print_board(map, frog_pos);
  //  print_stats(stats);
//  }
//}

void on_reach_state(frog_state *state, game_stats_t *stats, board_t *map,
                    player_pos *frog_pos) {
  stats->score += 1;
  add_proggress(map); // TO DO DEL

  if (check_level_compl(map)) {
    stats->level++;
    stats->speed++;
    //*state = SPAWN;
  } else {
    frogpos_init(frog_pos);
    // print_finished(map);
    *state = Action;
  }
}

void on_collide_state(frog_state *state, game_stats_t *stats,
                      player_pos *frog_pos) {
  if (stats->lives) {
    stats->lives--;
    frogpos_init(frog_pos);
    *state = Action; //MOVING;
  } else
    *state = GAMEOVER;
}

void sigact(signals sig, frog_state *state, game_stats_t *gamestats,
            board_t *map, player_pos *frog_pos, figura *posStart) {
  switch (*state) {
    case Start:
      on_start_state(sig, state, gamestats);
      break;
    //case SPAWN:
    //  on_spawn_state(state, gamestats, map, frog_pos, posStart);
    //  break;
    case Action: //MOVING:
      on_moving_state(sig, state, map, frog_pos, posStart, gamestats);
      break;
    //case SHIFTING:  // сдвиг карты
    //  on_shifting_state(state, gamestats, map, frog_pos);
    //  break;
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
