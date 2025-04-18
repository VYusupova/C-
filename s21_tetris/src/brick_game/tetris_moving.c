#include "tetris.h"



int collisionDown(figura *f, game_stats_t *gb) {
  int result = SUCCESS;
  if (f->y + f->n >= BOARD_N) result = ERROR;
  else 
  if (collisionGameField(f,gb)) result = ERROR;
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
  if ((f->x) <= 1) result = ERROR;
//   
//   // Если крайняя левая позиция фигуры слева встретит игровое поле занятое
//   // фигурой, тут нужен цикл проверить для I
//   for(int y = 0 ; y < FSIZE; y++)
//     if (gb->gameField[f->y+y][positonX-1]) result = ERROR;
// if (check(f, gb)) result = ERROR;
  return result;
}

int collisionRight(figura *f, game_stats_t *gb) {
//  int positonX = -1;
   int result = SUCCESS;
   if (f->x + f->m-1 >= BOARD_M) result = ERROR;
//   for(int y = 0 ; y < FSIZE; y++)
//     if (gb->gameField[f->y+y][positonX+1]) result = ERROR;
// if (check(f, gb)) result = ERROR;
  return result;
}

int collisionGameField(figura *f, game_stats_t *gb) {
  int result = SUCCESS;
  for (int y = f->y + 1, k = 0; y < BOARD_N && k < f->n; y++, k++)
    for (int j = f->x, l = 0; j < BOARD_M && l < f->m; j++, l++)
      if (gb->gameField[y][j] != 0 && f->figur[k][l] == 1) result = ERROR;
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
