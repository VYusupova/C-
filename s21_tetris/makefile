CC := gcc
CFLAGS := -I inc -std=c11 -Wall -Werror -Wpedantic
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
CHECK_LIBS = $(shell pkg-config --libs check) #-lcheck -lm -lpthread -lrt -lsubunit

OBJS_FSMSWITCHCASE :=  out/tetris.o out/fsm.o 
BACKEND := out/brick_game/tetris/
BACK := $(BACKEND)tetris_init.o $(BACKEND)tetris_moving.o $(BACKEND)tetris_score.o
FRONT := out/gui/cli/tetris_frontend.o
#OBJS_FSMTABLE := out/tetris.o out/fsm_matrix.o  out/frontend.o

PATH_TEST = test
TEST_BIN = run_tests
DIR_INSTALL := ~/#'Рабочий стол'/

.PHONY: clean install tetris uninstall

all: clean install

install: mkdir tetris #clean - возможность очищать вспомогательные файлы после того как игра установлена 
ifdef DIR_INSTALL
	@if [ -d $(DIR_INSTALL) ]; then \
	  echo "\n 🚀📊✅  TETRIS GAME install in catalog $(DIR_INSTALL) >>>" ;\
          install tetris $(DIR_INSTALL) ; \
          $(DIR_INSTALL)./tetris; \
	  else echo "\ninstall aborted ... " ; \
	       echo "$(DIR_INSTALL) >>> not found catalog" ; \
	fi	
else
	$(error DIR_INSTALL must be set!)
endif


uninstall: clean
	$(RM) $(DIR_INSTALL)/tetris
	$(RM) $(DIR_INSTALL)/tetris_max_score.txt

tetris:  $(OBJS_FSMSWITCHCASE) $(BACK) $(FRONT)
	#clang-format -i src/*.c
	$(CC) $(CFLAGS) $^ -o $@ -lncurses

#frogger_fsmtable: $(OBJS_FSMTABLE)
#	$(CC) $(CFLAGS) $^ -o $@ -lncurses

out/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

mkdir:
	#mkdir out/
	#mkdir out/brick_game/
	mkdir -p out/brick_game/tetris/
	#mkdir out/gui/
	mkdir -p out/gui/cli/

clean:
	$(RM) out/*.o tetris #frogger_fsmtable  - возможность очищать вспомогательные файлы после того как игра установлена 
	rm -rf out/
	rm -rf test/*.gcov.*
	rm -rf $(TEST_BIN)
	#rm -rf tetris_max_score.txt



test_file:
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c test/test.c -o  test/tests.gcov.o

test: test_file
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -o $(TEST_BIN) test/*.gcov.o out/brick_game/tetris/*.o  $(CHECK_LIBS)
	@printf "\e[1;35;107m RUN FILE TESTING  \e[31;0m \n"
	./$(TEST_BIN)
	@printf "\n\e[1;35;107m END & DEL FILE TESTING    \e[31;0m \n"
	
	
valgrind: clean  test
	valgrind --leak-check=full --track-origins=yes ./$(TEST_RUN) $(GTEST_LIB)

	
cppcheck:
	#cppcheck --enable=all --suppress=missingIncludeSystem src/brick_game/*.c
	@printf "\n 🔧🔧🔧 CHECK FILE src/*.c \n" 
	#cppcheck -q --enable=all --inconclusive src/*.c
	#cppcheck --enable=all --suppress=missingIncludeSystem src/*.c
	@printf "\n 🔧🔧🔧 CHECK FILE src/gui/cli/*.c \n"
	#cppcheck -q --enable=all --inconclusive src/gui/cli/*.c
	cppcheck --enable=all --suppress=missingIncludeSystem src/gui/cli/*.c

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

