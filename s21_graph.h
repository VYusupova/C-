/*
Реализуй библиотеку s21_graph:

Библиотека должна быть разработана языке C.
Код библиотеки должен находиться в папке src в ветке develop.
При написании программы используй стандартный для выбранного языка стиль
написания кода. Оформи решение как статическую библиотеку (s21_graph).
Библиотека должна быть представлена в виде класса graph, который хранит в себе
информацию о графе с помощью матрицы смежности. Размерность матрицы смежности
должна задаваться динамически при инициализации графа (при его загрузке из
файла). Сборка программы должна быть настроена с помощью Makefile со стандартным
набором целей для GNU-программ: all, clean, test, s21_graph. Обеспечь полное
покрытие unit-тестами методов класса graph. Класс graph должен содержать в себе,
по крайней мере, следующие публичные методы: load_graph_from_file(char
*filename) — загрузка графа из файла в формате матрицы смежности;
export_graph_to_dot(char *filename) — выгрузка графа в файл в формате dot (см.
материалы).
*/

#ifndef S21_GRAPH_H
#define S21_GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

#define _ERR_OPEN "ошибка открытия файла"
#define _ERR_READ_SIZE "ошибка чтения из файла размера графа"
#define _ERR_READ_GRAPH "ошибка чтения из файла значений графа"
#define _ERR_CREATE_GRAPH "ошибка выделения памяти под граф"

#define _ERR_SIZE "размер матрицы не может быть меньше 1 или отрицательным"
#define _ERR_CALLOC "ошибка выделения памяти для матрицы графа"

typedef struct graph {
  int **matrix;
  int size;

  void (*print_graph_matrix)(struct graph *g);
  void (*print_graph_dot)(struct graph *g);
  void (*del_graph)(struct graph *g);
  int (*is_digraph)(const struct graph *g);
  void (*load_graph_from_file)(char *filename, struct graph *g);
  int (*export_graph_to_dot)(char *filename, struct graph *g);

} s21_graph;

s21_graph graph_init();
void print_matrix(s21_graph *g);
void print_dot(s21_graph *graph);

#endif
