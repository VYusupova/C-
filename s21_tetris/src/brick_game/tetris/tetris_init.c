// TO DO # 0 в отдельные методы вынесены операции инициализации фигуры по типу
// TO DO # 1 проверить на утечки памяти

#ifndef TETRIS_INIT
#define TETRIS_INIT

#include "../../../inc/tetris.h"

int **create(int size_n, int size_m){
	int **matrix = (int**)calloc(size_n, sizeof(int*));
	for (size_t i = 0; i < (size_t)size_n; i++){
		matrix[i] = (int*)calloc(size_m, sizeof(int));
	}
	return matrix;
}

void tetFree(int **matrix, int size_n, int size_m){

	for (size_t i = 0; i < (size_t)size_n; i++){
		free(matrix[i]);
		matrix[i] = NULL;
	}
	free(matrix);
}

void fillZero(int **matrix, int size_n, int size_m) {
    for (int i = 0; i < size_n; i++)
       for (int j = 0; j < size_m; j++) 
         matrix[i][j] = 0; 
}

void initFigure(figura *f){

    fillZero(f->figur, FSIZE, FSIZE);

    int fig = (rand() % 8)+1;   
    switch (fig){
    case FIGURE_Q :   
        iniFigura_Q(f);
        break;
    case FIGURE_I : 
        iniFigura_I(f);
        break;
    case FIGURE_S : 
        iniFigura_S(f);
        break;
    case FIGURE_Z : 
        iniFigura_Z(f);
        break;     
    case FIGURE_L : 
        iniFigura_L(f);
        break; 
     case FIGURE_J : 
        iniFigura_J(f);
        break;      
    default : 
        iniFigura_T(f);
        break;       
    }
     f->typeFigure = (int)(rand() % COLOR_PINK)+1; 
     while(f->typeFigure < 0){     f->typeFigure = (int)(rand() % COLOR_PINK)+1; }
}

void initStartPosFigure(figura *f, int x, int y){
    f->x = x;
    f->y = y;
}

void swapFigure(figura *fnow, figura *fnext){
   fnow->x = START_X;
   fnow->y = START_Y;
   fnow->n = fnext->n;
   fnow->m = fnext->m;
   fnow->typeFigure = fnext->typeFigure;
    for (int x = 0; x < FSIZE; x++)
        for (int y = 0; y < FSIZE; y++)
            fnow->figur[y][x] = fnext->figur[y][x];
}

void initGame(GameInfo_t *game) { 
  game->level = 0;
  game->score = 0;
  game->high_score = readScore();
  game->speed = SPEED;
  game->pause = 0;
  initStartPosFigure(game->fnow, START_X, START_Y);
  initStartPosFigure(game->fnext, R_NEXT_X, R_NEXT_Y);
  game->field = create(FIELD_N, FIELD_M);
  fillZero(game->field, FIELD_N, FIELD_M);
}

//запомним и зафиксируем фигуру на игровом поле
void figuraGamefield(GameInfo_t *gb, figura *f){
    for(int y = f->y, k = 0; y <  FIELD_N && k < f->n; y++, k++)
        for(int x = f->x, l = 0; x < FIELD_M && l < f->m; x++, l++)
            if(f->figur[k][l]) gb->field[y][x] = f->typeFigure;
}


void iniFigura_Q(figura *f){
    f->n = 2;
    f->m = 2;
    f->figur[0][0] = 1; 
    f->figur[0][1] = 1;
    f->figur[1][0] = 1;
    f->figur[1][1] = 1;
}
void iniFigura_I(figura *f){
    f->n = 4;
    f->m = 1;
    f->figur[0][0] = 1; 
    f->figur[1][0] = 1;
    f->figur[2][0] = 1;
    f->figur[3][0] = 1;
}
void iniFigura_S(figura *f){
    f->n = 2;
    f->m = 3;
    f->figur[0][0] = 0; 
    f->figur[0][1] = 1; 
    f->figur[0][2] = 1; 
    f->figur[1][0] = 1;
    f->figur[1][1] = 1;
    f->figur[1][2] = 0;
}
void iniFigura_Z(figura *f){
    f->n = 2;
    f->m = 3;
    f->figur[0][0] = 1; 
    f->figur[0][1] = 1; 
    f->figur[0][2] = 0;
    f->figur[1][0] = 0;
    f->figur[1][1] = 1;
    f->figur[1][2] = 1;
}
void iniFigura_L(figura *f){
    f->n = 3;
    f->m = 2;
    f->figur[0][0] = 1; 
    f->figur[1][0] = 1; 
    f->figur[2][0] = 1;
    f->figur[0][1] = 0; 
    f->figur[1][1] = 0; 
    f->figur[2][1] = 1;
}
void iniFigura_J(figura *f){
    f->n = 3;
    f->m = 2;
    f->figur[0][1] = 1; 
    f->figur[1][1] = 1; 
    f->figur[2][1] = 1;
    f->figur[0][0] = 0; 
    f->figur[1][0] = 0; 
    f->figur[2][0] = 1;
}
void iniFigura_T(figura *f){
    f->n = 2;
    f->m = 3;
    f->figur[0][0] = 0;
    f->figur[1][0] = 1; 
    f->figur[0][1] = 1; 
    f->figur[1][1] = 1;
    f->figur[0][2] = 0;
    f->figur[1][2] = 1;
}

#endif
