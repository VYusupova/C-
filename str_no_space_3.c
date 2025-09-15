/*Задача на работу со строками
   на вход подается строка ее надо отформатировать так что бы
   не было пробелов вначале и конце строки
   между словами по одному пробелу  */
/* 3й вариант с ипользованием конструкции     scanf("%ms", &str);
не работающий не доработанный цикл бесконечный*/
#include <stdio.h>
#include <stdlib.h>

int main() {
  char* str = NULL;
  printf("<");
  scanf("%ms", &str);
  if (str != NULL) printf("%s", str);
  while (1) {
    if (str == NULL) break;
    printf(" %s", str);
    free(str);
    if (0 == scanf("%ms", &str)) break;
    int i = 0;
    while (str[i] != '\0') {
      if (str[i] == '\n') printf("str[i]");
      i++;
    }
    if (str[0] == '\0') break;
  }
  free(str);
  printf(">");
}
