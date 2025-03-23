#include "tetris.h"

void initFigure(figura *f){

    f->x = START_X;
    f->y = START_Y;
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++) 
        f->figur[i][j] = 0;

    int fig = rand() % 7;    
    switch (fig){
      // потом можно вынести в отдельные функции инициализации
    case 1 :    //  FIGURE_Q
        f->figur[1][1] = 1; 
        f->figur[1][2] = 1;
        f->figur[2][1] = 1;
        f->figur[2][2] = 1;
        f->typeFigure = FIGURE_Q;  
        break;
    case 2 : 
        initialFigura_I(f);
        break;
    case 3 : // FIGURE_S
        f->figur[2][1] = 1;
        f->figur[1][2] = 1;
        f->figur[2][2] = 1;
        f->figur[3][1] = 1;
        f->typeFigure =  FIGURE_S;
        break;
    case 4 : // FIGURE_Z
        f->figur[1][1] = 1;
        f->figur[1][2] = 1;
        f->figur[2][2] = 1;
        f->figur[2][3] = 1;
        f->typeFigure =  FIGURE_Z;
        break;     
    case 5 : // FIGURE_L
        f->figur[0][1] = 1;
        f->figur[1][1] = 1;
        f->figur[2][1] = 1;
        f->figur[2][2] = 1;
        f->typeFigure =  FIGURE_L;
        break; 
     case 6 : // FIGURE_J
        f->figur[0][2] = 1;
        f->figur[1][2] = 1;
        f->figur[2][1] = 1;
        f->figur[2][2] = 1;
        f->typeFigure =  FIGURE_J;
        break;      
    default : // FIGURE_T
        f->figur[0][0] = 1;
        f->figur[0][1] = 1;
        f->figur[0][2] = 1;
        f->figur[1][1] = 1;
        f->typeFigure =  FIGURE_T;
        break;       
    }
}

void rotateFigure(figura *f){
    int tmp[4][4] = {0};
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++) 
        tmp[i][j] = f->figur[i][j];
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++) 
        f->figur[j][i] = tmp[4-i-1][j];
}
void initGameField(game_stats_t *gameBakend){
    for (int i = 0; i < BOARD_N; i++)
        for (int j = 0; j < BOARD_M; j++)
            gameBakend->gameField[i][j] = 0;
    //gameBakend->gameField[5][5] = 3;

}

void stats_init(game_stats_t *gameBakend) {
  gameBakend->level = 1;
  gameBakend->score = 0;
  gameBakend->speed = 1;
  gameBakend->lives = 99;
  gameBakend->won = FALSE;
  initGameField(gameBakend);
}

void figuraGamefield(game_stats_t *gb, figura *f){
    for(int i = f->y, k = 0; i <  BOARD_N && k < 4; i++, k++)
        for(int j = f->x, l = 0; j < BOARD_M && l < 4; j++, l++)
            if(f->figur[k][l]) gb->gameField[i][j] = f->typeFigure;

}

void initialFigura_I(figura *f){
        f->figur[0][3] = 1;
        f->figur[1][3] = 1;
        f->figur[2][3] = 1;
        f->figur[3][3] = 1;
        f->typeFigure = FIGURE_I;
}