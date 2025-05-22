NAME := tetris

CC := gcc
CFLAGS := -I inc -std=c11 -Wall -Werror -Wpedantic
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
CHECK_LIBS = $(shell pkg-config --libs check) #-lcheck -lm -lpthread -lrt -lsubunit

OBJS_FSMSWITCHCASE :=  out/tetris.o out/fsm.o 
BACKEND := out/brick_game/tetris/
FRONTEND := out/gui/cli/
BACK := $(BACKEND)tetris_init.o $(BACKEND)tetris_moving.o $(BACKEND)tetris_score.o
FRONT := $(FRONTEND)tetris_frontend.o
#OBJS_FSMTABLE := out/tetris.o out/fsm_matrix.o  out/frontend.o


PATH_TEST = test
TEST = run_tests
DIR_INSTALL := ~/#'Рабочий стол'/

.PHONY: clean install tetris uninstall

all: clean install

install: mkdir tetris #clean - возможность очищать вспомогательные файлы после того как игра установлена 
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

tetris: $(OBJS_FSMSWITCHCASE) $(BACK) $(FRONT)
	#clang-format -i src/*.c
	$(CC) $(CFLAGS) $^ -o $@ -lncurses

#frogger_fsmtable: $(OBJS_FSMTABLE)
#	$(CC) $(CFLAGS) $^ -o $@ -lncurses

out/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

mkdir:
	mkdir -p $(BACKEND)
	mkdir -p $(FRONTEND)

clean:
	$(RM) out/*.o tetris #frogger_fsmtable  - возможность очищать вспомогательные файлы после того как игра установлена 
	rm -rf out/
	rm -rf gcov/
	rm -rf *coverage.info
	rm -rf $(TEST)
	rm -rf tetris_max_score.txt



test_file:
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c test/test.c -o  test/tests.gcov.o

test: test_file
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -o $(TEST) test/*.gcov.o $(BACKEND)*.o  $(CHECK_LIBS)
	@printf "\e[1;35;107m RUN FILE TESTING  \e[31;0m \n"
	./$(TEST)
	@printf "\n\e[1;35;107m END FILE TESTING    \e[31;0m \n"
	

gcov_report: test
	@printf "\e[1;35;107m  📊 Отчет покрытия кода в 'gcov/index.html' ┃\e[31;0m \n"
	lcov -t "gcov_report" -o $(NAME)_coverage.info -c -d . --exclude '/usr/*' --exclude  $(TEST)
	genhtml -o gcov $(NAME)_coverage.info
	
valgrind: tetris test
	valgrind --leak-check=full --track-origins=yes ./$(TEST) $(GTEST_LIB)

	
cppcheck:
	@printf "\n 🔧🔧🔧 CHECK FILE --enable=all --inconclusive \n" 
	cppcheck -q --enable=all --inconclusive src/gui/cli/*.c src/*.c src/brick_game/tetris/*.c inc/*.h
	@printf "\n 🔧🔧🔧 CHECK FILE --enable=all --suppress=missingIncludeSystem \n"
	#cppcheck --enable=all --suppress=missingIncludeSystem src/gui/cli/*.c src/*.c src/brick_game/*.c ../inc/*.h





arch:
	mkdir $(ARCHDIR) $(ARCHDIR)/gui $(ARCHDIR)/brick_game
	cp -r $(LIBDIR) $(ARCHDIR)/$(LIBDIR) && cp -r $(GUIDIR) $(ARCHDIR)/$(GUIDIR) && cp -r $(HDIR) $(ARCHDIR) && cp -r $(INSTDIR) $(ARCHDIR) && cp Makefile $(ARCHDIR) && cp readme.txt $(ARCHDIR)
	tar -cvf willumye.tetris.tar.gz $(ARCHDIR)
	-rm -rf $(ARCHDIR)

dvi:
	mkdir -p dvi
	texi2dvi readme.texi --dvi -o readme.dvi
	mv readme.* dvi
	mv dvi/readme.txt .
	mv dvi/readme.texi .

# $^ это набор зависимых файлов, используемых для создания чего-то другого.
# $@ это имя цели, которая будет построена.

# $(RM) - переменная в Makefile. Существуют явные переменные (которые определяются внутри Makefile) и неявные переменные (определяются make и могут быть переопределены вами)
# Вы можете увидеть список неявных переменных с этим флагом: make -p
# Некоторые из наиболее распространённых переменных можно найти по адресу: 10.3 Переменные, используемые неявными правилами
# Вы можете развернуть переменную с помощью следующего синтаксиса $(NAME) или ${NAME}

