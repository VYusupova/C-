  double getMatrixEl(int i, int j) {
    if (i >= rows_ || j >= cols_) {
      throw std::out_of_range(THROW_INDEX_OUT);
    }
    return matrix_[i][j];
  }

    void setMatrixEl(int i, int j, double element) {
    if (i >= rows_ || j >= cols_) {
      throw std::out_of_range(THROW_INDEX_OUT);
    } else
      matrix_[i][j] = element;
  }


  void S21Matrix ::printMatrix() noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      std::cout << matrix_[i][j] << " ";
    }
    std::cout << "\n";
  }
  std::cout << "end\n";
}

  void setRows(int newRows) { setSize(newRows, cols_); }
  void setCols(int newCols) { setSize(rows_, newCols); }