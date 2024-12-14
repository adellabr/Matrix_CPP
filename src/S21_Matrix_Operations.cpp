#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) return false;
  bool is_equal = true;
  for (int i = 0; is_equal && i < this->rows_; i++) {
    for (int j = 0; is_equal && j < this->cols_; j++) {
      if (this->matrix_[i][j] != other.matrix_[i][j]) is_equal = false;
    }
  }
  return is_equal;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw invalid_argument("different matrix dimensions");
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw invalid_argument("different matrix dimensions");
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (this->cols_ != other.rows_) {
    throw invalid_argument(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix.");
  }
  S21Matrix result(this->rows_, other.cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int k = 0; k < other.cols_; k++) {
      result.matrix_[i][k] = 0;
      for (int j = 0; j < this->cols_; j++) {
        result.matrix_[i][k] += this->matrix_[i][j] * other.matrix_[j][k];
      }
    }
  }
  *this = result;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(this->cols_, this->rows_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      result.matrix_[j][i] = this->matrix_[i][j];
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  if (this->cols_ != this->rows_) {
    throw invalid_argument(" The matrix is not square.");
  }
  double det = -1;
  int k1 = 0;
  S21Matrix temp = (*this);
  for (int k = 1; k < rows_; k++, k1++) {
    for (int i = k; i < this->rows_; i++) {
      int j = 0;
      if (temp.matrix_[k - 1][k1] == 0) {
        for (; j < this->cols_; j++) {
          temp.matrix_[i - 1][j] += temp.matrix_[i][j];
        }
      }
      if (temp.matrix_[k - 1][k1] == 0) {
        continue;
      } else {
        j = 0;
        double koef = temp.matrix_[i][k1] / temp.matrix_[k - 1][k1];
        for (; j < this->cols_; j++) {
          temp.matrix_[i][j] =
              temp.matrix_[k - 1][j] * koef - temp.matrix_[i][j];
        }
      }
    }
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      if (i == j) det *= temp.matrix_[i][j];
    }
  }
  return det;
}

S21Matrix S21Matrix::Minors(int i_2, int j_2) {
  S21Matrix minors(this->rows_ - 1, this->cols_ - 1);
  int i_1 = 0;
  for (int i = 0; i < this->rows_; i++) {
    int j_1 = 0;
    for (int j = 0; j < this->cols_; j++) {
      if (i != i_2 && j != j_2) {
        minors.matrix_[i_1][j_1] = this->matrix_[i][j];
        j_1++;
        if (j_1 == minors.rows_) i_1++;
      }
    }
  }
  return minors;
}

S21Matrix S21Matrix::CalcComplements() {
  if (this->cols_ != this->rows_) {
    throw invalid_argument(" The matrix is not square.");
  }
  S21Matrix result(this->rows_, this->cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      S21Matrix minors = (*this).Minors(i, j);
      result.matrix_[i][j] = minors.Determinant();
      result.matrix_[i][j] = pow(-1, (i + j)) * result.matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = (*this).Determinant();
  if (det == 0) {
    throw invalid_argument("Matrix determinant is 0.");
  }
  S21Matrix complem = (*this).CalcComplements();
  S21Matrix transposed = complem.Transpose();
  S21Matrix result = transposed * (1 / det);
  return result;
}
