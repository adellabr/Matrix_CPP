#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  rows_ = 3;
  cols_ = 3;
  matrix_ = new double *[rows_] {};
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[rows_]{};
  }
}

S21Matrix::S21Matrix(int rows) {
  if (rows <= 0) {
    throw invalid_argument("received negative value");
  }
  rows_ = rows;
  cols_ = rows;
  matrix_ = new double *[rows_] {};
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[rows_]{};
  }
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    throw invalid_argument("received negative value");
  }
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double *[rows_] {};
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols]{};
  }
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = new double *[this->rows_];
  for (int i = 0; i < this->rows_; i++) {
    this->matrix_[i] = new double[this->cols_];
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = other.matrix_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

int S21Matrix::getRows() { return this->rows_; }

int S21Matrix::getCols() { return this->cols_; }

void S21Matrix::setRows(int rows) {
  if (rows <= 0) {
    throw invalid_argument("received negative value");
  }
  S21Matrix temp = (*this);
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  matrix_ = nullptr;
  matrix_ = new double *[rows] {};
  for (int i = 0; i < rows; i++) {
    matrix_[i] = new double[cols_]{};
  }
  if (rows < rows_) rows_ = rows;
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = temp.matrix_[i][j];
    }
  }
  rows_ = rows;
}

void S21Matrix::setCols(int cols) {
  if (cols <= 0) {
    throw invalid_argument("received negative value");
  }
  S21Matrix temp = (*this);
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols]{};
  }
  if (cols < cols_) cols_ = cols;
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = temp.matrix_[i][j];
    }
  }
  cols_ = cols;
}

void S21Matrix::Set_Matrix(double start, double step) {
  double value = start;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = value;
      value += step;
    }
  }
}
