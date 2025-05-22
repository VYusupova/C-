
#include <locale.h>
#include <stdlib.h>

#include "defines.h"

#include "fsm.h"
#include "objects.h"

int **create(int size_n, int size_m);
void tetFree(int **matrix, int size_n, int size_m);

void initFigure(figura *f);
void iniFigura_Q(figura *f);
void iniFigura_I(figura *f);
void iniFigura_S(figura *f);
void iniFigura_Z(figura *f);
void iniFigura_L(figura *f);
void iniFigura_J(figura *f);
void iniFigura_T(figura *f);
void swapFigure(figura *fnow, figura *fnext);

//void initGameField(GameInfo_t *game);
void initGame(GameInfo_t *game);
void figuraGamefield(GameInfo_t *game, figura *f);

//void initGame(GameInfo_t *game);

int collisionLeft(figura *f, GameInfo_t *game);
int collisionRight(figura *f, GameInfo_t *game);
int collisionUp(figura *f, GameInfo_t *game);
int collisionDown(figura *f, GameInfo_t *game);

int collisionGameField(GameInfo_t *game, int down, int left);

void rotateFigure(figura *f, GameInfo_t *game);

void score(GameInfo_t *game);
void levelUP(GameInfo_t *game);
void shiftField(GameInfo_t *game, int y);
int readScore();
void writeScore(GameInfo_t *game);

void initStartPosFigure(figura *f, int x, int y);
void initMatrix(figura *f);
