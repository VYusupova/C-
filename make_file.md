# лучшие практики из проектов 
## 1.  цели
> простое написание `make` в командной строке выполняет первую цель в файле, в большинстве случаев это цель all, но если поставить любую другую цель первой, то выполнена будет она  

### удобно задавать цель с автоподстановкой.   

<details>
<summary> Например:    </summary> 
	
```make
OBJS_FILE :=  stack.o # тут перечислим файлы а цель %.o скомпилирует их пооочереди из файлов %.cpp
                      # %.o: и stack.o:  будут делать одно и тоже
all : OBJS_FILE

%.o: %.cpp %.h
	$(CC) $(CFLAGS) -c $< -o $@

stack.o: s21_stack.h
	$(CC) $(CFLAGS) s21_stack.сpp  -o stack.o
```
</details>  

###  выделение цели под создание папки для библиотеки 

```make
stack: $(DIR_LIB)
	$(CC) $(CFLAGS) -c $@/$@.c  -o $@/$@.o
	ar rcs $(DIR_LIB)/lib$@.a $@/$@.o $@/$@.h
	@printf " ✅ stack.a created in directory [$(DIR_LIB)] \n\n"

$(DIR_LIB):
	@if [ -d $@ ]; then printf " ✅ directory [$@] - exists  \n" ;\
	else mkdir -p $@ ; \
	printf " ✅ directory [$@] - created  \n" ; \
	fi
```


## 2. вывод в консоль информации
 в целях можно делать с помощью команд `echo` или `printf`  

`@printf " ✅ lib/stack.a created in catalog [$(DIR_LIB)] \n\n"`
  > `@` перед `printf` - значит что сам `printf` не будет выведен  в консоль без `@` `printf`  продублируется в консоль

можно задавать цвета какими выводть :  

`@printf "\e[1;35;107m  Отчет покрытия кода в 'gcov/index.html' ┃\e[31;0m   📊 \n"`  
  
или  
  
```make
 	@echo"\e[1;35;107m" 											# серые буквы на белом фоне
	@echo "┃  Отчет покрытия кода создан в 'gcov/index.html' ┃"
	@echo "\e[0;30m"												# стави обратно по дефолту
```

## CPPCHECK

```make

CPPCHECK = -q --enable=all --inconclusive --suppress=missingIncludeSystem --check-level=exhaustive 
# --check-level=exhaustive  Ограничивающий анализ ветвей. Используйте --check-level=исчерпывающий для анализа всех ветвей. 
# Параметр --enable=all в инструменте CppCheck включает все возможные проверки
# Параметр --suppress переводится как подавлять, т.е. --suppress=missingIncludeSystem не будет писать в ошибки если не найдена какая то библиотека
all : lib
# Параметр -q означает «тихий» режим — выводятся только сообщения об ошибках, а не ход выполнения на экране.
# Параметр --inconclusive использовании этой опции возможны ложные срабатывания. Каждый результат должен быть тщательно проанализирован, прежде чем вы узнаете, хороший он или плохой.
```
## valgrind

valgrind --tool=memcheck --leak-check=yes --track-origins=yes

## n. Разности


- [ ] `-c` -  этот флаг нужен когда в файле нет функции main
- [ ] `.PHONY:` нужна для того что бы если например есть такой же файл по имени как и цель, то без описания этой цели в  `.PHONY` цель не будет работать
- [ ] `rm -r LIB` - удалить директорию и все ее содержимое рекурсивно `-r`  
- [ ] `mv $(NAME).o LIB/$(NAME)`  
- [ ] `mkdir -p LIB`

