.PHONY: all clean test  s21_graph s21_graph_algorithms s21_stack console

CC := gcc
CFLAGS := -std=c11 -Wall -Werror -Wpedantic
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
CHECK_LIBS = $(shell pkg-config --libs check) #-lcheck -lm -lpthread -lrt -lsubunit

CPPCHECK =  --enable=all --inconclusive --suppress=missingIncludeSystem --check-level=exhaustive #-q

NAME := SimpleNavigator
DIR_LIB := library
LIB_GRAPH := s21_graph
LIB_GRAPH_ALG = s21_graph_algorithms
TEST = run_tests

	# что бы подключать библиоктеки надо что бы все они создавались с префиксом lib
	# например libs21_graph.a
	# компиляция конечного файла описана https://firststeps.ru/linux/r.php?5
	# обязательно надо делать в два этапа 1 этап compile объектный файл, а
	# затем уже его компилить с подключением библиотек
LIB_ADD := -L ./$(DIR_LIB) -ls21_graph -ls21_graph_algorithms -ls21_stack -ls21_queue

all: clean s21_graph s21_graph_algorithms s21_stack s21_queue

clean:
	$(RM) $(TEST) $(LIB_GRAPH)  $(LIB_GRAPH_ALG) *.o */*.o
	rm -rf $(DIR_LIB)
	rm -rf test/*.gcov.*
	rm -rf gcov/
	rm -rf $(NAME)_coverage.info
	rm -rf run console

test: test/test.gcov.o test/test_graph.gcov.o test/test_algorithms.gcov.o
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $(LIB_GRAPH).c -o  test/$(LIB_GRAPH).gcov.o
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $(LIB_GRAPH_ALG).c -o  test/$(LIB_GRAPH_ALG).gcov.o
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -o $(TEST) test/*.gcov.o   $(LIB_ADD)  $(CHECK_LIBS)
	@printf "\e[1;35;107m RUN FILE TESTING  \e[31;0m \n"
	./$(TEST)
	@printf "\n\e[1;35;107m END FILE TESTING    \e[31;0m \n"
	@printf "\e[1;35;107m  📊 📊 📊 Отчет покрытия кода в 'gcov/index.html' ┃\e[31;0m   📊 📊 📊 \n"
	lcov -t "gcov_report" -o $(NAME)_coverage.info -c -d .
	genhtml -o gcov $(NAME)_coverage.info
	$(RM) test/*.gcov.*

%.gcov.o: %.c
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(LIB_ADD) -c $< -o $@

s21_graph: $(DIR_LIB)
	$(CC) $(CFLAGS) -c $@.c  -o $@.o
	ar rcs $(DIR_LIB)/lib$@.a $@.o $@.h
	@printf " ✅ lib$@.a created in directory [$(DIR_LIB)] \n\n"
	rm -rf *.o

s21_graph_algorithms: $(DIR_LIB)
	$(CC) $(CFLAGS) -c $@.c  -o $@.o -lm
	ar rcs $(DIR_LIB)/lib$@.a $@.o $@.h
	@printf " ✅ lib$@.a created in directory [$(DIR_LIB)] \n\n"
	rm -rf *.o

s21_stack: $(DIR_LIB)
	$(CC) $(CFLAGS) -c $@/$@.c  -o $@/$@.o
	ar rcs $(DIR_LIB)/lib$@.a $@/$@.o $@/$@.h
	@printf " ✅ lib$@.a created in directory [$(DIR_LIB)] \n\n"
	rm -rf *.o

s21_queue: $(DIR_LIB)
	$(CC) $(CFLAGS) -c $@/$@.c  -o $@/$@.o
	ar rcs $(DIR_LIB)/lib$@.a $@/$@.o
	@printf " ✅ lib$@.a created in directory [$(DIR_LIB)] \n\n"
	rm -rf *.o

$(DIR_LIB):
	@if [ -d $@ ]; then printf " ✅ directory [$@] - exists  \n" ;\
	else mkdir -p $@ ; \
	printf " ✅ directory [$@] - created  \n" ; \
	fi

console: s21_graph s21_graph_algorithms s21_stack s21_queue
	$(CC) $(CFLAGS) -c part5_console_interface/console_interface.c -o $@ -lm
	$(CC) $(CFLAGS) $@  $(LIB_ADD)  -o run -lm
	./run

clang:
	clang-format -i */*.h *.h */*.c *.c

cppcheck:
	@printf "\n 🔧🔧🔧 CHECK FILE 🔧🔧🔧 \n"
	cppcheck $(CPPCHECK) */*.c  *.c

valgrind:
	valgrind --leak-check=full --track-origins=yes ./$(TEST) $(GTEST_LIB)

