.PHONY: all clean test  s21_graph s21_graph_algorithms

CC := gcc
CFLAGS := -std=c11 -Wall -Werror -Wpedantic
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
CHECK_LIBS = $(shell pkg-config --libs check) #-lcheck -lm -lpthread -lrt -lsubunit



NAME := SimpleNavigator
DIR_LIB := lib
LIB_GRAPH := s21_graph
LIB_GRAPH_ALG = s21_graph_algorithms

all: clean s21_graph s21_graph_algorithms

clean:
	$(RM) $(LIB_GRAPH)  $(LIB_GRAPH_ALG) 
	rm -rf $(DIR_LIB) $(LIB_GRAPH).o

test:
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c test/$(LIB_GRAPH).c -o  test/$(LIB_GRAPH).gcov.o
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -o $(TEST) test/$(LIB_GRAPH).gcov.o   $(CHECK_LIBS)
	@printf "\e[1;35;107m RUN FILE TESTING  \e[31;0m \n"
	./$(TEST)
	@printf "\n\e[1;35;107m END FILE TESTING    \e[31;0m \n"
	@printf "\e[1;35;107m  Отчет покрытия кода в 'gcov/index.html' ┃\e[31;0m   📊 \n"
	lcov -t "gcov_report" -o $(NAME)_coverage.info -c -d .
	genhtml -o gcov $(NAME)_coverage.info
	$(RM) test/*.gcov.*


s21_graph:

	@if [ -d $(DIR_LIB) ]; then $(CC) $(CFLAGS)  $(LIB_GRAPH).c  -o $(LIB_GRAPH).o ;\
	else mkdir -p $(DIR_LIB) ; \
	$(CC) $(CFLAGS) $(LIB_GRAPH).c -o $(LIB_GRAPH).o ; 	\
	ar rcs  $(LIB_GRAPH).o *.o; 	\
	rm *.o ; 	\
	printf " \n ✅ $(LIB_GRAPH).a created in catalog [$(DIR_LIB)] \n\n" ; \
	fi

s21_graph_algorithms:
	@if [ -d $(DIR_LIB) ]; then $(CC) $(CFLAGS) $(LIB_GRAPH_ALG).c -o $(LIB_GRAPH_ALG).o;\
	else mkdir -p $(DIR_LIB) ; \
	$(CC) $(CFLAGS) $(LIB_GRAPH_ALG).c -o $(LIB_GRAPH_ALG).o; \
	ar rcs  $(LIB_GRAPH_ALG).a *.o; \
	rm *.o ; \
	printf " \n ✅ $(LIB_GRAPH_ALG).a created in catalog [$(DIR_LIB)] \n\n" ; \
	fi
	

dfs: clean
	$(CC) $(CFLAGS) -c stack/stack.c -o stack/stack.o
	$(CC) $(CFLAGS) algoritm_dfs.c stack/stack.o -o dfs
	./dfs 
	
