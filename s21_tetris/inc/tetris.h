
#include <locale.h>
#include <stdlib.h>

#include "defines.h"
#include "fsm.h"
#include "objects.h"

int **create(int size_n, int size_m);
void tetFree(int **matrix, int size_n, int size_m);

void initFigure(figura *f, int typeFigur);

void swapFigure(figura *fnow, figura *fnext);
void initGame(GameInfo_t *game);

void putGamefield(GameInfo_t *game);

int collisionLeft(const figura *f, GameInfo_t *game);
int collisionRight(const figura *f, GameInfo_t *game);
int collisionUp(const figura *f);
int collisionDown(const figura *f, GameInfo_t *game);

void rotateFigure(figura *f, GameInfo_t *game);

void score(GameInfo_t *game);

int readScore();
void writeScore(const GameInfo_t *game);
void initMatrix(figura *f);
