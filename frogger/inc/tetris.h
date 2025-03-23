#include "objects.h"
#include "defines.h"
#include <stdlib.h>

void initFigure(figura *f);
void rotateFigure(figura *f);
void initGameField(game_stats_t *gameBakend);
void figuraGamefield(game_stats_t *gb, figura *f);

void stats_init(game_stats_t *gameBakend);

void initialFigura_I(figura *f);