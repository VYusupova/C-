#include "frog_frontend.h"

#define MESSAGE_PRESS "Press"  // приветствие
#define MESSAGE_ENTER "ENTER"  // приветствие
#define MESSAGE_TO "TO"        // приветствие
#define MESSAGE_START "Start"  // приветствие

void initColors() {
  if (!has_colors()) {
    endwin();
    printf("COLORS NOT SUPPORTED");
  }
  // bkgdset(COLOR_PAIR()); включи что бы посмотреть эелменты которые надо
  // убрать COLOR_MAGENTA - милиновый COLOR_CYAN
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
  print_rectangle(0, BOARD_N + 1, 0, BOARD_M + 1);  // отрисовка игрового поля
  print_rectangle(0, BOARD_N + 1, BOARD_M + 2,
                  BOARD_M + HUD_WIDTH);  // отрисовка информационного поля
  print_rectangle(R_NEXT, R_NEXT_H, BOARD_M + 3,
                  BOARD_M + HUD_WIDTH - 1);  // отрисовка поля под новую фигуру

  MVPRINTW(R_LEV, BOARD_M + SHIFT_MESSAGE, "LEVEL");
  MVPRINTW(R_SCORE, BOARD_M + SHIFT_MESSAGE, "SCORE");
  MVPRINTW(R_SPEED, BOARD_M + SHIFT_MESSAGE, "SPEED");
  MVPRINTW(R_LIVES, BOARD_M + SHIFT_MESSAGE, "LIVES");
  showIntro();
}

void showIntro(void) {
  MVPRINTW(BOARD_N / 2, MAP_PADDING, MESSAGE_PRESS);
  MVPRINTW(BOARD_N / 2 + 1, MAP_PADDING, MESSAGE_ENTER);
  MVPRINTW(BOARD_N / 2 + 3, MAP_PADDING, MESSAGE_TO);
  MVPRINTW(BOARD_N / 2 + 3, MAP_PADDING, MESSAGE_START);
  //    clear();
  //  MVPRINTW(0, 0, "An error occured openning level file!");
  //  MVPRINTW(2, 0, "Please check ./tests/ directory.");
  //  MVPRINTW(3, 0, "There should be 5 level files named level_(1-5).txt.");
  //  MVPRINTW(4, 0, "Also try to open the game nearby ./tests/ directory.");
  //  MVPRINTW(6, 0, "Press any key to exit.");
}

void hideIntro(void) {
  bkgdset(COLOR_PAIR(FIGURE_HIDE));
  MVPRINTW(BOARD_N / 2, MAP_PADDING, HIDE_INTRO);
  MVPRINTW(BOARD_N / 2 + 1, MAP_PADDING, HIDE_INTRO);
  MVPRINTW(BOARD_N / 2 + 2, MAP_PADDING, HIDE_INTRO);
  MVPRINTW(BOARD_N / 2 + 3, MAP_PADDING, HIDE_INTRO);
}

void gameOver(void) {
  MVPRINTW(BOARD_N / 2, MAP_PADDING, OVER_MESSAGE1);
  MVPRINTW(BOARD_N / 2 + 1, MAP_PADDING, OVER_MESSAGE2);
}

// отрисовка прямоугольника с координатми
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  // ACS_BLOCK

  MVADDCH(top_y, left_x, ACS_ULCORNER);

  int i = left_x + 1;

  for (; i < right_x; i++) MVADDCH(top_y, i, ACS_HLINE);
  MVADDCH(top_y, i, ACS_URCORNER);

  for (i = top_y + 1; i < bottom_y; i++) {
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

// void print_finished(board_t *game) {
//   for (int i = 0; i < BOARD_M; i++) {
//     if (game->finish[i] == '0')
//       MVADDCH(1, i + 1, ACS_BLOCK);
//     else
//       MVADDCH(1, i + 1, ' ');
//   }
// }
// void print_banner(game_stats_t *stats) {
//  banner_t banner;

//  memset(banner.matrix, 0, (BANNER_N + 1) * (BANNER_M + 1));

//  clear();

//  if (!(read_banner(stats, &banner))) {
//    for (int i = 0; i < BANNER_N; i++)
//      for (int j = 0; j < BANNER_M; j++)
//        if (banner.matrix[i][j] == '#')
//          MVADDCH(i, j, ACS_BLOCK);
//        else
//          MVADDCH(i, j, ' ');
//    refresh();

//  }
//}

void writeScore(game_stats_t *stats) {
  FILE *file = fopen(MAX_SCORE, "w");
  ;

  if (file) {
    // WRITE

    fclose(file);
  }
}

void printFigure(figura *f) {
  for (int i = 0; i < f->n; i++)
    for (int j = 0; j < f->m; j++) {
      if (f->figur[i][j] == 1) PRINT(f->x + j, f->y + i);
    }
}

void hideFigure(figura *f) {
  bkgdset(COLOR_PAIR(FIGURE_HIDE));
  printFigure(f);
}

void showFigure(figura *f) {
  bkgdset(COLOR_PAIR(f->typeFigure));
  printFigure(f);
}
void refreshFigure(figura *f, int dx, int dy) {
  hideFigure(f);
  f->y += dy;
  f->x += dx;
  showFigure(f);
}

void printGameField(game_stats_t *gameBakend) {
  for (int i = 0; i < BOARD_N; i++)
    for (int j = 0; j < BOARD_M; j++) {
      if (gameBakend->gameField[i][j]) {
        bkgdset(COLOR_PAIR(gameBakend->gameField[i][j]));
        PRINT(j, i);
        bkgdset(COLOR_PAIR(0));
      }
    }
}
void refreshGameField(game_stats_t *gameBakend) {
  bkgdset(COLOR_PAIR(0));
  for (int i = 0; i < BOARD_N; i++)
    for (int j = 0; j < BOARD_M; j++) {
      if (gameBakend->gameField[i][j]) {
        PRINT(j, i);
      }
    }
  printGameField(gameBakend);
}
