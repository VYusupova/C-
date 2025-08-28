#ifndef SRC_TESTS_TEST_H_
#define SRC_TESTS_TEST_H_

#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "../graph/s21_graph.h"
#include "../graph_algorithms/s21_graph_algorithms.h"

Suite *test_graph(void);

Suite *test_algorithms(void);

#endif  // SRC_TESTS_TEST_H_