#include "s21_matrix_oop.h"

#include <gtest/gtest.h>

using namespace std;

// Тест на конструктор с параметрами, проверяем, что конструктор корректно
// работает для разных размеров матриц
// Тест на выделение памяти
TEST(createTest, c2x2) {
  S21Matrix small_matrix(2, 2);
  EXPECT_EQ(small_matrix.getRows(), 2);
  EXPECT_EQ(small_matrix.getColumns(), 2);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_DOUBLE_EQ(small_matrix(i, j), 0.0);
    }
  }
}
TEST(createTest, c3x3_DefaultConstructor) {
  int rows = 3;
  int cols = 3;
  S21Matrix m1;
  ASSERT_EQ(m1.getRows(), rows);
  ASSERT_EQ(m1.getColumns(), cols);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_DOUBLE_EQ(m1(i, j), 0.0);
    }
  }
}
TEST(createTest, c4x5) {
  int rows = 4;
  int cols = 5;
  S21Matrix m1(rows, cols);
  ASSERT_EQ(m1.getRows(), rows);
  ASSERT_EQ(m1.getColumns(), cols);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_DOUBLE_EQ(m1(i, j), 0.0);
    }
  }
}
TEST(createTest, c15x5) {
  int rows = 15;
  int cols = 5;
  S21Matrix m1(rows, cols);
  ASSERT_EQ(m1.getRows(), rows);
  ASSERT_EQ(m1.getColumns(), cols);
  m1.setMatrix(8.0);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_DOUBLE_EQ(m1(i, j), 8.0);
    }
  }
}
TEST(createTest, test_throw) {
  EXPECT_THROW(S21Matrix(-1, 5), std::invalid_argument);
  EXPECT_THROW(S21Matrix(4, 0), std::invalid_argument);
  EXPECT_THROW(S21Matrix(0, 0), std::invalid_argument);
  EXPECT_THROW(S21Matrix(-3, -3), std::invalid_argument);
}
// Тест на конструктор копирования
TEST(createTest, CopyConstructor_1) {
  S21Matrix original(2, 2);
  original(0, 0) = 1.0;
  original(0, 1) = 2.0;
  original(1, 0) = 3.0;
  original(1, 1) = 4.0;

  S21Matrix copy = original;

  EXPECT_EQ(copy.getRows(), original.getRows());
  EXPECT_EQ(copy.getColumns(), original.getColumns());

  EXPECT_EQ(copy(0, 0), original(0, 0));
  EXPECT_EQ(copy(0, 1), original(0, 1));
  EXPECT_EQ(copy(1, 0), original(1, 0));
  EXPECT_EQ(copy(1, 1), original(1, 1));

  copy(0, 0) = 10.6;
  EXPECT_NE(copy(0, 0), original(0, 0));
}
TEST(createTest, CopyConstructor_2) {
  int rows = 5;
  int cols = 5;
  S21Matrix original(rows, cols);
  S21Matrix copy(original);

  ASSERT_EQ(original.getRows(), copy.getRows());
  ASSERT_EQ(original.getColumns(), copy.getRows());

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) ASSERT_EQ(original(i, j), copy(i, j));

  copy(0, 0) = 15.55;
  EXPECT_NE(copy(0, 0), original(0, 0));
}
// Тест на повторное выделение памяти
TEST(createTest, memoryReall) {
  S21Matrix matrix(2, 2);         
  matrix(0, 0) = 1.45;  
  matrix(1, 1) = 2.45;

  EXPECT_EQ(matrix(0, 0), 1.45);
  EXPECT_EQ(matrix(1, 1), 2.45);
  // Теперь изменим размеры матрицы на 3x3
  matrix = S21Matrix(3, 3); 

  EXPECT_EQ(matrix(0, 0), 0.0); 
  EXPECT_EQ(matrix(1, 1), 0.0);  
  // Проверяем размеры новой матрицы
  EXPECT_EQ(matrix.getRows(), 3);
  EXPECT_EQ(matrix.getRows(), 3);
}
TEST(createTest, memoryReall_1) {
  S21Matrix matrix(3, 3);
  matrix(1, 1) = 5.0;
  EXPECT_EQ(matrix(1, 1), 5.0);
  // Повторное выделение памяти для новой матрицы 2x2
  matrix = S21Matrix(2, 2);
  EXPECT_EQ(matrix.getRows(), 2);
  EXPECT_EQ(matrix.getColumns(), 2);
  EXPECT_EQ(matrix(1, 1), 0.0);  // Новая матрица инициализирована нулями
}
// Тест на деструктор
TEST(destructorTest, test_1) {
  // Создаем матрицу внутри блока, чтобы проверить, что по завершению блока
  // память корректно освобождается деструктором
  {
    S21Matrix matrix(10, 10);
    // Заполним матрицу для теста
    for (int i = 0; i < 10; ++i) {
      for (int j = 0; j < 10; ++j) {
        matrix.setMatrixEl(i, j, i + j);
      }
    }

    matrix.~S21Matrix();

    EXPECT_EQ(matrix.getRows(), 0);
    EXPECT_EQ(matrix.getColumns(), 0);
  }
}
// Тест на освобождение памяти
TEST(destructorTest, test_2) {
  S21Matrix matrix(2, 2);  // Создаем матрицу 2x2

  // Проверяем, что память выделена
  // Метод не должен выбрасывать исключение
  EXPECT_NO_THROW(matrix.DeallocateMemory());

  // Проверяем, что размеры матрицы теперь 0
  EXPECT_EQ(matrix.getRows(), 0);
  EXPECT_EQ(matrix.getColumns(), 0);
}

TEST(eqMatrixTest, test_1) {
  int rows = 2;
  int cols = 2;
  S21Matrix m1(rows, cols);
  m1(0, 0) = 32.3337;
  m1(0, 1) = 53.3137;
  m1(1, 0) = 28.7227;
  m1(1, 1) = 10.7157;
  S21Matrix m2(m1);
  m2(1, 0) = -28.7227;
  ASSERT_FALSE(m1.EqMatrix(m2));
}
TEST(eqMatrixTest, test_2) {
  // сравниваем матрицы у которых небольшая погрешность
  int rows = 2;
  int cols = 2;
  S21Matrix m1(rows, cols);
  S21Matrix m2(rows, cols);
  m1(0, 0) = 32.3337;
  m1(0, 1) = 53.3137;
  m1(1, 0) = 28.7227;
  m1(1, 1) = 10.7157;
  m2(0, 0) = 32.33372;
  m2(0, 1) = 53.31372;
  m2(1, 0) = 28.72272;
  m2(1, 1) = 10.71572;
  ASSERT_FALSE(m1.EqMatrix(m2));
}
TEST(eqMatrixTest, test_3) {
  // сравниваем матрицы у которых небольшая погрешность
  int rows = 2;
  int cols = 2;
  S21Matrix m1(rows, cols);
  m1(0, 0) = 32.3337;
  m1(0, 1) = 53.3137;
  m1(1, 0) = 28.7227;
  m1(1, 1) = 10.7157;
  S21Matrix m2(rows, cols);
  m2(0, 0) = 32.333;
  m2(0, 1) = 53.313;
  m2(1, 0) = 28.722;
  m2(1, 1) = 10.715;
  ASSERT_TRUE(m1.EqMatrix(m2) == 0);
}
TEST(eqMatrixTest, test_4) {
  // сравниваем матрицы у которых небольшая погрешность
  int rows = 2;
  int cols = 2;
  S21Matrix m1(rows, cols);
  m1(0, 0) = 32.33372;
  m1(0, 1) = 53.31372;
  m1(1, 0) = 28.72272;
  m1(1, 1) = 10.71572;
  S21Matrix m2(rows, cols);
  m2(0, 0) = 32.333726;
  m2(0, 1) = 53.313726;
  m2(1, 0) = 28.722726;
  m2(1, 1) = 10.715726;
  ASSERT_TRUE(m1.EqMatrix(m2) == 0);
}
TEST(eqMatrixTest, test_8_sign0) {
  // сравниваем матрицы у которых небольшая погрешность различие в 8 знаке
  int rows = 2;
  int cols = 2;
  S21Matrix m1(rows, cols);
  m1(0, 0) = 32.3337261;
  m1(0, 1) = 53.3137261;
  m1(1, 0) = 28.7227261;
  m1(1, 1) = 10.7157261;
  S21Matrix m2(rows, cols);
  m2(0, 0) = 32.33372619;
  m2(0, 1) = 53.31372619;
  m2(1, 0) = 28.72272619;
  m2(1, 1) = 10.71572619;
  ASSERT_TRUE(m1.EqMatrix(m2) == 1);
}
TEST(eqMatrixTest, test_8_sign1) {
  // сравниваем матрицы у которых небольшая погрешность различие в 8 знаке после
  // запятой
  int rows = 2;
  int cols = 2;
  S21Matrix m1(rows, cols);
  m1(0, 0) = 32.3337261;
  m1(0, 1) = 53.3137261;
  m1(1, 0) = 28.7227261;
  m1(1, 1) = 10.7157261;
  S21Matrix m2(rows, cols);
  m2(0, 0) = 32.33372611;
  m2(0, 1) = 53.31372611;
  m2(1, 0) = 28.72272611;
  m2(1, 1) = 10.71572611;
  ASSERT_TRUE(m1.EqMatrix(m2) == 1);
}
// Тест для оператора сравнения (operator==)
TEST(eqMatrixTest, eqOperator_1_true) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 4.0;

  EXPECT_TRUE(matrix1 == matrix2);
}
TEST(eqMatrixTest, eqOperator_2_false) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 8.0;

  EXPECT_FALSE(matrix1 == matrix2);
}
TEST(sumMatrixTest, sum_test_1) {
  // складываем матрицы одинакового размера
  int rows = 2;
  int cols = 2;
  S21Matrix m1(rows, cols);
  S21Matrix m2(rows, cols);
  S21Matrix result(rows, cols);
  m1.setMatrix(7);
  m2.setMatrix(3);
  result.setMatrix(10);
  m1.SumMatrix(m2);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < rows; j++) ASSERT_EQ(m1(i, j), result(i, j));
}
TEST(sumMatrixTest, sum_test_2) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);

  m1.setMatrixEl(0, 0, 1.0);
  m1.setMatrixEl(0, 1, 2.0);
  m1.setMatrixEl(1, 0, 3.0);
  m1.setMatrixEl(1, 1, 4.0);

  m2.setMatrixEl(0, 0, 5.0);
  m2.setMatrixEl(0, 1, 6.0);
  m2.setMatrixEl(1, 0, 7.0);
  m2.setMatrixEl(1, 1, 8.0);

  m1.SumMatrix(m2);

  EXPECT_DOUBLE_EQ(m1(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(m1(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(m1(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(m1(1, 1), 12.0);
}
// Тест на выброс исключения при некорректных размерах матриц
TEST(sumMatrixTest, throwsInvalidArgument_0) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 3);

  EXPECT_THROW(matrix1.SumMatrix(matrix2), std::invalid_argument);
}
TEST(sumMatrixTest, throwsInvalidArgument_1) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 3);

  EXPECT_THROW(matrix1.SumMatrix(matrix2), std::invalid_argument);
}
TEST(sumMatrixTest, throwsInvalidArgument_2) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 2);

  EXPECT_THROW(matrix1.SumMatrix(matrix2), std::invalid_argument);
}
TEST(sumMatrixTest, throwsInvalidArgument_3) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(2, 2);

  EXPECT_THROW(matrix1.SumMatrix(matrix2), std::invalid_argument);
}
TEST(sumMatrixTest, throwsInvalidArgument_4) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 2);

  EXPECT_THROW(matrix1.SumMatrix(matrix2), std::invalid_argument);
}
// Тест для оператора сложения (operator+)
TEST(sumMatrixTest, test_1_addOperator) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  S21Matrix result = matrix1 + matrix2;

  EXPECT_DOUBLE_EQ(result(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 12.0);
}
TEST(sumMatrixTest, test_2_addOperator) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  S21Matrix result = matrix1 + matrix2;

  EXPECT_DOUBLE_EQ(result(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 0.0);
}
TEST(sumMatrixTest, throw_1_addOperator) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 2);

  EXPECT_THROW(matrix1 + matrix2, std::invalid_argument);
}
TEST(sumMatrixTest, throw_2_addOperator) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 3);

  EXPECT_THROW(matrix1 + matrix2, std::invalid_argument);
}
// Тест для оператора +=
TEST(sumMatrixTest, addEqOperator) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  matrix1 += matrix2;

  EXPECT_DOUBLE_EQ(matrix1(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 12.0);
}
// Тест для метода SubMatrix
TEST(subMatrixTest, test_1) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);

  m1(0, 0) = 5.0;
  m1(0, 1) = 6.0;
  m1(1, 0) = 7.0;
  m1(1, 1) = 8.0;
  m2(0, 0) = 1.0;
  m2(0, 1) = 2.0;
  m2(1, 0) = 3.0;
  m2(1, 1) = 4.0;

  m1.SubMatrix(m2);

  EXPECT_DOUBLE_EQ(m1(0, 0), 4.0);
  EXPECT_DOUBLE_EQ(m1(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(m1(1, 0), 4.0);
  EXPECT_DOUBLE_EQ(m1(1, 1), 4.0);
}
// Тест на выброс исключения при некорректных размерах матриц
TEST(subMatrixTest, throw_0) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 3);  // Матрица другого размера

  EXPECT_THROW(matrix1.SubMatrix(matrix2), std::invalid_argument);
}
TEST(subMatrixTest, throw_1) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 3);  // Матрица другого размера

  EXPECT_THROW(matrix1.SubMatrix(matrix2), std::invalid_argument);
}
TEST(subMatrixTest, throw_2) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 2);  // Матрица другого размера

  EXPECT_THROW(matrix1.SubMatrix(matrix2), std::invalid_argument);
}
TEST(subMatrixTest, throw_3) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(2, 2);  // Матрица другого размера

  EXPECT_THROW(matrix1.SubMatrix(matrix2), std::invalid_argument);
}
TEST(subMatrixTest, throw_4) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 2);  // Матрица другого размера

  EXPECT_THROW(matrix1.SubMatrix(matrix2), std::invalid_argument);
}
// Тест для оператора вычитания (operator-)
TEST(subMatrixTest, subOperator) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 10.0;
  matrix1(0, 1) = 20.0;
  matrix1(1, 0) = 30.0;
  matrix1(1, 1) = 40.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.00;
  matrix2(0, 1) = 10.0;
  matrix2(1, 0) = 15.0;
  matrix2(1, 1) = 20.0;

  S21Matrix result = matrix1 - matrix2;

  EXPECT_DOUBLE_EQ(result(0, 0), 5.00);
  EXPECT_DOUBLE_EQ(result(0, 1), 10.00);
  EXPECT_DOUBLE_EQ(result(1, 0), 15.00);
  EXPECT_DOUBLE_EQ(result(1, 1), 20.00);
}
TEST(subMatrixTest, subOperator_throw_0) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 2);

  EXPECT_THROW(matrix1 - matrix2, std::invalid_argument);
}
TEST(subMatrixTest, subOperator_throw_1) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 3);

  EXPECT_THROW(matrix1 - matrix2, std::invalid_argument);
}
// Тест для оператора -=
TEST(subMatrixTest, subEqOperator) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 10.0;
  matrix1(0, 1) = 20.0;
  matrix1(1, 0) = 30.0;
  matrix1(1, 1) = 40.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 10.0;
  matrix2(1, 0) = 15.0;
  matrix2(1, 1) = 20.0;

  matrix1 -= matrix2;

  EXPECT_DOUBLE_EQ(matrix1(0, 0), 5.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 10.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 15.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 20.0);
}
// Тест для метода MulNumber
TEST(mulMatrixNumber, test_1) {
  S21Matrix matrix(2, 2);

  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  matrix.MulNumber(2.0);

  EXPECT_DOUBLE_EQ(matrix(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 8.0);
}
// Тест для оператора умножения на скаляр (operator*(double))
TEST(mulMatrixNumber, test_2_operator) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  S21Matrix result = matrix * 2.0;

  EXPECT_DOUBLE_EQ(result(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 8.0);
}
// Тест для оператора *= (умножение матрицы на скаляр)
TEST(mulMatrixNumber, mulEqNumer) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  matrix *= 2.0;

  EXPECT_DOUBLE_EQ(matrix(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 8.0);
}
// Тест для метода MulMatrix
TEST(mulMatrix, test_1) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);

  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;
  m2(0, 0) = 5.0;
  m2(0, 1) = 6.0;
  m2(1, 0) = 7.0;
  m2(1, 1) = 8.0;

  m1.MulMatrix(m2);

  EXPECT_DOUBLE_EQ(m1(0, 0), 19.0);
  EXPECT_DOUBLE_EQ(m1(0, 1), 22.0);
  EXPECT_DOUBLE_EQ(m1(1, 0), 43.0);
  EXPECT_DOUBLE_EQ(m1(1, 1), 50.0);
}
// Тест для метода MulMatrix
TEST(mulMatrix, test_2) {
  S21Matrix m1(2, 3);
  S21Matrix m2(3, 2);

  m1(0, 0) = 5.0;
  m1(0, 1) = 5.0;
  m1(0, 2) = 1.0;
  m1(1, 0) = 5.0;
  m1(1, 1) = 5.0;
  m1(1, 2) = 1.0;

  m2.setMatrix(4);

  m1.MulMatrix(m2);

  EXPECT_DOUBLE_EQ(m1(0, 0), 44.0);
  EXPECT_DOUBLE_EQ(m1(0, 1), 44.0);
  EXPECT_DOUBLE_EQ(m1(1, 0), 44.0);
  EXPECT_DOUBLE_EQ(m1(1, 1), 44.0);
}
// Тест на выброс исключения при некорректных размерах матриц
TEST(mulMatrix, throw_1) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(4, 2);

  EXPECT_THROW(matrix1.MulMatrix(matrix2), std::invalid_argument);
}
TEST(mulMatrix, test_3) {
  S21Matrix m1(2, 3);
  S21Matrix m2(3, 5);

  m1(0, 0) = 5.0;
  m1(0, 1) = 5.0;
  m1(0, 2) = 1.0;
  m1(1, 0) = 5.0;
  m1(1, 1) = 5.0;
  m1(1, 2) = 1.0;

  m2.setMatrix(4);

  m1.MulMatrix(m2);

  EXPECT_DOUBLE_EQ(m1(0, 0), 44.0);
  EXPECT_DOUBLE_EQ(m1(0, 1), 44.0);
  EXPECT_DOUBLE_EQ(m1(0, 2), 44.0);
  EXPECT_DOUBLE_EQ(m1(0, 3), 44.0);
  EXPECT_DOUBLE_EQ(m1(0, 4), 44.0);
  EXPECT_DOUBLE_EQ(m1(1, 0), 44.0);
  EXPECT_DOUBLE_EQ(m1(1, 1), 44.0);
  EXPECT_DOUBLE_EQ(m1(1, 2), 44.0);
  EXPECT_DOUBLE_EQ(m1(1, 3), 44.0);
  EXPECT_DOUBLE_EQ(m1(1, 4), 44.0);
}
// Тест для оператора умножения матриц (operator*)
TEST(mulMatrix, mulOperator_1) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;

  S21Matrix matrix2(3, 2);
  matrix2(0, 0) =  7.0;
  matrix2(0, 1) =  8.0;
  matrix2(1, 0) =  9.0;
  matrix2(1, 1) =  10.0;
  matrix2(2, 0) =  11.0;
  matrix2(2, 1) =  12.0;

  S21Matrix result = matrix1 * matrix2;

  EXPECT_DOUBLE_EQ(result(0, 0), 58.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 64.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 139.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 154.0);
}
// Тест на проверку исключения при несоответствии размеров матриц
TEST(mulMatrix, mulOperator_throw_1) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 2);

  EXPECT_THROW(matrix1 * matrix2, std::invalid_argument);
}
TEST(mulMatrix, mulOperator_throw_2) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 3);

  EXPECT_THROW(matrix1 * matrix2, std::invalid_argument);
}
// // Тест для оператора *= (умножение матрицы на матрицу)
TEST(mulMatrix, mulEqOperator) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 2.0;
  matrix2(0, 1) = 0.0;
  matrix2(1, 0) = 1.0;
  matrix2(1, 1) = 2.0;

  matrix1 *= matrix2;

  EXPECT_DOUBLE_EQ(matrix1(0, 0), 4.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 8.0);
}

// Тест для оператора присваивания (operator=)
TEST(assignmentMatrix, test_1) {
  // Создаем матрицу 2x2 и заполняем её значениями
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 5.0;
  matrix(0, 1) = 6.0;
  matrix(1, 0) = 7.0;
  matrix(1, 1) = 8.0;

  // Выполняем присваивание через указатель на объект
  S21Matrix *matrix_ptr = &matrix;
  //*matrix_ptr = matrix;

  // Проверяем, что значения не изменились после самоприсваивания
  EXPECT_DOUBLE_EQ(matrix(0, 0), 5.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 6.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 7.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 8.0);
   matrix_ptr->printMatrix();
  //  for (int i{} ; i < matrix_ptr->getRows() ;i ++)
  //  for (int j{} ; j < matrix_ptr->getColumns() ; j ++)
  //  cout << matrix_ptr->operator(i,j);
  // EXPECT_DOUBLE_EQ(matrix_ptr(0, 0), 5.0);
  // EXPECT_DOUBLE_EQ(matrix_ptr(0, 1), 6.0);
  // EXPECT_DOUBLE_EQ(matrix_ptr(1, 0), 7.0);
  // EXPECT_DOUBLE_EQ(matrix_ptr(1, 1), 8.0);
}
// Тест для метода Transpose
TEST(MatrixFunctionTest, Transpose) {
  S21Matrix matrix(2, 3);

  matrix.setMatrixEl(0, 0, 1.0);
  matrix.setMatrixEl(0, 1, 2.0);
  matrix.setMatrixEl(0, 2, 3.0);
  matrix.setMatrixEl(1, 0, 4.0);
  matrix.setMatrixEl(1, 1, 5.0);
  matrix.setMatrixEl(1, 2, 6.0);

  S21Matrix transposed = matrix.Transpose();

  EXPECT_DOUBLE_EQ(transposed.getMatrixEl(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(transposed.getMatrixEl(1, 0), 2.0);
  EXPECT_DOUBLE_EQ(transposed.getMatrixEl(2, 0), 3.0);
  EXPECT_DOUBLE_EQ(transposed.getMatrixEl(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(transposed.getMatrixEl(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(transposed.getMatrixEl(2, 1), 6.0);
}
// Тест для метода GetMinor на матрице 2x2
TEST(GetMinorTest, test_2x2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  S21Matrix minor = matrix.GetMinor(0, 0);

  EXPECT_DOUBLE_EQ(minor(0, 0), 4.0);
}

// Тест для метода GetMinor на матрице 3x3
TEST(GetMinorTest, test1_3x3) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;
  matrix(2, 0) = 7.0;
  matrix(2, 1) = 8.0;
  matrix(2, 2) = 9.0;

  S21Matrix minor = matrix.GetMinor(1, 1);
  // Ожидаемый результат минора (2x2 матрица)
  EXPECT_DOUBLE_EQ(minor(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(minor(0, 1), 3.0);
  EXPECT_DOUBLE_EQ(minor(1, 0), 7.0);
  EXPECT_DOUBLE_EQ(minor(1, 1), 9.0);
}

TEST(GetMinorTest, test2_3x3) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;
  matrix(2, 0) = 7.0;
  matrix(2, 1) = 8.0;
  matrix(2, 2) = 9.0;

  S21Matrix minor = matrix.GetMinor(2, 2);

  // Ожидаемый результат минора (2x2 матрица)
  EXPECT_DOUBLE_EQ(minor(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(minor(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(minor(1, 0), 4.0);
  EXPECT_DOUBLE_EQ(minor(1, 1), 5.0);
}

// Тест для метода GetMinor на матрице 4x4
TEST(GetMinorTest, test_4x4) {
  S21Matrix matrix(4, 4);
  matrix.setMatrixEl(0, 0, 1.0);
  matrix.setMatrixEl(0, 1, 2.0);
  matrix.setMatrixEl(0, 2, 3.0);
  matrix.setMatrixEl(0, 3, 4.0);
  matrix.setMatrixEl(1, 0, 5.0);
  matrix.setMatrixEl(1, 1, 6.0);
  matrix.setMatrixEl(1, 2, 7.0);
  matrix.setMatrixEl(1, 3, 8.0);
  matrix.setMatrixEl(2, 0, 9.0);
  matrix.setMatrixEl(2, 1, 10.0);
  matrix.setMatrixEl(2, 2, 11.0);
  matrix.setMatrixEl(2, 3, 12.0);
  matrix.setMatrixEl(3, 0, 13.0);
  matrix.setMatrixEl(3, 1, 14.0);
  matrix.setMatrixEl(3, 2, 15.0);
  matrix.setMatrixEl(3, 3, 16.0);

  S21Matrix minor = matrix.GetMinor(0, 0);  // Минор для первого элемента

  // Ожидаемый результат минора (3x3 матрица)
  EXPECT_DOUBLE_EQ(minor(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(minor(0, 1), 7.0);
  EXPECT_DOUBLE_EQ(minor(0, 2), 8.0);
  EXPECT_DOUBLE_EQ(minor(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(minor(1, 1), 11.0);
  EXPECT_DOUBLE_EQ(minor(1, 2), 12.0);
  EXPECT_DOUBLE_EQ(minor(2, 0), 14.0);
  EXPECT_DOUBLE_EQ(minor(2, 1), 15.0);
  EXPECT_DOUBLE_EQ(minor(2, 2), 16.0);
}

// Тест для метода GetMinor на матрице 5x5
TEST(GetMinorTest, test_5x5) {
  S21Matrix matrix(5, 5);
  // Заполняем матрицу некоторыми значениями
  int value = 1;
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      matrix.setMatrixEl(i, j, value++);
    }
  }

  S21Matrix minor = matrix.GetMinor(2, 2);  // Минор для элемента в центре

  // Ожидаем, что минор будет матрицей 4x4
  EXPECT_EQ(minor.getRows(), 4);
  EXPECT_EQ(minor.getColumns(), 4);
}

// Тест для метода GetMinor на проверку выброса исключения при некорректных
TEST(GetMinorTest, throw_test) {
  S21Matrix matrix(3, 3);

  EXPECT_THROW(matrix.GetMinor(-1, 1), std::out_of_range);
  EXPECT_THROW(matrix.GetMinor(3, 1), std::out_of_range);
  EXPECT_THROW(matrix.GetMinor(1, -1), std::out_of_range);
  EXPECT_THROW(matrix.GetMinor(1, 3), std::out_of_range);
}

// Тест для мутатора: Изменение размера матрицы на больший
TEST(sizeTest, test_1) {
  S21Matrix matrix(2, 2);  // Создаем матрицу 2x2
  matrix.setMatrixEl(0, 0, 1.0);
  matrix.setMatrixEl(0, 1, 2.0);
  matrix.setMatrixEl(1, 0, 3.0);
  matrix.setMatrixEl(1, 1, 4.0);

  // Изменяем размер на 4x4 с помощью SetSize
  matrix.setSize(4, 4);

  // Проверяем, что старые элементы на месте
  EXPECT_EQ(matrix(0, 0), 1.0);
  EXPECT_EQ(matrix(0, 1), 2.0);
  EXPECT_EQ(matrix(1, 0), 3.0);
  EXPECT_EQ(matrix(1, 1), 4.0);

  // Проверяем, что новые элементы инициализированы нулями
  EXPECT_EQ(matrix(2, 2), 0.0);
  EXPECT_EQ(matrix(3, 3), 0.0);
}
// Тест для мутатора: Изменение размера матрицы на меньший
TEST(sizeTest, test_2) {
  S21Matrix matrix(4, 4);  // Создаем матрицу 4x4
  matrix.setMatrixEl(0, 0, 1.0);
  matrix.setMatrixEl(0, 1, 2.0);
  matrix.setMatrixEl(1, 0, 3.0);
  matrix.setMatrixEl(1, 1, 4.0);
  matrix.setMatrixEl(3, 3, 5.0);

  // Изменяем размер на 2x2
  matrix.setSize(2, 2);

  // Проверяем, что элементы, которые остались, на месте
  EXPECT_EQ(matrix(0, 0), 1.0);
  EXPECT_EQ(matrix(0, 1), 2.0);
  EXPECT_EQ(matrix(1, 0), 3.0);
  EXPECT_EQ(matrix(1, 1), 4.0);

  // Проверяем, что матрица стала меньше
  EXPECT_THROW(matrix(2, 2),
               std::out_of_range);  // Элемента (2, 2) больше не должно быть
}
// Тест для мутатора: Изменение размера на ту же матрицу
TEST(sizeTest, test_3) {
  S21Matrix matrix(3, 3);
  matrix.setMatrixEl(0, 0, 1.0);
  matrix.setMatrixEl(1, 1, 2.0);
  matrix.setMatrixEl(2, 2, 3.0);

  // Изменяем размер на такой же (3x3)
  matrix.setSize(3, 3);

  // Проверяем, что элементы остались на месте
  EXPECT_EQ(matrix(0, 0), 1.0);
  EXPECT_EQ(matrix(1, 1), 2.0);
  EXPECT_EQ(matrix(2, 2), 3.0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

// Тестирование параметризированного конструктора на выброс исключений при
// некорректных размерах
TEST(S21MatrixTest, ConstructorInvalidSize) {
  EXPECT_THROW(S21Matrix(-1, 5),
               std::invalid_argument);  // Отрицательное количество строк
  EXPECT_THROW(S21Matrix(4, 0),
               std::invalid_argument);  // Количество столбцов равно нулю
  EXPECT_THROW(S21Matrix(0, 0),
               std::invalid_argument);  // Оба параметра равны нулю
  EXPECT_THROW(S21Matrix(-3, -3),
               std::invalid_argument);  // Отрицательные значения
}
// Тест на проверку освобождения памяти при повторном выделении
// Тест на конструктор перемещения
TEST(MatrixConstructorTest, MoveConstructor) {
  S21Matrix matrix1(2, 2);
  matrix1.setMatrixEl(0, 0, 1.0);
  matrix1.setMatrixEl(0, 1, 2.0);

  S21Matrix matrix2(std::move(matrix1));  // Перемещение matrix1 в matrix2

  EXPECT_EQ(matrix2.getRows(), 2);
  EXPECT_EQ(matrix2.getColumns(), 2);
  EXPECT_DOUBLE_EQ(matrix2(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix2(0, 1), 2.0);

  // Проверяем, что matrix1 стал пустым после перемещения
  EXPECT_EQ(matrix1.getRows(), 0);
  EXPECT_EQ(matrix1.getColumns(), 0);
}

// Тесты для оператора индексации
TEST(MatrixOperatorTests, IndexInBounds) {
  S21Matrix matrix(3, 3);
  matrix(1, 1) = 5.0;  // Устанавливаем значение по индексу (1, 1)
  EXPECT_EQ(matrix(1, 1),
            5.0);  // Проверяем, что значение установлено корректно
}

// Тест для оператора индексации с выходом за пределы
TEST(MatrixOperatorTests, IndexOutOfBoundsThrows) {
  S21Matrix matrix(3, 3);

  // Ожидаем, что будет выброшено исключение при попытке доступа к
  // недопустимым индексам
  EXPECT_THROW(matrix(3, 3), std::out_of_range);  // Индекс вне границ
  EXPECT_THROW(matrix(-1, 0), std::out_of_range);  // Отрицательный индекс
  EXPECT_THROW(matrix(0, 3), std::out_of_range);  // Индекс столбца вне границ
  EXPECT_THROW(matrix(-1, -1), std::out_of_range);  // Обе индекса отрицательные
}

// Тест для метода EqMatrix, проверка на равенство матриц одного размера
TEST(MatrixFunctionTest, EqMatrixSameSizeEqual) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 4.0;

  EXPECT_TRUE(matrix1.EqMatrix(matrix2));  // Ожидаем, что матрицы равны
}

// Тест для метода EqMatrix, проверка на равенство матриц одного размера с
// неравными элементами
TEST(MatrixFunctionTest, EqMatrixSameSizeNotEqual) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 5.0;  // Измененный элемент

  EXPECT_FALSE(matrix1.EqMatrix(matrix2));  // Ожидаем, что матрицы не равны
}

/*********************************************************************************
 * ********************************************************************************
 * ********************************************************************************
 * ********************************************************************************
 * ********************************************************************************
 */

// Тест для метода CalcComplements: алгебраические дополнения для матрицы 2x2
TEST(MatrixComplementTests, CalcComplementsValidFor2x2) {
  // Создаем квадратную матрицу 2x2
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 4.0;
  matrix(0, 1) = 7;
  matrix(1, 0) = 2;
  matrix(1, 1) = 6;

  // Ожидаем, что вызов CalcComplements не выбросит исключение
  EXPECT_NO_THROW({
    S21Matrix complements = matrix.CalcComplements();

    // Проверка вычисленных алгебраических дополнений
    EXPECT_EQ(complements(0, 0), 6);  // Алгебраическое дополнение для (0, 0)
    EXPECT_EQ(complements(0, 1), -2);  // Алгебраическое дополнение для (0,1)
    EXPECT_EQ(complements(1, 0), -7);  // Алгебраическое дополнение для (1, 0)
    EXPECT_EQ(complements(1, 1), 4);  // Алгебраическое дополнение для (1, 1)
  });
}

// проверка вычисления для единичной матрицы
TEST(CalcComplements, test_2x2) {
  // Создаем единичную матрицу 2x2
  S21Matrix identity(2, 2);
  identity.setMatrixEl(0, 0, 1);
  identity.setMatrixEl(0, 1, 0);
  identity.setMatrixEl(1, 0, 0);
  identity.setMatrixEl(1, 1, 1);

  // Ожидаем, что вызов CalcComplements не выбросит исключение
  EXPECT_NO_THROW({
    S21Matrix complements = identity.CalcComplements();

    // Для единичной матрицы алгебраические дополнения должны совпадать с ней
    EXPECT_EQ(complements(0, 0), 1);
    EXPECT_EQ(complements(0, 1), 0);
    EXPECT_EQ(complements(1, 0), 0);
    EXPECT_EQ(complements(1, 1), 1);
  });
}

TEST(CalcComplements, test_1x1) {
  // Создаем единичную матрицу 2x2
  S21Matrix identity(1, 1);
  identity(0, 0) = 10.2;
  S21Matrix calcComp = identity.CalcComplements();

  EXPECT_EQ(calcComp(0, 0), 1);
}

// Тест для метода CalcComplements: проверка на матрицу с нулями
TEST(CalcComplements, test_1) {
  S21Matrix matrix(3, 3);
  matrix.setMatrixEl(0, 0, 0);
  matrix.setMatrixEl(0, 1, 2);
  matrix.setMatrixEl(0, 2, 0);
  matrix.setMatrixEl(1, 0, 0);
  matrix.setMatrixEl(1, 1, 1);
  matrix.setMatrixEl(1, 2, 4);
  matrix.setMatrixEl(2, 0, 5);
  matrix.setMatrixEl(2, 1, 0);
  matrix.setMatrixEl(2, 2, 0);

  // Ожидаем, что CalcComplements выполнится без исключений
  EXPECT_NO_THROW({
    S21Matrix complements = matrix.CalcComplements();

    // Проверяем алгебраические дополнения
    EXPECT_EQ(complements(0, 0), 0);  // Алгебраическое дополнение для (0,0)
    EXPECT_EQ(complements(0, 1), 20);  // Алгебраическое дополнение для (0,1)
    EXPECT_EQ(complements(0, 2), -5);  // Алгебраическое дополнение для (0,2)
    EXPECT_EQ(complements(1, 0), 0);  // Алгебраическое дополнение для (1,0)
    EXPECT_EQ(complements(1, 1), 0);  // Алгебраическое дополнение для (1,1)
    EXPECT_EQ(complements(1, 2), 10);  // Алгебраическое дополнение для (1,2)
    EXPECT_EQ(complements(2, 0), 8);  // Алгебраическое дополнение для (2,0)
    EXPECT_EQ(complements(2, 1), 0);  // Алгебраическое дополнение для (2,1)
    EXPECT_EQ(complements(2, 2), 0);  // Алгебраическое дополнение для (2,2)
  });
}

// сключения для неквадратной матрицы
TEST(CalcComplements, throw_cc) {
  S21Matrix matrix(2, 3);
  EXPECT_THROW(matrix.CalcComplements(), std::invalid_argument);
}

//  Тест для метода Determinant: матрица 1x1
TEST(MatrixFunctionTest, DeterminantTest1x1) {
  S21Matrix matrix(1, 1);
  matrix.setMatrixEl(0, 0, 42.0);

  double determinant = matrix.Determinant();
  EXPECT_DOUBLE_EQ(determinant, 42.0);
}

// Тест для метода Determinant: матрица 2x2
TEST(MatrixFunctionTest, DeterminantTest2x2) {
  S21Matrix matrix(2, 2);
  matrix.setMatrixEl(0, 0, 1.0);
  matrix.setMatrixEl(0, 1, 2.0);
  matrix.setMatrixEl(1, 0, 3.0);
  matrix.setMatrixEl(1, 1, 4.0);

  double determinant = matrix.Determinant();
  EXPECT_DOUBLE_EQ(determinant, -2.0);
}

// Тест для метода Determinant: матрица 3x3 (чередование знаков)
TEST(MatrixFunctionTest, DeterminantSignAlternationTest) {
  S21Matrix matrix(3, 3);
  matrix.setMatrixEl(0, 0, 1.0);
  matrix.setMatrixEl(0, 1, 2.0);
  matrix.setMatrixEl(0, 2, 3.0);
  matrix.setMatrixEl(1, 0, 0.0);
  matrix.setMatrixEl(1, 1, 1.0);
  matrix.setMatrixEl(1, 2, 4.0);
  matrix.setMatrixEl(2, 0, 5.0);
  matrix.setMatrixEl(2, 1, 6.0);
  matrix.setMatrixEl(2, 2, 0.0);

  double determinant = matrix.Determinant();
  EXPECT_DOUBLE_EQ(determinant, 1.0);  // Ожидаемое значение для матрицы 3x3
}

// Тест для метода Determinant: для неквадратной матрицы
TEST(MatrixFunctionTest, DeterminantNonSquareMatrixTest) {
  S21Matrix matrix(2, 3);  // Неквадратная матрица 2x3
  matrix.setMatrixEl(0, 0, 1.0);
  matrix.setMatrixEl(0, 1, 2.0);
  matrix.setMatrixEl(0, 2, 3.0);
  matrix.setMatrixEl(1, 0, 4.0);
  matrix.setMatrixEl(1, 1, 5.0);
  matrix.setMatrixEl(1, 2, 6.0);

  // Ожидаем выброс исключения invalid_argument
  EXPECT_THROW(matrix.Determinant(), std::invalid_argument);
}

// Тест для метода Inverse: инверсия матрицы 1x1
TEST(MatrixFunctionTest, InverseMatrix1x1) {
  // Тест для инверсии матрицы 1x1 с ненулевым значением
  S21Matrix one_by_one(1, 1);
  one_by_one(0, 0) = 5.0;

  S21Matrix inverse = one_by_one.InverseMatrix();
  EXPECT_NEAR(inverse(0, 0), 1.0 / 5.0, 1e-5);
}

// Тест для метода Inverse: инверсия матрицы 2x2
TEST(MatrixFunctionTest, InverseMatrix2x2) {
  S21Matrix two_by_two(2, 2);
  two_by_two(0, 0) = 4.0;
  two_by_two(0, 1) = 7.0;
  two_by_two(1, 0) = 2.0;
  two_by_two(1, 1) = 6.0;

  S21Matrix inverse = two_by_two.InverseMatrix();

  EXPECT_NEAR(inverse(0, 0), 0.6, 1e-5);
  EXPECT_NEAR(inverse(0, 1), -0.7, 1e-5);
  EXPECT_NEAR(inverse(1, 0), -0.2, 1e-5);
  EXPECT_NEAR(inverse(1, 1), 0.4, 1e-5);
}

// Тест для метода Inverse: для вырожденной матрицы (определитель равен 0)
TEST(MatrixFunctionTest, SingularMatrixThrowsException) {
  S21Matrix singular(2, 2);
  singular(0, 0) = 1.0;
  singular(0, 1) = 2.0;
  singular(1, 0) = 2.0;
  singular(1, 1) = 4.0;

  EXPECT_THROW(singular.InverseMatrix(), std::invalid_argument);
}

// Тест для метода Inverse: для неквадратной матрицы
TEST(MatrixFunctionTest, NonSquareMatrixThrowsException) {
  S21Matrix non_square(2, 3);
  non_square(0, 0) = 1.0;
  non_square(0, 1) = 2.0;
  non_square(0, 2) = 3.0;
  non_square(1, 0) = 4.0;
  non_square(1, 1) = 5.0;
  non_square(1, 2) = 6.0;

  EXPECT_THROW(non_square.InverseMatrix(), std::invalid_argument);
}
