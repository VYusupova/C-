CC = g++
#CC = gcc -lstdc++
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

OBJS_FILE :=  stack.o # тут перечислим файлы а цель %.o скомпилирует их пооочереди из файлов %.cpp
STL_LIB = libmy1.a
# nice) make в командной строке выполняет первую цель в файле, в нашем случае all, но если поставить любую другую цель первой, то выполнена будет она
all : lib

lib: #stack.o #$(OBJS_FILE)
	ar rcs  $(STL_LIB) s21_stack.tpp s21_stack.h
	rm *.o #Использованные объектные файлы можно удалить

stack.o: s21_stack.h
	$(CC) $(CFLAGS) s21_stack.сpp  -o stack.o

#%.o: %.cpp %.h
#	$(CC) $(CFLAGS) -c $< -o $@

test_main:
	$(CC) $(CFLAGS) main.cpp -o $@
	@printf "\e[1;35;107m RUN FILE TESTING \e[31;0m"
	./test_main
	@printf "\n\e[1;35;107m END & DEL FILE TESTING    \e[31;0m"
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
	#@echo "\e[0;35m"
	#lcov -t "gcov_report" -o $(NAME)_coverage.info -c -d . --exclude '/usr/*' --exclude  $(TEST_SRC)
	#genhtml -o gcov $(NAME)_coverage.info
	#@echo "\e[1;35;107m" # серые буквы на белом фоне
	#@echo "┏						  ┓"
	#@echo "┃  Отчет покрытия кода создан в 'gcov/index.html' ┃"
	#@echo "┗                                                 ┛"
	#@echo "\e[0;30m"



.PHONY: all clean test gcov_report rebuild valgrind formated_code cppcheck

formated_code:
	clang-format --style=Google -i *.cpp
	clang-format --style=Google -i *.h

valgrind: clean  test
	valgrind --leak-check=full --track-origins=yes ./$(TEST_RUN) $(GTEST_LIB)

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.cpp
	#cppcheck -q --enable=all --inconclusive *.cpp

rebuild: clean all



