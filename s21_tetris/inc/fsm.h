#ifndef FSM_H
#define FSM_H

#include "defines.h"
#include "frontend.h"
#include "objects.h"
#include "tetris.h"

typedef enum { START = 0, 
               MOVING, 
               SPAWN,
               SHIFTING,
               ATTACHING,
               GAMEOVER,
               EXIT 
} tetris_state;

void sigact(UserAction_t *userAct, tetris_state *state, GameInfo_t *gamestats,
            figura *fnow);
void started(UserAction_t *userAct, GameInfo_t *game, tetris_state *state);
void moved(UserAction_t *userAct, tetris_state *state, GameInfo_t *gamestats,
            figura *fnow);

void shifted(tetris_state *state, figura *f, GameInfo_t *game);
void attach(tetris_state *state, GameInfo_t *game, figura *f);

UserAction_t get_signal(int user_input);

//void moveleft(GameInfo_t *gamestats);
int check(figura *f, GameInfo_t *gb);

//int collisionDown(figura *f, GameInfo_t *gb);



#endif
