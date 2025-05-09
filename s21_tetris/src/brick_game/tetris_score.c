#include "tetris.h"

void score(game_stats_t *gb) {
  int s = 0; 
  int lines = 0;
  for(int y = FIELD_N-1; y >= 0; y--){
	s = 0;
        for(int x = FIELD_M-1; x >= 0; x--)
            if(gb->gameField[y][x] == 0) break;
            else {s++;}
      if (s == 10){ 
      	lines++;
        shiftField(gb,y); 
        y++;     
      }
      }
  if (lines == 4) gb->score += 1500;
  if (lines == 3) gb->score += 700;
  if (lines == 2) gb->score += 300;
  if (lines == 1) gb->score += 100;
}

void shiftField(game_stats_t *gb, int y){	
	for(int y1 = y; y1 >=1; y1--)
		for(int x = 0; x < FIELD_M; x++)
		gb->gameField[y1][x] = gb->gameField[y1-1][x];
	for(int x = 0; x < FIELD_M; x++)
		gb->gameField[0][x] = 0;
		
}

