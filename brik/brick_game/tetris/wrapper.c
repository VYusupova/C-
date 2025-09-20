#include <stdio.h>

#include "include/controller.h"

#define UNUSED(x) (void)(x)

/**
 * @file wrapper.c
 * @brief обёртка для контроллера
 *
 */
/**
 * @brief передача пользовательского ввода
 */
void userInput(UserAction_t action, bool hold __attribute__((unused))) { ProcessInput(action); }

/**
 * @brief получение текущего состояния игры
 */
GameInfo_t updateCurrentState() { return GetGameData(); }