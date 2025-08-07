.PHONY: install uninstall clean run clang cppcheck HTML
CC := gcc
CFLAGS := -I inc -Wall -Werror -Wextra  -std=c11
GCOV_FLAGS = -fprofile-arcs -ftest-coverage 
DIR_INSTALL := build/
TEST := s21_test

all: clean clang install run

HEAD_SRC := inc/
SRC := main.c maze.c maze_out.c cave.c find_way.c
TEST_SRC := maze.c find_way.c test/maze_test.c
CHECK_LIBS := $(shell pkg-config --libs check)  #-lcheck -lpthread -lm -lrt -lsubunit

install: 
	mkdir $(DIR_INSTALL)
	#cp ./test_file/*.txt $(DIR_INSTALL)
	$(CC) $(CFLAGS) $(SRC) -o $(DIR_INSTALL)s21_maze.o
	printf "\n ✅  MAZE & CAVE install in catalog $(DIR_INSTALL) >>>" ;\

uninstall: clean

clean:
	rm -rf $(DIR_INSTALL)
	rm -rf *.o $(TEST) *.gcda *.gcno *.info report
	rm -rf ~/bin/
	rm -rf ~/s21_maze/
run:
	./$(DIR_INSTALL)s21_maze.o

tests: 
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TEST_SRC) -o $(TEST) $(CHECK_LIBS)
	./$(TEST)

gcov_report: CFLAGS += -fprofile-arcs -ftest-coverage
gcov_report: clean tests
	lcov -c -d . -o coverage.info
	genhtml coverage.info -o report
	open ./report/index.html #убрать при проверке

clang:
	clang-format -i *.c $(HEAD_SRC)*.h


#CPPCHECK = --enable=all --suppress=missingIncludeSystem
#CPPCHECK = -q --enable=all --inconclusive
CPPCHECK = --enable=all --check-level=exhaustive --suppress=missingIncludeSystem
# --check-level=exhaustive >>> Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches. [normalCheckLevelMaxBranches]

cppcheck:
	@printf "\n 🔧🔧🔧 CHECK FILE \n"
	cppcheck $(CPPCHECK) *.c $(HEAD_SRC)*.h

HTML:
	mkdir -p ~/bin/
	mkdir -p ~/s21_maze/
	cp $(DIR_INSTALL)s21_maze.o ~/s21_maze/s21_maze.o
	cp HTML/open_app.sh ~/bin/open_app.sh
	chmod +x ~/bin/open_app.sh
	sudo cp HTML/appurl.desktop /usr/share/applications/appurl.desktop
	sudo update-desktop-database
	 

	
