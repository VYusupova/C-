#ifndef OBJECTS_H
#define OBJECTS_H

#include <ncurses.h>
#include "defines.h"

// конструктор для структуры 
/*
typedef struct Point
{
    Point (int x = START_X, int y = START_Y) : x(x) , y(y) {}
    int x;
    int y;
};
*/
/*typedef struct
{
    int x;
    int y;
} player_pos;*/

typedef struct
{
    char finish[BOARD_M + 2];
    char ways[21 + 2][21 + 2];
} board_t;


/*
* Переписываем структуру фигур добавив размер N*M 
* при инициализации фигуры будет задаваться размер 
* минимально необходимый для отрисовки данной фигуры на плоскости
* т.е для фигуры I это матрица размером 4х1  или 1х4 если делаем попворот
*/
typedef struct
{
    int n;
    int m;
    int x ;
    int y ;
//Point point;
    int figur[FSIZE][FSIZE]; 
//  int **figur;     //TO DO rewrite dynamic alloc memory 
    int typeFigure;
} figura;




typedef struct
{
    int score;
    int level;
    int speed;
    int lives;
    int won;
    int gameField[FIELD_N][FIELD_M];
    figura *fnow;
    figura *fnext;
} game_stats_t;
//} game;


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
