#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <cmath>
#include <iostream>
#include <stdexcept>

#define D_MATRIX 0
#define E_MATIX 1.0E-7
#define THROW_INV_PARAM "Invalid rows or/and columns!"
#define THROW_ROW_EQ_COL "columns 1s matrix not equal rows 2s matrix"
#define THROW_INDEX_OUT "Incorrect input, index is out of range"
#define THROW_SIZE "matrix not equal size"
#define THROW_SQR "Matrix not a square"
#define THROW_DETEMINANT_ZERO "Inverse matrix not exist (determinant is zero)"

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

 public:

  int getRows() const noexcept { return rows_; }
  int getColumns() const noexcept { return cols_; }

  S21Matrix() noexcept;
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);  // Конструктор копирования
  S21Matrix(S21Matrix&& other) noexcept;  // Конструктор переноса

  ~S21Matrix() noexcept {
    // std::cout << "matrix size:" << rows_<< "x" << cols_ << "deleted\n" ;
   deallocateMemory();
  };

  bool EqMatrix(const S21Matrix& other) const noexcept;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() noexcept;
  S21Matrix GetMinor(int row, int col) const;
  S21Matrix InverseMatrix();
  double Determinant() const;
  S21Matrix CalcComplements() const;

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(double num);
  bool operator==(const S21Matrix& other) const noexcept;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(double num) noexcept;

  double& operator()(int row, int col);

  // Other methods..
  void setMatrix() noexcept;
  void setMatrix(int m) noexcept;
  void copyMatrix(const S21Matrix& other) noexcept;
  void setSize(int newRows, int newCols);
  void deallocateMemory();

};

#endif
