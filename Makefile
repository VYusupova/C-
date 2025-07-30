CC := gcc
CFLAGS := -Wall -Werror -Wextra  -std=c11
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
DIR_INSTALL := build/
all: clean clang install run

HEAD_SRC := inc/

install: 
	mkdir $(DIR_INSTALL)
	cp ./test_file/*.txt $(DIR_INSTALL)
	$(CC) $(CFLAGS) main.c maze.c cave.c -o $(DIR_INSTALL)s21_maze.o
	printf "\n ✅  MAZE & CAVE install in catalog $(DIR_INSTALL) >>>" ;\

uninstall: clean

clean:
	rm -rf $(DIR_INSTALL)
run:
	./$(DIR_INSTALL)/s21_maze.o
tests:

gcov_report:

clang:
	clang-format -i *.c $(HEAD_SRC)*.h


#CPPCHECK = --enable=all --suppress=missingIncludeSystem
#CPPCHECK = -q --enable=all --inconclusive
CPPCHECK = --enable=all --check-level=exhaustive --suppress=missingIncludeSystem
# --check-level=exhaustive >>> Limiting analysis of branches. Use --check-level=exhaustive to analyze all branches. [normalCheckLevelMaxBranches]

cppcheck:
	@printf "\n 🔧🔧🔧 CHECK FILE \n"
	cppcheck $(CPPCHECK) *.c $(HEAD_SRC)*.h
