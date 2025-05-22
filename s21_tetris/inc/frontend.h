#ifndef FRONTEND_H
#define FRONTEND_H

//#include <string.h>
#include "defines.h"
#include "objects.h"
//#include <stdlib.h>

//#define FIGURE_HIDE 0
//#define 

typedef enum
{  
   FIGURE_HIDE = 0,
   COLOR_1 = 1,
   COLOR_2, COLOR_3, COLOR_4,
   COLOR_5, COLOR_6, COLOR_7, 
   COLOR_8, COLOR_9, COLOR_10,
   COLOR_11,COLOR_12,COLOR_13,
COLOR_14,COLOR_15,COLOR_16,COLOR_17,
COLOR_18,COLOR_19,
   COLOR_PINK,
   MASSEGE = 50
} Colors;



void initColors();
void printGameField(GameInfo_t *gameBakend);
void refreshGameField(GameInfo_t *gameBakend) ;
//void hide(void);

void refreshFigure(figura *f, int dx, int dy);
void printFigure(const figura *f);
void hideFigure(figura *f);
void showFigure(figura *f);



void print_overlay(void);
void print_levelerror(void);
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void print_stats(GameInfo_t *stats);

void print_cars(board_t *game);
void print_finished(board_t *game);

int read_banner(GameInfo_t *stats); //, banner_t *banner

void showIntro(void);
void gameOver(void);
void writeScore(GameInfo_t *stats);
void printPause(void);


#endif
