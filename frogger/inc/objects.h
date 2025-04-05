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
    int figur[FSIZE][FSIZE]; // может не работать 
//  int **figur;     //тогда надо писать доп функцию выделения памяти потом
    int typeFigure;
} figura;

typedef struct
{
    int score;
    int level;
    int speed;
    int lives;
    int won;
    int gameField[BOARD_N][BOARD_M];
    figura *fnow;
    figura *fnext;
} game_stats_t;

typedef struct
{
    char matrix[BANNER_N + 1][BANNER_M + 1];
} banner_t;




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
