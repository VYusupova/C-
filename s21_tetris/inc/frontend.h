#ifndef FRONTEND_H
#define FRONTEND_H

#include <stdlib.h>

#include "defines.h"
#include "objects.h"

typedef enum {
  FIGURE_HIDE = 0,
  COLOR_1 = 1,
  COLOR_2,
  COLOR_3,
  COLOR_4,
  COLOR_5,
  COLOR_6,
  COLOR_7,
  COLOR_8,
  COLOR_9,
  COLOR_10,
  COLOR_11,
  COLOR_12,
  COLOR_13,
  COLOR_14,
  COLOR_15,
  COLOR_16,
  COLOR_17,
  COLOR_18,
  COLOR_19,
  COLOR_PINK,
  MASSEGE = 50
} Colors;

void initColors(void);
void gameOver(void);
void print_stats(GameInfo_t *game);
void print_overlay(void);
void printPause(void);
void hideFigure(const figura *f);
void showFigure(figura *f);
void refreshFigure(figura *f, int dx, int dy);
void refreshGameField(GameInfo_t *game);

#endif