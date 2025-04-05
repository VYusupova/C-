#include "tetris.h"
// TO DO # 0 в отдельные методы вынесены операции инициализации фигуры по типу
void initFigure(figura *f){

    // TO DO в идеале надо сделать так что бы матрица выделялась динамически
    // TO DO выделение матрицы проиходить в функциях инициализации фигур
    for (int i = 0; i < FSIZE; i++)
       for (int j = 0; j < FSIZE; j++) 
         f->figur[i][j] = 0; 
    int fig = rand() % 7;    
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
    
}

void initFigureNow(figura *fnow){
    fnow->x = START_X;
    fnow->y = START_Y;
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

void initGameField(game_stats_t *gameBakend){
    for (int i = 0; i < BOARD_N; i++)
        for (int j = 0; j < BOARD_M; j++)
            gameBakend->gameField[i][j] = 0;
}

// TO DO переименовать метод в initGameField
void stats_init(game_stats_t *gameBakend) { 
  gameBakend->level = 1;
  gameBakend->score = 0;
  gameBakend->speed = 1;
  gameBakend->lives = 99;
  gameBakend->won = FALSE;
  //gameBakend->fnow = NULL;
  //gameBakend->fnext = NULL;
  //initFigure(gameBakend->fnext);
  initGameField(gameBakend);
}

//запомним и зафиксируем фигуру на игровом поле
void figuraGamefield(game_stats_t *gb, figura *f){
    // тут под новую структуру меняю 
    for(int y = f->y, k = 0; y <  f->y+f->n && k < f->n; y++, k++)
        for(int x = f->x, l = 0; x < f->x+f->m && l < f->m; x++, l++)
            if(f->figur[k][l]) gb->gameField[y][x] = f->typeFigure;

}


void iniFigura_Q(figura *f){
    f->n = 2;
    f->m = 2;
    f->figur[0][0] = 1; 
    f->figur[0][1] = 1;
    f->figur[1][0] = 1;
    f->figur[1][1] = 1;
        f->typeFigure = FIGURE_Q;  
}
void iniFigura_I(figura *f){
    f->n = 4;
    f->m = 1;
    f->figur[0][0] = 1; 
    f->figur[1][0] = 1;
    f->figur[2][0] = 1;
    f->figur[3][0] = 1;
        f->typeFigure = FIGURE_I;
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
        f->typeFigure =  FIGURE_S;
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
        f->typeFigure =  FIGURE_Z;
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
        f->typeFigure =  FIGURE_L;
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
        f->typeFigure =  FIGURE_J;
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
        f->typeFigure =  FIGURE_T;
}
