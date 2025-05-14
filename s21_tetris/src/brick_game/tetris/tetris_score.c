// TO DO #1 Максимальное количество очков должно изменяться во время игры, если пользователь превышает текущий показатель максимального количества очков во время игры.
/* логика игры тетрис - подсчет очков и повышение уровня 
shiftField - Уничтожение заполненных линий (Часть 1);
score - подсчет очков (Часть 2);
writeScore & readScore - хранение максимального количества очков(Часть 2)*/

#ifndef TETRIS_SCORE
#define TETRIS_SCORE

#include "tetris.h"

void score(GameInfo_t *game) {
  int cell = 0; 
  int lines = 0;
  for(int y = FIELD_N-1; y >= 0; y--){
	cell = 0;
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
}

void shiftField(GameInfo_t *gb, int y){	
	for(int y1 = y; y1 >=1; y1--)
		for(int x = 0; x < FIELD_M; x++)
		gb->field[y1][x] = gb->field[y1-1][x];
	for(int x = 0; x < FIELD_M; x++)
		gb->field[0][x] = 0;
		
}

void writeScore(GameInfo_t *stats) {
  if (stats->high_score < stats->score){
      FILE *file = fopen(MAX_SCORE, "w");
    if (file == NULL) {
        perror("Ошибка при открытии файла");
    }
    fprintf(file, "%d", stats->score);
    fclose(file);
  }
}

int readScore(void) {
   FILE *file = fopen(MAX_SCORE, "r");
    if (file == NULL) {
        perror("Ошибка при открытии файла");
        return 0;
    }

    int maxScore;
    fscanf(file, "%d", &maxScore);
    fclose(file);
    return maxScore;
}

// TO DO #2 Добавь в игру механику уровней. Каждый раз, когда игрок набирает 600 очков, уровень увеличивается на 1. Повышение уровня увеличивает скорость движения фигур. 
//Максимальное количество уровней — 10.
void levelUP(GameInfo_t *game){
 if(game->level == 10) return;
 if(game->score % 600 == 0) {
	 game->level = game->score % 600;
	 game->speed = game->speed - 10*game->level;
		 }
}

#endif
