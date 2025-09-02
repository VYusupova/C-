/*  Консольный интерфейс

консольное приложение для проверки работоспособности реализованных библиотек s21_graph и s21_graph_algorithms.
Содержит функционал:

1. Загрузка исходного графа из файла.
2. Обход графа в ширину с выводом результата обхода в консоль.
3. Обход графа в глубину с выводом результата обхода в консоль.
4. Поиск кратчайшего пути между произвольными двумя вершинами с выводом результата в консоль.
5. Поиск кратчайших путей между всеми парами вершин в графе с выводом результирующей матрицы в консоль.
6. Поиск минимального остовного дерева в графе с выводом результирующей матрицы смежности в консоль.
7. Решение задачи коммивояжера с выводом результирующего маршрута и его длины в консоль.

*/

#include "../s21_graph.h"
#include "../s21_graph_algorithms.h"
#include <stdio.h>

#define PRINT_CHOOSE \
  printf("ВЫБОР ДЕЙСТВИЯ: \n"); \
  printf("\t1. Загрузка исходного графа из файла.\n"); \
  printf("\t2. Обход графа в ширину с выводом результата обхода в консоль.\n"); \
  printf("\t3. Обход графа в глубину с выводом результата обхода в консоль.\n"); \
  printf("\t4. Поиск кратчайшего пути между произвольными двумя вершинами с выводом результата в консоль.\n"); \
  printf("\t5. Поиск кратчайших путей между всеми парами вершин в графе с выводом результирующей матрицы в консоль.\n"); \
  printf("\t6. Поиск минимального остовного дерева в графе с выводом результирующей матрицы смежности в консоль.\n"); \
  printf("\t7. Решение задачи коммивояжера с выводом результирующего маршрута и его длины в консоль.\n")

#define PRINT_QUESTION \
  printf("ВЫВЕСТИ ГРАФ на консоль в формате: \n"); \
  printf("\t1. матрицы смежности\n"); \
  printf("\t2. dot\n"); \
  printf("\tany key. без вывода\n") 

#define PRINT_LOAD_GRAP  printf("введите путь и  имя файла c графом : ")
#define ERR_PRINT_LOAD_GRAP printf("ERRORне удалось считать, неправильные прараметры в файле\n")
#define ERR printf("ERROR что то пошло не так\n")
/*
static void print_choose_option(){
  printf("ВЫБОР ДЕЙСТВИЯ: \n");
  printf("\t1. Загрузка исходного графа из файла.\n");
  printf("\t2. Обход графа в ширину с выводом результата обхода в консоль.\n");
  printf("\t3. Обход графа в глубину с выводом результата обхода в консоль.\n");
  printf("\t4. Поиск кратчайшего пути между произвольными двумя вершинами с выводом результата в консоль.\n");
  printf("\t5. Поиск кратчайших путей между всеми парами вершин в графе с выводом результирующей матрицы в консоль.\n");
  printf("\t6. Поиск минимального остовного дерева в графе с выводом результирующей матрицы смежности в консоль.\n");
  printf("\t7. Решение задачи коммивояжера с выводом результирующего маршрута и его длины в консоль.\n");
}
*/
  
static void question_print(s21_graph *g){
   PRINT_QUESTION;
   int user_input;
  scanf("%d", &user_input);
  switch (user_input) {
    case 1:
      g->print_graph_matrix(g);
      break;
    case 2:
      //g->print_graph_dot(g);
      break;
    default:
      break;
  }
}


static void load_grap(s21_graph *g){
      PRINT_LOAD_GRAP;
      char * filename = NULL;
      size_t len = 0;
      size_t read = getline( & str, & len, stdin);
      printf("\n");
      if (read != (unsigned long int)-1) {
        g->load_graph_from_file(filename, g);
        if (g->size == 0)  ERR_PRINT_LOAD_GRAP;
        else question_print(g);
      }
      else ERR;
    }

static void print_DFS(s21_graph *g){
  int *visit;
      if (g->size == 0 ){
         printf("граф пустой! загрузите граф, потом может построю обход =)\n");
      }
  else { 
    printf("введите чило от 0 до %d вершину с которой надо начать обход :", g->size);
    int vertex = 0;
    if (1 != scanf("%d", &vertex)) {
      printf("ты ввел какую-то ерунду, поэтому вершина с которой я начну будет 0");
     }
    else {
      if (vertex > g->size) {
        printf("ты ввел какую-то ерунду, поэтому вершина с которой я начну будет 0");
      }
      else {
        visit = depth_first_search(g, 0);
      }
      
    }
        printf("обход графа { ");
  for (int i = 0; i < g->size; i++)
    printf("%d  ", visit[i]);
  printf(" }\n");
  }
  
}

void  console(s21_graph *g) {
  int user_input;
  PRINT_CHOOSE;
  // print_choose_option();
  scanf("%d", &user_input);
  switch (user_input) {
    case 1:
      load_grap(g);
      break;
    case 2:
       print_DFS(g);
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:
      break;
    case 7:
      break;
  }
}




int main() {
  s21_graph g = graph_init();
  g.load_graph_from_file("test/file_test/t_2_load_export.txt", &g);
  printf("size graph %d\n", g.size);
  g.print_graph_matrix(&g);

  

  g.del_graph(&g);
  printf("size graph %d\n", g.size);
  
  int break_flag = 0; // TO DO переделать
  while (break_flag != 3) {
    console(&g);
    break_flag++;
  }

  return 0;
}


