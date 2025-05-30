// TO DO #1 Максимальное количество очков должно изменяться во время игры, если пользователь превышает текущий показатель максимального количества очков во время игры.
/* логика игры тетрис - подсчет очков и повышение уровня 
shiftField - Уничтожение заполненных линий (Часть 1);
score - подсчет очков (Часть 2);
writeScore & readScore - хранение максимального количества очков(Часть 2)*/

#ifndef TETRIS_SCORE
#define TETRIS_SCORE

#include "../../inc/tetris.h"


static void levelUP(GameInfo_t *game){
 if(game->level == 10) return;
 int level = game->score / 600 ;
 if (level > game->level)  {
	 game->level = level;
	 game->speed = game->speed*0.9;
		 }
}

static void shiftField(GameInfo_t *game, int y){	
	for(int y1 = y; y1 >=1; y1--)
		for(int x = 0; x < FIELD_M; x++)
		game->field[y1][x] = game->field[y1-1][x];
	for(int x = 0; x < FIELD_M; x++)
		game->field[0][x] = 0;
		
}



void score(GameInfo_t *game) {

  int lines = 0;
  for(int y = FIELD_N-1; y >= 0; y--){
	int cell = 0;
        for(int x = FIELD_M-1; x >= 0; x--){
            if(game->field[y][x] == 0) break;
            else cell++;
	}	
      if (cell == 10){ 
      	lines++;
        shiftField(game,y); 
        y++;     
      }
      }
  if (lines == 4) game->score += 1500;
  if (lines == 3) game->score += 700;
  if (lines == 2) game->score += 300;
  if (lines == 1) game->score += 100;
  levelUP(game);
}


void writeScore(const GameInfo_t *game) {
  if (game->high_score < game->score){
      FILE *file = fopen(MAX_SCORE, "w");
    if (file == NULL) {
        perror("Ошибка при открытии файла");
    }
    else {
    fprintf(file, "%d", game->score);
    fclose(file);}
  }
}

int readScore(void) {
   FILE *file = fopen(MAX_SCORE, "r");
    if (file == NULL) {
        //perror("Ошибка при открытии файла");
        return 0;
    }
    else {

    int maxScore;
    fscanf(file, "%d", &maxScore);
    fclose(file);
    return maxScore;}
}


#endif
