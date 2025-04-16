#include "frog_backend.h"

int lvlproc(board_t *map, game_stats_t *stats) {
  timeout(INITIAL_TIMEOUT - stats->speed * 15);

  // char levelname[LEVELNAME_MAX + 1] = { 0 };
  int rc = SUCCESS;
  // MVPRINTW(0, 0, "An error occured openning level file!");
  /*sprintf(levelname, LEVEL_DIR"%d.txt", stats->level);

  FILE *level = fopen(levelname, "r");

  if (level)
  {
      for (int i = 0; i < ROWS_MAP && !rc; i++)
      {
          if (fgets(map->ways[i], COLS_MAP + 2, level) == NULL)
              rc = ERROR;
          else
              map->ways[i][strcspn(map->ways[i], "\n")] = '\0';
      }
      fclose(level);
  }
  else
      rc = ERROR;
  */

  return rc;
}

void add_proggress(board_t *map) {
  int position = 0;

  for (; map->finish[position] == '0'; position++);

  for (int progress_cnt = BOARD_M / 5; progress_cnt > 0; progress_cnt--)
    map->finish[position++] = '0';
}

bool check_finish_state(player_pos *frog, board_t *map) {
  bool rc = FALSE;

  if (frog->y == 1) rc = TRUE;

  return rc;
}



void frogpos_init(player_pos *frog) {
  frog->x = START_X;
  frog->y = START_Y;
}

// void fill_finish(char *finish_line) {
//   for (int i = 0; i < BOARD_M; i++) finish_line[i] = '$';

//   finish_line[BOARD_M] = '\0';
// }



