1. Красим вывод в консоль [Если компиляция не в линукс, то управляющие коды \033 будут другими какими именно я не знаю]
 "\033[31m---test_CREATE_&_REMOVE_&_TRANSPOSE_matrix---\033[0m"

2. генеируем имя файла от текущей даты
```c
  #include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <cstring>
int main()
{
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  const char *format = "maze_%02d-%02d-%02d_%02d%02d%02d";
  int size_format = strlen(format);
  char *name = (char*)malloc(size_format*sizeof(char));
  sprintf(name, format,  tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec)  ;
  printf("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
  printf("%s", name);
}
```
