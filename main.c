#ifndef MAIN_C
#define MAIN_C

#include <stdio.h>
#include <time.h>

#include "inc/cave.h"
#include "inc/define.h"
#include "inc/maze.h"

void menu_way(maze_t *maze);

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
      char *name = NULL;
      printf("введите имя файла - \n");
      scanf("%ms", &name);  // динамически выделили память в конце освободили
      maze = read_file_maze(name);
      if (maze != NULL) {
        print_maze(NULL, maze);
        menu_way(maze);
        remove_maze(maze);
      } else {
        printf("не удалось считать, неправильные прараметры в файле\n");
      }
      if (name) free(name);
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
      print_maze(NULL, maze);
      menu_way(maze);
      write_file(maze);
      remove_maze(maze);
      break;
  }
}

int input_point(char *str, Point *p, maze_t *maze) {
  printf("ENTER point to %s: ", str);
  if (2 != scanf("%d%d", &p->x, &p->y)) {
    printf("ERROR");
    return 1;
  }
  if (p->x > maze->rows - 1 || p->x < 0) {
    printf("ERROR");
    return 1;
  }
  if (p->y > maze->columns - 1 || p->x < 0) {
    printf("ERROR");
    return 1;
  }
  return 0;
}

void menu_way(maze_t *maze) {
  int user_input = 0;
  printf("построить обход лабиринта: \n\tДа - 1\n\tНет - 2\n");
  scanf("%d", &user_input);
  if (user_input == 1) {
    Point start = {0, 0};
    Point end = {0, 0};
    if (input_point("входа в лабиринт", &start, maze) != 0) return;
    if (input_point("END", &end, maze) != 0) return;
    find_way(maze, start, end);
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
