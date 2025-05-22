#include "../../../inc/frontend.h"

void initColors(void) {
  if (!has_colors()) {
    endwin();
    printf("COLORS NOT SUPPORTED");
  }
  start_color();
  init_pair(FIGURE_HIDE, COLOR_BLACK, COLOR_BLACK);
  init_pair(MASSEGE, COLOR_WHITE, COLOR_BLACK);
  init_pair(COLOR_1, COLOR_BLACK, COLOR_YELLOW);
  init_pair(COLOR_2, COLOR_BLACK, 190);
  init_pair(COLOR_3, COLOR_BLACK, COLOR_RED);
  init_pair(COLOR_4, COLOR_BLACK, COLOR_GREEN);
  init_pair(COLOR_5, COLOR_BLACK, 70);
  init_pair(COLOR_6, COLOR_BLACK, 60); // color darck blue
  init_pair(COLOR_7, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(COLOR_8, COLOR_BLACK, 90);
 init_pair(COLOR_9, COLOR_BLACK, COLOR_CYAN);
                                                                                              
init_pair(COLOR_10, COLOR_BLACK, 100);
init_pair(COLOR_11, COLOR_BLACK, 210);
init_pair(COLOR_12, COLOR_BLACK, 220);
init_pair(COLOR_13, COLOR_BLACK, 230);
init_pair(COLOR_14, COLOR_BLACK, 240);
init_pair(COLOR_15, COLOR_BLACK, 250);
init_pair(COLOR_16, COLOR_BLACK, COLOR_RED);
init_pair(COLOR_17, COLOR_BLACK, 100);
init_pair(COLOR_18, COLOR_BLACK, 80);
init_pair(COLOR_19, COLOR_BLACK, 200); // color splash PINK 
  init_pair(COLOR_PINK, COLOR_BLACK, 213);

}

static void printColorPanel(void){
int startX = R_NEXT+16;
int startY = BOARD_M + SHIFT_MESSAGE;
int delta = 0;
for (int i = 1 ; i <= 5; i++)
{
	bkgdset(COLOR_PAIR(i));
	MVPRINTW(startX, startY+delta, " %d", i);
	bkgdset(COLOR_PAIR(i+4));
	MVPRINTW(startX+1, startY+delta, " %d", i+4);
	bkgdset(COLOR_PAIR(i+10));
	MVPRINTW(startX+2, startY+delta, "%d", i+10);
	bkgdset(COLOR_PAIR(i+15));
	MVPRINTW(startX+3, startY+delta, "%d", i+15);
	delta +=2;
}
	bkgdset(COLOR_PAIR(10));
	MVPRINTW(startX+1, startY+8, "10" );

}

static void showIntro(void) {
  int start = BOARD_N / 2 - 6;
  int Y = 4;
   MVPRINTW(start, Y, "Press");
   MVPRINTW(start+1, Y,"ENTER - start");
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
  MVPRINTW(BOARD_N / 2 + 2, BOARD_M/2-3, "Press ENTER");
  MVPRINTW(BOARD_N / 2 + 3, BOARD_M/2-1, "to start");

}

// отрисовка уровня и очков
void print_stats(GameInfo_t *game) {
  bkgdset(COLOR_PAIR(MASSEGE));
  int startY = R_NEXT; 
  MVPRINTW(startY, BOARD_M + SHIFT_MESSAGE, "NEXT");
  startY +=6;
  if (game->pause) MVPRINTW(startY, BOARD_M + SHIFT_MESSAGE, "  PAUSE");
  else MVPRINTW(startY, BOARD_M + SHIFT_MESSAGE, "       ");
  startY +=3;
  MVPRINTW(startY, BOARD_M + SHIFT_MESSAGE, "%d", game->level);
  startY +=2;
  MVPRINTW(startY, BOARD_M + SHIFT_MESSAGE, "%d", game->score);
  startY +=2;
  MVPRINTW(startY, BOARD_M + SHIFT_MESSAGE, "%d", game->speed);
  startY +=2;
  if (game->score > game->high_score) MVPRINTW(startY, BOARD_M + SHIFT_MESSAGE, "%d", game->score);
  else MVPRINTW(startY, BOARD_M + SHIFT_MESSAGE, "%d", game->high_score);
    
}


// отрисовка прямоугольника с координатми
static void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
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
  MVPRINTW(R_NEXT+14, BOARD_M + SHIFT_MESSAGE, "MAX SCORE");
  showIntro();
  printColorPanel();
}

void printPause(void) {
  bkgdset(COLOR_PAIR(MASSEGE));
  MVPRINTW(BOARD_N/2, BOARD_M/2, "PAUSE");
}

static void printFigure(const figura *f) {
  for (int i = 1; i < f->n+1; i++)
    for (int j = 1; j < f->m+1; j++) {
      if (f->figur[i-1][j-1] == 1) PRINT((f->x*2 + j*2), f->y + i);
    }
}

void hideFigure(const figura *f) {
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

static void printGameField(GameInfo_t *game) {
  for (int i = 1; i < BOARD_N+1; i++)
    for (int j = 1; j < FIELD_M+1; j++) {
      if (game->field[i-1][j-1]) {
        bkgdset(COLOR_PAIR(game->field[i-1][j-1]));
        PRINT(j*2, i);
      }
    }
}

void refreshGameField(GameInfo_t *game) {
  bkgdset(COLOR_PAIR(0));
  for (int i = 1; i < BOARD_N+1; i++)
    for (int j = 1; j < BOARD_M+1; j++) {
        PRINT(j, i);
    }
  printGameField(game);
  
}
