#ifndef MAZE_C
#define MAZE_C

/*
Part 2. Генерация идеального лабиринта

Добавь возможность автоматической генерации идеального лабиринта.
Идеальным считается лабиринт, в котором из каждой точки можно попасть в любую
другую точку ровно одним способом.

*Генерировать лабиринт нужно согласно алгоритму Эллера. +
*Сгенерированный лабиринт не должен иметь изолированных областей и петель. +
*Должно быть обеспечено полное покрытие unit-тестами модуля генерации идеального
лабиринта. *Пользователем указывается только размерность лабиринта: количество
строк и столбцов. *Сгенерированный лабиринт должен сохраняться в файл в формате,
описанном выше. *Созданный лабиринт должен отображаться на экране, как указано в
первой части. +
*/

#include "inc/maze.h"

void print_maze(int way[], maze_t *maze) {
  printf(COLOR_M);
  printf("+");
  for (int col = 0; col < maze->columns; col++) {
    printf("---+");
  }
  printf("\n");

  for (int row = 0; row < maze->rows; row++) {
    // Левая граница
    printf("|");

    // Ячейки и правые стены
    for (int col = 0; col < maze->columns; col++) {
      if (way != NULL && way[row * maze->columns + col] == 1)
        printf(COLOR_GREEN " o " COLOR_M);
      else
        printf("   ");
      if (col < maze->columns) {
        printf(maze->wall_v[row][col] ? "|" : " ");
      } else {
        printf("|");
      }
    }
    printf("\n");

    // Нижние стены
    if (row < maze->rows) {
      printf("+");
      for (int col = 0; col < maze->columns; col++) {
        printf(maze->wall_h[row][col] ? "---+" : "   +");
      }
      printf("\n");
    }
  }

  printf(COLOR_DEFAULT "\n");
}

void write_file(const maze_t *maze) {
  FILE *file = fopen("maze.txt", "w");
  if (file == NULL) {
    printf(ERR_OPEN);
  }
  fprintf(file, "%d %d\n", maze->rows, maze->columns);
  for (int i = 0; i < maze->rows; i++) {
    for (int j = 0; j < maze->columns; j++) {
      fprintf(file, "%d ", maze->wall_v[i][j]);
    }
    fprintf(file, "\n");
  }
  fprintf(file, "\n");

  for (int i = 0; i < maze->rows; i++) {
    for (int j = 0; j < maze->columns; j++) {
      fprintf(file, "%d ", maze->wall_h[i][j]);
    }
    fprintf(file, "\n");
  }
  fprintf(file, "\n");

  fclose(file);
}

maze_t *read_file_maze(char *name) {
  maze_t *maze = NULL;
  FILE *file = fopen(name, "r");
  if (file == NULL) {
    printf(RED_ERROR ERR_OPEN " Файл %s не найден" COLOR_DEFAULT, name);
  } else {
    int rows = 0, columns = 0;
    fscanf(file, "%d %d", &rows, &columns);
    MAXMIN(rows);
    MAXMIN(columns);

    maze = create_maze(rows, columns);

    for (int i = 0; i < maze->rows; i++) {
      for (int j = 0; j < maze->columns; j++) {
        fscanf(file, "%d", &maze->wall_v[i][j]);
      }
    }

    for (int i = 0; i < maze->rows; i++) {
      for (int j = 0; j < maze->columns; j++) {
        fscanf(file, "%d", &maze->wall_h[i][j]);
      }
    }
    fclose(file);
  }

  return maze;
}

// создание матрицы
maze_t *create_maze(int rows, int columns) {
  MAXMIN(rows);
  MAXMIN(columns);

  maze_t *maze = (maze_t *)malloc(sizeof(maze_t));
  if (!maze)
    return NULL;

  maze->rows = rows;
  maze->columns = columns;

  // Выделение памяти для двумерного массива
  maze->wall_v = (int **)malloc(rows * sizeof(int *));
  for (int i = 0; i < rows; i++) {
    maze->wall_v[i] = (int *)calloc(columns, sizeof(int));
  }
  maze->wall_h = (int **)malloc((rows) * sizeof(int *));
  for (int i = 0; i < rows; i++) {
    maze->wall_h[i] = (int *)calloc(columns, sizeof(int));
  }

  return maze;
}

void generate_maze(maze_t *maze) {
  if (!maze || !maze->wall_v || !maze->wall_h || maze->rows <= 0 ||
      maze->columns <= 0) {
    return;
  }
  // шаг 1 создаем массивы с пустыми значениями для указания множеств
  int *set = (int *)calloc(maze->columns, sizeof(int));
  int *set_counts = (int *)calloc(maze->columns, sizeof(int));
  int count = 1;

  // шаг 2 присваиваем свое уникальное множество
  for (int i = 0; i < maze->rows; i++) {
    for (int j = 0; j < maze->columns; j++) {
      if (set[j] == 0) {
        set[j] = count++;
        set_counts[j] = 1;
      }
    }

    // шаг 3 создание правой границы, двигаясь слева направо
    for (int j = 0; j < maze->columns - 1; j++) {
      int choice = rand() % 2;
      if (set[j] == set[j + 1] || (choice == 1 && i != maze->rows - 1)) {
        maze->wall_v[i][j] = 1;
      } else {
        int old_set = set[j + 1];
        for (int k = 0; k < maze->columns; k++) {
          if (set[k] == old_set) {
            set[k] = set[j];
            set_counts[j]++;
          }
        }
      }
    }
    // самая правая граница
    maze->wall_v[i][maze->columns - 1] = 1;

    // шаг 4 создание нижней границы, двигаясь слева направо
    if (i != maze->rows - 1) {
      for (int j = 0; j < maze->columns; j++) {
        int choice = rand() % 2;
        if (set_counts[j] > 1 && choice == 1) {
          maze->wall_h[i][j] = 1;
          set_counts[j]--;
          set[j] = 0; // удаление из множества
        }
        // для последней строки
        maze->wall_h[maze->rows - 1][j] = 1;
      }
      // шаг 5 копируем текущию строку для следущей
      for (int j = 0; j < maze->columns; j++) {
        if (maze->wall_h[i][j] == 1) {
          set[j] = 0;
        }
      }
    } else {
      for (int j = 0; j < maze->columns - 1; j++) {
        if (set[j] != set[j + 1]) {
          maze->wall_v[i][j] = 0; // удаление правых стен
          int old_set = set[j + 1];
          for (int k = 0; k < maze->columns; k++) {
            if (set[k] == old_set) {
              set[k] = set[j];
            }
          }
        }
      }
    }
  }
  free(set);
  free(set_counts);
}

// удаление матрицы
void remove_maze(maze_t *A) {
  if (A != NULL) {
    if (A->wall_v) {
      for (int i = 0; i < A->rows; i++) {
        free(A->wall_v[i]);
      }
      free(A->wall_v);
      A->wall_v = NULL;
    }
    if (A->wall_h) {
      for (int i = 0; i < A->rows; i++) {
        free(A->wall_h[i]);
      }
      free(A->wall_h);
      A->wall_h = NULL;
    }
    A->rows = 0;
    A->columns = 0;
    free(A);
  }
}

#endif
