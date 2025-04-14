CC := gcc
CFLAGS := -I inc -std=c11 -Wall -Werror -Wpedantic
OBJS_FSMSWITCHCASE :=  out/frogger.o out/fsm.o out/backend.o out/frontend.o  out/brick_game/tetris_init.o out/brick_game/tetris_moving.o
OBJS_FSMTABLE := out/frogger.o out/fsm_matrix.o out/backend.o out/frontend.o

GCOV_FLAGS = -fprofile-arcs -ftest-coverage
PATH_TEST = test
TEST_BIN = run_tests
CHECK_LIBS = -lcheck -lm -pthread -lrt -lsubunit

all: clean mkdir frogger

frogger:  $(OBJS_FSMSWITCHCASE)
	clang-format -i src/*.c
	$(CC) $(CFLAGS) $^ -o $@ -lncurses

frogger_fsmtable: $(OBJS_FSMTABLE)
	$(CC) $(CFLAGS) $^ -o $@ -lncurses

out/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

mkdir:
	mkdir out/brick_game/

clean:
	$(RM) out/*.o frogger frogger_fsmtable
	rm -rf out/brick_game/

.PHONY: clean

test_file:
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c src/test/test.c -o  src/test/tests.gcov.o

test: test_file
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -o $(TEST_BIN) src/test/*.gcov.o out/brick_game/tetris_init.o  $(CHECK_LIBS)
	@printf "\e[1;35;107m RUN FILE TESTING  \e[31;0m \n"
	./$(TEST_BIN)
	@printf "\n\e[1;35;107m END & DEL FILE TESTING    \e[31;0m \n"


# $^ это набор зависимых файлов, используемых для создания чего-то другого.
# $@ это имя цели, которая будет построена.

# $(RM) - переменная в Makefile. Существуют явные переменные (которые определяются внутри Makefile) и неявные переменные (определяются make и могут быть переопределены вами)
# Вы можете увидеть список неявных переменных с этим флагом: make -p
# Некоторые из наиболее распространённых переменных можно найти по адресу: 10.3 Переменные, используемые неявными правилами
# Вы можете развернуть переменную с помощью следующего синтаксиса $(NAME) или ${NAME}

