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
    printf("YES way found\n");
    print_maze(temp_maze, maze);
  } else {
    printf(RED_ERROR "No valid way found.\n" COLOR_DEFAULT);
  }
}

bool is_valid_move(int x, int y, int n, int m, bool visited[n][m]) {
  return x >= 0 && y >= 0 && x < n && y < m && !visited[x][y];
}

bool dfs(maze_t *maze, bool visited[maze->rows][maze->columns], Point start,
         Point end, Point path[], int *path_length) {
  int n = maze->rows;
  int m = maze->columns;
  bool error = false;
  if (start.x == end.x && start.y == end.y) {
    path[(*path_length)++] = start;
    error = true;
  }

  if (error != true) {
    visited[start.x][start.y] = true;
    path[(*path_length)++] = start;

    // Направления: вправо, вниз, влево, вверх
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};

    for (int i = 0; i < 4; i++) {
      int nx = start.x + dx[i];
      int ny = start.y + dy[i];

      // Проверка на правые стены
      if (i == 0 &&
          (start.y == m - 1 || maze->wall_v[start.x][start.y] == 1))
        continue;

      // Проверка на нижние стены
      if (i == 1 &&
          (start.x == n - 1 || maze->wall_h[start.x][start.y] == 1))
        continue;

      // Проверка на левые стены
      if (i == 2 &&
          (start.y == 0 || maze->wall_v[start.x][start.y - 1] == 1))
        continue;

      // Проверка на верхние стены
      if (i == 3 &&
          (start.x == 0 || maze->wall_h[start.x - 1][start.y] == 1))
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
