#ifndef MAIN_C
#define MAIN_C

#include <stdio.h>
#include <time.h>

#include "inc/cave.h"
#include "inc/define.h"
#include "inc/maze.h"

void print_maze(maze_t *maze) {
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

void print_cave(cave_t *cave) {
  printf("\033[H\033[J");
  for (int i = 0; i < cave->rows; i++) {
    for (int j = 0; j < cave->columns; j++) {
      printf("%c", cave->matrix[i][j] ? '#' : ' ');
    }
    printf("\n");
  }
}

void input_maze() {
  int rows, cols;
  maze_t *maze;
  int user_input;
  printf("Загрузить из файла - 1\nСгенерировать - 2\n");
  scanf("%d", &user_input);
  switch (user_input) {
    case 1:
      maze = read_file_maze();
      if (maze != NULL) {
        print_maze(maze);
        remove_maze(maze);
      } else {
        printf("не удалось считать, неправильные прараметры в файле\n");
      }
      break;
    case 2:
      printf("введите размеры лабиринта: ");
      scanf("%d %d", &rows, &cols);
      maze = create_maze(rows, cols);

      if (!maze) {
        printf("Ошибка инициализации лабиринта\n");
        return;
      }

      generate_maze(maze);
      print_maze(maze);
      write_file(maze);
      remove_maze(maze);
      break;
  }
}

void cave_input_simulate(cave_t *cave) {
  int steps;
  printf("покзать следущий шаг'\n'Да = 1\nНет = 0\n");
  scanf("%d", &steps);
  while (steps != 0) {
    simulate_cave(cave, steps);
    print_cave(cave);
    printf("покзать следущий шаг = 1\nвозврат к меню выбора = 0\n");
    scanf("%d", &steps);
  }
}

void input_cave() {
  int user_input, birth_limit, death_limit;
  printf("Загрузить из файла\nДа - 1\nСгенерировать - 2\n");
  scanf("%d", &user_input);
  if (user_input == 1) {
    char filename[256];
    printf("введите имя файла\n");
    scanf("%s", filename);
    printf("введите лимиты численности: ");
    scanf("%d %d", &birth_limit, &death_limit);
    cave_t *cave = read_file(filename, birth_limit, death_limit);
    if (!cave) {
      printf("ошибка в файле\n");
      return;
    }
    print_cave(cave);
    cave_input_simulate(cave);
    remove_cave(cave);
  } else if (user_input == 2) {
    int rows, cols;
    printf("введите размеры пещеры: ");
    scanf("%d %d", &rows, &cols);
    printf("введите лимиты численности: ");
    scanf("%d %d", &birth_limit, &death_limit);
    cave_t *cave = init_cave(rows, cols, birth_limit, death_limit);
    if (!cave) {
      printf(RED_ERROR "Ошибка инициализации пещеры!" COLOR_DEFAULT);
      return;
    }
    printf("введите шансы на рождение: ");
    int change;
    scanf("%d", &change);
    generate_random_cave(cave, change);
    print_cave(cave);
    cave_input_simulate(cave);
    remove_cave(cave);
  }
}

int main() {
  srand(time(NULL));
  int user_input, break_flag = 0;

  while (break_flag != 1) {
    printf("Лабиринт - 1\nПещеры - 2\nВыход - 3\n");
    if (scanf("%d", &user_input) != 1) {
      printf("n/a\n");
      break_flag = 1;
    }
    switch (user_input) {
      case 1:
        input_maze();
        break;
      case 2:
        input_cave();
        break;
      case 3:
        break_flag = 1;
        break;
      default:
        printf(RED_ERROR "неверная команда!" COLOR_DEFAULT);
        break;
    }
  }

  return 0;
}

#endif
