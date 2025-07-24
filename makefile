CC = gcc #-lstdc++
CFLAGS = -Wall -Wextra -Werror  

arr: 
	$(CC) $(CFLAGS) array_numbers.c -o task01
	./task01

v_arr: 
	valgrind --leak-check=full --track-origins=yes ./task01

c_arr:
	#cppcheck --enable=all --suppress=missingIncludeSystem array_numbers.c
	cppcheck -q --enable=all --inconclusive array_numbers.c
		
str: 
	$(CC) $(CFLAGS) str_no_space.c -o task02
	./task02

v_str: 
	valgrind --leak-check=full --track-origins=yes ./task02

c_str:
	#cppcheck --enable=all --suppress=missingIncludeSystem str_no_space.c
	cppcheck -q --enable=all --inconclusive str_no_space.c
			
formated_code:
	clang-format --style=Google -i *.cpp
	clang-format --style=Google -i *.h




rebuild: clean all


#rm -r LIB # удалить директорию и все ее содержимое рекурсивно -r
#mv $(NAME).o LIB/$(NAME).
#	mkdir LIB
