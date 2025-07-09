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
## 3. как работать с регулярными выражениями
https://www.opennet.ru/cgi-bin/opennet/man.cgi?topic=regcomp&category=3


https://github.com/rynortheast/21-string/blob/main/src/CORE/s21_strerror.c

https://github.com/lcoon21/s21_string/blob/main/src/s21_strerror.c


## 4. покрасить консоль
1. проверить что файла нет `ls -la`
1.1 он есть в /etc/skel/.bashrc пойти и проверить 1. cd /etc/skel/.bashrc 2. ls -la
2. скопировать его себе `cp /etc/skel/.bashrc ~/`
3. в конец файла добавить строки
```bash
PS1='\[\e[0;32m\]\u\[\e[m\] \[\e[1;34m\]\w\[\e[m\] \[\e[1;32m\]\$\[\e[m\] '
```
### Краткая таблица применяемых цветов:

```bash
'\e[0;30m' # Черный
'\e[0;31m' # Красный
'\e[0;32m' # Зеленый
'\e[0;33m' # Желтый
'\e[0;34m' # Синий
'\e[0;35m' # Фиолетовый
'\e[0;36m' # Бирюзовый
'\e[0;37m' # Белый
```

## 6. Алиасы в консоли

```bash
#My alias в файле .bashrc
alias gst="git status -s"
alias comm="git add . && git commit -m"
alias push="git push origin develop"
alias maze="git push origin lymondka"
#alias ..="cd .."
```

## 6. GIT
0. `git clone`
1. create fork `develop git branch <name>`  OR `git checkout -b <new_branch>`
