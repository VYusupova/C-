#ifndef FRONTEND_H
#define FRONTEND_H

#include <string.h>
#include "defines.h"
#include "objects.h"
#include <stdlib.h>

#define FIGURE_HIDE 0


void initColors();
void printGameField(game_stats_t *gameBakend);
void refreshGameField(game_stats_t *gameBakend) ;
void hide(void);

void refreshFigure(figura *f, int dx, int dy);
void printFigure(figura *position);
void hideFigure(figura *position);
void showFigure(figura *position);



void print_overlay(void);
void print_levelerror(void);
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void print_stats(game_stats_t *stats);

void print_cars(board_t *game);
void print_finished(board_t *game);

int read_banner(game_stats_t *stats); //, banner_t *banner

void showIntro(void);
void gameOver(void);
void writeScore(game_stats_t *stats);


#endif
