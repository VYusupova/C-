#ifndef OBJECTS_H
#define OBJECTS_H

#include <ncurses.h>
#include "defines.h"

typedef struct
{
    int x;
    int y;
} player_pos;

typedef struct
{
    char finish[BOARD_M + 2];
    char ways[21 + 2][21 + 2];
} board_t;

typedef struct
{
    int score;
    int level;
    int speed;
    int lives;
    int won;
    int gameField[BOARD_N][BOARD_M];
} game_stats_t;

typedef struct
{
    char matrix[BANNER_N + 1][BANNER_M + 1];
} banner_t;


typedef struct
{
    int x ;
    int y ;
    int figur[FSIZE][FSIZE];
    int typeFigure;
} figura;

typedef enum
{
   FIGURE_Q = 1,
   FIGURE_I,
   FIGURE_S,
   FIGURE_Z,
   FIGURE_L,
   FIGURE_J,
   FIGURE_T
} listFigures;


#endif