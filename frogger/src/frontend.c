#include "frog_frontend.h"

void initColors() {
  if (!has_colors()) {
    endwin();
    MVPRINTW(BOARD_N/2, BOARD_N/2, "COLORS NOT SUPPORTED");
  }
 // bkgdset(COLOR_PAIR()); включи что бы посмотреть эелменты которые надо убрать 
 // COLOR_MAGENTA - милиновый
 // COLOR_CYAN
  start_color();
  init_pair(FIGURE_HIDE, COLOR_BLACK, COLOR_BLACK);
  init_pair(FIGURE_Q, COLOR_BLACK, COLOR_YELLOW);
  init_pair(FIGURE_I, COLOR_BLACK, COLOR_CYAN);
  init_pair(FIGURE_S, COLOR_BLACK, COLOR_RED);
  init_pair(FIGURE_Z, COLOR_BLACK, COLOR_GREEN);
  init_pair(FIGURE_L, COLOR_YELLOW, COLOR_RED); 
  init_pair(FIGURE_J, COLOR_BLACK, COLOR_MAGENTA); 
  init_pair(FIGURE_T, COLOR_YELLOW, COLOR_CYAN); 
}

void print_overlay(void) {
  print_rectangle(0, BOARD_N + 1, 0, BOARD_M + 1); // отрисовка игрового поля
  print_rectangle(0, BOARD_N + 1, BOARD_M + 2, BOARD_M + HUD_WIDTH); // отрисовка информационного поля
  print_rectangle(R_NEXT, 7, BOARD_M + 3, BOARD_M + HUD_WIDTH);

  
  MVPRINTW(R_LEV, BOARD_M + SHIFT_MESSAGE, "LEVEL");
  MVPRINTW(R_SCORE, BOARD_M + SHIFT_MESSAGE, "SCORE");
  MVPRINTW(R_SPEED, BOARD_M + SHIFT_MESSAGE,"SPEED");  
  MVPRINTW(R_LIVES, BOARD_M + SHIFT_MESSAGE, "LIVES");
  MVPRINTW(BOARD_N/2, 0, INTRO_MESSAGE);
}

void hideIntro(void){
bkgdset(COLOR_PAIR(FIGURE_HIDE));
MVPRINTW(BOARD_N/2, 0, HIDE_INTRO);
}

void print_levelerror(void) {
  clear();
  MVPRINTW(0, 0, "An error occured openning level file!");
  MVPRINTW(2, 0, "Please check ./tests/ directory.");
  MVPRINTW(3, 0, "There should be 5 level files named level_(1-5).txt.");
  MVPRINTW(4, 0, "Also try to open the game nearby ./tests/ directory.");
  MVPRINTW(6, 0, "Press any key to exit.");
}

// отрисовка прямоугольника с координатми
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  MVADDCH(top_y, left_x, ACS_ULCORNER);

  int i = left_x + 1;

  for (; i < right_x; i++) MVADDCH(top_y, i, ACS_HLINE);
  MVADDCH(top_y, i, ACS_URCORNER);

  for (int i = top_y + 1; i < bottom_y; i++) {
    MVADDCH(i, left_x, ACS_VLINE);
    MVADDCH(i, right_x, ACS_VLINE);
  }

  MVADDCH(bottom_y, left_x, ACS_LLCORNER);
  i = left_x + 1;
  for (; i < right_x; i++) MVADDCH(bottom_y, i, ACS_HLINE);
  MVADDCH(bottom_y, i, ACS_LRCORNER);
}
// отрисовка уровня и очков
void print_stats(game_stats_t *stats) {
  bkgdset(COLOR_PAIR(FIGURE_HIDE));
  MVPRINTW(R_NEXT, BOARD_M + SHIFT_MESSAGE, "NEXT");
  MVPRINTW(R_LEV + 1, BOARD_M + SHIFT_MESSAGE, "%d", stats->level);
  MVPRINTW(R_SCORE + 1, BOARD_M + SHIFT_MESSAGE, "%d", stats->score);
  MVPRINTW(R_SPEED + 1, BOARD_M + SHIFT_MESSAGE, "%d", stats->speed);
  MVPRINTW(R_LIVES + 1, BOARD_M + SHIFT_MESSAGE, "%d", stats->lives);
}

void print_board(board_t *game, player_pos *frog) {
  // print_cars(game);
  PRINT(frog->x, frog->y);
}

// отрисвка чего то
void print_cars(board_t *game) {
  for (int i = MAP_PADDING + 1; i < BOARD_N - MAP_PADDING + 1; i++) {
    if (i % 2 == (MAP_PADDING + 1) % 2) {
      for (int j = 1; j < BOARD_M + 1; j++) MVADDCH(i, j, ACS_BLOCK);
    } else {
      for (int j = 1; j < BOARD_M + 1; j++) {
        if (game->ways[i - MAP_PADDING - 1][j - 1] == '0')
          MVADDCH(i, j, ' ');
        else
          MVADDCH(i, j, ']');
      }
    }
  }
}

// void print_finished(board_t *game) {
//   for (int i = 0; i < BOARD_M; i++) {
//     if (game->finish[i] == '0')
//       MVADDCH(1, i + 1, ACS_BLOCK);
//     else
//       MVADDCH(1, i + 1, ' ');
//   }
// }
void print_banner(game_stats_t *stats) {
  banner_t banner;

  memset(banner.matrix, 0, (BANNER_N + 1) * (BANNER_M + 1));

  clear();

  if (!(read_banner(stats, &banner))) {
    for (int i = 0; i < BANNER_N; i++)
      for (int j = 0; j < BANNER_M; j++)
        if (banner.matrix[i][j] == '#')
          MVADDCH(i, j, ACS_BLOCK);
        else
          MVADDCH(i, j, ' ');
    refresh();
    napms(2000);
  }
}

int read_banner(game_stats_t *stats, banner_t *banner) {
  int rc = SUCCESS;
  FILE *file = NULL;

  if (stats->lives)
    file = fopen(YOU_WON, "r");
  else
    file = fopen(YOU_LOSE, "r");

  if (file) {
    for (int i = 0; i < BANNER_N - 1 && !rc; i++) {
      if (fgets(banner->matrix[i], BANNER_M + 2, file) == NULL)
        rc = ERROR;
      else
        banner->matrix[i][strcspn(banner->matrix[i], "\n")] = '\0';
    }

    fclose(file);
  } else
    rc = ERROR;

  return rc;
}


void printFigure(figura *position){
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      if ( position->figur[i][j] == 1)  PRINT(position->x+j, position->y+i);
  }
}

void hideFigure(figura *position){ 
   bkgdset(COLOR_PAIR(FIGURE_HIDE));
   printFigure(position);
}

void showFigure(figura *position){ 
  bkgdset(COLOR_PAIR(position->typeFigure));
  printFigure(position);
}

void printGameField(game_stats_t *gameBakend){
  for (int i = 0; i < BOARD_N; i++)
    for (int j = 0; j < BOARD_M; j++) {
      if (gameBakend->gameField[i][j])  {
        bkgdset(COLOR_PAIR(gameBakend->gameField[i][j]));
        PRINT(j, i);
        bkgdset(COLOR_PAIR(0));
      }
  }
}

void refreshFigure(figura *f, int dx, int dy){
    hideFigure(f);
    f->y += dy;
    f->x += dx;
    showFigure(f);
}