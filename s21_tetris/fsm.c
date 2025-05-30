#include "../inc/fsm.h"

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

UserAction_t get_signal(int user_input) {
  UserAction_t action = -1;

  switch (user_input) {
    case KEY_DOWN:
      action = Down;
      break;
    case KEY_LEFT:
      action = Left;
      break;
    case KEY_RIGHT:
      action = Right;
      break;
    case ESCAPE:
      action = Terminate;
      break;
    case ENTER_KEY:
      action = Start;
      break;
    case SPACE:
      action = Action;
      break;
    case PAUSE_p:
      action = Pause;
      break;
    case PAUSE_P:
      action = Pause;
      break;
    default:
      break;
  }
  return action;
}

static void shifted(tetris_state *state, GameInfo_t *game) {
  if (!collisionDown(game->fnow, game)) {
    refreshFigure(game->fnow, 0, 1);
    *state = MOVING;
  } else {
    *state = ATTACHING;
  }
}

static void rotate(GameInfo_t *game) {
  hideFigure(game->fnow);
  rotateFigure(game->fnow, game);
  showFigure(game->fnow);
}

static void started(const UserAction_t *act, GameInfo_t *game,
                    tetris_state *state) {
  switch (*act) {
    case Start:
      hideFigure(game->fnext);
      initGame(game);
      refreshGameField(game);
      initFigure(game->fnow, ((rand() % 8) + 1));
      initFigure(game->fnext, ((rand() % 8) + 1));
      *state = SPAWN;
      break;
    case Terminate:
      *state = EXIT;
      break;
    default:
      break;
  }
}

static void spawned(GameInfo_t *game, tetris_state *state) {
  swapFigure(game->fnow, game->fnext);
  hideFigure(game->fnext);
  initFigure(game->fnext, ((rand() % 8) + 1));
  showFigure(game->fnext);
  showFigure(game->fnow);
}

static void attach(tetris_state *state, GameInfo_t *game) {
  if (collisionUp(game->fnow)) {
    *state = GAMEOVER;
  } else
    *state = SPAWN;
  putGamefield(game);
  score(game);
  refreshGameField(game);
}

static void moved(const UserAction_t *act, tetris_state *state,
                  GameInfo_t *game) {
  switch (*act) {
    case Left:
      if (!collisionLeft(game->fnow, game)) refreshFigure(game->fnow, -1, 0);
      *state = SHIFTING;
      break;
    case Right:
      if (!collisionRight(game->fnow, game)) refreshFigure(game->fnow, 1, 0);
      *state = SHIFTING;
      break;
    case Down:
      while (*state != ATTACHING) {
        shifted(state, game);
      }
      break;
    case Action:
      rotate(game);
      *state = SHIFTING;
      break;
    case Pause:
      *state = SHIFTING;
      printPause();
      game->pause = 1;
      print_stats(game);
      while (game->pause) {
        UserAction_t action = get_signal(GET_USER_INPUT);
        if (action == Pause) game->pause = 0;
        if (action == Start) game->pause = 0;
        if (action == Terminate) {
          game->pause = 0;
          *state = EXIT;
        }
      }
      print_stats(game);
      refreshGameField(game);
      refreshFigure(game->fnow, 0, 0);
      break;
    case Terminate:
      *state = EXIT;
      break;
    default:
      *state = SHIFTING;
      break;
  }
}

void sigact(const UserAction_t *act, tetris_state *state, GameInfo_t *game) {
  print_stats(game);
  // napms(2000); //func sleep for at least ms milliseconds
  switch (*state) {
    case START:
      started(act, game, state);
      break;
    case SPAWN: /*Рождение нового блока*/
      spawned(game, state);
      *state = MOVING;
      break;
    case MOVING:
      moved(act, state, game);

      break;
    case SHIFTING: /*движение блока вниз*/
      shifted(state, game);

      break;
    case ATTACHING: /*положить блок на игровое поле*/
      attach(state, game);

      break;
    case GAMEOVER:
      gameOver();  // gameOVER thanks for game
      *state = START;
      break;
    default:
      break;
  }
}
