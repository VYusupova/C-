void find_and_draw_path(int rows, int cols, int **maze_vert, int **maze_hor,
                        Point start, Point end) {
  bool visited[MAZE_SIZE][MAZE_SIZE] = {false};  // Массив пути
  Point path[rows * cols];  // Максимальная длина пути = rows * cols
  int path_length = 0;

  // Поиск пути
  if (dfs(rows, cols, maze_vert, maze_hor, visited, start, end, path,
          &path_length)) {
    int temp_maze[rows * cols];  // Одномерная матрица для хранения пути
    memset(temp_maze, 0, sizeof(int) * rows * cols);

    for (int i = 0; i < path_length; i++) {
      temp_maze[path[i].x * cols + path[i].y] = 1;  // Путь отмечаем 1
    }
    draw_maze(temp_maze, rows, cols, maze_vert, maze_hor);
  } else {
    draw_error_message("No valid path found.\n");
  }
}

const char *select_maze_file() {
  int example_choice = select_example();

  const char *filename = NULL;
  if (example_choice == 1) {
    filename = "files/maze_1";
  } else if (example_choice == 2) {
    filename = "files/maze_2";
  } else if (example_choice == 3) {
    filename = "files/maze_3";
  }
  return filename;
}

bool is_valid_move(int x, int y, int n, int m, bool visited[n][m]) {
  return x >= 0 && y >= 0 && x < n && y < m && !visited[x][y];
}

bool dfs(int n, int m, int **right_walls, int **bottom_walls,
         bool visited[n][m], Point current, Point end, Point path[],
         int *path_length) {
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
          (current.y == m - 1 || right_walls[current.x][current.y] == 1))
        continue;

      // Проверка на нижние стены
      if (i == 1 &&
          (current.x == n - 1 || bottom_walls[current.x][current.y] == 1))
        continue;

      // Проверка на левые стены
      if (i == 2 &&
          (current.y == 0 || right_walls[current.x][current.y - 1] == 1))
        continue;

      // Проверка на верхние стены
      if (i == 3 &&
          (current.x == 0 || bottom_walls[current.x - 1][current.y] == 1))
        continue;

      if (is_valid_move(nx, ny, n, m, visited)) {
        if (dfs(n, m, right_walls, bottom_walls, visited, (Point){nx, ny}, end,
                path, path_length)) {
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

