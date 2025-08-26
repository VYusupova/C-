CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 -pedantic -lsubunit
#-pedantic - соответствие определенному стандарту
GCOVR_CFLAGS =-fprofile-arcs -ftest-coverage -fPIC
GTEST_LIB = -lgtest -lgtest_main

NAME = s21_matrix_oop
SRC = $(NAME).cpp
OBJ = $(NAME).o
RCS = $(NAME).a

TEST_SRC = s21_matrix_oop_test.cpp
TEST_RUN = run_tests

OUT_FILE = $(NAME).exe

GCOV_REPORT_DIR = report

all: clean $(RCS)

$(RCS): $(OBJ)
	ar rcs $(RCS) $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

test: clean
	$(CC) $(CFLAGS) $(SRC) $(GCOVR_CFLAGS) $(TEST_SRC) -o $(TEST_RUN) $(GTEST_LIB)
	./$(TEST_RUN)

gcov_report: test
	@echo "\e[0;35m"
	lcov -t "gcov_report" -o $(NAME)_coverage.info -c -d . --exclude '/usr/*' --exclude  $(TEST_SRC)
	genhtml -o gcov $(NAME)_coverage.info
	@echo "\e[1;35;107m" # серые буквы на белом фоне
	@echo "┏						  ┓"
	@echo "┃  Отчет покрытия кода создан в 'gcov/index.html' ┃"
	@echo "┗                                                 ┛"
	@echo "\e[0;30m"

clean:
	rm -f $(TEST_RUN)
	rm -rf gcov
	rm -f *.*[oa]
	rm -f *.info

.PHONY: all clean test gcov_report rebuild valgrind formated_code cppcheck

formated_code:
	clang-format --style=Google -i *.cpp
	clang-format --style=Google -i *.h

valgrind: test
	valgrind --leak-check=full --track-origins=yes ./$(TEST_RUN) $(GTEST_LIB)

cppcheck:
	#cppcheck --enable=all --suppress=missingIncludeSystem *.cpp
	cppcheck -q --enable=all --inconclusive *.cpp

rebuild: clean all

#
#rm -r LIB # удалить директорию и все ее содержимое рекурсивно -r
#mv $(NAME).o LIB/$(NAME).
#	mkdir LIB
