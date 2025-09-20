#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "back.h"

void ProcessInput(UserAction_t input);
GameInfo_t GetGameData();
typedef enum {
  START,
  PLAY,
  PAUSE,
  GAME_OVER,
  QUIT,
} GameState;

#endif  // CONTROLLER_H