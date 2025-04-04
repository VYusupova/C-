#ifndef DEFINES_H
#define DEFINES_H

#define WIN_INIT(time) {\
                             initscr();\
                             noecho();\
                             curs_set(0);\
                             keypad(stdscr, TRUE);\
                             timeout(time);\
                        }
#define FSIZE  4  // размер матрицы для фигуры
#define GET_USER_INPUT getch()

#define INTRO_MESSAGE_LEN     5
#define INTRO_MESSAGE1 "Press" // приветствие
#define INTRO_MESSAGE2 "ENTER" // приветствие
#define HIDE_INTRO    "     "

#define BOARDS_BEGIN 0            // начало игрового поля левый верхний угол с отступом на 0 позиции
#define START_X      (BOARD_M / 2)  // начальные позиции фигуры для игры
#define START_Y      (1)
#define BOARD_N     20// (ROWS_MAP + MAP_PADDING * 2) // ширина и высота игрового поля
#define BOARD_M     10
#define HUD_WIDTH   10  // ширана  поля для вывода информации по уровням и т.д.

#define PRINT(x, y) mvprintw(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), " ") // функция рисования с задаными координатами
#define MVPRINTW(y, x, ...) mvprintw(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), __VA_ARGS__)
#define MVADDCH(y, x, c) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), c)
#define CLEAR_BACKPOS(y, x) { bkgdset(COLOR_PAIR(0)); mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), ' ');}

#define YOU_WON "tests/game_progress/you_won.txt"
#define YOU_LOSE "tests/game_progress/you_lose.txt"
#define LEVEL_DIR "tests/levels/level_"


#define LEVEL_CNT 5
#define LEVELNAME_MAX 25

#define MAX_WIN_COUNT    10

#define INITIAL_TIMEOUT  150

#define MAP_PADDING 3 

#define BANNER_N    10
#define BANNER_M    100

#define SUCCESS   0
#define ERROR     1

#define ESCAPE 27
#define ENTER_KEY 10

#define SHIFT_MESSAGE 4
#define R_NEXT 1   // координаты отрисовки поля под новую фигуру
#define R_NEXT_H 7 
#define R_LEV 11
#define R_SCORE 13
#define R_SPEED 15
#define R_LIVES 17

#endif
