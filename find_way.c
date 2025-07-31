#include "inc/maze.h"

void find_way(maze_t *maze, Point start, Point end) {
  int row = maze->rows;
  int col = maze->columns;
  bool visited[MAX][MAX] = {false}; // Массив пути
  Point path[row * col]; // Максимальная длина пути = rows * cols
  int path_length = 0;

  // Поиск пути
  if (dfs(maze, visited, start, end, path, &path_length)) {
    int temp_maze[row * col]; // Одномерная матрица для хранения пути
    memset(temp_maze, 0, sizeof(int) * row * col);

    for (int i = 0; i < path_length; i++) {
      temp_maze[path[i].x * col + path[i].y] = 1; // Путь отмечаем 1
    }
    // draw_maze(temp_maze, row, col, maze->wall_v,
    // maze->wall_h);
    printf("YES way found\n");
    print_maze(temp_maze, maze);
  } else {
    // draw_error_message("No valid path found.\n");
    printf(RED_ERROR "No valid way found.\n" COLOR_DEFAULT);
  }
}

bool is_valid_move(int x, int y, int n, int m, bool visited[n][m]) {
  return x >= 0 && y >= 0 && x < n && y < m && !visited[x][y];
}

bool dfs(maze_t *maze, bool visited[maze->rows][maze->columns], Point current,
         Point end, Point path[], int *path_length) {
  int n = maze->rows;
  int m = maze->columns;
  bool error = false;
  if (current.x == end.x && current.y == end.y) {
    path[(*path_length)++] = current;
    error = true;
  }

  if (error != true) {
    visited[current.x][current.y] = true;
    path[(*path_length)++] = current;

    // Направления: вправо, вниз, влево, вверх
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};

    for (int i = 0; i < 4; i++) {
      int nx = current.x + dx[i];
      int ny = current.y + dy[i];

      // Проверка на правые стены
      if (i == 0 &&
          (current.y == m - 1 || maze->wall_v[current.x][current.y] == 1))
        continue;

      // Проверка на нижние стены
      if (i == 1 &&
          (current.x == n - 1 || maze->wall_h[current.x][current.y] == 1))
        continue;

      // Проверка на левые стены
      if (i == 2 &&
          (current.y == 0 || maze->wall_v[current.x][current.y - 1] == 1))
        continue;

      // Проверка на верхние стены
      if (i == 3 &&
          (current.x == 0 || maze->wall_h[current.x - 1][current.y] == 1))
        continue;

      if (is_valid_move(nx, ny, n, m, visited)) {
        if (dfs(maze, visited, (Point){nx, ny}, end, path, path_length)) {
          error = true;
        }
      }
    }
    // Убираем из пути, если этот путь не привел к цели
    if (error != true) {
      (*path_length)--;
    }
  }
  return error;
}
