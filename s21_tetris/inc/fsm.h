#ifndef FSM_H
#define FSM_H

#include "defines.h"
#include "frontend.h"
#include "objects.h"
#include "tetris.h"

typedef enum {
  START = 0,
  MOVING,
  SPAWN,
  SHIFTING,
  ATTACHING,
  GAMEOVER,
  EXIT
} tetris_state;

UserAction_t get_signal(int user_input);
void sigact(const UserAction_t *act, tetris_state *state, GameInfo_t *game);

GameInfo_t updateCurrentState();

#endif
