#include "inc/fsm.h"

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
      initGame(game);
      refreshGameField(game);
      initFigure(game->fnow, (RAND_TYPE_FIGUR);
      initFigure(game->fnext, (RAND_TYPE_FIGUR);
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
  initFigure(game->fnext, (RAND_TYPE_FIGUR);
  showFigure(game->fnext);
  showFigure(game->fnow);
}

static void attach(tetris_state *state, GameInfo_t *game) {
  if (collisionUp(game->fnow)) {
    *state = GAMEOVER;
  } else {
    *state = SPAWN;
    putGamefield(game);
    score(game);
    refreshGameField(game);
  }
}

static void pause(GameInfo_t *game, tetris_state *state) {
  print_stats(game);
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
      pause(game, state);
      *state = SHIFTING;
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
      gameOver(); /* gameOVER thanks for game*/
      hideFigure(game->fnext);
      *state = START;
      break;
    default:
      break;
  }
}
