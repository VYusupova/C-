CC = gcc #-lstdc++
CFLAGS = -Wall -Wextra -Werror  

arr:
	$(CC) $(CFLAGS) array_numbers.c -o task01
	./task01

v_arr: 
	valgrind --leak-check=full --track-origins=yes ./task01

c_arr:
	#cppcheck --enable=all --suppress=missingIncludeSystem array_numbers.c
	cppcheck --enable=all --inconclusive array_numbers.c
		
str: 
	clang-format -i  *.h  *.c
	cppcheck --enable=all str_no_space.c
	$(CC) $(CFLAGS) str_no_space.c -o task02
	valgrind --leak-check=full --track-origins=yes ./task02

logic: logic_task.c
	clang-format -i  *.h  *.c
	cppcheck --enable=all $<
	$(CC) $(CFLAGS) $< -o $@
	valgrind --leak-check=full --track-origins=yes ./$@

numbers: numbers.c
	clang-format -i  *.h  *.c
	cppcheck --enable=all $<
	$(CC) $(CFLAGS) $< -o $@
	valgrind --leak-check=full --track-origins=yes ./$@

telephone: telephone.c
	clang-format -i  *.h  *.c
	cppcheck --enable=all $<
	$(CC) $(CFLAGS) $< -o $@
	valgrind --leak-check=full --track-origins=yes ./$@

rebuild: clean all

clean:
	rm -rf task01 task02 logic numbers
