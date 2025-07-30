#ifndef CAVE_H
#define CAVE_H

#include <stdio.h>
#include <stdlib.h>

#include "define.h"

typedef struct cave_struct {
  int **matrix;
  int rows;
  int columns;
  int birth_limit;
  int death_limit;  // Пределы «рождения» и «смерти могут иметь значения от 0
                    // до 7.
} cave_t;

void simulate_cave(cave_t *cave, int steps);
cave_t *read_file(const char *filename, int birth_limit, int death_limit);
void generate_random_cave(cave_t *result, int chance);
int count_neighbors(const cave_t *cave, int row, int col);
cave_t *copy_cave(const cave_t *cave);

cave_t *init_cave(int rows, int cols, int birth_limit, int death_limit);
void remove_cave(cave_t *A);

#endif
