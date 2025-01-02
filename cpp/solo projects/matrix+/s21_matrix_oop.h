#pragma once
#include <math.h>
#include <string.h>

#include <iostream>

using namespace std;

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  ~S21Matrix();
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);

  int getrows();
  int getcols();
  double** getmatrix();

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  friend const S21Matrix operator+(const S21Matrix& my, const S21Matrix& other);
  friend const S21Matrix operator-(const S21Matrix& my, const S21Matrix& other);
  friend const S21Matrix operator*(S21Matrix& my, const S21Matrix& other);
  friend const S21Matrix operator*(const S21Matrix& other, const double num);
  friend bool operator==(S21Matrix& my, const S21Matrix& other);
  const S21Matrix& operator=(const S21Matrix& other);
  friend S21Matrix& operator+=(S21Matrix& my, const S21Matrix& other);
  friend S21Matrix& operator-=(S21Matrix& my, const S21Matrix& other);
  friend S21Matrix& operator*=(S21Matrix& my, const S21Matrix& other);
  friend S21Matrix& operator*=(S21Matrix& other, const double num);
  double operator()(int i, int j);
};