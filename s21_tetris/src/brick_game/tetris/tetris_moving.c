#include "../../../inc/tetris.h"

 // f->n & FIELD_N - строк 
 // t->m & FIELD_M - столбцов
static int collisionGameField(GameInfo_t *game, int down, int left) {
  int result = SUCCESS;
  for (int y = game->fnow->y+down, k = 0; y < FIELD_N && k <  game->fnow->n; y++, k++)
    for (int j =  game->fnow->x+left, l = 0; j < FIELD_M && l <  game->fnow->m; j++, l++)
      if (game->field[y][j] != 0 &&  game->fnow->figur[k][l] == 1) result = ERROR;
   return result;
}

int collisionDown(const figura *f, GameInfo_t *game) {
  int result = SUCCESS;
  if ((f->y + f->n) >= (FIELD_N)) result = ERROR;
  else 
  if (collisionGameField(game,1,0)) result = ERROR;
  return result;
}

int collisionUp(const figura *f){ //to do del? 
 if (f->y <= START_Y) return ERROR;  // TO DO 
 return SUCCESS;
}

int collisionLeft(const figura *f, GameInfo_t *game) {
  int result = SUCCESS;
  if ((f->x) <= 0) result = ERROR;
  else 
  if (collisionGameField(game,0,-1)) result = ERROR;
  return result;
}

int collisionRight(const figura *f, GameInfo_t *game) {
   int result = SUCCESS;
   if (f->x + f->m >= (FIELD_M)) result = ERROR;
   if (collisionGameField(game,0,1)) result = ERROR;
  return result;
}



void rotateFigure(figura *f, GameInfo_t *game){
        //задаем новую фигуру 
        figura new;
        new.x = f->x;
        new.y = f->y;
        new.n = f->m;
        new.m = f->n;
        //if (new.n == 1 ) new.y +=2;
        new.typeFigure = f->typeFigure;
        new.figur = create(FSIZE,FSIZE);
        for(int i = 0; i < new.n; i++)
            for (int j = 0; j < new.m; j++)
               new.figur[i][j] = f->figur[j][new.n-1-i];


// // добавить условие что если новая позиция фигуры не выходит за рамки игрового поля
// // и не сталкивается с уже занятыми на поле ячейками (т.е другими  фигурами) выполнить поворот
        //  переписываем в старую фигуру новую
//        if (f->x + f->m >= (FIELD_M)) { new.x -=1;}
        if (!collisionRight(&new, game) && !collisionLeft(&new, game) &&
       !collisionDown(&new, game)){
        for(int y = 0; y < new.n; y++)
            for (int x = 0; x < new.m; x++)
                f->figur[y][x] =new.figur[y][x];
        f->m = new.m;
        f->n = new.n;
        f->x = new.x;
        f->y = new.y;}
    tetFree(new.figur, FSIZE, FSIZE);
}
