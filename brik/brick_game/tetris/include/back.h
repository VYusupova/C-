#ifndef BACK_H
#define BACK_H

#include <sys/time.h>
#include <time.h>

#include "../../../include/library_spec.h"

typedef struct {
  int corner_x, corner_y;
  int** figure_field;
} Figure;

typedef struct {
  GameInfo_t game_info;
  GameInfo_t copy_to_share;
  Figure* figure_controller;
  struct timeval last_tick;
  struct timeval pause_time;
  int initialized;
} TetrisGameData;

GameInfo_t CollectGameData(TetrisGameData* game);
void CheckLinesAddScore(TetrisGameData* game);
void NewGame(TetrisGameData* game);
void SetPause(TetrisGameData* game);
void UnsetPause(TetrisGameData* game);
int MoveFigure(TetrisGameData* game, UserAction_t direction);
void RotateFigure(TetrisGameData* game);
void QuitGame(TetrisGameData* game);
int ProcessTimer(TetrisGameData* game);
TetrisGameData* GetData();
void SaveHighScore(TetrisGameData* game);
int TopLineFill(TetrisGameData* game);
void SpawnFigure(TetrisGameData* game);
void NewNextFigure(TetrisGameData* game);
void GameOver(TetrisGameData* game_data);
void PlaceFigure(int** field, Figure* f_controller);
void ShowFigure(int** field, Figure* f_controller);
#endif  // BACK_H