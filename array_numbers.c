#include <stdio.h>
#include <stdlib.h>

static void my_realloc(int new_size, int* a) {
  unsigned size = new_size * sizeof(int);
  int* temp = (int*)realloc((void*)a, size);
  if (temp)
    a = temp;
  else {
    free(a);
    a = NULL;
  }
}

/*функция считывания массива целых чисел */

static int* read_arr(int* len) {
  int capacity = 0;
  int* arr = (int*)calloc(capacity, sizeof(int));
  if (NULL == arr) return NULL;
  int a, i = 0;
  while (1 != scanf("%d", &a)) {
    while (getchar() != ' ');
  }
  while (a != -1) {
    /*Признак конца строки -1*/
    arr[i] = a;
    i++;
    if (capacity <= i) {
      my_realloc(capacity + 5, arr);
      if (NULL == arr) return NULL;
    }
    /*Проверка на тот случай если в строке ввода будут символы а не числа
    в цикле очищаем буфер ввода пока не встретим конец строки или пробел*/
    while (1 != scanf("%d", &a)) {
      while (getchar() != ' ');
    }
  }
  *len = i;
  return arr;
}

static void print_arr(const int* arr, int len) {
  for (int i = 0; i < len; i++) {
    printf("%d ", arr[i]);
  }
}
/* стоки для проверки
1 2 3 4 -1
asd 1 2 3 -1
1 2 3 4 dfsd sdfsdfw fhhgfth rggre 5 8 9 -1
1 2 5 d d d3 -1
1 2 3 4 d g gddf 1d 2d3 -1
*/

int main() {
  int len = 5;
  int* arr = read_arr(&len);
  if (arr) {
    print_arr(arr, len);
    free(arr);
  } else
    printf("NOT READ");
  printf("GOOD");
}
