#include <stdexcept>

#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

#define EPSILON 1e-6

TEST(TEST_, DEFAULT_CONSTRUCTOR) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.getRows(), 3);
  EXPECT_EQ(matrix.getCols(), 3);
}

TEST(TEST_, CONSTRUCTOR_SQUAERE) {
  S21Matrix matrix(4);
  EXPECT_EQ(matrix.getRows(), 4);
  EXPECT_EQ(matrix.getCols(), 4);
  EXPECT_THROW(S21Matrix matrix2(0), std::invalid_argument);
}

TEST(TEST_, CONSTRUCTOR_ROW_COL) {
  S21Matrix matrix(2, 4);
  EXPECT_EQ(matrix.getRows(), 2);
  EXPECT_EQ(matrix.getCols(), 4);
  EXPECT_THROW(S21Matrix matrix2(5, -1), std::invalid_argument);
}

TEST(TEST_, COPY_1) {
  S21Matrix matrix1(3, 4);
  matrix1.Set_Matrix(-1.231, 0.9492);
  S21Matrix matrix2(matrix1);
  EXPECT_EQ(matrix1.getRows(), matrix2.getRows());
  EXPECT_EQ(matrix1.getCols(), matrix2.getCols());
  for (int i = 0; i < matrix1.getRows(); i++) {
    for (int j = 0; j < matrix1.getCols(); j++) {
      EXPECT_NEAR(matrix1[i][j], matrix2[i][j], EPSILON);
    }
  }
}

TEST(TEST_, COPY_2) {
  S21Matrix matrix1(1, 1);
  matrix1.Set_Matrix(-1.231, 0.9492);
  S21Matrix matrix2(matrix1);
  EXPECT_EQ(matrix1.getRows(), matrix2.getRows());
  EXPECT_EQ(matrix1.getCols(), matrix2.getCols());
  for (int i = 0; i < matrix1.getRows(); i++) {
    for (int j = 0; j < matrix1.getCols(); j++) {
      EXPECT_NEAR(matrix1[i][j], matrix2[i][j], EPSILON);
    }
  }
}

TEST(TEST_, MOVE) {
  S21Matrix matrix1(4, 6);
  matrix1.Set_Matrix(-1.231, 0.9492);
  S21Matrix matrix2(matrix1);
  S21Matrix matrix3(std::move(matrix1));
  EXPECT_EQ(matrix2.getRows(), matrix3.getRows());
  EXPECT_EQ(matrix2.getCols(), matrix3.getCols());
  for (int i = 0; i < matrix1.getRows(); i++) {
    for (int j = 0; j < matrix1.getCols(); j++) {
      EXPECT_NEAR(matrix2[i][j], matrix3[i][j], EPSILON);
    }
  }
  EXPECT_EQ(matrix1.getRows(), 0);
  EXPECT_EQ(matrix1.getCols(), 0);
}

TEST(TEST_, SET_ROW) {
  S21Matrix matrix(2, 4);
  matrix.setRows(5);
  EXPECT_EQ(matrix.getRows(), 5);
  EXPECT_THROW(matrix.setRows(-5), std::invalid_argument);
}

TEST(TEST_, SET_COL) {
  S21Matrix matrix(2, 4);
  matrix.setCols(5);
  EXPECT_EQ(matrix.getCols(), 5);
}

TEST(TEST_, SET_COL_2) {
  S21Matrix matrix(2, 4);
  EXPECT_THROW(matrix.setCols(-5), std::invalid_argument);
}

TEST(TEST_, INDEX_TEST) {
  S21Matrix matrix(2, 2);
  EXPECT_THROW(matrix(0, -1), std::invalid_argument);
  EXPECT_THROW(matrix(0, 2), std::invalid_argument);
}

TEST(TEST_, MATH_ADD_TEST) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  S21Matrix matrix3(2, 3);
  matrix1(0, 0) = 0.15;
  matrix1(0, 1) = 2.04;
  matrix1(1, 0) = -3.00006;
  matrix1(1, 1) = 40;

  matrix2(0, 0) = 0;
  matrix2(0, 1) = -2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 25.02;
  S21Matrix matrix = matrix1 + matrix2;
  EXPECT_EQ(matrix.getCols(), 2);
  EXPECT_EQ(matrix.getRows(), 2);
  EXPECT_NEAR(matrix(0, 0), 0.15, EPSILON);
  EXPECT_NEAR(matrix(0, 1), 0.04, EPSILON);
  EXPECT_NEAR(matrix(1, 0), -0.00006, EPSILON);
  EXPECT_NEAR(matrix(1, 1), 65.02, EPSILON);
  EXPECT_THROW(matrix1 - matrix3, std::invalid_argument);
}

TEST(TEST_, MATH_SUB_TEST) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  S21Matrix matrix3(2, 3);
  matrix1(0, 0) = 14.02;
  matrix1(0, 1) = 458.20;
  matrix1(1, 0) = 4389;
  matrix1(1, 1) = -0.1;

  matrix2(0, 0) = 0.02;
  matrix2(0, 1) = 458;
  matrix2(1, 0) = 4390;
  matrix2(1, 1) = 0.9;

  S21Matrix matrix = matrix1 - matrix2;
  EXPECT_EQ(matrix.getCols(), 2);
  EXPECT_EQ(matrix.getRows(), 2);
  EXPECT_NEAR(matrix(0, 0), 14, EPSILON);
  EXPECT_NEAR(matrix(0, 1), 0.2, EPSILON);
  EXPECT_NEAR(matrix(1, 0), -1, EPSILON);
  EXPECT_NEAR(matrix(1, 1), -1, EPSILON);
  EXPECT_THROW(matrix1 - matrix3, std::invalid_argument);
}

TEST(TEST_, MATH_MUL_NUMBER_TEST) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 0;
  matrix1(0, 1) = 9.111111;
  matrix1(1, 0) = -0.94;
  matrix1(1, 1) = -44;

  S21Matrix matrix = matrix1 * -5.5;
  EXPECT_EQ(matrix.getCols(), 2);
  EXPECT_EQ(matrix.getRows(), 2);
  EXPECT_NEAR(matrix(0, 0), 0, EPSILON);
  EXPECT_NEAR(matrix(0, 1), -50.111111, EPSILON);
  EXPECT_NEAR(matrix(1, 0), 5.17, EPSILON);
  EXPECT_NEAR(matrix(1, 1), 242, EPSILON);
}

TEST(TEST_, MATH_MUL_MATRIX_TEST) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 2);
  S21Matrix matrix3(2, 3);
  matrix1(0, 0) = 12.0;
  matrix1(0, 1) = 0.4;
  matrix1(0, 2) = -3.0;
  matrix1(1, 0) = 92.0;
  matrix1(1, 1) = -1.1;
  matrix1(1, 2) = 4.0;

  matrix2(0, 0) = 0.1;
  matrix2(0, 1) = -3.2;
  matrix2(1, 0) = 0.0;
  matrix2(1, 1) = -74.0;
  matrix2(2, 0) = -23.0;
  matrix2(2, 1) = 555.0;

  S21Matrix matrix = matrix1 * matrix2;
  EXPECT_EQ(matrix1.getRows(), 2);
  EXPECT_EQ(matrix.getCols(), 2);

  EXPECT_NEAR(matrix(0, 0), 70.2, EPSILON);
  EXPECT_NEAR(matrix(0, 1), -1733, EPSILON);
  EXPECT_NEAR(matrix(1, 0), -82.8, EPSILON);
  EXPECT_NEAR(matrix(1, 1), 2007, EPSILON);
  EXPECT_THROW(matrix1 * matrix3, std::invalid_argument);
}

TEST(TEST_, EQUAL_TEST) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  S21Matrix matrix3(2, 2);
  S21Matrix matrix4(3, 2);

  matrix1(0, 0) = 1.02;
  matrix1(0, 1) = -2.04;
  matrix1(1, 0) = 3.000006;
  matrix1(1, 1) = 0;

  matrix2(0, 0) = 1.02;
  matrix2(0, 1) = -2.04;
  matrix2(1, 0) = 3.6;
  matrix2(1, 1) = 0;

  matrix3(0, 0) = 1.02;
  matrix3(0, 1) = -2.04;
  matrix3(1, 0) = 3.000006;
  matrix3(1, 1) = 0;

  matrix4(0, 0) = 1.02;
  matrix4(0, 1) = -2.04;
  matrix4(1, 0) = 3.000006;
  matrix4(1, 1) = 0;

  EXPECT_TRUE(matrix1 == matrix3);
  EXPECT_FALSE(matrix1 == matrix2);
  EXPECT_FALSE(matrix3 == matrix2);
  EXPECT_FALSE(matrix1 == matrix4);
  EXPECT_FALSE(matrix4 == matrix2);
}

TEST(TEST_, TRANSPOSE_TEST) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(1, 2) = 6;
  matrix(2, 0) = 7;
  matrix(2, 1) = 8;
  matrix(2, 2) = 9;
  matrix = matrix.Transpose();

  EXPECT_EQ(matrix.getRows(), 3);
  EXPECT_EQ(matrix.getCols(), 3);

  EXPECT_NEAR(matrix(0, 0), 1, EPSILON);
  EXPECT_NEAR(matrix(0, 1), 4, EPSILON);
  EXPECT_NEAR(matrix(0, 2), 7, EPSILON);
  EXPECT_NEAR(matrix(1, 0), 2, EPSILON);
  EXPECT_NEAR(matrix(1, 1), 5, EPSILON);
  EXPECT_NEAR(matrix(1, 2), 8, EPSILON);
  EXPECT_NEAR(matrix(2, 0), 3, EPSILON);
  EXPECT_NEAR(matrix(2, 1), 6, EPSILON);
  EXPECT_NEAR(matrix(2, 2), 9, EPSILON);
}

TEST(TEST_, DETERMINANT_TEST_1) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(1, 2) = 6;
  matrix(2, 0) = 7;
  matrix(2, 1) = 8;
  matrix(2, 2) = 9;
  double determinant = matrix.Determinant();
  EXPECT_EQ(determinant, 0);
}

TEST(TEST_, DETERMINANT_TEST_2) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 5;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(1, 2) = -0.5;
  matrix(2, 0) = 7;
  matrix(2, 1) = 4;
  matrix(2, 2) = 9;
  double determinant = matrix.Determinant();
  EXPECT_NEAR(determinant, 99, EPSILON);
}

TEST(TEST_, DETERMINANT_TEST_3) {
  S21Matrix invalid_matrix(3, 2);
  EXPECT_THROW(invalid_matrix.Determinant(), std::invalid_argument);
}

TEST(TEST_, CALC_COMPLEMENTS_TEST) {
  S21Matrix matrix1(3, 3);
  matrix1[0][0] = 1;
  matrix1[0][1] = 2;
  matrix1[0][2] = 3;
  matrix1[1][0] = 0;
  matrix1[1][1] = 4;
  matrix1[1][2] = 2;
  matrix1[2][0] = 5;
  matrix1[2][1] = 2;
  matrix1[2][2] = 1;
  S21Matrix complements = matrix1.CalcComplements();

  EXPECT_EQ(complements.getRows(), 3);
  EXPECT_EQ(complements.getCols(), 3);

  EXPECT_NEAR(complements(0, 0), -0, EPSILON);
  EXPECT_NEAR(complements(0, 1), 10, EPSILON);
  EXPECT_NEAR(complements(0, 2), -20, EPSILON);
  EXPECT_NEAR(complements(1, 0), 4, EPSILON);
  EXPECT_NEAR(complements(1, 1), -14, EPSILON);
  EXPECT_NEAR(complements(1, 2), 8, EPSILON);
  EXPECT_NEAR(complements(2, 0), -8, EPSILON);
  EXPECT_NEAR(complements(2, 1), -2, EPSILON);
  EXPECT_NEAR(complements(2, 2), 4, EPSILON);
}

TEST(TEST_, INVERSE_MATRIX_TEST) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 2;
  matrix(0, 1) = 5;
  matrix(0, 2) = 7;
  matrix(1, 0) = 6;
  matrix(1, 1) = 3;
  matrix(1, 2) = 4;
  matrix(2, 0) = 5;
  matrix(2, 1) = -2;
  matrix(2, 2) = -3;
  S21Matrix inverse = matrix.InverseMatrix();

  EXPECT_EQ(inverse.getRows(), 3);
  EXPECT_EQ(inverse.getCols(), 3);
  EXPECT_NEAR(inverse(0, 0), 1, EPSILON);
  EXPECT_NEAR(inverse(0, 1), -1, EPSILON);
  EXPECT_NEAR(inverse(0, 2), 1, EPSILON);
  EXPECT_NEAR(inverse(1, 0), -38, EPSILON);
  EXPECT_NEAR(inverse(1, 1), 41, EPSILON);
  EXPECT_NEAR(inverse(1, 2), -34, EPSILON);
  EXPECT_NEAR(inverse(2, 0), 27, EPSILON);
  EXPECT_NEAR(inverse(2, 1), -29, EPSILON);
  EXPECT_NEAR(inverse(2, 2), 24, EPSILON);
}

TEST(TEST_, OVERLOADING_TEST) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 2.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 2.0;
  matrix1(1, 1) = 2.0;
  S21Matrix matrix2(matrix1);
  matrix1 += matrix2;
  EXPECT_NEAR(matrix1(0, 0), 4, EPSILON);
  EXPECT_NEAR(matrix1(0, 1), 4, EPSILON);
  EXPECT_NEAR(matrix1(1, 0), 4, EPSILON);
  EXPECT_NEAR(matrix1(1, 1), 4, EPSILON);
  matrix1 *= matrix2;
  EXPECT_NEAR(matrix1(0, 0), 16, EPSILON);
  EXPECT_NEAR(matrix1(0, 1), 16, EPSILON);
  EXPECT_NEAR(matrix1(1, 0), 16, EPSILON);
  EXPECT_NEAR(matrix1(1, 1), 16, EPSILON);
  matrix1 -= matrix2;
  EXPECT_NEAR(matrix1(0, 0), 14, EPSILON);
  EXPECT_NEAR(matrix1(0, 1), 14, EPSILON);
  EXPECT_NEAR(matrix1(1, 0), 14, EPSILON);
  EXPECT_NEAR(matrix1(1, 1), 14, EPSILON);
  matrix1 *= 2.0;
  EXPECT_NEAR(matrix1(0, 0), 28, EPSILON);
  EXPECT_NEAR(matrix1(0, 1), 28, EPSILON);
  EXPECT_NEAR(matrix1(1, 0), 28, EPSILON);
  EXPECT_NEAR(matrix1(1, 1), 28, EPSILON);
  double n = 2.0;
  S21Matrix matrix3 = n * matrix1;
  EXPECT_NEAR(matrix3(0, 0), 56, EPSILON);
  EXPECT_NEAR(matrix3(0, 1), 56, EPSILON);
  EXPECT_NEAR(matrix3(1, 0), 56, EPSILON);
  EXPECT_NEAR(matrix3(1, 1), 56, EPSILON);

  EXPECT_FALSE(matrix1 == matrix2);
}

TEST(TEST_, OVERLOADING_TEST_2) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 2;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 2;
  matrix1(1, 1) = 2;
  S21Matrix matrix2(matrix1);
  S21Matrix result = matrix1 + matrix2;
  EXPECT_NEAR(result(0, 0), 4, EPSILON);
  EXPECT_NEAR(result(0, 1), 4, EPSILON);
  EXPECT_NEAR(result(1, 0), 4, EPSILON);
  EXPECT_NEAR(result(1, 1), 4, EPSILON);
  result = matrix1 * matrix2;
  EXPECT_NEAR(result(0, 0), 8, EPSILON);
  EXPECT_NEAR(result(0, 1), 8, EPSILON);
  EXPECT_NEAR(result(1, 0), 8, EPSILON);
  EXPECT_NEAR(result(1, 1), 8, EPSILON);
  result = matrix1 - matrix2;
  EXPECT_NEAR(result(0, 0), 0, EPSILON);
  EXPECT_NEAR(result(0, 1), 0, EPSILON);
  EXPECT_NEAR(result(1, 0), 0, EPSILON);
  EXPECT_NEAR(result(1, 1), 0, EPSILON);
  result = matrix1 * 2;
  EXPECT_NEAR(result(0, 0), 4, EPSILON);
  EXPECT_NEAR(result(0, 1), 4, EPSILON);
  EXPECT_NEAR(result(1, 0), 4, EPSILON);
  EXPECT_NEAR(result(1, 1), 4, EPSILON);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
