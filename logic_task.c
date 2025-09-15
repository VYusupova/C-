/*Задача
на  stdin числа x, y и z
каждое из которых может  принимать одно из 2-х значений 0 или 1
вывести на stdout единицу, если значение выражения истино
выражение :  x and (z or y)
в противном случае вывести ноль.
В конце ответа не должно быть переноса на новую строку
в случае любой ошибки вывести n\a
*/

#include <stdio.h>

/*тестовые строки
0 0 0
0 0 1
0 1 0
0 1 1
1 0 0
1 0 1
1 1 0
1 1 1
*/

static int valid_scan(int *x) {
  int result = 1;
  if (1 == scanf("%d", x)) {
    if ((*x == 0) || (*x == 1))
      result = 1;
    else
      result = 0;
  } else
    result = 0;
  return result;
}

int main() {
  int x = 0;
  int y = 0;
  int z = 0;
  if (valid_scan(&x)) {
    if (valid_scan(&y)) {
      if (valid_scan(&z)) {
        printf("%d", (x & (y | z)));
      } else
        printf("n/a");
    } else
      printf("n/a");
  } else
    printf("n/a");
}
