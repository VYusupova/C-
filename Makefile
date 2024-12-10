CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 -pedantic -lsubunit
#-pedantic - соответсвие определенному стандарту
GCOVR_CFLAGS =-fprofile-arcs -ftest-coverage -fPIC
GTEST_LIB = -lgtest -lgtest_main

NAME = s21_matrix_oop
SRC = $(NAME).cpp
OBJ = $(NAME).o

TEST_SRC = s21_matrix_oop_test.cpp
TEST_RUN = run_tests

OUT_FILE = $(NAME).exe
PATH_TEST = tests


GCOV_REPORT_DIR = report

all: clean $(NAME).a

$(NAME).a: $(NAME).o
	ar rcs $(NAME).a $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

test: clean
	$(CC) $(CFLAGS) $(SRC) $(GCOVR_CFLAGS) $(TEST_SRC) -o $(TEST_RUN) $(GTEST_LIB)

run_test: test
	./$(TEST_RUN)

run_valgrind: test
	valgrind --leak-check=full --track-origins=yes ./$(TEST_RUN)

gcov_report: run_test
	./$(TEST_RUN)
	lcov -t "gcov_report" -o $(NAME)_coverage.info -c -d . --exclude '/usr/*' --exclude  $(TEST_SRC)
	genhtml -o gcov $(NAME)_coverage.info
	@echo "Отчет покрытия кода создан в 'gcov/index.html'"

clean:
	rm -f $(TEST_RUN)
	rm -rf gcov
	rm -f *.*[oa]
	rm -f *.info

.PHONY: all clean test gcov_report rebuild valgrind clang

formated_code:
	clang-format -i *.cpp
	clang-format -i *.h
cppcheck:
	#cppcheck --enable=all --suppress=missingIncludeSystem *.cpp
	cppcheck -q --enable=all --inconclusive *.cpp

rebuild: clean all

#
#rm -r LIB # удалить директорию и все ее содержимое рекурсивно -r
#mv $(NAME).o LIB/$(NAME).
#	mkdir LIB
