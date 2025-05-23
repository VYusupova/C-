#ifndef OBJECTS_H
#define OBJECTS_H

#include "defines.h"

typedef struct
{
    int n;
    int m;
    int x ;
    int y ;
    int **figur;
    int typeFigure;
} figura;

typedef struct
{
    int **field;       //[FIELD_N][FIELD_M];
    figura *fnext;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;    
    figura *fnow;

} GameInfo_t;


typedef enum
{
   FIGURE_Q = 1,
   FIGURE_I,
   FIGURE_S,
   FIGURE_Z,
   FIGURE_L,
   FIGURE_J,
   FIGURE_T
} typeFigures;

typedef enum
{
    Start = 0,
    Pause,
    Terminate, // GAMEOVER
    Left,
    Right,
    Up,
    Down,
    Action
} UserAction_t;

#endif
