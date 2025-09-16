/*Задача про телефонный справочние Exam_01_05 Уровень 4
Напиши телефонный справочник который выводить
данные о контактах построчно храняться в текстовом файле, путь до которго
задается на потоке ввода stdin(относительно корневой директории) и заканчивается
символом новой строки \n
при этом формат хранения данных отличается от необходимого формата вывода
В конце ответа не должно быть переноса на новую строку

входные данне
Smith : 8-950-111-22-23
выходные данные
Smith +7(950)111-22-23
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void out(char *str, int len) {
  int i = 0;
  for (i = 0; i < len; i++) {
    if (str[i] == ':')
      break;
    else
      printf("%c", str[i]);
  }

  int num = 0;
  int n8 = 1;
  for (i++; i < len; i++) {
    if (num == 3) {
      printf(")");
      num++;
      i++;
    }
    if (num == 4)
      printf("%c", str[i]);
    else if (str[i] >= '0' && str[i] <= '9') {
      if (str[i] == '8' && n8) {
        printf("+7(");
        n8 = 0;
      } else {
        printf("%c", str[i]);
        num++;
      }
    }
  }
}

int main() {
  char *filename = (char *)malloc(256 * sizeof(char));
  if (scanf("%256s", filename) != 1)
    printf("n/a");
  else {
    FILE *f = fopen(filename, "r");
    if (f != NULL) {
      char *string = NULL;
      size_t len = 0;
      ssize_t read = 0;
      while ((read = getline(&string, &len, f)) != -1) {
        out(string, read);
      }
      if (string) free(string);
    }
  }
  if (filename) free(filename);
}
