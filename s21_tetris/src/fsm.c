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

UserAction_t get_signal(int user_input) {  // TO DO RENAME
  UserAction_t rc = -1;

  switch (user_input) {
    case KEY_UP:
      rc = Up;
      break;
    case KEY_DOWN:
      rc = Down;
      break;
    case KEY_LEFT:
      rc = Left;
      break;
    case KEY_RIGHT:
      rc = Right;
      break;
    case ESCAPE:
      rc = Terminate;
      break;
    case ENTER_KEY:
      rc = Start;
      break;
    case SPACE:
      rc = Action;
      break;
    case PAUSE_p:
      rc = Pause;
      break;
    case PAUSE_P:
      rc = Pause;
      break;
    default:
      // rc = Down;
      break;
  }
  return rc;
}

void movedown(tetris_state *state, figura *f, game_stats_t *gb) {
  if (!collisionDown(f, gb)) {
    refreshFigure(f, 0, 1);
    *state = MOVING;
  } else {
    *state = ATTACHING;
    if (collisionUp(f, gb)) {
      *state = GAMEOVER;
    }
  }
}

void rotate(figura *f, game_stats_t *gb) {
  hideFigure(f);
  rotateFigure(f, gb);
  showFigure(f);
}

void started(UserAction_t *userAct, game_stats_t *game, tetris_state *state) {
  switch (*userAct) {
    case Start:
      refreshGameField(game);
      initFigure(game->fnow);  // инициализируем фигуру
      initFigure(game->fnext);
      *state = SPAWN;
      break;
    case Terminate:
      *state = GAMEOVER;
      break;
    default:
      break;
  }
}

void spawned(game_stats_t *gb, tetris_state *state) {
  swapFigure(gb->fnow, gb->fnext);
  hideFigure(gb->fnext);
  initFigure(gb->fnext);
  showFigure(gb->fnext);
  showFigure(gb->fnow);
}

void attaching(game_stats_t *gb, figura *f) {
  figuraGamefield(gb, f);
  score(gb);
  refreshGameField(gb);
}

void moved(UserAction_t *userAct, tetris_state *state, game_stats_t *gb,
           figura *fnow) {
  switch (*userAct) {
    case Left:
      if (!collisionLeft(gb->fnow, gb)) refreshFigure(gb->fnow, -1, 0);
      *state = SHIFTING;
      break;
    case Right:
      if (!collisionRight(gb->fnow, gb)) refreshFigure(gb->fnow, 1, 0);
      *state = SHIFTING;
      break;
    case Up:
      break;
    case Down:
      while (*state != ATTACHING) {
        movedown(state, fnow, gb);
      }
      break;
    case Action:
      rotate(fnow, gb);
      *state = SHIFTING;
      break;
    case Pause:
      printPause();
      while (get_signal(GET_USER_INPUT) != Pause) {
      };
      refreshGameField(gb);
      refreshFigure(gb->fnow, 0, 0);
      break;
    case Terminate:
      gameOver();
      *state = GAMEOVER;
      break;
    default:
      *state = SHIFTING;
      break;
  }
}

void sigact(UserAction_t *userAct, tetris_state *state, game_stats_t *gamestats,
            figura *fnow) {
  print_stats(gamestats);
  // napms(2000); //func sleep for at least ms milliseconds
  switch (*state) {
    case START:
      started(userAct, gamestats, state);
      break;
    case SPAWN: /*Рождение нового блока*/
      spawned(gamestats, state);
      *state = MOVING;
      break;
    case MOVING:
      moved(userAct, state, gamestats, fnow);
      break;
    case SHIFTING: /*движение блока вниз*/
      movedown(state, fnow, gamestats);
      break;
    case ATTACHING: /*положить блок на игровое поле*/
      attaching(gamestats, fnow);
      *state = SPAWN;
      break;
    case GAMEOVER:
      gameOver();  // gameOVER thanks for game
      timeout(1700);
      break;
    default:
      break;
  }
}
