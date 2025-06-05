CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 -lpthread -pedantic -lsubunit -pthread

all : test_main

test_main:
	$(CC) $(CFLAGS) main.cpp -o $@
	@printf "\e[1;35;107m RUN FILE TESTING \e[31;0m"
	./test_main
	@printf "\n\e[1;35;107m END & DEL FILE TESTING    \e[31;0m"
	rm -f test_main


GCOVR_CFLAGS = -fprofile-arcs -ftest-coverage -fPIC
GTEST_LIB =  -lgtest -lgtest_main
TEST_SRC = test.cpp
TEST_RUN = run_tests

test: clean
	$(CC)  $(CFLAGS)  $(GCOVR_CFLAGS) $(TEST_SRC) -o $(TEST_RUN)  $(GTEST_LIB)
	./$(TEST_RUN)

clean:
	#rm -rf gcov
	rm -f *.*[oa]
	rm -f $(TEST_RUN)

clang_cp:
	cp ../materials/linters/.clang-format .clang-format

clang_google:
	clang-format --style=Google -i *.tpp
	clang-format --style=Google -i *.cpp
	clang-format --style=Google -i *.h

clang_def:
	clang-format -i *.tpp
	clang-format -i *.h
	clang-format -i *.cpp

.PHONY: all clean test gcov_report rebuild valgrind formated_code cppcheck



valgrind: clean  test
	valgrind --leak-check=full --track-origins=yes ./$(TEST_RUN) $(GTEST_LIB)

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.cpp
	#cppcheck -q --enable=all --inconclusive *.cpp

rebuild: clean all

#никто не пишет либу (
STL_LIB = libmy1.a

#lib

lib: #stack.o #$(OBJS_FILE)
	ar rcs  $(STL_LIB) s21_stack.tpp s21_stack.h
	rm -f *.o #Использованные объектные файлы можно удалить

stack.o: s21_stack.h
	$(CC) $(CFLAGS) s21_stack.сpp  -o stack.o

#%.o: %.cpp %.h
#	$(CC) $(CFLAGS) -c $< -o $@

t1:
	 g++ -fprofile-arcs main.cpp -lmy1 -L. -o four
	 #rm -f $(STL_LIB)
