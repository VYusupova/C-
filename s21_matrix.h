

#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define OK_MATRIX 0
#define INCORRECT_MATRIX 1
#define CALCULATE_ERROR 2  // TO DO

#define EPSILON 1e-7
#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

//Основный функции
int s21_create_matrix(int rows, int columns, matrix_t *result);

void s21_remove_matrix(matrix_t *A);

int s21_eq_matrix(matrix_t *A, matrix_t *B);

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_mult_number(matrix_t *A, double number, matrix_t *result);

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_transpose(matrix_t *A, matrix_t *result);

int s21_calc_complements(matrix_t *A, matrix_t *result);

int s21_determinant(matrix_t *A, double *result);

int s21_inverse_matrix(matrix_t *A, matrix_t *result);

//Дополнительные функции
int s21_eq_size_matrix(matrix_t *A, matrix_t *B);

void s21_minor(matrix_t *A, matrix_t *minor, int i, int j);
int s21_error_matrix(const matrix_t *A);
