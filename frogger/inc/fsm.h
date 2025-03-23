#ifndef FSM_H
#define FSM_H

#include "defines.h"
#include "objects.h"
#include "frog_backend.h"
#include "frog_frontend.h"
#include "tetris.h"

typedef enum
{
    START = 0,
    SPAWN,
    MOVING,
    SHIFTING,
    REACH,
    COLLIDE,
    GAMEOVER,
    EXIT_STATE,
    FILE_ERROR_STATE  // TO END DELETE in tetris not use file
} frog_state;

typedef enum
{
    MOVE_UP = 0,
    MOVE_DOWN,
    MOVE_RIGHT,
    MOVE_LEFT,
    ESCAPE_BTN,
    ENTER_BTN,
    ROTOR,
    NOSIG
} signals;


signals get_signal(int user_input);
void sigact(signals sig, frog_state *state, game_stats_t *stats, board_t *map, player_pos *frog_pos, figura *posStart);
void on_start_state(signals sig, frog_state *state);
void movedown(player_pos *frog_pos,  figura *moveFigure,  game_stats_t *gamestats);
int check(figura *f,  game_stats_t *gb);
#endif