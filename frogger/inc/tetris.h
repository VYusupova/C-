#include "objects.h"
#include "defines.h"
#include <stdlib.h>
#include <frog_frontend.h>

void initFigure(figura *f);
void initMatrix(figura *f);
void iniFigura_Q(figura *f);
void iniFigura_I(figura *f);
void iniFigura_S(figura *f);
void iniFigura_Z(figura *f);
void iniFigura_L(figura *f);
void iniFigura_J(figura *f);
void iniFigura_T(figura *f);


void initGameField(game_stats_t *gameBakend);
void figuraGamefield(game_stats_t *gb, figura *f);

void stats_init(game_stats_t *gameBakend);

int collisionLeft(figura *f, game_stats_t *gb);
int collisionRight(figura *f, game_stats_t *gb);
int collisionUp(figura *f, game_stats_t *gb);

int collisionGameField(figura *f,  game_stats_t *gb);

void rotateFigure(figura *f, game_stats_t *gb);

int collisionDown(figura *f, game_stats_t *gb);
