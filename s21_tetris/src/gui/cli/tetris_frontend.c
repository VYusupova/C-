#include "frontend.h"



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
  init_pair(MASSEGE, COLOR_WHITE, COLOR_BLACK);
}

void showIntro(void) {
  int start = BOARD_N / 2 - 6;
  int Y = 4;
   MVPRINTW(start, Y, "Press");
   MVPRINTW(start+1, Y,"ENTER - start");
  // MVPRINTW(start+2, Y, "to start");
//   MVPRINTW(start+3,  Y, " ");
   MVPRINTW(start+5,  Y, "USED:");
   MVPRINTW(start+6,  Y, "P     - pause");
   MVPRINTW(start+7,  Y, "SPACE - rotate ");
   MVPRINTW(start+8,  Y, "ESC   - exit");
   MVPRINTW(start+9,  Y, "DOWN");
   MVPRINTW(start+10, Y, "LEFT");
   MVPRINTW(start+11, Y, "RIGHT");
}

void gameOver(void) {
  MVPRINTW(BOARD_N / 2, BOARD_M/2, "GAME");
  MVPRINTW(BOARD_N / 2 + 1,  BOARD_M/2, "OVER");
  MVPRINTW(BOARD_N / 2 + 3, BOARD_M/2-1, "Press");
  MVPRINTW(BOARD_N / 2 + 4, BOARD_M/2-1,"ENTER");
  MVPRINTW(BOARD_N / 2 + 5, BOARD_M/2, "to");
  MVPRINTW(BOARD_N / 2 + 5, BOARD_M/2-1, "start");
}

// отрисовка уровня и очков
void print_stats(GameInfo_t *game) {
  bkgdset(COLOR_PAIR(MASSEGE));
  
  MVPRINTW(R_NEXT, BOARD_M + SHIFT_MESSAGE, "NEXT");
  if (game->pause) MVPRINTW(R_NEXT+6, BOARD_M + SHIFT_MESSAGE, "  PAUSE");
  else MVPRINTW(R_NEXT+6, BOARD_M + SHIFT_MESSAGE, "       ");
  MVPRINTW(R_NEXT+9, BOARD_M + SHIFT_MESSAGE, "%d", game->level);
  MVPRINTW(R_NEXT+11, BOARD_M + SHIFT_MESSAGE, "%d", game->score);
  MVPRINTW(R_NEXT+13, BOARD_M + SHIFT_MESSAGE, "%d", game->speed);
  if (game->score > game->high_score) MVPRINTW(R_NEXT+17, BOARD_M + SHIFT_MESSAGE, "%d", game->score);
  else MVPRINTW(R_NEXT+17, BOARD_M + SHIFT_MESSAGE, "%d", game->high_score);
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


void print_overlay(void) {
  print_rectangle(0, BOARD_N + 1, 0, BOARD_M + 2);  // отрисовка игрового поля
  //print_rectangle(0, BOARD_N + 1, BOARD_M + 3,
  //                BOARD_M + HUD_WIDTH);  // отрисовка информационного поля
  //print_rectangle(R_NEXT, R_NEXT_H, BOARD_M + 4,
    //              BOARD_M + HUD_WIDTH - 1);  // отрисовка поля под новую фигуру

  MVPRINTW(R_NEXT+8,  BOARD_M + SHIFT_MESSAGE, "LEVEL");
  MVPRINTW(R_NEXT+10, BOARD_M + SHIFT_MESSAGE, "SCORE");
  MVPRINTW(R_NEXT+12, BOARD_M + SHIFT_MESSAGE, "SPEED");
  MVPRINTW(R_NEXT+15, BOARD_M + SHIFT_MESSAGE, "MAX SCORE");
  MVPRINTW(R_NEXT+16, BOARD_M + SHIFT_MESSAGE, "SCORE");
  showIntro();
}

void printPause(void) {
  bkgdset(COLOR_PAIR(MASSEGE));
  MVPRINTW(BOARD_N/2, BOARD_M/2, "PAUSE");
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


void printFigure(figura *f) {
  for (int i = 1; i < f->n+1; i++)
    for (int j = 1; j < f->m+1; j++) {
      if (f->figur[i-1][j-1] == 1) PRINT((f->x*2 + j*2), f->y + i);
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

void printGameField(GameInfo_t *gameBakend) {
  for (int i = 1; i < BOARD_N+1; i++)
    for (int j = 1; j < FIELD_M+1; j++) {
      if (gameBakend->field[i-1][j-1]) {
        bkgdset(COLOR_PAIR(gameBakend->field[i-1][j-1]));
        PRINT(j*2, i);
      }
    }
}

void refreshGameField(GameInfo_t *gameBakend) {
  bkgdset(COLOR_PAIR(0));
  for (int i = 1; i < BOARD_N+1; i++)
    for (int j = 1; j < BOARD_M+1; j++) {
        PRINT(j, i);
    }
  printGameField(gameBakend);
  
}
