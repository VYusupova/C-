/*Задача на работу со строками
   на вход подается строка ее надо отформатировать так что бы
   не было пробелов вначале и конце строки
   между словами по одному пробелу  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void drop_space(char *c){
    char space = ' ';
    while (*c == space) {
        *c = getchar();
      }
}

int main() {
  char space = ' ';
  char end = '\n';
  char c;
  printf("<");
  c = getchar();

  if (c == space){
      drop_space(&c);
  }

  while (c != end) {
    if (c == space) {
      drop_space(&c);
       if ( c!= end) printf(" ");
       else break;
    }
    printf("%c", c);
    if ( c!= end) c = getchar();
  }
  printf(">");
}
