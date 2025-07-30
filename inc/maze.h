#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>

#include "define.h"

typedef struct maze_struct {
  int **wall_v;
  int **wall_h;
  int rows;
  int columns;
} maze_t;

void write_file(const maze_t *maze);
maze_t *read_file_maze();
maze_t *create_maze(int rows, int columns);
void remove_maze(maze_t *A);
void generate_maze(maze_t *maze);

#endif
