#include "tetris.h"

void score(game_stats_t *gb) {
  		      int s = 0;
      for(int y = BOARD_N; y <= 0; y--){
		s = 0;
        for(int x = BOARD_M; x <= 0; x--)
            if(gb->gameField[y][x] == 0) break;
            else {s++;}
      if (s == 10) gb->score +=100;
      }
}

