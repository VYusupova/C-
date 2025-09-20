

#include "include/back.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file back.c
 * @brief модель тетриса
 *
 */

int** InitField(int x, int y);

int** FreeField(int** field, int size);
void LoadHighScore(int* high_score);

/**
 * @brief Возвращение ссылки на статический объект
 */
TetrisGameData* GetData() {
  static TetrisGameData data = {0};
  if (!data.initialized) {
    data.figure_controller = malloc(sizeof(Figure));
    data.game_info.field = InitField(10, 23);
    data.game_info.next = InitField(5, 5);
    data.figure_controller->figure_field = InitField(5, 5);
    data.copy_to_share.field = InitField(10, 20);
    data.copy_to_share.next = InitField(5, 5);
    data.initialized = 1;
    data.game_info.pause = 0;
    data.game_info.score = 0;
    data.game_info.speed = 1;
    data.game_info.high_score = 0;
    gettimeofday(&data.last_tick, NULL);
    LoadHighScore(&data.game_info.high_score);
  }

  return &data;
}

/**
 * @brief Таймер автоматического движения
 */
int ProcessTimer(TetrisGameData* game) {
  int code = 0;
  struct timeval current_time;
  gettimeofday(&current_time, NULL);

  if (!game->game_info.pause) {
    int drop_delay_ms = 1000 / game->game_info.speed;

    long elapsed_ms = (current_time.tv_sec - game->last_tick.tv_sec) * 1000 +
                      (current_time.tv_usec - game->last_tick.tv_usec) / 1000;

    if (elapsed_ms >= drop_delay_ms) {
      code = 1;
      game->last_tick = current_time;
    }
  }
  return code;
}

/**
 * @brief срез данных игры для передачи
 */
GameInfo_t CollectGameData(TetrisGameData* game) {
  if (game->game_info.field == NULL && game->game_info.pause) {
    return game->copy_to_share;
  }

  for (int i = 0; i < 20; i++) {
    memcpy(game->copy_to_share.field[i], game->game_info.field[i + 3],
           10 * sizeof(int));
  }
  int original_corner_y = game->figure_controller->corner_y;
  game->figure_controller->corner_y = original_corner_y - 3;
  game->figure_controller->corner_y = original_corner_y;
  for (int i = 0; i < 5; i++) {
    memcpy(game->copy_to_share.next[i], game->game_info.next[i],
           5 * sizeof(int));
  }
  game->copy_to_share.pause = game->game_info.pause;
  game->copy_to_share.score = game->game_info.score;
  game->copy_to_share.speed = game->game_info.speed;
  game->copy_to_share.high_score = game->game_info.high_score;
  return game->copy_to_share;
}

/**
 * @brief размещение фигуры на поле бэкенда
 */
void PlaceFigure(int** field, Figure* f_controller) {
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      if (f_controller->figure_field[i][j] == 1) {
        int field_x = f_controller->corner_x + j;
        int field_y = f_controller->corner_y + i;
        if (field_x >= 0 && field_x < 10 && field_y >= 0 && field_y < 23) {
          field[field_y][field_x] = f_controller->figure_field[i][j];
        }
      }
    }
  }
}

/**
 * @brief отрисовка фигуры на поле представления
 */
void ShowFigure(int** field, Figure* f_controller) {
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      if (f_controller->figure_field[i][j] == 1) {
        int field_x = f_controller->corner_x + j;
        int field_y = f_controller->corner_y + i - 3;
        if (field_x >= 0 && field_x < 10 && field_y >= 0 && field_y < 20) {
          field[field_y][field_x] = f_controller->figure_field[i][j];
        }
      }
    }
  }
}

/**
 * @brief начало новой игры
 */
void NewGame(TetrisGameData* game) {
  for (int i = 0; i < 23; i++) {
    memset(game->game_info.field[i], 0, 10 * sizeof(int));
    if (i < 20) memset(game->copy_to_share.field[i], 0, 10 * sizeof(int));
  }
  for (int i = 0; i < 5; i++) {
    memset(game->game_info.next[i], 0, 5 * sizeof(int));
    memset(game->copy_to_share.next[i], 0, 5 * sizeof(int));
  }
  game->figure_controller->corner_x = 3;
  game->figure_controller->corner_y = 0;
  game->game_info.score = 0;
  game->game_info.speed = 1;
  game->game_info.pause = 0;
  gettimeofday(&game->last_tick, NULL);
}

/**
 * @brief конец игры
 */
void GameOver(TetrisGameData* game_data) {
  game_data->game_info.pause = 1;
  for (int i = 0; i < 23; i++) {
    for (int j = 0; j < 10; j++) {
      game_data->game_info.field[i][j] = 1;
    }
  }
}

/**
 * @brief закрытие игры
 */
void QuitGame(TetrisGameData* game) {
  if (game) {
    game->game_info.field = FreeField(game->game_info.field, 23);
    game->game_info.next = FreeField(game->game_info.next, 5);
    if (game->figure_controller) {
      game->figure_controller->figure_field =
          FreeField(game->figure_controller->figure_field, 5);
      free(game->figure_controller);
    }
    game->copy_to_share.field = FreeField(game->copy_to_share.field, 20);
    game->copy_to_share.next = FreeField(game->copy_to_share.next, 5);
    game->copy_to_share.field = NULL;
    game->copy_to_share.next = NULL;
    game->game_info.field = NULL;
    game->game_info.next = NULL;
    game->figure_controller = NULL;
    game->copy_to_share.pause = 1;
    game->game_info.pause = 1;
  }
}

/**
 * @brief проверка линий, удаление заполненных, добавление очков
 */
void CheckLinesAddScore(TetrisGameData* game) {
  int deleted_lines = 0;
  for (int i = 3; i < 23;) {
    int can_delete = 1;

    for (int j = 0; j < 10 && can_delete; j++) {
      if (!game->game_info.field[i][j]) {
        can_delete = 0;
      }
    }
    if (can_delete) {
      for (int j = i; j > 0; j--) {
        memcpy(game->game_info.field[j], game->game_info.field[j - 1],
               10 * sizeof(int));
      }

      memset(game->game_info.field[0], 0, 10 * sizeof(int));
      deleted_lines++;
    } else {
      i++;
    }
  }
  switch (deleted_lines) {
    case 1:
      game->game_info.score += 100;
      break;
    case 2:
      game->game_info.score += 300;
      break;
    case 3:
      game->game_info.score += 700;
      break;
    case 4:
      game->game_info.score += 1500;
      break;
  }
  if (game->game_info.score > game->game_info.high_score) {
    game->game_info.high_score = game->game_info.score;
  }
  if (game->game_info.speed != 10) {
    game->game_info.speed = (game->game_info.score / 600) + 1;
    if (game->game_info.speed > 10) {
      game->game_info.speed = 10;
    }
  }
}

void DropFigure(TetrisGameData* game) {
  int max_y = game->figure_controller->corner_y;
  int can_move = 1;

  while (can_move) {
    max_y++;
    for (int i = 0; i < 5 && can_move; i++) {
      for (int j = 0; j < 5 && can_move; j++) {
        if (game->figure_controller->figure_field[i][j] == 1) {
          int new_x = game->figure_controller->corner_x + j;
          int new_y = max_y + i;
          if (new_x < 0 || new_x >= 10 || new_y >= 0 || new_y >= 23 ||
              game->game_info.field[new_y][new_x]) {
            can_move = 0;
          }
        }
      }
    }
  }
  game->figure_controller->corner_y = max_y - 1;
}

/**
 * @brief движение фигуры
 */
int MoveFigure(TetrisGameData* game, UserAction_t direction) {
  int code = 0;
  int old_x = game->figure_controller->corner_x;
  int old_y = game->figure_controller->corner_y;

  switch (direction) {
    case Down:
        game->figure_controller->corner_y++;
      break;
    case Left:
      game->figure_controller->corner_x--;
      break;
    case Right:
      game->figure_controller->corner_x++;
      break;
    default:
      break;
  }
  int collision = 0;
  for (int i = 0; i < 5 && !collision; i++) {
    for (int j = 0; j < 5 && !collision; j++) {
      if (game->figure_controller->figure_field[i][j] == 1) {
        int new_x = game->figure_controller->corner_x + j;
        int new_y = game->figure_controller->corner_y + i;

        if (new_x < 0 || new_x >= 10 || new_y > 22 ||
            game->game_info.field[new_y][new_x]) {
          collision = 1;
        }
      }
    }
  }
  if (collision) {
    game->figure_controller->corner_x = old_x;
    game->figure_controller->corner_y = old_y;
  }

  if (collision && direction == Down) {
    code = 1;
  }
  return code;
}

/**
 * @brief поворот фигуры c SRS
 */
void RotateFigure(TetrisGameData* game) {
  int** temp = InitField(5, 5);
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      temp[j][5 - 1 - i] = game->figure_controller->figure_field[i][j];

  // Новый порядок: сначала слабые сдвиги, потом сильные
  int offsets[7][2] = {
      {0, 0},   // без смещения
      {1, 0},   // вправо 1
      {-1, 0},  // влево 1
      {2, 0},   // вправо 2
      {-2, 0},  // влево 2
      {0, -1},  // вверх
      {0, 1},   // вниз
  };
  int code = 1;
  for (int test = 0; test < 7 && code; test++) {
    int x_offset = offsets[test][0];
    int y_offset = offsets[test][1];
    int can_rotate = 1;

    // Проверяем, можно ли повернуть с этим смещением
    for (int i = 0; i < 5 && can_rotate; i++) {
      for (int j = 0; j < 5 && can_rotate; j++) {
        if (temp[i][j]) {
          int new_x = game->figure_controller->corner_x + j + x_offset;
          int new_y = game->figure_controller->corner_y + i + y_offset;

          if (new_x < 0 || new_x >= 10 || new_y < 0 || new_y >= 23 ||
              game->game_info.field[new_y][new_x]) {
            can_rotate = 0;
          }
        }
      }
    }

    // Если можно - применяем поворот и выходим
    if (can_rotate) {
      
      for (int i = 0; i < 5; i++) {
        memcpy(game->figure_controller->figure_field[i], temp[i],
               5 * sizeof(int));
      }
      game->figure_controller->corner_x += x_offset;
      game->figure_controller->corner_y += y_offset;
      code = 0;
    }
  }
  FreeField(temp, 5);
}

/**
 * @brief выбор новой следующей фигуры
 */
void NewNextFigure(TetrisGameData* game) {
  const int shapes[7][5][5] = {// L
                               {{0, 0, 0, 0, 0},
                                {0, 0, 1, 0, 0},
                                {0, 0, 1, 0, 0},
                                {0, 0, 1, 1, 0},
                                {0, 0, 0, 0, 0}},
                               // J
                               {{0, 0, 0, 0, 0},
                                {0, 0, 1, 0, 0},
                                {0, 0, 1, 0, 0},
                                {0, 1, 1, 0, 0},
                                {0, 0, 0, 0, 0}},
                               // O
                               {{0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0},
                                {0, 0, 1, 1, 0},
                                {0, 0, 1, 1, 0},
                                {0, 0, 0, 0, 0}},
                               // S
                               {{0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0},
                                {0, 0, 1, 1, 0},
                                {0, 1, 1, 0, 0},
                                {0, 0, 0, 0, 0}},
                               // Z
                               {{0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0},
                                {0, 1, 1, 0, 0},
                                {0, 0, 1, 1, 0},
                                {0, 0, 0, 0, 0}},
                               // I
                               {{0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0},
                                {0, 1, 1, 1, 1},
                                {0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0}},
                               // T
                               {{0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0},
                                {0, 0, 1, 0, 0},
                                {0, 1, 1, 1, 0},
                                {0, 0, 0, 0, 0}}};

  int shape_id = rand() % 7;
  for (int i = 0; i < 5; i++) {
    memset(game->game_info.next[i], 0, 5 * sizeof(int));
    memcpy(game->game_info.next[i], shapes[shape_id][i], 5 * sizeof(int));
  }

  int rotations = rand() % 4;
  for (int r = 0; r < rotations; r++) {
    int** temp = InitField(5, 5);

    for (int i = 0; i < 5; i++)
      for (int j = 0; j < 5; j++)
        temp[j][5 - 1 - i] = game->game_info.next[i][j];

    for (int i = 0; i < 5; i++)
      for (int j = 0; j < 5; j++) game->game_info.next[i][j] = temp[i][j];

    FreeField(temp, 5);
  }
  game->figure_controller->corner_x = 3;
  game->figure_controller->corner_y = 0;
}

/**
 * @brief создание новой фигуры
 */
void SpawnFigure(TetrisGameData* game) {
  for (int i = 0; i < 5; ++i) {
    memcpy(game->figure_controller->figure_field[i], game->game_info.next[i],
           5 * sizeof(int));
  }
  NewNextFigure(game);
}

/**
 * @brief проверка на заполнение верхней строки
 */
int TopLineFill(TetrisGameData* game) {
  int code = 0;
  for (int i = 0; i < 10 && !code; i++) {
    if (game->game_info.field[3][i] != 0) {
      code = 1;
    }
  }
  return code;
}

/**
 * @brief установка паузы
 */
void SetPause(TetrisGameData* game) {
  gettimeofday(&game->pause_time, NULL);
  game->game_info.pause = 1;
}

/**
 * @brief снятие паузы
 */
void UnsetPause(TetrisGameData* game) { game->game_info.pause = 0; }

/**
 * @brief загрузка рекорда
 */
void LoadHighScore(int* high_score) {
  int code = 1;
  FILE* file = fopen("tetris_score.txt", "a+");
  if (file == NULL) {
    code = 0;
  }

  if (code) {
    rewind(file);
    int c = fgetc(file);
    if (c == EOF) {
      *high_score = 0;
    } else {
      ungetc(c, file);
      int result = fscanf(file, "%d", high_score);
      if (result != 1) {
        *high_score = 0;
      }
    }
    fclose(file);
  }
}

/**
 * @brief сохранение рекорда
 */
void SaveHighScore(TetrisGameData* game) {
  int code = 1;
  FILE* file = fopen("tetris_score.txt", "w");
  if (file == NULL) {
    code = 0;
  }

  if (code) {
    fprintf(file, "%d\n", game->game_info.high_score);
    fclose(file);
  }
}

/**
 * @brief инициализация поля в памяти
 */
int** InitField(int x, int y) {
  int** field = NULL;
  int code = 1;
  field = (int**)malloc(y * sizeof(int*));
  if (field == NULL) {
    code = 0;
  }
  if (code)
    for (int i = 0; i < y && code; ++i) {
      field[i] = (int*)malloc(x * sizeof(int));
      if (field[i] == NULL) {
        for (int j = 0; j < i; ++j) {
          free(field[j]);
        }
        free(field);
        code = 0;
      }
    }

  if (code)
    for (int i = 0; i < y; i++) {
      for (int j = 0; j < x; j++) {
        field[i][j] = 0;
      }
    }

  if (!code) {
    field = NULL;
  }
  return field;
}

/**
 * @brief освобождение памяти
 */
int** FreeField(int** field, int size) {
  for (int i = 0; i < size; i++) free(field[i]);
  free(field);
  field = NULL;
  return field;
}