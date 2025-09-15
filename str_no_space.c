/*Задача на работу со строками
   на вход подается строка ее надо отформатировать так что бы
   не было пробелов вначале и конце строки
   между словами по одному пробелу  */

#include <stdio.h>
#include <stdlib.h>

static void print_str(const char* str) {
  int i = 0;
  char space = ' ';
  // посчитаем длину строки
  while (str[i] != '\0') {
    if (str[i] == '\n') break;
    i++;
  }
  //  выделим память под новую строку

  char* out = NULL;
  /*под результирующую строку надо выделить на один симво больше
  так можно избежать ситуации когда в веденной строке нечего будет удалять
  */
  if (i > 0) out = malloc((i + 1) * sizeof(char));
  if (out == NULL) return;
  i = 0;
  int j = 0;
  // пропустим начальные пробелы
  while (str[i] == space) {
    i++;
  }
  while (str[i] != '\0') {
    if (str[i] == '\n') break;
    if (space == str[i] && str[i - 1] == space) {
    } else {
      out[j] = str[i];
      j++;
    }
    i++;
  }
  if (out[j - 1] == space)
    out[j - 1] = '\0';
  else /*без конструкции else будет ошибка valgrind*/
    out[j] = '\0';
  printf("%s", out);
  free(out);
}
/*
test string norm
test    string     space normal
test    string     last space
     test string norm and start space
      test      string      start     space
*/
int main() {
  char* str = NULL;
  size_t len = 0;
  size_t read = getline(&str, &len, stdin);
  if (read != (unsigned long int)-1) {
    if (str != NULL) {
      // printf("%s",str);
      printf("<");
      print_str(str);
      printf(">");
      free(str);
    }
  } else {
    printf("Error");
  }
}
