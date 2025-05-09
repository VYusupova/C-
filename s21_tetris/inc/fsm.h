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
               GAMEOVER 
} tetris_state;

void sigact(UserAction_t *userAct, tetris_state *state, game_stats_t *gamestats,
            figura *fnow);
void started(UserAction_t *userAct, game_stats_t *game, tetris_state *state);
void moved(UserAction_t *userAct, tetris_state *state, game_stats_t *gamestats,
            figura *fnow);
            void gg(game_stats_t *game, tetris_state *state);


void movedown(/*UserAction_t *userAct,*/ tetris_state *state,
              figura *moveFigure, game_stats_t *gamestats);

UserAction_t get_signal(int user_input);

// void on_start_state(signals sig, frog_state *state, game_stats_t *game);

void moveleft(game_stats_t *gamestats);
int check(figura *f, game_stats_t *gb);

int collisionDown(figura *f, game_stats_t *gb);



#endif
