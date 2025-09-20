#include "include/controller.h"

#include <stdio.h>

/**
 * @file controller.c
 * @brief контроллер с FSM
 *
 */

/**
 * @brief возврат текущего состояния FSM контроллера
 */
GameState* GetControllerState() {
  static GameState current_state = START;
  return &current_state;
}

/**
 * @brief обработка события завершения игры
 */
void HandleTerminate() {
  SetPause(GetData());
  *GetControllerState() = QUIT;
  SaveHighScore(GetData());
  QuitGame(GetData());
}

/**
 * @brief начало новой игры
 */
void StartNewGame() {
  SaveHighScore(GetData());
  NewGame(GetData());
  NewNextFigure(GetData());
  SpawnFigure(GetData());
  *GetControllerState() = PLAY;
}

/**
 * @brief обработка столкновения фигуры с другими фигурами
 */
void HandleCollision() {
  PlaceFigure(GetData()->game_info.field, GetData()->figure_controller);
  CheckLinesAddScore(GetData());
  if (TopLineFill(GetData())) {
    *GetControllerState() = GAME_OVER;
    SaveHighScore(GetData());
    GameOver(GetData());
  } else {
    SpawnFigure(GetData());
    NewNextFigure(GetData());
  }
}

/**
 * @brief получение информации о текущем состоянии игры и обновленпие
 */
GameInfo_t GetGameData() {
  TetrisGameData* data = GetData();
  GameInfo_t game_info = CollectGameData(data);

  if (*GetControllerState() == PLAY) {
    ShowFigure(game_info.field, data->figure_controller);
    if (ProcessTimer(GetData())) {
      if (MoveFigure(GetData(), Down)) {
        HandleCollision();
      }
    }
  }
  return game_info;
}

/**
 * @brief обработка события паузы
 */
void ProcessPause(UserAction_t input) {
  switch (input) {
    case Terminate:
      HandleTerminate();
      break;
    case Pause:
      UnsetPause(GetData());
      *GetControllerState() = PLAY;
      break;
    case Start:
      StartNewGame();
      break;
    default:
      break;
  }
}

/**
 * @brief обработка события движения фигуры
 */
void ProcessAction(UserAction_t input) {
  switch (input) {
    case Left:
    case Right:
    case Down:
      if (MoveFigure(GetData(), input)) {
        HandleCollision();
      }
      break;
    case Action:
      RotateFigure(GetData());
      break;
    case Start:
      StartNewGame();
      break;
    case Pause:
      SetPause(GetData());
      *GetControllerState() = PAUSE;
      break;
    default:
      break;
  }
}

/**
 * @brief обработка события ввода
 */
void ProcessInput(UserAction_t input) {
  if (input == Terminate) {
    HandleTerminate();
    return;
  }

  switch (*GetControllerState()) {
    case START:
    case GAME_OVER:
      if (input == Start) {
        StartNewGame();
      }
      break;
    case PLAY:
      ProcessAction(input);
      break;
    case PAUSE:
      ProcessPause(input);
    default:
      break;
  }
}