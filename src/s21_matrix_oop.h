#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H
#include <cmath>
#include <iostream>
using namespace std;

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

 public:
  S21Matrix();
  S21Matrix(int rows);
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  int getRows();
  int getCols();
  void setRows(int rows);
  void setCols(int cols);
  void Set_Matrix(double strat, double step);

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  double Determinant();
  S21Matrix CalcComplements();
  S21Matrix Minors(int i_2, int j_2);
  S21Matrix InverseMatrix();

  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(double num);
  S21Matrix operator*(const S21Matrix& other);

  bool operator==(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(double num);
  S21Matrix& operator*=(const S21Matrix& other);
  double* operator[](int row);
  double& operator()(int row, int col);

  friend S21Matrix operator*(double num, const S21Matrix& other);
};

#endif