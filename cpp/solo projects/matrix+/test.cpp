#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(arif, arif_1) {
  S21Matrix A(3, 3);
  A.getmatrix()[0][0] = 2.5;
  A.getmatrix()[0][1] = 3.5;
  A.getmatrix()[0][2] = 4.5;
  A.getmatrix()[1][0] = 5.5;
  A.getmatrix()[1][1] = 6.5;
  A.getmatrix()[1][2] = 7.5;
  A.getmatrix()[2][0] = 8.5;
  A.getmatrix()[2][1] = 9.5;
  A.getmatrix()[2][2] = 0.5;
  ASSERT_FLOAT_EQ(A(1, 1), 2.5);
  S21Matrix B(3, 3);
  B.getmatrix()[0][0] = 2.5;
  B.getmatrix()[0][1] = 3.5;
  B.getmatrix()[0][2] = 4.5;
  B.getmatrix()[1][0] = 5.5;
  B.getmatrix()[1][1] = 6.5;
  B.getmatrix()[1][2] = 7.5;
  B.getmatrix()[2][0] = 8.5;
  B.getmatrix()[2][1] = 9.5;
  B.getmatrix()[2][2] = 0.5;
  A.SumMatrix(B);
  S21Matrix Z = A.InverseMatrix();
  S21Matrix G;
  G.getmatrix()[0][0] = -1.1333333;
  G.getmatrix()[0][1] = 1.0166666;
  G.getmatrix()[0][2] = -0.05;
  G.getmatrix()[1][0] = 0.6833333;
  G.getmatrix()[1][1] = -0.6166666;
  G.getmatrix()[1][2] = 0.1;
  G.getmatrix()[2][0] = -0.05;
  G.getmatrix()[2][1] = 0.1;
  G.getmatrix()[2][2] = -0.05;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_FALSE(fabs(Z.getmatrix()[i][j] - G.getmatrix()[i][j]) > 1e-7);
    }
  }
  S21Matrix C(3, 3);
  C.getmatrix()[0][0] = 2.5 * 2;
  C.getmatrix()[0][1] = 3.5 * 2;
  C.getmatrix()[0][2] = 4.5 * 2;
  C.getmatrix()[1][0] = 5.5 * 2;
  C.getmatrix()[1][1] = 6.5 * 2;
  C.getmatrix()[1][2] = 7.5 * 2;
  C.getmatrix()[2][0] = 8.5 * 2;
  C.getmatrix()[2][1] = 9.5 * 2;
  C.getmatrix()[2][2] = 0.5 * 2;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_FLOAT_EQ(A.getmatrix()[i][j], C.getmatrix()[i][j]);
    }
  }
  A.SubMatrix(B);
  A += B;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_FLOAT_EQ(A.getmatrix()[i][j], C.getmatrix()[i][j]);
    }
  }
  A -= B;
  A.MulNumber(2.0);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_FLOAT_EQ(A.getmatrix()[i][j], C.getmatrix()[i][j]);
    }
  }
  A = A * 0.5;
  A = A + B;
  A = A - B;
  A *= 2;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_FLOAT_EQ(A.getmatrix()[i][j], C.getmatrix()[i][j]);
    }
  }
  A *= 0.5;
  A.MulMatrix(B);
  C.getmatrix()[0][0] = 63.75;
  C.getmatrix()[0][1] = 74.25;
  C.getmatrix()[0][2] = 39.75;
  C.getmatrix()[1][0] = 113.25;
  C.getmatrix()[1][1] = 132.75;
  C.getmatrix()[1][2] = 77.25;
  C.getmatrix()[2][0] = 77.75;
  C.getmatrix()[2][1] = 96.25;
  C.getmatrix()[2][2] = 109.75;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_FLOAT_EQ(A.getmatrix()[i][j], C.getmatrix()[i][j]);
    }
  }
  double det = A.Determinant();
  ASSERT_FLOAT_EQ(det, 900);
  ASSERT_FALSE(A.EqMatrix(B));
  ASSERT_TRUE(A == A);
  A.getmatrix()[0][0] = 2.5;
  A.getmatrix()[0][1] = 3.5;
  A.getmatrix()[0][2] = 4.5;
  A.getmatrix()[1][0] = 5.5;
  A.getmatrix()[1][1] = 6.5;
  A.getmatrix()[1][2] = 7.5;
  A.getmatrix()[2][0] = 8.5;
  A.getmatrix()[2][1] = 9.5;
  A.getmatrix()[2][2] = 0.5;
  A *= B;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_FLOAT_EQ(A.getmatrix()[i][j], C.getmatrix()[i][j]);
    }
  }
  A.getmatrix()[0][0] = 2.5;
  A.getmatrix()[0][1] = 3.5;
  A.getmatrix()[0][2] = 4.5;
  A.getmatrix()[1][0] = 5.5;
  A.getmatrix()[1][1] = 6.5;
  A.getmatrix()[1][2] = 7.5;
  A.getmatrix()[2][0] = 8.5;
  A.getmatrix()[2][1] = 9.5;
  A.getmatrix()[2][2] = 0.5;

  G.getmatrix()[0][0] = 1;
  G.getmatrix()[0][1] = 0;
  G.getmatrix()[0][2] = 0;
  G.getmatrix()[1][0] = 0;
  G.getmatrix()[1][1] = 1;
  G.getmatrix()[1][2] = 0;
  G.getmatrix()[2][0] = 0;
  G.getmatrix()[2][1] = 0;
  G.getmatrix()[2][2] = 1;
  B = B * G;
  ASSERT_TRUE(A == B);
  S21Matrix S = A;
  S21Matrix D = move(B);
  S = D;
}

TEST(throws, throw_1) {
  S21Matrix A(1, 2);
  S21Matrix B(3, 4);
  ASSERT_FALSE(A.EqMatrix(B));
  ASSERT_ANY_THROW(S21Matrix A(-1, 9));
  S21Matrix D = move(A);
  ASSERT_ANY_THROW(A(1, 1));
  ASSERT_ANY_THROW(B(54, 1));
  ASSERT_ANY_THROW(A.EqMatrix(B));
  ASSERT_ANY_THROW(A.SumMatrix(B));
  ASSERT_ANY_THROW(D.SumMatrix(B));
  ASSERT_ANY_THROW(A.SubMatrix(B));
  ASSERT_ANY_THROW(D.SubMatrix(B));
  ASSERT_ANY_THROW(A.MulNumber(2));
  ASSERT_ANY_THROW(A.MulMatrix(B));
  ASSERT_ANY_THROW(D.MulMatrix(B));
  ASSERT_ANY_THROW(A.Transpose());
  ASSERT_ANY_THROW(A.CalcComplements());
  ASSERT_ANY_THROW(B.CalcComplements());
  ASSERT_ANY_THROW(A.Determinant());
  ASSERT_ANY_THROW(B.Determinant());
  ASSERT_ANY_THROW(A.InverseMatrix());
  ASSERT_ANY_THROW(B.InverseMatrix());
  ASSERT_ANY_THROW(A = A + B);
  ASSERT_ANY_THROW(D = D + B);
  ASSERT_ANY_THROW(A = A - B);
  ASSERT_ANY_THROW(D = D - B);
  ASSERT_ANY_THROW(A = A * B);
  ASSERT_ANY_THROW(D = D * B);
  ASSERT_ANY_THROW(A = A * 2);
  ASSERT_ANY_THROW(A == B);
  ASSERT_ANY_THROW(A += B);
  ASSERT_ANY_THROW(D += B);
  ASSERT_ANY_THROW(A -= B);
  ASSERT_ANY_THROW(D -= B);
  ASSERT_ANY_THROW(A *= B);
  ASSERT_ANY_THROW(D *= B);
  ASSERT_ANY_THROW(A *= 2);
  S21Matrix ZOV(1, 1);
  ASSERT_NO_THROW(ZOV.CalcComplements());
  ASSERT_NO_THROW(ZOV.Determinant());
  S21Matrix CBO(2, 2);
  CBO.getmatrix()[0][0] = 1;
  CBO.getmatrix()[0][1] = 1;
  CBO.getmatrix()[1][0] = 1;
  CBO.getmatrix()[1][1] = 1;
  ASSERT_ANY_THROW(CBO.InverseMatrix());
  ASSERT_NO_THROW(CBO = CBO);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}