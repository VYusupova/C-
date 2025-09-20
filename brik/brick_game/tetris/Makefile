CC = gcc
CFLAGS = -fPIC -std=c11 -Wall -Wextra -Werror -I../../../include
TEST_CFLAGS = $(CFLAGS) --coverage -O0 -g
LDFLAGS = -shared
TEST_LDFLAGS = -lpthread -lcheck -lsubunit -lm --coverage

SRC = controller.c back.c wrapper.c
TEST_SRC ?= ../../tests/tetris_test.c  # Путь по умолчанию, может быть переопределен
LIBTARGET = $(BUILD_DIR)/libtetris_back.so
TEST_TARGET = $(BUILD_DIR)/tetris_test
OBJ = $(addprefix $(BUILD_DIR)/,$(SRC:.c=.o))
COVERAGE_DIR = $(abspath $(BUILD_DIR)/../../../bin/coverage/tetris)

all: $(LIBTARGET)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBTARGET): $(OBJ)
	mkdir -p ../../bin/lib
	$(CC) $(LDFLAGS) -o $@ $(OBJ)
	cp $(LIBTARGET) ../../bin/lib/

clean:
	rm -f $(OBJ) $(LIBTARGET) $(TEST_TARGET) $(BUILD_DIR)/tetris_test.o *.gcno *.gcda *.gcov

.PHONY: all test clean
