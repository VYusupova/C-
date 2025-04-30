#ifndef FSM_H
#define FSM_H

#include "defines.h"
#include "objects.h"

#include "frog_frontend.h"
#include "tetris.h"




UserAction_t get_signal(int user_input);
void sigact(UserAction_t *state, game_stats_t *stats, figura *posStart); //board_t *map,
			 
//void on_start_state(signals sig, frog_state *state, game_stats_t *game);
void movedown(UserAction_t *state,  figura *moveFigure,  game_stats_t *gamestats);
void moveleft(figura *moveFigure,  game_stats_t *gamestats);
int check(figura *f,  game_stats_t *gb);

int collisionDown(figura *f, game_stats_t *gb);

void start(game_stats_t *game);

#endif
