#ifndef MAZE_OUT
#define MAZE_OUT

#include "inc/maze.h"

void print_top(int columns);
void left_way(int row, int col, int way[], maze_t *maze) {
  int w = row * maze->columns + col;
  if ((col - 1) >= 0) {
    int left = way[w - 1];
    int lwall = maze->wall_v[row][col - 1];
    if ((left == 1) && lwall != 1)
      PRINT_WAY;
    else
      printf(" ");
  } else
    printf(" ");
}

int right_way(int row, int col, int way[], maze_t *maze) {
  int r = 0;
  int w = row * maze->columns + col;
  if ((col + 1) < maze->columns) {
    int right = way[w + 1];
    int rwall = maze->wall_v[row][col];
    if (right == 1 && rwall != 1) {
      PRINT_WAY;
      r = 1;
    } else
      printf(" ");
  } else
    printf(" ");
  return r;
}

void print_wall(int wall, int way) {
  if (wall == 1 && way == 0)
    printf("|");
  else if (way == 1)
    PRINT_WAY;
  else
    printf(" ");
}

void print_bottom_way(int row, int col, int way[], maze_t *maze) {
  if (way != NULL && (row + 1) < (maze->rows)) {
    int w_b = (row + 1) * maze->columns + col;
    int bottom_way = way[w_b];
    int w = way[row * maze->columns + col];
    if (w == 1 && bottom_way == 1) {
      printf(" ");
      PRINT_WAY;
      printf(" +");
    } else
      printf("   +");
  } else
    printf("   +");
}

void print_maze(int way[], maze_t *maze) {
  printf(COLOR_M);
  print_top(maze->columns);

  for (int row = 0; row < maze->rows; row++) {
    printf("|"); // Левая граница

    // Ячейки и правые стены
    for (int col = 0; col < maze->columns; col++) {
      int w = row * maze->columns + col;
      int r_way = 0;

      if (way != NULL && way[w] == 1) {
        left_way(row, col, way, maze);
        PRINT_WAY;
        r_way = right_way(row, col, way, maze);
      } else
        printf("   ");
      print_wall(maze->wall_v[row][col], r_way);
    }
    printf("\n");

    // Нижние стены
    if (row < maze->rows) {
      printf("+");
      for (int col = 0; col < maze->columns; col++) {
        if (maze->wall_h[row][col] == 1)
          printf("---+");
        else
          print_bottom_way(row, col, way, maze);
      }
      printf("\n");
    }
  }

  printf(COLOR_DEFAULT "\n");
}

void print_top(int columns) {
  printf("+");
  for (int col = 0; col < columns; col++) {
    printf("---+");
  }
  printf("\n");
}

#endif
