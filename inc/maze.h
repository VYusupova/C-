#ifndef MAZE_H
#define MAZE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "define.h"

typedef struct maze_struct {
  int **wall_v;
  int **wall_h;
  int rows;
  int columns;
} maze_t;

typedef struct Point_struct {
  int x;
  int y;
} Point;

void write_file(const maze_t *maze);
maze_t *read_file_maze();
maze_t *create_maze(int rows, int columns);
void remove_maze(maze_t *A);
void generate_maze(maze_t *maze);

void find_way(maze_t *maze, Point start, Point end);
bool dfs(maze_t *maze, bool visited[n][m], Point current, Point end, Point path[], int *path_length);

#endif
