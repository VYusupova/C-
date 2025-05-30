#ifndef DEFINES_H
#define DEFINES_H

#include <ncurses.h>

#define WIN_INIT(time)    \
  {                       \
    initscr();            \
    noecho();             \
    curs_set(0);          \
    keypad(stdscr, TRUE); \
    timeout(time);        \
  }

#define GET_USER_INPUT getch()

#define PRINT(x, y) mvprintw(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), "  ")
#define MVPRINTW(y, x, ...) \
  mvprintw(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), __VA_ARGS__)
#define MVADDCH(y, x, c) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), c)

#define FSIZE 4  // размер матрицы для фигуры

// начало игрового поля левый верхний угол с отступом на 0 позиции
#define BOARDS_BEGIN 0
#define START_X (FIELD_M / 2) - 1  // начальные позиции фигуры для игры
#define START_Y MAP_PADDING
#define MAP_PADDING 0  // сдвиг игрового поля для фронтэнда
#define BOARD_N 20
#define BOARD_M FIELD_M * 2
// ширина и высота игрового поля для матрицы бэкенда
#define FIELD_N 20
#define FIELD_M 10
// ширана  поля для вывода информации по уровням и т.д.
#define HUD_WIDTH 10

#define MAX_SCORE "tetris_max_score.txt"

//#define LEVEL_CNT 5
#define LEVEL_MAX 10
#define SPEED 780

#define MAX_WIN_COUNT 10

#define INITIAL_TIMEOUT 150

#define SUCCESS 0
#define ERROR 1

#define ESCAPE 27
#define ENTER_KEY 10
#define PAUSE_p 112
#define PAUSE_P 80
#define SPACE ' '

#define SHIFT_MESSAGE 4
// координаты отрисовки поля под новую фигуру
#define R_NEXT 1
#define R_NEXT_H 7
#define R_NEXT_X FIELD_M + 2
#define R_NEXT_Y 2

#endif
