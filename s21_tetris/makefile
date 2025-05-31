NAME := tetris
DIR_GAME := s21_BrickGame
DIR_INSTALL := ~/$(DIR_GAME)/

CC := gcc
CFLAGS := -I inc -std=c11 -Wall -Werror -Wpedantic
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
CHECK_LIBS = $(shell pkg-config --libs check) #-lcheck -lm -lpthread -lrt -lsubunit

#CPPCHECK = --enable=all --suppress=missingIncludeSystem
#CPPCHECK = -q --enable=all --inconclusive
CPPCHECK = --enable=all --check-level=exhaustive --suppress=missingIncludeSystem
# --check-level=exhaustive >>> Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches. [normalCheckLevelMaxBranches]



OBJS_FSMSWITCHCASE :=  out/tetris.o out/fsm.o 
BACK_SRC := brick_game/tetris/
FRONT_SRC := gui/cli/
HEAD_SRC := inc/
BACKEND := out/brick_game/tetris/
FRONTEND := out/gui/cli/
BACK := $(BACKEND)tetris_init.o $(BACKEND)tetris_moving.o $(BACKEND)tetris_score.o
FRONT := $(FRONTEND)tetris_frontend.o

PATH_TEST = test
TEST = run_tests


.PHONY: clean install tetris uninstall

all: clean install

install: mkdir tetris 
ifdef DIR_INSTALL
	@if [ -d $(DIR_INSTALL) ]; then \
	  echo "\n ✅  TETRIS GAME install in catalog $(DIR_INSTALL) >>>" ;\
          install tetris $(DIR_INSTALL) ; 	\
          printf " 🚀 Running tetris game ? [Y/N] > " && read ans && if [ $${ans:-'N'} = 'y' ]; \
          then $(DIR_INSTALL)./tetris; fi \
	  else echo "\ninstall aborted ... " ; \
	       echo "$(DIR_INSTALL) >>> not found catalog" ; \
	fi	
else
	$(error DIR_INSTALL must be set!)
endif


uninstall: clean
	$(RM) $(DIR_INSTALL)tetris
	$(RM) $(DIR_INSTALL)tetris_max_score.txt
	$(RM) $(DIR_INSTALL)readme.dvi

tetris: $(OBJS_FSMSWITCHCASE) $(BACK) $(FRONT)
	#clang-format -i src/*.c
	$(CC) $(CFLAGS) $^ -o $@ -lncurses

out/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

mkdir:
	mkdir -p ~/$(DIR_GAME)
	mkdir -p $(BACKEND)
	mkdir -p $(FRONTEND)

clean:
	$(RM) out/*.o $(NAME)
	rm -rf out/ dvi/ gcov/
	rm -rf *coverage.info
	rm -rf $(TEST)
	$(RM) test/*.gcov.*
	$(RM) *.gcno
	rm -rf tetris_max_score.txt

test_file: 
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c test/test.c -o  test/tests.gcov.o
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $(BACK_SRC)tetris_init.c -o  test/init.gcov.o
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $(BACK_SRC)tetris_score.c -o  test/score.gcov.o
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $(BACK_SRC)tetris_moving.c -o  test/move.gcov.o
	#$(CC) $(CFLAGS) $(GCOV_FLAGS) -c src/tetris.c -o  test/teris.gcov.o
	#$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $(FRONT_SRC)tetris_frontend.c -o  test/front.gcov.o 
	#$(CC) $(CFLAGS) $(GCOV_FLAGS) -c src/fsm.c -o  test/fsm.gcov.o

test: test_file 
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -o $(TEST) test/*.gcov.o   $(CHECK_LIBS)
	@printf "\e[1;35;107m RUN FILE TESTING  \e[31;0m \n"
	./$(TEST)
	@printf "\n\e[1;35;107m END FILE TESTING    \e[31;0m \n"
	

gcov_report: test
	@printf "\e[1;35;107m  📊 Отчет покрытия кода в 'gcov/index.html' ┃\e[31;0m \n"
	lcov -t "gcov_report" -o $(NAME)_coverage.info -c -d . 
	genhtml -o gcov $(NAME)_coverage.info
	$(RM) test/*.gcov.*
	
valgrind: mkdir tetris test
	valgrind --leak-check=full --track-origins=yes ./$(TEST) $(GTEST_LIB)

	
cppcheck:	
	@printf "\n 🔧🔧🔧 CHECK FILE \n"
	cppcheck $(CPPCHECK) *.c $(FRONT_SRC)*.c $(BACK_SRC)*.c $(HEAD_SRC)*.h

dvi:
	mkdir -p dvi
	texi2dvi --pdf readme.texi -I . -o dvi/readme.dvi
	mv readme.* dvi
	mv dvi/readme.dvi $(DIR_INSTALL)
	mv dvi/readme.texi .
	

clang_n:
	clang-format -n *.c
	clang-format -n $(FRONT_SRC)*.c
	clang-format -n $(BACK_SRC)*.c
	clang-format -n $(HEAD_SRC)*.h
	clang-format -n test/*.[ch]

clang_i:
	clang-format -i *.c $(FRONT_SRC)*.c $(BACK_SRC)*.c $(HEAD_SRC)*.h test/test.c test/test.h

arch:
	mkdir -p $(ARCHDIR)/$(HEAD_SRC) $(ARCHDIR)/$(FRONT_SRC) $(ARCHDIR)/$(BACK_SRC)
	cp -r *.c $(ARCHDIR)
	cp -r $(HEAD_SRC)* $(ARCHDIR)/$(HEAD_SRC)
	cp -r $(FRONT_SRC)* $(ARCHDIR)/$(FRONT_SRC)
	cp -r $(BACK_SRC)* $(ARCHDIR)/$(BACK_SRC)
	cp makefile $(ARCHDIR)
	#cp readme.txt $(ARCHDIR)
	tar -cvf lymondka.tetris.tar.gz $(ARCHDIR)
	-rm -rf $(ARCHDIR)
# $^ это набор зависимых файлов, используемых для создания чего-то другого.
# $@ это имя цели, которая будет построена.

# $(RM) - переменная в Makefile. Существуют явные переменные (которые определяются внутри Makefile) и неявные переменные (определяются make и могут быть переопределены вами)
# Вы можете увидеть список неявных переменных с этим флагом: make -p
# Некоторые из наиболее распространённых переменных можно найти по адресу: 10.3 Переменные, используемые неявными правилами
# Вы можете развернуть переменную с помощью следующего синтаксиса $(NAME) или ${NAME}

