#include "s21_matrix_oop.h"

// Конструктор без параметров вызвает конструктор с параметрами
S21Matrix ::S21Matrix() noexcept : S21Matrix(3, 3){}

// Конструктор с параметрами
S21Matrix::S21Matrix(int rows, int cols)
    : rows_(rows), cols_(cols), matrix_(nullptr) {
  if (rows <= 0 || cols <= 0) throw std::invalid_argument(THROW_INV_PARAM);

  matrix_ = new double* [rows_] {};
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]{};
  }
  setMatrix();
}

// Конструктор копирования матрицы // делегирование конструктора
S21Matrix ::S21Matrix(const S21Matrix& other)
    : S21Matrix(other.rows_, other.cols_) {
  copyMatrix(other);
}

// Конструктор перемещения
S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

bool S21Matrix ::EqMatrix(const S21Matrix& other) const noexcept {
  bool result = true;

  if (rows_ != other.rows_) result = false;
  if (cols_ != other.cols_) result = false;

  for (int i = 0; i < rows_ && result; i++) {
    for (int j = 0; j < cols_ && result; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > E_MATIX) result = false;
    }
  }
  return result;
}

void S21Matrix ::SumMatrix(const S21Matrix& other) {
  if (rows_ == other.rows_ && cols_ == other.cols_)
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
      }
    }
  else
    throw std::invalid_argument(THROW_SIZE);
}

void S21Matrix ::SubMatrix(const S21Matrix& other) {
  if (rows_ == other.rows_ && cols_ == other.cols_)
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
      }
    }
  else
    throw std::invalid_argument(THROW_SIZE);
}

void S21Matrix ::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(THROW_ROW_EQ_COL);
  } else {
    S21Matrix result(rows_, other.cols_);

    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        result.matrix_[i][j] = 0.0;
        for (int k = 0; k < cols_; ++k) {
          result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
        }
      }
    }
    this->~S21Matrix();
    rows_ = result.rows_;
    cols_ = result.cols_;
    matrix_ = result.matrix_;
    result.matrix_ = nullptr;
  }
}

S21Matrix S21Matrix ::Transpose() noexcept {
  S21Matrix transposed(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      transposed.matrix_[j][i] = matrix_[i][j];
    }
  }
  return transposed;
}
S21Matrix S21Matrix::GetMinor(int row, int col) const {
  S21Matrix minor(rows_ - 1, cols_ - 1);
  for (int i = 0, minor_i = 0; i < rows_; i++) {
    if (i == row) continue;  // Пропускаем строку, которую нужно удалить
    for (int j = 0, minor_j = 0; j < cols_; j++) {
      if (j == col) continue;  // Пропускаем столбец, который нужно удалить
      minor(minor_i, minor_j) = matrix_[i][j];
      ++minor_j;
    }
    ++minor_i;
  }
  return minor;
}
S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::invalid_argument(THROW_SQR);
  }

  S21Matrix complements(rows_, cols_);
  if (rows_ == 1) {
    complements(0, 0) = 1;
    return complements;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor = GetMinor(i, j);
      double determinant = minor.Determinant();
      // Вычисляем знак по формуле (-1)^(i+j)
      double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
      complements(i, j) = sign * determinant;
    }
  }
  return complements;
}
double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::invalid_argument(THROW_SQR);
  }

  if (rows_ == 1) return matrix_[0][0];
  if (rows_ == 2)
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];

  double determinant = 0.0;
  // Инициализируем переменную для хранения значения определителя.

  // Для матриц размером больше 2x2 вычисляем определитель рекурсивно, используя
  // разложение по первому ряду.
  for (int j = 0; j < cols_; j++) {
    S21Matrix minor =
        GetMinor(0, j);  // Получаем минор, исключая текущую строку и столбец.

    // Вычисляем определитель с учетом знака по формуле (-1)^(i+j) и суммируем.
    determinant += (j % 2 == 0 ? 1 : -1) * matrix_[0][j] * minor.Determinant();
  }

  return determinant;
}
S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw std::invalid_argument(THROW_SQR);
  }

  double det = Determinant();
  if (det == 0) {
    throw std::invalid_argument(THROW_DETEMINANT_ZERO);
  }

  // Специальный случай для матрицы 1x1
  if (rows_ == 1) {
    S21Matrix inverse(1, 1);
    inverse(0, 0) = 1.0 / matrix_[0][0];  // Инициализируем значение
    return inverse;
  }

  // Вычисляем матрицу алгебраических дополнений и транспонируем её
  S21Matrix adjugate = CalcComplements().Transpose();

  // Умножаем союзную матрицу на 1/детерминант
  adjugate.MulNumber(1.0 / det);

  return adjugate;
}
S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}
S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}
S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}
S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}
bool S21Matrix::operator==(const S21Matrix& other) const noexcept {
  return EqMatrix(other);
}
S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {  // Проверка на самоприсваивание
    setSize(other.rows_, other.cols_);  // Изменяем размеры матрицы
    copyMatrix(other);
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  // Проверка на самоприсваивание
  if (this != &other) {
    SumMatrix(other);
  }
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  if (this != &other) {
    SubMatrix(other);
  }
  return *this;
}

S21Matrix& S21Matrix::operator*=(double num) noexcept {
  MulNumber(num);  // Умножение на число, здесь самоприсваивание не требуется
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  if (this != &other) {
    MulMatrix(other);
  }
  return *this;
}

double& S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_) {
    throw std::out_of_range(THROW_INDEX_OUT);
  }
  if (row < 0 || col < 0) {
    throw std::out_of_range(THROW_INDEX_OUT);
  }
  return matrix_[row][col];
}

// Other methods..
void S21Matrix ::setMatrix() noexcept { setMatrix(D_MATRIX); }
void S21Matrix ::setMatrix(int number) noexcept {
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = number;
    }
}
void S21Matrix ::copyMatrix(const S21Matrix& other) noexcept {
  // что если размеры матриц не совпадают
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
}


  void S21Matrix ::setSize(int newRows, int newCols) {
    S21Matrix temp(newRows, newCols);

    // Определяем минимальные размеры для копирования существующих элементов
    int minRows = (rows_ < newRows) ? rows_ : newRows;
    int minCols = (cols_ < newCols) ? cols_ : newCols;

    for (int i = 0; i < minRows; i++) {
      for (int j = 0; j < minCols; j++) {
        temp.matrix_[i][j] = matrix_[i][j];
      }
    }

    deallocateMemory();

    // Перемещаем указатель на новую матрицу
    matrix_ = temp.matrix_;
    rows_ = newRows;
    cols_ = newCols;

    // Обнуляем указатель у временной матрицы, чтобы избежать двойного
    // освобождения памяти
    temp.matrix_ = nullptr;
  }

  void S21Matrix :: deallocateMemory() {
    if (matrix_) {
      for (int i = 0; i < rows_; ++i) {
        delete[] matrix_[i];  // Удаляем строки матрицы
        matrix_[i] = nullptr;
      }
      delete[] matrix_;  // Удаляем указатель на массив указателей
      matrix_ = nullptr;  // Сбрасываем указатель
    }
    rows_ = 0;
    cols_ = 0;
  }

