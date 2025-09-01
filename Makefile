.PHONY: all clean test  s21_graph s21_graph_algorithms stack console

CC := gcc
CFLAGS := -std=c11 -Wall -Werror -Wpedantic
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
CHECK_LIBS = $(shell pkg-config --libs check) #-lcheck -lm -lpthread -lrt -lsubunit

CPPCHECK = -q --enable=all --inconclusive --suppress=missingIncludeSystem --check-level=exhaustive

NAME := SimpleNavigator
DIR_LIB := library
LIB_GRAPH := s21_graph
LIB_GRAPH_ALG = s21_graph_algorithms
TEST = run_tests

all: clean s21_graph s21_graph_algorithms

clean:
	$(RM) $(TEST) $(LIB_GRAPH)  $(LIB_GRAPH_ALG) *.o
	rm -rf $(DIR_LIB)
	rm -rf test/*.gcov.*
	rm -rf gcov/
	rm -rf $(NAME)_coverage.info

test: test/test.gcov.o test/test_graph.gcov.o
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $(LIB_GRAPH).c -o  test/$(LIB_GRAPH).gcov.o
	#$(CC) $(CFLAGS) $(GCOV_FLAGS) -c test/test.c -o  test/test.gcov.o
	#$(CC) $(CFLAGS) $(GCOV_FLAGS) -c test/test_graph.c -o  test/test_graph.gcov.o
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -o $(TEST) test/*.gcov.o   $(CHECK_LIBS)
	@printf "\e[1;35;107m RUN FILE TESTING  \e[31;0m \n"
	./$(TEST)
	@printf "\n\e[1;35;107m END FILE TESTING    \e[31;0m \n"
	@printf "\e[1;35;107m  Отчет покрытия кода в 'gcov/index.html' ┃\e[31;0m   📊 \n"
	lcov -t "gcov_report" -o $(NAME)_coverage.info -c -d .
	genhtml -o gcov $(NAME)_coverage.info
	$(RM) test/*.gcov.*

%.gcov.o: %.c
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $< -o $@

s21_graph: $(DIR_LIB)
	$(CC) $(CFLAGS) -c $@.c  -o $@.o
	ar rcs $(DIR_LIB)/lib$@.a $@.o $@.h
	@printf " ✅ $@.a created in directory [$(DIR_LIB)] \n\n"

s21_graph_algorithms: $(DIR_LIB)
	$(CC) $(CFLAGS) -c $@.c  -o $@.o
	ar rcs $(DIR_LIB)/lib$@.a $@.o $@.h
	@printf " ✅ $@.a created in directory [$(DIR_LIB)] \n\n"

stack: $(DIR_LIB)
	$(CC) $(CFLAGS) -c $@/$@.c  -o $@/$@.o
	ar rcs $(DIR_LIB)/lib$@.a $@/$@.o $@/$@.h
	@printf " ✅ stack.a created in directory [$(DIR_LIB)] \n\n"

$(DIR_LIB):
	@if [ -d $@ ]; then printf " ✅ directory [$@] - exists  \n" ;\
	else mkdir -p $@ ; \
	printf " ✅ directory [$@] - created  \n" ; \
	fi

	# что бы подключать библиоктеки надо что бы все они создавались с префиксом lib
	# например libs21_graph.a
	# компиляция конечного файла описана https://firststeps.ru/linux/r.php?5
	# обязательно надо делать в два этапа 1 этап полчеть объектный файл, а
	# затем уже его компилить с подключением библиотек
console: s21_graph
	$(CC) $(CFLAGS) -c part5_console_interface/console_interface.c  -L/$(DIR_LIB) -ls21_graph  -I $(DIR_LIB) -o $@
	$(CC) $(CFLAGS) $@ -L/$(DIR_LIB) -ls21_graph -o run
	./run


clang:
	clang-format -n */*.h *.h

cppcheck:
	@printf "\n 🔧🔧🔧 CHECK FILE 🔧🔧🔧 \n"
	cppcheck $(CPPCHECK) */*.c */*.h *.c *.h

