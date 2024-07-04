#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <algorithm>
#include <stdexcept>
#include <vector>

template <typename T>

class Matrix {
 public:
  Matrix(int rows, int columns) : n_row_{rows}, n_column_{columns} {
    if (rows <= 0 || columns <= 0) {
      throw std::domain_error("number of rows/columns is inadequate");
    }
    vector_.resize(rows * columns);
  }

  Matrix(Matrix<T> const& matrix)
      : n_row_{matrix.GetHeight()}, n_column_{matrix.GetLength()} {
    vector_.resize(n_row_ * n_column_);
    for (int i = 1; i <= matrix.GetHeight(); ++i) {
      for (int j = 1; j <= matrix.GetLength(); ++j) {
        (*this)(i, j) = matrix(i, j);
      }
    }
  }

  void CheckInRange(int row, int column) const {
    if (row <= 0 || column <= 0) {
      throw std::out_of_range("negative or zero indexes not accepted");
    }
    if (row > n_row_ || column > n_column_)
      throw std::out_of_range("matrix is out of range");
  };

  void for_all(void (*f)(T&)) {
    std::for_each(vector_.begin(), vector_.end(), f);
  }

  T& operator()(int row, int column) {
    CheckInRange(row, column);
    return vector_[CalculateIndex(row, column)];
  }

  T operator()(int row, int column) const {
    CheckInRange(row, column);
    return vector_[CalculateIndex(row, column)];
  }

  void operator=(const Matrix<T>& to_copy) {
    if (to_copy.GetHeight() != n_row_ || to_copy.GetLength() != n_column_) {
      throw std::out_of_range("matrixes are incompatible for copy");
    }
    for (int i = 1; i <= n_row_; ++i) {
      for (int j = 1; j <= n_column_; ++j) {
        (*this)(i, j) = to_copy(i, j);
      }
    }
  };

  int GetHeight() const { return n_row_; }
  int GetLength() const { return n_column_; }

 private:
  std::vector<T> vector_;
  int n_row_;
  int n_column_;

  int CalculateIndex(int row, int column) const {
    return n_column_ * (row - 1) + (column - 1);
  }
};

template <typename T>
bool IsInRange(Matrix<T> const& matrix, int i, int j) {
  if (i <= 0 || j <= 0 || i > matrix.GetHeight() || j > matrix.GetLength())
    return false;
  return true;
}

#endif