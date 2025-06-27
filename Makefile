CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
CHECK_LIBS = -lcheck -lm -pthread -lrt -lsubunit

SRC = s21_matrix.c
PATH_TEST = tests

TEST_BIN = run_tests
GCOV_REPORT_DIR = report

all: clean s21_matrix.a

s21_matrix.a: s21_matrix.o
	ar rcs s21_matrix.a s21_matrix.o

s21_matrix.o: s21_matrix.c
	$(CC) $(CFLAGS) -c s21_matrix.c -o s21_matrix.o

test_file:
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c s21_matrix.c -o s21_matrix.gcov.o
	ar rcs s21_matrix_cov.a s21_matrix.gcov.o
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c tests/tests.c  -o tests/tests.gcov.o
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c tests/test_eq_matrix.c  -o tests/test_eq_matrix.gcov.o
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c tests/test_sum_matrix.c -o tests/test_sum_matrix.gcov.o
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c tests/test_mult_matrix.c -o tests/test_mult_matrix.gcov.o
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c tests/test_determinant_matrix.c -o tests/test_determinant_matrix.gcov.o
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c tests/test_inverse_matrix.c -o tests/test_inverse_matrix.gcov.o

test: clean test_file

	$(CC) $(CFLAGS) $(GCOV_FLAGS) -o $(TEST_BIN) $(PATH_TEST)/*.gcov.o  s21_matrix_cov.a $(CHECK_LIBS)
	@echo "\e[0;35m"
	@echo "┏=========================================┓"
	@echo "┃   START TESTING ...  ...  ...  ...      ┃"
	@echo "┗=========================================┛"
	@echo "\e[0;30m"
	./$(TEST_BIN)

gcov_report: test
	mkdir -p $(GCOV_REPORT_DIR)
	lcov -t "s21_matrix" -o $(GCOV_REPORT_DIR)/coverage.info -c -d .
	genhtml -o $(GCOV_REPORT_DIR) $(GCOV_REPORT_DIR)/coverage.info

	@echo "\e[1;35;107m" # серые буквы на белом фоне
	@echo "┏=========================================┓"
	@echo "┃   Generating html report is OK          ┃"
	@echo "┗=========================================┛"
	@echo "\e[0;30m"

clang:
	cp ../materials/linters/.clang-format .clang-format
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i *.c
	clang-format -i *.h
	clang-format -i $(PATH_TEST)/*.c
	clang-format -i $(PATH_TEST)/*.h

valgrind: test
	valgrind --tool=memcheck --leak-check=yes ./$(TEST_BIN) 2>&1 | grep "ERROR SUMMARY"

clean:
	rm -f *.o s21_matrix.a s21_matrix_cov.a $(TEST_BIN)
	rm -rf $(GCOV_REPORT_DIR)
	rm -f *.gcda *.gcno *.gcov *.gcov.o
	rm -f tests/*.gcda
	rm -f tests/*.gcov
	rm -f tests/*.gcov.o  # deleted
	rm -f tests/*.gcno

rebuild: clean all

.PHONY: all clean test gcov_report rebuild valgrind clang


