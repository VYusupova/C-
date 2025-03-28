#include "tetris.h"
// TO DO # 0 в отдельные методы вынесены операции инициализации фигуры по типу
void initFigure(figura *f){

    f->x = START_X;
    f->y = START_Y;
    // TO DO в идеале надо сделать так что бы матрица выделялась динамически
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++) 
        f->figur[i][j] = 0;

    int fig = rand() % 7;    
    switch (fig){
    case FIGURE_Q :    //  FIGURE_Q
        iniFigura_Q(f);
        break;
    case FIGURE_I : 
        iniFigura_I(f);
        break;
    case FIGURE_S : // FIGURE_S
        iniFigura_S(f);
        break;
    case FIGURE_Z : // FIGURE_Z
        iniFigura_Z(f);
        break;     
    case FIGURE_L : // FIGURE_L
        iniFigura_L(f);
        break; 
     case FIGURE_J : // 
        iniFigura_J(f);
        break;      
    default : // FIGURE_T
        iniFigura_J(f);
        break;       
    }
}

void rotateFigure(figura *f){
    int tmp[4][4] = {0};
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++) 
        tmp[i][j] = f->figur[i][j];
// добавить условие что если новая позиция фигуры не выходит за рамки игрового поля
// и не сталкивается с уже занятыми на поле ячейками (т.е другими  фигурами) выполнить поворот
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

// TO DO переименовать метод в initGameField
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

//Добавленный код без проверки 
void iniFigura_Q(figura *f){
        f->figur[1][1] = 1; 
        f->figur[1][2] = 1;
        f->figur[2][1] = 1;
        f->figur[2][2] = 1;
        f->typeFigure = FIGURE_Q;  
}

void iniFigura_I(figura *f){
        f->figur[0][3] = 1;
        f->figur[1][3] = 1;
        f->figur[2][3] = 1;
        f->figur[3][3] = 1;
        f->typeFigure = FIGURE_I;
}
void iniFigura_S(figura *f){
        f->figur[2][1] = 1;
        f->figur[1][2] = 1;
        f->figur[2][2] = 1;
        f->figur[3][1] = 1;
        f->typeFigure =  FIGURE_S;
}
void iniFigura_Z(figura *f){
        f->figur[1][1] = 1;
        f->figur[1][2] = 1;
        f->figur[2][2] = 1;
        f->figur[2][3] = 1;
        f->typeFigure =  FIGURE_Z;
}
void iniFigura_L(figura *f){
        f->figur[0][1] = 1;
        f->figur[1][1] = 1;
        f->figur[2][1] = 1;
        f->figur[2][2] = 1;
        f->typeFigure =  FIGURE_L;
}
void iniFigura_J(figura *f){
        f->figur[0][2] = 1;
        f->figur[1][2] = 1;
        f->figur[2][1] = 1;
        f->figur[2][2] = 1;
        f->typeFigure =  FIGURE_J;
}
void iniFigura_T(figura *f){
        f->figur[0][0] = 1;
        f->figur[0][1] = 1;
        f->figur[0][2] = 1;
        f->figur[1][1] = 1;
        f->typeFigure =  FIGURE_T;
}
