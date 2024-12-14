#include "s21_matrix_oop.h"

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this->matrix_ != nullptr) {
    for (int i = 0; i < this->rows_; i++) {
      delete[] this->matrix_[i];
    }
    delete[] this->matrix_;
  }
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;

  this->matrix_ = new double*[this->rows_];
  for (int i = 0; i < this->rows_; i++) {
    this->matrix_[i] = new double[this->rows_];
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->rows_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix result = *this;
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix result = *this;
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(double num) {
  S21Matrix result = *this;
  result.MulNumber(num);
  return result;
}

S21Matrix operator*(double num, const S21Matrix& other) {
  S21Matrix result = other;
  result.MulNumber(num);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result = *this;
  result.MulMatrix(other);
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) {
  return (*this).EqMatrix(other);
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  (*this).SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  (*this).SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(double num) {
  (*this).MulNumber(num);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  (*this).MulMatrix(other);
  return *this;
}

double* S21Matrix::operator[](int row) { return this->matrix_[row]; }

double& S21Matrix::operator()(int row, int col) {
  if (row < 0 || row >= this->rows_ || col < 0 || col >= this->cols_) {
    throw invalid_argument("Index is outside the matrix");
  }
  return this->matrix_[row][col];
}