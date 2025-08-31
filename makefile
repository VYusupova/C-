#########################################################################################
################# лучшие практики из проектов ###########################################
#________________________________________________________________________________________

NAME := SimpleNavigator
DIR_GAME := s21_projects
DIR_INSTALL := ~/$(DIR_GAME)/
ARCHDIR := arhiv_project_dir

BACK_SRC 
FRONT_SRC 
HEAD_SRC := inc/

CC := gcc
CFLAGS := -I inc -std=c11 -Wall -Werror -Wpedantic
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
CHECK_LIBS = $(shell pkg-config --libs check) #-lcheck -lm -lpthread -lrt -lsubunit

CPPCHECK = -q --enable=all --inconclusive --suppress=missingIncludeSystem --check-level=exhaustive 

PATH_TEST = test
TEST = run_tests

STL_LIB = libmy1.a

.PHONY: all clean install tetris uninstall test gcov_report rebuild valgrind formated_code cppcheck

all: clean install

install: mkdir tetris dvi
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
	$(RM) $(DIR_INSTALL)readME.md
	rm -rf $(DIR_INSTALL)misc

tetris: $(OBJS_FSMSWITCHCASE) $(BACK) $(FRONT)
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

test: test_file
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -o $(TEST) test/*.gcov.o   $(CHECK_LIBS)
	./$(TEST)


gcov_report: test
	lcov -t "gcov_report" -o $(NAME)_coverage.info -c -d .
	genhtml -o gcov $(NAME)_coverage.info
	$(RM) test/*.gcov.*

valgrind: mkdir tetris test
	valgrind --leak-check=full --track-origins=yes ./$(TEST) $(GTEST_LIB)


cppcheck:
	@printf "\n 🔧🔧🔧 CHECK FILE \n"
	cppcheck $(CPPCHECK) *.c $(FRONT_SRC)*.c $(BACK_SRC)*.c $(HEAD_SRC)*.h

dvi:
	mkdir -p $(DIR_INSTALL)misc/img
	cp -r misc/img/*.png $(DIR_INSTALL)misc/img
	cp readME.md $(DIR_INSTALL)

clang_n:
	clang-format -n *.c
	clang-format -n $(FRONT_SRC)*.c
	clang-format -n $(BACK_SRC)*.c
	clang-format -n $(HEAD_SRC)*.h
	clang-format -n test/*.[ch]

clang_i:
	clang-format -i *.c $(FRONT_SRC)*.c $(BACK_SRC)*.c $(HEAD_SRC)*.h test/test.c test/test.h

dist:
	mkdir -p $(ARCHDIR)/$(HEAD_SRC) $(ARCHDIR)/$(FRONT_SRC) $(ARCHDIR)/$(BACK_SRC)
	cp -r *.c $(ARCHDIR)
	cp -r $(HEAD_SRC)* $(ARCHDIR)/$(HEAD_SRC)
	cp -r $(FRONT_SRC)* $(ARCHDIR)/$(FRONT_SRC)
	cp -r $(BACK_SRC)* $(ARCHDIR)/$(BACK_SRC)
	cp makefile $(ARCHDIR)
	mkdir -p $(ARCHDIR)/misc/img
	cp -r misc/img/*.png $(ARCHDIR)/misc/img
	cp readME.md $(ARCHDIR)
	tar -cvf lymondka.tetris.tar.gz $(ARCHDIR)
	-rm -rf $(ARCHDIR)

lib: #stack.o #$(OBJS_FILE)
	ar rcs  $(STL_LIB) s21_stack.tpp s21_stack.h
	rm *.o #Использованные объектные файлы можно удалить



test_main:
	$(CC) $(CFLAGS) main.cpp -o $@
	./test_main
	rm -f test_main

t1:
	#$(CC) $(CFLAGS) -Llibrary -lmy1   main.cpp -o test_main
	 #g++ -Wall -Wextra -Werror -std=c++11    main.cpp -o test_main -Llibrary -lmy1
	 g++ -fprofile-arcs main.cpp -lmy1 -L. -o four


GCOVR_CFLAGS = -fprofile-arcs -ftest-coverage -fPIC
GTEST_LIB =  -lgtest -lgtest_main
TEST_SRC = test.cpp
TEST_RUN = run_tests

test: clean
	$(CC)  $(CFLAGS)  $(GCOVR_CFLAGS) $(TEST_SRC) -o $(TEST_RUN)  $(GTEST_LIB)
	./$(TEST_RUN)

clean:
	rm -f $(STL_LIB)
	#rm -rf gcov
	rm -f *.*[oa]
	rm -f $(TEST_RUN)




#OUT_FILE = $(NAME).exe

#GCOV_REPORT_DIR = report



gcov_report: test
	#lcov -t "gcov_report" -o $(NAME)_coverage.info -c -d . --exclude '/usr/*' --exclude  $(TEST_SRC)
	#genhtml -o gcov $(NAME)_coverage.info


formated_code:
	clang-format --style=Google -i *.cpp
	clang-format --style=Google -i *.h

valgrind: clean  test
	valgrind --leak-check=full --track-origins=yes ./$(TEST_RUN) $(GTEST_LIB)

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.cpp
	#cppcheck -q --enable=all --inconclusive *.cpp

rebuild: clean all




#########################################################################################
################# справочный матрериал ##################################################

#<2> nice) Коомпиляция и линковка
#CC = gcc -lstdc++ CC = g++
#Да, можно откомпилировать с -lstdc++ Можно микроскопом забивать гвозди, а асфальтовым катком колоть орехи. Можно вообще все на ассемблере писать, и голова болеть не будет...
CFLAGS = -Wall -Wextra -Werror -std=c++20 #-lpthread -pedantic -lsubunit -pthread
#-Wall - Выводит большинство предупреждений
#-Wfloat-equal - Предупреждает о не безопасном сравнении
#-Wsign-conversion или -Wsign-promo - Предупреждения преобразования signed в unsigned (и обратно)
#-Wold-style-cast - Выводит C Style преобразования типов
#-Warray-bounds - Доступ за пределы массива
#-Wdiv-by-zero - Предупреждать о делении на 0
#-Wdouble-promotion - Предупреждает о преобразовании с float на double
#-Wbool-compire - Предупреждение о сравнении int с bool
#-pedantic - соответствие определенному стандарту



# CPPCHECK = -q --enable=all --inconclusive --suppress=missingIncludeSystem --check-level=exhaustive 
# --check-level=exhaustive  Ограничивающий анализ ветвей. Используйте --check-level=исчерпывающий для анализа всех ветвей. 
# Параметр --enable=all в инструменте CppCheck включает все возможные проверки
# Параметр --suppress переводится как подавлять, т.е. --suppress=missingIncludeSystem не будет писать в ошибки если не найдена какая то библиотека
all : lib
# Параметр -q означает «тихий» режим — выводятся только сообщения об ошибках, а не ход выполнения на экране.
 Разрешите, чтобы Cppcheck сообщал о результатах, даже если анализ не дал результатов. При
# Параметр --inconclusive использовании этой опции возможны ложные срабатывания. Каждый результат должен быть тщательно проанализирован, прежде чем вы узнаете, хороший он или плохой.

# 
