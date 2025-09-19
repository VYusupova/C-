#include <dlfcn.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/library_spec.h"

typedef void (*UserInputFunc)(UserAction_t, bool);
typedef GameInfo_t (*UpdateCurrentStateFunc)(void);
typedef void (*StartWindowsFunc)(UserInputFunc, UpdateCurrentStateFunc);

void print_menu() {
  printf("Выберите игру:\n");
  printf("1. Змейка\n");
  printf("2. Тетрис\n");
  printf("3. Выход\n");
  printf("Ваш выбор: ");
}
int main() {
  int game_choice, interface_choice;
  void *game_handle = NULL, *front_handle = NULL;
  UserInputFunc userInput = NULL;
  UpdateCurrentStateFunc updateCurrentState = NULL;
  StartWindowsFunc startWindows = NULL;
  char *error;
  int should_exit = 0;
  int input_valid;

  do {
    print_menu();
    
    // Считываем только выбор игры
    input_valid = scanf("%d", &game_choice);
    while(getchar() != '\n'); // Очищаем буфер ввода
    
    if (input_valid != 1) {
      fprintf(stderr, "Неверный ввод\n");
      continue;
    }

    if (game_choice == 3) {
      should_exit = 1;
      continue;
    }

    // Проверяем валидность выбора игры
    if (game_choice != 1 && game_choice != 2) {
      fprintf(stderr, "Неподдерживаемая игра\n");
      continue;
    }

    // Загрузка библиотеки игры
    const char* game_lib = (game_choice == 1) ? "./lib/libsnake_back.so" : "./lib/libtetris_back.so";
    game_handle = dlopen(game_lib, RTLD_LAZY);
    if (!game_handle) {
      fprintf(stderr, "Ошибка загрузки %s: %s\n", game_lib, dlerror());
      should_exit = 1;
      continue;
    }

    // Получаем указатели на функции игры
    userInput = (UserInputFunc)dlsym(game_handle, "userInput");
    updateCurrentState = (UpdateCurrentStateFunc)dlsym(game_handle, "updateCurrentState");
    if ((error = dlerror()) != NULL) {
      should_exit = 1;
      fprintf(stderr, "Ошибка загрузки функций игры: %s\n", error);
      dlclose(game_handle);
      continue;
    }

    // Теперь запрашиваем выбор интерфейса
    printf("Выберите интерфейс (1 - ncurses, 2 - qt): ");
    input_valid = scanf("%d", &interface_choice);
    while(getchar() != '\n'); // Очищаем буфер ввода
    
    if (input_valid != 1 || (interface_choice != 1 && interface_choice != 2)) {
      fprintf(stderr, "Неподдерживаемый интерфейс\n");
      dlclose(game_handle);
      continue;
    }

    // Загрузка библиотеки интерфейса
    const char* front_lib = (interface_choice == 1) ? "./lib/libncurses_front.so" : "./lib/libqt_front.so";
    if (interface_choice == 2) {
      fprintf(stderr, "Attempting to load libqt-front.so\n");
    }
    
    front_handle = dlopen(front_lib, RTLD_LAZY);
    if (!front_handle) {
      should_exit = 1;
      fprintf(stderr, "Ошибка загрузки %s: %s\n", front_lib, dlerror());
      dlclose(game_handle);
      continue;
    }

    // Получаем указатель на функцию интерфейса
    startWindows = (StartWindowsFunc)dlsym(front_handle, "startWindows");
    if ((error = dlerror()) != NULL) {
      should_exit = 1;
      fprintf(stderr, "Ошибка загрузки startWindows: %s\n", error);
      dlclose(game_handle);
      dlclose(front_handle);
      continue;
    }

    // Запуск интерфейса
    if (startWindows) {
      startWindows(userInput, updateCurrentState);
    }

    // Освобождение ресурсов
    if (game_handle) dlclose(game_handle);
    if (front_handle) dlclose(front_handle);

  } while (!should_exit);

  return 0;
}