/*Задача
реверс последовательности
написать программу выводящую через пробел в обратном порядке элементы
последовательности, состоящей из целых неотрицательных чисел
*/

#include <stdio.h>
#include <stdlib.h>

/* тестовые данные
1 2 3 -1
1 2 3 4 5 6 7 8 9 d4 4d d4d 1 2 3 -1

dd ddfs dsgfdf j k l ; h g f o 1 5 9 -1
*/

int main() {
  int a = 0;
  int i = 0;
  int size = 10;
  int *array = malloc(size * sizeof(int));
  if (array) {
    while (a != -1) {
      if (1 == scanf("%d", &a)) {
        array[i] = a;
        i++;
        if (i >= size) {
          size = size + 10;
          int *temp = realloc((int *)array, size * sizeof(int));
          if (temp)
            array = temp;
          else {
            free(array);
            printf("n/a");
            break;
          }
        }
      } else {
        while (getchar() != ' ');
        //printf("n/a");
      }
    }
    if (array)
      for (i = i - 2; i >= 0; i--) printf("%d ", array[i]);
    free(array);
  } else
    printf("n/a");
}
