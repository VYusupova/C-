#ifndef CAVE_C
#define CAVE_C

/*
Part 4. Дополнительно. Генерация пещер

Добавь генерацию пещер с использованием клеточного автомата:

*Пользователем указывается файл, в котором описана пещера по описанному выше
формату. *Максимальный размер пещеры — 50х50. + *Загруженная пещера должна быть
отрисована на экране в консоли псевдографикой. + *Пользователем задаются пределы
«рождения» и «смерти» клетки, а также шанс на начальную инициализацию клетки. +
*Пределы «рождения» и «смерти могут иметь значения от 0 до 7. +
*Клетки за границей пещеры считаются живыми. +
*Должен быть предусмотрен пошаговый режим отрисовки результатов работы алгоритма
в двух вариантах:
*
        *По выбору опции следующего шага отрисовывается очередная итерация
работы алгоритма; + *По выбору опции автоматической работы запускается отрисовка
итераций работы алгоритма с частотой 1 шаг в N миллисекунд, где число
миллисекунд N задаётся отдельно пользователем.
*
*
*Размер клеток в пикселях вычисляется таким образом, чтобы пещера занимала всё
отведенное под него поле. ? *Должно быть обеспечено полное покрытие unit-тестами
модуля генерации пещер.
*/

#include "inc/cave.h"

cave_t *read_file(const char *filename, int birth_limit, int death_limit) {
  FILE *f = fopen(filename, "r");
  if (f == NULL)
    return NULL;

  int rows = 0, columns = 0;
  if (fscanf(f, "%d %d", &rows, &columns) != 2) {
    printf("ошибка чтения");
    fclose(f);
    return NULL;
  }
  cave_t *cave = init_cave(rows, columns, birth_limit, death_limit);
  for (int i = 0; i < cave->rows; i++) {
    for (int j = 0; j < cave->columns; j++) {
      if (fscanf(f, "%d", &cave->matrix[i][j]) != 1) {
        fclose(f);
        return NULL;
      }
    }
  }
  fclose(f);
  return cave;
}

cave_t *init_cave(int rows, int cols, int birth_limit, int death_limit) {
  MAXMIN(rows);
  MAXMIN(cols);
  if (birth_limit > 7 || death_limit > 7 || birth_limit < 0 || death_limit < 0)
    return NULL;

  cave_t *cave = (cave_t *)malloc(sizeof(cave_t));
  if (!cave)
    return NULL;

  cave->rows = rows;
  cave->columns = cols;
  cave->birth_limit = birth_limit;
  cave->death_limit = death_limit;

  // Выделение памяти для двумерного массива
  cave->matrix = (int **)malloc(rows * sizeof(int *));
  if (!cave->matrix) {
    free(cave);
    return NULL;
  }

  for (int i = 0; i < rows; i++) {
    cave->matrix[i] = (int *)malloc(cols * sizeof(int));
    if (!cave->matrix[i]) {
      // Если выделение не удалось, освобождаем уже выделенную память
      for (int j = 0; j < i; j++) {
        free(cave->matrix[j]);
      }
      free(cave->matrix);
      free(cave);
      return NULL;
    }
  }

  return cave;
}

void generate_random_cave(cave_t *result, int chance) {
  if (result->matrix == NULL)
    return;

  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      result->matrix[i][j] = (rand() % 100) < chance ? 1 : 0;
    }
  }
}

void simulate_cave(cave_t *cave, int steps) {
  for (int i = 0; i < steps; i++) {
    cave_t *new_cave = copy_cave(cave);

    for (int row = 0; row < cave->rows; row++) {
      for (int col = 0; col < cave->columns; col++) {
        int neighbors = count_neighbors(cave, row, col);

        if (cave->matrix[row][col] == 1)
          new_cave->matrix[row][col] = (neighbors < cave->death_limit) ? 0 : 1;
        else
          new_cave->matrix[row][col] = (neighbors > cave->birth_limit) ? 1 : 0;
      }
    }
    remove_cave(cave);
    *cave = *new_cave;
    free(new_cave);
  }
}

int count_neighbors(const cave_t *cave, int row, int col) {
  int count = 0;

  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i == 0 && j == 0)
        continue;

      int neighbors_row = row + i;
      int neighbors_col = col + j;
      if (neighbors_row >= 0 && neighbors_row < cave->rows &&
          neighbors_col >= 0 && neighbors_col < cave->columns) {
        // Если клетка "живая" (стена), увеличиваем счетчик
        count += cave->matrix[neighbors_row][neighbors_col];
      } else {
        count += 1;
      }
    }
  }
  return count;
}

cave_t *copy_cave(const cave_t *cave) {
  cave_t *dest = init_cave(cave->rows, cave->columns, cave->birth_limit,
                           cave->death_limit);

  for (int i = 0; i < cave->rows; i++) {
    for (int j = 0; j < cave->columns; j++) {
      dest->matrix[i][j] = cave->matrix[i][j];
    }
  }
  return dest;
}

// Удаление матрицы
void remove_cave(cave_t *A) {
  if (A != NULL) {
    for (int i = 0; i < A->rows; i++)
      free(A->matrix[i]);
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

#endif
