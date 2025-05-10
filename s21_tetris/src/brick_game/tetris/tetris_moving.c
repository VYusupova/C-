#include "tetris.h"

int collisionDown(figura *f, game_stats_t *gb) {
  int result = SUCCESS;
  if ((f->y + f->n) >= (BOARD_N)) result = ERROR;
  else 
  if (collisionGameField(gb,1,0)) result = ERROR;
  return result;
}

// проверяем что фигура появилась и не упирается вниз
int collisionUp(figura *f, game_stats_t *gb){
 if (f->y == START_Y && collisionDown(f,gb)) return ERROR;
 return SUCCESS;
}

 // f->n & BOARD_N - строк 
 // t->m & BOARD_M - столбцов
int collisionLeft(figura *f, game_stats_t *gb) {
  int result = SUCCESS;
  if ((f->x) <= 0) result = ERROR;
  else 
  if (collisionGameField(gb,0,-1)) result = ERROR;
  return result;
}

int collisionRight(figura *f, game_stats_t *gb) {
   int result = SUCCESS;
   if (f->x + f->m >= (BOARD_M)) result = ERROR;
   if (collisionGameField(gb,0,1)) result = ERROR;
  return result;
}

int collisionGameField(game_stats_t *gb, int down, int left) {
  int result = SUCCESS;
  for (int y = gb->fnow->y+down, k = 0; y < BOARD_N && k <  gb->fnow->n; y++, k++)
    for (int j =  gb->fnow->x+left, l = 0; j < BOARD_M && l <  gb->fnow->m; j++, l++)
      if (gb->gameField[y][j] != 0 &&  gb->fnow->figur[k][l] == 1) result = ERROR;
   return result;
}

void rotateFigure(figura *f, game_stats_t *gb){
    if (f->typeFigure != FIGURE_Q) 
    {
        //задаем новую фигуру 
        figura new;
        new.x = f->x;
        new.y = f->y;
        new.n = f->m;
        new.m = f->n;
        new.typeFigure = f->typeFigure;
      for (int i = 0; i < FSIZE; i++)
       for (int j = 0; j < FSIZE; j++) 
         new.figur[i][j] = 0;
        for(int i = 0; i < new.n; i++)
            for (int j = 0; j < new.m; j++)
               new.figur[i][j] = f->figur[j][new.n-1-i];
        //showFigure(&new); 

// // добавить условие что если новая позиция фигуры не выходит за рамки игрового поля
// // и не сталкивается с уже занятыми на поле ячейками (т.е другими  фигурами) выполнить поворот
        //  переписываем в старую фигуру новую
        if (!collisionRight(f, gb) && !collisionLeft(f, gb) &&
       !collisionDown(f, gb)){
        for(int y = 0; y < new.n; y++)
            for (int x = 0; x < new.m; x++)
                f->figur[y][x] =new.figur[y][x];
        f->m = new.m;
        f->n = new.n;}
    }
}
