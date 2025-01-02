#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <exception>
#include <iostream>
#include <utility>

class S21Matrix final {
 public:
  S21Matrix() noexcept;                    // Default constructor
  explicit S21Matrix(int rows, int cols);  // matrix rows*cols size
  S21Matrix(const S21Matrix& other);       // copy
  S21Matrix(S21Matrix&& other) noexcept;   // move
  ~S21Matrix() noexcept;                   // Destructor

  int getRows() const noexcept;  // accessor
  int getCols() const noexcept;  // accessor

  void setRow(int row);  // mutator
  void setCol(int col);  // mutator

  void SumMatrix(const S21Matrix& other);
  bool EqMatrix(const S21Matrix& other) const noexcept;
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const float num) noexcept;
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() noexcept;
  S21Matrix CalcComplements() const;
  float Determinant() const;
  S21Matrix InverseMatrix() const;

  bool operator==(const S21Matrix& other) const;
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator*(float num) const noexcept;
  S21Matrix operator*(const S21Matrix& other) const;
  friend S21Matrix operator*(float num, const S21Matrix& matrix) noexcept;
  S21Matrix& operator*=(float num);
  S21Matrix& operator*=(const S21Matrix& other);

  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);

  float& operator()(int row, int col) &;
  float& operator()(int row, int col) && = delete;
  const float& operator()(int row, int col) const&;
  const float& operator()(int row, int col) const&& = delete;

 private:
  // Attributes
  int rows_, cols_;  // Rows and columns
  float* matrix_;    // Pointer to the memory where the matrix is allocated

  // Private methods
  void Free() noexcept;
  const float& GetElem(int row, int col) const;
  float Minor(int row, int col) const;
};

#endif