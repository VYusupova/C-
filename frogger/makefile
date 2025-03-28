CC := gcc
CFLAGS := -I inc -std=c11 -Wall -Werror -Wpedantic
OBJS_FSMSWITCHCASE := out/frogger.o out/fsm.o out/backend.o out/frontend.o  out/tetris.o
OBJS_FSMTABLE := out/frogger.o out/fsm_matrix.o out/backend.o out/frontend.o 

frogger: $(OBJS_FSMSWITCHCASE)
	#clang-format -i src/*.c
	$(CC) $(CFLAGS) $^ -o $@ -lncurses

# $^ это набор зависимых файлов, используемых для создания чего-то другого.
# $@ это имя цели, которая будет построена.

frogger_fsmtable: $(OBJS_FSMTABLE)
	$(CC) $(CFLAGS) $^ -o $@ -lncurses

out/%.o: src/%.c  
	$(CC) $(CFLAGS) -c $< -o $@

out/tetris.o: src/brick_game/tetris.c  # попробуй это сделать под шаблон , т.е ошничек должен положиться в подпапочку Еще надо проверить создаст она подпапку если нет надо ее создать отдельным правилом
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) out/*.o frogger frogger_fsmtable
# $(RM) - переменная в Makefile. Существуют явные переменные (которые определяются внутри Makefile) и неявные переменные (определяются make и могут быть переопределены вами)
# Вы можете увидеть список неявных переменных с этим флагом: make -p
# Некоторые из наиболее распространённых переменных можно найти по адресу: 10.3 Переменные, используемые неявными правилами
# Вы можете развернуть переменную с помощью следующего синтаксиса $(NAME) или ${NAME}

