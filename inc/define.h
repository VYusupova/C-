#ifndef DEFINE_H
#define DEFINE_H

// #define OK 0
#define INCORRECT 1
#define CALCULATE_ERROR 2  // TO DO

#define MAX 50
#define MIN 4
#define MAXMIN(a) \
  if ((a) > MAX || (a) < MIN) return NULL;

#define RED_ERROR "\033[31m"
#define ERR_OPEN "ошибка открытия файла\n"
#define COLOR_DEFAULT "\033[0m\n"
#define COLOR_M "\033[35m"

#define WIN_INIT(time)    \
  {                       \
    initscr();            \
    noecho();             \
    curs_set(0);          \
    keypad(stdscr, TRUE); \
    timeout(time);        \
  }

#endif
