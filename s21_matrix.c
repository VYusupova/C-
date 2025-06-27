#include "s21_matrix.h"
// 0 - OK_MATRIX 1 - INCORRECT_MATRIX 2 - CALCULATE_ERROR
// Проверка матрицы на корректность
int s21_check_matrix(const matrix_t *A) {
  return (A == NULL || A->matrix == NULL || A->rows < 1 || A->columns < 1)
             ? INCORRECT_MATRIX
             : OK_MATRIX;
}
// Проверка матрицы на корректность
int s21_error_matrix(const matrix_t *A) {
  if (s21_check_matrix(A)) return INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALCULATE_ERROR;
  return OK_MATRIX;
}

// Проверка что размер матриц одинаковый
int s21_eq_size_matrix(matrix_t *A, matrix_t *B) {
  return (A->rows == B->rows) && (A->columns == B->columns);
}

// Проверка матрицы на корректность и создание
int s21_check_create(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = s21_check_matrix(A) || s21_check_matrix(B);
  if (!err && !s21_eq_size_matrix(A, B)) err = CALCULATE_ERROR;
  if (!err) err = s21_create_matrix(A->rows, A->columns, result);
  return err;
}

// Минор матрицы
void s21_minor(matrix_t *A, matrix_t *minor, int i, int j) {
  for (int row = 0, minor_row = 0; row < A->rows; row++) {
    if (row == i) continue;
    for (int col = 0, minor_col = 0; col < A->columns; col++) {
      if (col == j) continue;
      minor->matrix[minor_row][minor_col] = A->matrix[row][col];
      minor_col++;
    }
    minor_row++;
  }
}

// Создание матрицы
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows < 1 || columns < 1 || !result) return INCORRECT_MATRIX;

  result->matrix = (double **)calloc(rows, sizeof(double *));

  if (!result->matrix) return INCORRECT_MATRIX;
  for (int i = 0; i < rows; i++) {
    result->matrix[i] = (double *)calloc(columns, sizeof(double));

    if (!result->matrix[i]) {
      while (i--) free(result->matrix[i]);
      free(result->matrix);
      return INCORRECT_MATRIX;
    }
  }

  result->rows = rows;
  result->columns = columns;

  return OK_MATRIX;
}

// Удаление матрицы
void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    for (int i = 0; i < A->rows; i++) free(A->matrix[i]);
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

// Сравнение матриц
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int eq_matrix = SUCCESS;
  if (s21_check_matrix(A) || s21_check_matrix(B) || !s21_eq_size_matrix(A, B))
    eq_matrix = FAILURE;

  for (int i = 0; i < A->rows && eq_matrix; i++) {
    for (int j = 0; j < A->columns && eq_matrix; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPSILON)
        eq_matrix = FAILURE;
    }
  }
  return eq_matrix;
}

// Сумма матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  // 0 - OK_MATRIX 1 - INCORRECT_MATRIX
  int error = s21_check_create(A, B, result);
  if (!error) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return error;
}

// Разность матриц
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = s21_check_create(A, B, result);
  if (!error) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return error;
}

// Умножение матрицы на число
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  // 0 - OK_MATRIX 1 - INCORRECT_MATRIX
  int error =
      s21_check_matrix(A) || s21_create_matrix(A->rows, A->columns, result);
  if (error) return INCORRECT_MATRIX;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
  return OK_MATRIX;
}

// Умножение матриц
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  // 0 - OK_MATRIX 1 - INCORRECT_MATRIX
  int error = s21_check_matrix(A) || s21_check_matrix(B);

  if (!error && (A->columns != B->rows)) error = CALCULATE_ERROR;

  if (!error) error = s21_create_matrix(A->rows, B->columns, result);
  if (!error) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        double sum = 0.0;
        for (int k = 0; k < A->columns; k++) {
          sum += A->matrix[i][k] * B->matrix[k][j];
        }
        result->matrix[i][j] = sum;
      }
    }
  }
  return error;
}

// Транспонирование матрицы
int s21_transpose(matrix_t *A, matrix_t *result) {
  // 0 - OK_MATRIX 1 - INCORRECT_MATRIX
  int error = s21_check_matrix(A);
  if (!error) error = s21_create_matrix(A->columns, A->rows, result);
  if (error) return error;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }
  return OK_MATRIX;
}

// Вычисление дополнений матрицы
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  // 0 - OK_MATRIX 1 - INCORRECT_MATRIX
  int error = s21_error_matrix(A);

  if (!error) error = s21_create_matrix(A->columns, A->rows, result);
  if (error) return error;
  if (A->rows == 1) {
    result->matrix[0][0] = 1;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        matrix_t minor;
        error = s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
        s21_minor(A, &minor, i, j);
        double minor_determinant = 0.0;
        s21_determinant(&minor, &minor_determinant);
        s21_remove_matrix(&minor);
        result->matrix[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * minor_determinant;
      }
    }
  }
  return OK_MATRIX;
}

// Вычисление детерминанта матрицы
int s21_determinant(matrix_t *A, double *result) {
  int error = s21_error_matrix(A);
  if (error) return error;
  switch (A->rows) {
    case 1:
      *result = A->matrix[0][0];
      break;
    case 2:
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
      break;
    default:
      *result = 0.0;
      for (int j = 0; j < A->columns; j++) {
        matrix_t minor;
        s21_create_matrix(A->rows - 1, A->columns - 1, &minor);

        for (int row = 1; row < A->rows; row++) {
          for (int col = 0, minor_col = 0; col < A->columns; col++) {
            if (col == j) continue;
            minor.matrix[row - 1][minor_col] = A->matrix[row][col];
            minor_col++;
          }
        }

        double minor_determinant = 0.0;
        s21_determinant(&minor, &minor_determinant);
        *result += (j % 2 == 0 ? 1 : -1) * A->matrix[0][j] * minor_determinant;

        s21_remove_matrix(&minor);
      }
  }
  return OK_MATRIX;
}

// Обратная матрица
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = s21_error_matrix(A);
  if (error) return error;
  double determinant = 0.0;

  int res = s21_determinant(A, &determinant);

  if (res != OK_MATRIX || fabs(determinant) < EPSILON) return CALCULATE_ERROR;

  matrix_t complements, transpose_matrix;
  res = s21_calc_complements(A, &complements);

  if (res == OK_MATRIX) {
    res = s21_transpose(&complements, &transpose_matrix);
    s21_remove_matrix(&complements);
    if (res == OK_MATRIX) {
      res = s21_create_matrix(A->rows, A->columns, result);
    }

    if (res == OK_MATRIX) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = transpose_matrix.matrix[i][j] / determinant;
        }
      }
    }
    s21_remove_matrix(&transpose_matrix);
  }
  return OK_MATRIX;
}